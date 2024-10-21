/* main.c */
#define SPARK_DEFINE_ALL_ALIASES
#include "spark.h"

/* Server receive callback */
void server_receive_callback(SparkServer server, SparkClientConnection client, SparkEnvelope* envelope) {
    printf("Server received data from client.\n");
    /* Echo the data back to the client */
    SparkSendToClient(server, client, envelope);
}

/* Client receive callback */
void client_receive_callback(SparkClient client, SparkEnvelope* envelope) {
    printf("Client received data from server.\n");
    /* Process the data */
}

static SparkClient client = NULL;

void update_send(Application app) {
	SparkEnvelope envelope;
	envelope.type = SPARK_ENVELOPE_TYPE_DATA;
	const char* message = "Hello, Server!";
	envelope.packet.size = strlen(message) + 1;
	envelope.packet.data = (SparkBuffer)message;

	if (SparkSendToServer(client, &envelope) != SPARK_SUCCESS) {
		printf("Failed to send data to server.\n");
	}
}

int main() {
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

    AddUpdateFunctionApplication(app, update_send);

    StartApplication(app);

    /* Clean up */
    SparkDisconnectClient(client);
    SparkDestroyClient(client);
    SparkStopServer(server);
    SparkDestroyServer(server);

    return 0;
}
