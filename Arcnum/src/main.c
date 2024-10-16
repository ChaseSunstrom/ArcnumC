#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define SPARK_DEFINE_ALL_ALIASES
#include <spark.h>
#include <stdio.h>
#include <string.h>

#define SOME_CUSTOM_EVENT SPARK_EVENT_MAX_BIT

void_t KeyPressedFunction(Event event) {
	if (event.type == SPARK_EVENT_KEY_PRESSED) {
		EventDataKeyPressed key_press = event.data;
		SPARK_LOG_DEBUG("Key Pressed: %s", KeyToString(key_press->key));
	}
	else if (event.type == SPARK_EVENT_KEY_RELEASED | SOME_CUSTOM_EVENT) {
		EventDataKeyReleased key_press = event.data;
		SPARK_LOG_DEBUG("Key Released: %s", KeyToString(key_press->key));
	}
}

void_t MousePressedFunction(Event event) {
}

i32 main()
{
	Application app = CreateApplication(
		CreateWindow(
			CreateWindowData("Hello", 1000, 1000, SPARK_FALSE)
		)
	);

	AddEventFunctionApplication(app, SPARK_EVENT_KEY_PRESSED |
		                             SPARK_EVENT_KEY_RELEASED |
									 SOME_CUSTOM_EVENT, KeyPressedFunction);

	UpdateApplication(app);

	DestroyApplication(app);

	return 0;
}
