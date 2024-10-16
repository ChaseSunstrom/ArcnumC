
#define SPARK_IMPLEMENTATION
#include "spark.h"
#include "spark_shader.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

#pragma region ENUM

SPARKAPI SparkConstString SparkTypeToString(SparkType type) {
	switch (type) {
		/* False, None, Null*/
	case SPARK_NONE: return "SPARK_NONE";
		/* True, Success, Valid */
	case SPARK_SUCCESS: return "SPARK_SUCCESS";
		/* Invalid, */
	case SPARK_INVALID: return "SPARK_INVALID";
	case SPARK_ERROR: return "SPARK_ERROR";
	case SPARK_UNKNOWN: return "SPARK_UNKNOWN";
	case SPARK_PENDING: return "SPARK_PENDING";
	case SPARK_IN_PROGRESS: return "SPARK_IN_PROGRESS";
	case SPARK_COMPLETE: return "SPARK_COMPLETE";
	case SPARK_TIMEOUT: return "SPARK_TIMEOUT";
	case SPARK_CANCELLED: return "SPARK_CANCELLED";
	case SPARK_NOT_IMPLEMENTED: return "SPARK_NOT_IMPLEMENTED";
	case SPARK_ACCESS_DENIED: return "SPARK_ACCESS_DENIED";
	case SPARK_NOT_FOUND: return "SPARK_NOT_FOUND";
	case SPARK_BUSY: return "SPARK_BUSY";
	case SPARK_OVERLOADED: return "SPARK_OVERLOADED";
	case SPARK_DISCONNECTED: return "SPARK_DISCONNECTED";
	case SPARK_CONNECTED: return "SPARK_CONNECTED";
	case SPARK_RETRY: return "SPARK_RETRY";
	case SPARK_DEPRECATED: return "SPARK_DEPRECATED";
	case SPARK_UNSUPPORTED: return "SPARK_UNSUPPORTED";
	case SPARK_INITIALIZED: return "SPARK_INITIALIZED";
	case SPARK_UNINITIALIZED: return "SPARK_UNINITIALIZED";
	case SPARK_ENABLED: return "SPARK_ENABLED";
	case SPARK_DISABLED: return "SPARK_DISABLED";
	case SPARK_READ_ONLY: return "SPARK_READ_ONLY";
	case SPARK_WRITE_ONLY: return "SPARK_WRITE_ONLY";
	case SPARK_READ_WRITE: return "SPARK_READ_WRITE";
	case SPARK_SUCCESS_PARTIAL: return "SPARK_SUCCESS_PARTIAL";
	case SPARK_INVALID_ARGUMENT: return "SPARK_INVALID_ARGUMENT";
	case SPARK_OUT_OF_MEMORY: return "SPARK_OUT_OF_MEMORY";
	case SPARK_OVERFLOW: return "SPARK_OVERFLOW";
	case SPARK_UNDERFLOW: return "SPARK_UNDERFLOW";
	case SPARK_END_OF_FILE: return "SPARK_END_OF_FILE";
	case SPARK_PERMISSION_DENIED: return "SPARK_PERMISSION_DENIED";
	case SPARK_BAD_REQUEST: return "SPARK_BAD_REQUEST";
	case SPARK_CONFLICT: return "SPARK_CONFLICT";
	case SPARK_PRECONDITION_FAILED: return "SPARK_PRECONDITION_FAILED";
	default: return "UNKNOWN_SPARK_TYPE";
	}
}

SPARKAPI SparkType SparkStringToType(SparkConstString string) {
	if (strcmp(string, "SPARK_FALSE") == 0) return SPARK_FALSE;
	else if (strcmp(string, "SPARK_TRUE") == 0) return SPARK_TRUE;
	else if (strcmp(string, "SPARK_SUCCESS") == 0) return SPARK_SUCCESS;
	else if (strcmp(string, "SPARK_FAILURE") == 0) return SPARK_FAILURE;
	else if (strcmp(string, "SPARK_ERROR") == 0) return SPARK_ERROR;
	else if (strcmp(string, "SPARK_VALID") == 0) return SPARK_VALID;
	else if (strcmp(string, "SPARK_INVALID") == 0) return SPARK_INVALID;
	else if (strcmp(string, "SPARK_NULL") == 0) return SPARK_NULL;
	else if (strcmp(string, "SPARK_NONE") == 0) return SPARK_NONE;
	else if (strcmp(string, "SPARK_UNKNOWN") == 0) return SPARK_UNKNOWN;
	else if (strcmp(string, "SPARK_PENDING") == 0) return SPARK_PENDING;
	else if (strcmp(string, "SPARK_IN_PROGRESS") == 0) return SPARK_IN_PROGRESS;
	else if (strcmp(string, "SPARK_COMPLETE") == 0) return SPARK_COMPLETE;
	else if (strcmp(string, "SPARK_TIMEOUT") == 0) return SPARK_TIMEOUT;
	else if (strcmp(string, "SPARK_CANCELLED") == 0) return SPARK_CANCELLED;
	else if (strcmp(string, "SPARK_NOT_IMPLEMENTED") == 0) return SPARK_NOT_IMPLEMENTED;
	else if (strcmp(string, "SPARK_ACCESS_DENIED") == 0) return SPARK_ACCESS_DENIED;
	else if (strcmp(string, "SPARK_NOT_FOUND") == 0) return SPARK_NOT_FOUND;
	else if (strcmp(string, "SPARK_BUSY") == 0) return SPARK_BUSY;
	else if (strcmp(string, "SPARK_OVERLOADED") == 0) return SPARK_OVERLOADED;
	else if (strcmp(string, "SPARK_DISCONNECTED") == 0) return SPARK_DISCONNECTED;
	else if (strcmp(string, "SPARK_CONNECTED") == 0) return SPARK_CONNECTED;
	else if (strcmp(string, "SPARK_RETRY") == 0) return SPARK_RETRY;
	else if (strcmp(string, "SPARK_DEPRECATED") == 0) return SPARK_DEPRECATED;
	else if (strcmp(string, "SPARK_UNSUPPORTED") == 0) return SPARK_UNSUPPORTED;
	else if (strcmp(string, "SPARK_INITIALIZED") == 0) return SPARK_INITIALIZED;
	else if (strcmp(string, "SPARK_UNINITIALIZED") == 0) return SPARK_UNINITIALIZED;
	else if (strcmp(string, "SPARK_ENABLED") == 0) return SPARK_ENABLED;
	else if (strcmp(string, "SPARK_DISABLED") == 0) return SPARK_DISABLED;
	else if (strcmp(string, "SPARK_READ_ONLY") == 0) return SPARK_READ_ONLY;
	else if (strcmp(string, "SPARK_WRITE_ONLY") == 0) return SPARK_WRITE_ONLY;
	else if (strcmp(string, "SPARK_READ_WRITE") == 0) return SPARK_READ_WRITE;
	else if (strcmp(string, "SPARK_SUCCESS_PARTIAL") == 0) return SPARK_SUCCESS_PARTIAL;
	else if (strcmp(string, "SPARK_INVALID_ARGUMENT") == 0) return SPARK_INVALID_ARGUMENT;
	else if (strcmp(string, "SPARK_OUT_OF_MEMORY") == 0) return SPARK_OUT_OF_MEMORY;
	else if (strcmp(string, "SPARK_OVERFLOW") == 0) return SPARK_OVERFLOW;
	else if (strcmp(string, "SPARK_UNDERFLOW") == 0) return SPARK_UNDERFLOW;
	else if (strcmp(string, "SPARK_END_OF_FILE") == 0) return SPARK_END_OF_FILE;
	else if (strcmp(string, "SPARK_PERMISSION_DENIED") == 0) return SPARK_PERMISSION_DENIED;
	else if (strcmp(string, "SPARK_BAD_REQUEST") == 0) return SPARK_BAD_REQUEST;
	else if (strcmp(string, "SPARK_CONFLICT") == 0) return SPARK_CONFLICT;
	else if (strcmp(string, "SPARK_PRECONDITION_FAILED") == 0) return SPARK_PRECONDITION_FAILED;
	else return SPARK_UNKNOWN;
}

SPARKAPI SparkConstString SparkErrorToString(SparkError error) {
	switch (error) {
	case SPARK_ERROR_NONE: return "SPARK_ERROR_NONE";
	case SPARK_ERROR_UNKNOWN: return "SPARK_ERROR_UNKNOWN";
	case SPARK_ERROR_INVALID: return "SPARK_ERROR_INVALID";
	case SPARK_ERROR_NULL: return "SPARK_ERROR_NULL";
	case SPARK_ERROR_NOT_FOUND: return "SPARK_ERROR_NOT_FOUND";
	case SPARK_ERROR_NOT_IMPLEMENTED: return "SPARK_ERROR_NOT_IMPLEMENTED";
	case SPARK_ERROR_ACCESS_DENIED: return "SPARK_ERROR_ACCESS_DENIED";
	case SPARK_ERROR_BUSY: return "SPARK_ERROR_BUSY";
	case SPARK_ERROR_OVERLOADED: return "SPARK_ERROR_OVERLOADED";
	case SPARK_ERROR_DISCONNECTED: return "SPARK_ERROR_DISCONNECTED";
	case SPARK_ERROR_TIMEOUT: return "SPARK_ERROR_TIMEOUT";
	case SPARK_ERROR_CANCELLED: return "SPARK_ERROR_CANCELLED";
	case SPARK_ERROR_RETRY: return "SPARK_ERROR_RETRY";
	case SPARK_ERROR_UNSUPPORTED: return "SPARK_ERROR_UNSUPPORTED";
	case SPARK_ERROR_DEPRECATED: return "SPARK_ERROR_DEPRECATED";
	case SPARK_ERROR_UNINITIALIZED: return "SPARK_ERROR_UNINITIALIZED";
	case SPARK_ERROR_DISABLED: return "SPARK_ERROR_DISABLED";
	case SPARK_ERROR_READ_ONLY: return "SPARK_ERROR_READ_ONLY";
	case SPARK_ERROR_WRITE_ONLY: return "SPARK_ERROR_WRITE_ONLY";
	case SPARK_ERROR_OUT_OF_MEMORY: return "SPARK_ERROR_OUT_OF_MEMORY";
	case SPARK_ERROR_OVERFLOW: return "SPARK_ERROR_OVERFLOW";
	case SPARK_ERROR_UNDERFLOW: return "SPARK_ERROR_UNDERFLOW";
	case SPARK_ERROR_END_OF_FILE: return "SPARK_ERROR_END_OF_FILE";
	case SPARK_ERROR_PERMISSION_DENIED: return "SPARK_ERROR_PERMISSION_DENIED";
	case SPARK_ERROR_BAD_REQUEST: return "SPARK_ERROR_BAD_REQUEST";
	case SPARK_ERROR_CONFLICT: return "SPARK_ERROR_CONFLICT";
	case SPARK_ERROR_PRECONDITION_FAILED: return "SPARK_ERROR_PRECONDITION_FAILED";
	case SPARK_ERROR_INVALID_ARGUMENT: return "SPARK_ERROR_INVALID_ARGUMENT";
	case SPARK_ERROR_INVALID_STATE: return "SPARK_ERROR_INVALID_STATE";
	case SPARK_ERROR_INVALID_FUNCTION_CALL: return "SPARK_ERROR_INVALID_FUNCTION_CALL";
	default: return "UNKNOWN_SPARK_ERROR";
	}
}

SPARKAPI SparkError SparkStringToError(SparkConstString string) {
	if (strcmp(string, "SPARK_ERROR_NONE") == 0) return SPARK_ERROR_NONE;
	else if (strcmp(string, "SPARK_ERROR_UNKNOWN") == 0) return SPARK_ERROR_UNKNOWN;
	else if (strcmp(string, "SPARK_ERROR_INVALID") == 0) return SPARK_ERROR_INVALID;
	else if (strcmp(string, "SPARK_ERROR_NULL") == 0) return SPARK_ERROR_NULL;
	else if (strcmp(string, "SPARK_ERROR_NOT_FOUND") == 0) return SPARK_ERROR_NOT_FOUND;
	else if (strcmp(string, "SPARK_ERROR_NOT_IMPLEMENTED") == 0) return SPARK_ERROR_NOT_IMPLEMENTED;
	else if (strcmp(string, "SPARK_ERROR_ACCESS_DENIED") == 0) return SPARK_ERROR_ACCESS_DENIED;
	else if (strcmp(string, "SPARK_ERROR_BUSY") == 0) return SPARK_ERROR_BUSY;
	else if (strcmp(string, "SPARK_ERROR_OVERLOADED") == 0) return SPARK_ERROR_OVERLOADED;
	else if (strcmp(string, "SPARK_ERROR_DISCONNECTED") == 0) return SPARK_ERROR_DISCONNECTED;
	else if (strcmp(string, "SPARK_ERROR_TIMEOUT") == 0) return SPARK_ERROR_TIMEOUT;
	else if (strcmp(string, "SPARK_ERROR_CANCELLED") == 0) return SPARK_ERROR_CANCELLED;
	else if (strcmp(string, "SPARK_ERROR_RETRY") == 0) return SPARK_ERROR_RETRY;
	else if (strcmp(string, "SPARK_ERROR_UNSUPPORTED") == 0) return SPARK_ERROR_UNSUPPORTED;
	else if (strcmp(string, "SPARK_ERROR_DEPRECATED") == 0) return SPARK_ERROR_DEPRECATED;
	else if (strcmp(string, "SPARK_ERROR_UNINITIALIZED") == 0) return SPARK_ERROR_UNINITIALIZED;
	else if (strcmp(string, "SPARK_ERROR_DISABLED") == 0) return SPARK_ERROR_DISABLED;
	else if (strcmp(string, "SPARK_ERROR_READ_ONLY") == 0) return SPARK_ERROR_READ_ONLY;
	else if (strcmp(string, "SPARK_ERROR_WRITE_ONLY") == 0) return SPARK_ERROR_WRITE_ONLY;
	else if (strcmp(string, "SPARK_ERROR_OUT_OF_MEMORY") == 0) return SPARK_ERROR_OUT_OF_MEMORY;
	else if (strcmp(string, "SPARK_ERROR_OVERFLOW") == 0) return SPARK_ERROR_OVERFLOW;
	else if (strcmp(string, "SPARK_ERROR_UNDERFLOW") == 0) return SPARK_ERROR_UNDERFLOW;
	else if (strcmp(string, "SPARK_ERROR_END_OF_FILE") == 0) return SPARK_ERROR_END_OF_FILE;
	else if (strcmp(string, "SPARK_ERROR_PERMISSION_DENIED") == 0) return SPARK_ERROR_PERMISSION_DENIED;
	else if (strcmp(string, "SPARK_ERROR_BAD_REQUEST") == 0) return SPARK_ERROR_BAD_REQUEST;
	else if (strcmp(string, "SPARK_ERROR_CONFLICT") == 0) return SPARK_ERROR_CONFLICT;
	else if (strcmp(string, "SPARK_ERROR_PRECONDITION_FAILED") == 0) return SPARK_ERROR_PRECONDITION_FAILED;
	else if (strcmp(string, "SPARK_ERROR_INVALID_ARGUMENT") == 0) return SPARK_ERROR_INVALID_ARGUMENT;
	else if (strcmp(string, "SPARK_ERROR_INVALID_STATE") == 0) return SPARK_ERROR_INVALID_STATE;
	else if (strcmp(string, "SPARK_ERROR_INVALID_FUNCTION_CALL") == 0) return SPARK_ERROR_INVALID_FUNCTION_CALL;
	else return SPARK_ERROR_UNKNOWN;
}

SPARKAPI SparkConstString SparkResultToString(SparkResult result) {
	switch (result) {
	case SPARK_SUCCESS: return "SPARK_SUCCESS";
	case SPARK_FAILURE: return "SPARK_FAILURE";
	default: "SPARK_INVALID";
	}
}

SPARKAPI SparkResult SparkStringToResult(SparkConstString string) {
	if (strcmp(string, "SPARK_SUCCESS") == 0) return SPARK_SUCCESS;
	else if (strcmp(string, "SPARK_FAILURE") == 0) return SPARK_FAILURE;
	else return SPARK_INVALID;
}

SPARKAPI SparkConstString SparkAccessToString(SparkAccess access) {
	switch (access) {
	case SPARK_ACCESS_NONE: return "SPARK_ACCESS_NONE";
	case SPARK_ACCESS_READ: return "SPARK_ACCESS_READ";
	case SPARK_ACCESS_WRITE: return "SPARK_ACCESS_WRITE";
	case SPARK_ACCESS_READ_WRITE: return "SPARK_ACCESS_READ_WRITE";
	default: return "UNKNOWN_SPARK_ACCESS";
	}
}

SPARKAPI SparkAccess SparkStringToAccess(SparkConstString string) {
	if (strcmp(string, "SPARK_ACCESS_NONE") == 0) return SPARK_ACCESS_NONE;
	else if (strcmp(string, "SPARK_ACCESS_READ") == 0) return SPARK_ACCESS_READ;
	else if (strcmp(string, "SPARK_ACCESS_WRITE") == 0) return SPARK_ACCESS_WRITE;
	else if (strcmp(string, "SPARK_ACCESS_READ_WRITE") == 0) return SPARK_ACCESS_READ_WRITE;
	else return SPARK_ACCESS_NONE;
}

SPARKAPI SparkConstString SparkMouseButtonToString(SparkMouseButton button) {
	switch (button) {
		/* Left */
	case SPARK_MOUSE_BUTTON_1: return "SPARK_MOUSE_BUTTON_1";
		/* Right */
	case SPARK_MOUSE_BUTTON_2: return "SPARK_MOUSE_BUTTON_2";
		/* Middle */
	case SPARK_MOUSE_BUTTON_3: return "SPARK_MOUSE_BUTTON_3";
	case SPARK_MOUSE_BUTTON_4: return "SPARK_MOUSE_BUTTON_4";
	case SPARK_MOUSE_BUTTON_5: return "SPARK_MOUSE_BUTTON_5";
	case SPARK_MOUSE_BUTTON_6: return "SPARK_MOUSE_BUTTON_6";
	case SPARK_MOUSE_BUTTON_7: return "SPARK_MOUSE_BUTTON_7";
	case SPARK_MOUSE_BUTTON_8: return "SPARK_MOUSE_BUTTON_8";
	default: return "UNKNOWN_SPARK_MOUSE_BUTTON";
	}
}

SPARKAPI SparkMouseButton SparkStringToMouseButton(SparkConstString string) {
	if (strcmp(string, "SPARK_MOUSE_BUTTON_1") == 0) return SPARK_MOUSE_BUTTON_1;
	else if (strcmp(string, "SPARK_MOUSE_BUTTON_2") == 0) return SPARK_MOUSE_BUTTON_2;
	else if (strcmp(string, "SPARK_MOUSE_BUTTON_3") == 0) return SPARK_MOUSE_BUTTON_3;
	else if (strcmp(string, "SPARK_MOUSE_BUTTON_4") == 0) return SPARK_MOUSE_BUTTON_4;
	else if (strcmp(string, "SPARK_MOUSE_BUTTON_5") == 0) return SPARK_MOUSE_BUTTON_5;
	else if (strcmp(string, "SPARK_MOUSE_BUTTON_6") == 0) return SPARK_MOUSE_BUTTON_6;
	else if (strcmp(string, "SPARK_MOUSE_BUTTON_7") == 0) return SPARK_MOUSE_BUTTON_7;
	else if (strcmp(string, "SPARK_MOUSE_BUTTON_8") == 0) return SPARK_MOUSE_BUTTON_8;
	else if (strcmp(string, "SPARK_MOUSE_BUTTON_LAST") == 0) return SPARK_MOUSE_BUTTON_LAST;
	else if (strcmp(string, "SPARK_MOUSE_BUTTON_LEFT") == 0) return SPARK_MOUSE_BUTTON_LEFT;
	else if (strcmp(string, "SPARK_MOUSE_BUTTON_RIGHT") == 0) return SPARK_MOUSE_BUTTON_RIGHT;
	else if (strcmp(string, "SPARK_MOUSE_BUTTON_MIDDLE") == 0) return SPARK_MOUSE_BUTTON_MIDDLE;
	else return (SparkMouseButton)-1;
}

SPARKAPI SparkConstString SparkKeyToString(SparkKey key)
{
	switch (key)
	{
	case SPARK_KEY_UNKNOWN: return "SPARK_KEY_UNKNOWN";
	case SPARK_KEY_SPACE: return "SPARK_KEY_SPACE";
	case SPARK_KEY_APOSTROPHE: return "SPARK_KEY_APOSTROPHE";
	case SPARK_KEY_COMMA: return "SPARK_KEY_COMMA";
	case SPARK_KEY_MINUS: return "SPARK_KEY_MINUS";
	case SPARK_KEY_PERIOD: return "SPARK_KEY_PERIOD";
	case SPARK_KEY_SLASH: return "SPARK_KEY_SLASH";
	case SPARK_KEY_0: return "SPARK_KEY_0";
	case SPARK_KEY_1: return "SPARK_KEY_1";
	case SPARK_KEY_2: return "SPARK_KEY_2";
	case SPARK_KEY_3: return "SPARK_KEY_3";
	case SPARK_KEY_4: return "SPARK_KEY_4";
	case SPARK_KEY_5: return "SPARK_KEY_5";
	case SPARK_KEY_6: return "SPARK_KEY_6";
	case SPARK_KEY_7: return "SPARK_KEY_7";
	case SPARK_KEY_8: return "SPARK_KEY_8";
	case SPARK_KEY_9: return "SPARK_KEY_9";
	case SPARK_KEY_SEMICOLON: return "SPARK_KEY_SEMICOLON";
	case SPARK_KEY_EQUAL: return "SPARK_KEY_EQUAL";
	case SPARK_KEY_A: return "SPARK_KEY_A";
	case SPARK_KEY_B: return "SPARK_KEY_B";
	case SPARK_KEY_C: return "SPARK_KEY_C";
	case SPARK_KEY_D: return "SPARK_KEY_D";
	case SPARK_KEY_E: return "SPARK_KEY_E";
	case SPARK_KEY_F: return "SPARK_KEY_F";
	case SPARK_KEY_G: return "SPARK_KEY_G";
	case SPARK_KEY_H: return "SPARK_KEY_H";
	case SPARK_KEY_I: return "SPARK_KEY_I";
	case SPARK_KEY_J: return "SPARK_KEY_J";
	case SPARK_KEY_K: return "SPARK_KEY_K";
	case SPARK_KEY_L: return "SPARK_KEY_L";
	case SPARK_KEY_M: return "SPARK_KEY_M";
	case SPARK_KEY_N: return "SPARK_KEY_N";
	case SPARK_KEY_O: return "SPARK_KEY_O";
	case SPARK_KEY_P: return "SPARK_KEY_P";
	case SPARK_KEY_Q: return "SPARK_KEY_Q";
	case SPARK_KEY_R: return "SPARK_KEY_R";
	case SPARK_KEY_S: return "SPARK_KEY_S";
	case SPARK_KEY_T: return "SPARK_KEY_T";
	case SPARK_KEY_U: return "SPARK_KEY_U";
	case SPARK_KEY_V: return "SPARK_KEY_V";
	case SPARK_KEY_W: return "SPARK_KEY_W";
	case SPARK_KEY_X: return "SPARK_KEY_X";
	case SPARK_KEY_Y: return "SPARK_KEY_Y";
	case SPARK_KEY_Z: return "SPARK_KEY_Z";
	case SPARK_KEY_LEFT_BRACKET: return "SPARK_KEY_LEFT_BRACKET";
	case SPARK_KEY_BACKSLASH: return "SPARK_KEY_BACKSLASH";
	case SPARK_KEY_RIGHT_BRACKET: return "SPARK_KEY_RIGHT_BRACKET";
	case SPARK_KEY_GRAVE_ACCENT: return "SPARK_KEY_GRAVE_ACCENT";
	case SPARK_KEY_WORLD_1: return "SPARK_KEY_WORLD_1";
	case SPARK_KEY_WORLD_2: return "SPARK_KEY_WORLD_2";
	case SPARK_KEY_ESCAPE: return "SPARK_KEY_ESCAPE";
	case SPARK_KEY_ENTER: return "SPARK_KEY_ENTER";
	case SPARK_KEY_TAB: return "SPARK_KEY_TAB";
	case SPARK_KEY_BACKSPACE: return "SPARK_KEY_BACKSPACE";
	case SPARK_KEY_INSERT: return "SPARK_KEY_INSERT";
	case SPARK_KEY_DELETE: return "SPARK_KEY_DELETE";
	case SPARK_KEY_RIGHT: return "SPARK_KEY_RIGHT";
	case SPARK_KEY_LEFT: return "SPARK_KEY_LEFT";
	case SPARK_KEY_DOWN: return "SPARK_KEY_DOWN";
	case SPARK_KEY_UP: return "SPARK_KEY_UP";
	case SPARK_KEY_PAGE_UP: return "SPARK_KEY_PAGE_UP";
	case SPARK_KEY_PAGE_DOWN: return "SPARK_KEY_PAGE_DOWN";
	case SPARK_KEY_HOME: return "SPARK_KEY_HOME";
	case SPARK_KEY_END: return "SPARK_KEY_END";
	case SPARK_KEY_CAPS_LOCK: return "SPARK_KEY_CAPS_LOCK";
	case SPARK_KEY_SCROLL_LOCK: return "SPARK_KEY_SCROLL_LOCK";
	case SPARK_KEY_NUM_LOCK: return "SPARK_KEY_NUM_LOCK";
	case SPARK_KEY_PRINT_SCREEN: return "SPARK_KEY_PRINT_SCREEN";
	case SPARK_KEY_PAUSE: return "SPARK_KEY_PAUSE";
	case SPARK_KEY_F1: return "SPARK_KEY_F1";
	case SPARK_KEY_F2: return "SPARK_KEY_F2";
	case SPARK_KEY_F3: return "SPARK_KEY_F3";
	case SPARK_KEY_F4: return "SPARK_KEY_F4";
	case SPARK_KEY_F5: return "SPARK_KEY_F5";
	case SPARK_KEY_F6: return "SPARK_KEY_F6";
	case SPARK_KEY_F7: return "SPARK_KEY_F7";
	case SPARK_KEY_F8: return "SPARK_KEY_F8";
	case SPARK_KEY_F9: return "SPARK_KEY_F9";
	case SPARK_KEY_F10: return "SPARK_KEY_F10";
	case SPARK_KEY_F11: return "SPARK_KEY_F11";
	case SPARK_KEY_F12: return "SPARK_KEY_F12";
	case SPARK_KEY_F13: return "SPARK_KEY_F13";
	case SPARK_KEY_F14: return "SPARK_KEY_F14";
	case SPARK_KEY_F15: return "SPARK_KEY_F15";
	case SPARK_KEY_F16: return "SPARK_KEY_F16";
	case SPARK_KEY_F17: return "SPARK_KEY_F17";
	case SPARK_KEY_F18: return "SPARK_KEY_F18";
	case SPARK_KEY_F19: return "SPARK_KEY_F19";
	case SPARK_KEY_F20: return "SPARK_KEY_F20";
	case SPARK_KEY_F21: return "SPARK_KEY_F21";
	case SPARK_KEY_F22: return "SPARK_KEY_F22";
	case SPARK_KEY_F23: return "SPARK_KEY_F23";
	case SPARK_KEY_F24: return "SPARK_KEY_F24";
	case SPARK_KEY_F25: return "SPARK_KEY_F25";
	case SPARK_KEY_KP_0: return "SPARK_KEY_KP_0";
	case SPARK_KEY_KP_1: return "SPARK_KEY_KP_1";
	case SPARK_KEY_KP_2: return "SPARK_KEY_KP_2";
	case SPARK_KEY_KP_3: return "SPARK_KEY_KP_3";
	case SPARK_KEY_KP_4: return "SPARK_KEY_KP_4";
	case SPARK_KEY_KP_5: return "SPARK_KEY_KP_5";
	case SPARK_KEY_KP_6: return "SPARK_KEY_KP_6";
	case SPARK_KEY_KP_7: return "SPARK_KEY_KP_7";
	case SPARK_KEY_KP_8: return "SPARK_KEY_KP_8";
	case SPARK_KEY_KP_9: return "SPARK_KEY_KP_9";
	case SPARK_KEY_KP_DECIMAL: return "SPARK_KEY_KP_DECIMAL";
	case SPARK_KEY_KP_DIVIDE: return "SPARK_KEY_KP_DIVIDE";
	case SPARK_KEY_KP_MULTIPLY: return "SPARK_KEY_KP_MULTIPLY";
	case SPARK_KEY_KP_SUBTRACT: return "SPARK_KEY_KP_SUBTRACT";
	case SPARK_KEY_KP_ADD: return "SPARK_KEY_KP_ADD";
	case SPARK_KEY_KP_ENTER: return "SPARK_KEY_KP_ENTER";
	case SPARK_KEY_KP_EQUAL: return "SPARK_KEY_KP_EQUAL";
	case SPARK_KEY_LEFT_SHIFT: return "SPARK_KEY_LEFT_SHIFT";
	case SPARK_KEY_LEFT_CONTROL: return "SPARK_KEY_LEFT_CONTROL";
	case SPARK_KEY_LEFT_ALT: return "SPARK_KEY_LEFT_ALT";
	case SPARK_KEY_LEFT_SUPER: return "SPARK_KEY_LEFT_SUPER";
	case SPARK_KEY_RIGHT_SHIFT: return "SPARK_KEY_RIGHT_SHIFT";
	case SPARK_KEY_RIGHT_CONTROL: return "SPARK_KEY_RIGHT_CONTROL";
	case SPARK_KEY_RIGHT_ALT: return "SPARK_KEY_RIGHT_ALT";
	case SPARK_KEY_RIGHT_SUPER: return "SPARK_KEY_RIGHT_SUPER";
	case SPARK_KEY_MENU: return "SPARK_KEY_MENU";
	default: return "UNKNOWN_SPARK_KEY";
	}
}

SPARKAPI SparkKey SparkStringToKey(SparkConstString string)
{
	if (strcmp(string, "SPARK_KEY_UNKNOWN") == 0) return SPARK_KEY_UNKNOWN;
	else if (strcmp(string, "SPARK_KEY_SPACE") == 0) return SPARK_KEY_SPACE;
	else if (strcmp(string, "SPARK_KEY_APOSTROPHE") == 0) return SPARK_KEY_APOSTROPHE;
	else if (strcmp(string, "SPARK_KEY_COMMA") == 0) return SPARK_KEY_COMMA;
	else if (strcmp(string, "SPARK_KEY_MINUS") == 0) return SPARK_KEY_MINUS;
	else if (strcmp(string, "SPARK_KEY_PERIOD") == 0) return SPARK_KEY_PERIOD;
	else if (strcmp(string, "SPARK_KEY_SLASH") == 0) return SPARK_KEY_SLASH;
	else if (strcmp(string, "SPARK_KEY_0") == 0) return SPARK_KEY_0;
	else if (strcmp(string, "SPARK_KEY_1") == 0) return SPARK_KEY_1;
	else if (strcmp(string, "SPARK_KEY_2") == 0) return SPARK_KEY_2;
	else if (strcmp(string, "SPARK_KEY_3") == 0) return SPARK_KEY_3;
	else if (strcmp(string, "SPARK_KEY_4") == 0) return SPARK_KEY_4;
	else if (strcmp(string, "SPARK_KEY_5") == 0) return SPARK_KEY_5;
	else if (strcmp(string, "SPARK_KEY_6") == 0) return SPARK_KEY_6;
	else if (strcmp(string, "SPARK_KEY_7") == 0) return SPARK_KEY_7;
	else if (strcmp(string, "SPARK_KEY_8") == 0) return SPARK_KEY_8;
	else if (strcmp(string, "SPARK_KEY_9") == 0) return SPARK_KEY_9;
	else if (strcmp(string, "SPARK_KEY_SEMICOLON") == 0) return SPARK_KEY_SEMICOLON;
	else if (strcmp(string, "SPARK_KEY_EQUAL") == 0) return SPARK_KEY_EQUAL;
	else if (strcmp(string, "SPARK_KEY_A") == 0) return SPARK_KEY_A;
	else if (strcmp(string, "SPARK_KEY_B") == 0) return SPARK_KEY_B;
	else if (strcmp(string, "SPARK_KEY_C") == 0) return SPARK_KEY_C;
	else if (strcmp(string, "SPARK_KEY_D") == 0) return SPARK_KEY_D;
	else if (strcmp(string, "SPARK_KEY_E") == 0) return SPARK_KEY_E;
	else if (strcmp(string, "SPARK_KEY_F") == 0) return SPARK_KEY_F;
	else if (strcmp(string, "SPARK_KEY_G") == 0) return SPARK_KEY_G;
	else if (strcmp(string, "SPARK_KEY_H") == 0) return SPARK_KEY_H;
	else if (strcmp(string, "SPARK_KEY_I") == 0) return SPARK_KEY_I;
	else if (strcmp(string, "SPARK_KEY_J") == 0) return SPARK_KEY_J;
	else if (strcmp(string, "SPARK_KEY_K") == 0) return SPARK_KEY_K;
	else if (strcmp(string, "SPARK_KEY_L") == 0) return SPARK_KEY_L;
	else if (strcmp(string, "SPARK_KEY_M") == 0) return SPARK_KEY_M;
	else if (strcmp(string, "SPARK_KEY_N") == 0) return SPARK_KEY_N;
	else if (strcmp(string, "SPARK_KEY_O") == 0) return SPARK_KEY_O;
	else if (strcmp(string, "SPARK_KEY_P") == 0) return SPARK_KEY_P;
	else if (strcmp(string, "SPARK_KEY_Q") == 0) return SPARK_KEY_Q;
	else if (strcmp(string, "SPARK_KEY_R") == 0) return SPARK_KEY_R;
	else if (strcmp(string, "SPARK_KEY_S") == 0) return SPARK_KEY_S;
	else if (strcmp(string, "SPARK_KEY_T") == 0) return SPARK_KEY_T;
	else if (strcmp(string, "SPARK_KEY_U") == 0) return SPARK_KEY_U;
	else if (strcmp(string, "SPARK_KEY_V") == 0) return SPARK_KEY_V;
	else if (strcmp(string, "SPARK_KEY_W") == 0) return SPARK_KEY_W;
	else if (strcmp(string, "SPARK_KEY_X") == 0) return SPARK_KEY_X;
	else if (strcmp(string, "SPARK_KEY_Y") == 0) return SPARK_KEY_Y;
	else if (strcmp(string, "SPARK_KEY_Z") == 0) return SPARK_KEY_Z;
	else if (strcmp(string, "SPARK_KEY_LEFT_BRACKET") == 0) return SPARK_KEY_LEFT_BRACKET;
	else if (strcmp(string, "SPARK_KEY_BACKSLASH") == 0) return SPARK_KEY_BACKSLASH;
	else if (strcmp(string, "SPARK_KEY_RIGHT_BRACKET") == 0) return SPARK_KEY_RIGHT_BRACKET;
	else if (strcmp(string, "SPARK_KEY_GRAVE_ACCENT") == 0) return SPARK_KEY_GRAVE_ACCENT;
	else if (strcmp(string, "SPARK_KEY_WORLD_1") == 0) return SPARK_KEY_WORLD_1;
	else if (strcmp(string, "SPARK_KEY_WORLD_2") == 0) return SPARK_KEY_WORLD_2;
	else if (strcmp(string, "SPARK_KEY_ESCAPE") == 0) return SPARK_KEY_ESCAPE;
	else if (strcmp(string, "SPARK_KEY_ENTER") == 0) return SPARK_KEY_ENTER;
	else if (strcmp(string, "SPARK_KEY_TAB") == 0) return SPARK_KEY_TAB;
	else if (strcmp(string, "SPARK_KEY_BACKSPACE") == 0) return SPARK_KEY_BACKSPACE;
	else if (strcmp(string, "SPARK_KEY_INSERT") == 0) return SPARK_KEY_INSERT;
	else if (strcmp(string, "SPARK_KEY_DELETE") == 0) return SPARK_KEY_DELETE;
	else if (strcmp(string, "SPARK_KEY_RIGHT") == 0) return SPARK_KEY_RIGHT;
	else if (strcmp(string, "SPARK_KEY_LEFT") == 0) return SPARK_KEY_LEFT;
	else if (strcmp(string, "SPARK_KEY_DOWN") == 0) return SPARK_KEY_DOWN;
	else if (strcmp(string, "SPARK_KEY_UP") == 0) return SPARK_KEY_UP;
	else if (strcmp(string, "SPARK_KEY_PAGE_UP") == 0) return SPARK_KEY_PAGE_UP;
	else if (strcmp(string, "SPARK_KEY_PAGE_DOWN") == 0) return SPARK_KEY_PAGE_DOWN;
	else if (strcmp(string, "SPARK_KEY_HOME") == 0) return SPARK_KEY_HOME;
	else if (strcmp(string, "SPARK_KEY_END") == 0) return SPARK_KEY_END;
	else if (strcmp(string, "SPARK_KEY_CAPS_LOCK") == 0) return SPARK_KEY_CAPS_LOCK;
	else if (strcmp(string, "SPARK_KEY_SCROLL_LOCK") == 0) return SPARK_KEY_SCROLL_LOCK;
	else if (strcmp(string, "SPARK_KEY_NUM_LOCK") == 0) return SPARK_KEY_NUM_LOCK;
	else if (strcmp(string, "SPARK_KEY_PRINT_SCREEN") == 0) return SPARK_KEY_PRINT_SCREEN;
	else if (strcmp(string, "SPARK_KEY_PAUSE") == 0) return SPARK_KEY_PAUSE;
	else if (strcmp(string, "SPARK_KEY_F1") == 0) return SPARK_KEY_F1;
	else if (strcmp(string, "SPARK_KEY_F2") == 0) return SPARK_KEY_F2;
	else if (strcmp(string, "SPARK_KEY_F3") == 0) return SPARK_KEY_F3;
	else if (strcmp(string, "SPARK_KEY_F4") == 0) return SPARK_KEY_F4;
	else if (strcmp(string, "SPARK_KEY_F5") == 0) return SPARK_KEY_F5;
	else if (strcmp(string, "SPARK_KEY_F6") == 0) return SPARK_KEY_F6;
	else if (strcmp(string, "SPARK_KEY_F7") == 0) return SPARK_KEY_F7;
	else if (strcmp(string, "SPARK_KEY_F8") == 0) return SPARK_KEY_F8;
	else if (strcmp(string, "SPARK_KEY_F9") == 0) return SPARK_KEY_F9;
	else if (strcmp(string, "SPARK_KEY_F10") == 0) return SPARK_KEY_F10;
	else if (strcmp(string, "SPARK_KEY_F11") == 0) return SPARK_KEY_F11;
	else if (strcmp(string, "SPARK_KEY_F12") == 0) return SPARK_KEY_F12;
	else if (strcmp(string, "SPARK_KEY_F13") == 0) return SPARK_KEY_F13;
	else if (strcmp(string, "SPARK_KEY_F14") == 0) return SPARK_KEY_F14;
	else if (strcmp(string, "SPARK_KEY_F15") == 0) return SPARK_KEY_F15;
	else if (strcmp(string, "SPARK_KEY_F16") == 0) return SPARK_KEY_F16;
	else if (strcmp(string, "SPARK_KEY_F17") == 0) return SPARK_KEY_F17;
	else if (strcmp(string, "SPARK_KEY_F18") == 0) return SPARK_KEY_F18;
	else if (strcmp(string, "SPARK_KEY_F19") == 0) return SPARK_KEY_F19;
	else if (strcmp(string, "SPARK_KEY_F20") == 0) return SPARK_KEY_F20;
	else if (strcmp(string, "SPARK_KEY_F21") == 0) return SPARK_KEY_F21;
	else if (strcmp(string, "SPARK_KEY_F22") == 0) return SPARK_KEY_F22;
	else if (strcmp(string, "SPARK_KEY_F23") == 0) return SPARK_KEY_F23;
	else if (strcmp(string, "SPARK_KEY_F24") == 0) return SPARK_KEY_F24;
	else if (strcmp(string, "SPARK_KEY_F25") == 0) return SPARK_KEY_F25;
	else if (strcmp(string, "SPARK_KEY_KP_0") == 0) return SPARK_KEY_KP_0;
	else if (strcmp(string, "SPARK_KEY_KP_1") == 0) return SPARK_KEY_KP_1;
	else if (strcmp(string, "SPARK_KEY_KP_2") == 0) return SPARK_KEY_KP_2;
	else if (strcmp(string, "SPARK_KEY_KP_3") == 0) return SPARK_KEY_KP_3;
	else if (strcmp(string, "SPARK_KEY_KP_4") == 0) return SPARK_KEY_KP_4;
	else if (strcmp(string, "SPARK_KEY_KP_5") == 0) return SPARK_KEY_KP_5;
	else if (strcmp(string, "SPARK_KEY_KP_6") == 0) return SPARK_KEY_KP_6;
	else if (strcmp(string, "SPARK_KEY_KP_7") == 0) return SPARK_KEY_KP_7;
	else if (strcmp(string, "SPARK_KEY_KP_8") == 0) return SPARK_KEY_KP_8;
	else if (strcmp(string, "SPARK_KEY_KP_9") == 0) return SPARK_KEY_KP_9;
	else if (strcmp(string, "SPARK_KEY_KP_DECIMAL") == 0) return SPARK_KEY_KP_DECIMAL;
	else if (strcmp(string, "SPARK_KEY_KP_DIVIDE") == 0) return SPARK_KEY_KP_DIVIDE;
	else if (strcmp(string, "SPARK_KEY_KP_MULTIPLY") == 0) return SPARK_KEY_KP_MULTIPLY;
	else if (strcmp(string, "SPARK_KEY_KP_SUBTRACT") == 0) return SPARK_KEY_KP_SUBTRACT;
	else if (strcmp(string, "SPARK_KEY_KP_ADD") == 0) return SPARK_KEY_KP_ADD;
	else if (strcmp(string, "SPARK_KEY_KP_ENTER") == 0) return SPARK_KEY_KP_ENTER;
	else if (strcmp(string, "SPARK_KEY_KP_EQUAL") == 0) return SPARK_KEY_KP_EQUAL;
	else if (strcmp(string, "SPARK_KEY_LEFT_SHIFT") == 0) return SPARK_KEY_LEFT_SHIFT;
	else if (strcmp(string, "SPARK_KEY_LEFT_CONTROL") == 0) return SPARK_KEY_LEFT_CONTROL;
	else if (strcmp(string, "SPARK_KEY_LEFT_ALT") == 0) return SPARK_KEY_LEFT_ALT;
	else if (strcmp(string, "SPARK_KEY_LEFT_SUPER") == 0) return SPARK_KEY_LEFT_SUPER;
	else if (strcmp(string, "SPARK_KEY_RIGHT_SHIFT") == 0) return SPARK_KEY_RIGHT_SHIFT;
	else if (strcmp(string, "SPARK_KEY_RIGHT_CONTROL") == 0) return SPARK_KEY_RIGHT_CONTROL;
	else if (strcmp(string, "SPARK_KEY_RIGHT_ALT") == 0) return SPARK_KEY_RIGHT_ALT;
	else if (strcmp(string, "SPARK_KEY_RIGHT_SUPER") == 0) return SPARK_KEY_RIGHT_SUPER;
	else if (strcmp(string, "SPARK_KEY_MENU") == 0) return SPARK_KEY_MENU;
	return SPARK_KEY_UNKNOWN;
}

SPARKAPI SparkConstString SparkModifierToString(SparkModifier modifier) {
	switch (modifier) {
	case SPARK_MOD_SHIFT:   return "SPARK_MOD_SHIFT";
	case SPARK_MOD_CONTROL: return "SPARK_MOD_CONTROL";
	case SPARK_MOD_ALT:     return "SPARK_MOD_ALT";
	case SPARK_MOD_SUPER:   return "SPARK_MOD_SUPER";
	default:                return "UNKNOWN_SPARK_MODIFIER";
	}
}

SPARKAPI SparkModifier SparkStringToModifier(SparkConstString string) {
	if (strcmp(string, "SPARK_MOD_SHIFT") == 0)         return SPARK_MOD_SHIFT;
	else if (strcmp(string, "SPARK_MOD_CONTROL") == 0)  return SPARK_MOD_CONTROL;
	else if (strcmp(string, "SPARK_MOD_ALT") == 0)      return SPARK_MOD_ALT;
	else if (strcmp(string, "SPARK_MOD_SUPER") == 0)    return SPARK_MOD_SUPER;
	else                                                return (SparkModifier)0;
}

SPARKAPI SparkConstString SparkActionToString(SparkAction action) {
	switch (action) {
	case SPARK_RELEASE: return "SPARK_RELEASE";
	case SPARK_PRESS:   return "SPARK_PRESS";
	case SPARK_REPEAT:  return "SPARK_REPEAT";
	default:            return "UNKNOWN_SPARK_ACTION";
	}
}

SPARKAPI SparkAction SparkStringToAction(SparkConstString string) {
	if (strcmp(string, "SPARK_RELEASE") == 0)      return SPARK_RELEASE;
	else if (strcmp(string, "SPARK_PRESS") == 0)   return SPARK_PRESS;
	else if (strcmp(string, "SPARK_REPEAT") == 0)  return SPARK_REPEAT;
	else                                           return (SparkAction)-1;
}

SPARKAPI SparkConstString SparkCursorToString(SparkCursor cursor) {
	switch (cursor) {
	case SPARK_CURSOR_ARROW:     return "SPARK_CURSOR_ARROW";
	case SPARK_CURSOR_IBEAM:     return "SPARK_CURSOR_IBEAM";
	case SPARK_CURSOR_CROSSHAIR: return "SPARK_CURSOR_CROSSHAIR";
	case SPARK_CURSOR_HAND:      return "SPARK_CURSOR_HAND";
	case SPARK_CURSOR_HRESIZE:   return "SPARK_CURSOR_HRESIZE";
	case SPARK_CURSOR_VRESIZE:   return "SPARK_CURSOR_VRESIZE";
	default:                     return "UNKNOWN_SPARK_CURSOR";
	}
}

SPARKAPI SparkCursor SparkStringToCursor(SparkConstString string) {
	if (strcmp(string, "SPARK_CURSOR_ARROW") == 0)         return SPARK_CURSOR_ARROW;
	else if (strcmp(string, "SPARK_CURSOR_IBEAM") == 0)    return SPARK_CURSOR_IBEAM;
	else if (strcmp(string, "SPARK_CURSOR_CROSSHAIR") == 0)return SPARK_CURSOR_CROSSHAIR;
	else if (strcmp(string, "SPARK_CURSOR_HAND") == 0)     return SPARK_CURSOR_HAND;
	else if (strcmp(string, "SPARK_CURSOR_HRESIZE") == 0)  return SPARK_CURSOR_HRESIZE;
	else if (strcmp(string, "SPARK_CURSOR_VRESIZE") == 0)  return SPARK_CURSOR_VRESIZE;
	else                                                   return (SparkCursor)-1;
}

SPARKAPI SparkConstString SparkEventTypeToString(SparkEventType eventType) {
	switch (eventType) {
	case SPARK_EVENT_NONE:                     return "SPARK_EVENT_NONE";
	case SPARK_EVENT_WINDOW_CLOSE:             return "SPARK_EVENT_WINDOW_CLOSE";
	case SPARK_EVENT_WINDOW_RESIZE:            return "SPARK_EVENT_WINDOW_RESIZE";
	case SPARK_EVENT_WINDOW_FOCUS:             return "SPARK_EVENT_WINDOW_FOCUS";
	case SPARK_EVENT_WINDOW_LOST_FOCUS:        return "SPARK_EVENT_WINDOW_LOST_FOCUS";
	case SPARK_EVENT_WINDOW_MOVED:             return "SPARK_EVENT_WINDOW_MOVED";
	case SPARK_EVENT_KEY_PRESSED:              return "SPARK_EVENT_KEY_PRESSED";
	case SPARK_EVENT_KEY_RELEASED:             return "SPARK_EVENT_KEY_RELEASED";
	case SPARK_EVENT_KEY_TYPED:                return "SPARK_EVENT_KEY_TYPED";
	case SPARK_EVENT_MOUSE_BUTTON_PRESSED:     return "SPARK_EVENT_MOUSE_BUTTON_PRESSED";
	case SPARK_EVENT_MOUSE_BUTTON_RELEASED:    return "SPARK_EVENT_MOUSE_BUTTON_RELEASED";
	case SPARK_EVENT_MOUSE_MOVED:              return "SPARK_EVENT_MOUSE_MOVED";
	case SPARK_EVENT_MOUSE_SCROLLED:           return "SPARK_EVENT_MOUSE_SCROLLED";
	default:                                   return "UNKNOWN_SPARK_EVENT_TYPE";
	}
}

SPARKAPI SparkEventType SparkStringToEventType(SparkConstString string) {
	if (strcmp(string, "SPARK_EVENT_NONE") == 0)                      return SPARK_EVENT_NONE;
	else if (strcmp(string, "SPARK_EVENT_WINDOW_CLOSE") == 0)         return SPARK_EVENT_WINDOW_CLOSE;
	else if (strcmp(string, "SPARK_EVENT_WINDOW_RESIZE") == 0)        return SPARK_EVENT_WINDOW_RESIZE;
	else if (strcmp(string, "SPARK_EVENT_WINDOW_FOCUS") == 0)         return SPARK_EVENT_WINDOW_FOCUS;
	else if (strcmp(string, "SPARK_EVENT_WINDOW_LOST_FOCUS") == 0)    return SPARK_EVENT_WINDOW_LOST_FOCUS;
	else if (strcmp(string, "SPARK_EVENT_WINDOW_MOVED") == 0)         return SPARK_EVENT_WINDOW_MOVED;
	else if (strcmp(string, "SPARK_EVENT_KEY_PRESSED") == 0)          return SPARK_EVENT_KEY_PRESSED;
	else if (strcmp(string, "SPARK_EVENT_KEY_RELEASED") == 0)         return SPARK_EVENT_KEY_RELEASED;
	else if (strcmp(string, "SPARK_EVENT_KEY_TYPED") == 0)            return SPARK_EVENT_KEY_TYPED;
	else if (strcmp(string, "SPARK_EVENT_MOUSE_BUTTON_PRESSED") == 0) return SPARK_EVENT_MOUSE_BUTTON_PRESSED;
	else if (strcmp(string, "SPARK_EVENT_MOUSE_BUTTON_RELEASED") == 0)return SPARK_EVENT_MOUSE_BUTTON_RELEASED;
	else if (strcmp(string, "SPARK_EVENT_MOUSE_MOVED") == 0)          return SPARK_EVENT_MOUSE_MOVED;
	else if (strcmp(string, "SPARK_EVENT_MOUSE_SCROLLED") == 0)       return SPARK_EVENT_MOUSE_SCROLLED;
	else                                                              return (SparkEventType)-1;
}

SPARKAPI SparkConstString SparkShaderTypeToString(SparkShaderType shaderType) {
	switch (shaderType) {
	case SPARK_SHADER_VERTEX:                  return "SPARK_SHADER_VERTEX";
	case SPARK_SHADER_FRAGMENT:                return "SPARK_SHADER_FRAGMENT";
	case SPARK_SHADER_GEOMETRY:                return "SPARK_SHADER_GEOMETRY";
	case SPARK_SHADER_TESSELLATION_CONTROL:    return "SPARK_SHADER_TESSELLATION_CONTROL";
	case SPARK_SHADER_TESSELLATION_EVALUATION: return "SPARK_SHADER_TESSELLATION_EVALUATION";
	case SPARK_SHADER_COMPUTE:                 return "SPARK_SHADER_COMPUTE";
	default:                                   return "UNKNOWN_SPARK_SHADER_TYPE";
	}
}

SPARKAPI SparkShaderType SparkStringToShaderType(SparkConstString string) {
	if (strcmp(string, "SPARK_SHADER_VERTEX") == 0)                   return SPARK_SHADER_VERTEX;
	else if (strcmp(string, "SPARK_SHADER_FRAGMENT") == 0)            return SPARK_SHADER_FRAGMENT;
	else if (strcmp(string, "SPARK_SHADER_GEOMETRY") == 0)            return SPARK_SHADER_GEOMETRY;
	else if (strcmp(string, "SPARK_SHADER_TESSELLATION_CONTROL") == 0)return SPARK_SHADER_TESSELLATION_CONTROL;
	else if (strcmp(string, "SPARK_SHADER_TESSELLATION_EVALUATION") == 0)return SPARK_SHADER_TESSELLATION_EVALUATION;
	else if (strcmp(string, "SPARK_SHADER_COMPUTE") == 0)             return SPARK_SHADER_COMPUTE;
	else                                                              return (SparkShaderType)-1;
}

SPARKAPI SparkConstString SparkPrimitiveTypeToString(SparkPrimitiveType primitiveType) {
	switch (primitiveType) {
	case SPARK_PRIMITIVE_POINTS:         return "SPARK_PRIMITIVE_POINTS";
	case SPARK_PRIMITIVE_LINES:          return "SPARK_PRIMITIVE_LINES";
	case SPARK_PRIMITIVE_LINE_STRIP:     return "SPARK_PRIMITIVE_LINE_STRIP";
	case SPARK_PRIMITIVE_TRIANGLES:      return "SPARK_PRIMITIVE_TRIANGLES";
	case SPARK_PRIMITIVE_TRIANGLE_STRIP: return "SPARK_PRIMITIVE_TRIANGLE_STRIP";
	case SPARK_PRIMITIVE_TRIANGLE_FAN:   return "SPARK_PRIMITIVE_TRIANGLE_FAN";
	default:                             return "UNKNOWN_SPARK_PRIMITIVE_TYPE";
	}
}

SPARKAPI SparkPrimitiveType SparkStringToPrimitiveType(SparkConstString string) {
	if (strcmp(string, "SPARK_PRIMITIVE_POINTS") == 0)          return SPARK_PRIMITIVE_POINTS;
	else if (strcmp(string, "SPARK_PRIMITIVE_LINES") == 0)          return SPARK_PRIMITIVE_LINES;
	else if (strcmp(string, "SPARK_PRIMITIVE_LINE_STRIP") == 0)     return SPARK_PRIMITIVE_LINE_STRIP;
	else if (strcmp(string, "SPARK_PRIMITIVE_TRIANGLES") == 0)      return SPARK_PRIMITIVE_TRIANGLES;
	else if (strcmp(string, "SPARK_PRIMITIVE_TRIANGLE_STRIP") == 0) return SPARK_PRIMITIVE_TRIANGLE_STRIP;
	else if (strcmp(string, "SPARK_PRIMITIVE_TRIANGLE_FAN") == 0)   return SPARK_PRIMITIVE_TRIANGLE_FAN;
	else                                                            return (SparkPrimitiveType)-1;
}

SPARKAPI SparkConstString SparkBlendModeToString(SparkBlendMode blendMode) {
	switch (blendMode) {
	case SPARK_BLEND_ZERO:                     return "SPARK_BLEND_ZERO";
	case SPARK_BLEND_ONE:                      return "SPARK_BLEND_ONE";
	case SPARK_BLEND_SRC_COLOR:                return "SPARK_BLEND_SRC_COLOR";
	case SPARK_BLEND_ONE_MINUS_SRC_COLOR:      return "SPARK_BLEND_ONE_MINUS_SRC_COLOR";
	case SPARK_BLEND_DST_COLOR:                return "SPARK_BLEND_DST_COLOR";
	case SPARK_BLEND_ONE_MINUS_DST_COLOR:      return "SPARK_BLEND_ONE_MINUS_DST_COLOR";
	case SPARK_BLEND_SRC_ALPHA:                return "SPARK_BLEND_SRC_ALPHA";
	case SPARK_BLEND_ONE_MINUS_SRC_ALPHA:      return "SPARK_BLEND_ONE_MINUS_SRC_ALPHA";
	case SPARK_BLEND_DST_ALPHA:                return "SPARK_BLEND_DST_ALPHA";
	case SPARK_BLEND_ONE_MINUS_DST_ALPHA:      return "SPARK_BLEND_ONE_MINUS_DST_ALPHA";
	case SPARK_BLEND_CONSTANT_COLOR:           return "SPARK_BLEND_CONSTANT_COLOR";
	case SPARK_BLEND_ONE_MINUS_CONSTANT_COLOR: return "SPARK_BLEND_ONE_MINUS_CONSTANT_COLOR";
	case SPARK_BLEND_CONSTANT_ALPHA:           return "SPARK_BLEND_CONSTANT_ALPHA";
	case SPARK_BLEND_ONE_MINUS_CONSTANT_ALPHA: return "SPARK_BLEND_ONE_MINUS_CONSTANT_ALPHA";
	case SPARK_BLEND_SRC_ALPHA_SATURATE:       return "SPARK_BLEND_SRC_ALPHA_SATURATE";
	default:                                   return "UNKNOWN_SPARK_BLEND_MODE";
	}
}

SPARKAPI SparkBlendMode SparkStringToBlendMode(SparkConstString string) {
	if (strcmp(string, "SPARK_BLEND_ZERO") == 0)                     return SPARK_BLEND_ZERO;
	else if (strcmp(string, "SPARK_BLEND_ONE") == 0)                      return SPARK_BLEND_ONE;
	else if (strcmp(string, "SPARK_BLEND_SRC_COLOR") == 0)                return SPARK_BLEND_SRC_COLOR;
	else if (strcmp(string, "SPARK_BLEND_ONE_MINUS_SRC_COLOR") == 0)      return SPARK_BLEND_ONE_MINUS_SRC_COLOR;
	else if (strcmp(string, "SPARK_BLEND_DST_COLOR") == 0)                return SPARK_BLEND_DST_COLOR;
	else if (strcmp(string, "SPARK_BLEND_ONE_MINUS_DST_COLOR") == 0)      return SPARK_BLEND_ONE_MINUS_DST_COLOR;
	else if (strcmp(string, "SPARK_BLEND_SRC_ALPHA") == 0)                return SPARK_BLEND_SRC_ALPHA;
	else if (strcmp(string, "SPARK_BLEND_ONE_MINUS_SRC_ALPHA") == 0)      return SPARK_BLEND_ONE_MINUS_SRC_ALPHA;
	else if (strcmp(string, "SPARK_BLEND_DST_ALPHA") == 0)                return SPARK_BLEND_DST_ALPHA;
	else if (strcmp(string, "SPARK_BLEND_ONE_MINUS_DST_ALPHA") == 0)      return SPARK_BLEND_ONE_MINUS_DST_ALPHA;
	else if (strcmp(string, "SPARK_BLEND_CONSTANT_COLOR") == 0)           return SPARK_BLEND_CONSTANT_COLOR;
	else if (strcmp(string, "SPARK_BLEND_ONE_MINUS_CONSTANT_COLOR") == 0) return SPARK_BLEND_ONE_MINUS_CONSTANT_COLOR;
	else if (strcmp(string, "SPARK_BLEND_CONSTANT_ALPHA") == 0)           return SPARK_BLEND_CONSTANT_ALPHA;
	else if (strcmp(string, "SPARK_BLEND_ONE_MINUS_CONSTANT_ALPHA") == 0) return SPARK_BLEND_ONE_MINUS_CONSTANT_ALPHA;
	else if (strcmp(string, "SPARK_BLEND_SRC_ALPHA_SATURATE") == 0)       return SPARK_BLEND_SRC_ALPHA_SATURATE;
	else                                                                  return (SparkBlendMode)-1;
}

SPARKAPI SparkConstString SparkTextureFilterToString(SparkTextureFilter filter) {
	switch (filter) {
	case SPARK_TEXTURE_FILTER_NEAREST:                return "SPARK_TEXTURE_FILTER_NEAREST";
	case SPARK_TEXTURE_FILTER_LINEAR:                 return "SPARK_TEXTURE_FILTER_LINEAR";
	case SPARK_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST: return "SPARK_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST";
	case SPARK_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST:  return "SPARK_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST";
	case SPARK_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR:  return "SPARK_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR";
	case SPARK_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR:   return "SPARK_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR";
	default:                                          return "UNKNOWN_SPARK_TEXTURE_FILTER";
	}
}

SPARKAPI SparkTextureFilter SparkStringToTextureFilter(SparkConstString string) {
	if (strcmp(string, "SPARK_TEXTURE_FILTER_NEAREST") == 0)                return SPARK_TEXTURE_FILTER_NEAREST;
	else if (strcmp(string, "SPARK_TEXTURE_FILTER_LINEAR") == 0)                 return SPARK_TEXTURE_FILTER_LINEAR;
	else if (strcmp(string, "SPARK_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST") == 0) return SPARK_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST;
	else if (strcmp(string, "SPARK_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST") == 0)  return SPARK_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST;
	else if (strcmp(string, "SPARK_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR") == 0)  return SPARK_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR;
	else if (strcmp(string, "SPARK_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR") == 0)   return SPARK_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR;
	else                                                                         return (SparkTextureFilter)-1;
}

SPARKAPI SparkConstString SparkLogLevelToString(SparkLogLevel level) {
	switch (level) {
	case SPARK_LOG_LEVEL_TRACE: return "SPARK_LOG_LEVEL_TRACE";
	case SPARK_LOG_LEVEL_DEBUG: return "SPARK_LOG_LEVEL_DEBUG";
	case SPARK_LOG_LEVEL_INFO:  return "SPARK_LOG_LEVEL_INFO";
	case SPARK_LOG_LEVEL_WARN:  return "SPARK_LOG_LEVEL_WARN";
	case SPARK_LOG_LEVEL_ERROR: return "SPARK_LOG_LEVEL_ERROR";
	case SPARK_LOG_LEVEL_FATAL: return "SPARK_LOG_LEVEL_FATAL";
	default:                    return "UNKNOWN_SPARK_LOG_LEVEL";
	}
}

SPARKAPI SparkLogLevel SparkStringToLogLevel(SparkConstString string) {
	if (strcmp(string, "SPARK_LOG_LEVEL_TRACE") == 0) return SPARK_LOG_LEVEL_TRACE;
	else if (strcmp(string, "SPARK_LOG_LEVEL_DEBUG") == 0) return SPARK_LOG_LEVEL_DEBUG;
	else if (strcmp(string, "SPARK_LOG_LEVEL_INFO") == 0)  return SPARK_LOG_LEVEL_INFO;
	else if (strcmp(string, "SPARK_LOG_LEVEL_WARN") == 0)  return SPARK_LOG_LEVEL_WARN;
	else if (strcmp(string, "SPARK_LOG_LEVEL_ERROR") == 0) return SPARK_LOG_LEVEL_ERROR;
	else if (strcmp(string, "SPARK_LOG_LEVEL_FATAL") == 0) return SPARK_LOG_LEVEL_FATAL;
	else                                                   return (SparkLogLevel)-1;
}

SPARKAPI SparkConstString SparkRenderAPIToString(SparkRenderAPI api) {
	switch (api) {
	case SPARK_RENDER_API_NONE:    return "SPARK_RENDER_API_NONE";
	case SPARK_RENDER_API_OPENGL:  return "SPARK_RENDER_API_OPENGL";
	case SPARK_RENDER_API_VULKAN:  return "SPARK_RENDER_API_VULKAN";
	case SPARK_RENDER_API_DIRECTX: return "SPARK_RENDER_API_DIRECTX";
	case SPARK_RENDER_API_METAL:   return "SPARK_RENDER_API_METAL";
	default:                       return "UNKNOWN_SPARK_RENDER_API";
	}
}

SPARKAPI SparkRenderAPI SparkStringToRenderAPI(SparkConstString string) {
	if (strcmp(string, "SPARK_RENDER_API_NONE") == 0)    return SPARK_RENDER_API_NONE;
	else if (strcmp(string, "SPARK_RENDER_API_OPENGL") == 0)  return SPARK_RENDER_API_OPENGL;
	else if (strcmp(string, "SPARK_RENDER_API_VULKAN") == 0)  return SPARK_RENDER_API_VULKAN;
	else if (strcmp(string, "SPARK_RENDER_API_DIRECTX") == 0) return SPARK_RENDER_API_DIRECTX;
	else if (strcmp(string, "SPARK_RENDER_API_METAL") == 0)   return SPARK_RENDER_API_METAL;
	else                                                      return (SparkRenderAPI)-1;
}

#pragma endregion

#pragma region UTIL

SPARKAPI SparkConstString SparkFormatString(SparkConstString format, ...) {
	va_list args;
	va_start(args, format);

	// Get the length of the formatted string
	SparkSize length = vsnprintf(NULL, 0, format, args);

	// Allocate a buffer to store the formatted string
	SparkBuffer buffer = SparkAllocate(length + 1);

	// Format the string
	vsprintf(buffer, format, args);

	va_end(args);

	return buffer;
}

SPARKAPI SparkVoid SetConsoleColor(SparkU32 color);

#ifdef _WIN32

#include <Windows.h>

SPARKAPI SparkVoid SetConsoleColor(SparkU32 color) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, color);
}

#else

SPARKAPI SparkVoid SetConsoleColor(SparkU32 color) {}

#endif

SPARKAPI SparkVoid SparkLog(SparkLogLevel log_level, SparkConstString format, ...)
{
	va_list args;
	va_start(args, format);

	// Set the appropriate color based on the log level
	switch (log_level)
	{
	case SPARK_LOG_LEVEL_DEBUG:
		SetConsoleColor(11);
		printf("[DEBUG] ");
		break;
	case SPARK_LOG_LEVEL_INFO:
		SetConsoleColor(2);
		printf("[INFO] ");
		break;
	case SPARK_LOG_LEVEL_WARN:
		SetConsoleColor(14);
		printf("[WARN] ");
		break;
	case SPARK_LOG_LEVEL_ERROR:
		SetConsoleColor(4);
		printf("[ERROR] ");
		break;
	case SPARK_LOG_LEVEL_FATAL:
		SetConsoleColor(4);
		printf("[FATAL] ");
		break;
	default:
		break;
	}

	// Print the formatted message using vprintf to handle the variable arguments
	vprintf(format, args);
	printf("\n"); // Add newline after the message

	// If the log level is fatal, crash the program
	if (log_level == SPARK_LOG_LEVEL_FATAL)
	{
		SPARK_CRASH_PROGRAM("Fatal error occurred!");
	}

	va_end(args);
}

SPARKAPI SparkResult SparkCheckSuccess(SparkResult result) {
	if (result != SPARK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, SparkResultToString(result));
	}
	return result;
}

SPARKAPI SparkConstString SparkGetTime() {
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	SparkConstString output[50];

	snprintf(output, 50, "[%d %d %d %d:%d:%d]", timeinfo->tm_mday,
		timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
		timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

	return output;
}

#pragma endregion

#pragma region MATH

SPARKAPI SparkScalar SparkClampS(SparkScalar value, SparkScalar min, SparkScalar max) {
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

#pragma endregion

#pragma region ALLOCATOR

SPARKAPI SparkHandle SparkAllocate(SparkSize size) {
	return malloc(size);
}

SPARKAPI SparkHandle SparkReallocate(SparkHandle handle, SparkSize size) {
	return realloc(handle, size);
}

SPARKAPI SparkVoid SparkFree(SparkHandle handle) {
	free(handle);
}

SPARKAPI SparkAllocator SparkDefaultAllocator() {
	SparkAllocator allocator = SparkAllocate(sizeof(struct SparkAllocatorT));
	allocator->allocate = SparkAllocate;
	allocator->reallocate = SparkReallocate;
	allocator->free = SparkFree;
	return allocator;
}

SPARKAPI SparkAllocator SparkCreateAllocator(SparkAllocateFunction allocate, SparkReallocateFunction reallocate, SparkFreeFunction free) {
	SparkAllocator allocator = allocate(sizeof(struct SparkAllocatorT));
	allocator->allocate = allocate;
	allocator->reallocate = reallocate;
	allocator->free = free;
	return allocator;
}

SPARKAPI SparkVoid SparkDestroyAllocator(SparkAllocator allocator) {
	allocator->free(allocator);
}



#pragma endregion

#pragma region VECTOR

SPARKAPI SparkVector SparkDefaultVector() {
	SparkVector vector = SparkAllocate(sizeof(struct SparkVectorT));
	vector->allocator = SparkDefaultAllocator();
	vector->capacity = 1;
	vector->size = 0;
	vector->destructor = NULL; // Default destructor is NULL
	vector->elements = vector->allocator->allocate(vector->capacity * sizeof(SparkHandle));
	vector->external_allocator = SPARK_FALSE;
	return vector;
}

SPARKAPI SparkVector SparkCreateVector(SparkSize capacity, SparkAllocator allocator, SparkFreeFunction destructor) {
	SparkBool external_allocator = SPARK_TRUE;

	if (!allocator) {
		allocator = SparkDefaultAllocator();
		external_allocator = SPARK_FALSE;
	}

	SparkVector vector = allocator->allocate(sizeof(struct SparkVectorT));
	vector->allocator = allocator;
	vector->capacity = capacity;
	vector->size = 0;
	vector->destructor = destructor; // Set destructor
	vector->elements = allocator->allocate(vector->capacity * sizeof(SparkHandle));
	vector->external_allocator = external_allocator;
	return vector;
}

SPARKAPI SparkVoid SparkDestroyVector(SparkVector vector) {
	SparkAllocator allocator = vector->allocator;

	// Call destructor on each element if destructor is not NULL
	if (vector->destructor != NULL) {
		for (SparkSize i = 0; i < vector->size; i++) {
			vector->destructor(vector->elements[i]);
		}
	}

	allocator->free(vector->elements);

	SparkBool external_allocator = vector->external_allocator;

	allocator->free(vector);

	if (!external_allocator) {
		SparkDestroyAllocator(allocator);
	}
}

SPARKAPI SparkHandle SparkGetElementVector(SparkVector vector, SparkSize index) {
	if (index >= vector->size) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Index out of bounds!");
		return SPARK_NULL;
	}
	return vector->elements[index];
}

SPARKAPI SparkResult SparkPushBackVector(SparkVector vector, SparkHandle element) {
	if (vector->size >= vector->capacity) {
		vector->capacity *= 2;
		vector->elements = vector->allocator->reallocate(vector->elements, vector->capacity * sizeof(SparkHandle));
		if (vector->elements == SPARK_NULL) {
			SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to reallocate vector!");
			return SPARK_ERROR_INVALID_STATE;
		}
	}
	vector->elements[vector->size++] = element;
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkPopBackVector(SparkVector vector) {
	if (vector->size == 0) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Vector is empty!");
		return SPARK_ERROR_INVALID_STATE;
	}
	vector->size--;

	// Call destructor on the element if destructor is not NULL
	if (vector->destructor != NULL) {
		vector->destructor(vector->elements[vector->size]);
	}

	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkInsertVector(SparkVector vector, SparkSize index, SparkHandle element) {
	if (index > vector->size) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Index out of bounds!");
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	if (vector->size >= vector->capacity) {
		vector->capacity *= 2;
		vector->elements = vector->allocator->reallocate(vector->elements, vector->capacity * sizeof(SparkHandle));
		if (vector->elements == SPARK_NULL) {
			SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to reallocate vector!");
			return SPARK_ERROR_INVALID_STATE;
		}
	}

	// Move elements to make space
	for (SparkSize i = vector->size; i > index; i--) {
		vector->elements[i] = vector->elements[i - 1];
	}

	vector->elements[index] = element;
	vector->size++;
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkRemoveVector(SparkVector vector, SparkSize index) {
	if (index >= vector->size) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Index out of bounds!");
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	// Call destructor on the element if destructor is not NULL
	if (vector->destructor != NULL) {
		vector->destructor(vector->elements[index]);
	}

	// Move elements to fill the gap
	for (SparkSize i = index; i < vector->size - 1; i++) {
		vector->elements[i] = vector->elements[i + 1];
	}
	vector->size--;
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkEraseVector(SparkVector vector, SparkSize begin, SparkSize end) {
	for (SparkSize i = begin; i < end; i++) {
		if (i >= vector->size) {
			SparkLog(SPARK_LOG_LEVEL_ERROR, "Index out of bounds!");
			return SPARK_ERROR_INVALID_ARGUMENT;
		}

		// Call destructor on the element if destructor is not NULL
		if (vector->destructor != NULL) {
			vector->destructor(vector->elements[i]);
		}
	}

	// Move elements to fill the gap
	for (SparkSize i = begin; i < vector->size - (end - begin); i++) {
		vector->elements[i] = vector->elements[i + (end - begin)];
	}

	vector->size -= (end - begin);
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkSetVector(SparkVector vector, SparkSize index, SparkHandle element) {
	if (index >= vector->size) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Index out of bounds!");
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	// Call destructor on the existing element if destructor is not NULL
	if (vector->destructor != NULL) {
		vector->destructor(vector->elements[index]);
	}

	vector->elements[index] = element;
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkResizeVector(SparkVector vector, SparkSize capacity) {
	if (capacity < vector->size) {
		// If new capacity is less than current size, need to destroy extra elements
		if (vector->destructor != NULL) {
			for (SparkSize i = capacity; i < vector->size; i++) {
				vector->destructor(vector->elements[i]);
			}
		}
		vector->size = capacity;
	}
	vector->capacity = capacity;
	vector->elements = vector->allocator->reallocate(vector->elements, vector->capacity * sizeof(SparkHandle));
	if (vector->elements == SPARK_NULL) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to reallocate vector!");
		return SPARK_ERROR_INVALID_STATE;
	}
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkClearVector(SparkVector vector) {
	// Call destructor on each element if destructor is not NULL
	if (vector->destructor != NULL) {
		for (SparkSize i = 0; i < vector->size; i++) {
			vector->destructor(vector->elements[i]);
		}
	}
	vector->size = 0;
	return SPARK_SUCCESS;
}

#pragma endregion

#pragma region LIST

SPARKAPI SparkList SparkDefaultList() {
	SparkList list = SparkAllocate(sizeof(struct SparkListT));
	list->allocator = SparkDefaultAllocator();
	list->destructor = NULL; // Default destructor is NULL
	list->head = SPARK_NULL;
	list->tail = SPARK_NULL;
	list->size = 0;
	list->external_allocator = SPARK_FALSE;
	return list;
}

SPARKAPI SparkList SparkCreateList(SparkAllocator allocator, SparkFreeFunction destructor) {
	SparkBool external_allocator = SPARK_TRUE;

	if (!allocator) {
		allocator = SparkDefaultAllocator();
		external_allocator = SPARK_FALSE;
	}

	SparkList list = allocator->allocate(sizeof(struct SparkListT));
	list->allocator = allocator;
	list->destructor = destructor;
	list->head = SPARK_NULL;
	list->tail = SPARK_NULL;
	list->size = 0;
	list->external_allocator = external_allocator;
	return list;
}

SPARKAPI SparkVoid SparkDestroyList(SparkList list) {
	SparkAllocator allocator = list->allocator;

	// Call destructor on each element if destructor is not NULL
	SparkListNode node = list->head;
	while (node != SPARK_NULL) {
		if (list->destructor != NULL) {
			list->destructor(node->data);
		}
		SparkListNode temp = node;
		node = node->next;
		allocator->free(temp);
	}

	SparkBool external_allocator = list->external_allocator;

	allocator->free(list);

	if (!external_allocator) {
		SparkDestroyAllocator(allocator);
	}
}

SPARKAPI SparkHandle SparkGetElementList(SparkList list, SparkIndex index) {
	if (index >= list->size) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Index out of bounds!");
		return SPARK_NULL;
	}

	SparkListNode node = list->head;
	while (index-- > 0) {
		node = node->next;
	}
	return node->data;
}

SPARKAPI SparkResult SparkPushBackList(SparkList list, SparkHandle element) {
	SparkListNode node = list->allocator->allocate(sizeof(struct SparkListNodeT));
	node->data = element;
	node->next = SPARK_NULL;

	if (list->head == SPARK_NULL) {
		list->head = node;
		list->tail = node;
	}
	else {
		list->tail->next = node;
		list->tail = node;
	}

	list->size++;
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkPopBackList(SparkList list) {
	if (list->size == 0) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "List is empty!");
		return SPARK_ERROR_INVALID_STATE;
	}

	SparkListNode node = list->head;
	SparkListNode prev = SPARK_NULL;

	while (node->next != SPARK_NULL) {
		prev = node;
		node = node->next;
	}

	// Call destructor on the element if destructor is not NULL
	if (list->destructor != NULL) {
		list->destructor(node->data);
	}

	if (prev != SPARK_NULL) {
		prev->next = SPARK_NULL;
		list->tail = prev;
	}
	else {
		list->head = SPARK_NULL;
		list->tail = SPARK_NULL;
	}

	list->allocator->free(node);
	list->size--;
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkInsertList(SparkList list, SparkIndex index, SparkHandle element) {
	if (index > list->size) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Index out of bounds!");
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	SparkListNode node = list->allocator->allocate(sizeof(struct SparkListNodeT));
	node->data = element;

	if (index == 0) {
		node->next = list->head;
		list->head = node;
		if (list->size == 0) {
			list->tail = node;
		}
	}
	else {
		SparkListNode prev = list->head;
		for (SparkIndex i = 0; i < index - 1; i++) {
			prev = prev->next;
		}
		node->next = prev->next;
		prev->next = node;
		if (node->next == SPARK_NULL) {
			list->tail = node;
		}
	}

	list->size++;
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkRemoveList(SparkList list, SparkIndex index) {
	if (index >= list->size) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Index out of bounds!");
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	SparkListNode node_to_remove;
	if (index == 0) {
		node_to_remove = list->head;
		list->head = node_to_remove->next;
		if (list->head == SPARK_NULL) {
			list->tail = SPARK_NULL;
		}
	}
	else {
		SparkListNode prev = list->head;
		for (SparkIndex i = 0; i < index - 1; i++) {
			prev = prev->next;
		}
		node_to_remove = prev->next;
		prev->next = node_to_remove->next;
		if (prev->next == SPARK_NULL) {
			list->tail = prev;
		}
	}

	// Call destructor on the element if destructor is not NULL
	if (list->destructor != NULL) {
		list->destructor(node_to_remove->data);
	}

	list->allocator->free(node_to_remove);
	list->size--;
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkSetList(SparkList list, SparkIndex index, SparkHandle element) {
	if (index >= list->size) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Index out of bounds!");
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	SparkListNode node = list->head;
	for (SparkIndex i = 0; i < index; i++) {
		node = node->next;
	}

	// Call destructor on the existing element if destructor is not NULL
	if (list->destructor != NULL) {
		list->destructor(node->data);
	}

	node->data = element;
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkClearList(SparkList list) {
	SparkListNode node = list->head;
	while (node != SPARK_NULL) {
		if (list->destructor != NULL) {
			list->destructor(node->data);
		}
		SparkListNode temp = node;
		node = node->next;
		list->allocator->free(temp);
	}
	list->head = SPARK_NULL;
	list->tail = SPARK_NULL;
	list->size = 0;
	return SPARK_SUCCESS;
}

#pragma endregion

#pragma region HASH

// 1. DJB2 (Original version)
// Fast and simple, good for strings
SparkSize DJB2Hash(SparkConstBuffer data, SparkSize size) {
	SparkSize hash = 5381;
	for (SparkSize i = 0; i < size; i++) {
		hash = ((hash << 5) + hash) + data[i];
	}
	return hash;
}

// 2. FNV-1a
// Simple and effective, good balance of speed and distribution
#define FNV_PRIME 0x01000193
#define FNV_OFFSET 0x811c9dc5
SparkSize FNV1AHash(SparkConstBuffer data, SparkSize size) {
	SparkSize hash = FNV_OFFSET;
	for (SparkSize i = 0; i < size; i++) {
		hash ^= data[i];
		hash *= FNV_PRIME;
	}
	return hash;
}

// 3. Jenkins One-at-a-time
// Good distribution, a bit slower than FNV-1a
SparkSize JenkinsHash(SparkConstBuffer data, SparkSize size) {
	SparkSize hash = 0;
	for (SparkSize i = 0; i < size; i++) {
		hash += data[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}

// 4. MurmurHash2
// Fast hash with good distribution
SparkSize Murmur2Hash(SparkConstBuffer data, SparkSize size) {
	const SparkSize m = 0x5bd1e995;
	const SparkSize r = 24;
	SparkSize h = size ^ 0x5BD1E995;
	const SparkSize* p = (const SparkSize*)data;

	while (size >= 4) {
		SparkSize k = *p++;
		k *= m;
		k ^= k >> r;
		k *= m;
		h *= m;
		h ^= k;
		size -= 4;
	}

	switch (size) {
	case 3:
		h ^= data[2] << 16;
	case 2:
		h ^= data[1] << 8;
	case 1:
		h ^= data[0];
		h *= m;
	};

	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h;
}

// 5. SipHash-2-4 (simplified, 64-bit version)
// Cryptographically strong, but slower
#define ROTL(x, b) (SparkSize)(((x) << (b)) | ((x) >> (64 - (b))))
#define SIPROUND                                                               \
  do {                                                                         \
    v0 += v1;                                                                  \
    v1 = ROTL(v1, 13);                                                         \
    v1 ^= v0;                                                                  \
    v0 = ROTL(v0, 32);                                                         \
    v2 += v3;                                                                  \
    v3 = ROTL(v3, 16);                                                         \
    v3 ^= v2;                                                                  \
    v0 += v3;                                                                  \
    v3 = ROTL(v3, 21);                                                         \
    v3 ^= v0;                                                                  \
    v2 += v1;                                                                  \
    v1 = ROTL(v1, 17);                                                         \
    v1 ^= v2;                                                                  \
    v2 = ROTL(v2, 32);                                                         \
  } while (0)

SparkSize SipHash(SparkConstBuffer data, SparkSize size) {
	SparkSize k0 = 0x0706050403020100ULL;
	SparkSize k1 = 0x0F0E0D0C0B0A0908ULL;
	SparkSize v0 = 0x736f6d6570736575ULL ^ k0;
	SparkSize v1 = 0x646f72616e646f6dULL ^ k1;
	SparkSize v2 = 0x6c7967656e657261ULL ^ k0;
	SparkSize v3 = 0x7465646279746573ULL ^ k1;
	SparkSize b = ((SparkSize)size) << 56;

	while (size >= 8) {
		SparkSize m = *(SparkSize*)data;
		v3 ^= m;
		for (SparkSize i = 0; i < 2; i++)
			SIPROUND;
		v0 ^= m;
		data += 8;
		size -= 8;
	}

	switch (size) {
	case 7:
		b |= ((SparkSize)data[6]) << 48;
	case 6:
		b |= ((SparkSize)data[5]) << 40;
	case 5:
		b |= ((SparkSize)data[4]) << 32;
	case 4:
		b |= ((SparkSize)data[3]) << 24;
	case 3:
		b |= ((SparkSize)data[2]) << 16;
	case 2:
		b |= ((SparkSize)data[1]) << 8;
	case 1:
		b |= ((SparkSize)data[0]);
	}

	v3 ^= b;
	for (SparkSize i = 0; i < 2; i++)
		SIPROUND;
	v0 ^= b;
	v2 ^= 0xff;
	for (SparkSize i = 0; i < 4; i++)
		SIPROUND;
	return v0 ^ v1 ^ v2 ^ v3;
}

// 6. XXHash (64-bit version)
#define PRIME32_1 2654435761U
#define PRIME32_2 2246822519U
#define PRIME32_3 3266489917U
#define PRIME32_4  668265263U
#define PRIME32_5  374761393U

SparkSize XXHash(SparkConstBuffer data, SparkSize length) {
	SparkConstBuffer end = data + length;
	SparkSize hash;

	if (length >= 16) {
		SparkConstBuffer limit = end - 16;
		SparkSize v1 = PRIME32_1 + PRIME32_2;
		SparkSize v2 = PRIME32_2;
		SparkSize v3 = 0;
		SparkSize v4 = -PRIME32_1;

		do {
			v1 += *((const SparkU32*)data) * PRIME32_2; data += 4;
			v1 = (v1 << 13) | (v1 >> 19); // Rotate left 13 bits
			v1 *= PRIME32_1;

			v2 += *((const SparkU32*)data) * PRIME32_2; data += 4;
			v2 = (v2 << 13) | (v2 >> 19); // Rotate left 13 bits
			v2 *= PRIME32_1;

			v3 += *((const SparkU32*)data) * PRIME32_2; data += 4;
			v3 = (v3 << 13) | (v3 >> 19); // Rotate left 13 bits
			v3 *= PRIME32_1;

			v4 += *((const SparkU32*)data) * PRIME32_2; data += 4;
			v4 = (v4 << 13) | (v4 >> 19); // Rotate left 13 bits
			v4 *= PRIME32_1;
		} while (data <= limit);

		hash = ((v1 << 1) | (v1 >> 31)) + ((v2 << 7) | (v2 >> 25)) + ((v3 << 12) | (v3 >> 20)) + ((v4 << 18) | (v4 >> 14));
	}
	else {
		hash = PRIME32_5;
	}

	hash += length;

	while (data + 4 <= end) {
		hash += *((const SparkU32*)data) * PRIME32_3;
		hash = ((hash << 17) | (hash >> 15)) * PRIME32_4;
		data += 4;
	}

	while (data < end) {
		hash += (*data) * PRIME32_5;
		hash = ((hash << 11) | (hash >> 21)) * PRIME32_1;
		data++;
	}

	hash ^= hash >> 15;
	hash *= PRIME32_2;
	hash ^= hash >> 13;
	hash *= PRIME32_3;
	hash ^= hash >> 16;

	return hash;
}

#pragma endregion

#pragma region HASHMAP

SPARKAPI SparkHashMap SparkDefaultHashMap() {
	SparkHashMap hashmap = SparkAllocate(sizeof(struct SparkHashMapT));
	hashmap->allocator = SparkDefaultAllocator();
	hashmap->capacity = 16; // Default capacity
	hashmap->hash = FNV1AHash;
	hashmap->size = 0;
	hashmap->key_destructor = NULL;   // Default to NULL
	hashmap->value_destructor = NULL; // Default to NULL
	hashmap->external_allocator = SPARK_FALSE;

	// Allocate buckets array
	hashmap->buckets = hashmap->allocator->allocate(hashmap->capacity * sizeof(SparkList));
	for (SparkSize i = 0; i < hashmap->capacity; i++) {
		hashmap->buckets[i] = SparkCreateList(hashmap->allocator, NULL); // Create lists with no destructor
	}
	return hashmap;
}

SPARKAPI SparkHashMap SparkCreateHashMap(SparkSize capacity, SparkHashFunction hash, SparkAllocator allocator, SparkFreeFunction key_destructor, SparkFreeFunction value_destructor) {
	SparkBool external_allocator = SPARK_TRUE;

	if (!allocator) {
		allocator = SparkDefaultAllocator();
		external_allocator = SPARK_FALSE;
	}

	if (!hash) {
		hash = FNV1AHash;
	}

	SparkHashMap hashmap = allocator->allocate(sizeof(struct SparkHashMapT));
	hashmap->capacity = capacity;
	hashmap->hash = hash;
	hashmap->allocator = allocator;
	hashmap->size = 0;
	hashmap->key_destructor = key_destructor;
	hashmap->value_destructor = value_destructor;
	hashmap->external_allocator = external_allocator;

	// Allocate buckets array
	hashmap->buckets = allocator->allocate(hashmap->capacity * sizeof(SparkList));
	for (SparkSize i = 0; i < hashmap->capacity; i++) {
		hashmap->buckets[i] = SparkCreateList(allocator, NULL); // Create lists with no destructor
	}
	return hashmap;
}

SPARKAPI SparkVoid SparkDestroyHashMap(SparkHashMap hashmap) {
	SparkAllocator allocator = hashmap->allocator;

	for (SparkSize i = 0; i < hashmap->capacity; i++) {
		SparkList bucket = hashmap->buckets[i];

		SparkListNode node = bucket->head;
		while (node != SPARK_NULL) {
			SparkHashMapNode hashmap_node = (SparkHashMapNode)node->data;

			// Call destructors on key and value, ensuring no double free
			if (hashmap->key_destructor != NULL) {
				hashmap->key_destructor(hashmap_node->key);
			}
			if (hashmap->value_destructor != NULL) {
				if (hashmap_node->value != hashmap_node->key) {
					hashmap->value_destructor(hashmap_node->value);
				}
			}

			allocator->free(hashmap_node);
			node = node->next;
		}

		// Destroy the bucket list
		SparkDestroyList(bucket);
	}

	allocator->free(hashmap->buckets);

	SparkBool external_allocator = hashmap->external_allocator;

	allocator->free(hashmap);

	if (!external_allocator) {
		SparkDestroyAllocator(allocator);
	}
}

SPARKAPI SparkHandle SparkGetElementHashMap(SparkHashMap hashmap, SparkConstBuffer key, SparkSize key_size) {
	SparkSize hash_value = hashmap->hash(key, key_size);
	SparkSize index = hash_value % hashmap->capacity;

	SparkList bucket = hashmap->buckets[index];
	SparkListNode node = bucket->head;

	while (node != SPARK_NULL) {
		SparkHashMapNode hashmap_node = (SparkHashMapNode)node->data;
		if (hashmap_node->hash == hash_value && hashmap_node->key_size == key_size && memcmp(hashmap_node->key, key, key_size) == 0) {
			return hashmap_node->value;
		}
		node = node->next;
	}

	return SPARK_NULL;
}

SPARKAPI SparkResult SparkInsertHashMap(SparkHashMap hashmap, SparkHandle key, SparkSize key_size, SparkHandle value) {
	SparkSize hash_value = hashmap->hash(key, key_size);
	SparkSize index = hash_value % hashmap->capacity;

	SparkList bucket = hashmap->buckets[index];
	SparkListNode node = bucket->head;

	while (node != SPARK_NULL) {
		SparkHashMapNode hashmap_node = (SparkHashMapNode)node->data;
		if (hashmap_node->hash == hash_value && hashmap_node->key_size == key_size && memcmp(hashmap_node->key, key, key_size) == 0) {
			// Key already exists, update value
			if (hashmap->value_destructor != NULL) {
				hashmap->value_destructor(hashmap_node->value);
			}
			hashmap_node->value = value;
			return SPARK_SUCCESS;
		}
		node = node->next;
	}

	// Key not found, insert new node
	SparkHashMapNode new_node = hashmap->allocator->allocate(sizeof(struct SparkHashMapNodeT));
	new_node->key = key;
	new_node->value = value;
	new_node->key_size = key_size;
	new_node->hash = hash_value;

	SparkPushBackList(bucket, new_node);
	hashmap->size++;

	// Optionally, check load factor and resize if necessary
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkRemoveHashMap(SparkHashMap hashmap, SparkConstBuffer key, SparkSize key_size) {
	SparkSize hash_value = hashmap->hash(key, key_size);
	SparkSize index = hash_value % hashmap->capacity;

	SparkList bucket = hashmap->buckets[index];
	SparkListNode prev = SPARK_NULL;
	SparkListNode node = bucket->head;

	while (node != SPARK_NULL) {
		SparkHashMapNode hashmap_node = (SparkHashMapNode)node->data;
		if (hashmap_node->hash == hash_value &&
			hashmap_node->key_size == key_size &&
			memcmp(hashmap_node->key, key, key_size) == 0) {

			// Call destructors on key and value, ensuring no double free
			if (hashmap->key_destructor != NULL) {
				hashmap->key_destructor(hashmap_node->key);
			}
			if (hashmap->value_destructor != NULL) {
				if (hashmap_node->value != hashmap_node->key) {
					hashmap->value_destructor(hashmap_node->value);
				}
			}

			hashmap->allocator->free(hashmap_node);

			// Remove node from the list
			if (prev == SPARK_NULL) {
				bucket->head = node->next;
			}
			else {
				prev->next = node->next;
			}
			if (node == bucket->tail) {
				bucket->tail = prev;
			}
			bucket->allocator->free(node);
			bucket->size--;
			hashmap->size--;
			return SPARK_SUCCESS;
		}
		prev = node;
		node = node->next;
	}
	return SPARK_ERROR_NOT_FOUND;
}

SPARKAPI SparkResult SparkClearHashMap(SparkHashMap hashmap) {
	for (SparkSize i = 0; i < hashmap->capacity; i++) {
		SparkList bucket = hashmap->buckets[i];
		SparkListNode node = bucket->head;
		while (node != SPARK_NULL) {
			SparkHashMapNode hashmap_node = (SparkHashMapNode)node->data;

			// Call destructors on key and value, ensuring no double free
			if (hashmap->key_destructor != NULL) {
				hashmap->key_destructor(hashmap_node->key);
			}
			if (hashmap->value_destructor != NULL) {
				if (hashmap_node->value != hashmap_node->key) {
					hashmap->value_destructor(hashmap_node->value);
				}
			}

			hashmap->allocator->free(hashmap_node);
			node = node->next;
		}
		SparkClearList(bucket);
	}
	hashmap->size = 0;
	return SPARK_SUCCESS;
}

#pragma endregion

#pragma region SET

SPARKAPI SparkSet SparkDefaultSet() {
	return SparkCreateSet(1, NULL, NULL);
}

SPARKAPI SparkSet SparkCreateSet(SparkSize capacity, SparkAllocator allocator, SparkFreeFunction destructor) {
	SparkBool external_allocator = SPARK_TRUE;

	if (!allocator) {
		allocator = SparkDefaultAllocator();
		external_allocator = SPARK_FALSE;
	}

	SparkSet set = allocator->allocate(sizeof(struct SparkSetT));
	if (set == SPARK_NULL) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to allocate memory for set!");
		if (!external_allocator) {
			SparkDestroyAllocator(allocator);
		}
		return SPARK_NULL;
	}

	set->allocator = allocator;
	set->capacity = capacity;
	set->size = 0;
	set->destructor = destructor;
	set->external_allocator = external_allocator;

	set->elements = allocator->allocate(set->capacity * sizeof(SparkHandle));
	if (set->elements == SPARK_NULL) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to allocate memory for set elements!");
		allocator->free(set);
		if (!external_allocator) {
			SparkDestroyAllocator(allocator);
		}
		return SPARK_NULL;
	}
	return set;
}

SPARKAPI SparkVoid SparkDestroySet(SparkSet set) {
	if (set == SPARK_NULL) {
		return;
	}
	SparkAllocator allocator = set->allocator;

	// Call destructor on each element if destructor is not NULL
	if (set->destructor != NULL) {
		for (SparkSize i = 0; i < set->size; i++) {
			if (set->elements[i] != SPARK_NULL) {
				set->destructor(set->elements[i]);
				set->elements[i] = SPARK_NULL; // Optional, to avoid dangling pointers
			}
		}
	}

	if (set->elements != SPARK_NULL) {
		allocator->free(set->elements);
		set->elements = SPARK_NULL;
	}

	SparkBool external_allocator = set->external_allocator;

	allocator->free(set);
	set = SPARK_NULL;

	if (!external_allocator) {
		SparkDestroyAllocator(allocator);
	}
}

SPARKAPI SparkHandle SparkGetElementSet(SparkSet set, SparkSize index) {
	if (set == SPARK_NULL || set->elements == SPARK_NULL) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Set is NULL!");
		return SPARK_NULL;
	}
	if (index >= set->size) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Index out of bounds!");
		return SPARK_NULL;
	}
	return set->elements[index];
}

SPARKAPI SparkBool SparkContainsSet(SparkSet set, SparkHandle element, SparkCompareFunction compare) {
	if (set == SPARK_NULL || set->elements == SPARK_NULL || compare == SPARK_NULL) {
		return SPARK_FALSE;
	}
	for (SparkSize i = 0; i < set->size; i++) {
		if (compare(set->elements[i], element) == 0) {
			return SPARK_TRUE;
		}
	}
	return SPARK_FALSE;
}

SPARKAPI SparkResult SparkInsertSet(SparkSet set, SparkHandle element, SparkCompareFunction compare) {
	if (set == SPARK_NULL || element == SPARK_NULL || compare == SPARK_NULL) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	if (SparkContainsSet(set, element, compare)) {
		return SPARK_SUCCESS; // Element already in set
	}

	if (set->size >= set->capacity) {
		SparkSize new_capacity = set->capacity * 2;
		SparkHandle* new_elements = set->allocator->reallocate(set->elements, new_capacity * sizeof(SparkHandle));
		if (new_elements == SPARK_NULL) {
			SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to reallocate set!");
			return SPARK_ERROR_OUT_OF_MEMORY;
		}
		set->elements = new_elements;
		set->capacity = new_capacity;
	}

	set->elements[set->size++] = element;
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkRemoveSet(SparkSet set, SparkHandle element, SparkCompareFunction compare) {
	if (set == SPARK_NULL || element == SPARK_NULL || compare == SPARK_NULL) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	SparkSize index = set->size;
	for (SparkSize i = 0; i < set->size; i++) {
		if (compare(set->elements[i], element) == 0) {
			index = i;
			break;
		}
	}

	if (index == set->size) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Element not found in set!");
		return SPARK_ERROR_NOT_FOUND;
	}

	// Call destructor on the element if destructor is not NULL
	if (set->destructor != NULL && set->elements[index] != SPARK_NULL) {
		set->destructor(set->elements[index]);
		set->elements[index] = SPARK_NULL; // Optional
	}

	// Move elements to fill the gap
	for (SparkSize i = index; i < set->size - 1; i++) {
		set->elements[i] = set->elements[i + 1];
	}
	set->size--;
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkClearSet(SparkSet set) {
	if (set == SPARK_NULL) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	// Call destructor on each element if destructor is not NULL
	if (set->destructor != NULL) {
		for (SparkSize i = 0; i < set->size; i++) {
			if (set->elements[i] != SPARK_NULL) {
				set->destructor(set->elements[i]);
				set->elements[i] = SPARK_NULL;
			}
		}
	}
	set->size = 0;
	return SPARK_SUCCESS;
}

#pragma endregion

#pragma region HASH_SET

SPARKAPI SparkHashSet SparkDefaultHashSet() {
	return SparkCreateHashSet(16, sizeof(SparkHandle), NULL, NULL, NULL);
}

SPARKAPI SparkHashSet SparkCreateHashSet(SparkSize capacity, SparkSize element_size, SparkHashFunction hash, SparkAllocator allocator, SparkFreeFunction destructor) {
	SparkBool external_allocator = SPARK_TRUE;

	if (!allocator) {
		allocator = SparkDefaultAllocator();
		external_allocator = SPARK_FALSE;
	}

	if (!hash) {
		hash = DJB2Hash; // Use default hash function if none provided
	}

	SparkHashSet hashset = allocator->allocate(sizeof(struct SparkHashSetT));
	if (hashset == SPARK_NULL) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to allocate memory for hashset!");
		if (!external_allocator) {
			SparkDestroyAllocator(allocator);
		}
		return SPARK_NULL;
	}

	hashset->allocator = allocator;
	hashset->capacity = capacity;
	hashset->size = 0;
	hashset->destructor = destructor;
	hashset->hash_function = hash;
	hashset->external_allocator = external_allocator;
	hashset->element_size = element_size;

	hashset->elements = allocator->allocate(hashset->capacity * sizeof(SparkHandle));
	if (hashset->elements == SPARK_NULL) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to allocate memory for hashset elements!");
		allocator->free(hashset);
		if (!external_allocator) {
			SparkDestroyAllocator(allocator);
		}
		return SPARK_NULL;
	}

	hashset->hashes = allocator->allocate(hashset->capacity * sizeof(SparkSize));
	if (hashset->hashes == SPARK_NULL) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to allocate memory for hashset hashes!");
		allocator->free(hashset->elements);
		allocator->free(hashset);
		if (!external_allocator) {
			SparkDestroyAllocator(allocator);
		}
		return SPARK_NULL;
	}

	// Initialize elements and hashes
	for (SparkSize i = 0; i < hashset->capacity; i++) {
		hashset->elements[i] = SPARK_NULL;
		hashset->hashes[i] = 0;
	}

	return hashset;
}

SPARKAPI SparkVoid SparkDestroyHashSet(SparkHashSet hashset) {
	if (hashset == SPARK_NULL) {
		return;
	}
	SparkAllocator allocator = hashset->allocator;

	// Call destructor on each element if destructor is not NULL
	if (hashset->destructor != NULL) {
		for (SparkSize i = 0; i < hashset->capacity; i++) {
			if (hashset->elements[i] != SPARK_NULL) {
				hashset->destructor(hashset->elements[i]);
				hashset->elements[i] = SPARK_NULL; // Optional
			}
		}
	}

	if (hashset->elements != SPARK_NULL) {
		allocator->free(hashset->elements);
		hashset->elements = SPARK_NULL;
	}

	if (hashset->hashes != SPARK_NULL) {
		allocator->free(hashset->hashes);
		hashset->hashes = SPARK_NULL;
	}

	SparkBool external_allocator = hashset->external_allocator;

	allocator->free(hashset);
	hashset = SPARK_NULL;

	if (!external_allocator) {
		SparkDestroyAllocator(allocator);
	}
}

SPARKAPI SPARKSTATIC SparkResult SparkHashSetResize(SparkHashSet hashset, SparkSize new_capacity) {
	SparkHandle* old_elements = hashset->elements;
	SparkSize* old_hashes = hashset->hashes;
	SparkSize old_capacity = hashset->capacity;

	hashset->capacity = new_capacity;
	hashset->elements = hashset->allocator->allocate(hashset->capacity * sizeof(SparkHandle));
	hashset->hashes = hashset->allocator->allocate(hashset->capacity * sizeof(SparkSize));

	if (hashset->elements == SPARK_NULL || hashset->hashes == SPARK_NULL) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to allocate memory for hashset resizing!");

		// Restore old capacity
		hashset->capacity = old_capacity;

		// Clean up any allocated memory
		if (hashset->elements != SPARK_NULL) {
			hashset->allocator->free(hashset->elements);
			hashset->elements = old_elements; // Restore old pointers
		}
		if (hashset->hashes != SPARK_NULL) {
			hashset->allocator->free(hashset->hashes);
			hashset->hashes = old_hashes;
		}
		return SPARK_ERROR_OUT_OF_MEMORY;
	}

	// Initialize new elements and hashes
	for (SparkSize i = 0; i < hashset->capacity; i++) {
		hashset->elements[i] = SPARK_NULL;
		hashset->hashes[i] = 0;
	}

	// Rehash all elements
	SparkSize old_size = hashset->size;
	hashset->size = 0;
	for (SparkSize i = 0; i < old_capacity; i++) {
		if (old_elements[i] != SPARK_NULL) {
			SparkResult res = SparkInsertHashSet(hashset, old_elements[i], hashset->element_size);
			if (res != SPARK_SUCCESS) {
				SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to re-insert element during hashset resizing!");

				// Free new elements and hashes
				hashset->allocator->free(hashset->elements);
				hashset->allocator->free(hashset->hashes);

				// Restore old pointers and capacity
				hashset->elements = old_elements;
				hashset->hashes = old_hashes;
				hashset->capacity = old_capacity;
				hashset->size = old_size;

				return res;
			}
		}
	}

	// Free old elements and hashes
	hashset->allocator->free(old_elements);
	hashset->allocator->free(old_hashes);

	return SPARK_SUCCESS;
}

SPARKAPI SparkBool SparkContainsHashSet(SparkHashSet hashset, SparkHandle element, SparkSize element_size) {
	if (hashset == SPARK_NULL || element == SPARK_NULL) {
		return SPARK_FALSE;
	}
	SparkSize element_hash = hashset->hash_function((SparkConstBuffer)element, element_size);
	SparkSize index = element_hash % hashset->capacity;

	SparkSize original_index = index;
	while (hashset->elements[index] != SPARK_NULL) {
		if (hashset->hashes[index] == element_hash) {
			// Possible match (add actual comparison if necessary)
			return SPARK_TRUE;
		}
		index = (index + 1) % hashset->capacity;
		if (index == original_index) {
			break; // Table is full
		}
	}
	return SPARK_FALSE;
}

SPARKAPI SparkResult SparkInsertHashSet(SparkHashSet hashset, SparkHandle element, SparkSize element_size) {
	if (hashset == SPARK_NULL || element == SPARK_NULL) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	if ((hashset->size + 1) * 100 / hashset->capacity > 75) {
		// Resize if load factor exceeds 75%
		SparkResult res = SparkHashSetResize(hashset, hashset->capacity * 2);
		if (res != SPARK_SUCCESS) {
			return res;
		}
	}

	SparkSize element_hash = hashset->hash_function((SparkConstBuffer)element, element_size);
	SparkSize index = element_hash % hashset->capacity;

	while (hashset->elements[index] != SPARK_NULL) {
		if (hashset->hashes[index] == element_hash) {
			// Element already exists
			return SPARK_SUCCESS;
		}
		index = (index + 1) % hashset->capacity;
	}

	hashset->elements[index] = element;
	hashset->hashes[index] = element_hash;
	hashset->size++;
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkRemoveHashSet(SparkHashSet hashset, SparkHandle element, SparkSize element_size) {
	if (hashset == SPARK_NULL || element == SPARK_NULL) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	SparkSize element_hash = hashset->hash_function((SparkConstBuffer)element, element_size);
	SparkSize index = element_hash % hashset->capacity;

	SparkSize original_index = index;
	while (hashset->elements[index] != SPARK_NULL) {
		if (hashset->hashes[index] == element_hash) {
			// Call destructor on the element if destructor is not NULL
			if (hashset->destructor != NULL) {
				hashset->destructor(hashset->elements[index]);
			}

			hashset->elements[index] = SPARK_NULL;
			hashset->hashes[index] = 0;
			hashset->size--;
			return SPARK_SUCCESS;
		}
		index = (index + 1) % hashset->capacity;
		if (index == original_index) {
			break; // Came full circle
		}
	}

	SparkLog(SPARK_LOG_LEVEL_ERROR, "Element not found in hashset!");
	return SPARK_ERROR_NOT_FOUND;
}

SPARKAPI SparkResult SparkClearHashSet(SparkHashSet hashset) {
	if (hashset == SPARK_NULL) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	// Call destructor on each element if destructor is not NULL
	if (hashset->destructor != NULL) {
		for (SparkSize i = 0; i < hashset->capacity; i++) {
			if (hashset->elements[i] != SPARK_NULL) {
				hashset->destructor(hashset->elements[i]);
				hashset->elements[i] = SPARK_NULL;
			}
		}
	}

	// Reset elements and hashes
	for (SparkSize i = 0; i < hashset->capacity; i++) {
		hashset->elements[i] = SPARK_NULL;
		hashset->hashes[i] = 0;
	}

	hashset->size = 0;
	return SPARK_SUCCESS;
}

#pragma endregion

#pragma region QUEUE

SPARKAPI SparkQueue SparkDefaultQueue() {
	return SparkCreateQueue(16, NULL, NULL);
}

SPARKAPI SparkQueue SparkCreateQueue(SparkSize capacity, SparkAllocator allocator, SparkFreeFunction destructor) {
	SparkBool external_allocator = SPARK_TRUE;

	if (!allocator) {
		allocator = SparkDefaultAllocator();
		external_allocator = SPARK_FALSE;
	}

	SparkQueue queue = allocator->allocate(sizeof(struct SparkQueueT));
	if (queue == SPARK_NULL) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to allocate memory for queue!");
		if (!external_allocator) {
			SparkDestroyAllocator(allocator);
		}
		return SPARK_NULL;
	}

	queue->allocator = allocator;
	queue->capacity = capacity;
	queue->size = 0;
	queue->front = 0;
	queue->rear = 0;
	queue->destructor = destructor;
	queue->external_allocator = external_allocator;

	queue->elements = allocator->allocate(queue->capacity * sizeof(SparkHandle));
	if (queue->elements == SPARK_NULL) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to allocate memory for queue elements!");
		allocator->free(queue);
		if (!external_allocator) {
			SparkDestroyAllocator(allocator);
		}
		return SPARK_NULL;
	}
	return queue;
}

SPARKAPI SparkVoid SparkDestroyQueue(SparkQueue queue) {
	if (queue == SPARK_NULL) {
		return;
	}
	SparkAllocator allocator = queue->allocator;

	// Call destructor on each element if destructor is not NULL
	if (queue->destructor != NULL) {
		for (SparkSize i = 0; i < queue->size; i++) {
			SparkSize index = (queue->front + i) % queue->capacity;
			if (queue->elements[index] != SPARK_NULL) {
				queue->destructor(queue->elements[index]);
				queue->elements[index] = SPARK_NULL;
			}
		}
	}

	if (queue->elements != SPARK_NULL) {
		allocator->free(queue->elements);
		queue->elements = SPARK_NULL;
	}

	SparkBool external_allocator = queue->external_allocator;

	allocator->free(queue);
	queue = SPARK_NULL;

	if (!external_allocator) {
		SparkDestroyAllocator(allocator);
	}
}

SPARKAPI SparkResult SparkEnqueueQueue(SparkQueue queue, SparkHandle element) {
	if (queue == SPARK_NULL || element == SPARK_NULL) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	if (queue->size >= queue->capacity) {
		// Resize the queue
		SparkSize new_capacity = queue->capacity * 2;
		SparkHandle* new_elements = queue->allocator->allocate(new_capacity * sizeof(SparkHandle));
		if (new_elements == SPARK_NULL) {
			SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to allocate memory for queue resizing!");
			return SPARK_ERROR_OUT_OF_MEMORY;
		}

		// Copy elements to new array
		for (SparkSize i = 0; i < queue->size; i++) {
			SparkSize index = (queue->front + i) % queue->capacity;
			new_elements[i] = queue->elements[index];
		}

		queue->allocator->free(queue->elements);
		queue->elements = new_elements;
		queue->capacity = new_capacity;
		queue->front = 0;
		queue->rear = queue->size;
	}

	queue->elements[queue->rear] = element;
	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->size++;
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkDequeueQueue(SparkQueue queue) {
	if (queue == SPARK_NULL) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	if (queue->size == 0) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Queue is empty!");
		return SPARK_ERROR_INVALID_STATE;
	}

	// Call destructor on the element if destructor is not NULL
	if (queue->destructor != NULL && queue->elements[queue->front] != SPARK_NULL) {
		queue->destructor(queue->elements[queue->front]);
		queue->elements[queue->front] = SPARK_NULL;
	}

	queue->front = (queue->front + 1) % queue->capacity;
	queue->size--;
	return SPARK_SUCCESS;
}

SPARKAPI SparkHandle SparkGetFrontQueue(SparkQueue queue) {
	if (queue == SPARK_NULL || queue->size == 0) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Queue is empty or NULL!");
		return SPARK_NULL;
	}
	return queue->elements[queue->front];
}

SPARKAPI SparkHandle SparkGetBackQueue(SparkQueue queue) {
	if (queue == SPARK_NULL || queue->size == 0) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Queue is empty or NULL!");
		return SPARK_NULL;
	}
	SparkSize index = (queue->rear == 0) ? queue->capacity - 1 : queue->rear - 1;
	return queue->elements[index];
}

SPARKAPI SparkResult SparkClearQueue(SparkQueue queue) {
	if (queue == SPARK_NULL) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	// Call destructor on each element if destructor is not NULL
	if (queue->destructor != NULL) {
		for (SparkSize i = 0; i < queue->size; i++) {
			SparkSize index = (queue->front + i) % queue->capacity;
			if (queue->elements[index] != SPARK_NULL) {
				queue->destructor(queue->elements[index]);
				queue->elements[index] = SPARK_NULL;
			}
		}
	}
	queue->size = 0;
	queue->front = 0;
	queue->rear = 0;
	return SPARK_SUCCESS;
}

#pragma endregion

#pragma region STACK

SPARKAPI SparkStack SparkDefaultStack() {
	return SparkCreateStack(1, NULL, NULL);
}

SPARKAPI SparkStack SparkCreateStack(SparkSize capacity, SparkAllocator allocator, SparkFreeFunction destructor) {
	SparkBool external_allocator = SPARK_TRUE;

	if (!allocator) {
		allocator = SparkDefaultAllocator();
		external_allocator = SPARK_FALSE;
	}

	SparkStack stack = allocator->allocate(sizeof(struct SparkStackT));
	if (stack == SPARK_NULL) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to allocate memory for stack!");
		if (!external_allocator) {
			SparkDestroyAllocator(allocator);
		}
		return SPARK_NULL;
	}

	stack->allocator = allocator;
	stack->capacity = capacity;
	stack->size = 0;
	stack->destructor = destructor;
	stack->external_allocator = external_allocator;

	stack->elements = allocator->allocate(stack->capacity * sizeof(SparkHandle));
	if (stack->elements == SPARK_NULL) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to allocate memory for stack elements!");
		allocator->free(stack);
		if (!external_allocator) {
			SparkDestroyAllocator(allocator);
		}
		return SPARK_NULL;
	}
	return stack;
}

SPARKAPI SparkVoid SparkDestroyStack(SparkStack stack) {
	if (stack == SPARK_NULL) {
		return;
	}
	SparkAllocator allocator = stack->allocator;

	// Call destructor on each element if destructor is not NULL
	if (stack->destructor != NULL) {
		for (SparkSize i = 0; i < stack->size; i++) {
			if (stack->elements[i] != SPARK_NULL) {
				stack->destructor(stack->elements[i]);
				stack->elements[i] = SPARK_NULL;
			}
		}
	}

	if (stack->elements != SPARK_NULL) {
		allocator->free(stack->elements);
		stack->elements = SPARK_NULL;
	}

	SparkBool external_allocator = stack->external_allocator;

	allocator->free(stack);
	stack = SPARK_NULL;

	if (!external_allocator) {
		SparkDestroyAllocator(allocator);
	}
}

SPARKAPI SparkResult SparkPushStack(SparkStack stack, SparkHandle element) {
	if (stack == SPARK_NULL || element == SPARK_NULL) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	if (stack->size >= stack->capacity) {
		SparkSize new_capacity = stack->capacity * 2;
		SparkHandle* new_elements = stack->allocator->reallocate(stack->elements, new_capacity * sizeof(SparkHandle));
		if (new_elements == SPARK_NULL) {
			SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to reallocate stack!");
			return SPARK_ERROR_OUT_OF_MEMORY;
		}
		stack->elements = new_elements;
		stack->capacity = new_capacity;
	}
	stack->elements[stack->size++] = element;
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkPopStack(SparkStack stack) {
	if (stack == SPARK_NULL) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	if (stack->size == 0) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Stack is empty!");
		return SPARK_ERROR_INVALID_STATE;
	}
	stack->size--;

	// Call destructor on the element if destructor is not NULL
	if (stack->destructor != NULL && stack->elements[stack->size] != SPARK_NULL) {
		stack->destructor(stack->elements[stack->size]);
		stack->elements[stack->size] = SPARK_NULL;
	}

	return SPARK_SUCCESS;
}

SPARKAPI SparkHandle SparkGetTopStack(SparkStack stack) {
	if (stack == SPARK_NULL || stack->size == 0) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Stack is empty or NULL!");
		return SPARK_NULL;
	}
	return stack->elements[stack->size - 1];
}

SPARKAPI SparkResult SparkClearStack(SparkStack stack) {
	if (stack == SPARK_NULL) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	// Call destructor on each element if destructor is not NULL
	if (stack->destructor != NULL) {
		for (SparkSize i = 0; i < stack->size; i++) {
			if (stack->elements[i] != SPARK_NULL) {
				stack->destructor(stack->elements[i]);
				stack->elements[i] = SPARK_NULL;
			}
		}
	}
	stack->size = 0;
	return SPARK_SUCCESS;
}

#pragma endregion

#pragma region ECS

SPARKAPI SparkEcs SparkCreateEcs() {
	SparkEcs ecs = SparkAllocate(sizeof(struct SparkEcsT));
	ecs->components = SparkDefaultHashMap();
	ecs->entities = SparkDefaultVector();
	ecs->systems = SparkDefaultVector();
	return ecs;
}

SPARKAPI SparkVoid SparkDestroyEcs(SparkEcs ecs) {
	SparkStopEcs(ecs);
	SparkDestroyHashMap(ecs->components);
	SparkDestroyVector(ecs->entities);
	SparkDestroyVector(ecs->systems);
	SparkFree(ecs);
}

SPARKAPI SparkResult SparkAddSystem(SparkEcs ecs, SparkSystem system) {
	SparkPushBackVector(ecs->systems, system);
}

SPARKAPI SparkResult SparkRemoveSystem(SparkEcs ecs, SparkSystem system) {
	for (SparkSize i = 0; i < ecs->systems->size; i++) {
		if (SparkGetElementVector(ecs->systems, i) == system) {
			SparkRemoveVector(ecs->systems, i);
			return SPARK_SUCCESS;
		}
	}
}

SPARKAPI SparkResult SparkStartEcs(SparkEcs ecs) {
	for (SparkSize i = 0; i < ecs->systems->size; i++) {
		SparkSystem system = SparkGetElementVector(ecs->systems, i);
		if (system->start != SPARK_NULL) {
			SparkResult res = system->start(ecs);
			if (res != SPARK_SUCCESS) {
				return res;
			}
		}
	}
}

SPARKAPI SparkResult SparkUpdateEcs(SparkEcs ecs, SparkF32 delta) {
	for (SparkSize i = 0; i < ecs->systems->size; i++) {
		SparkSystem system = SparkGetElementVector(ecs->systems, i);
		if (system->update != SPARK_NULL) {
			SparkResult res = system->update(ecs, delta);
			if (res != SPARK_SUCCESS) {
				return res;
			}
		}
	}
}

SPARKAPI SparkResult SparkStopEcs(SparkEcs ecs) {
	for (SparkSize i = 0; i < ecs->systems->size; i++) {
		SparkSystem system = SparkGetElementVector(ecs->systems, i);
		if (system->stop != SPARK_NULL) {
			SparkResult res = system->stop(ecs);
			if (res != SPARK_SUCCESS) {
				return res;
			}
		}
	}
}

#pragma endregion

#pragma region VULKAN

#ifdef NDEBUG
const SparkBool ENABLE_VALIDATION_LAYERS = SPARK_FALSE;
#else
const SparkBool ENABLE_VALIDATION_LAYERS = SPARK_TRUE;
#endif

const SparkConstString VALIDATION_LAYERS[] = {
	"VK_LAYER_KHRONOS_validation"
};

const SparkConstString DEVICE_EXTENSIONS[] = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

const VkDynamicState DYNAMIC_STATES[] = {
	VK_DYNAMIC_STATE_VIEWPORT,
	VK_DYNAMIC_STATE_SCISSOR
};

struct VulkanExtensions {
	SparkU32 count;
	SparkConstString* names;
};

struct VulkanQueueFamilyIndices {
	SparkBool valid_graphics;
	SparkBool valid_present;
	SparkU32 graphics_family;
	SparkU32 present_family;
};

struct VulkanSwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	VkSurfaceFormatKHR* formats;
	VkPresentModeKHR* present_modes;
	SparkU32 formats_size;
	SparkU32 present_modes_size;
};

SPARKAPI SPARKSTATIC SparkBool __SparkIndicesComplete(struct VulkanQueueFamilyIndices* indices) {
	return indices->valid_graphics && indices->valid_present;
}

SPARKAPI SPARKSTATIC SparkBool __SparkCheckValidationLayerSupport() {
	SparkU32 layer_count;
	vkEnumerateInstanceLayerProperties(&layer_count, SPARK_NULL);

	VkLayerProperties* available_layers = SparkAllocate(layer_count * sizeof(VkLayerProperties));
	vkEnumerateInstanceLayerProperties(&layer_count, available_layers);

	for (SparkU32 i = 0; i < sizeof(VALIDATION_LAYERS) / sizeof(SparkConstString); i++) {
		SparkBool layer_found = SPARK_FALSE;
		for (SparkU32 j = 0; j < layer_count; j++) {
			if (strcmp(VALIDATION_LAYERS[i], available_layers[j].layerName) == 0) {
				layer_found = SPARK_TRUE;
				break;
			}
		}
		if (!layer_found) {
			SparkFree(available_layers);
			return SPARK_FALSE;
		}

	}

	SparkFree(available_layers);

	return SPARK_TRUE;
}

SPARKAPI SPARKSTATIC struct VulkanExtensions __SparkGetRequiredExtensions() {
	SparkU32 glfw_extension_count = 0;
	SparkConstString* glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

	SparkU32 extension_count = glfw_extension_count;
	if (ENABLE_VALIDATION_LAYERS) {
		extension_count++;
	}

	SparkConstString* extensions = SparkAllocate(extension_count * sizeof(SparkConstString));
	for (SparkU32 i = 0; i < glfw_extension_count; i++) {
		extensions[i] = glfw_extensions[i];
	}

	if (ENABLE_VALIDATION_LAYERS) {
		extensions[glfw_extension_count] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
	}

	return (struct VulkanExtensions) { extension_count, extensions };
}

SPARKAPI SPARKSTATIC struct VulkanQueueFamilyIndices __SparkFindQueueFamilies(SparkWindow window, VkPhysicalDevice device) {
	struct VulkanQueueFamilyIndices indices = { 0 };

	SparkU32 queue_family_count = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, SPARK_NULL);

	VkQueueFamilyProperties* queue_families = SparkAllocate(queue_family_count * sizeof(VkQueueFamilyProperties));
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families);

	for (SparkU32 i = 0; i < queue_family_count; i++) {
		if (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphics_family = i;
			indices.valid_graphics = SPARK_TRUE;
		}

		VkBool32 present_support = SPARK_FALSE;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, window->surface, &present_support);
		if (present_support) {
			indices.present_family = i;
			indices.valid_present = SPARK_TRUE;
		}

		if (__SparkIndicesComplete(&indices)) {
			break;
		}
	}

	SparkFree(queue_families);

	return indices;
}

SPARKAPI SPARKSTATIC VKAPI_ATTR SparkBool VKAPI_CALL __SparkDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity, VkDebugUtilsMessageTypeFlagsEXT message_type, const VkDebugUtilsMessengerCallbackDataEXT* callback_data, SparkHandle user_data) {
	if (message_severity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, callback_data->pMessage);
	}
	else {
		SparkLog(SPARK_LOG_LEVEL_INFO, callback_data->pMessage);
	}
	return VK_FALSE;
}

SPARKAPI SPARKSTATIC VkResult __SparkCreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* create_info, const VkAllocationCallbacks* allocator, VkDebugUtilsMessengerEXT* debug_messenger) {
	PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != SPARK_NULL) {
		return func(instance, create_info, allocator, debug_messenger);
	}
	else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

SPARKAPI SPARKSTATIC SparkVoid __SparkDestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debug_messenger, const VkAllocationCallbacks* allocator) {
	PFN_vkDestroyDebugUtilsMessengerEXT func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != SPARK_NULL) {
		func(instance, debug_messenger, allocator);
	}
}

SPARKAPI SPARKSTATIC VkDebugUtilsMessengerCreateInfoEXT __SparkPopulateDebugMessengerCreateInfo() {
	VkDebugUtilsMessengerCreateInfoEXT create_info = { 0 };
	create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	create_info.pfnUserCallback = __SparkDebugCallback;
	return create_info;
}

SPARKAPI SPARKSTATIC SparkResult __SparkSetupDebugMessenger(SparkWindow window) {
	if (!ENABLE_VALIDATION_LAYERS) {
		return SPARK_SUCCESS;
	}

	VkDebugUtilsMessengerCreateInfoEXT create_info = __SparkPopulateDebugMessengerCreateInfo();
	if (__SparkCreateDebugUtilsMessengerEXT(window->instance, &create_info, SPARK_NULL, &window->debug_messenger)) {
		return SPARK_ERROR_INVALID;
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkCreateVulkanInstance(VkInstance* instance, SparkConstString title) {
	if (ENABLE_VALIDATION_LAYERS && !__SparkCheckValidationLayerSupport()) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Validation layers requested, but not available!");
		return SPARK_ERROR_INVALID;
	}

	SparkU32 glfw_extension_count = 0;
	VkApplicationInfo app_info = { 0 };
	VkInstanceCreateInfo create_info = { 0 };
	struct VulkanExtensions extensions = __SparkGetRequiredExtensions();

	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pApplicationName = title;
	app_info.pEngineName = "Spark";
	app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.apiVersion = VK_API_VERSION_1_0;

	create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	create_info.pApplicationInfo = &app_info;
	create_info.enabledExtensionCount = extensions.count;
	create_info.ppEnabledExtensionNames = extensions.names;

	if (ENABLE_VALIDATION_LAYERS) {
		create_info.enabledLayerCount = sizeof(VALIDATION_LAYERS) / sizeof(SparkConstString);
		create_info.ppEnabledLayerNames = VALIDATION_LAYERS;

		VkDebugUtilsMessengerCreateInfoEXT debug_create_info = __SparkPopulateDebugMessengerCreateInfo();
		create_info.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debug_create_info;
	}
	else {
		create_info.enabledLayerCount = 0;
		create_info.pNext = SPARK_NULL;
	}

	VkResult result = vkCreateInstance(&create_info, SPARK_NULL, instance);
	if (result != VK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to create Vulkan instance!");
		return SPARK_ERROR_INVALID;
	}

	SparkFree(extensions.names);

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkBool __SparkCheckDeviceExtensionSupport(SparkWindow window, VkPhysicalDevice device) {
	SparkU32 extension_count;
	vkEnumerateDeviceExtensionProperties(device, SPARK_NULL, &extension_count, SPARK_NULL);

	VkExtensionProperties* available_extensions = SparkAllocate(sizeof(VkExtensionProperties) * extension_count);
	vkEnumerateDeviceExtensionProperties(device, SPARK_NULL, &extension_count, available_extensions);

	SparkBool all_extensions = SPARK_TRUE;

	for (SparkU32 i = 0; i < sizeof(DEVICE_EXTENSIONS) / sizeof(SparkConstString); i++) {
		SparkBool extension_found = SPARK_FALSE;
		for (SparkU32 j = 0; j < extension_count; j++) {
			if (strcmp(DEVICE_EXTENSIONS[i], available_extensions[j].extensionName) == 0) {
				extension_found = SPARK_TRUE;
				break;
			}
		}
		if (!extension_found) {
			all_extensions = SPARK_FALSE;
			break;
		}
	}

	SparkFree(available_extensions);

	return all_extensions;
}

SPARKAPI SPARKSTATIC struct VulkanSwapChainSupportDetails __SparkQuerySwapChainSupport(SparkWindow window, VkPhysicalDevice device) {
	struct VulkanSwapChainSupportDetails details = { 0 };

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, window->surface, &details.capabilities);

	SparkU32 format_count;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, window->surface, &format_count, SPARK_NULL);
	if (format_count != 0) {
		details.formats = SparkAllocate(format_count * sizeof(VkSurfaceFormatKHR));
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, window->surface, &format_count, details.formats);
	}

	SparkU32 present_mode_count;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, window->surface, &present_mode_count, SPARK_NULL);
	if (present_mode_count != 0) {
		details.present_modes = SparkAllocate(present_mode_count * sizeof(VkPresentModeKHR));
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, window->surface, &present_mode_count, details.present_modes);
	}

	details.formats_size = format_count;
	details.present_modes_size = present_mode_count;

	return details;
}

SPARKAPI SPARKSTATIC VkSurfaceFormatKHR __SparkChooseSwapSurfaceFormat(const VkSurfaceFormatKHR* available_formats, const SparkSize available_formats_size) {
	for (SparkSize i = 0; i < available_formats_size; i++) {
		if (available_formats[i].format == VK_FORMAT_B8G8R8A8_SRGB && available_formats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return available_formats[i];
		}
	}

	return available_formats[0];
}

SPARKAPI SPARKSTATIC VkPresentModeKHR __SparkChooseSwapPresentMode(const VkPresentModeKHR* available_present_modes, const SparkSize available_present_modes_size) {
	for (SparkSize i = 0; i < available_present_modes_size; i++) {
		if (available_present_modes[i] == VK_PRESENT_MODE_MAILBOX_KHR) {
			return available_present_modes[i];
		}
	}

	return VK_PRESENT_MODE_FIFO_KHR;
}

SPARKAPI SPARKSTATIC VkExtent2D __SparkChooseSwapExtent(const SparkWindow window, VkSurfaceCapabilitiesKHR* capabilities) {
	if (capabilities->currentExtent.width != UINT32_MAX) {
		return capabilities->currentExtent;
	}
	else {
		SparkI32 width, height;
		glfwGetFramebufferSize(window->window, &width, &height);

		VkExtent2D actual_extent = { width, height };
		actual_extent.width = SparkClamp((SparkScalar)actual_extent.width, (SparkScalar)capabilities->minImageExtent.width, (SparkScalar)capabilities->maxImageExtent.width);
		actual_extent.height = SparkClamp((SparkScalar)actual_extent.height, (SparkScalar)capabilities->minImageExtent.height, (SparkScalar)capabilities->maxImageExtent.height);
		return actual_extent;
	}
}

SPARKAPI SPARKSTATIC SparkBool __SparkIsDeviceSuitable(SparkWindow window, VkPhysicalDevice device) {
	struct VulkanQueueFamilyIndices indices = __SparkFindQueueFamilies(window, device);
	SparkBool extensions_supported = __SparkCheckDeviceExtensionSupport(window, device);

	SparkBool swap_chain_adequete = SPARK_FALSE;
	if (extensions_supported) {
		struct VulkanSwapChainSupportDetails swap_chain_support = __SparkQuerySwapChainSupport(window, device);
		swap_chain_adequete = swap_chain_support.formats && swap_chain_support.present_modes;

		SparkFree(swap_chain_support.formats);
		SparkFree(swap_chain_support.present_modes);
	}

	return __SparkIndicesComplete(&indices) && extensions_supported && swap_chain_adequete;
}

SPARKAPI SPARKSTATIC SparkI32 __SparkRateDeviceSuitability(VkPhysicalDevice device) {
	SparkI32 score = 0;

	VkPhysicalDeviceProperties device_properties;
	VkPhysicalDeviceFeatures device_features;

	vkGetPhysicalDeviceProperties(device, &device_properties);
	vkGetPhysicalDeviceFeatures(device, &device_features);

	if (device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
		score += 1000;
	}

	score += device_properties.limits.maxImageDimension2D;
	score += device_properties.limits.maxImageArrayLayers;
	score += device_properties.limits.maxFramebufferWidth;
	score += device_properties.limits.maxFramebufferHeight;
	score += device_properties.limits.maxFramebufferLayers;
	score += device_properties.limits.maxViewportDimensions[0];
	score += device_properties.limits.maxViewportDimensions[1];
	score += device_properties.limits.maxColorAttachments;

	if (!device_features.geometryShader) {
		return 0;
	}

	return score;
}

SPARKAPI SPARKSTATIC SparkResult __SparkPickPhysicalDevice(SparkWindow window) {
	VkPhysicalDevice physical_device = VK_NULL_HANDLE;
	SparkU32 device_count = 0;

	vkEnumeratePhysicalDevices(window->instance, &device_count, SPARK_NULL);

	if (!device_count) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to find GPUs with Vulkan support!");
		return SPARK_ERROR_INVALID;
	}

	VkPhysicalDevice* devices = SparkAllocate(device_count * sizeof(VkPhysicalDevice));
	vkEnumeratePhysicalDevices(window->instance, &device_count, devices);

	for (SparkU32 i = 0; i < device_count; i++) {
		if (__SparkIsDeviceSuitable(window, devices[i])) {
			physical_device = devices[i];
			break;
		}
	}

	if (physical_device == VK_NULL_HANDLE) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to find a suitable GPU!");
		SparkFree(devices);
		return SPARK_ERROR_INVALID;
	}

	VkPhysicalDevice* candidates = SparkAllocate(device_count * sizeof(VkPhysicalDevice));
	SparkU32* scores = SparkAllocate(device_count * sizeof(SparkU32));

	for (SparkU32 i = 0; i < device_count; i++) {
		candidates[i] = devices[i];
		scores[i] = __SparkRateDeviceSuitability(devices[i]);
	}

	SparkU32 max_score = 0;
	for (SparkU32 i = 0; i < device_count; i++) {
		if (scores[i] > max_score) {
			max_score = scores[i];
			physical_device = candidates[i];
		}
	}

	if (physical_device == VK_NULL_HANDLE || max_score == 0) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to find a suitable GPU!");
		SparkFree(devices);
		SparkFree(candidates);
		SparkFree(scores);
		return SPARK_ERROR_INVALID;
	}

	window->physical_device = physical_device;

	SparkFree(devices);
	SparkFree(candidates);
	SparkFree(scores);

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkCreateSurface(SparkWindow window) {
	if (glfwCreateWindowSurface(window->instance, window->window, SPARK_NULL, &window->surface) != VK_SUCCESS) {
		return SPARK_ERROR_INVALID;
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkCreateLogicalDevice(SparkWindow window) {
	struct VulkanQueueFamilyIndices indices = __SparkFindQueueFamilies(window, window->physical_device);

	const SparkU32 indices_size = 2;
	VkDeviceQueueCreateInfo* queue_create_infos = SparkAllocate(sizeof(VkDeviceQueueCreateInfo) * indices_size);
	SparkU32* unique_queue_families = SparkAllocate(sizeof(SparkU32) * indices_size);

	unique_queue_families[0] = indices.graphics_family;
	unique_queue_families[1] = indices.present_family;

	SparkF32 queue_priority = 1.0f;

	for (SparkU32 i = 0; i < indices_size; i++) {
		VkDeviceQueueCreateInfo queue_create_info = { 0 };
		queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queue_create_info.queueFamilyIndex = i;
		queue_create_info.queueCount = 1;
		queue_create_info.pQueuePriorities = &queue_priority;
		queue_create_infos[i] = queue_create_info;
	}


	VkDeviceQueueCreateInfo queue_create_info = { 0 };
	VkPhysicalDeviceFeatures device_features = { 0 };
	VkDeviceCreateInfo create_info = { 0 };

	queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queue_create_info.queueFamilyIndex = indices.graphics_family;
	queue_create_info.queueCount = 1;
	queue_create_info.pQueuePriorities = &queue_priority;

	create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	create_info.pQueueCreateInfos = queue_create_infos;
	create_info.queueCreateInfoCount = indices_size;
	create_info.pEnabledFeatures = &device_features;
	create_info.enabledExtensionCount = sizeof(DEVICE_EXTENSIONS) / sizeof(SparkConstString);
	create_info.ppEnabledExtensionNames = DEVICE_EXTENSIONS;

	if (ENABLE_VALIDATION_LAYERS) {
		create_info.enabledLayerCount = sizeof(VALIDATION_LAYERS) / sizeof(SparkConstString);
		create_info.ppEnabledLayerNames = VALIDATION_LAYERS;
	}
	else {
		create_info.enabledLayerCount = 0;
	}

	if (vkCreateDevice(window->physical_device, &create_info, SPARK_NULL, &window->device) != VK_SUCCESS) {
		SparkFree(queue_create_infos);
		SparkFree(unique_queue_families);
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to create logical device!");
		return SPARK_ERROR_INVALID;
	}

	vkGetDeviceQueue(window->device, indices.graphics_family, 0, &window->graphics_queue);
	vkGetDeviceQueue(window->device, indices.present_family, 0, &window->present_queue);

	SparkFree(queue_create_infos);
	SparkFree(unique_queue_families);

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkCreateSwapChain(SparkWindow window) {
	struct VulkanSwapChainSupportDetails swap_chain_support = __SparkQuerySwapChainSupport(window, window->physical_device);

	VkSurfaceFormatKHR surface_format = __SparkChooseSwapSurfaceFormat(swap_chain_support.formats, swap_chain_support.formats_size);
	VkPresentModeKHR present_mode = __SparkChooseSwapPresentMode(swap_chain_support.present_modes, swap_chain_support.present_modes_size);
	VkExtent2D extent = __SparkChooseSwapExtent(window, &swap_chain_support.capabilities);

	SparkU32 image_count = swap_chain_support.capabilities.minImageCount + 1;

	if (swap_chain_support.capabilities.maxImageCount > 0 && image_count > swap_chain_support.capabilities.maxImageCount) {
		image_count = swap_chain_support.capabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR create_info = { 0 };
	create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	create_info.surface = window->surface;
	create_info.minImageCount = image_count;
	create_info.imageFormat = surface_format.format;
	create_info.imageColorSpace = surface_format.colorSpace;
	create_info.imageExtent = extent;
	create_info.imageArrayLayers = 1;
	create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	struct VulkanQueueFamilyIndices indices = __SparkFindQueueFamilies(window, window->physical_device);
	SparkU32 queue_family_indices[] = { indices.graphics_family, indices.present_family };

	if (indices.graphics_family != indices.present_family) {
		create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		create_info.queueFamilyIndexCount = 2;
		create_info.pQueueFamilyIndices = queue_family_indices;
	}
	else {
		create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		create_info.queueFamilyIndexCount = 0;
		create_info.pQueueFamilyIndices = SPARK_NULL;
	}

	create_info.preTransform = swap_chain_support.capabilities.currentTransform;
	create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	create_info.presentMode = present_mode;
	create_info.clipped = VK_TRUE;
	create_info.oldSwapchain = VK_NULL_HANDLE;

	if (vkCreateSwapchainKHR(window->device, &create_info, SPARK_NULL, &window->swap_chain) != VK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to create swap chain!");
		return SPARK_ERROR_INVALID;
	}

	vkGetSwapchainImagesKHR(window->device, window->swap_chain, &image_count, SPARK_NULL);
	window->swap_chain_images = SparkAllocate(image_count * sizeof(VkImage));
	vkGetSwapchainImagesKHR(window->device, window->swap_chain, &image_count, window->swap_chain_images);

	window->swap_chain_images_size = image_count;
	window->swap_chain_image_format = surface_format.format;

	window->swap_chain_extent = SparkAllocate(sizeof(VkExtent2D));
	if (!window->swap_chain_extent) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to allocate memory for swap_chain_extent!");
		return SPARK_ERROR_NULL;
	}

	*(window->swap_chain_extent) = extent;

	SparkFree(swap_chain_support.formats);
	SparkFree(swap_chain_support.present_modes);

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkCreateImageViews(SparkWindow window) {
	window->swap_chain_image_views = SparkAllocate(window->swap_chain_images_size * sizeof(VkImageView));
	window->swap_chain_image_views_size = window->swap_chain_images_size;

	for (SparkSize i = 0; i < window->swap_chain_images_size; i++) {
		VkImageViewCreateInfo create_info = { 0 };
		create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		create_info.image = window->swap_chain_images[i];
		create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
		create_info.format = window->swap_chain_image_format;
		create_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		create_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		create_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		create_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		create_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		create_info.subresourceRange.baseMipLevel = 0;
		create_info.subresourceRange.levelCount = 1;
		create_info.subresourceRange.baseArrayLayer = 0;
		create_info.subresourceRange.layerCount = 1;

		if (vkCreateImageView(window->device, &create_info, SPARK_NULL, &window->swap_chain_image_views[i]) != VK_SUCCESS) {
			SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to create image views!");
			return SPARK_ERROR_INVALID;
		}
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC VkShaderModule __SparkCreateShaderModule(SparkWindow window, SparkConstBuffer code, SparkSize code_size) {
	VkShaderModuleCreateInfo create_info = { 0 };
	create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	create_info.codeSize = code_size;
	create_info.pCode = (SparkU32*)code;

	VkShaderModule shader_module;
	if (vkCreateShaderModule(window->device, &create_info, SPARK_NULL, &shader_module) != VK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to create shader module!");
		return VK_NULL_HANDLE;
	}
	return shader_module;
}

SPARKAPI SPARKSTATIC SparkResult __SparkCreateRenderPass(SparkWindow window) {
	VkAttachmentDescription color_attachment = { 0 };
	color_attachment.format = window->swap_chain_image_format;
	color_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
	color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	color_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference color_attachment_ref = { 0 };
	color_attachment_ref.attachment = 0;
	color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass = { 0 };
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &color_attachment_ref;

	VkSubpassDependency dependency = { 0 };
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.dstSubpass = 0;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.srcAccessMask = 0;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	VkRenderPassCreateInfo render_pass_info = { 0 };
	render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	render_pass_info.attachmentCount = 1;
	render_pass_info.pAttachments = &color_attachment;
	render_pass_info.subpassCount = 1;
	render_pass_info.pSubpasses = &subpass;
	render_pass_info.dependencyCount = 1;
	render_pass_info.pDependencies = &dependency;

	if (vkCreateRenderPass(window->device, &render_pass_info, SPARK_NULL, &window->render_pass) != VK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to create render pass!");
		return SPARK_ERROR_INVALID;
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkCreateGraphicsPipeline(SparkWindow window) {
	SparkBuffer vert_buf;
	SparkBuffer frag_buf;
	SparkSize vert_size;
	SparkSize frag_size;

	SparkCompileShaderToSpirv("src/shader.vert", SPARK_SHADER_STAGE_VERTEX, &vert_buf, &vert_size);
	SparkCompileShaderToSpirv("src/shader.frag", SPARK_SHADER_STAGE_FRAGMENT, &frag_buf, &frag_size);
	
	VkShaderModule vert_shader_module = __SparkCreateShaderModule(window, vert_buf, vert_size);
	VkShaderModule frag_shader_module = __SparkCreateShaderModule(window, frag_buf, frag_size);

	VkPipelineShaderStageCreateInfo vert_shader_stage_info = { 0 };
	vert_shader_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vert_shader_stage_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vert_shader_stage_info.module = vert_shader_module;
	vert_shader_stage_info.pName = "main";

	VkPipelineShaderStageCreateInfo frag_shader_stage_info = { 0 };
	frag_shader_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	frag_shader_stage_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	frag_shader_stage_info.module = frag_shader_module;
	frag_shader_stage_info.pName = "main";

	VkPipelineShaderStageCreateInfo shader_stages[] = { vert_shader_stage_info, frag_shader_stage_info };

	VkPipelineVertexInputStateCreateInfo vertex_input_info = { 0 };
	vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	
	VkPipelineInputAssemblyStateCreateInfo input_assembly = { 0 };
	input_assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	input_assembly.primitiveRestartEnable = VK_FALSE;

	VkViewport viewport = { 0 };
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (SparkF32)window->swap_chain_extent->width;
	viewport.height = (SparkF32)window->swap_chain_extent->height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	VkRect2D scissor = { 0 };
	scissor.offset = (VkOffset2D){ 0, 0 };
	scissor.extent = *window->swap_chain_extent;

	VkPipelineDynamicStateCreateInfo dynamic_state = { 0 };
	dynamic_state.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamic_state.dynamicStateCount = sizeof(DYNAMIC_STATES) / sizeof(DYNAMIC_STATES[0]);
	dynamic_state.pDynamicStates = DYNAMIC_STATES;

	VkPipelineViewportStateCreateInfo viewport_state = { 0 };
	viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewport_state.viewportCount = 1;
	viewport_state.scissorCount = 1;

	VkPipelineRasterizationStateCreateInfo rasterizer = { 0 };
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.lineWidth = 1.0f;
	rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterizer.depthBiasEnable = VK_FALSE;

	VkPipelineMultisampleStateCreateInfo multisampling = { 0 };
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	VkPipelineColorBlendAttachmentState color_blend_attachment = { 0 };
	color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	color_blend_attachment.blendEnable = VK_FALSE;
	color_blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
	color_blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
	color_blend_attachment.colorBlendOp = VK_BLEND_OP_ADD;
	color_blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	color_blend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	color_blend_attachment.alphaBlendOp = VK_BLEND_OP_ADD;

	VkPipelineColorBlendStateCreateInfo color_blending = { 0 };
	color_blending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	color_blending.logicOpEnable = VK_FALSE;
	color_blending.logicOp = VK_LOGIC_OP_COPY;
	color_blending.attachmentCount = 1;
	color_blending.pAttachments = &color_blend_attachment;

	VkPipelineLayoutCreateInfo pipeline_layout_info = { 0 };
	pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

	if (vkCreatePipelineLayout(window->device, &pipeline_layout_info, SPARK_NULL, &window->pipeline_layout) != VK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to create pipeline layout!");
		return SPARK_ERROR_INVALID;
	}

	VkGraphicsPipelineCreateInfo pipeline_info = { 0 };
	pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipeline_info.stageCount = sizeof(shader_stages) / sizeof(shader_stages[0]);
	pipeline_info.pStages = shader_stages;
	pipeline_info.pVertexInputState = &vertex_input_info;
	pipeline_info.pInputAssemblyState = &input_assembly;
	pipeline_info.pViewportState = &viewport_state;
	pipeline_info.pRasterizationState = &rasterizer;
	pipeline_info.pMultisampleState = &multisampling;
	pipeline_info.pColorBlendState = &color_blending;
	pipeline_info.pDynamicState = &dynamic_state;
	pipeline_info.layout = window->pipeline_layout;
	pipeline_info.renderPass = window->render_pass;
	pipeline_info.subpass = 0;

	if (vkCreateGraphicsPipelines(window->device, VK_NULL_HANDLE, 1, &pipeline_info, SPARK_NULL, &window->graphics_pipeline) != VK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to create graphics pipeline!");
		return SPARK_ERROR_INVALID;
	}

	SparkFree(vert_buf);
	SparkFree(frag_buf);

	vkDestroyShaderModule(window->device, vert_shader_module, SPARK_NULL);
	vkDestroyShaderModule(window->device, frag_shader_module, SPARK_NULL);

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkCreateFramebuffers(SparkWindow window) {
	window->swap_chain_framebuffers = SparkAllocate(window->swap_chain_image_views_size * sizeof(VkFramebuffer));

	for (SparkSize i = 0; i < window->swap_chain_image_views_size; i++) {
		VkImageView attachments[] = { window->swap_chain_image_views[i] };

		VkFramebufferCreateInfo framebuffer_info = { 0 };
		framebuffer_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebuffer_info.renderPass = window->render_pass;
		framebuffer_info.attachmentCount = 1;
		framebuffer_info.pAttachments = attachments;
		framebuffer_info.width = window->swap_chain_extent->width;
		framebuffer_info.height = window->swap_chain_extent->height;
		framebuffer_info.layers = 1;

		if (vkCreateFramebuffer(window->device, &framebuffer_info, SPARK_NULL, &window->swap_chain_framebuffers[i]) != VK_SUCCESS) {
			SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to create framebuffer!");
			return SPARK_ERROR_INVALID;
		}
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkCreateCommandPool(SparkWindow window) {
	struct VulkanQueueFamilyIndices queue_family_indices = __SparkFindQueueFamilies(window, window->physical_device);
	
	VkCommandPoolCreateInfo pool_info = { 0 };
	pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	pool_info.queueFamilyIndex = queue_family_indices.graphics_family;

	if (vkCreateCommandPool(window->device, &pool_info, SPARK_NULL, &window->command_pool) != VK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to create command pool!");
		return SPARK_ERROR_INVALID;
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkRecordCommandBuffer(SparkWindow window, VkCommandBuffer command_buffer, SparkU32 image_index) {
	VkCommandBufferBeginInfo begin_info = { 0 };
	begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	
	if (vkBeginCommandBuffer(command_buffer, &begin_info) != VK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to begin recording command buffer!");
		return SPARK_ERROR_INVALID;
	}

	VkRenderPassBeginInfo render_pass_info = { 0 };
	render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	render_pass_info.renderPass = window->render_pass;
	render_pass_info.framebuffer = window->swap_chain_framebuffers[image_index];
	render_pass_info.renderArea.offset = (VkOffset2D){ 0, 0 };
	render_pass_info.renderArea.extent = *window->swap_chain_extent;

	VkClearValue clear_color = { 0.0f, 0.0f, 0.0f, 1.0f };
	render_pass_info.clearValueCount = 1;
	render_pass_info.pClearValues = &clear_color;

	vkCmdBeginRenderPass(command_buffer, &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);

	vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, window->graphics_pipeline);

	VkViewport viewport = { 0 };
	viewport.width = (SparkScalar)window->swap_chain_extent->width;
	viewport.height = (SparkScalar)window->swap_chain_extent->height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	vkCmdSetViewport(window->command_buffer, 0, 1, &viewport);

	VkRect2D scissor = { 0 };
	scissor.offset = (VkOffset2D){ 0, 0 };
	scissor.extent = *window->swap_chain_extent;
	vkCmdSetScissor(window->command_buffer, 0, 1, &scissor);

	vkCmdDraw(command_buffer, 3, 1, 0, 0);

	vkCmdEndRenderPass(command_buffer);

	if (vkEndCommandBuffer(command_buffer) != VK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to record command buffer!");
		return SPARK_ERROR_INVALID;
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkCreateCommandBuffer(SparkWindow window) {
	VkCommandBufferAllocateInfo alloc_info = { 0 };
	alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	alloc_info.commandPool = window->command_pool;
	alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	alloc_info.commandBufferCount = 1;

	if (vkAllocateCommandBuffers(window->device, &alloc_info, &window->command_buffer) != VK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to allocate command buffers!");
		return SPARK_ERROR_INVALID;
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkCreateSyncObjects(SparkWindow window) {
	VkSemaphoreCreateInfo semaphore_info = { 0 };
	semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VkFenceCreateInfo fence_info = { 0 };
	fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	if (vkCreateSemaphore(window->device, &semaphore_info, SPARK_NULL, &window->image_available_semaphore) != VK_SUCCESS ||
		vkCreateSemaphore(window->device, &semaphore_info, SPARK_NULL, &window->render_finished_semaphore) != VK_SUCCESS ||
		vkCreateFence(window->device, &fence_info, SPARK_NULL, &window->in_flight_fence) != VK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to create synchronization objects!");
		return SPARK_ERROR_INVALID;
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkInitializeVulkan(SparkWindow window) {
	if (__SparkCreateVulkanInstance(&window->instance, window->window_data->title) != SPARK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to create Vulkan instance!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkSetupDebugMessenger(window) != SPARK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to setup debug messenger!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkCreateSurface(window) != SPARK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to setup window surface!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkPickPhysicalDevice(window) != SPARK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to pick physical device!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkCreateLogicalDevice(window) != SPARK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to create logical device!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkCreateSwapChain(window) != SPARK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to create swap chain!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkCreateImageViews(window) != SPARK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to create image views!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkCreateRenderPass(window) != SPARK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to create render pass!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkCreateGraphicsPipeline(window) != SPARK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to create graphics pipeline!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkCreateFramebuffers(window) != SPARK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to create framebuffers!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkCreateCommandPool(window) != SPARK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to create command pool!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkCreateCommandBuffer(window) != SPARK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to create command buffer!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkCreateSyncObjects(window) != SPARK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to create sync objects!");
		return SPARK_ERROR_INVALID;
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkVoid __SparkDestroyVulkan(SparkWindow window) {
	vkDestroySemaphore(window->device, window->image_available_semaphore, SPARK_NULL);
	vkDestroySemaphore(window->device, window->render_finished_semaphore, SPARK_NULL);
	vkDestroyFence(window->device, window->in_flight_fence, SPARK_NULL);
	vkDestroyCommandPool(window->device, window->command_pool, SPARK_NULL);

	// Technically this is bad because the swap chain image views size could be different,
	// TODO: Fix
	for (SparkSize i = 0; i < window->swap_chain_image_views_size; i++) {
		vkDestroyFramebuffer(window->device, window->swap_chain_framebuffers[i], SPARK_NULL);
	}

	vkDestroyPipeline(window->device, window->graphics_pipeline, SPARK_NULL);
	vkDestroyPipelineLayout(window->device, window->pipeline_layout, SPARK_NULL);
	vkDestroyRenderPass(window->device, window->render_pass, SPARK_NULL);

	for (SparkSize i = 0; i < window->swap_chain_image_views_size; i++) {
		vkDestroyImageView(window->device, window->swap_chain_image_views[i], SPARK_NULL);
	}

	vkDestroySwapchainKHR(window->device, window->swap_chain, SPARK_NULL);

	SparkFree(window->swap_chain_images);
	SparkFree(window->swap_chain_image_views);
	SparkFree(window->swap_chain_extent);

	vkDestroyDevice(window->device, SPARK_NULL);

	if (ENABLE_VALIDATION_LAYERS) {
		__SparkDestroyDebugUtilsMessengerEXT(window->instance, window->debug_messenger, SPARK_NULL);
	}

	vkDestroySurfaceKHR(window->instance, window->surface, SPARK_NULL);

	vkDestroyInstance(window->instance, SPARK_NULL);
}

SPARKAPI SPARKSTATIC SparkResult __SparkDrawFrame(SparkWindow window) {
	vkWaitForFences(window->device, 1, &window->in_flight_fence, VK_TRUE, UINT64_MAX);
	vkResetFences(window->device, 1, &window->in_flight_fence);

	SparkU32 image_index;
	vkAcquireNextImageKHR(window->device, window->swap_chain, UINT64_MAX, window->image_available_semaphore, VK_NULL_HANDLE, &image_index);

	vkResetCommandBuffer(window->command_buffer, 0);

	__SparkRecordCommandBuffer(window, window->command_buffer, image_index);

	VkSemaphore wait_semaphores[] = { window->image_available_semaphore };
	VkSemaphore signal_semaphores[] = { window->render_finished_semaphore };
	VkPipelineStageFlags wait_stages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

	VkSubmitInfo submit_info = { 0 };
	submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submit_info.waitSemaphoreCount = 1;
	submit_info.pWaitSemaphores = wait_semaphores;
	submit_info.pWaitDstStageMask = wait_stages;
	submit_info.commandBufferCount = 1;
	submit_info.pCommandBuffers = &window->command_buffer;
	submit_info.signalSemaphoreCount = 1;
	submit_info.pSignalSemaphores = signal_semaphores;

	if (vkQueueSubmit(window->graphics_queue, 1, &submit_info, window->in_flight_fence) != VK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, "Failed to submit draw command buffer!");
		return SPARK_ERROR_INVALID;
	}

	VkSwapchainKHR swap_chains[] = { window->swap_chain };

	VkPresentInfoKHR present_info = { 0 };
	present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	present_info.waitSemaphoreCount = 1;
	present_info.pWaitSemaphores = signal_semaphores;
	present_info.swapchainCount = 1;
	present_info.pSwapchains = swap_chains;
	present_info.pImageIndices = &image_index;

	vkQueuePresentKHR(window->present_queue, &present_info);

	return SPARK_SUCCESS;
}

#pragma endregion

#pragma region EVENT

SPARKAPI SparkEventHandler SparkDefaultEventHandler() {
	SparkEventHandler event_handler = SparkAllocate(sizeof(struct SparkEventHandlerT));
	event_handler->functions = SparkCreateVector(2, SPARK_NULL, SparkFree);
	return event_handler;
}

SPARKAPI SparkEventHandler SparkCreateEventHandler(SparkEventHandlerFunction functions[], SparkSize function_count) {
	SparkEventHandler event_handler = SparkAllocate(sizeof(struct SparkEventHandlerT));
	event_handler->functions = SparkCreateVector(2, SPARK_NULL, SparkFree);
	
	for (SparkSize i = 0; i < function_count; i++) {
		SparkPushBackVector(event_handler->functions, functions[i]);
	}

	return event_handler;
}

SPARKAPI SparkResult SparkDestroyEventHandler(SparkEventHandler event_handler) {
	SparkDestroyVector(event_handler->functions);
	SparkFree(event_handler);
}

SPARKAPI SparkResult SparkAddEventListener(SparkEventHandler event_handler, SparkEventType event_type, SparkEventFunction function) {
	SparkEventHandlerFunction event_handler_function = SparkAllocate(sizeof(struct SparkEventHandlerFunctionT));
	if (!event_handler_function) return SPARK_ERROR_INVALID_STATE;
	event_handler_function->type = event_type;
	event_handler_function->function = function;
	SparkPushBackVector(event_handler->functions, (SparkHandle)event_handler_function);
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkRemoveEventListener(SparkEventHandler event_handler, SparkEventType event_type, SparkEventFunction function) {
	SparkEventHandlerFunction event_handler_function = SPARK_NULL;
	for (SparkSize i = 0; i < event_handler->functions->size; i++) {
		event_handler_function = (SparkEventHandlerFunction)SparkGetElementVector(event_handler->functions, i);
		if (event_handler_function->type == event_type && event_handler_function->function == function) {
			SparkRemoveVector(event_handler->functions, i);
			SparkFree(event_handler_function);
			return SPARK_SUCCESS;
		}
	}
	return SPARK_ERROR_INVALID;
}

SPARKAPI SparkResult SparkDispatchEvent(SparkEventHandler event_handler, SparkEvent event) {
	for (SparkSize i = 0; i < event_handler->functions->size; i++) {
		SparkEventHandlerFunction function = SparkGetElementVector(event_handler->functions, i);
		if (function->type & event.type) {
			function->function(event);
		}
	}

	return SPARK_SUCCESS;
}

SPARKAPI SparkEvent SparkCreateEvent(SparkEventType event_type, SparkHandle event_data, SparkFreeFunction destructor) {
	return (SparkEvent){ event_type, event_data, SparkGetTime(), destructor };
}

SPARKAPI SparkEvent SparkCreateEventT(SparkEventType event_type, SparkHandle event_data, SparkFreeFunction destructor, SparkConstString time_stamp) {
	return (SparkEvent) { event_type, event_data, time_stamp, destructor };
}

SPARKAPI SparkResult SparkDestroyEvent(SparkEvent event) {
	if (event.destructor)
		event.destructor(event.data);
	return SPARK_SUCCESS;
}

#pragma endregion

#pragma region WINDOW

SPARKAPI SparkWindowData SparkCreateWindowData(SparkConstString title, SparkI32 width, SparkI32 height, SparkBool vsync) {
	SparkWindowData window_data = SparkAllocate(sizeof(struct SparkWindowDataT));
	window_data->title = SparkAllocate(strlen(title) + 1);
	strcpy(window_data->title, title);
	window_data->width = width;
	window_data->height = height;
	window_data->vsync = vsync;
	window_data->event_handler = SparkDefaultEventHandler();
	return window_data;
}

SPARKAPI SparkVoid SparkDestroyWindowData(SparkWindowData window_data) {
	SparkFree(window_data->title);
	SparkFree(window_data);
}

SPARKAPI SPARKSTATIC SparkVoid __GlfwErrorCallback(SparkI32 error, SparkConstString description) {
	SparkLog(SPARK_LOG_LEVEL_ERROR, "GLFW Error (%d): %s", error, description);
}

SPARKAPI SPARKSTATIC SparkVoid __GlfwSetKeyCallback(GLFWwindow* window, SparkI32 key, SparkI32 scancode, SparkI32 action, SparkI32 mods) {
	SparkWindowData data = (SparkWindowData)glfwGetWindowUserPointer(window);

	switch (action) {
	case GLFW_PRESS: {
		SparkEventDataKeyPressed event_data = SparkAllocate(sizeof(struct SparkEventDataKeyPressedT));
		event_data->key = key;
		event_data->repeat = SPARK_FALSE;
		SparkEvent event = SparkCreateEvent(SPARK_EVENT_KEY_PRESSED, (SparkHandle)event_data, SPARK_NULL);
		SparkDispatchEvent(data->event_handler, event);
		SparkFree(event_data);
		break;
	}
	case GLFW_RELEASE: {
		SparkEventDataKeyReleased event_data = SparkAllocate(sizeof(struct SparkEventDataKeyReleasedT));
		event_data->key = key;
		SparkEvent event = SparkCreateEvent(SPARK_EVENT_KEY_RELEASED, (SparkHandle)event_data, SPARK_NULL);
		SparkDispatchEvent(data->event_handler, event);
		SparkFree(event_data);
		break;
	}
	case GLFW_REPEAT: {
		SparkEventDataKeyPressed event_data = SparkAllocate(sizeof(struct SparkEventDataKeyPressedT));
		event_data->key = key;
		event_data->repeat = SPARK_TRUE;
		SparkEvent event = SparkCreateEvent(SPARK_EVENT_KEY_PRESSED, (SparkHandle)event_data, SPARK_NULL);
		SparkDispatchEvent(data->event_handler, event);
		SparkFree(event_data);
		break;
	}
	}
}

SPARKAPI SPARKSTATIC SparkVoid __GlfwSetCursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
	SparkWindowData data = (SparkWindowData)glfwGetWindowUserPointer(window);

	SparkEventDataMouseMoved event_data = SparkAllocate(sizeof(struct SparkEventDataMouseMovedT));
	event_data->xpos = xpos;
	event_data->ypos = ypos;
	SparkEvent event = SparkCreateEvent(SPARK_EVENT_MOUSE_MOVED, (SparkHandle)event_data, SPARK_NULL);
	SparkDispatchEvent(data->event_handler, event);
	SparkFree(event_data);
}

SPARKAPI SPARKSTATIC SparkVoid __GlfwSetMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	SparkWindowData data = (SparkWindowData)glfwGetWindowUserPointer(window);

	switch (action) {
	case GLFW_PRESS: {
		SparkEventDataMouseButtonPressed event_data = SparkAllocate(sizeof(struct SparkEventDataMouseButtonPressedT));
		event_data->button = button;
		SparkEvent event = SparkCreateEvent(SPARK_EVENT_MOUSE_BUTTON_PRESSED, (SparkHandle)event_data, SPARK_NULL);
		SparkDispatchEvent(data->event_handler, event);
		SparkFree(event_data);
		break;
	}
	case GLFW_RELEASE: {
		SparkEventDataMouseButtonReleased event_data = SparkAllocate(sizeof(struct SparkEventDataMouseButtonReleasedT));
		event_data->button = button;
		SparkEvent event = SparkCreateEvent(SPARK_EVENT_MOUSE_BUTTON_RELEASED, (SparkHandle)event_data, SPARK_NULL);
		SparkDispatchEvent(data->event_handler, event);
		SparkFree(event_data);
		break;
	}
	}
}

SPARKAPI SPARKSTATIC SparkVoid __GlfwSetScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	SparkWindowData data = (SparkWindowData)glfwGetWindowUserPointer(window);

	SparkEventDataMouseScrolled event_data = SparkAllocate(sizeof(struct SparkEventDataMouseScrolledT));
	event_data->x = xoffset;
	event_data->y = yoffset;
	SparkEvent event = SparkCreateEvent(SPARK_EVENT_MOUSE_SCROLLED, (SparkHandle)event_data, SPARK_NULL);
	SparkDispatchEvent(data->event_handler, event);
	SparkFree(event_data);
}

SPARKAPI SPARKSTATIC SparkVoid __GlfwSetFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	SparkWindowData data = (SparkWindowData)glfwGetWindowUserPointer(window);

	SparkEventDataWindowResized event_data = SparkAllocate(sizeof(struct SparkEventDataWindowResizedT));
	event_data->width = width;
	event_data->height = height;
	SparkEvent event = SparkCreateEvent(SPARK_EVENT_WINDOW_RESIZE, (SparkHandle)event_data, SPARK_NULL);
	SparkDispatchEvent(data->event_handler, event);
	SparkFree(event_data);
}

SPARKAPI SparkWindow SparkCreateWindow(SparkWindowData window_data) {
	SparkWindow window = SparkAllocate(sizeof(struct SparkWindowT));
	memset(window, 0, sizeof(struct SparkWindowT));
	window->window_data = window_data;
	window->renderer = SparkCreateRenderer();

	if (!glfwInit()) {
		SparkLog(SPARK_LOG_LEVEL_FATAL, "Failed to initialize GLFW!");
		SparkFree(window);
		return NULL;
	}

	glfwSetErrorCallback(__GlfwErrorCallback);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window->window = glfwCreateWindow(window_data->width, window_data->height, window_data->title, SPARK_NULL, SPARK_NULL);

	if (!window->window) {
		SparkLog(SPARK_LOG_LEVEL_FATAL, "Failed to create GLFW window!");
		SparkDestroyRenderer(window->renderer);
		SparkDestroyWindowData(window->window_data);
		SparkFree(window);
		glfwTerminate();
		return NULL;
	}

	glfwSetWindowUserPointer(window->window, window->window_data);

	glfwSetKeyCallback(window->window, __GlfwSetKeyCallback);
	glfwSetCursorPosCallback(window->window, __GlfwSetCursorPosCallback);
	glfwSetMouseButtonCallback(window->window, __GlfwSetMouseButtonCallback);
	glfwSetScrollCallback(window->window, __GlfwSetScrollCallback);
	glfwSetFramebufferSizeCallback(window->window, __GlfwSetFramebufferSizeCallback);

	if (__SparkInitializeVulkan(window) != SPARK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_FATAL, "Failed to initialize Vulkan!");
		glfwDestroyWindow(window->window);
		SparkDestroyRenderer(window->renderer);
		SparkDestroyWindowData(window->window_data);
		SparkFree(window);
		glfwTerminate();
		return NULL;
	}

	return window;
}


SPARKAPI SparkVoid SparkDestroyWindow(SparkWindow window) {
	glfwDestroyWindow(window->window);
	glfwTerminate();
	__SparkDestroyVulkan(window);
	SparkDestroyRenderer(window->renderer);
	SparkDestroyWindowData(window->window_data);
	SparkFree(window);
}

SPARKAPI SPARKSTATIC SparkVoid __SparkUpdateWindow(SparkWindow window) {
	glfwPollEvents();
	__SparkDrawFrame(window);
}

#pragma endregion

#pragma region RENDER

SPARKAPI SparkRenderer SparkCreateRenderer() {
	return SparkAllocate(sizeof(struct SparkRendererT));
}

SPARKAPI SparkVoid SparkDestroyRenderer(SparkRenderer renderer) {
	SparkFree(renderer);
}

#pragma endregion

#pragma region APPLICATION

SPARKAPI SparkApplication SparkCreateApplication(SparkWindow window) {
	SparkApplication app = SparkAllocate(sizeof(struct SparkApplicationT));
	app->window = window;
	app->ecs = SparkCreateEcs();
	app->event_handler = window->window_data->event_handler;
	return app;
}

SPARKAPI SparkVoid SparkDestroyApplication(SparkApplication app) {
	SparkDestroyWindow(app->window);
	SparkDestroyEcs(app->ecs);
	SparkDestroyEventHandler(app->event_handler);
	SparkFree(app);
}

SPARKAPI SPARKSTATIC SparkBool __SparkApplicationKeepOpen(SparkApplication app) {
	return !glfwWindowShouldClose(app->window) || SPARK_TRUE;
}

SPARKAPI SparkVoid SparkUpdateApplication(SparkApplication app) {
	while (__SparkApplicationKeepOpen(app)) {
		__SparkUpdateWindow(app->window);
	}
}

SPARKAPI SparkResult SparkAddEventFunctionApplication(SparkApplication app, SparkEventType event_type, SparkEventFunction function) {
	return SparkAddEventListener(app->event_handler, event_type, function);
}

SPARKAPI SparkResult SparkDispatchEventApplication(SparkApplication app, SparkEvent event) {
	return SparkDispatchEvent(app->event_handler, event);
}

#pragma endregion