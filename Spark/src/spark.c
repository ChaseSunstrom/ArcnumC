
#include "spark.h"
#include <string.h>
#include <stdlib.h>

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

SPARKAPI SparkVoid SparkLog(SparkLogLevel log_level, SparkConstString message) {
	switch (log_level) {
	case SPARK_LOG_LEVEL_DEBUG: printf("[DEBUG] %s\n", message); break;
	case SPARK_LOG_LEVEL_INFO: printf("[INFO] %s\n", message); break;
	case SPARK_LOG_LEVEL_WARN: printf("[WARN] %s\n", message); break;
	case SPARK_LOG_LEVEL_ERROR: printf("[ERROR] %s\n", message); break;
	case SPARK_LOG_LEVEL_FATAL: printf("[FATAL] %s\n", message); break;
	default: break;
	}
}

SPARKAPI SparkResult SparkCheckSuccess(SparkResult result) {
	if (result != SPARK_SUCCESS) {
		SparkLog(SPARK_LOG_LEVEL_ERROR, SparkResultToString(result));
	}
	return result;
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

#pragma region WINDOW

SPARKAPI SparkWindowData SparkCreateWindowData(SparkConstString title, SparkI32 width, SparkI32 height, SparkBool vsync) {
	SparkWindowData window_data = malloc(sizeof(struct SparkWindowDataT));
	window_data->title = strdup(title);
	window_data->width = width;
	window_data->height = height;
	window_data->vsync = vsync;
	return window_data;
}

SPARKAPI SparkVoid SparkDestroyWindowData(SparkWindowData window_data) {
	free(window_data->title);
	free(window_data);
}

SPARKAPI SparkWindow SparkCreateWindow(SparkWindowData window_data) {
	SparkWindow window = malloc(sizeof(struct SparkWindowT));
	window->window_data = window_data;
	return window;
}

SPARKAPI SparkVoid SparkDestroyWindow(SparkWindow window) {
	SparkDestroyWindowData(window->window_data);
	free(window);
}

#pragma endregion

#pragma region RENDER



#pragma endregion

#pragma region APPLICATION


#pragma endregion