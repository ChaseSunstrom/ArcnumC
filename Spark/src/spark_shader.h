#ifndef __SPARK_VULKAN_H__
#define __SPARK_VULKAN_H__

#include "spark.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

	typedef enum SparkShaderVariableType {
		SPARK_SHADER_VARIABLE_TYPE_UNKNOWN = 0,
		SPARK_SHADER_VARIABLE_TYPE_BOOL,
		SPARK_SHADER_VARIABLE_TYPE_INT,
		SPARK_SHADER_VARIABLE_TYPE_UINT,
		SPARK_SHADER_VARIABLE_TYPE_FLOAT,
		SPARK_SHADER_VARIABLE_TYPE_DOUBLE,
		SPARK_SHADER_VARIABLE_TYPE_STRUCT,
		// Add more types as needed
	} SparkShaderVariableType;

	typedef struct SparkShaderVariable {
		char* name;
		uint32_t location; // For inputs/outputs
		uint32_t set;      // For resources
		uint32_t binding;  // For resources
		uint32_t offset;   // For push constants
		uint32_t size;
		SparkShaderVariableType type;
		uint32_t vec_size;
		uint32_t columns;
		uint32_t array_size;
		uint32_t member_count;
		struct SparkShaderVariable* members; // For structs
	} SparkShaderVariable;

	typedef struct SparkShaderReflectionData {
		// SPIR-V data
		void* spirv_data;
		size_t spirv_size;

		// Shader stage
		enum SparkShaderStage stage;

		// Input variables
		size_t input_variable_count;
		SparkShaderVariable* input_variables;

		// Output variables
		size_t output_variable_count;
		SparkShaderVariable* output_variables;

		// Uniform buffers
		size_t uniform_buffer_count;
		SparkShaderVariable* uniform_buffers;

		// Storage buffers
		size_t storage_buffer_count;
		SparkShaderVariable* storage_buffers;

		// Sampled images (textures)
		size_t sampled_image_count;
		SparkShaderVariable* sampled_images;

		// Storage images
		size_t storage_image_count;
		SparkShaderVariable* storage_images;

		// Push constants
		size_t push_constant_count;
		SparkShaderVariable* push_constants;

		// Subpass inputs
		size_t subpass_input_count;
		SparkShaderVariable* subpass_inputs;

		// Specialization constants
		size_t specialization_constant_count;
		SparkShaderVariable* specialization_constants;
	} SparkShaderReflectionData;

	typedef enum SparkShaderStage {
		SPARK_SHADER_STAGE_VERTEX = 0,
		SPARK_SHADER_STAGE_FRAGMENT = 1,
		SPARK_SHADER_STAGE_COMPUTE = 2,
		SPARK_SHADER_STAGE_GEOMETRY = 3,
		SPARK_SHADER_STAGE_TESS_CONTROL = 4,
		SPARK_SHADER_STAGE_TESS_EVALUATION = 5
	} SparkShaderStage;

	SPARKAPI SparkResult SparkCompileShaderToSpirv(SparkConstString source,
		SparkShaderStage shader_stage,
		SparkBuffer* spirv_data,
		SparkSize* spirv_size);

#ifdef __cplusplus
}
#endif

#endif