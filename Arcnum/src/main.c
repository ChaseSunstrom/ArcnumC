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

i32 main() {
	Application app = CreateApplication(
		CreateWindow(
			CreateWindowData("Hello", 1000, 1000, SPARK_FALSE)
		)
	);

	AddEventFunctionApplication(app, SPARK_EVENT_KEY_PRESSED |
		                             SPARK_EVENT_KEY_RELEASED, KeyPressedFunction);

	AddEventFunctionApplication(app, SPARK_EVENT_MOUSE_BUTTON_PRESSED |
		                             SPARK_EVENT_MOUSE_BUTTON_RELEASED, MousePressedFunction);




	UpdateApplication(app);

	DestroyApplication(app);

	return 0;
}
