// shader_compiler.cpp

#include "spark_shader.h"
#include "spark.h"

// Include glslang headers
#include <glslang/Include/ResourceLimits.h>
#include <glslang/Public/ShaderLang.h>
#include <glslang/SPIRV/GlslangToSpv.h>

#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <limits.h>
#endif

#include <fstream>
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

// Namespace to avoid naming conflicts
namespace {

    class GlslangInitializer {
    public:
        GlslangInitializer() { glslang::InitializeProcess(); }
        ~GlslangInitializer() { glslang::FinalizeProcess(); }
    };

    // Ensure that glslang is initialized before use
    static GlslangInitializer glslangInitializer;

    // Helper function to map ShaderStage enum to glslang stage
    EShLanguage GetShaderStage(SparkShaderStage stage) {
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

    std::string ShaderStageToString(SparkShaderStage stage) {
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


    std::string ReadFile(const std::filesystem::path& path) {
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

    inline bool FileExists(const std::filesystem::path& path) {
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

    void SHA256_Init(SHA256_CTX* ctx) {
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

    SparkU32 ROTRIGHT(SparkU32 a, SparkU32 b) {
        return ((a >> b) | (a << (32 - b)));
    }

    void SHA256_Transform(SHA256_CTX* ctx, const SparkU8 data[]) {
        SparkU32 a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];

        for (i = 0, j = 0; i < 16; ++i, j += 4)
            m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
        for (; i < 64; ++i)
            m[i] = ROTRIGHT(m[i - 2], 17) ^ ROTRIGHT(m[i - 2], 19) ^ (m[i - 2] >> 10) +
            m[i - 7] + ROTRIGHT(m[i - 15], 7) ^ ROTRIGHT(m[i - 15], 18) ^ (m[i - 15] >> 3) +
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
            t1 = h + (ROTRIGHT(e, 6) ^ ROTRIGHT(e, 11) ^ ROTRIGHT(e, 25)) +
                ((e & f) ^ (~e & g)) + k[i] + m[i];
            t2 = (ROTRIGHT(a, 2) ^ ROTRIGHT(a, 13) ^ ROTRIGHT(a, 22)) +
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

    void SHA256_Update(SHA256_CTX* ctx, const SparkU8 data[], size_t len) {
        size_t i = 0;

        for (i = 0; i < len; ++i) {
            ctx->buffer[ctx->bitcount / 8 % 64] = data[i];
            ctx->bitcount += 8;
            if ((ctx->bitcount / 8) % 64 == 0)
                SHA256_Transform(ctx, ctx->buffer);
        }
    }

    void SHA256_Final(SHA256_CTX* ctx, SparkU8 hash[]) {
        SparkU8 finalcount[8];
        SparkU32 i;

        for (i = 0; i < 8; ++i)
            finalcount[i] = (SparkU8)((ctx->bitcount >> ((7 - i) * 8)) & 0xFF);

        SparkU8 c = 0x80;
        SHA256_Update(ctx, &c, 1);

        while ((ctx->bitcount / 8) % 64 != 56) {
            c = 0x00;
            SHA256_Update(ctx, &c, 1);
        }

        SHA256_Update(ctx, finalcount, 8);

        for (i = 0; i < 8; ++i) {
            hash[i * 4] = (ctx->state[i] >> 24) & 0xFF;
            hash[i * 4 + 1] = (ctx->state[i] >> 16) & 0xFF;
            hash[i * 4 + 2] = (ctx->state[i] >> 8) & 0xFF;
            hash[i * 4 + 3] = ctx->state[i] & 0xFF;
        }
    }

    std::string ComputeSHA256(const std::string& data) {
        SHA256_CTX ctx;
        SparkU8 hash[32];
        SparkI8 buf[3];
        buf[2] = 0;

        SHA256_Init(&ctx);
        SHA256_Update(&ctx, reinterpret_cast<const SparkU8*>(data.c_str()), data.size());
        SHA256_Final(&ctx, hash);

        std::stringstream ss;
        for (SparkI32 i = 0; i < 32; ++i) {
            sprintf(buf, "%02x", hash[i]);
            ss << buf;
        }

        return ss.str();
    }

    // Helper function to create directories if they don't exist
    bool EnsureDirectoryExists(const std::filesystem::path& dir_path) {
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


    // Helper function to get the executable directory
    std::filesystem::path GetExecutablePath() {
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

    // Modify the GetCacheDirectories function
    void GetCacheDirectories(const std::filesystem::path& /*source_path*/,
        std::filesystem::path& compiled_shaders_dir,
        std::filesystem::path& hashed_shaders_dir) {
        // Get the executable directory
        std::filesystem::path exe_dir = GetExecutablePath();

        // Set the cache directories inside the executable directory
        compiled_shaders_dir = exe_dir / "compiled_shaders";
        hashed_shaders_dir = exe_dir / "hashed_shaders";
    }


    // Helper function to compute the hash of the shader source
    std::string GetShaderHash(const std::string& source_code) {
        return ComputeSHA256(source_code);
    }

    std::filesystem::path GetHashFilePath(const std::filesystem::path& hashed_shaders_dir,
        const std::filesystem::path& source_path, SparkShaderStage stage) {
        std::string hash_filename = source_path.stem().string() + "_" +
            ShaderStageToString(stage) + ".hash";
        return hashed_shaders_dir / hash_filename;
    }

    std::filesystem::path GetCompiledSpirvPath(const std::filesystem::path& compiled_shaders_dir,
        const std::filesystem::path& source_path, SparkShaderStage stage) {
        std::string spirv_filename = source_path.stem().string() + "_" +
            ShaderStageToString(stage) + ".spv";
        return compiled_shaders_dir / spirv_filename;
    }

    // Helper function to read hash from file
    bool ReadHashFromFile(const std::filesystem::path& hash_path, std::string& stored_hash) {
        std::ifstream hash_file(hash_path, std::ios::in);
        if (!hash_file) {
            SPARK_LOG_ERROR("Could not open hash file %s", hash_path.string().c_str());
            return false;
        }

        std::getline(hash_file, stored_hash);
        hash_file.close();
        return true;
    }

    // Helper function to write hash to file
    bool WriteHashToFile(const std::filesystem::path& hash_path, const std::string& hash) {
        std::ofstream hash_file(hash_path, std::ios::out | std::ios::trunc);
        if (!hash_file) {
            SPARK_LOG_ERROR("Could not write hash file %s", hash_path.string().c_str());
            return false;
        }

        hash_file << hash;
        hash_file.close();
        return true;
    }

} // anonymous namespace

extern "C" {
    SPARKAPI SparkResult SparkCompileShaderToSpirv(SparkConstString source,
        SparkShaderStage shader_stage,
        SparkBuffer* spirv_data,
        SparkSize* spirv_size) {
        if (!source || !spirv_data || !spirv_size) {
            return SPARK_ERROR_INVALID_ARGUMENT;
        }

        EShLanguage stage = GetShaderStage(shader_stage);
        std::filesystem::path source_path = std::filesystem::absolute(source);

        // Determine cache directories
        std::filesystem::path compiled_shaders_dir;
        std::filesystem::path hashed_shaders_dir;
        GetCacheDirectories(source_path, compiled_shaders_dir, hashed_shaders_dir);

        // Ensure cache directories exist
        if (!EnsureDirectoryExists(compiled_shaders_dir) ||
            !EnsureDirectoryExists(hashed_shaders_dir)) {
            SPARK_LOG_ERROR("Failed to ensure cache directories exist.");
            return SPARK_ERROR_INVALID;
        }

        // Determine cache file paths
        std::filesystem::path compiled_spirv_path = GetCompiledSpirvPath(compiled_shaders_dir, source_path, shader_stage);
        std::filesystem::path hash_file_path = GetHashFilePath(hashed_shaders_dir, source_path, shader_stage);

        // Read shader source code
        std::string source_code = ReadFile(source_path);
        if (source_code.empty()) {
            SPARK_LOG_ERROR("Shader source is empty or could not be read.");
            return SPARK_ERROR_INVALID;
        }

        // Compute current shader hash
        std::string current_hash = GetShaderHash(source_code);

        bool use_cache = false;

        // Check if compiled SPIR-V and hash files exist
        if (FileExists(compiled_spirv_path) && FileExists(hash_file_path)) {
            // Read stored hash
            std::string stored_hash;
            if (ReadHashFromFile(hash_file_path, stored_hash)) {
                // Compare hashes
                if (stored_hash == current_hash) {
                    // Hashes match; cache is valid
                    // Read the compiled SPIR-V binary
                    std::ifstream spirv_file(compiled_spirv_path, std::ios::in | std::ios::binary | std::ios::ate);
                    if (!spirv_file) {
                        SPARK_LOG_ERROR("Could not open compiled SPIR-V file %s", compiled_spirv_path.string().c_str());
                        // Proceed to compile if .sprv exists but cannot be opened
                    }
                    else {
                        std::streamsize size = spirv_file.tellg();
                        spirv_file.seekg(0, std::ios::beg);

                        // Allocate memory for SPIR-V data
                        *spirv_data = (SparkBuffer)malloc(size);
                        if (!(*spirv_data)) {
                            SPARK_LOG_ERROR("Memory allocation failed for SPIR-V data");
                            return SPARK_ERROR_OUT_OF_MEMORY;
                        }

                        if (!spirv_file.read(reinterpret_cast<char*>(*spirv_data), size)) {
                            SPARK_LOG_ERROR("Failed to read compiled SPIR-V file %s", compiled_spirv_path.string().c_str());
                            free(*spirv_data);
                            *spirv_data = nullptr;
                            return SPARK_ERROR_INVALID;
                        }

                        *spirv_size = static_cast<SparkSize>(size);
                        SPARK_LOG_INFO("Loaded SPIR-V from cache: %s", compiled_spirv_path.string().c_str());
                        return SPARK_SUCCESS;
                    }
                }
                else {
                    SPARK_LOG_INFO("Shader source has changed. Recompiling shader: %s", source_path.string().c_str());
                }
            }
            else {
                SPARK_LOG_ERROR("Failed to read stored hash. Recompiling shader: %s", source_path.string().c_str());
            }
        }
        else {
            if (!FileExists(compiled_spirv_path)) {
                SPARK_LOG_INFO("Compiled SPIR-V file does not exist. Compiling shader: %s", source_path.string().c_str());
            }
            if (!FileExists(hash_file_path)) {
                SPARK_LOG_INFO("Hash file does not exist. Compiling shader: %s", source_path.string().c_str());
            }
        }

        // Proceed to compile the shader

        const char* shader_source_cstr = source_code.c_str();

        glslang::TShader shader(stage);
        shader.setStrings(&shader_source_cstr, 1);

        // Set up the environment
        const int default_version = 100;
        glslang::EShTargetClientVersion client_version = glslang::EShTargetVulkan_1_0;
        glslang::EShTargetLanguageVersion target_version = glslang::EShTargetSpv_1_0;

        shader.setEnvInput(glslang::EShSourceGlsl, stage, glslang::EShClientVulkan,
            default_version);
        shader.setEnvClient(glslang::EShClientVulkan, client_version);
        shader.setEnvTarget(glslang::EShTargetSpv, target_version);

        TBuiltInResource resources = DefaultTBuiltInResource;

        // Parse and compile the shader
        EShMessages messages = (EShMessages)(EShMsgSpvRules | EShMsgVulkanRules);

        if (!shader.parse(&resources, default_version, false, messages)) {
            // Compilation failed
            std::string log = shader.getInfoLog();
            fprintf(stderr, "Shader compilation error:%s", log.c_str());
            return SPARK_ERROR_INVALID;
        }

        glslang::TProgram program;
        program.addShader(&shader);

        // Link the program
        if (!program.link(messages)) {
            // Linking failed
            std::string log = program.getInfoLog();
            fprintf(stderr, "Shader linking error:%s", log.c_str());
            return SPARK_ERROR_INVALID;
        }

        // Convert to SPIR-V
        std::vector<SparkU32> spirv;
        glslang::GlslangToSpv(*program.getIntermediate(stage), spirv);

        // Allocate memory for SPIR-V data
        size_t byte_size = spirv.size() * sizeof(SparkU32);
        *spirv_data = (SparkBuffer)malloc(byte_size);
        if (!(*spirv_data)) {
            SPARK_LOG_ERROR("Memory allocation failed for SPIR-V data");
            return SPARK_ERROR_OUT_OF_MEMORY;
        }

        memcpy(*spirv_data, spirv.data(), byte_size);
        *spirv_size = byte_size;

        // Write the SPIR-V binary to the compiled_shaders directory for caching
        std::ofstream spirv_file_out(compiled_spirv_path, std::ios::out | std::ios::binary | std::ios::trunc);
        if (!spirv_file_out) {
            SPARK_LOG_WARN("Could not write compiled SPIR-V cache file %s", compiled_spirv_path.string().c_str());
            // Continue without caching
        }
        else {
            spirv_file_out.write(reinterpret_cast<const char*>(spirv.data()), byte_size);
            spirv_file_out.close();
            SPARK_LOG_INFO("Compiled and cached SPIR-V: %s", compiled_spirv_path.string().c_str());
        }

        // Write the current hash to the hash file
        if (!WriteHashToFile(hash_file_path, current_hash)) {
            SPARK_LOG_WARN("Could not write hash file %s", hash_file_path.string().c_str());
        }
        else {
            SPARK_LOG_INFO("Stored shader hash: %s", hash_file_path.string().c_str());
        }

        return SPARK_SUCCESS; // Success
    }
} // extern "C"
