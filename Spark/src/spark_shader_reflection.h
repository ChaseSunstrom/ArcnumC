#ifndef __SPARK_SHADER_REFLECTION_H__
#define __SPARK_SHADER_REFLECTION_H__

#include "spark_defines.h"
#include "spark_types.h"

#ifdef __cplusplus
extern "C" {
#endif

	SPARKAPI SparkVoid SparkDestroyShaderReflectionData(SparkShaderReflectionData data);
	SPARKAPI SparkVoid SparkPrintShaderReflectionData(const SparkShaderReflectionData reflection_data);

#ifdef __cplusplus
}
#endif

// We dont want to cause include errors when we include this in the C files
#ifdef SPARK_SHADER_REFLECTION_IMPL

#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>

SPARKAPI SparkSize SparkComputeTypeSize(spirv_cross::Compiler& compiler, const spirv_cross::SPIRType& type);
SPARKAPI SparkShaderVariableType SparkConvertSPIRTypeToVariableType(const spirv_cross::SPIRType& type);
SPARKAPI bool SparkWriteReflectionDataToFile(const std::filesystem::path& path, SparkShaderReflectionData reflection_data);
SPARKAPI bool SparkReadReflectionDataFromFile(const std::filesystem::path& path, SparkShaderReflectionData reflection_data);
SPARKAPI bool SparkWriteVariables(std::ofstream& out, SparkShaderVariable* vars, SparkSize count);
SPARKAPI bool SparkReadVariables(std::ifstream& in, SparkShaderVariable** vars, SparkSize count);
SPARKAPI SparkShaderImageDimension SparkConvertImageDimension(spv::Dim dim);
SPARKAPI SparkShaderVariable SparkExtractVariable(
	spirv_cross::Compiler& compiler,
	const spirv_cross::Resource& res,
	SparkShaderResourceType resource_type);
SPARKAPI SparkVoid SparkExtractAllResources(spirv_cross::Compiler& compiler, SparkShaderReflectionData reflection_data);
SPARKAPI SparkVoid SparkExtractSpecializationConstants(spirv_cross::Compiler& compiler, SparkShaderReflectionData reflection_data);
SPARKAPI SparkVoid SparkExtractStructMembers(spirv_cross::Compiler& compiler, const spirv_cross::SPIRType& type, SparkShaderVariable* var);

#endif

#endif