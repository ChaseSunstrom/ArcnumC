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
void server_receive_callback(Server server, ClientConnection client, Envelope* envelope) {
	printf("Server received data from client.\n");

	TestThing* test = envelope->packet.data;

	SPARK_LOG_WARN("Name: %s", test->name);
	SPARK_LOG_WARN("Age: %f", test->age);
	SPARK_LOG_WARN("ID: %lld", test->id);

	/* Echo the data back to the client */
	SparkBroadcast(server, envelope);

	//Free(test->name);
}

/* Client receive callback */
void client_receive_callback(Client  client, Envelope* envelope) {
	printf("Client received data from server.\n");
	/* Process the data */
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
		printf("Failed to send data to server.\n");
	}
}

void TestGetPairs(Application app) {
	HashMap hmap = DefaultHashMap();

	InsertHashMap(hmap, "Hello", strlen("Hello"), "World");
	InsertHashMap(hmap, "Goodbye", strlen("Goodbye"), "World");
	InsertHashMap(hmap, "Test", strlen("Test"), "World");


	Vector pairs = GetAllPairsHashMap(hmap);

	for (u32 i = 0; i < pairs->size; i++) {
		Pair* pair = pairs->elements[i];
		printf("Key: %s, Value: %s\n", pair->first, pair->second);
	}

	DestroyHashMap(hmap);
	DestroyVector(pairs);
}

void EventHandlerThing(Application app, Event event) {
	EventDataKeyPressed key = event.data;
	//SPARK_LOG_DEBUG("Key pressed: %s", KeyToString(key->key));
}

void CreateEntities(Application app) {
	for (size_t i = 0; i < 10000; i++) {
		Entity e = CreateEntity(app->ecs);
		TestThing* data = SparkAllocate(sizeof(TestThing));
		data->name = "Hello";
		data->age = 20.0f;
		data->id = 1234567890;
		AddComponent(app->ecs, e, CreateComponent(SPARK_TRANSFORM_COMPONENT, "Transform", data, SparkFree));
	}
}

void QueryThing(Application app) {
	SparkVector components = SparkGetAllComponentsByType(app->ecs, SPARK_TRANSFORM_COMPONENT);
	for (u32 i = 0; i < components->size; i++) {
		Component component = components->elements[i];
		TestThing* test = component->data;
		SPARK_LOG_DEBUG("Name: %s", test->name);
		SPARK_LOG_DEBUG("Age: %f", test->age);
		SPARK_LOG_DEBUG("ID: %lld", test->id);
	}
	SparkDestroyVector(components);
}

void ResourceCreater(Application app) {
	Vertex vertices[] = { 
		MakeVertex(-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
		MakeVertex(0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f),
		MakeVertex(0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f),
		MakeVertex(-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f)
	};
	
	Resource res = CreateResourceApplication(
		app,
		StaticMeshResourceType,
		"Square",
		CreateStaticMesh(
			ArrayArg(vertices)
		)
	);

	StaticMesh mesh = res->data;

	for (size_t i = 0; i < mesh->vertex_count; i++) {
		Vertex curr_vertex = mesh->vertices[i];
		SPARK_LOG_DEBUG("Vertex %d: %f, %f, %f, %f, %f, %f, %f, %f", 
			i, 
			curr_vertex.position.x, 
			curr_vertex.position.y, 
			curr_vertex.position.z, 
			curr_vertex.normal.x, 
			curr_vertex.normal.y, 
			curr_vertex.normal.z, 
			curr_vertex.texcoord.x, 
			curr_vertex.texcoord.y);
	}

	RemoveResourceApplication(app, StaticMeshResourceType, "Square");
}

void ExitOnEscape(Application app, Event event) {
	EventDataKeyPressed kp = event.data;

	if (kp->key == SPARK_KEY_ESCAPE) {
		app->window->should_close = SPARK_TRUE;
	}
}

void TestIterator(Application app)
{
	HashMap hmap = DefaultHashMap();

	InsertHashMap(hmap, "Hello", strlen("Hello"), "World");
	InsertHashMap(hmap, "Goodbye", strlen("Goodbye"), "Goodbye");
	InsertHashMap(hmap, "Test", strlen("Test"), "World");


	HashMapIterator kit = CreateHashMapIterator(SPARK_ITERATOR_STATE_BEGIN, SPARK_HASHMAP_ITERATOR_TYPE_KEY, hmap);
	do {
		SPARK_LOG_DEBUG("Key: %s", GetCurrentHashMapIterator(kit));
	} while (IterateForwardHashMapIterator(kit) != SPARK_ITERATOR_STATE_END);

	HashMapIterator vit = CreateHashMapIterator(SPARK_ITERATOR_STATE_BEGIN, SPARK_HASHMAP_ITERATOR_TYPE_VALUE, hmap);
	do {
		SPARK_LOG_DEBUG("Value: %s", GetCurrentHashMapIterator(vit));
	} while (IterateForwardHashMapIterator(vit) != SPARK_ITERATOR_STATE_END);

	HashMapIterator pit = CreateHashMapIterator(SPARK_ITERATOR_STATE_BEGIN, SPARK_HASHMAP_ITERATOR_TYPE_PAIR, hmap);
	do {
		SPARK_LOG_DEBUG("Key: %s", ((Pair*)GetCurrentHashMapIterator(pit))->first);
		SPARK_LOG_DEBUG("Value: %s", ((Pair*)GetCurrentHashMapIterator(pit))->second);
	} while (IterateForwardHashMapIterator(pit) != SPARK_ITERATOR_STATE_END);

	DestroyHashMapIterator(kit);
	DestroyHashMapIterator(vit);
	DestroyHashMapIterator(pit);
	DestroyHashMap(hmap);
}

i32 main() {
	/* Create server */
	Application app = CreateApplication(
		CreateWindow(
			CreateWindowData("Hello", 1080, 1080, SPARK_FALSE)
		),
		3
	);

	server = CreateServer(app->thread_pool, 12345, server_receive_callback);

	client = CreateClient(app->thread_pool, "127.0.0.1", 12345, client_receive_callback);

	StartServer(server);
	ConnectClient(client);

	AddStartFunctionApplication(app, ResourceCreater, SPARK_UNTHREADED);
	AddStartFunctionApplication(app, TestGetPairs, SPARK_UNTHREADED);
	AddStartFunctionApplication(app, TestSerialization, SPARK_UNTHREADED);
	AddStartFunctionApplication(app, TestDeserialization, SPARK_UNTHREADED);
	AddStartFunctionApplication(app, CreateEntities, SPARK_UNTHREADED);
	AddEventFunctionApplication(app, SPARK_EVENT_KEY_PRESSED, ExitOnEscape, SPARK_UNTHREADED);
	AddStartFunctionApplication(app, TestIterator, SPARK_UNTHREADED);

	//AddUpdateFunctionApplication(app, update_send, (SparkPair){true, false});

	StartApplication(app);

	return 0;
}