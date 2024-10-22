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
	if (SparkSendToServer(client, &envelope) != SPARK_SUCCESS) {
		printf("Failed to send data to server.\n");
	}
}

void TestSerialization(Application app) {
	TestThing test = { "Hello, hehehe", 20.0f, 1234567890 };

    SparkFileSerializer serializer = SparkCreateFileSerializer("test.bin");

    SparkSerialize(serializer, "Hello, World!", strlen("Hello, World!"));
    SparkSerialize(serializer, "Test, string!", strlen("Test, string!"));

    SparkSerialize(serializer, test.name, strlen(test.name));
    SparkSerialize(serializer, test.age);
	SparkSerialize(serializer, test.id);

    SparkDestroyFileSerializer(serializer);
}

void TestDeserialization(Application app) {
    SparkFileDeserializer deserializer = SparkCreateFileDeserializer("test.bin");

    const_string_t hello;
    const_string_t test;

    TestThing testt = { 0 };

    size_t hellos;
    size_t tests;

    size_t names;
    size_t ages;
    size_t ids;

    SparkGetDeserializedStringA(deserializer, &hello, &hellos);
    SparkGetDeserializedStringA(deserializer, &test, &tests);

    SparkGetDeserializedStringA(deserializer, &testt.name, &names);
    SparkDeserializeTrivial(deserializer, &testt.age, sizeof(f32));
	SparkDeserializeTrivial(deserializer, &testt.id, sizeof(i64));

    SPARK_LOG_DEBUG("First string: %s, Size: %d", hello, hellos);
    SPARK_LOG_DEBUG("Second string: %s, Size: %d", test, tests);

	SPARK_LOG_DEBUG("Name: %s, Size: %d", testt.name, names);
	SPARK_LOG_DEBUG("Age: %lf, Size: %d", testt.age, 4);
	SPARK_LOG_DEBUG("ID: %d, Size: %d", testt.id, 8);

    SparkDestroyFileDeserializer(deserializer);

    SparkFree(hello);
    SparkFree(test);
    SparkFree(testt.name);
}

i32 main() {
    /* Create server */ 
    Application app = CreateApplication(
        CreateWindow(
            CreateWindowData("Hello", 1080, 1080, SPARK_FALSE)
        ),
        8
    );



    SparkServer server = SparkCreateServer(app->thread_pool, 12345, server_receive_callback);
    if (!server) {
        printf("Failed to create server.\n");
        return 1;
    }

    if (SparkStartServer(server) != SPARK_SUCCESS) {
        printf("Failed to start server.\n");
        SparkDestroyServer(server);
        return 1;
    }

    /* Create client */
    client = SparkCreateClient(app->thread_pool, "127.0.0.1", 12345, client_receive_callback);

    if (!client) {
        printf("Failed to create client.\n");
        SparkDestroyServer(server);
        return 1;
    }

    if (SparkConnectClient(client) != SPARK_SUCCESS) {
        printf("Failed to connect client.\n");
        SparkDestroyClient(client);
        SparkDestroyServer(server);
        return 1;
    }

    envelope.type = SPARK_ENVELOPE_TYPE_DATA;
    const_string_t message = "Hello, Server!";
    envelope.packet.size = strlen(message) + 1;
    envelope.packet.data = (SparkBuffer)message;

    AddStartFunctionApplication(app, TestSerialization);
    AddStartFunctionApplication(app, TestDeserialization);
    AddUpdateFunctionApplication(app, update_send);

    StartApplication(app);

    SparkDestroyClient(client);
    SparkDestroyServer(server);

    return 0;
}