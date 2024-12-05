#define SPARK_SHADER_REFLECTION_IMPL
#include "spark_shader_reflection.h"
#include "spark.h"

#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

// On MSVC, strdup is deprecated. Use _strdup instead
#ifdef _MSC_VER
#define strdup _strdup
#endif


SPARKAPI  const SparkU32 REFLECTION_FILE_VERSION = 1;

// Extract arrays
SPARKAPI SparkVoid ExtractArraySizes(const spirv_cross::SPIRType& type, SparkShaderVariable* var) {
	var->array_dimension_count = (SparkU32)type.array.size();
	if (!type.array.empty()) {
		var->array_sizes = (SparkU32*)malloc(var->array_dimension_count * sizeof(SparkU32));
		for (SparkU32 i = 0; i < var->array_dimension_count; i++) {
			// If array size is not literal, we set to 0
			var->array_sizes[i] = type.array_size_literal[i] ? (SparkU32)type.array[i] : 0;
		}
	}
	else {
		var->array_sizes = NULL;
	}
}

// Convert SPIRType to SparkShaderVariableType
SPARKAPI SparkShaderVariableType SparkConvertSPIRTypeToVariableType(const spirv_cross::SPIRType& type) {
	switch (type.basetype) {
	case spirv_cross::SPIRType::Boolean: return SPARK_SHADER_VARIABLE_TYPE_BOOL;
	case spirv_cross::SPIRType::Int:     return SPARK_SHADER_VARIABLE_TYPE_INT;
	case spirv_cross::SPIRType::UInt:    return SPARK_SHADER_VARIABLE_TYPE_UINT;
	case spirv_cross::SPIRType::Float:   return SPARK_SHADER_VARIABLE_TYPE_FLOAT;
	case spirv_cross::SPIRType::Double:  return SPARK_SHADER_VARIABLE_TYPE_DOUBLE;
	case spirv_cross::SPIRType::Struct:  return SPARK_SHADER_VARIABLE_TYPE_STRUCT;
	default:                             return SPARK_SHADER_VARIABLE_TYPE_UNKNOWN;
	}
}

// Recursively extract struct members
SPARKAPI SparkVoid SparkExtractStructMembers(spirv_cross::Compiler& compiler, const spirv_cross::SPIRType& type, SparkShaderVariable* var) {
	var->member_count = (SparkU32)type.member_types.size();
	if (var->member_count > 0) {
		var->members = (SparkShaderVariable*)malloc(var->member_count * sizeof(SparkShaderVariable));
		SparkSize total_struct_size = compiler.get_declared_struct_size(type);

		for (SparkU32 i = 0; i < var->member_count; i++) {
			SparkShaderVariable member = {};
			member.name = strdup(compiler.get_member_name(type.self, i).c_str());
			member.resource_type = SPARK_SHADER_RESOURCE_TYPE_UNKNOWN;
			const spirv_cross::SPIRType& member_type = compiler.get_type(type.member_types[i]);

			SparkSize member_offset = compiler.type_struct_member_offset(type, i);
			SparkSize member_size = 0;
			if (i + 1 < var->member_count) {
				SparkSize next_offset = compiler.type_struct_member_offset(type, i + 1);
				member_size = next_offset - member_offset;
			}
			else {
				member_size = total_struct_size - member_offset;
			}

			member.size = (SparkU32)member_size;
			member.offset = (SparkU32)member_offset;
			member.base_type = SparkConvertSPIRTypeToVariableType(member_type);
			member.vec_size = member_type.vecsize;
			member.columns = member_type.columns;
			ExtractArraySizes(member_type, &member);

			// Recursively extract member structs
			SparkExtractStructMembers(compiler, member_type, &member);

			// Built-in decoration check
			if (compiler.has_member_decoration(type.self, i, spv::DecorationBuiltIn)) {
				member.is_builtin = 1;
				member.builtin_type = compiler.get_member_decoration(type.self, i, spv::DecorationBuiltIn);
			}
			else {
				member.is_builtin = 0;
			}

			member.image_dimension = SPARK_SHADER_IMAGE_DIM_UNSPECIFIED;
			var->members[i] = member;
		}
	}
	else {
		var->members = NULL;
	}
}

SPARKAPI SparkShaderImageDimension SparkConvertImageDimension(spv::Dim dim) {
	switch (dim) {
	case spv::Dim1D:     return SPARK_SHADER_IMAGE_DIM_1D;
	case spv::Dim2D:     return SPARK_SHADER_IMAGE_DIM_2D;
	case spv::Dim3D:     return SPARK_SHADER_IMAGE_DIM_3D;
	case spv::DimCube:   return SPARK_SHADER_IMAGE_DIM_CUBE;
	case spv::DimRect:   return SPARK_SHADER_IMAGE_DIM_RECT;
	case spv::DimBuffer: return SPARK_SHADER_IMAGE_DIM_BUFFER;
	case spv::DimSubpassData: return SPARK_SHADER_IMAGE_DIM_SUBPASS;
	default: return SPARK_SHADER_IMAGE_DIM_UNSPECIFIED;
	}
}

// Compute size for non-struct types
// If struct: use get_declared_struct_size
// Else: size = (width/8)*vecsize*columns, multiplied by arrays if any
SPARKAPI SparkSize SparkComputeTypeSize(spirv_cross::Compiler& compiler, const spirv_cross::SPIRType& type) {
	SparkSize base_size = 0;
	if (type.basetype == spirv_cross::SPIRType::Struct) {
		base_size = compiler.get_declared_struct_size(type);
	}
	else {
		base_size = (type.width / 8) * type.vecsize * type.columns;
	}

	// Apply array dimensions
	for (SparkU32 i = 0; i < (SparkU32)type.array.size(); i++) {
		if (type.array_size_literal[i]) {
			base_size *= type.array[i];
		}
		else {
			// Unknown size array, could set to 0 or leave as is.
			// We'll leave as is which might not be fully correct for unknown array sizes.
		}
	}

	return base_size;
}

SPARKAPI SparkShaderVariable SparkExtractVariable(
	spirv_cross::Compiler& compiler,
	const spirv_cross::Resource& res,
	SparkShaderResourceType resource_type) {

	SparkShaderVariable var = {};
	var.resource_type = resource_type;
	var.name = strdup(res.name.c_str());

	const spirv_cross::SPIRType& type = compiler.get_type(res.type_id);

	// Decorations
	if (compiler.has_decoration(res.id, spv::DecorationLocation)) {
		var.location = compiler.get_decoration(res.id, spv::DecorationLocation);
	}
	if (compiler.has_decoration(res.id, spv::DecorationDescriptorSet)) {
		var.set = compiler.get_decoration(res.id, spv::DecorationDescriptorSet);
	}
	if (compiler.has_decoration(res.id, spv::DecorationBinding)) {
		var.binding = compiler.get_decoration(res.id, spv::DecorationBinding);
	}
	if (compiler.has_decoration(res.id, spv::DecorationOffset)) {
		var.offset = compiler.get_decoration(res.id, spv::DecorationOffset);
	}

	// Built-in check
	if (compiler.has_decoration(res.id, spv::DecorationBuiltIn)) {
		var.is_builtin = 1;
		var.builtin_type = compiler.get_decoration(res.id, spv::DecorationBuiltIn);
	}
	else {
		var.is_builtin = 0;
	}

	// Compute size
	var.size = (SparkU32)SparkComputeTypeSize(compiler, type);
	var.base_type = SparkConvertSPIRTypeToVariableType(type);
	var.vec_size = type.vecsize;
	var.columns = type.columns;
	ExtractArraySizes(type, &var);

	// If struct, extract members
	if (type.basetype == spirv_cross::SPIRType::Struct) {
		SparkExtractStructMembers(compiler, type, &var);
	}
	else {
		var.member_count = 0;
		var.members = NULL;
	}

	// Image/sampler info if applicable
	if (type.basetype == spirv_cross::SPIRType::Image ||
		type.basetype == spirv_cross::SPIRType::SampledImage ||
		type.basetype == spirv_cross::SPIRType::Sampler) {
		// These checks are heuristic
		var.is_depth = 0; // You can refine by checking decorations or type.image.depth
		var.is_multisampled = type.image.ms ? 1 : 0;
		var.is_arrayed = type.image.arrayed ? 1 : 0;
		var.is_storage = (resource_type == SPARK_SHADER_RESOURCE_TYPE_STORAGE_IMAGE) ? 1 : 0;
		var.is_sampled = (type.basetype == spirv_cross::SPIRType::SampledImage ||
			resource_type == SPARK_SHADER_RESOURCE_TYPE_SAMPLED_IMAGE ||
			resource_type == SPARK_SHADER_RESOURCE_TYPE_SEPARATE_IMAGE) ? 1 : 0;
		var.image_dimension = SparkConvertImageDimension(type.image.dim);
		var.is_subpass_input = (resource_type == SPARK_SHADER_RESOURCE_TYPE_SUBPASS_INPUT) ? 1 : 0;
	}
	else {
		var.image_dimension = SPARK_SHADER_IMAGE_DIM_UNSPECIFIED;
		var.is_depth = 0;
		var.is_multisampled = 0;
		var.is_arrayed = 0;
		var.is_storage = 0;
		var.is_sampled = 0;
		var.is_subpass_input = 0;
	}

	return var;
}

// Template to handle SmallVector or std::vector
template<typename ResourceContainer>
SPARKAPI SparkVoid ExtractResourceArray(
	spirv_cross::Compiler& compiler,
	const ResourceContainer& resources,
	SparkShaderVariable** out_array,
	SparkSize* out_count,
	SparkShaderResourceType resource_type) {

	*out_count = resources.size();
	if (*out_count == 0) {
		*out_array = NULL;
		return;
	}

	*out_array = (SparkShaderVariable*)malloc((*out_count) * sizeof(SparkShaderVariable));
	for (SparkSize i = 0; i < *out_count; i++) {
		(*out_array)[i] = SparkExtractVariable(compiler, resources[i], resource_type);
	}
}

SPARKAPI SparkVoid SparkExtractSpecializationConstants(spirv_cross::Compiler& compiler, SparkShaderReflectionData reflection_data) {
	auto spec_constants = compiler.get_specialization_constants();
	reflection_data->specialization_constant_count = spec_constants.size();
	if (reflection_data->specialization_constant_count > 0) {
		reflection_data->specialization_constants = (SparkShaderVariable*)malloc(reflection_data->specialization_constant_count * sizeof(SparkShaderVariable));
		for (SparkSize i = 0; i < spec_constants.size(); i++) {
			SparkShaderVariable var = {};
			var.resource_type = SPARK_SHADER_RESOURCE_TYPE_SPECIALIZATION_CONSTANT;
			var.spec_constant_id = spec_constants[i].constant_id;

			std::string name = compiler.get_name(spec_constants[i].id);
			if (name.empty()) {
				name = "spec_const_" + std::to_string(spec_constants[i].constant_id);
			}
			var.name = strdup(name.c_str());

			auto& c = compiler.get_constant(spec_constants[i].id);
			auto& t = compiler.get_type(c.constant_type);
			var.base_type = SparkConvertSPIRTypeToVariableType(t);
			var.vec_size = t.vecsize;
			var.columns = t.columns;
			ExtractArraySizes(t, &var);
			var.size = (SparkU32)SparkComputeTypeSize(compiler, t);

			var.is_builtin = 0;
			var.members = NULL;
			var.member_count = 0;

			reflection_data->specialization_constants[i] = var;
		}
	}
	else {
		reflection_data->specialization_constants = NULL;
	}
}

SPARKAPI SparkVoid SparkExtractAllResources(spirv_cross::Compiler& compiler, SparkShaderReflectionData reflection_data) {
	auto res = compiler.get_shader_resources();

	// Stage inputs/outputs
	ExtractResourceArray(compiler, res.stage_inputs, &reflection_data->stage_inputs, &reflection_data->stage_input_count, SPARK_SHADER_RESOURCE_TYPE_STAGE_INPUT);
	ExtractResourceArray(compiler, res.stage_outputs, &reflection_data->stage_outputs, &reflection_data->stage_output_count, SPARK_SHADER_RESOURCE_TYPE_STAGE_OUTPUT);

	// Buffers
	ExtractResourceArray(compiler, res.uniform_buffers, &reflection_data->uniform_buffers, &reflection_data->uniform_buffer_count, SPARK_SHADER_RESOURCE_TYPE_UNIFORM_BUFFER);
	ExtractResourceArray(compiler, res.storage_buffers, &reflection_data->storage_buffers, &reflection_data->storage_buffer_count, SPARK_SHADER_RESOURCE_TYPE_STORAGE_BUFFER);

	// Images/Samplers
	ExtractResourceArray(compiler, res.sampled_images, &reflection_data->sampled_images, &reflection_data->sampled_image_count, SPARK_SHADER_RESOURCE_TYPE_SAMPLED_IMAGE);
	ExtractResourceArray(compiler, res.storage_images, &reflection_data->storage_images, &reflection_data->storage_image_count, SPARK_SHADER_RESOURCE_TYPE_STORAGE_IMAGE);
	ExtractResourceArray(compiler, res.separate_images, &reflection_data->separate_images, &reflection_data->separate_image_count, SPARK_SHADER_RESOURCE_TYPE_SEPARATE_IMAGE);
	ExtractResourceArray(compiler, res.separate_samplers, &reflection_data->separate_samplers, &reflection_data->separate_sampler_count, SPARK_SHADER_RESOURCE_TYPE_SEPARATE_SAMPLER);
	// No separate_storage_images in new SPIRV-Cross versions, remove them.

	// Subpass inputs
	ExtractResourceArray(compiler, res.subpass_inputs, &reflection_data->subpass_inputs, &reflection_data->subpass_input_count, SPARK_SHADER_RESOURCE_TYPE_SUBPASS_INPUT);

	// Push constants
	ExtractResourceArray(compiler, res.push_constant_buffers, &reflection_data->push_constants, &reflection_data->push_constant_count, SPARK_SHADER_RESOURCE_TYPE_PUSH_CONSTANT);

	// Acceleration structures
	ExtractResourceArray(compiler, res.acceleration_structures, &reflection_data->acceleration_structures, &reflection_data->acceleration_structure_count, SPARK_SHADER_RESOURCE_TYPE_ACCELERATION_STRUCTURE);

	// Atomic counters
	ExtractResourceArray(compiler, res.atomic_counters, &reflection_data->atomic_counters, &reflection_data->atomic_counter_count, SPARK_SHADER_RESOURCE_TYPE_ATOMIC_COUNTER);

	// Specialization constants
	SparkExtractSpecializationConstants(compiler, reflection_data);
}

SPARKAPI  bool WriteString(std::ofstream& out, SparkConstString str) {
	size_t length = str ? strlen(str) : 0;
	out.write((SparkConstString)&length, sizeof(length));
	if (length > 0) {
		out.write(str, length);
	}
	return true;
}

SPARKAPI bool ReadString(std::ifstream& in, char** out_str) {
	size_t length;
	in.read((char*)&length, sizeof(length));
	if (in.fail()) return false;
	if (length == 0) {
		*out_str = NULL;
		return true;
	}
	*out_str = (char*)malloc(length + 1);
	if (!*out_str) return false;
	in.read(*out_str, length);
	(*out_str)[length] = '\0';
	return !in.fail();
}

SPARKAPI bool WriteVariable(std::ofstream& out, SparkShaderVariable* var) {
	// Write name
	if (!WriteString(out, var->name)) return false;

	// Write enums and integral fields
	out.write((SparkConstString)&var->resource_type, sizeof(var->resource_type));
	out.write((SparkConstString)&var->location, sizeof(var->location));
	out.write((SparkConstString)&var->set, sizeof(var->set));
	out.write((SparkConstString)&var->binding, sizeof(var->binding));
	out.write((SparkConstString)&var->offset, sizeof(var->offset));
	out.write((SparkConstString)&var->size, sizeof(var->size));
	out.write((SparkConstString)&var->base_type, sizeof(var->base_type));
	out.write((SparkConstString)&var->vec_size, sizeof(var->vec_size));
	out.write((SparkConstString)&var->columns, sizeof(var->columns));
	out.write((SparkConstString)&var->array_dimension_count, sizeof(var->array_dimension_count));

	// Write array sizes
	if (var->array_dimension_count > 0) {
		out.write((SparkConstString)var->array_sizes, var->array_dimension_count * sizeof(SparkU32));
	}

	out.write((SparkConstString)&var->member_count, sizeof(var->member_count));

	// Write members
	if (var->member_count > 0) {
		if (!SparkWriteVariables(out, var->members, var->member_count)) return false;
	}

	out.write((SparkConstString)&var->is_builtin, sizeof(var->is_builtin));
	out.write((SparkConstString)&var->builtin_type, sizeof(var->builtin_type));

	out.write((SparkConstString)&var->image_dimension, sizeof(var->image_dimension));
	out.write((SparkConstString)&var->is_depth, sizeof(var->is_depth));
	out.write((SparkConstString)&var->is_arrayed, sizeof(var->is_arrayed));
	out.write((SparkConstString)&var->is_multisampled, sizeof(var->is_multisampled));
	out.write((SparkConstString)&var->is_storage, sizeof(var->is_storage));
	out.write((SparkConstString)&var->is_sampled, sizeof(var->is_sampled));
	out.write((SparkConstString)&var->is_subpass_input, sizeof(var->is_subpass_input));

	out.write((SparkConstString)&var->spec_constant_id, sizeof(var->spec_constant_id));

	return !out.fail();
}

SPARKAPI bool ReadVariable(std::ifstream& in, SparkShaderVariable* var) {
	memset(var, 0, sizeof(*var));
	if (!ReadString(in, &var->name)) return false;
	in.read((char*)&var->resource_type, sizeof(var->resource_type));
	in.read((char*)&var->location, sizeof(var->location));
	in.read((char*)&var->set, sizeof(var->set));
	in.read((char*)&var->binding, sizeof(var->binding));
	in.read((char*)&var->offset, sizeof(var->offset));
	in.read((char*)&var->size, sizeof(var->size));
	in.read((char*)&var->base_type, sizeof(var->base_type));
	in.read((char*)&var->vec_size, sizeof(var->vec_size));
	in.read((char*)&var->columns, sizeof(var->columns));
	in.read((char*)&var->array_dimension_count, sizeof(var->array_dimension_count));

	if (in.fail()) return false;

	if (var->array_dimension_count > 0) {
		var->array_sizes = (SparkU32*)malloc(var->array_dimension_count * sizeof(SparkU32));
		if (!var->array_sizes) return false;
		in.read((char*)var->array_sizes, var->array_dimension_count * sizeof(SparkU32));
		if (in.fail()) return false;
	}
	else {
		var->array_sizes = NULL;
	}

	in.read((char*)&var->member_count, sizeof(var->member_count));
	if (in.fail()) return false;

	if (var->member_count > 0) {
		var->members = (SparkShaderVariable*)malloc(var->member_count * sizeof(SparkShaderVariable));
		if (!var->members) return false;
		if (!SparkReadVariables(in, &var->members, var->member_count)) return false;
	}
	else {
		var->members = NULL;
	}

	in.read((char*)&var->is_builtin, sizeof(var->is_builtin));
	in.read((char*)&var->builtin_type, sizeof(var->builtin_type));
	in.read((char*)&var->image_dimension, sizeof(var->image_dimension));
	in.read((char*)&var->is_depth, sizeof(var->is_depth));
	in.read((char*)&var->is_arrayed, sizeof(var->is_arrayed));
	in.read((char*)&var->is_multisampled, sizeof(var->is_multisampled));
	in.read((char*)&var->is_storage, sizeof(var->is_storage));
	in.read((char*)&var->is_sampled, sizeof(var->is_sampled));
	in.read((char*)&var->is_subpass_input, sizeof(var->is_subpass_input));
	in.read((char*)&var->spec_constant_id, sizeof(var->spec_constant_id));

	return !in.fail();
}

SPARKAPI bool SparkWriteVariables(std::ofstream& out, SparkShaderVariable* vars, SparkSize count) {
	for (SparkSize i = 0; i < count; i++) {
		if (!WriteVariable(out, &vars[i])) return false;
	}
	return true;
}

SPARKAPI bool SparkReadVariables(std::ifstream& in, SparkShaderVariable** vars, SparkSize count) {
	for (SparkSize i = 0; i < count; i++) {
		if (!ReadVariable(in, &(*vars)[i])) return false;
	}
	return true;
}

SPARKAPI bool SparkWriteReflectionDataToFile(const std::filesystem::path& path, SparkShaderReflectionData reflection_data) {
	std::ofstream out(path, std::ios::binary | std::ios::trunc);
	if (!out) return false;

	// Write file version
	out.write((SparkConstString)&REFLECTION_FILE_VERSION, sizeof(REFLECTION_FILE_VERSION));

	// Write all counts
	out.write((SparkConstString)&reflection_data->stage_input_count, sizeof(reflection_data->stage_input_count));
	out.write((SparkConstString)&reflection_data->stage_output_count, sizeof(reflection_data->stage_output_count));
	out.write((SparkConstString)&reflection_data->uniform_buffer_count, sizeof(reflection_data->uniform_buffer_count));
	out.write((SparkConstString)&reflection_data->storage_buffer_count, sizeof(reflection_data->storage_buffer_count));
	out.write((SparkConstString)&reflection_data->sampled_image_count, sizeof(reflection_data->sampled_image_count));
	out.write((SparkConstString)&reflection_data->storage_image_count, sizeof(reflection_data->storage_image_count));
	out.write((SparkConstString)&reflection_data->separate_sampler_count, sizeof(reflection_data->separate_sampler_count));
	out.write((SparkConstString)&reflection_data->separate_image_count, sizeof(reflection_data->separate_image_count));
	out.write((SparkConstString)&reflection_data->separate_storage_image_count, sizeof(reflection_data->separate_storage_image_count));
	out.write((SparkConstString)&reflection_data->subpass_input_count, sizeof(reflection_data->subpass_input_count));
	out.write((SparkConstString)&reflection_data->push_constant_count, sizeof(reflection_data->push_constant_count));
	out.write((SparkConstString)&reflection_data->acceleration_structure_count, sizeof(reflection_data->acceleration_structure_count));
	out.write((SparkConstString)&reflection_data->atomic_counter_count, sizeof(reflection_data->atomic_counter_count));
	out.write((SparkConstString)&reflection_data->specialization_constant_count, sizeof(reflection_data->specialization_constant_count));

	// Write arrays
	if (!SparkWriteVariables(out, reflection_data->stage_inputs, reflection_data->stage_input_count)) return false;
	if (!SparkWriteVariables(out, reflection_data->stage_outputs, reflection_data->stage_output_count)) return false;
	if (!SparkWriteVariables(out, reflection_data->uniform_buffers, reflection_data->uniform_buffer_count)) return false;
	if (!SparkWriteVariables(out, reflection_data->storage_buffers, reflection_data->storage_buffer_count)) return false;
	if (!SparkWriteVariables(out, reflection_data->sampled_images, reflection_data->sampled_image_count)) return false;
	if (!SparkWriteVariables(out, reflection_data->storage_images, reflection_data->storage_image_count)) return false;
	if (!SparkWriteVariables(out, reflection_data->separate_samplers, reflection_data->separate_sampler_count)) return false;
	if (!SparkWriteVariables(out, reflection_data->separate_images, reflection_data->separate_image_count)) return false;
	if (!SparkWriteVariables(out, reflection_data->separate_storage_images, reflection_data->separate_storage_image_count)) return false;
	if (!SparkWriteVariables(out, reflection_data->subpass_inputs, reflection_data->subpass_input_count)) return false;
	if (!SparkWriteVariables(out, reflection_data->push_constants, reflection_data->push_constant_count)) return false;
	if (!SparkWriteVariables(out, reflection_data->acceleration_structures, reflection_data->acceleration_structure_count)) return false;
	if (!SparkWriteVariables(out, reflection_data->atomic_counters, reflection_data->atomic_counter_count)) return false;
	if (!SparkWriteVariables(out, reflection_data->specialization_constants, reflection_data->specialization_constant_count)) return false;

	return true;
}

SPARKAPI bool SparkReadReflectionDataFromFile(const std::filesystem::path& path, SparkShaderReflectionData reflection_data) {
	std::ifstream in(path, std::ios::binary);
	if (!in) return false;

	SparkU32 version;
	in.read((char*)&version, sizeof(version));
	if (in.fail() || version != REFLECTION_FILE_VERSION) return false;

	in.read((char*)&reflection_data->stage_input_count, sizeof(reflection_data->stage_input_count));
	in.read((char*)&reflection_data->stage_output_count, sizeof(reflection_data->stage_output_count));
	in.read((char*)&reflection_data->uniform_buffer_count, sizeof(reflection_data->uniform_buffer_count));
	in.read((char*)&reflection_data->storage_buffer_count, sizeof(reflection_data->storage_buffer_count));
	in.read((char*)&reflection_data->sampled_image_count, sizeof(reflection_data->sampled_image_count));
	in.read((char*)&reflection_data->storage_image_count, sizeof(reflection_data->storage_image_count));
	in.read((char*)&reflection_data->separate_sampler_count, sizeof(reflection_data->separate_sampler_count));
	in.read((char*)&reflection_data->separate_image_count, sizeof(reflection_data->separate_image_count));
	in.read((char*)&reflection_data->separate_storage_image_count, sizeof(reflection_data->separate_storage_image_count));
	in.read((char*)&reflection_data->subpass_input_count, sizeof(reflection_data->subpass_input_count));
	in.read((char*)&reflection_data->push_constant_count, sizeof(reflection_data->push_constant_count));
	in.read((char*)&reflection_data->acceleration_structure_count, sizeof(reflection_data->acceleration_structure_count));
	in.read((char*)&reflection_data->atomic_counter_count, sizeof(reflection_data->atomic_counter_count));
	in.read((char*)&reflection_data->specialization_constant_count, sizeof(reflection_data->specialization_constant_count));

	auto ReadArray = [&](SparkShaderVariable** arr, SparkSize count) {
		if (count == 0) {
			*arr = NULL;
			return true;
		}
		*arr = (SparkShaderVariable*)malloc(count * sizeof(SparkShaderVariable));
		if (!*arr) return false;
		return SparkReadVariables(in, arr, count);
		};

	if (!ReadArray(&reflection_data->stage_inputs, reflection_data->stage_input_count)) return false;
	if (!ReadArray(&reflection_data->stage_outputs, reflection_data->stage_output_count)) return false;
	if (!ReadArray(&reflection_data->uniform_buffers, reflection_data->uniform_buffer_count)) return false;
	if (!ReadArray(&reflection_data->storage_buffers, reflection_data->storage_buffer_count)) return false;
	if (!ReadArray(&reflection_data->sampled_images, reflection_data->sampled_image_count)) return false;
	if (!ReadArray(&reflection_data->storage_images, reflection_data->storage_image_count)) return false;
	if (!ReadArray(&reflection_data->separate_samplers, reflection_data->separate_sampler_count)) return false;
	if (!ReadArray(&reflection_data->separate_images, reflection_data->separate_image_count)) return false;
	if (!ReadArray(&reflection_data->separate_storage_images, reflection_data->separate_storage_image_count)) return false;
	if (!ReadArray(&reflection_data->subpass_inputs, reflection_data->subpass_input_count)) return false;
	if (!ReadArray(&reflection_data->push_constants, reflection_data->push_constant_count)) return false;
	if (!ReadArray(&reflection_data->acceleration_structures, reflection_data->acceleration_structure_count)) return false;
	if (!ReadArray(&reflection_data->atomic_counters, reflection_data->atomic_counter_count)) return false;
	if (!ReadArray(&reflection_data->specialization_constants, reflection_data->specialization_constant_count)) return false;

	return true;
}

SPARKAPI SPARKSTATIC SparkVoid PrintIndent(SparkI32 indent_level) {
	for (SparkI32 i = 0; i < indent_level; i++) {
		printf("  ");
	}
}

// Convert enums to strings for readability
SPARKAPI SPARKSTATIC SparkConstString ShaderVariableTypeToString(SparkShaderVariableType type) {
	switch (type) {
	case SPARK_SHADER_VARIABLE_TYPE_UNKNOWN: return "UNKNOWN";
	case SPARK_SHADER_VARIABLE_TYPE_BOOL: return "BOOL";
	case SPARK_SHADER_VARIABLE_TYPE_INT: return "INT";
	case SPARK_SHADER_VARIABLE_TYPE_UINT: return "UINT";
	case SPARK_SHADER_VARIABLE_TYPE_FLOAT: return "FLOAT";
	case SPARK_SHADER_VARIABLE_TYPE_DOUBLE: return "DOUBLE";
	case SPARK_SHADER_VARIABLE_TYPE_STRUCT: return "STRUCT";
	default: return "UNDEFINED";
	}
}

SPARKAPI SPARKSTATIC SparkConstString ShaderResourceTypeToString(SparkShaderResourceType res_type) {
	switch (res_type) {
	case SPARK_SHADER_RESOURCE_TYPE_UNKNOWN: return "UNKNOWN";
	case SPARK_SHADER_RESOURCE_TYPE_STAGE_INPUT: return "STAGE_INPUT";
	case SPARK_SHADER_RESOURCE_TYPE_STAGE_OUTPUT: return "STAGE_OUTPUT";
	case SPARK_SHADER_RESOURCE_TYPE_UNIFORM_BUFFER: return "UNIFORM_BUFFER";
	case SPARK_SHADER_RESOURCE_TYPE_STORAGE_BUFFER: return "STORAGE_BUFFER";
	case SPARK_SHADER_RESOURCE_TYPE_SAMPLED_IMAGE: return "SAMPLED_IMAGE";
	case SPARK_SHADER_RESOURCE_TYPE_STORAGE_IMAGE: return "STORAGE_IMAGE";
	case SPARK_SHADER_RESOURCE_TYPE_SEPARATE_SAMPLER: return "SEPARATE_SAMPLER";
	case SPARK_SHADER_RESOURCE_TYPE_SEPARATE_IMAGE: return "SEPARATE_IMAGE";
	case SPARK_SHADER_RESOURCE_TYPE_SEPARATE_STORAGE_IMAGE: return "SEPARATE_STORAGE_IMAGE";
	case SPARK_SHADER_RESOURCE_TYPE_SUBPASS_INPUT: return "SUBPASS_INPUT";
	case SPARK_SHADER_RESOURCE_TYPE_PUSH_CONSTANT: return "PUSH_CONSTANT";
	case SPARK_SHADER_RESOURCE_TYPE_ACCELERATION_STRUCTURE: return "ACCELERATION_STRUCTURE";
	case SPARK_SHADER_RESOURCE_TYPE_ATOMIC_COUNTER: return "ATOMIC_COUNTER";
	case SPARK_SHADER_RESOURCE_TYPE_SPECIALIZATION_CONSTANT: return "SPECIALIZATION_CONSTANT";
	default: return "UNDEFINED";
	}
}

SPARKAPI SPARKSTATIC SparkConstString ShaderImageDimensionToString(SparkShaderImageDimension dim) {
	switch (dim) {
	case SPARK_SHADER_IMAGE_DIM_UNSPECIFIED: return "UNSPECIFIED";
	case SPARK_SHADER_IMAGE_DIM_1D: return "1D";
	case SPARK_SHADER_IMAGE_DIM_2D: return "2D";
	case SPARK_SHADER_IMAGE_DIM_3D: return "3D";
	case SPARK_SHADER_IMAGE_DIM_CUBE: return "CUBE";
	case SPARK_SHADER_IMAGE_DIM_RECT: return "RECT";
	case SPARK_SHADER_IMAGE_DIM_BUFFER: return "BUFFER";
	case SPARK_SHADER_IMAGE_DIM_SUBPASS: return "SUBPASS";
	default: return "UNDEFINED";
	}
}

// Recursive function to print a single variable and its members
SPARKAPI SPARKSTATIC SparkVoid PrintShaderVariable(const SparkShaderVariable* var, SparkI32 indent) {
	PrintIndent(indent);
	printf("Variable: name=\"%s\" resource_type=%s\n", var->name ? var->name : "(null)", ShaderResourceTypeToString(var->resource_type));

	PrintIndent(indent);
	printf(" base_type=%s vec_size=%u columns=%u\n", ShaderVariableTypeToString(var->base_type), var->vec_size, var->columns);

	PrintIndent(indent);
	printf(" location=%u set=%u binding=%u offset=%u size=%u\n", var->location, var->set, var->binding, var->offset, var->size);

	if (var->array_dimension_count > 0) {
		PrintIndent(indent);
		printf(" Array Dimensions: %u\n", var->array_dimension_count);
		for (SparkU32 i = 0; i < var->array_dimension_count; i++) {
			PrintIndent(indent + 1);
			printf("Dimension %u: size=%u\n", i, var->array_sizes[i]);
		}
	}

	PrintIndent(indent);
	printf(" is_builtin=%d builtin_type=%u\n", var->is_builtin, var->builtin_type);

	if (var->image_dimension != SPARK_SHADER_IMAGE_DIM_UNSPECIFIED ||
		var->is_depth || var->is_arrayed || var->is_multisampled || var->is_storage || var->is_sampled || var->is_subpass_input) {
		PrintIndent(indent);
		printf(" Image/Sampler Info: dim=%s depth=%d arrayed=%d multisampled=%d storage=%d sampled=%d subpass=%d\n",
			ShaderImageDimensionToString(var->image_dimension), var->is_depth, var->is_arrayed, var->is_multisampled, var->is_storage, var->is_sampled, var->is_subpass_input);
	}

	if (var->spec_constant_id != 0) {
		PrintIndent(indent);
		printf(" spec_constant_id=%u\n", var->spec_constant_id);
	}

	if (var->member_count > 0) {
		PrintIndent(indent);
		printf(" Members (count=%u):\n", var->member_count);
		for (SparkU32 i = 0; i < var->member_count; i++) {
			PrintShaderVariable(&var->members[i], indent + 1);
		}
	}
}

// Print an array of variables
SPARKAPI SPARKSTATIC SparkVoid PrintShaderVariableArray(SparkConstString label, SparkShaderVariable* vars, SparkSize count) {
	printf("%s (count=%llu):\n", label, (unsigned long long)count);
	for (SparkSize i = 0; i < count; i++) {
		PrintShaderVariable(&vars[i], 1);
	}
	if (count == 0) {
		printf("  (none)\n");
	}
}

#ifdef __cplusplus
extern "C" {
#endif

	SPARKAPI SparkVoid SparkDestroyShaderReflectionData(SparkShaderReflectionData data) {
		if (!data) return;

		if (data->spirv_data) {
			free(data->spirv_data);
			data->spirv_data = NULL;
		}

		auto FreeVariables = [](SparkShaderVariable* vars, SparkSize count, auto& FreeVariablesRef) -> SparkVoid {
			if (!vars) return;
			for (SparkSize i = 0; i < count; i++) {
				if (vars[i].name) free(vars[i].name);
				if (vars[i].array_sizes) free(vars[i].array_sizes);
				if (vars[i].members) {
					FreeVariablesRef(vars[i].members, vars[i].member_count, FreeVariablesRef);
				}
			}
			free(vars);
			};

		FreeVariables(data->stage_inputs, data->stage_input_count, FreeVariables);
		FreeVariables(data->stage_outputs, data->stage_output_count, FreeVariables);
		FreeVariables(data->uniform_buffers, data->uniform_buffer_count, FreeVariables);
		FreeVariables(data->storage_buffers, data->storage_buffer_count, FreeVariables);
		FreeVariables(data->sampled_images, data->sampled_image_count, FreeVariables);
		FreeVariables(data->storage_images, data->storage_image_count, FreeVariables);
		FreeVariables(data->separate_samplers, data->separate_sampler_count, FreeVariables);
		FreeVariables(data->separate_images, data->separate_image_count, FreeVariables);
		FreeVariables(data->subpass_inputs, data->subpass_input_count, FreeVariables);
		FreeVariables(data->push_constants, data->push_constant_count, FreeVariables);
		FreeVariables(data->acceleration_structures, data->acceleration_structure_count, FreeVariables);
		FreeVariables(data->atomic_counters, data->atomic_counter_count, FreeVariables);
		FreeVariables(data->specialization_constants, data->specialization_constant_count, FreeVariables);

		data->stage_input_count = 0;
		data->stage_output_count = 0;
		data->uniform_buffer_count = 0;
		data->storage_buffer_count = 0;
		data->sampled_image_count = 0;
		data->storage_image_count = 0;
		data->separate_sampler_count = 0;
		data->separate_image_count = 0;
		data->subpass_input_count = 0;
		data->push_constant_count = 0;
		data->acceleration_structure_count = 0;
		data->atomic_counter_count = 0;
		data->specialization_constant_count = 0;
	}

	SPARKAPI SparkVoid SparkPrintShaderReflectionData(const SparkShaderReflectionData reflection_data) {
		if (!reflection_data) {
			printf("No reflection data.\n");
			return;
		}

		printf("=== Shader Reflection Data ===\n");
		printf("SPIR-V Size: %llu bytes\n", (SparkU64)reflection_data->spirv_size);
		printf("Stage: %u\n", (SparkU32)reflection_data->stage);

		PrintShaderVariableArray("Stage Inputs", reflection_data->stage_inputs, reflection_data->stage_input_count);
		PrintShaderVariableArray("Stage Outputs", reflection_data->stage_outputs, reflection_data->stage_output_count);
		PrintShaderVariableArray("Uniform Buffers", reflection_data->uniform_buffers, reflection_data->uniform_buffer_count);
		PrintShaderVariableArray("Storage Buffers", reflection_data->storage_buffers, reflection_data->storage_buffer_count);
		PrintShaderVariableArray("Sampled Images", reflection_data->sampled_images, reflection_data->sampled_image_count);
		PrintShaderVariableArray("Storage Images", reflection_data->storage_images, reflection_data->storage_image_count);
		PrintShaderVariableArray("Separate Samplers", reflection_data->separate_samplers, reflection_data->separate_sampler_count);
		PrintShaderVariableArray("Separate Images", reflection_data->separate_images, reflection_data->separate_image_count);
		PrintShaderVariableArray("Separate Storage Images", reflection_data->separate_storage_images, reflection_data->separate_storage_image_count);
		PrintShaderVariableArray("Subpass Inputs", reflection_data->subpass_inputs, reflection_data->subpass_input_count);
		PrintShaderVariableArray("Push Constants", reflection_data->push_constants, reflection_data->push_constant_count);
		PrintShaderVariableArray("Acceleration Structures", reflection_data->acceleration_structures, reflection_data->acceleration_structure_count);
		PrintShaderVariableArray("Atomic Counters", reflection_data->atomic_counters, reflection_data->atomic_counter_count);
		PrintShaderVariableArray("Specialization Constants", reflection_data->specialization_constants, reflection_data->specialization_constant_count);

		printf("=== End of Reflection Data ===\n");
	}

#ifdef __cplusplus
}
#endif