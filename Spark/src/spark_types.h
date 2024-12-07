#ifndef __SPARK_TYPES_H__
#define __SPARK_TYPES_H__

#include <stdio.h>

typedef unsigned char SparkU8;
typedef char SparkI8;
typedef unsigned short SparkU16;
typedef short SparkI16;
typedef unsigned int SparkU32;
typedef int SparkI32;
typedef unsigned long long SparkU64;
typedef long long SparkI64;
typedef float SparkF32;
typedef double SparkF64;
typedef SparkU8 SparkBool;
typedef SparkI32 SparkResult;
typedef void SparkVoid;
typedef void* SparkHandle;
typedef char* SparkString;
typedef const char* SparkConstString;
typedef SparkU8* SparkBuffer;
typedef const SparkU8* SparkConstBuffer;
typedef SparkU64 SparkSize;
typedef SparkU32 SparkIndex;
typedef SparkU32 SparkCount;
typedef SparkU32 SparkOffset;
typedef SparkU32 SparkTime;
typedef SparkU32 SparkDuration;
typedef SparkU32 SparkFrequency;
typedef SparkU32 SparkRate;
typedef SparkU64 SparkEventType;
typedef SparkU64 SparkSignature;


#ifdef _WIN32
#define _WIN32_WINNT 0x0600
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#endif


#ifdef _WIN32
#include <windows.h>
typedef HANDLE SparkThread;
typedef CRITICAL_SECTION SparkMutex;
typedef CONDITION_VARIABLE SparkCondition;
#else
#include <pthread.h>
typedef pthread_t SparkThread;
typedef pthread_mutex_t SparkMutex;
typedef pthread_cond_t SparkCondition;
#endif

typedef enum SparkShaderStage {
	SPARK_SHADER_STAGE_VERTEX = 0,
	SPARK_SHADER_STAGE_FRAGMENT = 1,
	SPARK_SHADER_STAGE_COMPUTE = 2,
	SPARK_SHADER_STAGE_GEOMETRY = 3,
	SPARK_SHADER_STAGE_TESS_CONTROL = 4,
	SPARK_SHADER_STAGE_TESS_EVALUATION = 5
} SparkShaderStage;

#define SPARK_EVENT_NONE ((SparkEventType)0x0ULL)
#define SPARK_EVENT_WINDOW_CLOSE ((SparkEventType)0x1ULL)
#define SPARK_EVENT_WINDOW_RESIZE ((SparkEventType)0x1ULL << 1)
#define SPARK_EVENT_WINDOW_FOCUS ((SparkEventType)0x1ULL << 2)
#define SPARK_EVENT_WINDOW_LOST_FOCUS ((SparkEventType)0x1ULL << 3)
#define SPARK_EVENT_WINDOW_MOVED ((SparkEventType)0x1ULL << 4)
#define SPARK_EVENT_KEY_PRESSED ((SparkEventType)0x1ULL << 5)
#define SPARK_EVENT_KEY_RELEASED ((SparkEventType)0x1ULL << 6)
#define SPARK_EVENT_KEY_TYPED ((SparkEventType)0x1ULL << 7)
#define SPARK_EVENT_MOUSE_BUTTON_PRESSED ((SparkEventType)0x1ULL << 8)
#define SPARK_EVENT_MOUSE_BUTTON_RELEASED ((SparkEventType)0x1ULL << 9)
#define SPARK_EVENT_MOUSE_MOVED ((SparkEventType)0x1ULL << 10)
#define SPARK_EVENT_MOUSE_SCROLLED ((SparkEventType)0x1ULL << 11)
#define SPARK_EVENT_ENTITY_CREATED ((SparkEventType)0x1ULL << 12)
#define SPARK_EVENT_ENTITY_DESTROYED ((SparkEventType)0x1ULL << 13)
#define SPARK_EVENT_COMPONENT_ADDED ((SparkEventType)0x1ULL << 14)
#define SPARK_EVENT_COMPONENT_UPDATED ((SparkEventType)0x1ULL << 15)
#define SPARK_EVENT_COMPONENT_REMOVED ((SparkEventType)0x1ULL << 16)
#define SPARK_EVENT_MAX_BIT ((SparkEventType)0x1ULL << 17)
#define SPARK_EVENT_ALL 0xFFFFFFFFFFFFFFFF

#define SPARK_ARRAY_ARG(arr) (arr), sizeof((arr)) / sizeof((arr)[0])

#define SPARK_EVENT_TYPE_WINDOW                                                \
  SPARK_EVENT_WINDOW_CLOSE | SPARK_EVENT_WINDOW_RESIZE |                       \
      SPARK_EVENT_WINDOW_FOCUS | SPARK_EVENT_WINDOW_LOST_FOCUS |               \
      SPARK_EVENT_WINDOW_MOVED
#define SPARK_EVENT_TYPE_KEY                                                   \
  SPARK_EVENT_KEY_PRESSED | SPARK_EVENT_KEY_RELEASED | SPARK_EVENT_KEY_TYPED
#define SPARK_EVENT_TYPE_MOUSE                                                 \
  SPARK_EVENT_MOUSE_BUTTON_PRESSED | SPARK_EVENT_MOUSE_BUTTON_RELEASED |       \
      SPARK_EVENT_MOUSE_MOVED | SPARK_EVENT_MOUSE_SCROLLED

#define SPARK_TRANSFORM_COMPONENT "__TRANSFORM_COMPONENT__"
#define SPARK_MATERIAL_COMPONENT "__MATERIAL_COMPONENT__"
#define SPARK_STATIC_MESH_COMPONENT "__STATIC_MESH_COMPONENT__"
#define SPARK_DYNAMIC_MESH_COMPONENT "__DYNAMIC_MESH_COMPONENT__"
#define SPARK_STATIC_MODEL_COMPONENT "__STATIC_MODEL_COMPONENT__"
#define SPARK_DYNAMIC_MODEL_COMPONENT "__DYNAMIC_MODEL_COMPONENT__"
#define SPARK_RIGID_BODY_COMPONENT "__RIGID_BODY_COMPONENT__"
#define SPARK_COLLIDER_COMPONENT "__COLLIDER_COMPONENT__"
#define SPARK_CAMERA_COMPONENT "__CAMERA_COMPONENT__"
#define SPARK_ANIMATION_COMPONENT "__ANIMATION_COMPONENT__"
#define SPARK_AI_BEHAVIOR_COMPONENT "__AI_BEHAVIOR_COMPONENT__"

#define SPARK_RESOURCE_TYPE_STATIC_MESH "__STATIC_MESH_RESOURCE__"
#define SPARK_RESOURCE_TYPE_DYNAMIC_MESH "__DYNAMIC_MESH_RESOURCE__"
#define SPARK_RESOURCE_TYPE_TEXTURE "__TEXTURE_RESOURCE__"
#define SPARK_RESOURCE_TYPE_SHADER "__SHADER_RESOURCE__"
#define SPARK_RESOURCE_TYPE_MATERIAL "__MATERIAL_RESOURCE__"
#define SPARK_RESOURCE_TYPE_STATIC_MODEL "__STATIC_MODEL_RESOURCE__"
#define SPARK_RESOURCE_TYPE_DYNAMIC_MODEL "__DYNAMIC_MODEL_RESOURCE__"
#define SPARK_RESOURCE_TYPE_AUDIO "__AUDIO_RESOURCE__"
#define SPARK_RESOURCE_TYPE_FONT "__FONT_RESOURCE__"
#define SPARK_RESOURCE_TYPE_ANIMATION "__ANIMATION_RESOURCE__"
#define SPARK_RESOURCE_TYPE_SCENE "__SCENE_RESOURCE__"
#define SPARK_RESOURCE_TYPE_AI_BEHAVIOR "__AI_BEHAVIOR_RESOURCE__"
#define SPARK_RESOURCE_TYPE_GRAPHICS_PIPELINE_CONFIG "__GRAPHICS_PIPELINE_CONFIG__"

#define SPARK_PI 3.14159265358979323846
#define SPARK_TWO_PI 6.28318530717958647692
#define SPARK_HALF_PI 1.57079632679489661923
#define SPARK_QUARTER_PI 0.78539816339744830962
#define SPARK_E 2.71828182845904523536
#define SPARK_SQRT2 1.41421356237309504880
#define SPARK_SQRT3 1.73205080756887729353
#define SPARK_LN2 0.69314718055994530942
#define SPARK_LN10 2.30258509299404568402
#define SPARK_LOG2E 1.44269504088896340736
#define SPARK_LOG10E 0.43429448190325182765
#define SPARK_INV_PI 0.31830988618379067154
#define SPARK_INV_SQRT_PI 0.56418958354775628694
#define SPARK_TWO_OVER_PI 0.63661977236758134308
#define SPARK_TWO_OVER_SQRT_PI 1.12837916709551257390
#define SPARK_DEG_TO_RAD (SPARK_PI / 180.0f)
#define SPARK_RAD_TO_DEG (180.0f / SPARK_PI)

#define SPARK_MAKE_VERTEX(x, y, z, nx, ny, nz, u, v)                           \
  (SparkVertex) {                                                              \
    .position = {x, y, z}, .normal = {nx, ny, nz}, .texcoord = { u, v }        \
  }

#define SPARK_UNTHREADED                                                       \
  (Pair) { SPARK_FALSE, SPARK_FALSE }
// Will block the main thread at the end of the frame until complete
#define SPARK_BLOCKED_PARRALLELISM                                             \
  (Pair) { SPARK_TRUE, SPARK_TRUE }
// Will continue running in between frames until complete
// good for async loading for models etc.
#define SPARK_UNBLOCKED_PARRALLELISM                                           \
  (Pair) { SPARK_TRUE, SPARK_FALSE }

#define SPARK_DEFAULT_SCENE "Default Scene"

#define INVALID_INDEX ((SparkSize)-1)

typedef enum SparkType {
	SPARK_FALSE = 0,
	SPARK_TRUE = 1,
	SPARK_SUCCESS = 1,
	SPARK_FAILURE = -1,
	SPARK_ERROR = -2,
	SPARK_VALID = 1,
	SPARK_INVALID = -1,
	SPARK_NULL = 0,
	SPARK_NONE = 0,
	SPARK_UNKNOWN = -4,
	SPARK_PENDING = -5,
	SPARK_IN_PROGRESS = -6,
	SPARK_COMPLETE = 2,
	SPARK_TIMEOUT = -7,
	SPARK_CANCELLED = -8,
	SPARK_NOT_IMPLEMENTED = -9,
	SPARK_ACCESS_DENIED = -10,
	SPARK_NOT_FOUND = -11,
	SPARK_BUSY = -12,
	SPARK_OVERLOADED = -13,
	SPARK_DISCONNECTED = -14,
	SPARK_CONNECTED = 3,
	SPARK_RETRY = -15,
	SPARK_DEPRECATED = -16,
	SPARK_UNSUPPORTED = -17,
	SPARK_INITIALIZED = 4,
	SPARK_UNINITIALIZED = -18,
	SPARK_ENABLED = 5,
	SPARK_DISABLED = -19,
	SPARK_READ_ONLY = -20,
	SPARK_WRITE_ONLY = -21,
	SPARK_READ_WRITE = 6,
	SPARK_SUCCESS_PARTIAL = -22,
	SPARK_INVALID_ARGUMENT = -23,
	SPARK_OUT_OF_MEMORY = -24,
	SPARK_OVERFLOW = -25,
	SPARK_UNDERFLOW = -26,
	SPARK_END_OF_FILE = -27,
	SPARK_PERMISSION_DENIED = -28,
	SPARK_BAD_REQUEST = -29,
	SPARK_CONFLICT = -30,
	SPARK_PRECONDITION_FAILED = -31
} SparkType;

typedef enum SparkError {
	SPARK_ERROR_NONE = 0,
	SPARK_ERROR_UNKNOWN = -1,
	SPARK_ERROR_INVALID = -2,
	SPARK_ERROR_NULL = -3,
	SPARK_ERROR_NOT_FOUND = -4,
	SPARK_ERROR_NOT_IMPLEMENTED = -5,
	SPARK_ERROR_ACCESS_DENIED = -6,
	SPARK_ERROR_BUSY = -7,
	SPARK_ERROR_OVERLOADED = -8,
	SPARK_ERROR_DISCONNECTED = -9,
	SPARK_ERROR_TIMEOUT = -10,
	SPARK_ERROR_CANCELLED = -11,
	SPARK_ERROR_RETRY = -12,
	SPARK_ERROR_UNSUPPORTED = -13,
	SPARK_ERROR_DEPRECATED = -14,
	SPARK_ERROR_UNINITIALIZED = -15,
	SPARK_ERROR_DISABLED = -16,
	SPARK_ERROR_READ_ONLY = -17,
	SPARK_ERROR_WRITE_ONLY = -18,
	SPARK_ERROR_OUT_OF_MEMORY = -19,
	SPARK_ERROR_OVERFLOW = -20,
	SPARK_ERROR_UNDERFLOW = -21,
	SPARK_ERROR_END_OF_FILE = -22,
	SPARK_ERROR_PERMISSION_DENIED = -23,
	SPARK_ERROR_BAD_REQUEST = -24,
	SPARK_ERROR_CONFLICT = -25,
	SPARK_ERROR_PRECONDITION_FAILED = -26,
	SPARK_ERROR_INVALID_ARGUMENT = -27,
	SPARK_ERROR_INVALID_STATE = -28,
	SPARK_ERROR_INVALID_FUNCTION_CALL = -29,
} SparkError;

typedef enum SparkAccess {
	SPARK_ACCESS_NONE = 0,
	SPARK_ACCESS_READ = 1,
	SPARK_ACCESS_WRITE = 2,
	SPARK_ACCESS_READ_WRITE = 3
} SparkAccess;

typedef enum SparkMouseButtonT {
	SPARK_MOUSE_BUTTON_1 = 0,
	SPARK_MOUSE_BUTTON_2 = 1,
	SPARK_MOUSE_BUTTON_3 = 2,
	SPARK_MOUSE_BUTTON_4 = 3,
	SPARK_MOUSE_BUTTON_5 = 4,
	SPARK_MOUSE_BUTTON_6 = 5,
	SPARK_MOUSE_BUTTON_7 = 6,
	SPARK_MOUSE_BUTTON_8 = 7,
	SPARK_MOUSE_BUTTON_LAST = SPARK_MOUSE_BUTTON_8,
	SPARK_MOUSE_BUTTON_LEFT = SPARK_MOUSE_BUTTON_1,
	SPARK_MOUSE_BUTTON_RIGHT = SPARK_MOUSE_BUTTON_2,
	SPARK_MOUSE_BUTTON_MIDDLE = SPARK_MOUSE_BUTTON_3
} SparkMouseButton;

typedef enum SparkKeyT {
	SPARK_KEY_UNKNOWN = -1,
	SPARK_KEY_SPACE = 32,
	SPARK_KEY_APOSTROPHE = 39, /* ' */
	SPARK_KEY_COMMA = 44,      /* , */
	SPARK_KEY_MINUS = 45,      /* - */
	SPARK_KEY_PERIOD = 46,     /* . */
	SPARK_KEY_SLASH = 47,      /* / */
	SPARK_KEY_0 = 48,
	SPARK_KEY_1 = 49,
	SPARK_KEY_2 = 50,
	SPARK_KEY_3 = 51,
	SPARK_KEY_4 = 52,
	SPARK_KEY_5 = 53,
	SPARK_KEY_6 = 54,
	SPARK_KEY_7 = 55,
	SPARK_KEY_8 = 56,
	SPARK_KEY_9 = 57,
	SPARK_KEY_SEMICOLON = 59, /* ; */
	SPARK_KEY_EQUAL = 61,     /* = */
	SPARK_KEY_A = 65,
	SPARK_KEY_B = 66,
	SPARK_KEY_C = 67,
	SPARK_KEY_D = 68,
	SPARK_KEY_E = 69,
	SPARK_KEY_F = 70,
	SPARK_KEY_G = 71,
	SPARK_KEY_H = 72,
	SPARK_KEY_I = 73,
	SPARK_KEY_J = 74,
	SPARK_KEY_K = 75,
	SPARK_KEY_L = 76,
	SPARK_KEY_M = 77,
	SPARK_KEY_N = 78,
	SPARK_KEY_O = 79,
	SPARK_KEY_P = 80,
	SPARK_KEY_Q = 81,
	SPARK_KEY_R = 82,
	SPARK_KEY_S = 83,
	SPARK_KEY_T = 84,
	SPARK_KEY_U = 85,
	SPARK_KEY_V = 86,
	SPARK_KEY_W = 87,
	SPARK_KEY_X = 88,
	SPARK_KEY_Y = 89,
	SPARK_KEY_Z = 90,
	SPARK_KEY_LEFT_BRACKET = 91,  /* [ */
	SPARK_KEY_BACKSLASH = 92,     /* \ */
	SPARK_KEY_RIGHT_BRACKET = 93, /* ] */
	SPARK_KEY_GRAVE_ACCENT = 96,  /* ` */
	SPARK_KEY_WORLD_1 = 161,      /* non-US #1 */
	SPARK_KEY_WORLD_2 = 162,      /* non-US #2 */

	/* Function keys */
	SPARK_KEY_ESCAPE = 256,
	SPARK_KEY_ENTER = 257,
	SPARK_KEY_TAB = 258,
	SPARK_KEY_BACKSPACE = 259,
	SPARK_KEY_INSERT = 260,
	SPARK_KEY_DELETE = 261,
	SPARK_KEY_RIGHT = 262,
	SPARK_KEY_LEFT = 263,
	SPARK_KEY_DOWN = 264,
	SPARK_KEY_UP = 265,
	SPARK_KEY_PAGE_UP = 266,
	SPARK_KEY_PAGE_DOWN = 267,
	SPARK_KEY_HOME = 268,
	SPARK_KEY_END = 269,
	SPARK_KEY_CAPS_LOCK = 280,
	SPARK_KEY_SCROLL_LOCK = 281,
	SPARK_KEY_NUM_LOCK = 282,
	SPARK_KEY_PRINT_SCREEN = 283,
	SPARK_KEY_PAUSE = 284,
	SPARK_KEY_F1 = 290,
	SPARK_KEY_F2 = 291,
	SPARK_KEY_F3 = 292,
	SPARK_KEY_F4 = 293,
	SPARK_KEY_F5 = 294,
	SPARK_KEY_F6 = 295,
	SPARK_KEY_F7 = 296,
	SPARK_KEY_F8 = 297,
	SPARK_KEY_F9 = 298,
	SPARK_KEY_F10 = 299,
	SPARK_KEY_F11 = 300,
	SPARK_KEY_F12 = 301,
	SPARK_KEY_F13 = 302,
	SPARK_KEY_F14 = 303,
	SPARK_KEY_F15 = 304,
	SPARK_KEY_F16 = 305,
	SPARK_KEY_F17 = 306,
	SPARK_KEY_F18 = 307,
	SPARK_KEY_F19 = 308,
	SPARK_KEY_F20 = 309,
	SPARK_KEY_F21 = 310,
	SPARK_KEY_F22 = 311,
	SPARK_KEY_F23 = 312,
	SPARK_KEY_F24 = 313,
	SPARK_KEY_F25 = 314,
	SPARK_KEY_KP_0 = 320,
	SPARK_KEY_KP_1 = 321,
	SPARK_KEY_KP_2 = 322,
	SPARK_KEY_KP_3 = 323,
	SPARK_KEY_KP_4 = 324,
	SPARK_KEY_KP_5 = 325,
	SPARK_KEY_KP_6 = 326,
	SPARK_KEY_KP_7 = 327,
	SPARK_KEY_KP_8 = 328,
	SPARK_KEY_KP_9 = 329,
	SPARK_KEY_KP_DECIMAL = 330,
	SPARK_KEY_KP_DIVIDE = 331,
	SPARK_KEY_KP_MULTIPLY = 332,
	SPARK_KEY_KP_SUBTRACT = 333,
	SPARK_KEY_KP_ADD = 334,
	SPARK_KEY_KP_ENTER = 335,
	SPARK_KEY_KP_EQUAL = 336,
	SPARK_KEY_LEFT_SHIFT = 340,
	SPARK_KEY_LEFT_CONTROL = 341,
	SPARK_KEY_LEFT_ALT = 342,
	SPARK_KEY_LEFT_SUPER = 343,
	SPARK_KEY_RIGHT_SHIFT = 344,
	SPARK_KEY_RIGHT_CONTROL = 345,
	SPARK_KEY_RIGHT_ALT = 346,
	SPARK_KEY_RIGHT_SUPER = 347,
	SPARK_KEY_MENU = 348
} SparkKey;

typedef enum SparkModifierT {
	SPARK_MOD_SHIFT = 0x0001,
	SPARK_MOD_CONTROL = 0x0002,
	SPARK_MOD_ALT = 0x0004,
	SPARK_MOD_SUPER = 0x0008
} SparkModifier;

typedef enum SparkActionT {
	SPARK_RELEASE = 0,
	SPARK_PRESS = 1,
	SPARK_REPEAT = 2
} SparkAction;

typedef enum SparkCursorT {
	SPARK_CURSOR_ARROW = 0,
	SPARK_CURSOR_IBEAM = 1,
	SPARK_CURSOR_CROSSHAIR = 2,
	SPARK_CURSOR_HAND = 3,
	SPARK_CURSOR_HRESIZE = 4,
	SPARK_CURSOR_VRESIZE = 5
} SparkCursor;

/* Shader types */
typedef enum SparkShaderTypeT {
	SPARK_SHADER_VERTEX = 0,
	SPARK_SHADER_FRAGMENT = 1,
	SPARK_SHADER_COMPUTE = 2,
	SPARK_SHADER_GEOMETRY = 3,
	SPARK_SHADER_TESSELLATION_CONTROL = 4,
	SPARK_SHADER_TESSELLATION_EVALUATION = 5
} SparkShaderType;

/* Primitive types */
typedef enum SparkPrimitiveTypeT {
	SPARK_PRIMITIVE_POINTS = 0,
	SPARK_PRIMITIVE_LINES,
	SPARK_PRIMITIVE_LINE_STRIP,
	SPARK_PRIMITIVE_TRIANGLES,
	SPARK_PRIMITIVE_TRIANGLE_STRIP,
	SPARK_PRIMITIVE_TRIANGLE_FAN
} SparkPrimitiveType;

/* Blend modes */
typedef enum SparkBlendModeT {
	SPARK_BLEND_ZERO = 0,
	SPARK_BLEND_ONE,
	SPARK_BLEND_SRC_COLOR,
	SPARK_BLEND_ONE_MINUS_SRC_COLOR,
	SPARK_BLEND_DST_COLOR,
	SPARK_BLEND_ONE_MINUS_DST_COLOR,
	SPARK_BLEND_SRC_ALPHA,
	SPARK_BLEND_ONE_MINUS_SRC_ALPHA,
	SPARK_BLEND_DST_ALPHA,
	SPARK_BLEND_ONE_MINUS_DST_ALPHA,
	SPARK_BLEND_CONSTANT_COLOR,
	SPARK_BLEND_ONE_MINUS_CONSTANT_COLOR,
	SPARK_BLEND_CONSTANT_ALPHA,
	SPARK_BLEND_ONE_MINUS_CONSTANT_ALPHA,
	SPARK_BLEND_SRC_ALPHA_SATURATE
} SparkBlendMode;

/* Texture filtering options */
typedef enum SparkTextureFilterT {
	SPARK_TEXTURE_FILTER_NEAREST = 0,
	SPARK_TEXTURE_FILTER_LINEAR = 1,
	SPARK_TEXTURE_FILTER_MIPMAP_NEAREST = 0,
	SPARK_TEXTURE_FILTER_MIPMAP_LINEAR = 1,
} SparkTextureFilter;

/* Log levels */
typedef enum SparkLogLevelT {
	SPARK_LOG_LEVEL_TRACE = 0,
	SPARK_LOG_LEVEL_DEBUG,
	SPARK_LOG_LEVEL_INFO,
	SPARK_LOG_LEVEL_WARN,
	SPARK_LOG_LEVEL_ERROR,
	SPARK_LOG_LEVEL_FATAL
} SparkLogLevel;

/* Render APIs */
typedef enum SparkRenderAPIT {
	SPARK_RENDER_API_NONE = 0,
	SPARK_RENDER_API_OPENGL,
	SPARK_RENDER_API_VULKAN,
	SPARK_RENDER_API_DIRECTX,
	SPARK_RENDER_API_METAL
} SparkRenderAPI;

typedef enum SparkPresentModeT {
	SPARK_PRESENT_MODE_IMMEDIATE = 0,
	SPARK_PRESENT_MODE_MAILBOX = 1
} SparkPresentMode;

typedef enum SparkEnvelopeTypeT {
	SPARK_ENVELOPE_TYPE_DATA = 0,
	SPARK_ENVELOPE_TYPE_COMMAND,
	SPARK_ENVELOPE_TYPE_RESPONSE,
} SparkEnvelopeType;

typedef enum SparkIteratorStateT {
	SPARK_ITERATOR_STATE_INVALID = -1,
	SPARK_ITERATOR_STATE_NONE = 0,
	SPARK_ITERATOR_STATE_ITERATING,
	SPARK_ITERATOR_STATE_BEGIN,
	SPARK_ITERATOR_STATE_END,
} SparkIteratorState;

typedef enum SparkIteratorTypeT {
	SPARK_ITERATOR_TYPE_INVALID = 0,
	SPARK_ITERATOR_TYPE_VECTOR,
	SPARK_ITERATOR_TYPE_HASHMAP,
	SPARK_ITERATOR_TYPE_LIST,
} SparkIteratorType;

typedef enum SparkHashMapIteratorTypeT {
	SPARK_HASHMAP_ITERATOR_TYPE_KEY,
	SPARK_HASHMAP_ITERATOR_TYPE_VALUE,
	SPARK_HASHMAP_ITERATOR_TYPE_PAIR,
} SparkHashMapIteratorType;


typedef enum SparkShaderVariableType {
	SPARK_SHADER_VARIABLE_TYPE_UNKNOWN = 0,
	SPARK_SHADER_VARIABLE_TYPE_BOOL,
	SPARK_SHADER_VARIABLE_TYPE_INT,
	SPARK_SHADER_VARIABLE_TYPE_UINT,
	SPARK_SHADER_VARIABLE_TYPE_FLOAT,
	SPARK_SHADER_VARIABLE_TYPE_DOUBLE,
	SPARK_SHADER_VARIABLE_TYPE_STRUCT
} SparkShaderVariableType;

typedef enum SparkShaderResourceType {
	SPARK_SHADER_RESOURCE_TYPE_UNKNOWN = 0,
	SPARK_SHADER_RESOURCE_TYPE_STAGE_INPUT,
	SPARK_SHADER_RESOURCE_TYPE_STAGE_OUTPUT,
	SPARK_SHADER_RESOURCE_TYPE_UNIFORM_BUFFER,
	SPARK_SHADER_RESOURCE_TYPE_STORAGE_BUFFER,
	SPARK_SHADER_RESOURCE_TYPE_SAMPLED_IMAGE,
	SPARK_SHADER_RESOURCE_TYPE_STORAGE_IMAGE,
	SPARK_SHADER_RESOURCE_TYPE_SEPARATE_SAMPLER,
	SPARK_SHADER_RESOURCE_TYPE_SEPARATE_IMAGE,
	SPARK_SHADER_RESOURCE_TYPE_SEPARATE_STORAGE_IMAGE,
	SPARK_SHADER_RESOURCE_TYPE_SUBPASS_INPUT,
	SPARK_SHADER_RESOURCE_TYPE_PUSH_CONSTANT,
	SPARK_SHADER_RESOURCE_TYPE_ACCELERATION_STRUCTURE,
	SPARK_SHADER_RESOURCE_TYPE_ATOMIC_COUNTER,
	SPARK_SHADER_RESOURCE_TYPE_SPECIALIZATION_CONSTANT
} SparkShaderResourceType;

typedef enum SparkShaderImageDimension {
	SPARK_SHADER_IMAGE_DIM_UNSPECIFIED = 0,
	SPARK_SHADER_IMAGE_DIM_1D,
	SPARK_SHADER_IMAGE_DIM_2D,
	SPARK_SHADER_IMAGE_DIM_3D,
	SPARK_SHADER_IMAGE_DIM_CUBE,
	SPARK_SHADER_IMAGE_DIM_RECT,
	SPARK_SHADER_IMAGE_DIM_BUFFER,
	SPARK_SHADER_IMAGE_DIM_SUBPASS
} SparkShaderImageDimension;

typedef struct SparkShaderVariableT {
	SparkString name;
	SparkShaderResourceType resource_type;

	SparkU32 location; // for stage inputs/outputs
	SparkU32 set;      // for descriptor-based resources
	SparkU32 binding;
	SparkU32 offset;   // for push constants or struct members
	SparkU32 size;     // size in bytes of this variable/struct

	SparkShaderVariableType base_type;
	SparkU32 vec_size;
	SparkU32 columns;
	SparkU32 array_dimension_count;
	SparkU32* array_sizes; // if array_dimension_count > 0

	// Struct members
	SparkU32 member_count;
	struct SparkShaderVariableT* members;

	// Built-in decoration
	SparkI32 is_builtin;
	SparkU32 builtin_type; // Use SPIR-V builtin enum if you need

	// Image/sampler info (if applicable)
	SparkShaderImageDimension image_dimension;
	SparkI32 is_depth;
	SparkI32 is_arrayed;
	SparkI32 is_multisampled;
	SparkI32 is_storage;
	SparkI32 is_sampled;
	SparkI32 is_subpass_input;
	// Format info can be extended as needed

	// Specialization constant ID
	SparkU32 spec_constant_id;
} SparkShaderVariable;

typedef struct SparkShaderReflectionDataT {
	SparkHandle spirv_data;
	SparkSize spirv_size;

	SparkShaderStage stage;

	// We store all resources in one array or separate arrays.
	// To simplify, let's store each resource type in its own array.
	SparkSize stage_input_count;
	SparkShaderVariable* stage_inputs;

	SparkSize stage_output_count;
	SparkShaderVariable* stage_outputs;

	SparkSize uniform_buffer_count;
	SparkShaderVariable* uniform_buffers;

	SparkSize storage_buffer_count;
	SparkShaderVariable* storage_buffers;

	SparkSize sampled_image_count;
	SparkShaderVariable* sampled_images;

	SparkSize storage_image_count;
	SparkShaderVariable* storage_images;

	SparkSize separate_sampler_count;
	SparkShaderVariable* separate_samplers;

	SparkSize separate_image_count;
	SparkShaderVariable* separate_images;

	SparkSize separate_storage_image_count;
	SparkShaderVariable* separate_storage_images;

	SparkSize subpass_input_count;
	SparkShaderVariable* subpass_inputs;

	SparkSize push_constant_count;
	SparkShaderVariable* push_constants;

	SparkSize acceleration_structure_count;
	SparkShaderVariable* acceleration_structures;

	SparkSize atomic_counter_count;
	SparkShaderVariable* atomic_counters;

	SparkSize specialization_constant_count;
	SparkShaderVariable* specialization_constants;
} *SparkShaderReflectionData;

typedef struct SparkEventDataKeyPressedT {
	SparkKey key;
	SparkI32 repeat;
} *SparkEventDataKeyPressed;

typedef struct SparkEventDataKeyReleasedT {
	SparkKey key;
} *SparkEventDataKeyReleased;

typedef struct SparkEventDataMouseMovedT {
	SparkF64 xpos;
	SparkF64 ypos;
} *SparkEventDataMouseMoved;

typedef struct SparkEventDataMouseButtonPressedT {
	SparkMouseButton button;
} *SparkEventDataMouseButtonPressed;

typedef struct SparkEventDataMouseButtonReleasedT {
	SparkMouseButton button;
} *SparkEventDataMouseButtonReleased;

typedef struct SparkEventDataMouseScrolledT {
	SparkF64 x;
	SparkF64 y;
} *SparkEventDataMouseScrolled;

typedef struct SparkEventDataWindowResizedT {
	SparkI32 width;
	SparkI32 height;
} *SparkEventDataWindowResized;

typedef SparkF32 SparkScalar;
typedef SparkI32 SparkIScalar;

struct SparkEcsT;

typedef struct SparkVector2T {
	SparkScalar x;
	SparkScalar y;
} SparkVec2;

typedef struct SparkVector3T {
	SparkScalar x;
	SparkScalar y;
	SparkScalar z;
} SparkVec3;

typedef struct SparkVector4T {
	SparkScalar x;
	SparkScalar y;
	SparkScalar z;
	SparkScalar w;
} SparkVec4;

typedef struct SparkMatrix2T {
	SparkScalar m00, m01;
	SparkScalar m10, m11;
} SparkMat2;

typedef struct SparkMatrix3T {
	SparkScalar m00, m01, m02;
	SparkScalar m10, m11, m12;
	SparkScalar m20, m21, m22;
} SparkMat3;

typedef struct SparkMatrix4T {
	SparkScalar m00, m10, m20, m30; // Column 0
	SparkScalar m01, m11, m21, m31; // Column 1
	SparkScalar m02, m12, m22, m32; // Column 2
	SparkScalar m03, m13, m23, m33; // Column 3
} SparkMat4;

typedef struct SparkQuaternionT {
	SparkScalar x;
	SparkScalar y;
	SparkScalar z;
	SparkScalar w;
} SparkQuat;

typedef struct SparkIVector2T {
	SparkIScalar x;
	SparkIScalar y;
} SparkIVec2;

typedef struct SparkIVector3T {
	SparkIScalar x;
	SparkIScalar y;
	SparkIScalar z;
} SparkIVec3;

typedef struct SparkIVector4T {
	SparkIScalar x;
	SparkIScalar y;
	SparkIScalar z;
	SparkIScalar w;
} SparkIVec4;

typedef struct SparkColorT {
	SparkScalar r;
	SparkScalar g;
	SparkScalar b;
	SparkScalar a;
} SparkColor;

typedef struct SparkRectT {
	SparkScalar x;
	SparkScalar y;
	SparkScalar width;
	SparkScalar height;
} SparkRect;

typedef struct SparkCircleT {
	SparkScalar x;
	SparkScalar y;
	SparkScalar radius;
} SparkCircle;

typedef struct SparkLineT {
	SparkScalar x1;
	SparkScalar y1;
	SparkScalar x2;
	SparkScalar y2;
} SparkLine;

typedef struct SparkTriangleT {
	SparkScalar x1;
	SparkScalar y1;
	SparkScalar x2;
	SparkScalar y2;
	SparkScalar x3;
	SparkScalar y3;
} SparkTriangle;

typedef struct SparkQuadT {
	SparkScalar x1;
	SparkScalar y1;
	SparkScalar x2;
	SparkScalar y2;
	SparkScalar x3;
	SparkScalar y3;
	SparkScalar x4;
	SparkScalar y4;
} SparkQuad;

typedef SparkHandle(*SparkAllocateFunction)(SparkSize size);
typedef SparkHandle(*SparkReallocateFunction)(SparkHandle handle,
	SparkSize size);
typedef SparkVoid(*SparkFreeFunction)(SparkHandle handle);
typedef SparkSize(*SparkHashFunction)(SparkConstBuffer buf, SparkSize length);
typedef SparkResult(*SparkSystemStartFunction)(struct SparkEcsT* ecs);
typedef SparkResult(*SparkSystemUpdateFunction)(struct SparkEcsT* ecs,
	SparkF32 delta);
typedef SparkResult(*SparkSystemStopFunction)(struct SparkEcsT* ecs);
typedef SparkI32(*SparkCompareFunction)(SparkHandle a, SparkSize a_size,
	SparkHandle b, SparkSize b_size);
typedef SparkHandle(*SparkThreadFunction)(SparkHandle arg);

typedef SparkVoid(*SparkApplicationStartFunction)(
	struct SparkApplicationT* app);
typedef SparkVoid(*SparkApplicationUpdateFunction)(
	struct SparkApplicationT* app);
typedef SparkVoid(*SparkApplicationStopFunction)(
	struct SparkApplicationT* app);
typedef SparkVoid(*SparkApplicationEventFunction)(
	struct SparkApplicationT* app, struct SparkEventT event);
typedef SparkVoid(*SparkApplicationQueryFunction)(
	struct SparkApplicationT* app, struct SparkVectorT* query);
typedef SparkVoid(*SparkApplicationQueryEventFunction)(
	struct ApplicationT* app, struct SparkVectorT* query,
	struct SparkEventT event);
typedef SparkVoid(*SparkServerReceiveCallback)(
	struct SparkServerT* server, struct SparkClientConnectionT* client,
	struct SparkEnvelopeT* envelope);
typedef SparkVoid(*SparkClientReceiveCallback)(
	struct SparkClientT* client, struct SparkEnvelopeT* envelope);
typedef SparkVoid(*SparkThreadPoolShutdownCallback)(SparkHandle arg);

typedef SparkIteratorState(*SparkIteratorIterateForward)(
	struct SparkIteratorT* it);
typedef SparkIteratorState(*SparkIteratorIterateBackward)(
	struct SparkIteratorT* it);
typedef SparkIteratorState(*SparkIteratorIsAtBeginningFunction)(
	struct SparkIteratorT* it);
typedef SparkIteratorState(*SparkIteratorIsAtEndFunction)(
	struct SparkIteratorT* it);
typedef SparkHandle(*SparkIteratorGetCurrentFunction)(
	struct SparkIteratorT* it);
typedef SparkHandle(*SparkIteratorGetPreviousFunction)(
	struct SparkIteratorT* it);
typedef SparkHandle(*SparkIteratorGetNextFunction)(struct SparkIteratorT* it);
typedef SparkBool(*SparkIteratorHasNextFunction)(struct SparkIteratorT* it);
typedef SparkBool(*SparkIteratorHasPreviousFunction)(
	struct SparkIteratorT* it);
typedef SparkVoid(*SparkIteratorFreeFunction)(struct SparkIteratorT* it);

typedef struct SparkAllocatorT {
	SparkAllocateFunction allocate;
	SparkReallocateFunction reallocate;
	SparkFreeFunction free;
	SparkU32 ref_count;
} *SparkAllocator;

typedef struct SparkPairT {
	SparkHandle first;
	SparkHandle second;
} SparkPair;

typedef struct SparkVectorT {
	SparkSize size;
	SparkSize capacity;
	/* Destructor to be called on each element */
	SparkFreeFunction destructor;
	SparkHandle* elements;
	SparkAllocator allocator;
} *SparkVector;

typedef struct SparkVectorIteratorT {
	SparkIteratorState state;
	SparkVector vector;
	SparkSize pos;
} *SparkVectorIterator;

typedef struct SparkListNodeT {
	SparkHandle data;
	struct SparkListNodeT* next;
} *SparkListNode;

typedef struct SparkListT {
	SparkSize size;
	/* Destructor to be called on each element */
	SparkFreeFunction destructor;
	SparkListNode head;
	SparkListNode tail;
	SparkAllocator allocator;
} *SparkList;

typedef struct SparkListIteratorT {
	SparkIteratorState state;
	SparkList list;
	SparkSize pos;
} *SparkListIterator;

typedef struct SparkHashMapNodeT {
	SparkHandle key;
	SparkHandle value;
	SparkSize key_size;
	SparkSize hash;
	struct SparkHashMapNodeT* next;
} *SparkHashMapNode;

typedef struct SparkHashMapT {
	SparkAllocator allocator;
	SparkSize capacity;
	SparkSize size;
	SparkHashMapNode* buckets;
	SparkHashFunction hash_function;
	SparkCompareFunction compare_function;
	SparkFreeFunction key_destructor;
	SparkFreeFunction value_destructor;
} *SparkHashMap;

typedef struct SparkAtomicVectorT {
	SparkMutex mutex;
	SparkVector vector;
	volatile SparkSize* ref_count;
} *SparkAtomicVector;

typedef struct SparkAtomicHashMapT {
	SparkMutex mutex;
	SparkCondition condition;
	SparkHashMap hashmap;
	volatile SparkSize* ref_count;
} *SparkAtomicHashMap;

typedef struct SparkHashMapIteratorT {
	SparkIteratorState state;
	SparkHashMap hash_map;
	SparkHashMapIteratorType iterator_type;
	/* Allocated data that gets constructed while iterating the HashMap */
	SparkVector iterator_data;
	SparkSize pos;
} *SparkHashMapIterator;

typedef struct SparkMapT {
	SparkSize size;
	SparkHandle root;
	SparkAllocator allocator;
} *SparkMap;

typedef struct SparkSetT {
	SparkAllocator allocator;
	SparkSize capacity;
	SparkSize size;
	SparkFreeFunction destructor;
	SparkHandle* elements;
} *SparkSet;

typedef struct SparkHashSetT {
	SparkAllocator allocator;
	SparkSize capacity;
	SparkSize size;
	SparkSize element_size;
	SparkFreeFunction destructor;
	SparkHandle* elements;
	SparkSize* hashes;
	SparkHashFunction hash_function;
} *SparkHashSet;

typedef struct SparkQueueT {
	SparkAllocator allocator;
	SparkSize capacity;
	SparkSize size;
	SparkSize front;
	SparkSize rear;
	SparkFreeFunction destructor;
	SparkHandle* elements;
} *SparkQueue;

typedef struct SparkStackT {
	SparkAllocator allocator;
	SparkSize capacity;
	SparkSize size;
	SparkFreeFunction destructor;
	SparkHandle* elements;
} *SparkStack;

typedef struct SparkIteratorT {
	SparkIteratorIterateForward iterate_forward;
	SparkIteratorIterateBackward iterate_backward;
	SparkIteratorIsAtBeginningFunction is_at_beginning;
	SparkIteratorIsAtEndFunction is_at_end;
	SparkIteratorGetCurrentFunction get_current;
	SparkIteratorGetPreviousFunction get_previous;
	SparkIteratorGetNextFunction get_next;
	SparkIteratorHasNextFunction has_next;
	SparkIteratorHasPreviousFunction has_previous;
	SparkIteratorFreeFunction free;
	SparkIteratorType iterator_type;
	union {
		SparkVectorIterator vector_iterator;
		SparkListIterator list_iterator;
		SparkHashMapIterator hash_map_iterator;
	};
} *SparkIterator;

typedef struct SparkTaskT {
	SparkThreadFunction function;
	SparkHandle arg;
	SparkHandle result;
	struct SparkTaskT* next;
	SparkMutex mutex;
	SparkCondition cond;
	/* Wait for this task to finish before continuing the next update frame */
	SparkBool wait_on_update;
	SparkI32 is_done;
} *SparkTaskHandle;

typedef struct SparkThreadPoolT {
	SparkThread* threads;
	SparkSize thread_count;
	SparkTaskHandle task_queue_head;
	SparkTaskHandle task_queue_tail;
	SparkMutex mutex;
	SparkCondition condition;
	SparkSize pending_task_count;
	SparkMutex pending_task_mutex;
	SparkCondition pending_task_cond;
	volatile SparkI32 stop;
	volatile SparkI32 shutdown;
	/* SparkVector <SparkThreadPoolShutdownCallback */
	SparkVector shutdown_callbacks;
	/* SparkVector <SparkHandle> */
	SparkVector shutdown_callback_args;
} *SparkThreadPool;

typedef struct SparkUniformBufferObjectT {
	struct VkBuffer_T* buffer;
	struct VkDeviceMemory_T* memory;
	struct VkDescriptorBufferInfo_T* descriptor;
	SparkHandle data;
};

typedef struct SparkQueryT {
	SparkSignature signature;   // Required components' signature
} *SparkQuery;

typedef struct SparkEventT {
	SparkEventType type;
	SparkHandle data;
	SparkConstString timestamp;
	SparkFreeFunction destructor;
	/* Atomic counter */
	volatile SparkSize* ref_count;
} SparkEvent;

typedef struct SparkEventHandlerFunctionT {
	SparkEventType event_type;
	SparkApplicationEventFunction function;
	SparkPair thread_settings;
} *SparkEventHandlerFunction;

typedef struct SparkQueryEventHandlerFunctionT {
	SparkEventType event_type;
	SparkQuery query;
	SparkApplicationQueryEventFunction function;
	SparkPair thread_settings;
} *SparkQueryEventHandlerFunction;

typedef struct SparkQueryHandlerFunctionT {
	SparkConstString component_type;
	SparkApplicationQueryFunction function;
	SparkPair thread_settings;
	SparkQuery query;
} *SparkQueryHandlerFunction;

typedef struct SparkUpdateHandlerFunctionT {
	SparkApplicationUpdateFunction function;
	SparkPair thread_settings;
} *SparkUpdateHandlerFunction;

typedef struct SparkStartHandlerFunctionT {
	SparkApplicationStartFunction function;
	SparkPair thread_settings;
} *SparkStartHandlerFunction;

typedef struct SparkStopHandlerFunctionT {
	SparkApplicationStopFunction function;
	SparkPair thread_settings;
} *SparkStopHandlerFunction;

typedef struct SparkEventHandlerT {
	/* Vector <SparkEventHandlerFunction> */
	SparkVector event_functions;
	/* HashMap <SparkConstString, SparkVector <SparkQueryEventHandlerFunction>> */
	SparkHashMap query_functions;
	struct SparkApplicationT* application;
	struct SparkEcsT* ecs;
	SparkMutex mutex;
} *SparkEventHandler;

typedef struct SparkShaderT {
	SparkShaderType type;
	struct VkShaderModule_T* module;
	struct VkDevice_T* device;
	SparkConstString entry_point; /* Usually main */
	SparkConstString filename;
	SparkShaderReflectionData shader_data;
} *SparkShader;

typedef SparkI32 SparkEntity;

typedef struct SparkComponentT {
	SparkConstString type;
	SparkConstString name;
	SparkHandle data;
	SparkFreeFunction destructor;
	/* Parent entity of this component */
	SparkEntity entity;
} *SparkComponent;

typedef struct SparkTransformComponentT {
	SparkVec3 position;
	SparkQuat rotation;
	SparkVec3 scale;
} *SparkTransformComponent;

typedef struct SparkStaticModelComponentT {
	SparkConstString model_name;
} *SparkStaticModelComponent;

typedef struct SparkDynamicModelComponentT {
	SparkConstString model_name;
} *SparkDynamicModelComponent;

typedef struct SparkComponentArrayT {
	SparkComponent* dense;   // Dense array of components
	SparkEntity* entities;   // Entity IDs corresponding to components
	SparkSize* sparse;       // Mapping from entity IDs to indices in dense array
	SparkSize size;          // Number of active components
	SparkSize dense_capacity;
	SparkSize sparse_capacity;
} *SparkComponentArray;


typedef struct SparkSystemT {
	SparkSystemStartFunction start;
	SparkSystemUpdateFunction update;
	SparkSystemStopFunction stop;
	SparkEventHandler event_handler;
	SparkHandle system_data;
} *SparkSystem;


typedef struct SparkQueryCacheT {
	SparkQuery query;
	SparkVector entities;  // Cached entities matching the query
	SparkSize version;     // ECS version at the time of caching
} *SparkQueryCache;

typedef struct SparkEcsT {
	SparkAllocator allocator;
	SparkVector entities;            // Vector<SparkEntity>
	SparkVector systems;             // Vector<SparkSystem>
	SparkHashMap components;         // HashMap<SparkString, SparkComponentArray>
	SparkStack recycled_ids;         // Stack<SparkEntity>
	SparkEventHandler event_handler;
	SparkSignature* signatures;      // Array of signatures for entities
	SparkSize entity_count;          // Total number of entities
	SparkSize version;               // Version for cache invalidation
	SparkVector query_caches;        // Vector<SparkQueryCache>
	SparkMutex mutex;
} *SparkEcs;

typedef struct SparkEventDataEntityCreatedT {
	SparkEntity entity;
	SparkEcs ecs;
} *SparkEventDataEntityCreated;

typedef struct SparkEventDataEntityDestroyedT {
	SparkEntity entity;
	SparkEcs ecs;
} *SparkEventDataEntityDestroyed;

typedef struct SparkEventDataComponentAddedT {
	SparkEntity entity;
	SparkComponent component;
	SparkEcs ecs;
} *SparkEventDataComponentAdded;

typedef struct SparkEventDataComponentUpdatedT {
	SparkEntity entity;
	SparkComponent component;
	SparkEcs ecs;
} *SparkEventDataComponentUpdated;

typedef struct SparkEventDataComponentRemovedT {
	SparkEntity entity;
	SparkEcs ecs;
	SparkConstString type;
	SparkConstString name;
} *SparkEventDataComponentRemoved;

typedef struct SparkResourceT {
	SparkHandle data;
	SparkConstString name;
	SparkConstString type;
	SparkFreeFunction destructor;
} *SparkResource;

typedef struct SparkSceneT {
	/* Temporary Scene stuff, right now just a color */
	SparkVec4 sky_color;
} *SparkScene;

typedef struct SparkResourceLoaderT {
	SparkConstString type;
	SparkHandle(*load)(SparkConstString path);
	SparkResult(*unload)(SparkHandle handle);
} *SparkResourceLoader;

typedef struct SparkResourceManagerT {
	/* HashMap <SparkString, SparkResourceLoader> */
	SparkHashMap loaders;
	/* Type to be inserted into all SparkResources */
	SparkConstString type;
	/* HashMap <SparkString, SparkResource> */
	SparkHashMap resources;
	/* Current resource, only used for some things like Scenes */
	SparkResource current_resource;
	SparkFreeFunction resource_destructor;
} *SparkResourceManager;

typedef struct SparkWindowDataT {
	SparkI32 width;
	SparkI32 height;
	SparkBool vsync;
	SparkPresentMode present_mode;
	SparkConstString title;
	SparkEventHandler event_handler;
} *SparkWindowData;

/* Physics-related declarations */
typedef struct SparkRigidBodyT {
	SparkVec3 position;
	SparkVec3 velocity;
	SparkVec3 acceleration;
	SparkQuat rotation;
	SparkScalar mass;
	SparkScalar friction;
	SparkScalar restitution;
} *SparkRigidBody;

typedef struct SparkTextureT {
	struct VkDevice_T* device;
	struct VkImage_T* image;
	struct VkDeviceMemory_T* image_memory;
	struct VkImageView_T* image_view;
	struct VkSampler_T* texture_sampler;
	SparkI32 width;
	SparkI32 height;
	SparkI32 channels;
} *SparkTexture;

typedef struct SparkColliderT {
	enum {
		SPARK_COLLIDER_TYPE_BOX,
		SPARK_COLLIDER_TYPE_SPHERE,
		SPARK_COLLIDER_TYPE_CAPSULE,
		SPARK_COLLIDER_TYPE_MESH,
	} type;
	// Collider-specific data
	union {
		struct {
			SparkVec3 half_extents;
		} box;
		struct {
			SparkScalar radius;
		} sphere;
	} data;
} *SparkCollider;

/* Input handling declarations */
typedef struct SparkInputT {
	SparkBool keys[1024];
	SparkBool mouseButtons[32];
	SparkScalar mousex;
	SparkScalar mousey;
} *SparkInput;

typedef struct SparkAudioBufferT {
	SparkU32 bufferid;        // OpenAL buffer identifier
	SparkI32 format;          // Audio data format (e.g., AL_FORMAT_MONO16)
	SparkFrequency frequency; // Sampling frequency (e.g., 44100 Hz)
	SparkSize size;           // Size of the audio data in bytes
	SparkHandle data;
} *SparkAudioBuffer;

typedef struct SparkAudioT {
	SparkU32 sourceid;       // OpenAL source identifier
	SparkVec3 position;      // Source position in 3D space
	SparkVec3 velocity;      // Source velocity in 3D space
	SparkVec3 direction;     // Source direction vector
	SparkBool looping;       // Looping flag (AL_TRUE or AL_FALSE)
	SparkF32 gain;           // Volume gain (default is 1.0)
	SparkF32 pitch;          // Pitch shift (default is 1.0)
	SparkAudioBuffer buffer; // Associated audio buffer
} *SparkAudio;

typedef struct SparkVertexT {
	SparkVec3 position;
	SparkVec3 normal;
	SparkVec2 texcoord;
} SparkVertex;

typedef struct SparkStaticMeshT {
	SparkVertex* vertices;
	SparkU32* indices;
	SparkU32 vertex_count;
	SparkU32 index_count;
	struct VulkanMemoryAllocationT* vertex_buffer;
	struct VulkanMemoryAllocationT* index_buffer;
} *SparkStaticMesh;

typedef struct SparkDynamicMeshT {
	SparkVertex* vertices;
	SparkU32* indices;
	SparkU32 vertex_count;
	SparkU32 index_count;
	struct VulkanMemoryAllocationT* vertex_buffer;
	struct VulkanMemoryAllocationT* index_buffer;
} *SparkDynamicMesh;

typedef struct SparkMaterialT {
	struct SparkGraphicsPipelineConfigT* pipeline_config;
	SparkTexture texture;
	SparkVec4 color;
} *SparkMaterial;

typedef struct SparkStaticModelT {
	SparkStaticMesh mesh;
	SparkMaterial material;
} *SparkStaticModel;

typedef struct SparkDynamicModelT {
	SparkDynamicMesh mesh;
	SparkMaterial material;
} *SparkDynamicModel;

/* Animation declarations */
typedef struct SparkAnimationT {
	SparkI8 unimplemented;
} *SparkAnimation;

/* GUI declarations */
typedef struct SparkGuiElementT* SparkGuiElement;
typedef struct SparkGuiStyleT* SparkGuiStyle;

typedef struct SparkAIBehaviorT {
	SparkU8 not_implemented;
} *SparkAIBehavior;

/* Particle system declarations */
typedef struct SparkParticleEmitterT* SparkParticleEmitter;

/* Font and text rendering declarations */
typedef struct SparkFontT* SparkFont;
typedef struct SparkTextT {
	SparkConstString content;
	SparkFont font;
	SparkScalar size;
	SparkColor color;
	SparkVec2 position;
} SparkText;

/* Packet Structure */
typedef struct SparkPacketT {
	SparkSize size;
	SparkBuffer data;
} SparkPacket;

/* Envelope Structure */
typedef struct SparkEnvelopeT {
	SparkEnvelopeType type;
	SparkPacket packet;
} SparkEnvelope;

/* Forward declarations */
typedef struct SparkServerT* SparkServer;
typedef struct SparkClientT* SparkClient;
typedef struct SparkClientConnectionT* SparkClientConnection;

typedef struct SparkFileDeserializerT {
	SparkU8* data;
	SparkU64 size;
	SparkU64 capacity;
	SparkConstString path;
	SparkU64 curr_off;
	FILE* file;
} *SparkFileDeserializer;

typedef struct SparkFileSerializerT {
	SparkU8* data;
	SparkU64 size;
	SparkU64 capacity;
	SparkConstString path;
	FILE* file;
} *SparkFileSerializer;

typedef struct SparkGraphicsPipelineConfigT {
	struct SparkApplicationT* application;
	SparkShader vertex_shader;
	SparkShader fragment_shader;
	SparkShader compute_shader;
	SparkShader geometry_shader;
	SparkShader tess_control_shader;
	SparkShader tess_evaluation_shader;
	struct VkPipelineLayout_T* pipeline_layout;
	struct VkPipeline_T* pipeline;
	struct VkRenderPass_T* render_pass;
	SparkU32 patch_control_points;              // For tessellation
	SparkBool owns_pipeline_layout;
} *SparkGraphicsPipelineConfig;

typedef struct SparkWindowT {
	SparkWindowData window_data;
	SparkBool should_close;
#ifdef SPARK_IMPLEMENTATION
	struct GLFWwindow* window;
	struct VkInstance_T* instance;
	struct VkDebugUtilsMessengerEXT_T* debug_messenger;
	struct VkPhysicalDevice_T* physical_device;
	struct VkDevice_T* device;
	struct VkQueue_T* graphics_queue;
	struct VkQueue_T* present_queue;
	struct VkSufraceKHR_T* surface;
	struct VkSwapchainKHR_T* swap_chain;
	struct VkImage_T** swap_chain_images;
	struct VkImageView_T** swap_chain_image_views;
	struct VkExtent2D* swap_chain_extent;
	struct VkFramebuffer_T** swap_chain_framebuffers;
	struct VkDescriptorSetLayout_T* descriptor_set_layout;
	struct VkRenderPass_T* render_pass;
	struct VkCommandPool_T* command_pool;
	struct VkCommandBuffer_T** command_buffers;
	struct VkSemaphore_T** image_available_semaphores;
	struct VkSemaphore_T** render_finished_semaphores;
	struct VkFence_T** in_flight_fences;
	struct VkDescriptorPool_T* descriptor_pool;
	struct VkBuffer_T** uniform_buffers;
	struct VkDeviceMemory_T** uniform_buffers_memory;
	struct VkDescriptorSet_T** descriptor_sets;
	SparkHandle* uniform_buffers_mapped;
	enum VkFormat swap_chain_image_format;
	SparkU32 current_frame;
	SparkU32 swap_chain_images_size;
	SparkU32 swap_chain_image_views_size;
	SparkU32 command_buffers_size;
	SparkU32 image_available_semaphores_size;
	SparkU32 render_finished_semaphores_size;
	SparkU32 in_flight_fences_size;
	SparkU32 uniform_buffers_size;
	SparkU32 uniform_buffers_memory_size;
	SparkU32 uniform_buffers_mapped_size;
	SparkBool framebuffer_resized;
#endif
} *SparkWindow;

typedef struct SparkApplicationT {
	SparkWindow window;
	SparkEcs ecs;
	SparkHashMap resource_manager;
	SparkEventHandler event_handler;
	SparkVector start_functions;         // Vector<SparkStartHandlerFunction>
	SparkVector update_functions;        // Vector<SparkUpdateHandlerFunction>
	SparkVector stop_functions;          // Vector<SparkStopHandlerFunction>
	SparkVector event_functions;         // Vector<SparkEventHandlerFunction>
	SparkVector query_functions;         // Vector<SparkQueryHandlerFunction>
	SparkHashMap query_event_functions;  // HashMap<SparkEventType, SparkVector<SparkQueryEventHandlerFunction>>
	SparkThreadPool thread_pool;
	SparkMutex mutex;
	SparkF32 delta_time;
	SparkBool should_close;
	SparkBool closing;
} *SparkApplication;

#endif