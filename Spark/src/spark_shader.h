#ifndef __SPARK_SHADER_H__
#define __SPARK_SHADER_H__

#include "spark_defines.h"
#include "spark_types.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
	SPARKAPI SparkResult SparkCompileShaderToSpirv(SparkConstString source,
		SparkShaderStage shader_stage,
		SparkShaderReflectionData reflection_data);

#ifdef __cplusplus
}
#endif

#endif