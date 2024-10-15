#ifndef __SPARK_H__
#define __SPARK_H__

#include <assert.h>

#if defined(_WIN32) && defined(_GLFW_BUILD_DLL)
/* We are building SPARKAPI as a Win32 DLL */
#define SPARKAPI __declspec(dllexport)
#elif defined(_WIN32) && defined(GLFW_DLL)
/* We are calling a SPARKAPI Win32 DLL */
#define SPARKAPI __declspec(dllimport)
#elif defined(__GNUC__) && defined(_GLFW_BUILD_DLL)
/* We are building SPARKAPI as a Unix shared library */
#define SPARKAPI __attribute__((visibility("default")))
#else
#define SPARKAPI
#endif

#define SPARK_VERSION_MAJOR 1
#define SPARK_VERSION_MINOR 0
#define SPARK_VERSION_PATCH 0

#define SPARK_MAKE_VERSION(major, minor, patch) \
	((major << 22) | (minor << 12) | patch)

#define SPARK_VERSION SPARK_MAKE_VERSION(SPARK_VERSION_MAJOR, SPARK_VERSION_MINOR, SPARK_VERSION_PATCH)

#define SPARK_IS_VERSION(version) (version == SPARK_VERSION)
#define SPARK_IS_VERSION_OR_GREATER(version) (version >= SPARK_VERSION)
#define SPARK_IS_VERSION_OR_LOWER(version) (version <= SPARK_VERSION)

#define SPARK_MAKE_VERSION_STRING(major, minor, patch) \
	#major "." #minor "." #patch

#define SPARK_VERSION_STRING SPARK_MAKE_VERSION_STRING(SPARK_VERSION_MAJOR, SPARK_VERSION_MINOR, SPARK_VERSION_PATCH)

#if !defined(SPARK_NO_DEBUG) && !defined(NDEBUG) && !defined(RELEASE)
#define SPARK_LOG_DEBUG(message, ...) SparkLog(SPARK_LOG_LEVEL_DEBUG, message, ##__VA_ARGS__)
#else
	#define SPARK_LOG_DEBUG(message, ...)
#endif
#ifndef SPARK_NO_INFO
	#define SPARK_LOG_INFO(message, ...) SparkLog(SPARK_LOG_LEVEL_INFO, message, ##__VA_ARGS__)
#else
	#define SPARK_LOG_INFO(message, ...)
#endif
#ifndef SPARK_NO_WARN
	#define SPARK_LOG_WARN(message, ...) SparkLog(SPARK_LOG_LEVEL_WARN, message, ##__VA_ARGS__)
#else
	#define SPARK_LOG_WARN(message, ...)
#endif
#ifndef SPARK_NO_ERROR
	#define SPARK_LOG_ERROR(message, ...) SparkLog(SPARK_LOG_LEVEL_ERROR, message, ##__VA_ARGS__)
#else
	#define SPARK_LOG_ERROR(message, ...)
#endif

/* Capabilities */
#define SPARK_DEPTH_TEST    0x0B71
#define SPARK_BLEND         0x0BE2
#define SPARK_CULL_FACE     0x0B44
#define SPARK_SCISSOR_TEST  0x0C11

/* Clear mask bits */
#define SPARK_COLOR_BUFFER_BIT   0x00004000
#define SPARK_DEPTH_BUFFER_BIT   0x00000100
#define SPARK_STENCIL_BUFFER_BIT 0x00000400

/*#ifdef __cplusplus
extern "C" {
#endif
*/

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
	SPARK_KEY_SEMICOLON = 59,  /* ; */
	SPARK_KEY_EQUAL = 61,      /* = */
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

/* Event types */
typedef enum SparkEventTypeT {
	SPARK_EVENT_NONE = 0,
	SPARK_EVENT_WINDOW_CLOSE,
	SPARK_EVENT_WINDOW_RESIZE,
	SPARK_EVENT_WINDOW_FOCUS,
	SPARK_EVENT_WINDOW_LOST_FOCUS,
	SPARK_EVENT_WINDOW_MOVED,
	SPARK_EVENT_KEY_PRESSED,
	SPARK_EVENT_KEY_RELEASED,
	SPARK_EVENT_KEY_TYPED,
	SPARK_EVENT_MOUSE_BUTTON_PRESSED,
	SPARK_EVENT_MOUSE_BUTTON_RELEASED,
	SPARK_EVENT_MOUSE_MOVED,
	SPARK_EVENT_MOUSE_SCROLLED
} SparkEventType;

/* Shader types */
typedef enum SparkShaderTypeT {
	SPARK_SHADER_VERTEX = 0,
	SPARK_SHADER_FRAGMENT,
	SPARK_SHADER_GEOMETRY,
	SPARK_SHADER_TESSELLATION_CONTROL,
	SPARK_SHADER_TESSELLATION_EVALUATION,
	SPARK_SHADER_COMPUTE
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
	SPARK_TEXTURE_FILTER_LINEAR,
	SPARK_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST,
	SPARK_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST,
	SPARK_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR,
	SPARK_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR
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


/* Shader data types */
typedef enum SparkShaderDataTypeT {
	SPARK_SHADER_DATA_TYPE_FLOAT,
	SPARK_SHADER_DATA_TYPE_VEC2,
	SPARK_SHADER_DATA_TYPE_VEC3,
	SPARK_SHADER_DATA_TYPE_VEC4,
	SPARK_SHADER_DATA_TYPE_INT,
	SPARK_SHADER_DATA_TYPE_IVEC2,
	SPARK_SHADER_DATA_TYPE_IVEC3,
	SPARK_SHADER_DATA_TYPE_IVEC4,
	SPARK_SHADER_DATA_TYPE_MAT2,
	SPARK_SHADER_DATA_TYPE_MAT3,
	SPARK_SHADER_DATA_TYPE_MAT4,
	SPARK_SHADER_DATA_TYPE_SAMPLER2D
} SparkShaderDataType;

typedef SparkF32 SparkScalar;
typedef SparkI32 SparkIScalar;

/* Forward declaration of Ecs */
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
	SparkScalar m00, m01, m02, m03;
	SparkScalar m10, m11, m12, m13;
	SparkScalar m20, m21, m22, m23;
	SparkScalar m30, m31, m32, m33;
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
typedef SparkHandle(*SparkReallocateFunction)(SparkHandle handle, SparkSize size);
typedef SparkVoid(*SparkFreeFunction)(SparkHandle handle);
typedef SparkSize(*SparkHashFunction)(SparkConstBuffer buf, SparkSize length);
typedef SparkResult(*SparkSystemStartFunction)(struct SparkEcsT* ecs);
typedef SparkResult(*SparkSystemUpdateFunction)(struct SparkEcsT* ecs, SparkF32 delta);
typedef SparkResult(*SparkSystemStopFunction)(struct SparkEcsT* ecs);
typedef SparkI32(*SparkCompareFunction)(SparkHandle a, SparkHandle b);

typedef struct SparkAllocatorT {
	SparkAllocateFunction allocate;
	SparkReallocateFunction reallocate;
	SparkFreeFunction free;
} *SparkAllocator;

typedef struct SparkVectorT {
	SparkSize size;
	SparkSize capacity;
	/* Destructor to be called on each element */
	SparkFreeFunction destructor;
	SparkHandle* elements;
	SparkAllocator allocator;
	SparkBool external_allocator;
} *SparkVector;

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
	SparkBool external_allocator;
} *SparkList;

typedef struct SparkHashMapNodeT {
	SparkHandle key;
	SparkHandle value;
	SparkSize key_size;
	SparkSize hash;
} *SparkHashMapNode;

typedef struct SparkHashMapT {
	SparkSize size;
	SparkSize capacity;
	SparkList* buckets;
	/* Destructor to be called on each key and value */
	SparkFreeFunction key_destructor;
	SparkFreeFunction value_destructor;
	SparkHashFunction hash;
	SparkAllocator allocator;
	SparkBool external_allocator;
} *SparkHashMap;

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
	SparkBool external_allocator;
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
	SparkBool external_allocator;
} *SparkHashSet;

typedef struct SparkQueueT {
	SparkAllocator allocator;
	SparkSize capacity;
	SparkSize size;
	SparkSize front;
	SparkSize rear;
	SparkFreeFunction destructor;
	SparkHandle* elements;
	SparkBool external_allocator;
} *SparkQueue;

typedef struct SparkStackT {
	SparkAllocator allocator;
	SparkSize capacity;
	SparkSize size;
	SparkFreeFunction destructor;
	SparkHandle* elements;
	SparkBool external_allocator;
} *SparkStack;

typedef struct SparkEventHandlerT {
	SparkI8 not_implemented;
} *SparkEventHandler;

typedef SparkI32 SparkEntity;
/* HashMap <SparkString, SparkComponent> */
typedef SparkHashMap SparkComponentArray;

typedef struct SparkComponentT {
	/* Parent entity of this component
	 * Component data needs to be composed inside other structures
	 * and also the first element in that struct
	 */
	SparkEntity entity;
	SparkConstString type;
	SparkConstString name;
} *SparkComponent;

typedef struct SparkSystemT {
	SparkSystemStartFunction start;
	SparkSystemUpdateFunction update;
	SparkSystemStopFunction stop;
	SparkEventHandler event_handler;
} *SparkSystem;

typedef struct SparkEcsT {
	/* Vector <SparkEntity> */
	SparkVector entities;
	/* Vector <SparkSystem> */
	SparkVector systems;
	/* HashMap <SparkString, SparkComponentArray> */
	SparkHashMap components;
	/* Stack <SparkI32> */
	SparkStack recycled_ids;
	SparkEventHandler event_handler;
} *SparkEcs;

typedef struct SparkResourceT {
	SparkConstString name;
	SparkConstString type;
	SparkHandle data;
} *SparkResource;

typedef struct SparkResourceLoaderT {
	SparkConstString type;
	SparkHandle(*load)(SparkConstString path);
	SparkResult(*unload)(SparkHandle handle);
} *SparkResourceLoader;

typedef struct SparkResourceRegistryT {
	/* HashMap <SparkString, SparkResourceLoader> */
	SparkHashMap loaders;
	/* HashMap <SparkString, SparkResource> */
	SparkHashMap resources;
} *SparkResourceRegistry;

typedef struct SparkWindowDataT {
	SparkConstString title;
	SparkI32 width;
	SparkI32 height;
	SparkBool vsync;
} *SparkWindowData;

typedef struct SparkRendererT {
	SparkI8 not_implemented;
} *SparkRenderer;

typedef struct SparkWindowT {
	SparkWindowData window_data;
	SparkRenderer renderer;
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
	struct VkPipelineLayout_T* pipeline_layout;
	struct VkRenderPass_T* render_pass;
	struct VkPipeline_T* graphics_pipeline;
	struct VkCommandPool_T* command_pool;
	struct VkCommandBuffer_T* command_buffer;
	struct VkSemaphore_T* image_available_semaphore;
	struct VkSemaphore_T* render_finished_semaphore;
	struct VkFence_T* in_flight_fence;
	enum VkFormat swap_chain_image_format;
	SparkU32 swap_chain_images_size;
	SparkU32 swap_chain_image_views_size;
} *SparkWindow;

typedef struct SparkApplicationT {
	SparkWindow window;
	SparkEcs ecs;
	SparkResourceRegistry resource_registry;
	SparkF32 delta_time;
} *SparkApplication;

SPARKAPI SparkConstString SparkTypeToString(SparkType type);
SPARKAPI SparkType SparkStringToType(SparkConstString string);
SPARKAPI SparkConstString SparkErrorToString(SparkError error);
SPARKAPI SparkError SparkStringToError(SparkConstString string);
SPARKAPI SparkConstString SparkResultToString(SparkResult result);
SPARKAPI SparkResult SparkStringToResult(SparkConstString string);
SPARKAPI SparkConstString SparkAccessToString(SparkAccess access);
SPARKAPI SparkAccess SparkStringToAccess(SparkConstString string);
SPARKAPI SparkConstString SparkMouseButtonToString(SparkMouseButton button);
SPARKAPI SparkMouseButton SparkStringToMouseButton(SparkConstString string);
SPARKAPI SparkConstString SparkKeyToString(SparkKey key);
SPARKAPI SparkKey SparkStringToKey(SparkConstString string);
SPARKAPI SparkConstString SparkModifierToString(SparkModifier modifier);
SPARKAPI SparkModifier SparkStringToModifier(SparkConstString string);
SPARKAPI SparkConstString SparkActionToString(SparkAction action);
SPARKAPI SparkAction SparkStringToAction(SparkConstString string);
SPARKAPI SparkConstString SparkCursorToString(SparkCursor cursor);
SPARKAPI SparkCursor SparkStringToCursor(SparkConstString string);
SPARKAPI SparkConstString SparkEventTypeToString(SparkEventType eventType);
SPARKAPI SparkEventType SparkStringToEventType(SparkConstString string);
SPARKAPI SparkConstString SparkShaderTypeToString(SparkShaderType shaderType);
SPARKAPI SparkShaderType SparkStringToShaderType(SparkConstString string);
SPARKAPI SparkConstString SparkPrimitiveTypeToString(SparkPrimitiveType primitiveType);
SPARKAPI SparkPrimitiveType SparkStringToPrimitiveType(SparkConstString string);
SPARKAPI SparkConstString SparkBlendModeToString(SparkBlendMode blendMode);
SPARKAPI SparkBlendMode SparkStringToBlendMode(SparkConstString string);
SPARKAPI SparkConstString SparkTextureFilterToString(SparkTextureFilter filter);
SPARKAPI SparkTextureFilter SparkStringToTextureFilter(SparkConstString string);
SPARKAPI SparkConstString SparkLogLevelToString(SparkLogLevel level);
SPARKAPI SparkLogLevel SparkStringToLogLevel(SparkConstString string);
SPARKAPI SparkConstString SparkRenderAPIToString(SparkRenderAPI api);
SPARKAPI SparkRenderAPI SparkStringToRenderAPI(SparkConstString string);

SPARKAPI SparkConstString FormatString(SparkConstString format, ...);

SPARKAPI SparkVoid SparkLog(SparkLogLevel log_level, SparkConstString format, ...);

/* Math stuff */

SPARKAPI SparkVec2 SparkVec2Add(SparkVec2 a, SparkVec2 b);
SPARKAPI SparkVec2 SparkVec2Subtract(SparkVec2 a, SparkVec2 b);
SPARKAPI SparkVec2 SparkVec2Multiply(SparkVec2 a, SparkVec2 b);
SPARKAPI SparkVec2 SparkVec2Divide(SparkVec2 a, SparkVec2 b);
SPARKAPI SparkVec2 SparkVec2Scale(SparkVec2 a, SparkScalar s);
SPARKAPI SparkScalar SparkVec2Dot(SparkVec2 a, SparkVec2 b);
SPARKAPI SparkScalar SparkVec2Length(SparkVec2 a);
SPARKAPI SparkVec2 SparkVec2Normalize(SparkVec2 a);
SPARKAPI SparkScalar SparkVec2Distance(SparkVec2 a, SparkVec2 b);
SPARKAPI SparkVec2 SparkVec2Negate(SparkVec2 a);
SPARKAPI SparkScalar SparkVec2Angle(SparkVec2 a, SparkVec2 b);
SPARKAPI SparkVec2 SparkVec2Reflect(SparkVec2 v, SparkVec2 n);
SPARKAPI SparkVec2 SparkVec2Lerp(SparkVec2 a, SparkVec2 b, SparkScalar t);

SPARKAPI SparkVec3 SparkVec3Add(SparkVec3 a, SparkVec3 b);
SPARKAPI SparkVec3 SparkVec3Subtract(SparkVec3 a, SparkVec3 b);
SPARKAPI SparkVec3 SparkVec3Multiply(SparkVec3 a, SparkVec3 b);
SPARKAPI SparkVec3 SparkVec3Divide(SparkVec3 a, SparkVec3 b);
SPARKAPI SparkVec3 SparkVec3Scale(SparkVec3 a, SparkScalar s);
SPARKAPI SparkScalar SparkVec3Dot(SparkVec3 a, SparkVec3 b);
SPARKAPI SparkVec3 SparkVec3Cross(SparkVec3 a, SparkVec3 b);
SPARKAPI SparkScalar SparkVec3Length(SparkVec3 a);
SPARKAPI SparkVec3 SparkVec3Normalize(SparkVec3 a);
SPARKAPI SparkScalar SparkVec3Distance(SparkVec3 a, SparkVec3 b);
SPARKAPI SparkVec3 SparkVec3Negate(SparkVec3 a);
SPARKAPI SparkScalar SparkVec3Angle(SparkVec3 a, SparkVec3 b);
SPARKAPI SparkVec3 SparkVec3Reflect(SparkVec3 v, SparkVec3 n);
SPARKAPI SparkVec3 SparkVec3Lerp(SparkVec3 a, SparkVec3 b, SparkScalar t);

SPARKAPI SparkVec4 SparkVec4Add(SparkVec4 a, SparkVec4 b);
SPARKAPI SparkVec4 SparkVec4Subtract(SparkVec4 a, SparkVec4 b);
SPARKAPI SparkVec4 SparkVec4Multiply(SparkVec4 a, SparkVec4 b);
SPARKAPI SparkVec4 SparkVec4Divide(SparkVec4 a, SparkVec4 b);
SPARKAPI SparkVec4 SparkVec4Scale(SparkVec4 a, SparkScalar s);
SPARKAPI SparkScalar SparkVec4Dot(SparkVec4 a, SparkVec4 b);
SPARKAPI SparkScalar SparkVec4Length(SparkVec4 a);
SPARKAPI SparkVec4 SparkVec4Normalize(SparkVec4 a);
SPARKAPI SparkScalar SparkVec4Distance(SparkVec4 a, SparkVec4 b);
SPARKAPI SparkVec4 SparkVec4Negate(SparkVec4 a);
SPARKAPI SparkVec4 SparkVec4Lerp(SparkVec4 a, SparkVec4 b, SparkScalar t);

SPARKAPI SparkMat2 SparkMat2Add(SparkMat2 a, SparkMat2 b);
SPARKAPI SparkMat2 SparkMat2Subtract(SparkMat2 a, SparkMat2 b);
SPARKAPI SparkMat2 SparkMat2Multiply(SparkMat2 a, SparkMat2 b);
SPARKAPI SparkMat2 SparkMat2Scale(SparkMat2 a, SparkScalar s);
SPARKAPI SparkMat2 SparkMat2Transpose(SparkMat2 m);
SPARKAPI SparkScalar SparkMat2Determinant(SparkMat2 m);
SPARKAPI SparkMat2 SparkMat2Inverse(SparkMat2 m);
SPARKAPI SparkMat2 SparkMat2Identity();

SPARKAPI SparkMat3 SparkMat3Add(SparkMat3 a, SparkMat3 b);
SPARKAPI SparkMat3 SparkMat3Subtract(SparkMat3 a, SparkMat3 b);
SPARKAPI SparkMat3 SparkMat3Multiply(SparkMat3 a, SparkMat3 b);
SPARKAPI SparkMat3 SparkMat3Scale(SparkMat3 a, SparkScalar s);
SPARKAPI SparkMat3 SparkMat3Transpose(SparkMat3 m);
SPARKAPI SparkScalar SparkMat3Determinant(SparkMat3 m);
SPARKAPI SparkMat3 SparkMat3Inverse(SparkMat3 m);
SPARKAPI SparkMat3 SparkMat3Identity();

SPARKAPI SparkMat4 SparkMat4Add(SparkMat4 a, SparkMat4 b);
SPARKAPI SparkMat4 SparkMat4Subtract(SparkMat4 a, SparkMat4 b);
SPARKAPI SparkMat4 SparkMat4Multiply(SparkMat4 a, SparkMat4 b);
SPARKAPI SparkMat4 SparkMat4Scale(SparkMat4 a, SparkScalar s);
SPARKAPI SparkMat4 SparkMat4Transpose(SparkMat4 m);
SPARKAPI SparkScalar SparkMat4Determinant(SparkMat4 m);
SPARKAPI SparkMat4 SparkMat4Inverse(SparkMat4 m);
SPARKAPI SparkMat4 SparkMat4Identity();
SPARKAPI SparkMat4 SparkMat4Translate(SparkVec3 translation);
SPARKAPI SparkMat4 SparkMat4ScaleVec3(SparkVec3 scale);
SPARKAPI SparkMat4 SparkMat4ScaleScalar(SparkScalar scale);
SPARKAPI SparkMat4 SparkMat4Rotate(SparkScalar angle, SparkVec3 axis);
SPARKAPI SparkMat4 SparkMat4RotateX(SparkScalar angle);
SPARKAPI SparkMat4 SparkMat4RotateY(SparkScalar angle);
SPARKAPI SparkMat4 SparkMat4RotateZ(SparkScalar angle);
SPARKAPI SparkMat4 SparkMat4LookAt(SparkVec3 eye, SparkVec3 center, SparkVec3 up);
SPARKAPI SparkMat4 SparkMat4Perspective(SparkScalar fovy, SparkScalar aspect, SparkScalar near, SparkScalar far);
SPARKAPI SparkMat4 SparkMat4Ortho(SparkScalar left, SparkScalar right, SparkScalar bottom, SparkScalar top, SparkScalar near, SparkScalar far);

SPARKAPI SparkVec3 SparkVec3Transform(SparkVec3 v, SparkMat4 m);
SPARKAPI SparkVec4 SparkVec4Transform(SparkVec4 v, SparkMat4 m);

SPARKAPI SparkQuat SparkQuatMultiply(SparkQuat a, SparkQuat b);
SPARKAPI SparkQuat SparkQuatConjugate(SparkQuat q);
SPARKAPI SparkQuat SparkQuatInverse(SparkQuat q);
SPARKAPI SparkQuat SparkQuatNormalize(SparkQuat q);
SPARKAPI SparkQuat SparkQuatFromAxisAngle(SparkVec3 axis, SparkScalar angle);
SPARKAPI SparkVoid SparkQuatToAxisAngle(SparkQuat q, SparkVec3* axis, SparkScalar* angle);
SPARKAPI SparkMat4 SparkQuatToMat4(SparkQuat q);
SPARKAPI SparkQuat SparkQuatSlerp(SparkQuat a, SparkQuat b, SparkScalar t);

SPARKAPI SparkScalar SparkRadians(SparkScalar degrees);
SPARKAPI SparkScalar SparkDegrees(SparkScalar radians);

SPARKAPI SparkScalar SparkSin(SparkScalar angle);
SPARKAPI SparkScalar SparkCos(SparkScalar angle);
SPARKAPI SparkScalar SparkTan(SparkScalar angle);
SPARKAPI SparkScalar SparkASin(SparkScalar value);
SPARKAPI SparkScalar SparkACos(SparkScalar value);
SPARKAPI SparkScalar SparkATan(SparkScalar value);
SPARKAPI SparkScalar SparkATan2(SparkScalar y, SparkScalar x);

SPARKAPI SparkScalar SparkSqrt(SparkScalar value);
SPARKAPI SparkScalar SparkPow(SparkScalar base, SparkScalar exponent);
SPARKAPI SparkScalar SparkExp(SparkScalar exponent);
SPARKAPI SparkScalar SparkLogs(SparkScalar value);
SPARKAPI SparkScalar SparkAbs(SparkScalar value);
SPARKAPI SparkScalar SparkFloor(SparkScalar value);
SPARKAPI SparkScalar SparkCeil(SparkScalar value);
SPARKAPI SparkScalar SparkClamp(SparkScalar value, SparkScalar min, SparkScalar max);
SPARKAPI SparkScalar SparkMix(SparkScalar a, SparkScalar b, SparkScalar t);

/* General math function declarations */

SPARKAPI SparkScalar SparkMin(SparkScalar a, SparkScalar b);
SPARKAPI SparkScalar SparkMax(SparkScalar a, SparkScalar b);
SPARKAPI SparkScalar SparkClamp(SparkScalar x, SparkScalar min_val, SparkScalar max_val);
SPARKAPI SparkScalar SparkMix(SparkScalar x, SparkScalar y, SparkScalar t);
SPARKAPI SparkScalar SparkStep(SparkScalar edge, SparkScalar x);
SPARKAPI SparkScalar SparkSmoothStep(SparkScalar edge0, SparkScalar edge1, SparkScalar x);
SPARKAPI SparkScalar SparkSign(SparkScalar x);
SPARKAPI SparkScalar SparkMod(SparkScalar x, SparkScalar y);

/* Vector and matrix type conversion functions */

SPARKAPI SparkVec3 SparkVec2ToVec3(SparkVec2 v, SparkScalar z);
SPARKAPI SparkVec4 SparkVec3ToVec4(SparkVec3 v, SparkScalar w);
SPARKAPI SparkVec2 SparkVec3ToVec2(SparkVec3 v);
SPARKAPI SparkVec3 SparkVec4ToVec3(SparkVec4 v);

/* Functions between different vector and matrix types */

SPARKAPI SparkVec2 SparkMat2MultiplyVec2(SparkMat2 m, SparkVec2 v);
SPARKAPI SparkVec3 SparkMat3MultiplyVec3(SparkMat3 m, SparkVec3 v);
SPARKAPI SparkVec4 SparkMat4MultiplyVec4(SparkMat4 m, SparkVec4 v);
SPARKAPI SparkVec3 SparkMat4MultiplyVec3(SparkMat4 m, SparkVec3 v);

/* Updated math function declarations */

SPARKAPI SparkVec2 SparkVec2Add(SparkVec2 a, SparkVec2 b);
SPARKAPI SparkVec2 SparkVec2Subtract(SparkVec2 a, SparkVec2 b);
SPARKAPI SparkVec2 SparkVec2Multiply(SparkVec2 a, SparkVec2 b);
SPARKAPI SparkVec2 SparkVec2Divide(SparkVec2 a, SparkVec2 b);
SPARKAPI SparkVec2 SparkVec2Scale(SparkVec2 a, SparkScalar s);
SPARKAPI SparkScalar SparkVec2Dot(SparkVec2 a, SparkVec2 b);
SPARKAPI SparkScalar SparkVec2Length(SparkVec2 a);
SPARKAPI SparkVec2 SparkVec2Normalize(SparkVec2 a);
SPARKAPI SparkScalar SparkVec2Distance(SparkVec2 a, SparkVec2 b);
SPARKAPI SparkVec2 SparkVec2Negate(SparkVec2 a);
SPARKAPI SparkScalar SparkVec2Angle(SparkVec2 a, SparkVec2 b);
SPARKAPI SparkVec2 SparkVec2Reflect(SparkVec2 v, SparkVec2 n);
SPARKAPI SparkVec2 SparkVec2Lerp(SparkVec2 a, SparkVec2 b, SparkScalar t);

SPARKAPI SparkVec3 SparkVec3Add(SparkVec3 a, SparkVec3 b);
SPARKAPI SparkVec3 SparkVec3Subtract(SparkVec3 a, SparkVec3 b);
SPARKAPI SparkVec3 SparkVec3Multiply(SparkVec3 a, SparkVec3 b);
SPARKAPI SparkVec3 SparkVec3Divide(SparkVec3 a, SparkVec3 b);
SPARKAPI SparkVec3 SparkVec3Scale(SparkVec3 a, SparkScalar s);
SPARKAPI SparkScalar SparkVec3Dot(SparkVec3 a, SparkVec3 b);
SPARKAPI SparkVec3 SparkVec3Cross(SparkVec3 a, SparkVec3 b);
SPARKAPI SparkScalar SparkVec3Length(SparkVec3 a);
SPARKAPI SparkVec3 SparkVec3Normalize(SparkVec3 a);
SPARKAPI SparkScalar SparkVec3Distance(SparkVec3 a, SparkVec3 b);
SPARKAPI SparkVec3 SparkVec3Negate(SparkVec3 a);
SPARKAPI SparkScalar SparkVec3Angle(SparkVec3 a, SparkVec3 b);
SPARKAPI SparkVec3 SparkVec3Reflect(SparkVec3 v, SparkVec3 n);
SPARKAPI SparkVec3 SparkVec3Lerp(SparkVec3 a, SparkVec3 b, SparkScalar t);

SPARKAPI SparkVec4 SparkVec4Add(SparkVec4 a, SparkVec4 b);
SPARKAPI SparkVec4 SparkVec4Subtract(SparkVec4 a, SparkVec4 b);
SPARKAPI SparkVec4 SparkVec4Multiply(SparkVec4 a, SparkVec4 b);
SPARKAPI SparkVec4 SparkVec4Divide(SparkVec4 a, SparkVec4 b);
SPARKAPI SparkVec4 SparkVec4Scale(SparkVec4 a, SparkScalar s);
SPARKAPI SparkScalar SparkVec4Dot(SparkVec4 a, SparkVec4 b);
SPARKAPI SparkScalar SparkVec4Length(SparkVec4 a);
SPARKAPI SparkVec4 SparkVec4Normalize(SparkVec4 a);
SPARKAPI SparkScalar SparkVec4Distance(SparkVec4 a, SparkVec4 b);
SPARKAPI SparkVec4 SparkVec4Negate(SparkVec4 a);
SPARKAPI SparkVec4 SparkVec4Lerp(SparkVec4 a, SparkVec4 b, SparkScalar t);

/* Matrix functions */

SPARKAPI SparkMat2 SparkMat2Add(SparkMat2 a, SparkMat2 b);
SPARKAPI SparkMat2 SparkMat2Subtract(SparkMat2 a, SparkMat2 b);
SPARKAPI SparkMat2 SparkMat2Multiply(SparkMat2 a, SparkMat2 b);
SPARKAPI SparkMat2 SparkMat2Scale(SparkMat2 m, SparkScalar s);
SPARKAPI SparkMat2 SparkMat2Transpose(SparkMat2 m);
SPARKAPI SparkScalar SparkMat2Determinant(SparkMat2 m);
SPARKAPI SparkMat2 SparkMat2Inverse(SparkMat2 m);
SPARKAPI SparkMat2 SparkMat2Identity();

SPARKAPI SparkMat3 SparkMat3Add(SparkMat3 a, SparkMat3 b);
SPARKAPI SparkMat3 SparkMat3Subtract(SparkMat3 a, SparkMat3 b);
SPARKAPI SparkMat3 SparkMat3Multiply(SparkMat3 a, SparkMat3 b);
SPARKAPI SparkMat3 SparkMat3Scale(SparkMat3 m, SparkScalar s);
SPARKAPI SparkMat3 SparkMat3Transpose(SparkMat3 m);
SPARKAPI SparkScalar SparkMat3Determinant(SparkMat3 m);
SPARKAPI SparkMat3 SparkMat3Inverse(SparkMat3 m);
SPARKAPI SparkMat3 SparkMat3Identity();

SPARKAPI SparkMat4 SparkMat4Add(SparkMat4 a, SparkMat4 b);
SPARKAPI SparkMat4 SparkMat4Subtract(SparkMat4 a, SparkMat4 b);
SPARKAPI SparkMat4 SparkMat4Multiply(SparkMat4 a, SparkMat4 b);
SPARKAPI SparkMat4 SparkMat4Scale(SparkMat4 m, SparkScalar s);
SPARKAPI SparkMat4 SparkMat4Transpose(SparkMat4 m);
SPARKAPI SparkScalar SparkMat4Determinant(SparkMat4 m);
SPARKAPI SparkMat4 SparkMat4Inverse(SparkMat4 m);
SPARKAPI SparkMat4 SparkMat4Identity();
SPARKAPI SparkMat4 SparkMat4Translate(SparkVec3 translation);
SPARKAPI SparkMat4 SparkMat4ScaleVec3(SparkVec3 scale);
SPARKAPI SparkMat4 SparkMat4ScaleScalar(SparkScalar scale);
SPARKAPI SparkMat4 SparkMat4Rotate(SparkScalar angle, SparkVec3 axis);
SPARKAPI SparkMat4 SparkMat4RotateX(SparkScalar angle);
SPARKAPI SparkMat4 SparkMat4RotateY(SparkScalar angle);
SPARKAPI SparkMat4 SparkMat4RotateZ(SparkScalar angle);
SPARKAPI SparkMat4 SparkMat4LookAt(SparkVec3 eye, SparkVec3 center, SparkVec3 up);
SPARKAPI SparkMat4 SparkMat4Perspective(SparkScalar fovy, SparkScalar aspect, SparkScalar near, SparkScalar far);
SPARKAPI SparkMat4 SparkMat4Ortho(SparkScalar left, SparkScalar right, SparkScalar bottom, SparkScalar top, SparkScalar near, SparkScalar far);

/* Quaternion functions */

SPARKAPI SparkQuat SparkQuatMultiply(SparkQuat a, SparkQuat b);
SPARKAPI SparkQuat SparkQuatConjugate(SparkQuat q);
SPARKAPI SparkQuat SparkQuatInverse(SparkQuat q);
SPARKAPI SparkQuat SparkQuatNormalize(SparkQuat q);
SPARKAPI SparkQuat SparkQuatFromAxisAngle(SparkVec3 axis, SparkScalar angle);
SPARKAPI SparkVoid SparkQuatToAxisAngle(SparkQuat q, SparkVec3* axis, SparkScalar* angle);
SPARKAPI SparkMat4 SparkQuatToMat4(SparkQuat q);
SPARKAPI SparkQuat SparkQuatSlerp(SparkQuat a, SparkQuat b, SparkScalar t);

/* Trigonometric functions */

SPARKAPI SparkScalar SparkRadians(SparkScalar degrees);
SPARKAPI SparkScalar SparkDegrees(SparkScalar radians);

SPARKAPI SparkScalar SparkSin(SparkScalar angle);
SPARKAPI SparkScalar SparkCos(SparkScalar angle);
SPARKAPI SparkScalar SparkTan(SparkScalar angle);
SPARKAPI SparkScalar SparkASin(SparkScalar value);
SPARKAPI SparkScalar SparkACos(SparkScalar value);
SPARKAPI SparkScalar SparkATan(SparkScalar value);
SPARKAPI SparkScalar SparkATan2(SparkScalar y, SparkScalar x);

/* Exponential and logarithmic functions */

SPARKAPI SparkScalar SparkExp(SparkScalar exponent);
SPARKAPI SparkScalar SparkLog2(SparkScalar value);
SPARKAPI SparkScalar SparkPow(SparkScalar base, SparkScalar exponent);
SPARKAPI SparkScalar SparkSqrt(SparkScalar value);
SPARKAPI SparkScalar SparkInverseSqrt(SparkScalar value);

/* Common functions */

SPARKAPI SparkScalar SparkAbs(SparkScalar value);
SPARKAPI SparkScalar SparkFloor(SparkScalar value);
SPARKAPI SparkScalar SparkCeil(SparkScalar value);
SPARKAPI SparkScalar SparkFract(SparkScalar value);
SPARKAPI SparkScalar SparkMod(SparkScalar x, SparkScalar y);
SPARKAPI SparkScalar SparkMin(SparkScalar a, SparkScalar b);
SPARKAPI SparkScalar SparkMax(SparkScalar a, SparkScalar b);
SPARKAPI SparkScalar SparkClamp(SparkScalar x, SparkScalar min_val, SparkScalar max_val);
SPARKAPI SparkScalar SparkMix(SparkScalar x, SparkScalar y, SparkScalar a);
SPARKAPI SparkScalar SparkStep(SparkScalar edge, SparkScalar x);
SPARKAPI SparkScalar SparkSmoothStep(SparkScalar edge0, SparkScalar edge1, SparkScalar x);
SPARKAPI SparkScalar SparkSign(SparkScalar x);

/* Functions operating on vectors */

SPARKAPI SparkVec3 SparkCross(SparkVec3 a, SparkVec3 b);
SPARKAPI SparkScalar SparkDistance(SparkVec3 a, SparkVec3 b);
SPARKAPI SparkScalar SparkLength(SparkVec3 v);
SPARKAPI SparkVec3 SparkNormalize(SparkVec3 v);
SPARKAPI SparkScalar SparkDot(SparkVec3 a, SparkVec3 b);
SPARKAPI SparkVec3 SparkReflect(SparkVec3 v, SparkVec3 n);
SPARKAPI SparkVec3 SparkRefract(SparkVec3 v, SparkVec3 n, SparkScalar eta);

/* Component-wise vector operations */

SPARKAPI SparkVec2 SparkVec2Min(SparkVec2 a, SparkVec2 b);
SPARKAPI SparkVec2 SparkVec2Max(SparkVec2 a, SparkVec2 b);
SPARKAPI SparkVec2 SparkVec2Clamp(SparkVec2 v, SparkVec2 min_val, SparkVec2 max_val);
SPARKAPI SparkVec2 SparkVec2Mix(SparkVec2 a, SparkVec2 b, SparkScalar t);
SPARKAPI SparkVec2 SparkVec2Step(SparkVec2 edge, SparkVec2 x);
SPARKAPI SparkVec2 SparkVec2SmoothStep(SparkVec2 edge0, SparkVec2 edge1, SparkVec2 x);

SPARKAPI SparkVec3 SparkVec3Min(SparkVec3 a, SparkVec3 b);
SPARKAPI SparkVec3 SparkVec3Max(SparkVec3 a, SparkVec3 b);
SPARKAPI SparkVec3 SparkVec3Clamp(SparkVec3 v, SparkVec3 min_val, SparkVec3 max_val);
SPARKAPI SparkVec3 SparkVec3Mix(SparkVec3 a, SparkVec3 b, SparkScalar t);
SPARKAPI SparkVec3 SparkVec3Step(SparkVec3 edge, SparkVec3 x);
SPARKAPI SparkVec3 SparkVec3SmoothStep(SparkVec3 edge0, SparkVec3 edge1, SparkVec3 x);

SPARKAPI SparkVec4 SparkVec4Min(SparkVec4 a, SparkVec4 b);
SPARKAPI SparkVec4 SparkVec4Max(SparkVec4 a, SparkVec4 b);
SPARKAPI SparkVec4 SparkVec4Clamp(SparkVec4 v, SparkVec4 min_val, SparkVec4 max_val);
SPARKAPI SparkVec4 SparkVec4Mix(SparkVec4 a, SparkVec4 b, SparkScalar t);
SPARKAPI SparkVec4 SparkVec4Step(SparkVec4 edge, SparkVec4 x);
SPARKAPI SparkVec4 SparkVec4SmoothStep(SparkVec4 edge0, SparkVec4 edge1, SparkVec4 x);

/* Returns either a success or failure depending on the error code */
SPARKAPI SparkResult SparkCheckSuccess(SparkResult result);

/* Hash functions */

SPARKAPI SparkSize DJB2Hash(SparkConstBuffer buf, SparkSize size);
SPARKAPI SparkSize FNV1AHash(SparkConstBuffer buf, SparkSize size);
SPARKAPI SparkSize JenkinsHash(SparkConstBuffer buf, SparkSize size);
SPARKAPI SparkSize Murmur2Hash(SparkConstBuffer buf, SparkSize size);
SPARKAPI SparkSize SipHash(SparkConstBuffer buf, SparkSize size);
SPARKAPI SparkSize XXHash(SparkConstBuffer buf, SparkSize size);

SPARKAPI SparkHandle SparkAllocate(SparkSize size);
SPARKAPI SparkHandle SparkReallocate(SparkHandle handle, SparkSize size);
SPARKAPI SparkVoid SparkFree(SparkHandle handle);
SPARKAPI SparkAllocator SparkDefaultAllocator();
SPARKAPI SparkAllocator SparkCreateAllocator(SparkAllocateFunction allocate, SparkReallocateFunction reallocate, SparkFreeFunction free);
SPARKAPI SparkVoid SparkDestroyAllocator(SparkAllocator allocator);

SPARKAPI SparkVector SparkDefaultVector(); 
SPARKAPI SparkVector SparkCreateVector(SparkSize capacity, SparkAllocator allocator, SparkFreeFunction destructor);
SPARKAPI SparkVoid SparkDestroyVector(SparkVector vector);
SPARKAPI SparkHandle SparkGetElementVector(SparkVector vector, SparkIndex index);
SPARKAPI SparkResult SparkPushBackVector(SparkVector vector, SparkHandle element);
SPARKAPI SparkResult SparkPopBackVector(SparkVector vector);
SPARKAPI SparkResult SparkInsertVector(SparkVector vector, SparkIndex index, SparkHandle element);
SPARKAPI SparkResult SparkRemoveVector(SparkVector vector, SparkIndex index);
SPARKAPI SparkResult SparkSetVector(SparkVector vector, SparkIndex index, SparkHandle element);
SPARKAPI SparkResult SparkResizeVector(SparkVector vector, SparkSize capacity);
SPARKAPI SparkResult SparkClearVector(SparkVector vector);

SPARKAPI SparkList SparkDefaultList(); 
SPARKAPI SparkList SparkCreateList(SparkAllocator allocator, SparkFreeFunction destructor);
SPARKAPI SparkVoid SparkDestroyList(SparkList list);
SPARKAPI SparkHandle SparkGetElementList(SparkList list, SparkIndex index);
SPARKAPI SparkResult SparkPushBackList(SparkList list, SparkHandle element);
SPARKAPI SparkResult SparkPopBackList(SparkList list, SparkBuffer element);
SPARKAPI SparkResult SparkInsertList(SparkList list, SparkIndex index, SparkHandle element);
SPARKAPI SparkResult SparkRemoveList(SparkList list, SparkIndex index);
SPARKAPI SparkResult SparkSetList(SparkList list, SparkIndex index, SparkHandle element);
SPARKAPI SparkResult SparkClearList(SparkList list);

SPARKAPI SparkMap SparkDefaultMap();
SPARKAPI SparkMap SparkCreateMap(SparkAllocator allocator);
SPARKAPI SparkVoid SparkDestroyMap(SparkMap map);
SPARKAPI SparkHandle SparkGetElementMap(SparkMap map, SparkConstBuffer key);
SPARKAPI SparkResult SparkInsertMap(SparkMap map, SparkConstBuffer key, SparkConstBuffer value);
SPARKAPI SparkResult SparkRemoveMap(SparkMap map, SparkConstBuffer key);
SPARKAPI SparkResult SparkSetMap(SparkMap map, SparkConstBuffer key, SparkConstBuffer value);
SPARKAPI SparkResult SparkClearMap(SparkMap map);

SPARKAPI SparkHashMap SparkDefaultHashMap();
SPARKAPI SparkHashMap SparkCreateHashMap(SparkSize capacity, SparkHashFunction hash, SparkAllocator allocator, SparkFreeFunction key_destructor, SparkFreeFunction value_destructor);
SPARKAPI SparkVoid SparkDestroyHashMap(SparkHashMap hashmap);
SPARKAPI SparkHandle SparkGetElementHashMap(SparkHashMap hashmap, SparkHandle key, SparkSize key_size);
SPARKAPI SparkResult SparkInsertHashMap(SparkHashMap hashmap, SparkHandle key, SparkSize key_size, SparkHandle value);
SPARKAPI SparkResult SparkRemoveHashMap(SparkHashMap hashmap, SparkHandle key, SparkSize key_size);
SPARKAPI SparkResult SparkClearHashMap(SparkHashMap hashmap);

SPARKAPI SparkSet SparkDefaultSet();
SPARKAPI SparkSet SparkCreateSet(SparkSize capacity, SparkAllocator allocator, SparkFreeFunction destructor);
SPARKAPI SparkVoid SparkDestroySet(SparkSet set);
SPARKAPI SparkHandle SparkGetElementSet(SparkSet set, SparkSize index);
SPARKAPI SparkBool SparkContainsSet(SparkSet set, SparkHandle element, SparkCompareFunction compare);
SPARKAPI SparkResult SparkInsertSet(SparkSet set, SparkHandle element, SparkCompareFunction compare);
SPARKAPI SparkResult SparkRemoveSet(SparkSet set, SparkHandle element, SparkCompareFunction compare);
SPARKAPI SparkResult SparkClearSet(SparkSet set);

SPARKAPI SparkHashSet SparkDefaultHashSet();
SPARKAPI SparkHashSet SparkCreateHashSet(SparkSize capacity, SparkSize element_size, SparkHashFunction hash, SparkAllocator allocator, SparkFreeFunction destructor);
SPARKAPI SparkVoid SparkDestroyHashSet(SparkHashSet hashset);
SPARKAPI SparkBool SparkContainsHashSet(SparkHashSet hashset, SparkHandle element, SparkSize element_size);
SPARKAPI SparkResult SparkInsertHashSet(SparkHashSet hashset, SparkHandle element, SparkSize element_size);
SPARKAPI SparkResult SparkRemoveHashSet(SparkHashSet hashset, SparkHandle element, SparkSize element_size);
SPARKAPI SparkResult SparkClearHashSet(SparkHashSet hashset);

SPARKAPI SparkQueue SparkDefaultQueue();
SPARKAPI SparkQueue SparkCreateQueue(SparkSize capacity, SparkAllocator allocator, SparkFreeFunction destructor);
SPARKAPI SparkVoid SparkDestroyQueue(SparkQueue queue);
SPARKAPI SparkResult SparkEnqueueQueue(SparkQueue queue, SparkHandle element);
SPARKAPI SparkResult SparkDequeueQueue(SparkQueue queue);
SPARKAPI SparkHandle SparkGetFrontQueue(SparkQueue queue);
SPARKAPI SparkHandle SparkGetBackQueue(SparkQueue queue);
SPARKAPI SparkResult SparkClearQueue(SparkQueue queue);

SPARKAPI SparkStack SparkDefaultStack();
SPARKAPI SparkStack SparkCreateStack(SparkSize capacity, SparkAllocator allocator, SparkFreeFunction destructor);
SPARKAPI SparkVoid SparkDestroyStack(SparkStack stack);
SPARKAPI SparkResult SparkPushStack(SparkStack stack, SparkHandle element);
SPARKAPI SparkResult SparkPopStack(SparkStack stack);
SPARKAPI SparkHandle SparkGetTopStack(SparkStack stack);
SPARKAPI SparkResult SparkClearStack(SparkStack stack);

/* Shader-related function declarations */

typedef struct SparkShaderT* SparkShader;
typedef struct SparkProgramT* SparkProgram;

/* Shader creation and deletion */
SPARKAPI SparkShader SparkCreateShader(SparkShaderType type, SparkConstString source);
SPARKAPI SparkResult SparkCompileShader(SparkShader shader);
SPARKAPI SparkVoid   SparkDeleteShader(SparkShader shader);

/* Program creation, linking, and deletion */
SPARKAPI SparkProgram SparkCreateProgram();
SPARKAPI SparkResult  SparkAttachShader(SparkProgram program, SparkShader shader);
SPARKAPI SparkResult  SparkLinkProgram(SparkProgram program);
SPARKAPI SparkVoid    SparkDeleteProgram(SparkProgram program);

/* Using the shader program */
SPARKAPI SparkResult SparkUseProgram(SparkProgram program);

/* Uniform setting functions */
SPARKAPI SparkResult SparkSetUniform1f(SparkProgram program, SparkConstString name, SparkF32 v0);
SPARKAPI SparkResult SparkSetUniform2f(SparkProgram program, SparkConstString name, SparkF32 v0, SparkF32 v1);
SPARKAPI SparkResult SparkSetUniform3f(SparkProgram program, SparkConstString name, SparkF32 v0, SparkF32 v1, SparkF32 v2);
SPARKAPI SparkResult SparkSetUniform4f(SparkProgram program, SparkConstString name, SparkF32 v0, SparkF32 v1, SparkF32 v2, SparkF32 v3);

SPARKAPI SparkResult SparkSetUniform1i(SparkProgram program, SparkConstString name, SparkI32 v0);
SPARKAPI SparkResult SparkSetUniform2i(SparkProgram program, SparkConstString name, SparkI32 v0, SparkI32 v1);
SPARKAPI SparkResult SparkSetUniform3i(SparkProgram program, SparkConstString name, SparkI32 v0, SparkI32 v1, SparkI32 v2);
SPARKAPI SparkResult SparkSetUniform4i(SparkProgram program, SparkConstString name, SparkI32 v0, SparkI32 v1, SparkI32 v2, SparkI32 v3);

/* Uniform setting functions for matrices */
SPARKAPI SparkResult SparkSetUniformMat2(SparkProgram program, SparkConstString name, SparkMat2 mat);
SPARKAPI SparkResult SparkSetUniformMat3(SparkProgram program, SparkConstString name, SparkMat3 mat);
SPARKAPI SparkResult SparkSetUniformMat4(SparkProgram program, SparkConstString name, SparkMat4 mat);

/* Attribute location functions */
SPARKAPI SparkResult SparkBindAttribLocation(SparkProgram program, SparkIndex index, SparkConstString name);
SPARKAPI SparkResult SparkGetAttribLocation(SparkProgram program, SparkConstString name, SparkIndex* location);

/* Error handling */
SPARKAPI SparkConstString SparkGetShaderLog(SparkShader shader);
SPARKAPI SparkConstString SparkGetProgramLog(SparkProgram program);

/* Shader reflection functions */
SPARKAPI SparkResult SparkGetUniformLocation(SparkProgram program, SparkConstString name, SparkIndex* location);

/* Shader utility functions */
SPARKAPI SparkResult SparkLoadShaderFromFile(SparkShader shader, SparkConstString filePath);
SPARKAPI SparkResult SparkSetShaderSource(SparkShader shader, SparkConstString source);

/* Uniform Buffer Object (UBO) functions */
typedef struct SparkUniformBufferT* SparkUniformBuffer;
SPARKAPI SparkUniformBuffer SparkCreateUniformBuffer(SparkSize size, SparkConstBuffer data);
SPARKAPI SparkVoid          SparkDeleteUniformBuffer(SparkUniformBuffer buffer);
SPARKAPI SparkResult        SparkBindUniformBuffer(SparkProgram program, SparkConstString name, SparkUniformBuffer buffer);


/* Vertex Buffer functions */
typedef struct SparkVertexBufferT* SparkVertexBuffer;
SPARKAPI SparkVertexBuffer SparkCreateVertexBuffer(SparkSize size, SparkConstBuffer data);
SPARKAPI SparkVoid         SparkDeleteVertexBuffer(SparkVertexBuffer buffer);
SPARKAPI SparkResult       SparkBindVertexBuffer(SparkVertexBuffer buffer);
SPARKAPI SparkResult       SparkSetVertexAttribPointer(SparkIndex index, SparkI32 size, SparkShaderDataType type, SparkBool normalized, SparkSize stride, SparkSize offset);

/* Index Buffer functions */
typedef struct SparkIndexBufferT* SparkIndexBuffer;
SPARKAPI SparkIndexBuffer SparkCreateIndexBuffer(SparkSize size, SparkConstBuffer data);
SPARKAPI SparkVoid        SparkDeleteIndexBuffer(SparkIndexBuffer buffer);
SPARKAPI SparkResult      SparkBindIndexBuffer(SparkIndexBuffer buffer);

/* Drawing functions */
SPARKAPI SparkResult SparkDrawArrays(SparkPrimitiveType mode, SparkIndex first, SparkSize count);
SPARKAPI SparkResult SparkDrawElements(SparkPrimitiveType mode, SparkSize count, SparkShaderDataType type, SparkSize offset);

/* Texture functions */
typedef struct SparkTextureT* SparkTexture;
SPARKAPI SparkTexture SparkCreateTexture2D(SparkI32 width, SparkI32 height, SparkConstBuffer data);
SPARKAPI SparkVoid    SparkDeleteTexture(SparkTexture texture);
SPARKAPI SparkResult  SparkBindTexture(SparkTexture texture, SparkI32 unit);
SPARKAPI SparkResult  SparkSetTextureParameter(SparkTexture texture, SparkI32 pname, SparkI32 param);

/* Framebuffer functions */
typedef struct SparkFramebufferT* SparkFramebuffer;
SPARKAPI SparkFramebuffer SparkCreateFramebuffer();
SPARKAPI SparkVoid        SparkDeleteFramebuffer(SparkFramebuffer framebuffer);
SPARKAPI SparkResult      SparkBindFramebuffer(SparkFramebuffer framebuffer);
SPARKAPI SparkResult      SparkFramebufferTexture2D(SparkFramebuffer framebuffer, SparkTexture texture);

/* Renderbuffer functions */
typedef struct SparkRenderbufferT* SparkRenderbuffer;
SPARKAPI SparkRenderbuffer SparkCreateRenderbuffer(SparkI32 width, SparkI32 height);
SPARKAPI SparkVoid         SparkDeleteRenderbuffer(SparkRenderbuffer renderbuffer);
SPARKAPI SparkResult       SparkBindRenderbuffer(SparkRenderbuffer renderbuffer);
SPARKAPI SparkResult       SparkFramebufferRenderbuffer(SparkFramebuffer framebuffer, SparkRenderbuffer renderbuffer);

/* Render loop functions */
SPARKAPI SparkResult SparkClear(SparkU32 mask);
SPARKAPI SparkResult SparkSetClearColor(SparkF32 red, SparkF32 green, SparkF32 blue, SparkF32 alpha);
SPARKAPI SparkResult SparkSetViewport(SparkI32 x, SparkI32 y, SparkI32 width, SparkI32 height);

/* State setting functions */
SPARKAPI SparkResult SparkEnable(SparkU32 capability);
SPARKAPI SparkResult SparkDisable(SparkU32 capability);

/* Blend functions */
SPARKAPI SparkResult SparkBlendFunc(SparkBlendMode sfactor, SparkBlendMode dfactor);

SPARKAPI SparkError       SparkGetError();
SPARKAPI SparkConstString SparkGetErrorString(SparkError error);
SPARKAPI SparkEcs SparkCreateEcs();
SPARKAPI SparkVoid SparkDestroyEcs(SparkEcs ecs);
SPARKAPI SparkEntity SparkCreateEntity(SparkEcs ecs);
SPARKAPI SparkResult SparkDestroyEntity(SparkEcs ecs, SparkEntity entity);
SPARKAPI SparkResult SparkAddComponent(SparkEcs ecs, SparkEntity entity, SparkComponent component);
SPARKAPI SparkResult SparkRemoveComponent(SparkEcs ecs, SparkEntity entity, SparkConstString component_type, SparkConstString component_name);
SPARKAPI SparkComponent SparkGetComponent(SparkEcs ecs, SparkEntity entity, SparkConstString component_type, SparkConstString component_name);
SPARKAPI SparkResult SparkAddSystem(SparkEcs ecs, SparkSystem system);
SPARKAPI SparkResult SparkRemoveSystem(SparkEcs ecs, SparkSystem system);
SPARKAPI SparkResult SparkStartEcs(SparkEcs ecs);
SPARKAPI SparkResult SparkUpdateEcs(SparkEcs ecs, SparkF32 delta);
SPARKAPI SparkResult SparkStopEcs(SparkEcs ecs);
SPARKAPI SparkWindowData SparkCreateWindowData(SparkConstString title, SparkI32 width, SparkI32 height, SparkBool vsync);
SPARKAPI SparkVoid SparkDestroyWindowData(SparkWindowData window_data);
SPARKAPI SparkWindow SparkCreateWindow(SparkWindowData window_data);
SPARKAPI SparkVoid SparkDestroyWindow(SparkWindow window);
SPARKAPI SparkRenderer SparkCreateRenderer();
SPARKAPI SparkVoid SparkDestroyRenderer(SparkRenderer renderer);
SPARKAPI SparkApplication SparkCreateApplication(SparkWindow window);
SPARKAPI SparkVoid SparkDestroyApplication(SparkApplication app);
SPARKAPI SparkVoid SparkUpdateApplication(SparkApplication app);

#define SPARK_ASSERT(condition, message) if (!(condition)) { assert(SPARK_FALSE && message); }
#define SPARK_ASSERT_NULL(pointer) SPARK_ASSERT(pointer != SPARK_NULL, "Pointer is null")
#define SPARK_ASSERT_NOT_NULL(pointer) SPARK_ASSERT(pointer != SPARK_NULL, "Pointer is not null")
#define SPARK_ASSERT_SUCCESS(result) SPARK_ASSERT(result == SPARK_SUCCESS, "Result is success")
#define SPARK_ASSERT_FAILURE(result) SPARK_ASSERT(result == SPARK_FAILURE, "Result is failure")
#define SPARK_ASSERT_VALID(result) SPARK_ASSERT(result == SPARK_VALID, "Result is valid")
#define SPARK_ASSERT_INVALID(result) SPARK_ASSERT(result == SPARK_INVALID, "Result is invalid")
#define SPARK_ASSERT_NOT_IMPLEMENTED(result) SPARK_ASSERT(result == SPARK_NOT_IMPLEMENTED, "Result is not implemented")
#define SPARK_ASSERT_NULL_OR_VALID(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_VALID, "Result is null or valid")
#define SPARK_ASSERT_NULL_OR_INVALID(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_INVALID, "Result is null or invalid")
#define SPARK_ASSERT_NULL_OR_SUCCESS(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_SUCCESS, "Result is null or success")
#define SPARK_ASSERT_NULL_OR_FAILURE(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_FAILURE, "Result is null or failure")
#define SPARK_ASSERT_NULL_OR_PENDING(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_PENDING, "Result is null or pending")
#define SPARK_ASSERT_NULL_OR_IN_PROGRESS(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_IN_PROGRESS, "Result is null or in progress")
#define SPARK_ASSERT_NULL_OR_COMPLETE(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_COMPLETE, "Result is null or complete")
#define SPARK_ASSERT_NULL_OR_TIMEOUT(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_TIMEOUT, "Result is null or timeout")
#define SPARK_ASSERT_NULL_OR_CANCELLED(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_CANCELLED, "Result is null or cancelled")
#define SPARK_ASSERT_NULL_OR_NOT_IMPLEMENTED(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_NOT_IMPLEMENTED, "Result is null or not implemented")
#define SPARK_ASSERT_NULL_OR_ACCESS_DENIED(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_ACCESS_DENIED, "Result is null or access denied")
#define SPARK_ASSERT_NULL_OR_NOT_FOUND(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_NOT_FOUND, "Result is null or not found")
#define SPARK_ASSERT_NULL_OR_BUSY(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_BUSY, "Result is null or busy")
#define SPARK_ASSERT_NULL_OR_OVERLOADED(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_OVERLOADED, "Result is null or overloaded")
#define SPARK_ASSERT_NULL_OR_DISCONNECTED(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_DISCONNECTED, "Result is null or disconnected")
#define SPARK_ASSERT_NULL_OR_CONNECTED(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_CONNECTED, "Result is null or connected")
#define SPARK_ASSERT_NULL_OR_RETRY(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_RETRY, "Result is null or retry")
#define SPARK_ASSERT_NULL_OR_DEPRECATED(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_DEPRECATED, "Result is null or deprecated")
#define SPARK_ASSERT_NULL_OR_UNSUPPORTED(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_UNSUPPORTED, "Result is null or unsupported")
#define SPARK_ASSERT_NULL_OR_UNINITIALIZED(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_UNINITIALIZED, "Result is null or uninitialized")
#define SPARK_ASSERT_NULL_OR_DISABLED(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_DISABLED, "Result is null or disabled")
#define SPARK_ASSERT_NULL_OR_READ_ONLY(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_READ_ONLY, "Result is null or read only")
#define SPARK_ASSERT_NULL_OR_WRITE_ONLY(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_WRITE_ONLY, "Result is null or write only")
#define SPARK_ASSERT_NULL_OR_OUT_OF_MEMORY(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_OUT_OF_MEMORY, "Result is null or out of memory")
#define SPARK_ASSERT_NULL_OR_OVERFLOW(result) SPARK_ASSERT(result == SPARK_NULL || result == SPARK_OVERFLOW, "Result is null or overflow")


#define SPARK_CRASH_PROGRAM(reason) \
    SPARK_ASSERT(SPARK_FALSE, "Program was forcibly closed for: " #reason)

#if defined(SPARK_DEFINE_BASIC_ALIASES) || defined(SPARK_DEFINE_ALL_ALIASES)

typedef SparkU8 u8;
typedef SparkI8 i8;
typedef SparkU16 u16;
typedef SparkI16 i16;
typedef SparkU32 u32;
typedef SparkI32 i32;
typedef SparkU64 u64;
typedef SparkI64 i64;
typedef SparkF32 f32;
typedef SparkF64 f64;
typedef SparkBool bool_t;
typedef SparkResult result;
typedef SparkError error;
typedef SparkVoid void_t;
typedef SparkHandle handle_t;
typedef SparkString string_t;
typedef SparkConstString const_string_t;
typedef SparkBuffer buffer_t;
typedef SparkConstBuffer const_buffer_t;
typedef SparkSize size_t;
typedef SparkIndex index_t;
typedef SparkCount count_t;
typedef SparkOffset offset_t;
typedef SparkTime stime_t;
typedef SparkDuration duration_t;
typedef SparkFrequency frequency_t;
typedef SparkRate rate_t;

#endif

#if defined(SPARK_DEFINE_ALIASES) || defined(SPARK_DEFINE_ALL_ALIASES)

typedef SparkType Type;
typedef SparkError Error;
typedef SparkAccess Access;
typedef SparkMouseButton MouseButton;
typedef SparkKey Key;
typedef SparkModifier Modifier;
typedef SparkAction Action;
typedef SparkCursor Cursor;
typedef SparkEventType EventType;
typedef SparkShaderType ShaderType;
typedef SparkPrimitiveType PrimitiveType;
typedef SparkBlendMode BlendMode;
typedef SparkTextureFilter TextureFilter;
typedef SparkLogLevel LogLevel;
typedef SparkRenderAPI RenderAPI;

typedef SparkAllocateFunction AllocateFunction;
typedef SparkReallocateFunction ReallocateFunction;
typedef SparkFreeFunction FreeFunction;
typedef SparkHashFunction HashFunction;
typedef SparkSystemStartFunction SystemStartFunction;
typedef SparkSystemUpdateFunction SystemUpdateFunction;
typedef SparkSystemStopFunction SystemStopFunction;

typedef SparkAllocator Allocator;
typedef SparkVector Vector;
typedef SparkList List;
typedef SparkMap Map;
typedef SparkHashMap HashMap;
typedef SparkSet Set;
typedef SparkHashSet HashSet;
typedef SparkQueue Queue;
typedef SparkStack Stack;

typedef SparkEntity Entity;
typedef SparkComponentArray ComponentArray;
typedef SparkComponent Component;
typedef SparkSystem System;
typedef SparkEcs Ecs;
typedef SparkEventHandler EventHandler;
typedef SparkResource Resource;
typedef SparkResourceLoader ResourceLoader;
typedef SparkResourceRegistry ResourceRegistry;
typedef SparkWindowData WindowData;
typedef SparkWindow Window;
typedef SparkRenderer Renderer;
typedef SparkApplication Application;

#define Vector(type) SparkVector
#define List(type) SparkList
#define Map(key, value) SparkMap
#define HashMap(key, value) SparkHashMap
#define Set(type) SparkSet
#define HashSet(type) SparkHashSet
#define Queue(type) SparkQueue
#define Stack(type) SparkStack
#define Graph(type) SparkGraph

#endif

#if defined(SPARK_DEFINE_FUNCTION_ALIASES) || defined(SPARK_DEFINE_ALL_ALIASES)

#define TypeToString SparkTypeToString
#define StringToType SparkStringToType
#define ErrorToString SparkErrorToString
#define StringToError SparkStringToError
#define CheckSuccess SparkCheckSuccess
#define AccessToString SparkAccessToString
#define StringToAccess SparkStringToAccess
#define MouseButtonToString SparkMouseButtonToString
#define StringToMouseButton SparkStringToMouseButton
#define KeyToString SparkKeyToString
#define StringToKey SparkStringToKey
#define ModifierToString SparkModifierToString
#define StringToModifier SparkStringToModifier
#define ActionToString SparkActionToString
#define StringToAction SparkStringToAction
#define CursorToString SparkCursorToString
#define StringToCursor SparkStringToCursor
#define EventTypeToString SparkEventTypeToString
#define StringToEventType SparkStringToEventType
#define ShaderTypeToString SparkShaderTypeToString
#define StringToShaderType SparkStringToShaderType
#define PrimitiveTypeToString SparkPrimitiveTypeToString
#define StringToPrimitiveType SparkStringToPrimitiveType
#define BlendModeToString SparkBlendModeToString
#define StringToBlendMode SparkStringToBlendMode
#define TextureFilterToString SparkTextureFilterToString
#define StringToTextureFilter SparkStringToTextureFilter
#define LogLevelToString SparkLogLevelToString
#define StringToLogLevel SparkStringToLogLevel
#define RenderAPIToString SparkRenderAPIToString
#define StringToRenderAPI SparkStringToRenderAPI

#define Allocate SparkAllocate
#define Reallocate SparkReallocate
#define Free SparkFree
#define CreateAllocator SparkCreateAllocator
#define DestroyAllocator SparkDestroyAllocator
#define GetDefaultAllocator SparkGetDefaultAllocator

#define DefaultVector SparkDefaultVector
#define CreateVector SparkCreateVector
#define DestroyVector SparkDestroyVector
#define GetElementVector SparkGetElementVector
#define PushBackVector SparkPushBackVector
#define PopBackVector SparkPopBackVector
#define InsertVector SparkInsertVector
#define RemoveVector SparkRemoveVector
#define SetVector SparkSetVector
#define ResizeVector SparkResizeVector
#define ClearVector SparkClearVector

#define DefaultList SparkDefaultList
#define CreateList SparkCreateList
#define DestroyList SparkDestroyList
#define GetElementList SparkGetElementList
#define PushList SparkPushList
#define PopList SparkPopList
#define InsertList SparkInsertList
#define RemoveList SparkRemoveList
#define SetList SparkSetList
#define ClearList SparkClearList

#define DefaultMap SparkDefaultMap
#define CreateMap SparkCreateMap
#define DestroyMap SparkDestroyMap
#define GetElementMap SparkGetElementMap
#define InsertMap SparkInsertMap
#define RemoveMap SparkRemoveMap
#define SetMap SparkSetMap
#define ClearMap SparkClearMap

#define DefaultHashMap SparkDefaultHashMap
#define CreateHashMap SparkCreateHashMap
#define DestroyHashMap SparkDestroyHashMap
#define GetElementHashMap SparkGetElementHashMap
#define InsertHashMap SparkInsertHashMap
#define RemoveHashMap SparkRemoveHashMap
#define SetHashMap SparkSetHashMap
#define ClearHashMap SparkClearHashMap

#define DefaultSet SparkDefaultSet
#define CreateSet SparkCreateSet
#define DestroySet SparkDestroySet
#define GetElementSet SparkGetElementSet
#define InsertSet SparkInsertSet
#define RemoveSet SparkRemoveSet
#define ContainsSet SparkContainsSet
#define ClearSet SparkClearSet

#define DefaultHashSet SparkDefaultHashSet
#define CreateHashSet SparkCreateHashSet
#define DestroyHashSet SparkDestroyHashSet
#define InsertHashSet SparkInsertHashSet
#define RemoveHashSet SparkRemoveHashSet
#define ContainsHashSet SparkContainsHashSet
#define ClearHashSet SparkClearHashSet

#define DefaultQueue SparkDefaultQueue
#define CreateQueue SparkCreateQueue
#define DestroyQueue SparkDestroyQueue
#define GetBackQueue SparkGetBackQueue
#define GetFrontQueue SparkGetFrontQueue
#define EnqueueQueue SparkEnqueueQueue
#define DequeueQueue SparkDequeueQueue
#define ClearQueue SparkClearQueue

#define DefaultStack SparkDefaultStack
#define CreateStack SparkCreateStack
#define DestroyStack SparkDestroyStack
#define GetTopStack SparkGetTopStack
#define PushStack SparkPushStack
#define PopStack SparkPopStack
#define ClearStack SparkClearStack

#define CreateEcs SparkCreateEcs
#define DestroyEcs SparkDestroyEcs
#define CreateEntity SparkCreateEntity
#define DestroyEntity SparkDestroyEntity
#define AddComponent SparkAddComponent
#define RemoveComponent SparkRemoveComponent
#define GetComponent SparkGetComponent
#define AddSystem SparkAddSystem
#define RemoveSystem SparkRemoveSystem
#define StartEcs SparkStartEcs
#define UpdateEcs SparkUpdateEcs
#define StopEcs SparkStopEcs

#define CreateWindowData SparkCreateWindowData
#define DestroyWindowData SparkDestroyWindowData
#define CreateWindow SparkCreateWindow
#define DestroyWindow SparkDestroyWindow

#define CreateRenderer SparkCreateRenderer
#define DestroyRenderer SparkDestroyRenderer

#define CreateApplication SparkCreateApplication
#define DestroyApplication SparkDestroyApplication
#define UpdateApplication SparkUpdateApplication

#endif

/*
#ifdef __cplusplus
}
#endif
*/
#endif /* SPARK_H */