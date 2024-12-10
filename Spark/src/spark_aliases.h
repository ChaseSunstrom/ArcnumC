#ifndef __SPARK_ALIASES_H__
#define __SPARK_ALIASES_H__

#include "spark_types.h"

/* Basic Aliases */

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

/* Additional Aliases */

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

typedef SparkEventDataKeyPressed EventDataKeyPressed;
typedef SparkEventDataKeyReleased EventDataKeyReleased;
typedef SparkEventDataMouseMoved EventDataMouseMoved;
typedef SparkEventDataMouseButtonPressed EventDataMouseButtonPressed;
typedef SparkEventDataMouseButtonReleased EventDataMouseButtonReleased;
typedef SparkEventDataMouseScrolled EventDataMouseScrolled;
typedef SparkEventDataWindowResized EventDataWindowResized;

typedef SparkAllocateFunction AllocateFunction;
typedef SparkReallocateFunction ReallocateFunction;
typedef SparkFreeFunction FreeFunction;
typedef SparkHashFunction HashFunction;
typedef SparkSystemStartFunction SystemStartFunction;
typedef SparkSystemUpdateFunction SystemUpdateFunction;
typedef SparkSystemStopFunction SystemStopFunction;

typedef SparkAllocator Allocator;
typedef SparkVector Vector;
typedef SparkAtomicVector AtomicVector;
typedef SparkList List;
typedef SparkMap Map;
typedef SparkHashMap HashMap;
typedef SparkSet Set;
typedef SparkHashSet HashSet;
typedef SparkQueue Queue;
typedef SparkStack Stack;
typedef SparkPair Pair;
typedef SparkVectorIterator VectorIterator;
typedef SparkListIterator ListIterator;
typedef SparkHashMapIterator HashMapIterator;
typedef SparkIterator SparkIterator;
typedef SparkIteratorState IteratorState;

typedef SparkVec2 Vec2;
typedef SparkVec3 Vec3;
typedef SparkVec4 Vec4;
typedef SparkIVec2 IVec2;
typedef SparkIVec3 IVec3;
typedef SparkIVec4 IVec4;
typedef SparkMat2 Mat2;
typedef SparkMat3 Mat3;
typedef SparkMat4 Mat4;
typedef SparkQuat Quat;

typedef SparkEntity Entity;
typedef SparkQuery Query;
typedef SparkComponentArray ComponentArray;
typedef SparkComponent Component;
typedef SparkSystem System;
typedef SparkEcs Ecs;
typedef SparkEventHandler EventHandler;
typedef SparkResource Resource;
typedef SparkResourceLoader ResourceLoader;
typedef SparkResourceManager ResourceRegistry;
typedef SparkWindowData WindowData;
typedef SparkWindow Window;
typedef SparkShader Shader;
typedef SparkEvent Event;
typedef SparkEventHandler EventHandler;
typedef SparkClientConnection ClientConnection;
typedef SparkEnvelope Envelope;
typedef SparkResource Resource;
typedef SparkResourceManager ResourceManager;
typedef SparkStaticMesh StaticMesh;
typedef SparkDynamicMesh DynamicMesh;
typedef SparkStaticModel StaticModel;
typedef SparkDynamicModel DynamicModel;
typedef SparkMaterial Material;
typedef SparkTexture Texture;
typedef SparkAudioBuffer AudioBuffer;
typedef SparkVertex Vertex;
typedef SparkAudio Audio;
typedef SparkThreadPool ThreadPool;
typedef SparkTaskHandle TaskHandle;
typedef SparkServer Server;
typedef SparkClient Client;
typedef SparkFileSerializer FileSerializer;
typedef SparkFileDeserializer FileDeserializer;
typedef SparkApplication Application;

/* Template-like macros for containers */
#define Vector(type) SparkVector
#define List(type) SparkList
#define Map(key, value) SparkMap
#define HashMap(key, value) SparkHashMap
#define Set(type) SparkSet
#define HashSet(type) SparkHashSet
#define Queue(type) SparkQueue
#define Stack(type) SparkStack

/* Function Aliases */

#define Log SparkLogImpl

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
#define DefaultAllocator SparkDefaultAllocator

#define DefaultVector SparkDefaultVector
#define CreateVector SparkCreateVector
#define DestroyVector SparkDestroyVector
#define GetElementVector SparkGetElementVector
#define PushBackVector SparkPushBackVector
#define PopBackVector SparkPopBackVector
#define InsertVector SparkInsertVector
#define RemoveVector SparkRemoveVector
#define EraseVector SparkEraseVector
#define SetVector SparkSetVector
#define CopyVector SparkCopyVector
#define ResizeVector SparkResizeVector
#define ClearVector SparkClearVector
#define PushBackBufferVector SparkPushBackBufferVector

#define DefaultList SparkDefaultList
#define CreateList SparkCreateList
#define DestroyList SparkDestroyList
#define GetElementList SparkGetElementList
#define PushList SparkPushBackList
#define PopList SparkPopBackList
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
#define GetAllKeysHashMap SparkGetAllKeysHashMap
#define GetAllValuesHashMap SparkGetAllValuesHashMap
#define GetAllPairsHashMap SparkGetAllPairsHashMap

#define DefaultSet SparkDefaultSet
#define CreateSet SparkCreateSet
#define DestroySet SparkDestroySet
#define GetElementSet SparkGetElementSet
#define InsertSet SparkInsertSet
#define RemoveSet SparkRemoveSet
#define ContainsSet SparkContainsSet
#define ClearSet SparkClearSet

#define CreateResourceManager SparkCreateResourceManager
#define DestroyResourceManager SparkDestroyResourceManager
#define AddResource SparkAddResource
#define CreateResource SparkCreateResource
#define RemoveResource SparkRemoveResource
#define CreateResourceDataV SparkCreateResourceData
#define CreateResourceData SparkCreateResourceData
#define GetResource SparkGetResource

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

#define CreateVectorIterator SparkCreateVectorIterator
#define DestroyVectorIterator SparkDestroyVectorIterator
#define IterateForwardVectorIterator SparkIterateForwardVectorIterator
#define IterateBackwardVectorIterator SparkIterateBackwardVectorIterator
#define IsAtBeginningVectorIterator SparkIsAtBeginningVectorIterator
#define IsAtEndVectorIterator SparkIsAtEndVectorIterator
#define GetCurrentVectorIterator SparkGetCurrentVectorIterator
#define GetPreviousVectorIterator SparkGetPreviousVectorIterator
#define GetNextVectorIterator SparkGetNextVectorIterator
#define HasNextVectoriterator SparkHasNextVectorIterator
#define HasPreviousVectorIterator SparkHasPreviousVectorIterator

#define CreateListIterator SparkCreateListIterator
#define DestroyListIterator SparkDestroyListIterator
#define IterateForwardListIterator SparkIterateForwardListIterator
#define IterateBackwardListIterator SparkIterateBackwardListIterator
#define IsAtBeginningListIterator SparkIsAtBeginningListIterator
#define IsAtEndListIterator SparkIsAtEndListIterator
#define GetCurrentListIterator SparkGetCurrentListIterator
#define GetPreviousListIterator SparkGetPreviousListIterator
#define GetNextListIterator SparkGetNextListIterator
#define HasNextListiterator SparkHasNextListIterator
#define HasPreviousListIterator SparkHasPreviousListIterator

#define CreateHashMapIterator SparkCreateHashMapIterator
#define DestroyHashMapIterator SparkDestroyHashMapIterator
#define IterateForwardHashMapIterator SparkIterateForwardHashMapIterator
#define IterateBackwardHashMapIterator SparkIterateBackwardHashMapIterator
#define IsAtBeginningHashMapIterator SparkIsAtBeginningHashMapIterator
#define IsAtEndHashMapIterator SparkIsAtEndHashMapIterator
#define GetCurrentHashMapIterator SparkGetCurrentHashMapIterator
#define GetPreviousHashMapIterator SparkGetPreviousHashMapIterator
#define GetNextHashMapIterator SparkGetNextHashMapIterator
#define HasNextHashMapiterator SparkHasNextHashMapIterator
#define HasPreviousHashMapIterator SparkHasPreviousHashMapIterator

#define CreateEcs SparkCreateEcs
#define DestroyEcs SparkDestroyEcs
#define CreateEntity SparkCreateEntity
#define DestroyEntity SparkDestroyEntity
#define AddComponent SparkAddComponent
#define CreateComponent SparkCreateComponent
#define RemoveComponent SparkRemoveComponent
#define GetComponent SparkGetComponent
#define AddSystem SparkAddSystem
#define RemoveSystem SparkRemoveSystem
#define StartEcs SparkStartEcs
#define UpdateEcs SparkUpdateEcs
#define StopEcs SparkStopEcs

#define CreateThreadPool SparkCreateThreadPool
#define DestroyThreadPool SparkDestroyThreadPool
#define WaitThreadPool SparkWaitThreadPool
#define AddTaskThreadPool SparkAddTaskThreadPool
#define IsTaskDone SparkIsTaskDone
#define WaitTask SparkWaitTask
#define TaskDestroy SparkTaskDestroy
#define AddShutdownCallbackThreadPool SparkAddShutdownCallbackThreadPool

#define CreateEventHandler SparkCreateEventHandler
#define DestroyEventHandler SparkDestroyEventHandler
#define AddEventListener SparkAddEventListener
#define RemoveEventListener SparkRemoveEventListener
#define DispatchEvent SparkDispatchEvent
#define CreateEvent SparkCreateEvent
#define DestroyEvent SparkDestroyEvent

#define CreateWindowData SparkCreateWindowData
#define DestroyWindowData SparkDestroyWindowData
#define CreateWindow SparkCreateWindow
#define DestroyWindow SparkDestroyWindow

#define CreateRenderer SparkCreateRenderer
#define DestroyRenderer SparkDestroyRenderer

#define CreateFileSerializer SparkCreateFileSerializer
#define DestroyFileSerializer SparkDestroyFileSerializer
#define SerializeRawData SparkSerializeRawData
#define SerializeData SparkSerializeData
#define SerializeHeader SparkSerializeHeader
#define SerializeVector SparkSerializeVector
#define CreateFileDeserializer SparkCreateFileDeserializer
#define DestroyFileDeserializer SparkDestroyFileDeserializer
#define DeserializeRawData SparkDeserializeRawData
#define DeserializeData SparkDeserializeData
#define DeserializeHeader SparkDeserializeHeader
#define DeserializeString SparkDeserializeString
#define DeserializeTrivial SparkDeserializeTrivial
#define DserializeVector SparkDeserializeVector
#define Serialize SparkSerialize
#define Deserialize SparkDeserialize

#define CreateClient SparkCreateClient
#define DestroyClient SparkDestroyClient
#define ConnectClient SparkConnectClient
#define DisconnectClient SparkDisconnectClient
#define SendToServer SparkSendToServer
#define CreateServer SparkCreateServer
#define DestroyServer SparkDestroyServer
#define StartServer SparkStartServer
#define StopServer SparkStopServer
#define SendToClient SparkSendToClient
#define Broadcast SparkBroadcast

#define CreateStaticMesh SparkCreateStaticMesh
#define CreateStaticMeshI SparkCreateStaticMeshI
#define DestroyStaticMesh SparkDestroyStaticMesh
#define CreateDynamicMesh SparkCreateDynamicMesh
#define CreateDynamicMeshI SparkCreateDynamicMeshI
#define DestroyDynamicMesh SparkDestroyDynamicMesh

#define CreateTexture SparkCreateTexture
#define DestroyTexture SparkDestroyTexture

#define CreateShader SparkCreateShader
#define CreateShaderE SparkCreateShaderE

#define CreateApplication SparkCreateApplication
#define DestroyApplication SparkDestroyApplication
#define AddEventFunctionApplication SparkAddEventFunctionApplication
#define DispatchEventApplication SparkDispatchEventApplication
#define StartApplication SparkStartApplication
#define AddStartFunctionApplication SparkAddStartFunctionApplication
#define AddUpdateFunctionApplication SparkAddUpdateFunctionApplication
#define AddStopFunctionApplication SparkAddStopFunctionApplication
#define AddQueryFunctionApplication SparkAddQueryFunctionApplication
#define AddQueryEventFunctionApplication SparkAddQueryEventFunctionApplication
#define CreateResourceApplication SparkCreateResourceApplication
#define GetResourceApplication SparkGetResourceApplication
#define AddResourceApplication SparkAddResourceApplication
#define AddResourceManagerApplication SparkAddResourceManagerApplication
#define RemoveResourceApplication SparkRemoveResourceApplication

/* Macro Aliases */

#define LogDebug SPARK_LOG_DEBUG
#define LogInfo SPARK_LOG_INFO
#define LogWarn SPARK_LOG_WARN
#define LogError SPARK_LOG_ERROR
#define LogFatal SPARK_LOG_FATAL

#define TransformComponent SPARK_TRANSFORM_COMPONENT
#define StaticMeshComponent SPARK_STATIC_MESH_COMPONENT
#define DynamicMeshComponent SPARK_DYNAMIC_MESH_COMPONENT
#define MaterialComponent SPARK_MATERIAL_COMPONENT
#define CameraComponent SPARK_CAMERA_COMPONENT
#define StaticModelComponent SPARK_STATIC_MODEL_COMPONENT
#define DynamicModelComponent SPARK_DYNAMIC_MODEL_COMPONENT
#define RigidBodyComponent SPARK_RIGID_BODY_COMPONENT
#define ColliderComponent SPARK_COLLIDER_COMPONENT
#define AnimationComponent SPARK_ANIMATION_COMPONENT
#define AIBehaviorComponent SPARK_AI_BEHAVIOR_COMPONENT

#define StaticMeshResourceType SPARK_RESOURCE_TYPE_STATIC_MESH
#define DynamicMeshResourceType SPARK_RESOURCE_TYPE_DYNAMIC_MESH
#define TextureResourceType SPARK_RESOURCE_TYPE_TEXTURE
#define ShaderResourceType SPARK_RESOURCE_TYPE_SHADER
#define FontResourceType SPARK_RESOURCE_TYPE_FONT
#define AnimationResourceType SPARK_RESOURCE_TYPE_ANIMATION
#define AudioResourceType SPARK_RESOURCE_TYPE_AUDIO
#define StaticModelResourceType SPARK_RESOURCE_TYPE_STATIC_MODEL
#define DynamicModelResourceType SPARK_RESOURCE_TYPE_DYNAMIC_MODEL
#define MaterialResourceType SPARK_RESOURCE_TYPE_MATERIAL
#define SceneResourceType SPARK_RESOURCE_TYPE_SCENE
#define AIBehaviorResourceType SPARK_RESOURCE_TYPE_AI_BEHAVIOR

#define ArrayArg SPARK_ARRAY_ARG
#define NoIndices SPARK_NULL, 0
#define MakeVertex(x, y, z, nx, ny, nz, u, v) SPARK_MAKE_VERTEX(x, y, z, nx, ny, nz, u, v)

#endif /* __SPARK_ALIASES_H__ */

