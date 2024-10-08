#ifndef __SPARK_H__
#define __SPARK_H__

#include <vulkan/vulkan_core.h>

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
typedef SparkU32 SparkSize;
typedef SparkU32 SparkIndex;
typedef SparkU32 SparkCount;
typedef SparkU32 SparkOffset;
typedef SparkU32 SparkLength;
typedef SparkU32 SparkTime;
typedef SparkU32 SparkDuration;
typedef SparkU32 SparkFrequency;
typedef SparkU32 SparkRate;

typedef enum SparkType : SparkI8 {
	// Boolean values
	SPARK_FALSE = 0,
	SPARK_TRUE = 1,

	// General statuses
	SPARK_SUCCESS = 0,
	SPARK_FAILURE = -1,
	SPARK_ERROR = -2,

	// Validation statuses
	SPARK_VALID = 1,
	SPARK_INVALID = 0,

	// Null and undefined values
	SPARK_NULL = 0,
	SPARK_NONE = 0,
	SPARK_UNKNOWN = -4,

	// Additional statuses
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

typedef enum SparkError : SparkI8 {
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

typedef enum SparkAccess : SparkI8 {
	SPARK_ACCESS_NONE = 0,
	SPARK_ACCESS_READ = 1,
	SPARK_ACCESS_WRITE = 2,
	SPARK_ACCESS_READ_WRITE = 3
} SparkAccess;

typedef SparkHandle(*SparkAllocateFunction)(SparkSize size);
typedef SparkHandle(*SparkReallocateFunction)(SparkHandle handle, SparkSize size);
typedef SparkVoid(*SparkFreeFunction)(SparkHandle handle);

typedef SparkSize(*SparkHashFunction)(SparkConstBuffer buf);

typedef SparkVoid(*SparkSystemStartFunction)(SparkVoid);
typedef SparkVoid(*SparkSystemUpdateFunction)(SparkF32 delta);
typedef SparkVoid(*SparkSystemStopFunction)(SparkVoid);

typedef struct SparkAllocatorT {
	SparkAllocateFunction allocate;
	SparkReallocateFunction reallocate;
	SparkFreeFunction free;
} *SparkAllocator;

typedef struct SparkVectorT {
	SparkSize size;
	SparkSize capacity;
	SparkSize element_size;
	SparkHandle elements;
	SparkAllocator allocator;
} *SparkVector;

typedef struct SparkListT {
	SparkSize size;
	SparkHandle head;
	SparkHandle tail;
	SparkAllocator allocator;
} *SparkList;

typedef struct SparkMapT {
	SparkSize size;
	SparkHandle root;
	SparkAllocator allocator;
} *SparkMap;

typedef struct SparkHashMapT {
	SparkSize size;
	SparkSize capacity;
	/* Allocator stored in the buckets */
	SparkList buckets;
	SparkHashFunction hash;
} *SparkHashMap;

typedef struct SparkSetT {
	SparkSize size;
	SparkHandle root;
	SparkAllocator allocator;
} *SparkSet;

typedef struct SparkHashSetT {
	SparkSize size;
	SparkSize capacity;
	/* Allocator stored in the buckets */
	SparkList buckets;
	SparkHashFunction hash;
} *SparkHashSet;

typedef struct SparkQueueT {
	SparkSize size;
	SparkHandle head;
	SparkHandle tail;
	SparkList buckets;
} *SparkQueue;

typedef struct SparkStackT {
	SparkSize size;
	SparkHandle top;
	SparkList buckets;
} *SparkStack;

typedef struct SparkGraphT {
	SparkSize size;
	SparkHandle nodes;
	SparkHandle edges;
	SparkList buckets;
} *SparkGraph;

typedef struct SparkEventHandlerT {

} *SparkEventHandler;

typedef SparkI32 SparkEntity;
typedef SparkVector SparkComponentArray;

typedef struct SparkComponentT {
	/* Parent entity of this component
	 * Component data needs to be composed inside other structures
	 * and also the first element in that struct
	 */
	SparkEntity entity;
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

typedef struct SparkWindowDataT {
	SparkConstString title;
	SparkI32 width;
	SparkI32 height;
} *SparkWindowData;

typedef struct SparkWindowT {
	SparkWindowData window_data;
} *SparkWindow;

typedef struct SparkRendererT {

} *SparkRenderer;


typedef struct SparkApplicationT {
	SparkWindow window;
	SparkRenderer renderer;
} *SparkApplication;

SPARKAPI SparkConstString SparkTypeToString(SparkType type);
SPARKAPI SparkType SparkStringToType(SparkConstString string);

SPARKAPI SparkConstString SparkErrorToString(SparkError error);
SPARKAPI SparkError SparkStringToError(SparkConstString string);

SPARKAPI SparkHandle SparkAllocate(SparkSize size);
SPARKAPI SparkHandle SparkReallocate(SparkHandle handle, SparkSize size);
SPARKAPI SparkVoid SparkFree(SparkHandle handle);

SPARKAPI SparkAllocator SparkCreateAllocator(SparkAllocateFunction allocate, SparkReallocateFunction reallocate, SparkFreeFunction free);
SPARKAPI SparkVoid SparkDestroyAllocator(SparkAllocator allocator);
SPARKAPI SparkAllocator SparkGetDefaultAllocator();

SPARKAPI SparkVector SparkDefaultVector();
SPARKAPI SparkVector SparkCreateVector(SparkSize element_size, SparkSize capacity, SparkAllocator allocator);
SPARKAPI SparkVoid SparkDestroyVector(SparkVector vector);
SPARKAPI SparkHandle SparkGetElementVector(SparkVector vector, SparkIndex index);
SPARKAPI SparkResult SparkPushVector(SparkVector vector, SparkConstBuffer element);
SPARKAPI SparkResult SparkPopVector(SparkVector vector, SparkBuffer element);
SPARKAPI SparkResult SparkInsertVector(SparkVector vector, SparkIndex index, SparkConstBuffer element);
SPARKAPI SparkResult SparkRemoveVector(SparkVector vector, SparkIndex index);
SPARKAPI SparkResult SparkSetVector(SparkVector vector, SparkIndex index, SparkConstBuffer element);
SPARKAPI SparkResult SparkResizeVector(SparkVector vector, SparkSize capacity);
SPARKAPI SparkResult SparkClearVector(SparkVector vector);

SPARKAPI SparkList SparkDefaultList();
SPARKAPI SparkList SparkCreateList(SparkAllocator allocator);
SPARKAPI SparkVoid SparkDestroyList(SparkList list);
SPARKAPI SparkHandle SparkGetElementList(SparkList list, SparkIndex index);
SPARKAPI SparkResult SparkPushList(SparkList list, SparkConstBuffer element);
SPARKAPI SparkResult SparkPopList(SparkList list, SparkBuffer element);
SPARKAPI SparkResult SparkInsertList(SparkList list, SparkIndex index, SparkConstBuffer element);
SPARKAPI SparkResult SparkRemoveList(SparkList list, SparkIndex index);
SPARKAPI SparkResult SparkSetList(SparkList list, SparkIndex index, SparkConstBuffer element);
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
SPARKAPI SparkHashMap SparkCreateHashMap(SparkSize capacity, SparkHashFunction hash, SparkAllocator allocator);
SPARKAPI SparkVoid SparkDestroyHashMap(SparkHashMap hashmap);
SPARKAPI SparkHandle SparkGetElementHashMap(SparkHashMap hashmap, SparkConstBuffer key);
SPARKAPI SparkResult SparkInsertHashMap(SparkHashMap hashmap, SparkConstBuffer key, SparkConstBuffer value);
SPARKAPI SparkResult SparkRemoveHashMap(SparkHashMap hashmap, SparkConstBuffer key);
SPARKAPI SparkResult SparkSetHashMap(SparkHashMap hashmap, SparkConstBuffer key, SparkConstBuffer value);
SPARKAPI SparkResult SparkClearHashMap(SparkHashMap hashmap);

SPARKAPI SparkSet SparkDefaultSet();
SPARKAPI SparkSet SparkCreateSet(SparkAllocator allocator);
SPARKAPI SparkVoid SparkDestroySet(SparkSet set);
SPARKAPI SparkHandle SparkGetElementSet(SparkSet set, SparkConstBuffer element);
SPARKAPI SparkResult SparkInsertSet(SparkSet set, SparkConstBuffer element);
SPARKAPI SparkResult SparkRemoveSet(SparkSet set, SparkConstBuffer element);
SPARKAPI SparkResult SparkContainsSet(SparkSet set, SparkConstBuffer element);
SPARKAPI SparkResult SparkClearSet(SparkSet set);

SPARKAPI SparkHashSet SparkDefaultHashSet();
SPARKAPI SparkHashSet SparkCreateHashSet(SparkSize capacity, SparkHashFunction hash, SparkAllocator allocator);
SPARKAPI SparkVoid SparkDestroyHashSet(SparkHashSet hashset);
SPARKAPI SparkHandle SparkGetElementHashSet(SparkHashSet hashset, SparkConstBuffer element);
SPARKAPI SparkResult SparkInsertHashSet(SparkHashSet hashset, SparkConstBuffer element);
SPARKAPI SparkResult SparkRemoveHashSet(SparkHashSet hashset, SparkConstBuffer element);
SPARKAPI SparkResult SparkContainsHashSet(SparkHashSet hashset, SparkConstBuffer element);
SPARKAPI SparkResult SparkClearHashSet(SparkHashSet hashset);

SPARKAPI SparkQueue SparkDefaultQueue();
SPARKAPI SparkQueue SparkCreateQueue(SparkSize capacity, SparkAllocator allocator);
SPARKAPI SparkVoid SparkDestroyQueue(SparkQueue queue);
SPARKAPI SparkHandle SparkGetBackQueue(SparkQueue queue);
SPARKAPI SparkHandle SparkGetFrontQueue(SparkQueue queue);
SPARKAPI SparkResult SparkEnqueueQueue(SparkQueue queue, SparkConstBuffer element);
SPARKAPI SparkResult SparkDequeueQueue(SparkQueue queue);
SPARKAPI SparkResult SparkClearQueue(SparkQueue queue);

SPARKAPI SparkStack SparkDefaultStack();
SPARKAPI SparkStack SparkCreateStack(SparkSize capacity, SparkAllocator allocator);
SPARKAPI SparkVoid SparkDestroyStack(SparkStack stack);
SPARKAPI SparkHandle SparkGetTopStack(SparkStack stack);
SPARKAPI SparkResult SparkPushStack(SparkStack stack, SparkConstBuffer element);
SPARKAPI SparkResult SparkPopStack(SparkStack stack);
SPARKAPI SparkResult SparkClearStack(SparkStack stack);

SPARKAPI SparkGraph SparkDefaultGraph();
SPARKAPI SparkGraph SparkCreateGraph(SparkAllocator allocator);
SPARKAPI SparkVoid SparkDestroyGraph(SparkGraph graph);
SPARKAPI SparkHandle SparkGetNodeGraph(SparkGraph graph, SparkConstBuffer key);
SPARKAPI SparkHandle SparkGetEdgeGraph(SparkGraph graph, SparkConstBuffer key);
SPARKAPI SparkResult SparkInsertNodeGraph(SparkGraph graph, SparkConstBuffer key, SparkConstBuffer value);
SPARKAPI SparkResult SparkInsertEdgeGraph(SparkGraph graph, SparkConstBuffer key, SparkConstBuffer value);
SPARKAPI SparkResult SparkRemoveNodeGraph(SparkGraph graph, SparkConstBuffer key);
SPARKAPI SparkResult SparkRemoveEdgeGraph(SparkGraph graph, SparkConstBuffer key);
SPARKAPI SparkResult SparkSetNodeGraph(SparkGraph graph, SparkConstBuffer key, SparkConstBuffer value);
SPARKAPI SparkResult SparkSetEdgeGraph(SparkGraph graph, SparkConstBuffer key, SparkConstBuffer value);
SPARKAPI SparkResult SparkClearGraph(SparkGraph graph);

SPARKAPI SparkWindowData SparkCreateWindowData(SparkConstString title, SparkI32 width, SparkI32 height);
SPARKAPI SparkVoid SparkDestroyWindowData(SparkWindowData window_data);
SPARKAPI SparkWindow SparkCreateWindow(SparkWindowData window_data);
SPARKAPI SparkVoid SparkDestroyWindow(SparkWindow window);

SPARKAPI SparkRenderer SparkCreateRenderer();
SPARKAPI SparkVoid SparkDestroyRenderer(SparkRenderer renderer);

SPARKAPI SparkApplication SparkCreateApplication(SparkWindow window, SparkRenderer renderer);
SPARKAPI SparkVoid SparkDestroyApplication(SparkApplication application);


#define SPARK_ASSERT(condition) if (!(condition)) { return SPARK_INVALID; }
#define SPARK_ASSERT_NULL(pointer) if ((pointer) == SPARK_NULL) { return SPARK_INVALID; }
#define SPARK_ASSERT_NOT_NULL(pointer) if ((pointer) != SPARK_NULL) { return SPARK_INVALID; }
#define SPARK_ASSERT_TRUE(condition) if (!(condition)) { return SPARK_INVALID; }
#define SPARK_ASSERT_FALSE(condition) if ((condition)) { return SPARK_INVALID; }
#define SPARK_ASSERT_SUCCESS(result) if ((result) != SPARK_SUCCESS) { return SPARK_INVALID; }
#define SPARK_ASSERT_FAILURE(result) if ((result) == SPARK_SUCCESS) { return SPARK_INVALID; }
#define SPARK_ASSERT_VALID(result) if ((result) != SPARK_VALID) { return SPARK_INVALID; }
#define SPARK_ASSERT_INVALID(result) if ((result) == SPARK_VALID) { return SPARK_INVALID; }

#ifdef SPARK_DEFINE_BASIC_ALIASES || defined(SPARK_DEFINE_ALL_ALIASES)

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

#endif

#ifdef SPARK_DEFINE_ALIASES || defined(SPARK_DEFINE_ALL_ALIASES)

typedef SparkAllocator Allocator;
typedef SparkWindowData WindowData
typedef SparkWindow Window;
typedef SparkApplication Application;

typedef SparkVector Vector;
typedef SparkList List;
typedef SparkMap Map;
typedef SparkHashMap HashMap;
typedef SparkSet Set;
typedef SparkHashSet HashSet;
typedef SparkQueue Queue;
typedef SparkStack Stack;
typedef SparkGraph Graph;

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

#ifdef SPARK_DEFINE_FUNCTION_ALIASES || defined(SPARK_DEFINE_ALL_ALIASES)

typedef SparkTypeToString TypeToString;
typedef SparkStringToType StringToType;
typedef SparkErrorToString ErrorToString;
typedef SparkStringToError StringToError;
typedef SparkAllocate Allocate;
typedef SparkReallocate Reallocate;
typedef SparkFree Free;
typedef SparkCreateAllocator CreateAllocator;
typedef SparkDestroyAllocator DestroyAllocator;
typedef SparkGetDefaultAllocator GetDefaultAllocator;
typedef SparkCreateWindowData CreateWindowData;
typedef SparkDestroyWindowData DestroyWindowData;
typedef SparkCreateWindow CreateWindow;
typedef SparkDestroyWindow DestroyWindow;
typedef SparkCreateRenderer CreateRenderer;
typedef SparkDestroyRenderer DestroyRenderer;
typedef SparkCreateApplication CreateApplication;
typedef SparkDestroyApplication DestroyApplication;

#endif


/*
#ifdef __cplusplus
}
#endif
*/
#endif