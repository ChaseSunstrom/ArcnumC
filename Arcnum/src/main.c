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

	CreateResourceApplication(app, StaticMeshResourceType, "Cube",
		CreateStaticMeshI(app, ArrayArg(vertices), ArrayArg(indices)));
}

void CreateShaders(Application app) {
	Shader vshader = CreateShader(app, SPARK_SHADER_VERTEX, "src/shader.vert");
	Shader fshader = CreateShader(app, SPARK_SHADER_FRAGMENT, "src/shader.frag");

	SparkGraphicsPipelineConfig gp = SparkCreateGraphicsPipelineConfig(app, vshader, fshader, SPARK_NULL, SPARK_NULL, SPARK_NULL, SPARK_NULL);

	CreateResourceApplication(app, SPARK_RESOURCE_TYPE_GRAPHICS_PIPELINE_CONFIG, "default", gp);
}

void ExitOnEscape(Application app, Event event) {
	EventDataKeyPressed kp = event.data;

	if (kp->key == SPARK_KEY_ESCAPE) {
		SparkStopApplication(app);
	}
}

typedef struct PositionComponent {
	 IVec3 pos;
} PositionComponent;

typedef struct VelocityComponent {
	IVec3 vel;
} VelocityComponent;

#define POS_COMPONENT "PositionComponent"
#define VEL_COMPONENT "VelocityComponent"

void CreateEntities(Application app) {
	for (size_t i = 0; i < 2000; i++) {
		Ecs ecs = app->ecs;
		Entity entity = CreateEntity(ecs);

		PositionComponent* pos = malloc(sizeof(PositionComponent));
		pos->pos = (SparkIVec3){ i, i, i };

		SparkComponent pos_component = CreateComponent(POS_COMPONENT, "Position", pos, free);
		AddComponent(ecs, entity, pos_component);

		if (i < 1000) {
			VelocityComponent* vel = malloc(sizeof(VelocityComponent));
			vel->vel = (SparkIVec3){ i, i, i };

			SparkComponent vel_component = CreateComponent(VEL_COMPONENT, "Velocity", vel, free);

			AddComponent(ecs, entity, vel_component);
		}
	}
}

void QueryEntities(Application app, Vector query) {
	if (!query)
		return;
	SPARK_LOG_DEBUG("Amount of entities with position and velocity: %d", query->size);
}

void QueryEntitiesWithPosition(Application app, Vector query) {
	if (!query)
		return;
	SPARK_LOG_DEBUG("Amount of entities with position: %d", query->size);
}

i32 main() {
	Application app = CreateApplication(
		CreateWindow(
			CreateWindowData("Hello", 1080, 1080, SPARK_FALSE, SPARK_PRESENT_MODE_MAILBOX)
		), 
	8);

	const_string_t component_types[] = { POS_COMPONENT, VEL_COMPONENT };
	Query movement_query = SparkCreateQuery(ArrayArg(component_types));

	const_string_t position_types[] = { POS_COMPONENT };
	Query position_query = SparkCreateQuery(ArrayArg(position_types));

	AddStartFunctionApplication(app, CreateEntities, SPARK_UNTHREADED);
	AddQueryFunctionApplication(app, movement_query, QueryEntities, SPARK_UNBLOCKED_PARRALLELISM);
	AddQueryFunctionApplication(app, position_query, QueryEntitiesWithPosition, SPARK_UNBLOCKED_PARRALLELISM);
	AddStartFunctionApplication(app, ResourceCreater, SPARK_UNBLOCKED_PARRALLELISM);
	AddStartFunctionApplication(app, CreateShaders, SPARK_UNBLOCKED_PARRALLELISM);
	AddEventFunctionApplication(app, SPARK_EVENT_KEY_PRESSED, ExitOnEscape, SPARK_UNBLOCKED_PARRALLELISM);

	StartApplication(app);

	return 0;
}