/* main.c */
#define SPARK_DEFINE_ALL_ALIASES
#include "spark.h"
#include <stdbool.h>

void ResourceCreater(Application app) {
	Vertex vertices[] = {
		// Front face
		MakeVertex(-0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f),
		MakeVertex(0.5f, -0.5f,  0.5f,  0.0f,  1.0f,  1.0f,  1.0f, 0.0f),
		MakeVertex(0.5f,  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  1.0f, 1.0f),
		MakeVertex(-0.5f,  0.5f,  0.5f,  0.4f,  0.0f,  1.0f,  0.0f, 1.0f),

		// Back face
		MakeVertex(-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f),
		MakeVertex(-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f),
		MakeVertex(0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f),
		MakeVertex(0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f),

		// Left face
		MakeVertex(-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f),
		MakeVertex(-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f),
		MakeVertex(-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f),
		MakeVertex(-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f),

		// Right face
		MakeVertex(0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  1.0f,  1.0f, 0.0f),
		MakeVertex(0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f),
		MakeVertex(0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,  0.0f, 1.0f),
		MakeVertex(0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f),

		// Top face
		MakeVertex(-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  1.0f,  0.0f, 1.0f),
		MakeVertex(-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f),
		MakeVertex(0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  1.0f, 0.0f),
		MakeVertex(0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f),

		// Bottom face
		MakeVertex(-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f),
		MakeVertex(0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f),
		MakeVertex(0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f),
		MakeVertex(-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f)
	};

	SparkU16 indices[] = {
		// Front face
		0, 1, 2, 2, 3, 0,

		// Back face
		4, 5, 6, 6, 7, 4,

		// Left face
		8, 9,10, 10,11, 8,

		// Right face
	    12,13,14, 14,15,12,

	    // Top face
		16,17,18, 18,19,16,

		// Bottom face
		20,21,22, 22,23,20,
	};

	Resource res =
		CreateResourceApplication(app, StaticMeshResourceType, "Cube",
			CreateStaticMeshI(app, ArrayArg(vertices), ArrayArg(indices)));

	StaticMesh mesh = res->data;

	for (size_t i = 0; i < mesh->vertex_count; i++) {
		Vertex curr_vertex = mesh->vertices[i];
		LogDebug("Vertex %d: %f, %f, %f, %f, %f, %f, %f, %f", i,
			curr_vertex.position.x, curr_vertex.position.y,
			curr_vertex.position.z, curr_vertex.normal.x, curr_vertex.normal.y,
			curr_vertex.normal.z, curr_vertex.texcoord.x,
			curr_vertex.texcoord.y);
	}
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
		SparkStopApplication(app);
	}
}

typedef struct PositionComponent {
	SparkIVec3 pos;
} PositionComponent;

typedef struct VelocityComponent {
	SparkIVec3 vel;
} VelocityComponent;

#define POS_COMPONENT "PositionComponent"
#define VEL_COMPONENT "VelocityComponent"

void CreateEntities(SparkApplication app) {
	for (size_t i = 0; i < 2000; i++) {
		SparkEcs ecs = app->ecs;
		SparkEntity entity = SparkCreateEntity(ecs);

		PositionComponent* pos = malloc(sizeof(PositionComponent));
		pos->pos = (SparkIVec3){ i, i, i };

		SparkComponent pos_component = SparkCreateComponent(POS_COMPONENT, "Position", pos, free);
		SparkAddComponent(ecs, entity, pos_component);

		if (i < 1000) {
			VelocityComponent* vel = malloc(sizeof(VelocityComponent));
			vel->vel = (SparkIVec3){ i, i, i };

			SparkComponent vel_component = SparkCreateComponent(VEL_COMPONENT, "Velocity", vel, free);

			SparkAddComponent(ecs, entity, vel_component);
		}
	}
}

void QueryEntities(SparkApplication app, SparkVector query) {
	SPARK_LOG_DEBUG("Amount of entities with position and velocity: %d", query->size);
}

void QueryEntitiesWithPosition(SparkApplication app, SparkVector query) {
	SPARK_LOG_DEBUG("Amount of entities with position: %d", query->size);
}

i32 main() {
	Application app = CreateApplication(
		CreateWindow(
			CreateWindowData("Hello", 1080, 1080, SPARK_FALSE, SPARK_PRESENT_MODE_MAILBOX)
		), 
	8);

	SparkConstString component_types[] = { POS_COMPONENT, VEL_COMPONENT };
	SparkQuery movement_query = SparkCreateQuery(component_types, 2);

	SparkConstString position_types[] = { POS_COMPONENT };
	SparkQuery position_query = SparkCreateQuery(position_types, 1);

	AddStartFunctionApplication(app, CreateEntities, SPARK_UNTHREADED);
	AddQueryFunctionApplication(app, movement_query, QueryEntities, SPARK_UNTHREADED);
	AddQueryFunctionApplication(app, position_query, QueryEntitiesWithPosition, SPARK_UNTHREADED);
	AddStartFunctionApplication(app, ResourceCreater, SPARK_UNBLOCKED_PARRALLELISM);
	AddStartFunctionApplication(app, CreateShaders, SPARK_UNTHREADED);
	AddEventFunctionApplication(app, SPARK_EVENT_KEY_PRESSED, ExitOnEscape, SPARK_UNBLOCKED_PARRALLELISM);

	StartApplication(app);

	return 0;
}