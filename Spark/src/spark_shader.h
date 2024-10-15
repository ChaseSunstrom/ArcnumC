#ifndef __SPARK_VULKAN_H__
#define __SPARK_VULKAN_H__

#include "spark.h"

#ifdef __cplusplus 
extern "C" {
#endif

typedef enum SparkShaderStage
{
	SPARK_SHADER_STAGE_VERTEX,
	SPARK_SHADER_STAGE_FRAGMENT,
	SPARK_SHADER_STAGE_COMPUTE,
	SPARK_SHADER_STAGE_GEOMETRY,
	SPARK_SHADER_STAGE_TESS_CONTROL,
	SPARK_SHADER_STAGE_TESS_EVALUATION
} SparkShaderStage;

SPARKAPI SparkResult SparkCompileShaderToSpirv(SparkConstString source, 
											   SparkShaderStage shader_stage, 
											   SparkBuffer* spirv_data, 
											   SparkSize* spirv_size);

#ifdef __cplusplus
}
#endif

#endif