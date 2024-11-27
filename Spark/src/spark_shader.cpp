// shader_compiler.cpp

#include "spark_shader.h"

// Include glslang headers
#include <glslang/Include/ResourceLimits.h>
#include <glslang/Public/ShaderLang.h>
#include <glslang/SPIRV/GlslangToSpv.h>

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#endif

#ifndef DefaultTBuiltInResource
TBuiltInResource DefaultTBuiltInResource = {
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

    std::string ReadFile(const std::filesystem::path& path) {
        std::ifstream file_stream(path, std::ios::in | std::ios::binary);
        if (!file_stream) {
            // Handle the error: file could not be opened
            fprintf(stderr, "Error: Could not open file %s\n", path.string().c_str());
            return "";
        }

        std::stringstream string_stream;
        string_stream << file_stream.rdbuf();
        file_stream.close();

        return string_stream.str();
    }

    inline std::string GetFileExtension(const std::filesystem::path& path) {
        return path.extension().string();
    }

    inline bool FileExists(const std::filesystem::path& path) {
        return std::filesystem::exists(path);
    }

    inline std::filesystem::path ExtendExtension(const std::filesystem::path& path, const std::string& new_ext) {
        return path.string() + new_ext;
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

        // Generate the corresponding .sprv file path
        std::filesystem::path sprv_path = ExtendExtension(source_path, ".sprv");

        // Check if the .sprv file exists
        if (FileExists(sprv_path)) {
            // Read the existing .sprv file
            std::ifstream sprv_file(sprv_path, std::ios::in | std::ios::binary | std::ios::ate);
            if (!sprv_file) {
                fprintf(stderr, "Error: Could not open SPIR-V file %s\n", sprv_path.string().c_str());
                // Proceed to compile if .sprv exists but cannot be opened
            }
            else {
                std::streamsize size = sprv_file.tellg();
                sprv_file.seekg(0, std::ios::beg);

                // Allocate memory for SPIR-V data
                *spirv_data = (SparkBuffer)malloc(size);
                if (!(*spirv_data)) {
                    fprintf(stderr, "Error: Memory allocation failed for SPIR-V data\n");
                    return SPARK_ERROR_OUT_OF_MEMORY;
                }

                if (!sprv_file.read(reinterpret_cast<char*>(*spirv_data), size)) {
                    fprintf(stderr, "Error: Failed to read SPIR-V file %s\n", sprv_path.string().c_str());
                    free(*spirv_data);
                    *spirv_data = nullptr;
                    return SPARK_ERROR_INVALID;
                }

                *spirv_size = static_cast<SparkSize>(size);
                fprintf(stdout, "Loaded SPIR-V from cache: %s\n", sprv_path.string().c_str());
                return SPARK_SUCCESS;
            }
        }

        // If .sprv does not exist or failed to read, proceed to compile

        std::string source_code = ReadFile(source_path);
        if (source_code.empty()) {
            fprintf(stderr, "Error: Shader source is empty or could not be read.\n");
            return SPARK_ERROR_INVALID;
        }

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
            fprintf(stderr, "Shader compilation error:\n%s\n", log.c_str());
            return SPARK_ERROR_INVALID;
        }

        glslang::TProgram program;
        program.addShader(&shader);

        // Link the program
        if (!program.link(messages)) {
            // Linking failed
            std::string log = program.getInfoLog();
            fprintf(stderr, "Shader linking error:\n%s\n", log.c_str());
            return SPARK_ERROR_INVALID;
        }

        // Convert to SPIR-V
        std::vector<uint32_t> spirv;
        glslang::GlslangToSpv(*program.getIntermediate(stage), spirv);

        // Allocate memory for SPIR-V data
        size_t byte_size = spirv.size() * sizeof(uint32_t);
        *spirv_data = (SparkBuffer)malloc(byte_size);
        if (!(*spirv_data)) {
            fprintf(stderr, "Error: Memory allocation failed for SPIR-V data\n");
            return SPARK_ERROR_OUT_OF_MEMORY;
        }

        memcpy(*spirv_data, spirv.data(), byte_size);
        *spirv_size = byte_size;

        // Write the SPIR-V binary to the .sprv file for caching
        std::ofstream sprv_file_out(sprv_path, std::ios::out | std::ios::binary);
        if (!sprv_file_out) {
            fprintf(stderr, "Warning: Could not write SPIR-V cache file %s\n", sprv_path.string().c_str());
            // Continue without caching
        }
        else {
            sprv_file_out.write(reinterpret_cast<const char*>(spirv.data()), byte_size);
            sprv_file_out.close();
            fprintf(stdout, "Compiled and cached SPIR-V: %s\n", sprv_path.string().c_str());
        }

        return SPARK_SUCCESS; // Success
    }
} // extern "C"
