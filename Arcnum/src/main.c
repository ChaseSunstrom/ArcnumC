/* main.c */
#define SPARK_DEFINE_ALL_ALIASES
#include "spark.h"

/* Server receive callback */
void server_receive_callback(Server server, ClientConnection client, Envelope* envelope) {
    printf("Server received data from client.\n");
    /* Echo the data back to the client */
    SparkBroadcast(server, envelope);
}

/* Client receive callback */
void client_receive_callback(Client  client, Envelope* envelope) {
    printf("Client received data from server.\n");
    /* Process the data */
}

static Client client = NULL;

static Envelope envelope;

typedef struct {
	char* name;
    f32 age;
    i64 id;
} TestThing;

void update_send(Application app) {
	if (SendToServer(client, &envelope) != SPARK_SUCCESS) {
		printf("Failed to send data to server.\n");
	}
}

void TestSerialization(Application app) {
	TestThing test = { "Hello, hehehe", 20.0f, 1234567890 };

    FileSerializer serializer = CreateFileSerializer("test.bin");

    Serialize(serializer, "Hello, World!");
    Serialize(serializer, "Test, string!");
    Serialize(serializer, test.name);
    Serialize(serializer, test.age);
	Serialize(serializer, test.id);

    DestroyFileSerializer(serializer);
}

void TestDeserialization(Application app) {
    FileDeserializer deserializer = CreateFileDeserializer("test.bin");

    const_string_t hello;
    const_string_t test;

    TestThing testt = { 0 };

    size_t hellos;
    size_t tests;

    size_t names;
    size_t ages;
    size_t ids;

    Deserialize(deserializer, hello, hellos);
    Deserialize(deserializer, test, tests);
    Deserialize(deserializer, testt.name, names);
    Deserialize(deserializer, testt.age);
    Deserialize(deserializer, testt.id);

    SPARK_LOG_DEBUG("First string: %s, Size: %d", hello, hellos);
    SPARK_LOG_DEBUG("Second string: %s, Size: %d", test, tests);

	SPARK_LOG_DEBUG("Name: %s, Size: %d", testt.name, names);
	SPARK_LOG_DEBUG("Age: %lf, Size: %d", testt.age, sizeof(testt.age));
	SPARK_LOG_DEBUG("ID: %d, Size: %d", testt.id, sizeof(testt.id));

    DestroyFileDeserializer(deserializer);

    Free(hello);
    Free(test);
    Free(testt.name);
}

i32 main() {
    /* Create server */ 
    Application app = CreateApplication(
        CreateWindow(
            CreateWindowData("Hello", 1080, 1080, SPARK_FALSE)
        ),
        8
    );

    Server server = CreateServer(app->thread_pool, 12345, server_receive_callback);

    client = CreateClient(app->thread_pool, "127.0.0.1", 12345, client_receive_callback);

    StartServer(server);    
    ConnectClient(client);

    envelope.type = SPARK_ENVELOPE_TYPE_DATA;
    const_string_t message = "Hello, Server!";
    envelope.packet.size = strlen(message) + 1;
    envelope.packet.data = (SparkBuffer)message;

    AddStartFunctionApplication(app, TestSerialization);
    AddStartFunctionApplication(app, TestDeserialization);
    AddUpdateFunctionApplication(app, update_send);

    StartApplication(app);

    DestroyClient(client);
    DestroyServer(server);

    return 0;
}