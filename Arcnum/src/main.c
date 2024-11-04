/* main.c */
#define SPARK_DEFINE_ALL_ALIASES
#include "spark.h"
#include <stdbool.h>

typedef struct {
	char* name;
	f32 age;
	i64 id;
} TestThing;

/* Server receive callback */
void server_receive_callback(Server server, ClientConnection client,
	Envelope* envelope) {
	printf("Server received data from client.\n");

	TestThing* test = envelope->packet.data;

	LogWarn("Name: %s", test->name);
	LogWarn("Age: %f", test->age);
	LogWarn("ID: %lld", test->id);

	SparkBroadcast(server, envelope);

	// Free(test->name);
}

/* Client receive callback */
void client_receive_callback(Client client, Envelope* envelope) {
	printf("Client received data from server.\n");
}

static Client client = NULL;
static Server server = NULL;
static Envelope envelope;

void SerializeTestThing(FileSerializer serializer, TestThing test) {
	Serialize(serializer, test.name);
	Serialize(serializer, test.age);
	Serialize(serializer, test.id);
}

TestThing DeserializeTestThing(FileDeserializer deserializer) {
	TestThing test = { 0 };
	size_t name_l;

	Deserialize(deserializer, test.name, name_l);
	Deserialize(deserializer, test.age);
	Deserialize(deserializer, test.id);

	return test;
}

void TestSerialization(Application app) {
	TestThing test = { "Hello, hehehe", 20.0f, 1234567890 };
	FileSerializer serializer = CreateFileSerializer("test.bin");
	SerializeTestThing(serializer, test);
	DestroyFileSerializer(serializer);
}

static TestThing test;

void TestDeserialization(Application app) {
	FileDeserializer deserializer = CreateFileDeserializer("test.bin");
	test = DeserializeTestThing(deserializer);
	DestroyFileDeserializer(deserializer);
}

void update_send(Application app) {
	envelope.type = SPARK_ENVELOPE_TYPE_DATA;
	envelope.packet.size = sizeof(TestThing);
	envelope.packet.data = (SparkBuffer)&test;
	if (SendToServer(client, &envelope) != SPARK_SUCCESS) {
		LogError("Failed to send data to server.\n");
	}
}

void EventHandlerThing(Application app, Event event) {
	EventDataKeyPressed key = event.data;
	LogDebug("Key pressed: %s", KeyToString(key->key));
}

void CreateEntities(Application app) {
	for (size_t i = 0; i < 10000; i++) {
		Entity e = CreateEntity(app->ecs);
		AddComponent(app->ecs, e, SparkDefaultTransformComponent("Transform"));
	}
}

void QueryThing(Application app) {
	SparkVector components =
		SparkGetAllComponentsByType(app->ecs, SPARK_TRANSFORM_COMPONENT);
	for (u32 i = 0; i < components->size; i++) {
		Component component = components->elements[i];
		TestThing* test = component->data;
		LogDebug("Name: %s", test->name);
		LogDebug("Age: %f", test->age);
		LogDebug("ID: %lld", test->id);
	}
	SparkDestroyVector(components);
}

void ResourceCreater(Application app) {
	Vertex vertices[] = {
		MakeVertex(-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
		MakeVertex(0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f),
		MakeVertex(0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f),
		MakeVertex(-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f) };

	Resource res =
		CreateResourceApplication(app, StaticMeshResourceType, "Square",
			CreateStaticMesh(ArrayArg(vertices)));

	StaticMesh mesh = res->data;

	for (size_t i = 0; i < mesh->vertex_count; i++) {
		Vertex curr_vertex = mesh->vertices[i];
		LogDebug("Vertex %d: %f, %f, %f, %f, %f, %f, %f, %f", i,
			curr_vertex.position.x, curr_vertex.position.y,
			curr_vertex.position.z, curr_vertex.normal.x, curr_vertex.normal.y,
			curr_vertex.normal.z, curr_vertex.texcoord.x,
			curr_vertex.texcoord.y);
	}

	RemoveResourceApplication(app, StaticMeshResourceType, "Square");
}

void CreateShaders(Application app) {
	Shader vshader = CreateShader(app, SPARK_SHADER_VERTEX, "src/shader.vert");
	Shader fshader = CreateShader(app, SPARK_SHADER_FRAGMENT, "src/shader.frag");

	Resource vres = CreateResourceApplication(app, SPARK_RESOURCE_TYPE_SHADER, "vshader", vshader);
	Resource fres = CreateResourceApplication(app, SPARK_RESOURCE_TYPE_SHADER, "fshader", fshader);

	SparkGraphicsPipelineConfig gp = SparkCreateGraphicsPipelineConfig(app, vshader, fshader, SPARK_NULL, SPARK_NULL, SPARK_NULL, SPARK_NULL);

	Resource res = CreateResourceApplication(app, SPARK_RESOURCE_TYPE_GRAPHICS_PIPELINE_CONFIG, "default", gp);
}

void ExitOnEscape(Application app, Event event) {
	EventDataKeyPressed kp = event.data;

	if (kp->key == SPARK_KEY_ESCAPE) {
		app->window->should_close = SPARK_TRUE;
	}
}

void TestIterator(Application app) {
	HashMap hmap = DefaultHashMap();

	InsertHashMap(hmap, "Hello", strlen("Hello"), "World");
	InsertHashMap(hmap, "Goodbye", strlen("Goodbye"), "Goodbye");
	InsertHashMap(hmap, "Test", strlen("Test"), "World");

	HashMapIterator kit = CreateHashMapIterator(
		SPARK_ITERATOR_STATE_BEGIN, SPARK_HASHMAP_ITERATOR_TYPE_KEY, hmap);
	do {
		LogDebug("Key: %s", GetCurrentHashMapIterator(kit));
	} while (IterateForwardHashMapIterator(kit) != SPARK_ITERATOR_STATE_END);

	HashMapIterator vit = CreateHashMapIterator(
		SPARK_ITERATOR_STATE_BEGIN, SPARK_HASHMAP_ITERATOR_TYPE_VALUE, hmap);
	do {
		LogDebug("Value: %s", GetCurrentHashMapIterator(vit));
	} while (IterateForwardHashMapIterator(vit) != SPARK_ITERATOR_STATE_END);

	HashMapIterator pit = CreateHashMapIterator(
		SPARK_ITERATOR_STATE_BEGIN, SPARK_HASHMAP_ITERATOR_TYPE_PAIR, hmap);
	do {
		LogDebug("Key: %s", ((Pair*)GetCurrentHashMapIterator(pit))->first);
		LogDebug("Value: %s", ((Pair*)GetCurrentHashMapIterator(pit))->second);
	} while (IterateForwardHashMapIterator(pit) != SPARK_ITERATOR_STATE_END);

	DestroyHashMapIterator(kit);
	DestroyHashMapIterator(vit);
	DestroyHashMapIterator(pit);
	DestroyHashMap(hmap);
}

void TestComponents(Application app, SparkVector vec) {

}

i32 main() {
	Application app = CreateApplication(
		CreateWindow(
			CreateWindowData("Hello", 1080, 1080, SPARK_FALSE, SPARK_PRESENT_MODE_MAILBOX)
		), 
	8);

	server = CreateServer(app->thread_pool, 12345, server_receive_callback);
	client = CreateClient(app->thread_pool, "127.0.0.1", 12345,
		client_receive_callback);

	StartServer(server);
	ConnectClient(client);

	AddStartFunctionApplication(app, ResourceCreater, SPARK_UNBLOCKED_PARRALLELISM);
	AddStartFunctionApplication(app, TestSerialization, SPARK_UNBLOCKED_PARRALLELISM);
	AddStartFunctionApplication(app, TestDeserialization, SPARK_UNBLOCKED_PARRALLELISM);
	AddStartFunctionApplication(app, CreateEntities, SPARK_UNBLOCKED_PARRALLELISM);
	AddStartFunctionApplication(app, TestIterator, SPARK_UNBLOCKED_PARRALLELISM);
	AddStartFunctionApplication(app, CreateShaders, SPARK_UNTHREADED);
	AddUpdateFunctionApplication(app, update_send, SPARK_UNTHREADED);
	AddQueryFunctionApplication(app, SPARK_TRANSFORM_COMPONENT, TestComponents, SPARK_UNTHREADED);
	AddEventFunctionApplication(app, SPARK_EVENT_KEY_PRESSED, ExitOnEscape, SPARK_UNBLOCKED_PARRALLELISM);
	AddEventFunctionApplication(app, SPARK_EVENT_KEY_PRESSED, EventHandlerThing, SPARK_UNBLOCKED_PARRALLELISM);

	StartApplication(app);

	Free(test.name);

	return 0;
}