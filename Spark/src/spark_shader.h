#ifndef __SPARK_VULKAN_H__
#define __SPARK_VULKAN_H__

#include "spark.h"

#ifdef __cplusplus
extern "C" {
#endif

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
                                               SparkBuffer *spirv_data,
                                               SparkSize *spirv_size);

#ifdef __cplusplus
}
#endif

#endif