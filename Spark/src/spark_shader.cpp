#include "spark_shader.h"
#define SPARK_SHADER_REFLECTION_IMPL
#include "spark_shader_reflection.h"


#include "spark.h"


#include <glslang/Include/ResourceLimits.h>
#include <glslang/SPIRV/GlslangToSpv.h>
#include <glslang/Public/ShaderLang.h>
#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <limits.h>
#endif

#include <fstream>
#include <filesystem>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdint>

#ifndef DefaultTBuiltInResource
TBuiltInResource DefaultTBuiltInResource = {
	// ... [existing initialization] ...
	32,    // maxLights
	6,     // maxClipPlanes
	32,    // maxTextureUnits
	32,    // maxTextureCoords
	64,    // maxVertexAttribs
	4096,  // maxVertexUniformComponents
	64,    // maxVaryingFloats
	32,    // maxVertexTextureImageUnits
	80,    // maxCombinedTextureImageUnits
	32,    // maxTextureImageUnits
	4096,  // maxFragmentUniformComponents
	32,    // maxDrawBuffers
	128,   // maxVertexUniformVectors
	8,     // maxVaryingVectors
	16,    // maxFragmentUniformVectors
	16,    // maxVertexOutputVectors
	15,    // maxFragmentInputVectors
	-8,    // minProgramTexelOffset
	7,     // maxProgramTexelOffset
	8,     // maxClipDistances
	65535, // maxComputeWorkGroupCountX
	65535, // maxComputeWorkGroupCountY
	65535, // maxComputeWorkGroupCountZ
	1024,  // maxComputeWorkGroupSizeX
	1024,  // maxComputeWorkGroupSizeY
	64,    // maxComputeWorkGroupSizeZ
	1024,  // maxComputeUniformComponents
	16,    // maxComputeTextureImageUnits
	8,     // maxComputeImageUniforms
	8,     // maxComputeAtomicCounters
	1,     // maxComputeAtomicCounterBuffers
	60,    // maxVaryingComponents
	64,    // maxVertexOutputComponents
	64,    // maxGeometryInputComponents
	128,   // maxGeometryOutputComponents
	128,   // maxFragmentInputComponents
	8,     // maxImageUnits
	8,     // maxCombinedImageUnitsAndFragmentOutputs
	8,     // maxCombinedShaderOutputResources
	0,     // maxImageSamples
	0,     // maxVertexImageUniforms
	0,     // maxTessControlImageUniforms
	0,     // maxTessEvaluationImageUniforms
	0,     // maxGeometryImageUniforms
	8,     // maxFragmentImageUniforms
	8,     // maxCombinedImageUniforms
	16,    // maxGeometryTextureImageUnits
	256,   // maxGeometryOutputVertices
	1024,  // maxGeometryTotalOutputComponents
	1024,  // maxGeometryUniformComponents
	64,    // maxGeometryVaryingComponents
	128,   // maxTessControlInputComponents
	128,   // maxTessControlOutputComponents
	16,    // maxTessControlTextureImageUnits
	1024,  // maxTessControlUniformComponents
	4096,  // maxTessControlTotalOutputComponents
	128,   // maxTessEvaluationInputComponents
	128,   // maxTessEvaluationOutputComponents
	16,    // maxTessEvaluationTextureImageUnits
	1024,  // maxTessEvaluationUniformComponents
	120,   // maxTessPatchComponents
	32,    // maxPatchVertices
	64,    // maxTessGenLevel
	16,    // maxViewports
	0,     // maxVertexAtomicCounters
	0,     // maxTessControlAtomicCounters
	0,     // maxTessEvaluationAtomicCounters
	0,     // maxGeometryAtomicCounters
	8,     // maxFragmentAtomicCounters
	8,     // maxCombinedAtomicCounters
	1,     // maxAtomicCounterBindings
	0,     // maxVertexAtomicCounterBuffers
	0,     // maxTessControlAtomicCounterBuffers
	0,     // maxTessEvaluationAtomicCounterBuffers
	0,     // maxGeometryAtomicCounterBuffers
	1,     // maxFragmentAtomicCounterBuffers
	1,     // maxCombinedAtomicCounterBuffers
	16384, // maxAtomicCounterBufferSize
	4,     // maxTransformFeedbackBuffers
	64,    // maxTransformFeedbackInterleavedComponents
	8,     // maxCullDistances
	8,     // maxCombinedClipAndCullDistances
	4,     // maxSamples
	0,     // maxMeshOutputVerticesNV
	0,     // maxMeshOutputPrimitivesNV
	0,     // maxMeshWorkGroupSizeX_NV
	0,     // maxMeshWorkGroupSizeY_NV
	0,     // maxMeshWorkGroupSizeZ_NV
	0,     // maxTaskWorkGroupSizeX_NV
	0,     // maxTaskWorkGroupSizeY_NV
	0,     // maxTaskWorkGroupSizeZ_NV
	0,     // maxMeshViewCountNV
	0,     // maxMeshOutputVerticesEXT
	0,     // maxMeshOutputPrimitivesEXT
	0,     // maxMeshWorkGroupSizeX_EXT
	0,     // maxMeshWorkGroupSizeY_EXT
	0,     // maxMeshWorkGroupSizeZ_EXT
	0,     // maxTaskWorkGroupSizeX_EXT
	0,     // maxTaskWorkGroupSizeY_EXT
	0,     // maxTaskWorkGroupSizeZ_EXT
	0,     // maxMeshViewCountEXT
	0,     // maxDualSourceDrawBuffersEXT

	// TLimits struct
	{
		true, // nonInductiveForLoops
		true, // whileLoops
		true, // doWhileLoops
		true, // generalUniformIndexing
		true, // generalAttributeMatrixVectorIndexing
		true, // generalVaryingIndexing
		true, // generalSamplerIndexing
		true, // generalVariableIndexing
		true  // generalConstantMatrixVectorIndexing
	}
};
#endif

class GlslangInitializer {
public:
	GlslangInitializer() { glslang::InitializeProcess(); }
	~GlslangInitializer() { glslang::FinalizeProcess(); }
};

// Ensure that glslang is initialized before use
SPARKSTATIC GlslangInitializer glslang_initializer;

SPARKAPI SPARKSTATIC EShLanguage __SparkGetShaderStage(SparkShaderStage stage) {
	switch (stage) {
	case SPARK_SHADER_STAGE_VERTEX:
		return EShLangVertex;
	case SPARK_SHADER_STAGE_FRAGMENT:
		return EShLangFragment;
	case SPARK_SHADER_STAGE_COMPUTE:
		return EShLangCompute;
	case SPARK_SHADER_STAGE_GEOMETRY:
		return EShLangGeometry;
	case SPARK_SHADER_STAGE_TESS_CONTROL:
		return EShLangTessControl;
	case SPARK_SHADER_STAGE_TESS_EVALUATION:
		return EShLangTessEvaluation;
	default:
		return EShLangVertex; // Default to vertex shader
	}
}

SPARKAPI SPARKSTATIC std::string __SparkShaderStageToString(SparkShaderStage stage) {
	switch (stage) {
	case SPARK_SHADER_STAGE_VERTEX:
		return "vertex";
	case SPARK_SHADER_STAGE_FRAGMENT:
		return "fragment";
	case SPARK_SHADER_STAGE_COMPUTE:
		return "compute";
	case SPARK_SHADER_STAGE_GEOMETRY:
		return "geometry";
	case SPARK_SHADER_STAGE_TESS_CONTROL:
		return "tess_control";
	case SPARK_SHADER_STAGE_TESS_EVALUATION:
		return "tess_evaluation";
	default:
		return "unknown";
	}
}

SPARKAPI SPARKSTATIC std::string __SparkReadFile(const std::filesystem::path& path) {
	std::ifstream file_stream(path, std::ios::in | std::ios::binary);
	if (!file_stream) {
		SPARK_LOG_ERROR("Could not open file %s", path.string().c_str());
		return "";
	}

	std::stringstream string_stream;
	string_stream << file_stream.rdbuf();
	file_stream.close();

	return string_stream.str();
}

SPARKAPI SPARKSTATIC bool __SparkFileExists(const std::filesystem::path& path) {
	return std::filesystem::exists(path);
}

struct SHA256_CTX {
	SparkU32 state[8];
	SparkU64 bitcount;
	SparkU8 buffer[64];
};

const SparkU32 k[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf,
	0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98,
	0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7,
	0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f,
	0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8,
	0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85,
	0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e,
	0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819,
	0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c,
	0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee,
	0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7,
	0xc67178f2
};

SPARKAPI SPARKSTATIC SparkVoid __SparkSHA256_Init(SHA256_CTX* ctx) {
	ctx->bitcount = 0;
	ctx->state[0] = 0x6a09e667;
	ctx->state[1] = 0xbb67ae85;
	ctx->state[2] = 0x3c6ef372;
	ctx->state[3] = 0xa54ff53a;
	ctx->state[4] = 0x510e527f;
	ctx->state[5] = 0x9b05688c;
	ctx->state[6] = 0x1f83d9ab;
	ctx->state[7] = 0x5be0cd19;
}

SPARKAPI SPARKSTATIC SparkU32 __SparkRotRight(SparkU32 a, SparkU32 b) {
	return ((a >> b) | (a << (32 - b)));
}

SPARKAPI SPARKSTATIC SparkVoid __SparkSHA256_Transform(SHA256_CTX* ctx, const SparkU8 data[]) {
	SparkU32 a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];

	for (i = 0, j = 0; i < 16; ++i, j += 4)
		m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
	for (; i < 64; ++i)
		m[i] = __SparkRotRight(m[i - 2], 17) ^ __SparkRotRight(m[i - 2], 19) ^ (m[i - 2] >> 10) +
		m[i - 7] + __SparkRotRight(m[i - 15], 7) ^ __SparkRotRight(m[i - 15], 18) ^ (m[i - 15] >> 3) +
		m[i - 16];

	a = ctx->state[0];
	b = ctx->state[1];
	c = ctx->state[2];
	d = ctx->state[3];
	e = ctx->state[4];
	f = ctx->state[5];
	g = ctx->state[6];
	h = ctx->state[7];

	for (i = 0; i < 64; ++i) {
		t1 = h + (__SparkRotRight(e, 6) ^ __SparkRotRight(e, 11) ^ __SparkRotRight(e, 25)) +
			((e & f) ^ (~e & g)) + k[i] + m[i];
		t2 = (__SparkRotRight(a, 2) ^ __SparkRotRight(a, 13) ^ __SparkRotRight(a, 22)) +
			((a & b) ^ (a & c) ^ (b & c));
		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;
	}

	ctx->state[0] += a;
	ctx->state[1] += b;
	ctx->state[2] += c;
	ctx->state[3] += d;
	ctx->state[4] += e;
	ctx->state[5] += f;
	ctx->state[6] += g;
	ctx->state[7] += h;
}

SPARKAPI SPARKSTATIC SparkVoid __SparkSHA256_Update(SHA256_CTX* ctx, const SparkU8 data[], size_t len) {
	size_t i = 0;

	for (i = 0; i < len; ++i) {
		ctx->buffer[ctx->bitcount / 8 % 64] = data[i];
		ctx->bitcount += 8;
		if ((ctx->bitcount / 8) % 64 == 0)
			__SparkSHA256_Transform(ctx, ctx->buffer);
	}
}

SPARKAPI SPARKSTATIC SparkVoid __SparkSHA256_Final(SHA256_CTX* ctx, SparkU8 hash[]) {
	SparkU8 finalcount[8];
	SparkU32 i;

	for (i = 0; i < 8; ++i)
		finalcount[i] = (SparkU8)((ctx->bitcount >> ((7 - i) * 8)) & 0xFF);

	SparkU8 c = 0x80;
	__SparkSHA256_Update(ctx, &c, 1);

	while ((ctx->bitcount / 8) % 64 != 56) {
		c = 0x00;
		__SparkSHA256_Update(ctx, &c, 1);
	}

	__SparkSHA256_Update(ctx, finalcount, 8);

	for (i = 0; i < 8; ++i) {
		hash[i * 4] = (ctx->state[i] >> 24) & 0xFF;
		hash[i * 4 + 1] = (ctx->state[i] >> 16) & 0xFF;
		hash[i * 4 + 2] = (ctx->state[i] >> 8) & 0xFF;
		hash[i * 4 + 3] = ctx->state[i] & 0xFF;
	}
}

SPARKAPI SPARKSTATIC std::string __SparkComputeSHA256(const std::string& data) {
	SHA256_CTX ctx;
	SparkU8 hash[32];
	SparkI8 buf[3];
	buf[2] = 0;

	__SparkSHA256_Init(&ctx);
	__SparkSHA256_Update(&ctx, reinterpret_cast<const SparkU8*>(data.c_str()), data.size());
	__SparkSHA256_Final(&ctx, hash);

	std::stringstream ss;
	for (SparkI32 i = 0; i < 32; ++i) {
		sprintf(buf, "%02x", hash[i]);
		ss << buf;
	}

	return ss.str();
}

SPARKAPI SPARKSTATIC bool __SparkEnsureDirectoryExists(const std::filesystem::path& dir_path) {
	std::error_code ec;
	if (!std::filesystem::exists(dir_path, ec)) {
		if (!std::filesystem::create_directories(dir_path, ec)) {
			SPARK_LOG_ERROR("Could not create directory %s: %s",
				dir_path.string().c_str(), ec.message().c_str());
			return false;
		}
	}
	return true;
}

SPARKAPI SPARKSTATIC std::filesystem::path __SparkGetExecutablePath() {
#ifdef _WIN32
	char path[MAX_PATH];
	HMODULE hModule = GetModuleHandle(nullptr);
	if (hModule != nullptr) {
		DWORD length = GetModuleFileNameA(hModule, path, MAX_PATH);
		if (length > 0 && length < MAX_PATH) {
			return std::filesystem::path(path).parent_path();
		}
		else {
			// Handle error
			return std::filesystem::current_path();
		}
	}
	else {
		// Handle error
		return std::filesystem::current_path();
	}
#else
	char result[PATH_MAX];
	ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
	if (count != -1) {
		return std::filesystem::path(std::string(result, count)).parent_path();
	}
	else {
		// Handle error
		return std::filesystem::current_path();
	}
#endif
}

SPARKAPI SPARKSTATIC SparkVoid __SparkGetCacheDirectories(const std::filesystem::path& /*source_path*/,
	std::filesystem::path& compiled_shaders_dir,
	std::filesystem::path& hashed_shaders_dir) {
	// Get the executable directory
	std::filesystem::path exe_dir = __SparkGetExecutablePath();

	// Set the cache directories inside the executable directory
	compiled_shaders_dir = exe_dir / "compiled_shaders";
	hashed_shaders_dir = exe_dir / "hashed_shaders";
}

SPARKAPI SPARKSTATIC std::string __SparkGetShaderHash(const std::string& source_code) {
	return __SparkComputeSHA256(source_code);
}

SPARKAPI SPARKSTATIC std::filesystem::path __SparkGetHashFilePath(const std::filesystem::path& hashed_shaders_dir,
	const std::filesystem::path& source_path, SparkShaderStage stage) {
	std::string hash_filename = source_path.stem().string() + "_" +
		__SparkShaderStageToString(stage) + ".hash";
	return hashed_shaders_dir / hash_filename;
}

SPARKAPI SPARKSTATIC std::filesystem::path __SparkGetCompiledSpirvPath(const std::filesystem::path& compiled_shaders_dir,
	const std::filesystem::path& source_path, SparkShaderStage stage) {
	std::string spirv_filename = source_path.stem().string() + "_" +
		__SparkShaderStageToString(stage) + ".spv";
	return compiled_shaders_dir / spirv_filename;
}

SPARKAPI SPARKSTATIC bool __SparkReadHashFromFile(const std::filesystem::path& hash_path, std::string& stored_hash) {
	std::ifstream hash_file(hash_path, std::ios::in);
	if (!hash_file) {
		SPARK_LOG_ERROR("Could not open hash file %s", hash_path.string().c_str());
		return false;
	}

	std::getline(hash_file, stored_hash);
	hash_file.close();
	return true;
}

SPARKAPI SPARKSTATIC bool __SparkWriteHashToFile(const std::filesystem::path& hash_path, const std::string& hash) {
	std::ofstream hash_file(hash_path, std::ios::out | std::ios::trunc);
	if (!hash_file) {
		SPARK_LOG_ERROR("Could not write hash file %s", hash_path.string().c_str());
		return false;
	}

	hash_file << hash;
	hash_file.close();
	return true;
}

SPARKAPI SPARKSTATIC SparkResult __SparkGetCodeFromCache(
	SparkHandle* spirv_data,
	SparkSize* spirv_size,
	SparkConstString compiled_spirv_path) {

	// Hashes match; cache is valid
	// Read the compiled SPIR-V binary
	std::ifstream spirv_file(compiled_spirv_path, std::ios::in | std::ios::binary | std::ios::ate);
	if (!spirv_file) {
		SPARK_LOG_ERROR("Could not open compiled SPIR-V file %s", compiled_spirv_path);
		return SPARK_ERROR_INVALID;
	}

	std::streamsize size = spirv_file.tellg();
	spirv_file.seekg(0, std::ios::beg);

	// Allocate memory for SPIR-V data
	*spirv_data = (SparkBuffer)malloc(size);
	if (!(*spirv_data)) {
		SPARK_LOG_ERROR("Memory allocation failed for SPIR-V data");
		return SPARK_ERROR_OUT_OF_MEMORY;
	}

	if (!spirv_file.read(reinterpret_cast<char*>(*spirv_data), size)) {
		SPARK_LOG_ERROR("Failed to read compiled SPIR-V file %s", compiled_spirv_path);
		free(*spirv_data);
		*spirv_data = nullptr;
		return SPARK_ERROR_INVALID;
	}

	*spirv_size = static_cast<SparkSize>(size);
	SPARK_LOG_INFO("Loaded SPIR-V from cache: %s", compiled_spirv_path);
	return SPARK_SUCCESS;
}

extern "C" {
	SPARKAPI SparkResult SparkCompileShaderToSpirv(
		SparkConstString source,
		SparkShaderStage shader_stage,
		SparkShaderReflectionData reflection_data) {

		if (!source || !reflection_data) {
			return SPARK_ERROR_INVALID_ARGUMENT;
		}

		EShLanguage stage = __SparkGetShaderStage(shader_stage);
		std::filesystem::path source_path = std::filesystem::absolute(source);

		// Determine cache directories
		std::filesystem::path compiled_shaders_dir;
		std::filesystem::path hashed_shaders_dir;
		__SparkGetCacheDirectories(source_path, compiled_shaders_dir, hashed_shaders_dir);

		// Ensure cache directories exist
		if (!__SparkEnsureDirectoryExists(compiled_shaders_dir) ||
			!__SparkEnsureDirectoryExists(hashed_shaders_dir)) {
			SPARK_LOG_ERROR("Failed to ensure cache directories exist.");
			return SPARK_ERROR_INVALID;
		}

		// Determine cache file paths
		std::filesystem::path compiled_spirv_path = __SparkGetCompiledSpirvPath(compiled_shaders_dir, source_path, shader_stage);
		std::filesystem::path hash_file_path = __SparkGetHashFilePath(hashed_shaders_dir, source_path, shader_stage);
		std::filesystem::path reflection_path = compiled_shaders_dir /
			(source_path.stem().string() + "_" + __SparkShaderStageToString(shader_stage) + ".ref");

		// Read shader source code
		std::string source_code = __SparkReadFile(source_path);
		if (source_code.empty()) {
			SPARK_LOG_ERROR("Shader source is empty or could not be read.");

			// Try loading from cache if available
			std::string stored_hash;
			if (__SparkFileExists(compiled_spirv_path) && __SparkFileExists(hash_file_path) && __SparkReadHashFromFile(hash_file_path, stored_hash)) {
				SparkResult res = __SparkGetCodeFromCache(&reflection_data->spirv_data, &reflection_data->spirv_size, compiled_spirv_path.string().c_str());
				if (res == SPARK_SUCCESS && __SparkFileExists(reflection_path)) {
					// Load reflection data from cache
					if (!SparkReadReflectionDataFromFile(reflection_path, reflection_data)) {
						SPARK_LOG_WARN("Failed to load reflection data from cache. Reflection data might be missing.");
					}
				}
				return res;
			}
			return SPARK_ERROR_INVALID;
		}

		// Compute current shader hash
		std::string current_hash = __SparkComputeSHA256(source_code);

		// Check if we can use the cached version
		std::string stored_hash;
		__SparkReadHashFromFile(hash_file_path, stored_hash);

		if (!stored_hash.empty() && stored_hash == current_hash && __SparkFileExists(compiled_spirv_path) && __SparkFileExists(reflection_path)) {
			// Load from cache
			SparkResult res = __SparkGetCodeFromCache(&reflection_data->spirv_data, &reflection_data->spirv_size, compiled_spirv_path.string().c_str());
			if (res == SPARK_SUCCESS) {
				// Load reflection data
				if (!SparkReadReflectionDataFromFile(reflection_path, reflection_data)) {
					SPARK_LOG_WARN("Failed to load reflection data from cache. Will need to re-reflect if needed.");
				}
			}
			return res;
		}

		SPARK_LOG_INFO("Hash mismatch or missing cache. Recompiling shader: %s", source_path.string().c_str());

		SparkConstString shader_source_cstr = source_code.c_str();

		glslang::TShader shader(stage);
		shader.setStrings(&shader_source_cstr, 1);

		const SparkI32 default_version = 100;
		glslang::EShTargetClientVersion client_version = glslang::EShTargetVulkan_1_0;
		glslang::EShTargetLanguageVersion target_version = glslang::EShTargetSpv_1_0;

		shader.setEnvInput(glslang::EShSourceGlsl, stage, glslang::EShClientVulkan, default_version);
		shader.setEnvClient(glslang::EShClientVulkan, client_version);
		shader.setEnvTarget(glslang::EShTargetSpv, target_version);

		TBuiltInResource resources = DefaultTBuiltInResource;
		EShMessages messages = (EShMessages)(EShMsgSpvRules | EShMsgVulkanRules);

		if (!shader.parse(&resources, default_version, false, messages)) {
			std::string log = shader.getInfoLog();
			fprintf(stderr, "Shader compilation error:%s\n", log.c_str());
			return SPARK_ERROR_INVALID;
		}

		glslang::TProgram program;
		program.addShader(&shader);

		if (!program.link(messages)) {
			std::string log = program.getInfoLog();
			fprintf(stderr, "Shader linking error:%s\n", log.c_str());
			return SPARK_ERROR_INVALID;
		}

		// Convert to SPIR-V
		std::vector<SparkU32> spirv;
		glslang::GlslangToSpv(*program.getIntermediate(stage), spirv);

		// Allocate memory for SPIR-V data
		size_t byte_size = spirv.size() * sizeof(SparkU32);
		reflection_data->spirv_data = (SparkBuffer)malloc(byte_size);
		if (!reflection_data->spirv_data) {
			SPARK_LOG_ERROR("Memory allocation failed for SPIR-V data");
			return SPARK_ERROR_OUT_OF_MEMORY;
		}

		memcpy(reflection_data->spirv_data, spirv.data(), byte_size);
		reflection_data->spirv_size = byte_size;
		reflection_data->stage = shader_stage;

		// Write SPIR-V to cache
		{
			std::ofstream spirv_file_out(compiled_spirv_path, std::ios::out | std::ios::binary | std::ios::trunc);
			if (!spirv_file_out) {
				SPARK_LOG_WARN("Could not write compiled SPIR-V cache file %s", compiled_spirv_path.string().c_str());
			}
			else {
				spirv_file_out.write(reinterpret_cast<const char*>(spirv.data()), byte_size);
				spirv_file_out.close();
				SPARK_LOG_INFO("Compiled and cached SPIR-V: %s", compiled_spirv_path.string().c_str());
			}
		}

		// Reflection extraction
		{
			spirv_cross::Compiler comp(spirv);
			SparkExtractAllResources(comp, reflection_data);
		}

		// Write reflection data to cache
		if (!SparkWriteReflectionDataToFile(reflection_path, reflection_data)) {
			SPARK_LOG_WARN("Could not write reflection data cache file %s", reflection_path.string().c_str());
		}
		else {
			SPARK_LOG_INFO("Compiled and cached reflection data: %s", reflection_path.string().c_str());
		}

		// Write the current hash to the hash file
		if (!__SparkWriteHashToFile(hash_file_path, current_hash)) {
			SPARK_LOG_WARN("Could not write hash file %s", hash_file_path.string().c_str());
		}
		else {
			SPARK_LOG_INFO("Stored shader hash: %s", hash_file_path.string().c_str());
		}

		return SPARK_SUCCESS; // Success
	}
} // extern "C"
