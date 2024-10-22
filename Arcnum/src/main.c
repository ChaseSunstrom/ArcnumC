/* main.c */
#define SPARK_DEFINE_ALL_ALIASES
#include "spark.h"


typedef struct {
    char* name;
    f32 age;
    i64 id;
} TestThing;


/* Server receive callback */
void server_receive_callback(Server server, ClientConnection client, Envelope* envelope) {
    printf("Server received data from client.\n");

    TestThing* test = envelope->packet.data;

	printf("Name: %s\n", test->name);
	printf("Age: %f\n", test->age);
	printf("ID: %lld\n", test->id);

    /* Echo the data back to the client */
    SparkBroadcast(server, envelope);

    Free(test->name);
}

/* Client receive callback */
void client_receive_callback(Client  client, Envelope* envelope) {
    printf("Client received data from server.\n");
    /* Process the data */
}

static Client client = NULL;

static Envelope envelope;

void update_send(Application app) {
	if (SendToServer(client, &envelope) != SPARK_SUCCESS) {
		printf("Failed to send data to server.\n");
	}
}

void TestSerialization(Application app) {
}

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

void TestDeserialization(Application app) {
    TestThing test = { "Hello, hehehe", 20.0f, 1234567890 };
    FileSerializer serializer = CreateFileSerializer("test.bin");
    SerializeTestThing(serializer, test);
    
    DestroyFileSerializer(serializer);
    FileDeserializer deserializer = CreateFileDeserializer("test.bin");
    TestThing test2 = DeserializeTestThing(deserializer);
    DestroyFileDeserializer(deserializer);

	envelope.type = SPARK_ENVELOPE_TYPE_DATA;
	envelope.packet.size = sizeof(TestThing);
	envelope.packet.data = (SparkBuffer)&test2;

	if (SendToServer(client, &envelope) != SPARK_SUCCESS) {
		printf("Failed to send data to server.\n");
	}
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

    AddStartFunctionApplication(app, TestSerialization);
    AddStartFunctionApplication(app, TestDeserialization);
   // AddUpdateFunctionApplication(app, update_send);

    StartApplication(app);

    DestroyClient(client);
    DestroyServer(server);

    return 0;
}