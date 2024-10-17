#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define SPARK_DEFINE_ALL_ALIASES
#include <spark.h>
#include <stdio.h>
#include <string.h>

void_t KeyPressedFunction(Application app, Event event) {
	if (event.type == SPARK_EVENT_KEY_PRESSED) {
		EventDataKeyPressed key_press = event.data;
		SPARK_LOG_DEBUG("Key Pressed: %s", KeyToString(key_press->key));
	}
	else if (event.type == SPARK_EVENT_KEY_RELEASED) {
		EventDataKeyReleased key_press = event.data;
		SPARK_LOG_DEBUG("Key Released: %s", KeyToString(key_press->key));
	}
}

void_t MousePressedFunction(Application app, Event event) {
	if (event.type == SPARK_EVENT_MOUSE_BUTTON_PRESSED) {
		EventDataMouseButtonPressed mouse_press = event.data;
		SPARK_LOG_DEBUG("Mouse Button Pressed: %s", MouseButtonToString(mouse_press->button));
	}
	else if (event.type == SPARK_EVENT_MOUSE_BUTTON_RELEASED) {
		EventDataMouseButtonReleased mouse_press = event.data;
		SPARK_LOG_DEBUG("Mouse Button Released: %s", MouseButtonToString(mouse_press->button));
	}
}

void_t StartFunction(Application app) {
	for (size_t i = 0; i < 100; i++) {
		Entity entity = CreateEntity(app->ecs);
		Component component = CreateComponent("Transform", "Transform", "TRANSFORM_COMPONENT", SPARK_NULL);
		AddComponent(app->ecs, entity, component);
		SPARK_LOG_DEBUG("Created entity: %d, Added component: %s", i, GetComponent(app->ecs, entity, "Transform", "Transform")->data);
	}

	for (size_t i = 0; i < 50; i++) {
		DestroyEntity(app->ecs, i);
		SPARK_LOG_DEBUG("Destroyed entity: %d", i);
	}

	for (size_t i = 0; i < 1000; i++) {
		CreateEntity(app->ecs);
		SPARK_LOG_DEBUG("Created entity: %d", i);
	}
}

i32 main() {
	Application app = CreateApplication(
		CreateWindow(
			CreateWindowData("Hello", 1000, 1000, SPARK_FALSE)
		)
	);

	AddStartFunctionApplication(app, StartFunction);

	AddEventFunctionApplication(app, SPARK_EVENT_KEY_PRESSED | SPARK_EVENT_KEY_RELEASED, KeyPressedFunction);
	AddEventFunctionApplication(app, SPARK_EVENT_MOUSE_BUTTON_PRESSED | SPARK_EVENT_MOUSE_BUTTON_RELEASED, MousePressedFunction);



	StartApplication(app);

	return 0;
}