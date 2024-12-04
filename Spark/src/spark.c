#define SPARK_IMPLEMENTATION
#include "spark.h"
#include "spark_shader.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <OPENAL/al.h>
#include <OPENAL/alc.h>

#define DR_FLAC_IMPLEMENTATION
#define DR_MP3_IMPLEMENTATION
#define DR_WAV_IMPLEMENTATION
#include <DR/dr_flac.h>
#include <DR/dr_mp3.h>
#include <DR/dr_wav.h>

#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>

#ifdef _MSC_VER
#include <windows.h>
#include <process.h>
#define SparkAtomicIncrement(data) InterlockedIncrement((LONG volatile *)(data))
#define SparkAtomicDecrement(data) InterlockedDecrement((LONG volatile *)(data))
#elif defined(__clang__) || defined(__GNUC__)
#define SparkAtomicIncrement(data) __sync_add_and_fetch((data), 1)
#define SparkAtomicDecrement(data) __sync_sub_and_fetch((data), 1)
#endif

#pragma region ENUM

SPARKAPI SparkConstString SparkTypeToString(SparkType type) {
	switch (type) {
		/* False, None, Null*/
	case SPARK_NONE:
		return "SPARK_NONE";
		/* True, Success, Valid */
	case SPARK_SUCCESS:
		return "SPARK_SUCCESS";
		/* Invalid, */
	case SPARK_INVALID:
		return "SPARK_INVALID";
	case SPARK_ERROR:
		return "SPARK_ERROR";
	case SPARK_UNKNOWN:
		return "SPARK_UNKNOWN";
	case SPARK_PENDING:
		return "SPARK_PENDING";
	case SPARK_IN_PROGRESS:
		return "SPARK_IN_PROGRESS";
	case SPARK_COMPLETE:
		return "SPARK_COMPLETE";
	case SPARK_TIMEOUT:
		return "SPARK_TIMEOUT";
	case SPARK_CANCELLED:
		return "SPARK_CANCELLED";
	case SPARK_NOT_IMPLEMENTED:
		return "SPARK_NOT_IMPLEMENTED";
	case SPARK_ACCESS_DENIED:
		return "SPARK_ACCESS_DENIED";
	case SPARK_NOT_FOUND:
		return "SPARK_NOT_FOUND";
	case SPARK_BUSY:
		return "SPARK_BUSY";
	case SPARK_OVERLOADED:
		return "SPARK_OVERLOADED";
	case SPARK_DISCONNECTED:
		return "SPARK_DISCONNECTED";
	case SPARK_CONNECTED:
		return "SPARK_CONNECTED";
	case SPARK_RETRY:
		return "SPARK_RETRY";
	case SPARK_DEPRECATED:
		return "SPARK_DEPRECATED";
	case SPARK_UNSUPPORTED:
		return "SPARK_UNSUPPORTED";
	case SPARK_INITIALIZED:
		return "SPARK_INITIALIZED";
	case SPARK_UNINITIALIZED:
		return "SPARK_UNINITIALIZED";
	case SPARK_ENABLED:
		return "SPARK_ENABLED";
	case SPARK_DISABLED:
		return "SPARK_DISABLED";
	case SPARK_READ_ONLY:
		return "SPARK_READ_ONLY";
	case SPARK_WRITE_ONLY:
		return "SPARK_WRITE_ONLY";
	case SPARK_READ_WRITE:
		return "SPARK_READ_WRITE";
	case SPARK_SUCCESS_PARTIAL:
		return "SPARK_SUCCESS_PARTIAL";
	case SPARK_INVALID_ARGUMENT:
		return "SPARK_INVALID_ARGUMENT";
	case SPARK_OUT_OF_MEMORY:
		return "SPARK_OUT_OF_MEMORY";
	case SPARK_OVERFLOW:
		return "SPARK_OVERFLOW";
	case SPARK_UNDERFLOW:
		return "SPARK_UNDERFLOW";
	case SPARK_END_OF_FILE:
		return "SPARK_END_OF_FILE";
	case SPARK_PERMISSION_DENIED:
		return "SPARK_PERMISSION_DENIED";
	case SPARK_BAD_REQUEST:
		return "SPARK_BAD_REQUEST";
	case SPARK_CONFLICT:
		return "SPARK_CONFLICT";
	case SPARK_PRECONDITION_FAILED:
		return "SPARK_PRECONDITION_FAILED";
	default:
		return "UNKNOWN_SPARK_TYPE";
	}
}

SPARKAPI SparkType SparkStringToType(SparkConstString string) {
	if (strcmp(string, "SPARK_FALSE") == 0)
		return SPARK_FALSE;
	else if (strcmp(string, "SPARK_TRUE") == 0)
		return SPARK_TRUE;
	else if (strcmp(string, "SPARK_SUCCESS") == 0)
		return SPARK_SUCCESS;
	else if (strcmp(string, "SPARK_FAILURE") == 0)
		return SPARK_FAILURE;
	else if (strcmp(string, "SPARK_ERROR") == 0)
		return SPARK_ERROR;
	else if (strcmp(string, "SPARK_VALID") == 0)
		return SPARK_VALID;
	else if (strcmp(string, "SPARK_INVALID") == 0)
		return SPARK_INVALID;
	else if (strcmp(string, "SPARK_NULL") == 0)
		return SPARK_NULL;
	else if (strcmp(string, "SPARK_NONE") == 0)
		return SPARK_NONE;
	else if (strcmp(string, "SPARK_UNKNOWN") == 0)
		return SPARK_UNKNOWN;
	else if (strcmp(string, "SPARK_PENDING") == 0)
		return SPARK_PENDING;
	else if (strcmp(string, "SPARK_IN_PROGRESS") == 0)
		return SPARK_IN_PROGRESS;
	else if (strcmp(string, "SPARK_COMPLETE") == 0)
		return SPARK_COMPLETE;
	else if (strcmp(string, "SPARK_TIMEOUT") == 0)
		return SPARK_TIMEOUT;
	else if (strcmp(string, "SPARK_CANCELLED") == 0)
		return SPARK_CANCELLED;
	else if (strcmp(string, "SPARK_NOT_IMPLEMENTED") == 0)
		return SPARK_NOT_IMPLEMENTED;
	else if (strcmp(string, "SPARK_ACCESS_DENIED") == 0)
		return SPARK_ACCESS_DENIED;
	else if (strcmp(string, "SPARK_NOT_FOUND") == 0)
		return SPARK_NOT_FOUND;
	else if (strcmp(string, "SPARK_BUSY") == 0)
		return SPARK_BUSY;
	else if (strcmp(string, "SPARK_OVERLOADED") == 0)
		return SPARK_OVERLOADED;
	else if (strcmp(string, "SPARK_DISCONNECTED") == 0)
		return SPARK_DISCONNECTED;
	else if (strcmp(string, "SPARK_CONNECTED") == 0)
		return SPARK_CONNECTED;
	else if (strcmp(string, "SPARK_RETRY") == 0)
		return SPARK_RETRY;
	else if (strcmp(string, "SPARK_DEPRECATED") == 0)
		return SPARK_DEPRECATED;
	else if (strcmp(string, "SPARK_UNSUPPORTED") == 0)
		return SPARK_UNSUPPORTED;
	else if (strcmp(string, "SPARK_INITIALIZED") == 0)
		return SPARK_INITIALIZED;
	else if (strcmp(string, "SPARK_UNINITIALIZED") == 0)
		return SPARK_UNINITIALIZED;
	else if (strcmp(string, "SPARK_ENABLED") == 0)
		return SPARK_ENABLED;
	else if (strcmp(string, "SPARK_DISABLED") == 0)
		return SPARK_DISABLED;
	else if (strcmp(string, "SPARK_READ_ONLY") == 0)
		return SPARK_READ_ONLY;
	else if (strcmp(string, "SPARK_WRITE_ONLY") == 0)
		return SPARK_WRITE_ONLY;
	else if (strcmp(string, "SPARK_READ_WRITE") == 0)
		return SPARK_READ_WRITE;
	else if (strcmp(string, "SPARK_SUCCESS_PARTIAL") == 0)
		return SPARK_SUCCESS_PARTIAL;
	else if (strcmp(string, "SPARK_INVALID_ARGUMENT") == 0)
		return SPARK_INVALID_ARGUMENT;
	else if (strcmp(string, "SPARK_OUT_OF_MEMORY") == 0)
		return SPARK_OUT_OF_MEMORY;
	else if (strcmp(string, "SPARK_OVERFLOW") == 0)
		return SPARK_OVERFLOW;
	else if (strcmp(string, "SPARK_UNDERFLOW") == 0)
		return SPARK_UNDERFLOW;
	else if (strcmp(string, "SPARK_END_OF_FILE") == 0)
		return SPARK_END_OF_FILE;
	else if (strcmp(string, "SPARK_PERMISSION_DENIED") == 0)
		return SPARK_PERMISSION_DENIED;
	else if (strcmp(string, "SPARK_BAD_REQUEST") == 0)
		return SPARK_BAD_REQUEST;
	else if (strcmp(string, "SPARK_CONFLICT") == 0)
		return SPARK_CONFLICT;
	else if (strcmp(string, "SPARK_PRECONDITION_FAILED") == 0)
		return SPARK_PRECONDITION_FAILED;
	else
		return SPARK_UNKNOWN;
}

SPARKAPI SparkConstString SparkErrorToString(SparkError error) {
	switch (error) {
	case SPARK_ERROR_NONE:
		return "SPARK_ERROR_NONE";
	case SPARK_ERROR_UNKNOWN:
		return "SPARK_ERROR_UNKNOWN";
	case SPARK_ERROR_INVALID:
		return "SPARK_ERROR_INVALID";
	case SPARK_ERROR_NULL:
		return "SPARK_ERROR_NULL";
	case SPARK_ERROR_NOT_FOUND:
		return "SPARK_ERROR_NOT_FOUND";
	case SPARK_ERROR_NOT_IMPLEMENTED:
		return "SPARK_ERROR_NOT_IMPLEMENTED";
	case SPARK_ERROR_ACCESS_DENIED:
		return "SPARK_ERROR_ACCESS_DENIED";
	case SPARK_ERROR_BUSY:
		return "SPARK_ERROR_BUSY";
	case SPARK_ERROR_OVERLOADED:
		return "SPARK_ERROR_OVERLOADED";
	case SPARK_ERROR_DISCONNECTED:
		return "SPARK_ERROR_DISCONNECTED";
	case SPARK_ERROR_TIMEOUT:
		return "SPARK_ERROR_TIMEOUT";
	case SPARK_ERROR_CANCELLED:
		return "SPARK_ERROR_CANCELLED";
	case SPARK_ERROR_RETRY:
		return "SPARK_ERROR_RETRY";
	case SPARK_ERROR_UNSUPPORTED:
		return "SPARK_ERROR_UNSUPPORTED";
	case SPARK_ERROR_DEPRECATED:
		return "SPARK_ERROR_DEPRECATED";
	case SPARK_ERROR_UNINITIALIZED:
		return "SPARK_ERROR_UNINITIALIZED";
	case SPARK_ERROR_DISABLED:
		return "SPARK_ERROR_DISABLED";
	case SPARK_ERROR_READ_ONLY:
		return "SPARK_ERROR_READ_ONLY";
	case SPARK_ERROR_WRITE_ONLY:
		return "SPARK_ERROR_WRITE_ONLY";
	case SPARK_ERROR_OUT_OF_MEMORY:
		return "SPARK_ERROR_OUT_OF_MEMORY";
	case SPARK_ERROR_OVERFLOW:
		return "SPARK_ERROR_OVERFLOW";
	case SPARK_ERROR_UNDERFLOW:
		return "SPARK_ERROR_UNDERFLOW";
	case SPARK_ERROR_END_OF_FILE:
		return "SPARK_ERROR_END_OF_FILE";
	case SPARK_ERROR_PERMISSION_DENIED:
		return "SPARK_ERROR_PERMISSION_DENIED";
	case SPARK_ERROR_BAD_REQUEST:
		return "SPARK_ERROR_BAD_REQUEST";
	case SPARK_ERROR_CONFLICT:
		return "SPARK_ERROR_CONFLICT";
	case SPARK_ERROR_PRECONDITION_FAILED:
		return "SPARK_ERROR_PRECONDITION_FAILED";
	case SPARK_ERROR_INVALID_ARGUMENT:
		return "SPARK_ERROR_INVALID_ARGUMENT";
	case SPARK_ERROR_INVALID_STATE:
		return "SPARK_ERROR_INVALID_STATE";
	case SPARK_ERROR_INVALID_FUNCTION_CALL:
		return "SPARK_ERROR_INVALID_FUNCTION_CALL";
	default:
		return "UNKNOWN_SPARK_ERROR";
	}
}

SPARKAPI SparkError SparkStringToError(SparkConstString string) {
	if (strcmp(string, "SPARK_ERROR_NONE") == 0)
		return SPARK_ERROR_NONE;
	else if (strcmp(string, "SPARK_ERROR_UNKNOWN") == 0)
		return SPARK_ERROR_UNKNOWN;
	else if (strcmp(string, "SPARK_ERROR_INVALID") == 0)
		return SPARK_ERROR_INVALID;
	else if (strcmp(string, "SPARK_ERROR_NULL") == 0)
		return SPARK_ERROR_NULL;
	else if (strcmp(string, "SPARK_ERROR_NOT_FOUND") == 0)
		return SPARK_ERROR_NOT_FOUND;
	else if (strcmp(string, "SPARK_ERROR_NOT_IMPLEMENTED") == 0)
		return SPARK_ERROR_NOT_IMPLEMENTED;
	else if (strcmp(string, "SPARK_ERROR_ACCESS_DENIED") == 0)
		return SPARK_ERROR_ACCESS_DENIED;
	else if (strcmp(string, "SPARK_ERROR_BUSY") == 0)
		return SPARK_ERROR_BUSY;
	else if (strcmp(string, "SPARK_ERROR_OVERLOADED") == 0)
		return SPARK_ERROR_OVERLOADED;
	else if (strcmp(string, "SPARK_ERROR_DISCONNECTED") == 0)
		return SPARK_ERROR_DISCONNECTED;
	else if (strcmp(string, "SPARK_ERROR_TIMEOUT") == 0)
		return SPARK_ERROR_TIMEOUT;
	else if (strcmp(string, "SPARK_ERROR_CANCELLED") == 0)
		return SPARK_ERROR_CANCELLED;
	else if (strcmp(string, "SPARK_ERROR_RETRY") == 0)
		return SPARK_ERROR_RETRY;
	else if (strcmp(string, "SPARK_ERROR_UNSUPPORTED") == 0)
		return SPARK_ERROR_UNSUPPORTED;
	else if (strcmp(string, "SPARK_ERROR_DEPRECATED") == 0)
		return SPARK_ERROR_DEPRECATED;
	else if (strcmp(string, "SPARK_ERROR_UNINITIALIZED") == 0)
		return SPARK_ERROR_UNINITIALIZED;
	else if (strcmp(string, "SPARK_ERROR_DISABLED") == 0)
		return SPARK_ERROR_DISABLED;
	else if (strcmp(string, "SPARK_ERROR_READ_ONLY") == 0)
		return SPARK_ERROR_READ_ONLY;
	else if (strcmp(string, "SPARK_ERROR_WRITE_ONLY") == 0)
		return SPARK_ERROR_WRITE_ONLY;
	else if (strcmp(string, "SPARK_ERROR_OUT_OF_MEMORY") == 0)
		return SPARK_ERROR_OUT_OF_MEMORY;
	else if (strcmp(string, "SPARK_ERROR_OVERFLOW") == 0)
		return SPARK_ERROR_OVERFLOW;
	else if (strcmp(string, "SPARK_ERROR_UNDERFLOW") == 0)
		return SPARK_ERROR_UNDERFLOW;
	else if (strcmp(string, "SPARK_ERROR_END_OF_FILE") == 0)
		return SPARK_ERROR_END_OF_FILE;
	else if (strcmp(string, "SPARK_ERROR_PERMISSION_DENIED") == 0)
		return SPARK_ERROR_PERMISSION_DENIED;
	else if (strcmp(string, "SPARK_ERROR_BAD_REQUEST") == 0)
		return SPARK_ERROR_BAD_REQUEST;
	else if (strcmp(string, "SPARK_ERROR_CONFLICT") == 0)
		return SPARK_ERROR_CONFLICT;
	else if (strcmp(string, "SPARK_ERROR_PRECONDITION_FAILED") == 0)
		return SPARK_ERROR_PRECONDITION_FAILED;
	else if (strcmp(string, "SPARK_ERROR_INVALID_ARGUMENT") == 0)
		return SPARK_ERROR_INVALID_ARGUMENT;
	else if (strcmp(string, "SPARK_ERROR_INVALID_STATE") == 0)
		return SPARK_ERROR_INVALID_STATE;
	else if (strcmp(string, "SPARK_ERROR_INVALID_FUNCTION_CALL") == 0)
		return SPARK_ERROR_INVALID_FUNCTION_CALL;
	else
		return SPARK_ERROR_UNKNOWN;
}

SPARKAPI SparkConstString SparkResultToString(SparkResult result) {
	switch (result) {
	case SPARK_SUCCESS:
		return "SPARK_SUCCESS";
	case SPARK_FAILURE:
		return "SPARK_FAILURE";
	default:
		"SPARK_INVALID";
	}
}

SPARKAPI SparkResult SparkStringToResult(SparkConstString string) {
	if (strcmp(string, "SPARK_SUCCESS") == 0)
		return SPARK_SUCCESS;
	else if (strcmp(string, "SPARK_FAILURE") == 0)
		return SPARK_FAILURE;
	else
		return SPARK_INVALID;
}

SPARKAPI SparkConstString SparkAccessToString(SparkAccess access) {
	switch (access) {
	case SPARK_ACCESS_NONE:
		return "SPARK_ACCESS_NONE";
	case SPARK_ACCESS_READ:
		return "SPARK_ACCESS_READ";
	case SPARK_ACCESS_WRITE:
		return "SPARK_ACCESS_WRITE";
	case SPARK_ACCESS_READ_WRITE:
		return "SPARK_ACCESS_READ_WRITE";
	default:
		return "UNKNOWN_SPARK_ACCESS";
	}
}

SPARKAPI SparkAccess SparkStringToAccess(SparkConstString string) {
	if (strcmp(string, "SPARK_ACCESS_NONE") == 0)
		return SPARK_ACCESS_NONE;
	else if (strcmp(string, "SPARK_ACCESS_READ") == 0)
		return SPARK_ACCESS_READ;
	else if (strcmp(string, "SPARK_ACCESS_WRITE") == 0)
		return SPARK_ACCESS_WRITE;
	else if (strcmp(string, "SPARK_ACCESS_READ_WRITE") == 0)
		return SPARK_ACCESS_READ_WRITE;
	else
		return SPARK_ACCESS_NONE;
}

SPARKAPI SparkConstString SparkMouseButtonToString(SparkMouseButton button) {
	switch (button) {
		/* Left */
	case SPARK_MOUSE_BUTTON_1:
		return "SPARK_MOUSE_BUTTON_1";
		/* Right */
	case SPARK_MOUSE_BUTTON_2:
		return "SPARK_MOUSE_BUTTON_2";
		/* Middle */
	case SPARK_MOUSE_BUTTON_3:
		return "SPARK_MOUSE_BUTTON_3";
	case SPARK_MOUSE_BUTTON_4:
		return "SPARK_MOUSE_BUTTON_4";
	case SPARK_MOUSE_BUTTON_5:
		return "SPARK_MOUSE_BUTTON_5";
	case SPARK_MOUSE_BUTTON_6:
		return "SPARK_MOUSE_BUTTON_6";
	case SPARK_MOUSE_BUTTON_7:
		return "SPARK_MOUSE_BUTTON_7";
	case SPARK_MOUSE_BUTTON_8:
		return "SPARK_MOUSE_BUTTON_8";
	default:
		return "UNKNOWN_SPARK_MOUSE_BUTTON";
	}
}

SPARKAPI SparkMouseButton SparkStringToMouseButton(SparkConstString string) {
	if (strcmp(string, "SPARK_MOUSE_BUTTON_1") == 0)
		return SPARK_MOUSE_BUTTON_1;
	else if (strcmp(string, "SPARK_MOUSE_BUTTON_2") == 0)
		return SPARK_MOUSE_BUTTON_2;
	else if (strcmp(string, "SPARK_MOUSE_BUTTON_3") == 0)
		return SPARK_MOUSE_BUTTON_3;
	else if (strcmp(string, "SPARK_MOUSE_BUTTON_4") == 0)
		return SPARK_MOUSE_BUTTON_4;
	else if (strcmp(string, "SPARK_MOUSE_BUTTON_5") == 0)
		return SPARK_MOUSE_BUTTON_5;
	else if (strcmp(string, "SPARK_MOUSE_BUTTON_6") == 0)
		return SPARK_MOUSE_BUTTON_6;
	else if (strcmp(string, "SPARK_MOUSE_BUTTON_7") == 0)
		return SPARK_MOUSE_BUTTON_7;
	else if (strcmp(string, "SPARK_MOUSE_BUTTON_8") == 0)
		return SPARK_MOUSE_BUTTON_8;
	else if (strcmp(string, "SPARK_MOUSE_BUTTON_LAST") == 0)
		return SPARK_MOUSE_BUTTON_LAST;
	else if (strcmp(string, "SPARK_MOUSE_BUTTON_LEFT") == 0)
		return SPARK_MOUSE_BUTTON_LEFT;
	else if (strcmp(string, "SPARK_MOUSE_BUTTON_RIGHT") == 0)
		return SPARK_MOUSE_BUTTON_RIGHT;
	else if (strcmp(string, "SPARK_MOUSE_BUTTON_MIDDLE") == 0)
		return SPARK_MOUSE_BUTTON_MIDDLE;
	else
		return (SparkMouseButton)-1;
}

SPARKAPI SparkConstString SparkKeyToString(SparkKey key) {
	switch (key) {
	case SPARK_KEY_UNKNOWN:
		return "SPARK_KEY_UNKNOWN";
	case SPARK_KEY_SPACE:
		return "SPARK_KEY_SPACE";
	case SPARK_KEY_APOSTROPHE:
		return "SPARK_KEY_APOSTROPHE";
	case SPARK_KEY_COMMA:
		return "SPARK_KEY_COMMA";
	case SPARK_KEY_MINUS:
		return "SPARK_KEY_MINUS";
	case SPARK_KEY_PERIOD:
		return "SPARK_KEY_PERIOD";
	case SPARK_KEY_SLASH:
		return "SPARK_KEY_SLASH";
	case SPARK_KEY_0:
		return "SPARK_KEY_0";
	case SPARK_KEY_1:
		return "SPARK_KEY_1";
	case SPARK_KEY_2:
		return "SPARK_KEY_2";
	case SPARK_KEY_3:
		return "SPARK_KEY_3";
	case SPARK_KEY_4:
		return "SPARK_KEY_4";
	case SPARK_KEY_5:
		return "SPARK_KEY_5";
	case SPARK_KEY_6:
		return "SPARK_KEY_6";
	case SPARK_KEY_7:
		return "SPARK_KEY_7";
	case SPARK_KEY_8:
		return "SPARK_KEY_8";
	case SPARK_KEY_9:
		return "SPARK_KEY_9";
	case SPARK_KEY_SEMICOLON:
		return "SPARK_KEY_SEMICOLON";
	case SPARK_KEY_EQUAL:
		return "SPARK_KEY_EQUAL";
	case SPARK_KEY_A:
		return "SPARK_KEY_A";
	case SPARK_KEY_B:
		return "SPARK_KEY_B";
	case SPARK_KEY_C:
		return "SPARK_KEY_C";
	case SPARK_KEY_D:
		return "SPARK_KEY_D";
	case SPARK_KEY_E:
		return "SPARK_KEY_E";
	case SPARK_KEY_F:
		return "SPARK_KEY_F";
	case SPARK_KEY_G:
		return "SPARK_KEY_G";
	case SPARK_KEY_H:
		return "SPARK_KEY_H";
	case SPARK_KEY_I:
		return "SPARK_KEY_I";
	case SPARK_KEY_J:
		return "SPARK_KEY_J";
	case SPARK_KEY_K:
		return "SPARK_KEY_K";
	case SPARK_KEY_L:
		return "SPARK_KEY_L";
	case SPARK_KEY_M:
		return "SPARK_KEY_M";
	case SPARK_KEY_N:
		return "SPARK_KEY_N";
	case SPARK_KEY_O:
		return "SPARK_KEY_O";
	case SPARK_KEY_P:
		return "SPARK_KEY_P";
	case SPARK_KEY_Q:
		return "SPARK_KEY_Q";
	case SPARK_KEY_R:
		return "SPARK_KEY_R";
	case SPARK_KEY_S:
		return "SPARK_KEY_S";
	case SPARK_KEY_T:
		return "SPARK_KEY_T";
	case SPARK_KEY_U:
		return "SPARK_KEY_U";
	case SPARK_KEY_V:
		return "SPARK_KEY_V";
	case SPARK_KEY_W:
		return "SPARK_KEY_W";
	case SPARK_KEY_X:
		return "SPARK_KEY_X";
	case SPARK_KEY_Y:
		return "SPARK_KEY_Y";
	case SPARK_KEY_Z:
		return "SPARK_KEY_Z";
	case SPARK_KEY_LEFT_BRACKET:
		return "SPARK_KEY_LEFT_BRACKET";
	case SPARK_KEY_BACKSLASH:
		return "SPARK_KEY_BACKSLASH";
	case SPARK_KEY_RIGHT_BRACKET:
		return "SPARK_KEY_RIGHT_BRACKET";
	case SPARK_KEY_GRAVE_ACCENT:
		return "SPARK_KEY_GRAVE_ACCENT";
	case SPARK_KEY_WORLD_1:
		return "SPARK_KEY_WORLD_1";
	case SPARK_KEY_WORLD_2:
		return "SPARK_KEY_WORLD_2";
	case SPARK_KEY_ESCAPE:
		return "SPARK_KEY_ESCAPE";
	case SPARK_KEY_ENTER:
		return "SPARK_KEY_ENTER";
	case SPARK_KEY_TAB:
		return "SPARK_KEY_TAB";
	case SPARK_KEY_BACKSPACE:
		return "SPARK_KEY_BACKSPACE";
	case SPARK_KEY_INSERT:
		return "SPARK_KEY_INSERT";
	case SPARK_KEY_DELETE:
		return "SPARK_KEY_DELETE";
	case SPARK_KEY_RIGHT:
		return "SPARK_KEY_RIGHT";
	case SPARK_KEY_LEFT:
		return "SPARK_KEY_LEFT";
	case SPARK_KEY_DOWN:
		return "SPARK_KEY_DOWN";
	case SPARK_KEY_UP:
		return "SPARK_KEY_UP";
	case SPARK_KEY_PAGE_UP:
		return "SPARK_KEY_PAGE_UP";
	case SPARK_KEY_PAGE_DOWN:
		return "SPARK_KEY_PAGE_DOWN";
	case SPARK_KEY_HOME:
		return "SPARK_KEY_HOME";
	case SPARK_KEY_END:
		return "SPARK_KEY_END";
	case SPARK_KEY_CAPS_LOCK:
		return "SPARK_KEY_CAPS_LOCK";
	case SPARK_KEY_SCROLL_LOCK:
		return "SPARK_KEY_SCROLL_LOCK";
	case SPARK_KEY_NUM_LOCK:
		return "SPARK_KEY_NUM_LOCK";
	case SPARK_KEY_PRINT_SCREEN:
		return "SPARK_KEY_PRINT_SCREEN";
	case SPARK_KEY_PAUSE:
		return "SPARK_KEY_PAUSE";
	case SPARK_KEY_F1:
		return "SPARK_KEY_F1";
	case SPARK_KEY_F2:
		return "SPARK_KEY_F2";
	case SPARK_KEY_F3:
		return "SPARK_KEY_F3";
	case SPARK_KEY_F4:
		return "SPARK_KEY_F4";
	case SPARK_KEY_F5:
		return "SPARK_KEY_F5";
	case SPARK_KEY_F6:
		return "SPARK_KEY_F6";
	case SPARK_KEY_F7:
		return "SPARK_KEY_F7";
	case SPARK_KEY_F8:
		return "SPARK_KEY_F8";
	case SPARK_KEY_F9:
		return "SPARK_KEY_F9";
	case SPARK_KEY_F10:
		return "SPARK_KEY_F10";
	case SPARK_KEY_F11:
		return "SPARK_KEY_F11";
	case SPARK_KEY_F12:
		return "SPARK_KEY_F12";
	case SPARK_KEY_F13:
		return "SPARK_KEY_F13";
	case SPARK_KEY_F14:
		return "SPARK_KEY_F14";
	case SPARK_KEY_F15:
		return "SPARK_KEY_F15";
	case SPARK_KEY_F16:
		return "SPARK_KEY_F16";
	case SPARK_KEY_F17:
		return "SPARK_KEY_F17";
	case SPARK_KEY_F18:
		return "SPARK_KEY_F18";
	case SPARK_KEY_F19:
		return "SPARK_KEY_F19";
	case SPARK_KEY_F20:
		return "SPARK_KEY_F20";
	case SPARK_KEY_F21:
		return "SPARK_KEY_F21";
	case SPARK_KEY_F22:
		return "SPARK_KEY_F22";
	case SPARK_KEY_F23:
		return "SPARK_KEY_F23";
	case SPARK_KEY_F24:
		return "SPARK_KEY_F24";
	case SPARK_KEY_F25:
		return "SPARK_KEY_F25";
	case SPARK_KEY_KP_0:
		return "SPARK_KEY_KP_0";
	case SPARK_KEY_KP_1:
		return "SPARK_KEY_KP_1";
	case SPARK_KEY_KP_2:
		return "SPARK_KEY_KP_2";
	case SPARK_KEY_KP_3:
		return "SPARK_KEY_KP_3";
	case SPARK_KEY_KP_4:
		return "SPARK_KEY_KP_4";
	case SPARK_KEY_KP_5:
		return "SPARK_KEY_KP_5";
	case SPARK_KEY_KP_6:
		return "SPARK_KEY_KP_6";
	case SPARK_KEY_KP_7:
		return "SPARK_KEY_KP_7";
	case SPARK_KEY_KP_8:
		return "SPARK_KEY_KP_8";
	case SPARK_KEY_KP_9:
		return "SPARK_KEY_KP_9";
	case SPARK_KEY_KP_DECIMAL:
		return "SPARK_KEY_KP_DECIMAL";
	case SPARK_KEY_KP_DIVIDE:
		return "SPARK_KEY_KP_DIVIDE";
	case SPARK_KEY_KP_MULTIPLY:
		return "SPARK_KEY_KP_MULTIPLY";
	case SPARK_KEY_KP_SUBTRACT:
		return "SPARK_KEY_KP_SUBTRACT";
	case SPARK_KEY_KP_ADD:
		return "SPARK_KEY_KP_ADD";
	case SPARK_KEY_KP_ENTER:
		return "SPARK_KEY_KP_ENTER";
	case SPARK_KEY_KP_EQUAL:
		return "SPARK_KEY_KP_EQUAL";
	case SPARK_KEY_LEFT_SHIFT:
		return "SPARK_KEY_LEFT_SHIFT";
	case SPARK_KEY_LEFT_CONTROL:
		return "SPARK_KEY_LEFT_CONTROL";
	case SPARK_KEY_LEFT_ALT:
		return "SPARK_KEY_LEFT_ALT";
	case SPARK_KEY_LEFT_SUPER:
		return "SPARK_KEY_LEFT_SUPER";
	case SPARK_KEY_RIGHT_SHIFT:
		return "SPARK_KEY_RIGHT_SHIFT";
	case SPARK_KEY_RIGHT_CONTROL:
		return "SPARK_KEY_RIGHT_CONTROL";
	case SPARK_KEY_RIGHT_ALT:
		return "SPARK_KEY_RIGHT_ALT";
	case SPARK_KEY_RIGHT_SUPER:
		return "SPARK_KEY_RIGHT_SUPER";
	case SPARK_KEY_MENU:
		return "SPARK_KEY_MENU";
	default:
		return "UNKNOWN_SPARK_KEY";
	}
}

SPARKAPI SparkKey SparkStringToKey(SparkConstString string) {
	if (strcmp(string, "SPARK_KEY_UNKNOWN") == 0)
		return SPARK_KEY_UNKNOWN;
	else if (strcmp(string, "SPARK_KEY_SPACE") == 0)
		return SPARK_KEY_SPACE;
	else if (strcmp(string, "SPARK_KEY_APOSTROPHE") == 0)
		return SPARK_KEY_APOSTROPHE;
	else if (strcmp(string, "SPARK_KEY_COMMA") == 0)
		return SPARK_KEY_COMMA;
	else if (strcmp(string, "SPARK_KEY_MINUS") == 0)
		return SPARK_KEY_MINUS;
	else if (strcmp(string, "SPARK_KEY_PERIOD") == 0)
		return SPARK_KEY_PERIOD;
	else if (strcmp(string, "SPARK_KEY_SLASH") == 0)
		return SPARK_KEY_SLASH;
	else if (strcmp(string, "SPARK_KEY_0") == 0)
		return SPARK_KEY_0;
	else if (strcmp(string, "SPARK_KEY_1") == 0)
		return SPARK_KEY_1;
	else if (strcmp(string, "SPARK_KEY_2") == 0)
		return SPARK_KEY_2;
	else if (strcmp(string, "SPARK_KEY_3") == 0)
		return SPARK_KEY_3;
	else if (strcmp(string, "SPARK_KEY_4") == 0)
		return SPARK_KEY_4;
	else if (strcmp(string, "SPARK_KEY_5") == 0)
		return SPARK_KEY_5;
	else if (strcmp(string, "SPARK_KEY_6") == 0)
		return SPARK_KEY_6;
	else if (strcmp(string, "SPARK_KEY_7") == 0)
		return SPARK_KEY_7;
	else if (strcmp(string, "SPARK_KEY_8") == 0)
		return SPARK_KEY_8;
	else if (strcmp(string, "SPARK_KEY_9") == 0)
		return SPARK_KEY_9;
	else if (strcmp(string, "SPARK_KEY_SEMICOLON") == 0)
		return SPARK_KEY_SEMICOLON;
	else if (strcmp(string, "SPARK_KEY_EQUAL") == 0)
		return SPARK_KEY_EQUAL;
	else if (strcmp(string, "SPARK_KEY_A") == 0)
		return SPARK_KEY_A;
	else if (strcmp(string, "SPARK_KEY_B") == 0)
		return SPARK_KEY_B;
	else if (strcmp(string, "SPARK_KEY_C") == 0)
		return SPARK_KEY_C;
	else if (strcmp(string, "SPARK_KEY_D") == 0)
		return SPARK_KEY_D;
	else if (strcmp(string, "SPARK_KEY_E") == 0)
		return SPARK_KEY_E;
	else if (strcmp(string, "SPARK_KEY_F") == 0)
		return SPARK_KEY_F;
	else if (strcmp(string, "SPARK_KEY_G") == 0)
		return SPARK_KEY_G;
	else if (strcmp(string, "SPARK_KEY_H") == 0)
		return SPARK_KEY_H;
	else if (strcmp(string, "SPARK_KEY_I") == 0)
		return SPARK_KEY_I;
	else if (strcmp(string, "SPARK_KEY_J") == 0)
		return SPARK_KEY_J;
	else if (strcmp(string, "SPARK_KEY_K") == 0)
		return SPARK_KEY_K;
	else if (strcmp(string, "SPARK_KEY_L") == 0)
		return SPARK_KEY_L;
	else if (strcmp(string, "SPARK_KEY_M") == 0)
		return SPARK_KEY_M;
	else if (strcmp(string, "SPARK_KEY_N") == 0)
		return SPARK_KEY_N;
	else if (strcmp(string, "SPARK_KEY_O") == 0)
		return SPARK_KEY_O;
	else if (strcmp(string, "SPARK_KEY_P") == 0)
		return SPARK_KEY_P;
	else if (strcmp(string, "SPARK_KEY_Q") == 0)
		return SPARK_KEY_Q;
	else if (strcmp(string, "SPARK_KEY_R") == 0)
		return SPARK_KEY_R;
	else if (strcmp(string, "SPARK_KEY_S") == 0)
		return SPARK_KEY_S;
	else if (strcmp(string, "SPARK_KEY_T") == 0)
		return SPARK_KEY_T;
	else if (strcmp(string, "SPARK_KEY_U") == 0)
		return SPARK_KEY_U;
	else if (strcmp(string, "SPARK_KEY_V") == 0)
		return SPARK_KEY_V;
	else if (strcmp(string, "SPARK_KEY_W") == 0)
		return SPARK_KEY_W;
	else if (strcmp(string, "SPARK_KEY_X") == 0)
		return SPARK_KEY_X;
	else if (strcmp(string, "SPARK_KEY_Y") == 0)
		return SPARK_KEY_Y;
	else if (strcmp(string, "SPARK_KEY_Z") == 0)
		return SPARK_KEY_Z;
	else if (strcmp(string, "SPARK_KEY_LEFT_BRACKET") == 0)
		return SPARK_KEY_LEFT_BRACKET;
	else if (strcmp(string, "SPARK_KEY_BACKSLASH") == 0)
		return SPARK_KEY_BACKSLASH;
	else if (strcmp(string, "SPARK_KEY_RIGHT_BRACKET") == 0)
		return SPARK_KEY_RIGHT_BRACKET;
	else if (strcmp(string, "SPARK_KEY_GRAVE_ACCENT") == 0)
		return SPARK_KEY_GRAVE_ACCENT;
	else if (strcmp(string, "SPARK_KEY_WORLD_1") == 0)
		return SPARK_KEY_WORLD_1;
	else if (strcmp(string, "SPARK_KEY_WORLD_2") == 0)
		return SPARK_KEY_WORLD_2;
	else if (strcmp(string, "SPARK_KEY_ESCAPE") == 0)
		return SPARK_KEY_ESCAPE;
	else if (strcmp(string, "SPARK_KEY_ENTER") == 0)
		return SPARK_KEY_ENTER;
	else if (strcmp(string, "SPARK_KEY_TAB") == 0)
		return SPARK_KEY_TAB;
	else if (strcmp(string, "SPARK_KEY_BACKSPACE") == 0)
		return SPARK_KEY_BACKSPACE;
	else if (strcmp(string, "SPARK_KEY_INSERT") == 0)
		return SPARK_KEY_INSERT;
	else if (strcmp(string, "SPARK_KEY_DELETE") == 0)
		return SPARK_KEY_DELETE;
	else if (strcmp(string, "SPARK_KEY_RIGHT") == 0)
		return SPARK_KEY_RIGHT;
	else if (strcmp(string, "SPARK_KEY_LEFT") == 0)
		return SPARK_KEY_LEFT;
	else if (strcmp(string, "SPARK_KEY_DOWN") == 0)
		return SPARK_KEY_DOWN;
	else if (strcmp(string, "SPARK_KEY_UP") == 0)
		return SPARK_KEY_UP;
	else if (strcmp(string, "SPARK_KEY_PAGE_UP") == 0)
		return SPARK_KEY_PAGE_UP;
	else if (strcmp(string, "SPARK_KEY_PAGE_DOWN") == 0)
		return SPARK_KEY_PAGE_DOWN;
	else if (strcmp(string, "SPARK_KEY_HOME") == 0)
		return SPARK_KEY_HOME;
	else if (strcmp(string, "SPARK_KEY_END") == 0)
		return SPARK_KEY_END;
	else if (strcmp(string, "SPARK_KEY_CAPS_LOCK") == 0)
		return SPARK_KEY_CAPS_LOCK;
	else if (strcmp(string, "SPARK_KEY_SCROLL_LOCK") == 0)
		return SPARK_KEY_SCROLL_LOCK;
	else if (strcmp(string, "SPARK_KEY_NUM_LOCK") == 0)
		return SPARK_KEY_NUM_LOCK;
	else if (strcmp(string, "SPARK_KEY_PRINT_SCREEN") == 0)
		return SPARK_KEY_PRINT_SCREEN;
	else if (strcmp(string, "SPARK_KEY_PAUSE") == 0)
		return SPARK_KEY_PAUSE;
	else if (strcmp(string, "SPARK_KEY_F1") == 0)
		return SPARK_KEY_F1;
	else if (strcmp(string, "SPARK_KEY_F2") == 0)
		return SPARK_KEY_F2;
	else if (strcmp(string, "SPARK_KEY_F3") == 0)
		return SPARK_KEY_F3;
	else if (strcmp(string, "SPARK_KEY_F4") == 0)
		return SPARK_KEY_F4;
	else if (strcmp(string, "SPARK_KEY_F5") == 0)
		return SPARK_KEY_F5;
	else if (strcmp(string, "SPARK_KEY_F6") == 0)
		return SPARK_KEY_F6;
	else if (strcmp(string, "SPARK_KEY_F7") == 0)
		return SPARK_KEY_F7;
	else if (strcmp(string, "SPARK_KEY_F8") == 0)
		return SPARK_KEY_F8;
	else if (strcmp(string, "SPARK_KEY_F9") == 0)
		return SPARK_KEY_F9;
	else if (strcmp(string, "SPARK_KEY_F10") == 0)
		return SPARK_KEY_F10;
	else if (strcmp(string, "SPARK_KEY_F11") == 0)
		return SPARK_KEY_F11;
	else if (strcmp(string, "SPARK_KEY_F12") == 0)
		return SPARK_KEY_F12;
	else if (strcmp(string, "SPARK_KEY_F13") == 0)
		return SPARK_KEY_F13;
	else if (strcmp(string, "SPARK_KEY_F14") == 0)
		return SPARK_KEY_F14;
	else if (strcmp(string, "SPARK_KEY_F15") == 0)
		return SPARK_KEY_F15;
	else if (strcmp(string, "SPARK_KEY_F16") == 0)
		return SPARK_KEY_F16;
	else if (strcmp(string, "SPARK_KEY_F17") == 0)
		return SPARK_KEY_F17;
	else if (strcmp(string, "SPARK_KEY_F18") == 0)
		return SPARK_KEY_F18;
	else if (strcmp(string, "SPARK_KEY_F19") == 0)
		return SPARK_KEY_F19;
	else if (strcmp(string, "SPARK_KEY_F20") == 0)
		return SPARK_KEY_F20;
	else if (strcmp(string, "SPARK_KEY_F21") == 0)
		return SPARK_KEY_F21;
	else if (strcmp(string, "SPARK_KEY_F22") == 0)
		return SPARK_KEY_F22;
	else if (strcmp(string, "SPARK_KEY_F23") == 0)
		return SPARK_KEY_F23;
	else if (strcmp(string, "SPARK_KEY_F24") == 0)
		return SPARK_KEY_F24;
	else if (strcmp(string, "SPARK_KEY_F25") == 0)
		return SPARK_KEY_F25;
	else if (strcmp(string, "SPARK_KEY_KP_0") == 0)
		return SPARK_KEY_KP_0;
	else if (strcmp(string, "SPARK_KEY_KP_1") == 0)
		return SPARK_KEY_KP_1;
	else if (strcmp(string, "SPARK_KEY_KP_2") == 0)
		return SPARK_KEY_KP_2;
	else if (strcmp(string, "SPARK_KEY_KP_3") == 0)
		return SPARK_KEY_KP_3;
	else if (strcmp(string, "SPARK_KEY_KP_4") == 0)
		return SPARK_KEY_KP_4;
	else if (strcmp(string, "SPARK_KEY_KP_5") == 0)
		return SPARK_KEY_KP_5;
	else if (strcmp(string, "SPARK_KEY_KP_6") == 0)
		return SPARK_KEY_KP_6;
	else if (strcmp(string, "SPARK_KEY_KP_7") == 0)
		return SPARK_KEY_KP_7;
	else if (strcmp(string, "SPARK_KEY_KP_8") == 0)
		return SPARK_KEY_KP_8;
	else if (strcmp(string, "SPARK_KEY_KP_9") == 0)
		return SPARK_KEY_KP_9;
	else if (strcmp(string, "SPARK_KEY_KP_DECIMAL") == 0)
		return SPARK_KEY_KP_DECIMAL;
	else if (strcmp(string, "SPARK_KEY_KP_DIVIDE") == 0)
		return SPARK_KEY_KP_DIVIDE;
	else if (strcmp(string, "SPARK_KEY_KP_MULTIPLY") == 0)
		return SPARK_KEY_KP_MULTIPLY;
	else if (strcmp(string, "SPARK_KEY_KP_SUBTRACT") == 0)
		return SPARK_KEY_KP_SUBTRACT;
	else if (strcmp(string, "SPARK_KEY_KP_ADD") == 0)
		return SPARK_KEY_KP_ADD;
	else if (strcmp(string, "SPARK_KEY_KP_ENTER") == 0)
		return SPARK_KEY_KP_ENTER;
	else if (strcmp(string, "SPARK_KEY_KP_EQUAL") == 0)
		return SPARK_KEY_KP_EQUAL;
	else if (strcmp(string, "SPARK_KEY_LEFT_SHIFT") == 0)
		return SPARK_KEY_LEFT_SHIFT;
	else if (strcmp(string, "SPARK_KEY_LEFT_CONTROL") == 0)
		return SPARK_KEY_LEFT_CONTROL;
	else if (strcmp(string, "SPARK_KEY_LEFT_ALT") == 0)
		return SPARK_KEY_LEFT_ALT;
	else if (strcmp(string, "SPARK_KEY_LEFT_SUPER") == 0)
		return SPARK_KEY_LEFT_SUPER;
	else if (strcmp(string, "SPARK_KEY_RIGHT_SHIFT") == 0)
		return SPARK_KEY_RIGHT_SHIFT;
	else if (strcmp(string, "SPARK_KEY_RIGHT_CONTROL") == 0)
		return SPARK_KEY_RIGHT_CONTROL;
	else if (strcmp(string, "SPARK_KEY_RIGHT_ALT") == 0)
		return SPARK_KEY_RIGHT_ALT;
	else if (strcmp(string, "SPARK_KEY_RIGHT_SUPER") == 0)
		return SPARK_KEY_RIGHT_SUPER;
	else if (strcmp(string, "SPARK_KEY_MENU") == 0)
		return SPARK_KEY_MENU;
	return SPARK_KEY_UNKNOWN;
}

SPARKAPI SparkConstString SparkModifierToString(SparkModifier modifier) {
	switch (modifier) {
	case SPARK_MOD_SHIFT:
		return "SPARK_MOD_SHIFT";
	case SPARK_MOD_CONTROL:
		return "SPARK_MOD_CONTROL";
	case SPARK_MOD_ALT:
		return "SPARK_MOD_ALT";
	case SPARK_MOD_SUPER:
		return "SPARK_MOD_SUPER";
	default:
		return "UNKNOWN_SPARK_MODIFIER";
	}
}

SPARKAPI SparkModifier SparkStringToModifier(SparkConstString string) {
	if (strcmp(string, "SPARK_MOD_SHIFT") == 0)
		return SPARK_MOD_SHIFT;
	else if (strcmp(string, "SPARK_MOD_CONTROL") == 0)
		return SPARK_MOD_CONTROL;
	else if (strcmp(string, "SPARK_MOD_ALT") == 0)
		return SPARK_MOD_ALT;
	else if (strcmp(string, "SPARK_MOD_SUPER") == 0)
		return SPARK_MOD_SUPER;
	else
		return (SparkModifier)0;
}

SPARKAPI SparkConstString SparkActionToString(SparkAction action) {
	switch (action) {
	case SPARK_RELEASE:
		return "SPARK_RELEASE";
	case SPARK_PRESS:
		return "SPARK_PRESS";
	case SPARK_REPEAT:
		return "SPARK_REPEAT";
	default:
		return "UNKNOWN_SPARK_ACTION";
	}
}

SPARKAPI SparkAction SparkStringToAction(SparkConstString string) {
	if (strcmp(string, "SPARK_RELEASE") == 0)
		return SPARK_RELEASE;
	else if (strcmp(string, "SPARK_PRESS") == 0)
		return SPARK_PRESS;
	else if (strcmp(string, "SPARK_REPEAT") == 0)
		return SPARK_REPEAT;
	else
		return (SparkAction)-1;
}

SPARKAPI SparkConstString SparkCursorToString(SparkCursor cursor) {
	switch (cursor) {
	case SPARK_CURSOR_ARROW:
		return "SPARK_CURSOR_ARROW";
	case SPARK_CURSOR_IBEAM:
		return "SPARK_CURSOR_IBEAM";
	case SPARK_CURSOR_CROSSHAIR:
		return "SPARK_CURSOR_CROSSHAIR";
	case SPARK_CURSOR_HAND:
		return "SPARK_CURSOR_HAND";
	case SPARK_CURSOR_HRESIZE:
		return "SPARK_CURSOR_HRESIZE";
	case SPARK_CURSOR_VRESIZE:
		return "SPARK_CURSOR_VRESIZE";
	default:
		return "UNKNOWN_SPARK_CURSOR";
	}
}

SPARKAPI SparkCursor SparkStringToCursor(SparkConstString string) {
	if (strcmp(string, "SPARK_CURSOR_ARROW") == 0)
		return SPARK_CURSOR_ARROW;
	else if (strcmp(string, "SPARK_CURSOR_IBEAM") == 0)
		return SPARK_CURSOR_IBEAM;
	else if (strcmp(string, "SPARK_CURSOR_CROSSHAIR") == 0)
		return SPARK_CURSOR_CROSSHAIR;
	else if (strcmp(string, "SPARK_CURSOR_HAND") == 0)
		return SPARK_CURSOR_HAND;
	else if (strcmp(string, "SPARK_CURSOR_HRESIZE") == 0)
		return SPARK_CURSOR_HRESIZE;
	else if (strcmp(string, "SPARK_CURSOR_VRESIZE") == 0)
		return SPARK_CURSOR_VRESIZE;
	else
		return (SparkCursor)-1;
}

SPARKAPI SparkConstString SparkEventTypeToString(SparkEventType eventType) {
	switch (eventType) {
	case SPARK_EVENT_NONE:
		return "SPARK_EVENT_NONE";
	case SPARK_EVENT_WINDOW_CLOSE:
		return "SPARK_EVENT_WINDOW_CLOSE";
	case SPARK_EVENT_WINDOW_RESIZE:
		return "SPARK_EVENT_WINDOW_RESIZE";
	case SPARK_EVENT_WINDOW_FOCUS:
		return "SPARK_EVENT_WINDOW_FOCUS";
	case SPARK_EVENT_WINDOW_LOST_FOCUS:
		return "SPARK_EVENT_WINDOW_LOST_FOCUS";
	case SPARK_EVENT_WINDOW_MOVED:
		return "SPARK_EVENT_WINDOW_MOVED";
	case SPARK_EVENT_KEY_PRESSED:
		return "SPARK_EVENT_KEY_PRESSED";
	case SPARK_EVENT_KEY_RELEASED:
		return "SPARK_EVENT_KEY_RELEASED";
	case SPARK_EVENT_KEY_TYPED:
		return "SPARK_EVENT_KEY_TYPED";
	case SPARK_EVENT_MOUSE_BUTTON_PRESSED:
		return "SPARK_EVENT_MOUSE_BUTTON_PRESSED";
	case SPARK_EVENT_MOUSE_BUTTON_RELEASED:
		return "SPARK_EVENT_MOUSE_BUTTON_RELEASED";
	case SPARK_EVENT_MOUSE_MOVED:
		return "SPARK_EVENT_MOUSE_MOVED";
	case SPARK_EVENT_MOUSE_SCROLLED:
		return "SPARK_EVENT_MOUSE_SCROLLED";
	default:
		return "UNKNOWN_SPARK_EVENT_TYPE";
	}
}

SPARKAPI SparkEventType SparkStringToEventType(SparkConstString string) {
	if (strcmp(string, "SPARK_EVENT_NONE") == 0)
		return SPARK_EVENT_NONE;
	else if (strcmp(string, "SPARK_EVENT_WINDOW_CLOSE") == 0)
		return SPARK_EVENT_WINDOW_CLOSE;
	else if (strcmp(string, "SPARK_EVENT_WINDOW_RESIZE") == 0)
		return SPARK_EVENT_WINDOW_RESIZE;
	else if (strcmp(string, "SPARK_EVENT_WINDOW_FOCUS") == 0)
		return SPARK_EVENT_WINDOW_FOCUS;
	else if (strcmp(string, "SPARK_EVENT_WINDOW_LOST_FOCUS") == 0)
		return SPARK_EVENT_WINDOW_LOST_FOCUS;
	else if (strcmp(string, "SPARK_EVENT_WINDOW_MOVED") == 0)
		return SPARK_EVENT_WINDOW_MOVED;
	else if (strcmp(string, "SPARK_EVENT_KEY_PRESSED") == 0)
		return SPARK_EVENT_KEY_PRESSED;
	else if (strcmp(string, "SPARK_EVENT_KEY_RELEASED") == 0)
		return SPARK_EVENT_KEY_RELEASED;
	else if (strcmp(string, "SPARK_EVENT_KEY_TYPED") == 0)
		return SPARK_EVENT_KEY_TYPED;
	else if (strcmp(string, "SPARK_EVENT_MOUSE_BUTTON_PRESSED") == 0)
		return SPARK_EVENT_MOUSE_BUTTON_PRESSED;
	else if (strcmp(string, "SPARK_EVENT_MOUSE_BUTTON_RELEASED") == 0)
		return SPARK_EVENT_MOUSE_BUTTON_RELEASED;
	else if (strcmp(string, "SPARK_EVENT_MOUSE_MOVED") == 0)
		return SPARK_EVENT_MOUSE_MOVED;
	else if (strcmp(string, "SPARK_EVENT_MOUSE_SCROLLED") == 0)
		return SPARK_EVENT_MOUSE_SCROLLED;
	else
		return (SparkEventType)-1;
}

SPARKAPI SparkConstString SparkShaderTypeToString(SparkShaderType shaderType) {
	switch (shaderType) {
	case SPARK_SHADER_VERTEX:
		return "SPARK_SHADER_VERTEX";
	case SPARK_SHADER_FRAGMENT:
		return "SPARK_SHADER_FRAGMENT";
	case SPARK_SHADER_GEOMETRY:
		return "SPARK_SHADER_GEOMETRY";
	case SPARK_SHADER_TESSELLATION_CONTROL:
		return "SPARK_SHADER_TESSELLATION_CONTROL";
	case SPARK_SHADER_TESSELLATION_EVALUATION:
		return "SPARK_SHADER_TESSELLATION_EVALUATION";
	case SPARK_SHADER_COMPUTE:
		return "SPARK_SHADER_COMPUTE";
	default:
		return "UNKNOWN_SPARK_SHADER_TYPE";
	}
}

SPARKAPI SparkShaderType SparkStringToShaderType(SparkConstString string) {
	if (strcmp(string, "SPARK_SHADER_VERTEX") == 0)
		return SPARK_SHADER_VERTEX;
	else if (strcmp(string, "SPARK_SHADER_FRAGMENT") == 0)
		return SPARK_SHADER_FRAGMENT;
	else if (strcmp(string, "SPARK_SHADER_GEOMETRY") == 0)
		return SPARK_SHADER_GEOMETRY;
	else if (strcmp(string, "SPARK_SHADER_TESSELLATION_CONTROL") == 0)
		return SPARK_SHADER_TESSELLATION_CONTROL;
	else if (strcmp(string, "SPARK_SHADER_TESSELLATION_EVALUATION") == 0)
		return SPARK_SHADER_TESSELLATION_EVALUATION;
	else if (strcmp(string, "SPARK_SHADER_COMPUTE") == 0)
		return SPARK_SHADER_COMPUTE;
	else
		return (SparkShaderType)-1;
}

SPARKAPI SparkConstString
SparkPrimitiveTypeToString(SparkPrimitiveType primitiveType) {
	switch (primitiveType) {
	case SPARK_PRIMITIVE_POINTS:
		return "SPARK_PRIMITIVE_POINTS";
	case SPARK_PRIMITIVE_LINES:
		return "SPARK_PRIMITIVE_LINES";
	case SPARK_PRIMITIVE_LINE_STRIP:
		return "SPARK_PRIMITIVE_LINE_STRIP";
	case SPARK_PRIMITIVE_TRIANGLES:
		return "SPARK_PRIMITIVE_TRIANGLES";
	case SPARK_PRIMITIVE_TRIANGLE_STRIP:
		return "SPARK_PRIMITIVE_TRIANGLE_STRIP";
	case SPARK_PRIMITIVE_TRIANGLE_FAN:
		return "SPARK_PRIMITIVE_TRIANGLE_FAN";
	default:
		return "UNKNOWN_SPARK_PRIMITIVE_TYPE";
	}
}

SPARKAPI SparkPrimitiveType
SparkStringToPrimitiveType(SparkConstString string) {
	if (strcmp(string, "SPARK_PRIMITIVE_POINTS") == 0)
		return SPARK_PRIMITIVE_POINTS;
	else if (strcmp(string, "SPARK_PRIMITIVE_LINES") == 0)
		return SPARK_PRIMITIVE_LINES;
	else if (strcmp(string, "SPARK_PRIMITIVE_LINE_STRIP") == 0)
		return SPARK_PRIMITIVE_LINE_STRIP;
	else if (strcmp(string, "SPARK_PRIMITIVE_TRIANGLES") == 0)
		return SPARK_PRIMITIVE_TRIANGLES;
	else if (strcmp(string, "SPARK_PRIMITIVE_TRIANGLE_STRIP") == 0)
		return SPARK_PRIMITIVE_TRIANGLE_STRIP;
	else if (strcmp(string, "SPARK_PRIMITIVE_TRIANGLE_FAN") == 0)
		return SPARK_PRIMITIVE_TRIANGLE_FAN;
	else
		return (SparkPrimitiveType)-1;
}

SPARKAPI SparkConstString SparkBlendModeToString(SparkBlendMode blendMode) {
	switch (blendMode) {
	case SPARK_BLEND_ZERO:
		return "SPARK_BLEND_ZERO";
	case SPARK_BLEND_ONE:
		return "SPARK_BLEND_ONE";
	case SPARK_BLEND_SRC_COLOR:
		return "SPARK_BLEND_SRC_COLOR";
	case SPARK_BLEND_ONE_MINUS_SRC_COLOR:
		return "SPARK_BLEND_ONE_MINUS_SRC_COLOR";
	case SPARK_BLEND_DST_COLOR:
		return "SPARK_BLEND_DST_COLOR";
	case SPARK_BLEND_ONE_MINUS_DST_COLOR:
		return "SPARK_BLEND_ONE_MINUS_DST_COLOR";
	case SPARK_BLEND_SRC_ALPHA:
		return "SPARK_BLEND_SRC_ALPHA";
	case SPARK_BLEND_ONE_MINUS_SRC_ALPHA:
		return "SPARK_BLEND_ONE_MINUS_SRC_ALPHA";
	case SPARK_BLEND_DST_ALPHA:
		return "SPARK_BLEND_DST_ALPHA";
	case SPARK_BLEND_ONE_MINUS_DST_ALPHA:
		return "SPARK_BLEND_ONE_MINUS_DST_ALPHA";
	case SPARK_BLEND_CONSTANT_COLOR:
		return "SPARK_BLEND_CONSTANT_COLOR";
	case SPARK_BLEND_ONE_MINUS_CONSTANT_COLOR:
		return "SPARK_BLEND_ONE_MINUS_CONSTANT_COLOR";
	case SPARK_BLEND_CONSTANT_ALPHA:
		return "SPARK_BLEND_CONSTANT_ALPHA";
	case SPARK_BLEND_ONE_MINUS_CONSTANT_ALPHA:
		return "SPARK_BLEND_ONE_MINUS_CONSTANT_ALPHA";
	case SPARK_BLEND_SRC_ALPHA_SATURATE:
		return "SPARK_BLEND_SRC_ALPHA_SATURATE";
	default:
		return "UNKNOWN_SPARK_BLEND_MODE";
	}
}

SPARKAPI SparkBlendMode SparkStringToBlendMode(SparkConstString string) {
	if (strcmp(string, "SPARK_BLEND_ZERO") == 0)
		return SPARK_BLEND_ZERO;
	else if (strcmp(string, "SPARK_BLEND_ONE") == 0)
		return SPARK_BLEND_ONE;
	else if (strcmp(string, "SPARK_BLEND_SRC_COLOR") == 0)
		return SPARK_BLEND_SRC_COLOR;
	else if (strcmp(string, "SPARK_BLEND_ONE_MINUS_SRC_COLOR") == 0)
		return SPARK_BLEND_ONE_MINUS_SRC_COLOR;
	else if (strcmp(string, "SPARK_BLEND_DST_COLOR") == 0)
		return SPARK_BLEND_DST_COLOR;
	else if (strcmp(string, "SPARK_BLEND_ONE_MINUS_DST_COLOR") == 0)
		return SPARK_BLEND_ONE_MINUS_DST_COLOR;
	else if (strcmp(string, "SPARK_BLEND_SRC_ALPHA") == 0)
		return SPARK_BLEND_SRC_ALPHA;
	else if (strcmp(string, "SPARK_BLEND_ONE_MINUS_SRC_ALPHA") == 0)
		return SPARK_BLEND_ONE_MINUS_SRC_ALPHA;
	else if (strcmp(string, "SPARK_BLEND_DST_ALPHA") == 0)
		return SPARK_BLEND_DST_ALPHA;
	else if (strcmp(string, "SPARK_BLEND_ONE_MINUS_DST_ALPHA") == 0)
		return SPARK_BLEND_ONE_MINUS_DST_ALPHA;
	else if (strcmp(string, "SPARK_BLEND_CONSTANT_COLOR") == 0)
		return SPARK_BLEND_CONSTANT_COLOR;
	else if (strcmp(string, "SPARK_BLEND_ONE_MINUS_CONSTANT_COLOR") == 0)
		return SPARK_BLEND_ONE_MINUS_CONSTANT_COLOR;
	else if (strcmp(string, "SPARK_BLEND_CONSTANT_ALPHA") == 0)
		return SPARK_BLEND_CONSTANT_ALPHA;
	else if (strcmp(string, "SPARK_BLEND_ONE_MINUS_CONSTANT_ALPHA") == 0)
		return SPARK_BLEND_ONE_MINUS_CONSTANT_ALPHA;
	else if (strcmp(string, "SPARK_BLEND_SRC_ALPHA_SATURATE") == 0)
		return SPARK_BLEND_SRC_ALPHA_SATURATE;
	else
		return (SparkBlendMode)-1;
}

SPARKAPI SparkConstString SparkLogLevelToString(SparkLogLevel level) {
	switch (level) {
	case SPARK_LOG_LEVEL_TRACE:
		return "SPARK_LOG_LEVEL_TRACE";
	case SPARK_LOG_LEVEL_DEBUG:
		return "SPARK_LOG_LEVEL_DEBUG";
	case SPARK_LOG_LEVEL_INFO:
		return "SPARK_LOG_LEVEL_INFO";
	case SPARK_LOG_LEVEL_WARN:
		return "SPARK_LOG_LEVEL_WARN";
	case SPARK_LOG_LEVEL_ERROR:
		return "SPARK_LOG_LEVEL_ERROR";
	case SPARK_LOG_LEVEL_FATAL:
		return "SPARK_LOG_LEVEL_FATAL";
	default:
		return "UNKNOWN_SPARK_LOG_LEVEL";
	}
}

SPARKAPI SparkLogLevel SparkStringToLogLevel(SparkConstString string) {
	if (strcmp(string, "SPARK_LOG_LEVEL_TRACE") == 0)
		return SPARK_LOG_LEVEL_TRACE;
	else if (strcmp(string, "SPARK_LOG_LEVEL_DEBUG") == 0)
		return SPARK_LOG_LEVEL_DEBUG;
	else if (strcmp(string, "SPARK_LOG_LEVEL_INFO") == 0)
		return SPARK_LOG_LEVEL_INFO;
	else if (strcmp(string, "SPARK_LOG_LEVEL_WARN") == 0)
		return SPARK_LOG_LEVEL_WARN;
	else if (strcmp(string, "SPARK_LOG_LEVEL_ERROR") == 0)
		return SPARK_LOG_LEVEL_ERROR;
	else if (strcmp(string, "SPARK_LOG_LEVEL_FATAL") == 0)
		return SPARK_LOG_LEVEL_FATAL;
	else
		return (SparkLogLevel)-1;
}

SPARKAPI SparkConstString SparkRenderAPIToString(SparkRenderAPI api) {
	switch (api) {
	case SPARK_RENDER_API_NONE:
		return "SPARK_RENDER_API_NONE";
	case SPARK_RENDER_API_OPENGL:
		return "SPARK_RENDER_API_OPENGL";
	case SPARK_RENDER_API_VULKAN:
		return "SPARK_RENDER_API_VULKAN";
	case SPARK_RENDER_API_DIRECTX:
		return "SPARK_RENDER_API_DIRECTX";
	case SPARK_RENDER_API_METAL:
		return "SPARK_RENDER_API_METAL";
	default:
		return "UNKNOWN_SPARK_RENDER_API";
	}
}

SPARKAPI SparkRenderAPI SparkStringToRenderAPI(SparkConstString string) {
	if (strcmp(string, "SPARK_RENDER_API_NONE") == 0)
		return SPARK_RENDER_API_NONE;
	else if (strcmp(string, "SPARK_RENDER_API_OPENGL") == 0)
		return SPARK_RENDER_API_OPENGL;
	else if (strcmp(string, "SPARK_RENDER_API_VULKAN") == 0)
		return SPARK_RENDER_API_VULKAN;
	else if (strcmp(string, "SPARK_RENDER_API_DIRECTX") == 0)
		return SPARK_RENDER_API_DIRECTX;
	else if (strcmp(string, "SPARK_RENDER_API_METAL") == 0)
		return SPARK_RENDER_API_METAL;
	else
		return (SparkRenderAPI)-1;
}

#pragma endregion

#pragma region UTIL

SPARKAPI SparkConstString SparkFormatString(SparkConstString format, ...) {
	va_list args;
	va_start(args, format);

	// Get the length of the formatted string
	SparkSize length = vsnprintf(SPARK_NULL, 0, format, args);

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

SPARKAPI SparkVoid SparkLogImpl(SparkLogLevel log_level, SparkConstString format,
	...) {
	va_list args;
	va_start(args, format);

	// Set the appropriate color based on the log level
	switch (log_level) {
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
	if (log_level == SPARK_LOG_LEVEL_FATAL) {
		SPARK_CRASH_PROGRAM("Fatal error occurred!");
	}

	va_end(args);
}

SPARKAPI SparkResult SparkCheckSuccess(SparkResult result) {
	if (result != SPARK_SUCCESS) {
		SPARK_LOG_ERROR(SparkResultToString(result));
	}
	return result;
}

SPARKAPI SparkConstString SparkGetTime() {
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	const SparkI32 output_size = 40;

	SparkConstString output = malloc(output_size);

	if (snprintf(output, output_size, "[%d/%d/%d %d:%d:%d]", timeinfo->tm_mday,
		timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour,
		timeinfo->tm_min, timeinfo->tm_sec) < 0)
		return SPARK_NULL;

	return output;
}

SPARKAPI SparkConstString SparkGetFileExtension(SparkConstString filename) {
	SparkConstString dot = strrchr(filename, '.');
	if (!dot || dot == filename)
		return "";
	return dot + 1;
}

#pragma endregion

#pragma region MATH

#include <math.h> // For standard math functions like sin, cos, sqrt, etc.

/* Scalar functions */
SPARKAPI SparkScalar SparkClampS(SparkScalar value, SparkScalar min,
	SparkScalar max) {
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

SPARKAPI SparkScalar SparkMinS(SparkScalar a, SparkScalar b) {
	return (a < b) ? a : b;
}

SPARKAPI SparkScalar SparkMaxS(SparkScalar a, SparkScalar b) {
	return (a > b) ? a : b;
}

SPARKAPI SparkScalar SparkMixS(SparkScalar x, SparkScalar y, SparkScalar a) {
	return x * (1 - a) + y * a;
}

SPARKAPI SparkScalar SparkStepS(SparkScalar edge, SparkScalar x) {
	return x < edge ? 0.0f : 1.0f;
}

SPARKAPI SparkScalar SparkSmoothStepS(SparkScalar edge0, SparkScalar edge1,
	SparkScalar x) {
	SparkScalar t = SparkClampS((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
	return t * t * (3 - 2 * t);
}

SPARKAPI SparkScalar SparkSign(SparkScalar x) {
	if (x > 0)
		return 1.0f;
	else if (x < 0)
		return -1.0f;
	else
		return 0.0f;
}

SPARKAPI SparkScalar SparkMod(SparkScalar x, SparkScalar y) {
	return fmodf(x, y);
}

SPARKAPI SparkScalar SparkAbs(SparkScalar value) { return fabsf(value); }

SPARKAPI SparkScalar SparkFloor(SparkScalar value) { return floorf(value); }

SPARKAPI SparkScalar SparkCeil(SparkScalar value) { return ceilf(value); }

SPARKAPI SparkScalar SparkFract(SparkScalar value) {
	return value - SparkFloor(value);
}

SPARKAPI SparkScalar SparkSqrt(SparkScalar value) { return sqrtf(value); }

SPARKAPI SparkScalar SparkPow(SparkScalar base, SparkScalar exponent) {
	return powf(base, exponent);
}

SPARKAPI SparkScalar SparkExp(SparkScalar exponent) { return expf(exponent); }

SPARKAPI SparkScalar SparkLog2(SparkScalar value) { return log2f(value); }

SPARKAPI SparkScalar SparkInverseSqrt(SparkScalar value) {
	return 1.0f / SparkSqrt(value);
}

/* Trigonometric functions */
SPARKAPI SparkScalar SparkRadians(SparkScalar degrees) {
	return degrees * (SparkScalar)(SPARK_PI / 180.0f);
}

SPARKAPI SparkScalar SparkDegrees(SparkScalar radians) {
	return radians * (SparkScalar)(180.0f / SPARK_PI);
}

SPARKAPI SparkScalar SparkSin(SparkScalar angle) { return sinf(angle); }

SPARKAPI SparkScalar SparkCos(SparkScalar angle) { return cosf(angle); }

SPARKAPI SparkScalar SparkTan(SparkScalar angle) { return tanf(angle); }

SPARKAPI SparkScalar SparkASin(SparkScalar value) { return asinf(value); }

SPARKAPI SparkScalar SparkACos(SparkScalar value) { return acosf(value); }

SPARKAPI SparkScalar SparkATan(SparkScalar value) { return atanf(value); }

SPARKAPI SparkScalar SparkATan2(SparkScalar y, SparkScalar x) {
	return atan2f(y, x);
}

/* SparkVec2 functions */
SPARKAPI SparkVec2 SparkVec2Add(SparkVec2 a, SparkVec2 b) {
	SparkVec2 result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return result;
}

SPARKAPI SparkVec2 SparkVec2Subtract(SparkVec2 a, SparkVec2 b) {
	SparkVec2 result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return result;
}

SPARKAPI SparkVec2 SparkVec2Multiply(SparkVec2 a, SparkVec2 b) {
	SparkVec2 result;
	result.x = a.x * b.x;
	result.y = a.y * b.y;
	return result;
}

SPARKAPI SparkVec2 SparkVec2Divide(SparkVec2 a, SparkVec2 b) {
	SparkVec2 result;
	result.x = a.x / b.x;
	result.y = a.y / b.y;
	return result;
}

SPARKAPI SparkVec2 SparkVec2Scale(SparkVec2 a, SparkScalar s) {
	SparkVec2 result;
	result.x = a.x * s;
	result.y = a.y * s;
	return result;
}

SPARKAPI SparkScalar SparkVec2Dot(SparkVec2 a, SparkVec2 b) {
	return a.x * b.x + a.y * b.y;
}

SPARKAPI SparkScalar SparkVec2Length(SparkVec2 a) {
	return SparkSqrt(a.x * a.x + a.y * a.y);
}

SPARKAPI SparkVec2 SparkVec2Normalize(SparkVec2 a) {
	SparkScalar length = SparkVec2Length(a);
	SparkVec2 result;
	if (length != 0) {
		result.x = a.x / length;
		result.y = a.y / length;
	}
	else {
		result.x = 0.0f;
		result.y = 0.0f;
	}
	return result;
}

SPARKAPI SparkScalar SparkVec2Distance(SparkVec2 a, SparkVec2 b) {
	SparkScalar dx = a.x - b.x;
	SparkScalar dy = a.y - b.y;
	return SparkSqrt(dx * dx + dy * dy);
}

SPARKAPI SparkVec2 SparkVec2Negate(SparkVec2 a) {
	SparkVec2 result;
	result.x = -a.x;
	result.y = -a.y;
	return result;
}

SPARKAPI SparkScalar SparkVec2Angle(SparkVec2 a, SparkVec2 b) {
	SparkScalar dot = SparkVec2Dot(a, b);
	SparkScalar lenA = SparkVec2Length(a);
	SparkScalar lenB = SparkVec2Length(b);
	if (lenA == 0 || lenB == 0) {
		return 0.0f;
	}
	SparkScalar cosTheta = dot / (lenA * lenB);
	cosTheta = SparkClampS(cosTheta, -1.0f, 1.0f);
	return SparkACos(cosTheta);
}

SPARKAPI SparkVec2 SparkVec2Reflect(SparkVec2 v, SparkVec2 n) {
	SparkScalar dotVN = SparkVec2Dot(v, n);
	SparkVec2 result;
	result.x = v.x - 2 * dotVN * n.x;
	result.y = v.y - 2 * dotVN * n.y;
	return result;
}

SPARKAPI SparkVec2 SparkVec2Lerp(SparkVec2 a, SparkVec2 b, SparkScalar t) {
	SparkVec2 result;
	result.x = a.x + t * (b.x - a.x);
	result.y = a.y + t * (b.y - a.y);
	return result;
}

/* SparkVec3 functions */
SPARKAPI SparkVec3 SparkVec3Add(SparkVec3 a, SparkVec3 b) {
	SparkVec3 result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return result;
}

SPARKAPI SparkVec3 SparkVec3Subtract(SparkVec3 a, SparkVec3 b) {
	SparkVec3 result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return result;
}

SPARKAPI SparkVec3 SparkVec3Multiply(SparkVec3 a, SparkVec3 b) {
	SparkVec3 result;
	result.x = a.x * b.x;
	result.y = a.y * b.y;
	result.z = a.z * b.z;
	return result;
}

SPARKAPI SparkVec3 SparkVec3Divide(SparkVec3 a, SparkVec3 b) {
	SparkVec3 result;
	result.x = a.x / b.x;
	result.y = a.y / b.y;
	result.z = a.z / b.z;
	return result;
}

SPARKAPI SparkVec3 SparkVec3Scale(SparkVec3 a, SparkScalar s) {
	SparkVec3 result;
	result.x = a.x * s;
	result.y = a.y * s;
	result.z = a.z * s;
	return result;
}

SPARKAPI SparkScalar SparkVec3Dot(SparkVec3 a, SparkVec3 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

SPARKAPI SparkVec3 SparkVec3Cross(SparkVec3 a, SparkVec3 b) {
	SparkVec3 result;
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return result;
}

SPARKAPI SparkScalar SparkVec3Length(SparkVec3 a) {
	return SparkSqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

SPARKAPI SparkVec3 SparkVec3Normalize(SparkVec3 a) {
	SparkScalar length = SparkVec3Length(a);
	SparkVec3 result;
	if (length != 0) {
		result.x = a.x / length;
		result.y = a.y / length;
		result.z = a.z / length;
	}
	else {
		result.x = 0.0f;
		result.y = 0.0f;
		result.z = 0.0f;
	}
	return result;
}

SPARKAPI SparkScalar SparkVec3Distance(SparkVec3 a, SparkVec3 b) {
	SparkScalar dx = a.x - b.x;
	SparkScalar dy = a.y - b.y;
	SparkScalar dz = a.z - b.z;
	return SparkSqrt(dx * dx + dy * dy + dz * dz);
}

SPARKAPI SparkVec3 SparkVec3Negate(SparkVec3 a) {
	SparkVec3 result;
	result.x = -a.x;
	result.y = -a.y;
	result.z = -a.z;
	return result;
}

SPARKAPI SparkScalar SparkVec3Angle(SparkVec3 a, SparkVec3 b) {
	SparkScalar dot = SparkVec3Dot(a, b);
	SparkScalar lenA = SparkVec3Length(a);
	SparkScalar lenB = SparkVec3Length(b);
	if (lenA == 0 || lenB == 0) {
		return 0.0f;
	}
	SparkScalar cosTheta = dot / (lenA * lenB);
	cosTheta = SparkClampS(cosTheta, -1.0f, 1.0f);
	return SparkACos(cosTheta);
}

SPARKAPI SparkVec3 SparkVec3Reflect(SparkVec3 v, SparkVec3 n) {
	SparkScalar dotVN = SparkVec3Dot(v, n);
	SparkVec3 result;
	result.x = v.x - 2 * dotVN * n.x;
	result.y = v.y - 2 * dotVN * n.y;
	result.z = v.z - 2 * dotVN * n.z;
	return result;
}

SPARKAPI SparkVec3 SparkVec3Lerp(SparkVec3 a, SparkVec3 b, SparkScalar t) {
	SparkVec3 result;
	result.x = a.x + t * (b.x - a.x);
	result.y = a.y + t * (b.y - a.y);
	result.z = a.z + t * (b.z - a.z);
	return result;
}

/* SparkVec4 functions */
SPARKAPI SparkVec4 SparkVec4Add(SparkVec4 a, SparkVec4 b) {
	SparkVec4 result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	result.w = a.w + b.w;
	return result;
}

SPARKAPI SparkVec4 SparkVec4Subtract(SparkVec4 a, SparkVec4 b) {
	SparkVec4 result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	result.w = a.w - b.w;
	return result;
}

SPARKAPI SparkVec4 SparkVec4Multiply(SparkVec4 a, SparkVec4 b) {
	SparkVec4 result;
	result.x = a.x * b.x;
	result.y = a.y * b.y;
	result.z = a.z * b.z;
	result.w = a.w * b.w;
	return result;
}

SPARKAPI SparkVec4 SparkVec4Divide(SparkVec4 a, SparkVec4 b) {
	SparkVec4 result;
	result.x = a.x / b.x;
	result.y = a.y / b.y;
	result.z = a.z / b.z;
	result.w = a.w / b.w;
	return result;
}

SPARKAPI SparkVec4 SparkVec4Scale(SparkVec4 a, SparkScalar s) {
	SparkVec4 result;
	result.x = a.x * s;
	result.y = a.y * s;
	result.z = a.z * s;
	result.w = a.w * s;
	return result;
}

SPARKAPI SparkScalar SparkVec4Dot(SparkVec4 a, SparkVec4 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

SPARKAPI SparkScalar SparkVec4Length(SparkVec4 a) {
	return SparkSqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
}

SPARKAPI SparkVec4 SparkVec4Normalize(SparkVec4 a) {
	SparkScalar length = SparkVec4Length(a);
	SparkVec4 result;
	if (length != 0) {
		result.x = a.x / length;
		result.y = a.y / length;
		result.z = a.z / length;
		result.w = a.w / length;
	}
	else {
		result.x = 0.0f;
		result.y = 0.0f;
		result.z = 0.0f;
		result.w = 0.0f;
	}
	return result;
}

SPARKAPI SparkScalar SparkVec4Distance(SparkVec4 a, SparkVec4 b) {
	SparkScalar dx = a.x - b.x;
	SparkScalar dy = a.y - b.y;
	SparkScalar dz = a.z - b.z;
	SparkScalar dw = a.w - b.w;
	return SparkSqrt(dx * dx + dy * dy + dz * dz + dw * dw);
}

SPARKAPI SparkVec4 SparkVec4Negate(SparkVec4 a) {
	SparkVec4 result;
	result.x = -a.x;
	result.y = -a.y;
	result.z = -a.z;
	result.w = -a.w;
	return result;
}

SPARKAPI SparkVec4 SparkVec4Lerp(SparkVec4 a, SparkVec4 b, SparkScalar t) {
	SparkVec4 result;
	result.x = a.x + t * (b.x - a.x);
	result.y = a.y + t * (b.y - a.y);
	result.z = a.z + t * (b.z - a.z);
	result.w = a.w + t * (b.w - a.w);
	return result;
}

/* Matrix functions */

/* SparkMat2 functions */
SPARKAPI SparkMat2 SparkMat2Add(SparkMat2 a, SparkMat2 b) {
	SparkMat2 result;
	result.m00 = a.m00 + b.m00;
	result.m01 = a.m01 + b.m01;
	result.m10 = a.m10 + b.m10;
	result.m11 = a.m11 + b.m11;
	return result;
}

SPARKAPI SparkMat2 SparkMat2Subtract(SparkMat2 a, SparkMat2 b) {
	SparkMat2 result;
	result.m00 = a.m00 - b.m00;
	result.m01 = a.m01 - b.m01;
	result.m10 = a.m10 - b.m10;
	result.m11 = a.m11 - b.m11;
	return result;
}

SPARKAPI SparkMat2 SparkMat2Multiply(SparkMat2 a, SparkMat2 b) {
	SparkMat2 result;
	result.m00 = a.m00 * b.m00 + a.m01 * b.m10;
	result.m01 = a.m00 * b.m01 + a.m01 * b.m11;
	result.m10 = a.m10 * b.m00 + a.m11 * b.m10;
	result.m11 = a.m10 * b.m01 + a.m11 * b.m11;
	return result;
}

SPARKAPI SparkMat2 SparkMat2Scale(SparkMat2 m, SparkScalar s) {
	SparkMat2 result;
	result.m00 = m.m00 * s;
	result.m01 = m.m01 * s;
	result.m10 = m.m10 * s;
	result.m11 = m.m11 * s;
	return result;
}

SPARKAPI SparkMat2 SparkMat2Transpose(SparkMat2 m) {
	SparkMat2 result;
	result.m00 = m.m00;
	result.m01 = m.m10;
	result.m10 = m.m01;
	result.m11 = m.m11;
	return result;
}

SPARKAPI SparkScalar SparkMat2Determinant(SparkMat2 m) {
	return m.m00 * m.m11 - m.m01 * m.m10;
}

SPARKAPI SparkMat2 SparkMat2Inverse(SparkMat2 m) {
	SparkScalar det = SparkMat2Determinant(m);
	SparkMat2 result;
	if (det != 0) {
		SparkScalar invDet = 1.0f / det;
		result.m00 = m.m11 * invDet;
		result.m01 = -m.m01 * invDet;
		result.m10 = -m.m10 * invDet;
		result.m11 = m.m00 * invDet;
	}
	else {
		// Matrix is not invertible, return zero matrix
		result.m00 = result.m01 = result.m10 = result.m11 = 0.0f;
	}
	return result;
}

SPARKAPI SparkMat2 SparkMat2Identity() {
	SparkMat2 result;
	result.m00 = 1.0f;
	result.m01 = 0.0f;
	result.m10 = 0.0f;
	result.m11 = 1.0f;
	return result;
}

/* SparkMat3 functions */
SPARKAPI SparkMat3 SparkMat3Add(SparkMat3 a, SparkMat3 b) {
	SparkMat3 result;
	result.m00 = a.m00 + b.m00;
	result.m01 = a.m01 + b.m01;
	result.m02 = a.m02 + b.m02;
	result.m10 = a.m10 + b.m10;
	result.m11 = a.m11 + b.m11;
	result.m12 = a.m12 + b.m12;
	result.m20 = a.m20 + b.m20;
	result.m21 = a.m21 + b.m21;
	result.m22 = a.m22 + b.m22;
	return result;
}

SPARKAPI SparkMat3 SparkMat3Subtract(SparkMat3 a, SparkMat3 b) {
	SparkMat3 result;
	result.m00 = a.m00 - b.m00;
	result.m01 = a.m01 - b.m01;
	result.m02 = a.m02 - b.m02;
	result.m10 = a.m10 - b.m10;
	result.m11 = a.m11 - b.m11;
	result.m12 = a.m12 - b.m12;
	result.m20 = a.m20 - b.m20;
	result.m21 = a.m21 - b.m21;
	result.m22 = a.m22 - b.m22;
	return result;
}

SPARKAPI SparkMat3 SparkMat3Multiply(SparkMat3 a, SparkMat3 b) {
	SparkMat3 result;
	result.m00 = a.m00 * b.m00 + a.m01 * b.m10 + a.m02 * b.m20;
	result.m01 = a.m00 * b.m01 + a.m01 * b.m11 + a.m02 * b.m21;
	result.m02 = a.m00 * b.m02 + a.m01 * b.m12 + a.m02 * b.m22;

	result.m10 = a.m10 * b.m00 + a.m11 * b.m10 + a.m12 * b.m20;
	result.m11 = a.m10 * b.m01 + a.m11 * b.m11 + a.m12 * b.m21;
	result.m12 = a.m10 * b.m02 + a.m11 * b.m12 + a.m12 * b.m22;

	result.m20 = a.m20 * b.m00 + a.m21 * b.m10 + a.m22 * b.m20;
	result.m21 = a.m20 * b.m01 + a.m21 * b.m11 + a.m22 * b.m21;
	result.m22 = a.m20 * b.m02 + a.m21 * b.m12 + a.m22 * b.m22;
	return result;
}

SPARKAPI SparkMat3 SparkMat3Scale(SparkMat3 m, SparkScalar s) {
	SparkMat3 result;
	result.m00 = m.m00 * s;
	result.m01 = m.m01 * s;
	result.m02 = m.m02 * s;
	result.m10 = m.m10 * s;
	result.m11 = m.m11 * s;
	result.m12 = m.m12 * s;
	result.m20 = m.m20 * s;
	result.m21 = m.m21 * s;
	result.m22 = m.m22 * s;
	return result;
}

SPARKAPI SparkMat3 SparkMat3Transpose(SparkMat3 m) {
	SparkMat3 result;
	result.m00 = m.m00;
	result.m01 = m.m10;
	result.m02 = m.m20;
	result.m10 = m.m01;
	result.m11 = m.m11;
	result.m12 = m.m21;
	result.m20 = m.m02;
	result.m21 = m.m12;
	result.m22 = m.m22;
	return result;
}

SPARKAPI SparkScalar SparkMat3Determinant(SparkMat3 m) {
	SparkScalar det = m.m00 * (m.m11 * m.m22 - m.m12 * m.m21) -
		m.m01 * (m.m10 * m.m22 - m.m12 * m.m20) +
		m.m02 * (m.m10 * m.m21 - m.m11 * m.m20);
	return det;
}

SPARKAPI SparkMat3 SparkMat3Inverse(SparkMat3 m) {
	SparkScalar det = SparkMat3Determinant(m);
	SparkMat3 result;
	if (det != 0) {
		SparkScalar invDet = 1.0f / det;

		result.m00 = (m.m11 * m.m22 - m.m12 * m.m21) * invDet;
		result.m01 = (m.m02 * m.m21 - m.m01 * m.m22) * invDet;
		result.m02 = (m.m01 * m.m12 - m.m02 * m.m11) * invDet;

		result.m10 = (m.m12 * m.m20 - m.m10 * m.m22) * invDet;
		result.m11 = (m.m00 * m.m22 - m.m02 * m.m20) * invDet;
		result.m12 = (m.m02 * m.m10 - m.m00 * m.m12) * invDet;

		result.m20 = (m.m10 * m.m21 - m.m11 * m.m20) * invDet;
		result.m21 = (m.m01 * m.m20 - m.m00 * m.m21) * invDet;
		result.m22 = (m.m00 * m.m11 - m.m01 * m.m10) * invDet;
	}
	else {
		// Matrix is not invertible, return zero matrix
		result.m00 = result.m01 = result.m02 = 0.0f;
		result.m10 = result.m11 = result.m12 = 0.0f;
		result.m20 = result.m21 = result.m22 = 0.0f;
	}
	return result;
}

SPARKAPI SparkMat3 SparkMat3Identity() {
	SparkMat3 result;
	result.m00 = 1.0f;
	result.m01 = 0.0f;
	result.m02 = 0.0f;
	result.m10 = 0.0f;
	result.m11 = 1.0f;
	result.m12 = 0.0f;
	result.m20 = 0.0f;
	result.m21 = 0.0f;
	result.m22 = 1.0f;
	return result;
}

/* SparkMat4 functions */
SPARKAPI SparkMat4 SparkMat4Add(SparkMat4 a, SparkMat4 b) {
	SparkMat4 result;
	result.m00 = a.m00 + b.m00;
	result.m01 = a.m01 + b.m01;
	result.m02 = a.m02 + b.m02;
	result.m03 = a.m03 + b.m03;
	result.m10 = a.m10 + b.m10;
	result.m11 = a.m11 + b.m11;
	result.m12 = a.m12 + b.m12;
	result.m13 = a.m13 + b.m13;
	result.m20 = a.m20 + b.m20;
	result.m21 = a.m21 + b.m21;
	result.m22 = a.m22 + b.m22;
	result.m23 = a.m23 + b.m23;
	result.m30 = a.m30 + b.m30;
	result.m31 = a.m31 + b.m31;
	result.m32 = a.m32 + b.m32;
	result.m33 = a.m33 + b.m33;
	return result;
}

SPARKAPI SparkMat4 SparkMat4Subtract(SparkMat4 a, SparkMat4 b) {
	SparkMat4 result;
	result.m00 = a.m00 - b.m00;
	result.m01 = a.m01 - b.m01;
	result.m02 = a.m02 - b.m02;
	result.m03 = a.m03 - b.m03;
	result.m10 = a.m10 - b.m10;
	result.m11 = a.m11 - b.m11;
	result.m12 = a.m12 - b.m12;
	result.m13 = a.m13 - b.m13;
	result.m20 = a.m20 - b.m20;
	result.m21 = a.m21 - b.m21;
	result.m22 = a.m22 - b.m22;
	result.m23 = a.m23 - b.m23;
	result.m30 = a.m30 - b.m30;
	result.m31 = a.m31 - b.m31;
	result.m32 = a.m32 - b.m32;
	result.m33 = a.m33 - b.m33;
	return result;
}

SPARKAPI SparkMat4 SparkMat4Multiply(SparkMat4 a, SparkMat4 b) {
	SparkMat4 result;
	result.m00 = a.m00 * b.m00 + a.m01 * b.m10 + a.m02 * b.m20 + a.m03 * b.m30;
	result.m01 = a.m00 * b.m01 + a.m01 * b.m11 + a.m02 * b.m21 + a.m03 * b.m31;
	result.m02 = a.m00 * b.m02 + a.m01 * b.m12 + a.m02 * b.m22 + a.m03 * b.m32;
	result.m03 = a.m00 * b.m03 + a.m01 * b.m13 + a.m02 * b.m23 + a.m03 * b.m33;

	result.m10 = a.m10 * b.m00 + a.m11 * b.m10 + a.m12 * b.m20 + a.m13 * b.m30;
	result.m11 = a.m10 * b.m01 + a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31;
	result.m12 = a.m10 * b.m02 + a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32;
	result.m13 = a.m10 * b.m03 + a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33;

	result.m20 = a.m20 * b.m00 + a.m21 * b.m10 + a.m22 * b.m20 + a.m23 * b.m30;
	result.m21 = a.m20 * b.m01 + a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31;
	result.m22 = a.m20 * b.m02 + a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32;
	result.m23 = a.m20 * b.m03 + a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33;

	result.m30 = a.m30 * b.m00 + a.m31 * b.m10 + a.m32 * b.m20 + a.m33 * b.m30;
	result.m31 = a.m30 * b.m01 + a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31;
	result.m32 = a.m30 * b.m02 + a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32;
	result.m33 = a.m30 * b.m03 + a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33;
	return result;
}

SPARKAPI SparkMat4 SparkMat4Scale(SparkMat4 m, SparkScalar s) {
	SparkMat4 result;
	result.m00 = m.m00 * s;
	result.m01 = m.m01 * s;
	result.m02 = m.m02 * s;
	result.m03 = m.m03 * s;
	result.m10 = m.m10 * s;
	result.m11 = m.m11 * s;
	result.m12 = m.m12 * s;
	result.m13 = m.m13 * s;
	result.m20 = m.m20 * s;
	result.m21 = m.m21 * s;
	result.m22 = m.m22 * s;
	result.m23 = m.m23 * s;
	result.m30 = m.m30 * s;
	result.m31 = m.m31 * s;
	result.m32 = m.m32 * s;
	result.m33 = m.m33 * s;
	return result;
}

SPARKAPI SparkMat4 SparkMat4Transpose(SparkMat4 m) {
	SparkMat4 result;
	result.m00 = m.m00;
	result.m01 = m.m10;
	result.m02 = m.m20;
	result.m03 = m.m30;
	result.m10 = m.m01;
	result.m11 = m.m11;
	result.m12 = m.m21;
	result.m13 = m.m31;
	result.m20 = m.m02;
	result.m21 = m.m12;
	result.m22 = m.m22;
	result.m23 = m.m32;
	result.m30 = m.m03;
	result.m31 = m.m13;
	result.m32 = m.m23;
	result.m33 = m.m33;
	return result;
}

SPARKAPI SparkScalar SparkMat4Determinant(SparkMat4 m) {
	// Compute the determinant of a 4x4 matrix using Laplace expansion
	SparkScalar det;

	SparkScalar a0 = m.m00 * m.m11 - m.m01 * m.m10;
	SparkScalar a1 = m.m00 * m.m12 - m.m02 * m.m10;
	SparkScalar a2 = m.m00 * m.m13 - m.m03 * m.m10;
	SparkScalar a3 = m.m01 * m.m12 - m.m02 * m.m11;
	SparkScalar a4 = m.m01 * m.m13 - m.m03 * m.m11;
	SparkScalar a5 = m.m02 * m.m13 - m.m03 * m.m12;
	SparkScalar b0 = m.m20 * m.m31 - m.m21 * m.m30;
	SparkScalar b1 = m.m20 * m.m32 - m.m22 * m.m30;
	SparkScalar b2 = m.m20 * m.m33 - m.m23 * m.m30;
	SparkScalar b3 = m.m21 * m.m32 - m.m22 * m.m31;
	SparkScalar b4 = m.m21 * m.m33 - m.m23 * m.m31;
	SparkScalar b5 = m.m22 * m.m33 - m.m23 * m.m32;

	det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;
	return det;
}

SPARKAPI SparkMat4 SparkMat4Inverse(SparkMat4 m) {
	SparkScalar det = SparkMat4Determinant(m);
	SparkMat4 result;

	if (det == 0.0f) {
		// Matrix is not invertible, return zero matrix
		result = (SparkMat4){ 0 };
		return result;
	}

	SparkScalar invDet = 1.0f / det;

	// Compute the cofactors of each element
	result.m00 = (m.m11 * (m.m22 * m.m33 - m.m23 * m.m32) -
		m.m12 * (m.m21 * m.m33 - m.m23 * m.m31) +
		m.m13 * (m.m21 * m.m32 - m.m22 * m.m31)) *
		invDet;
	result.m01 = -(m.m01 * (m.m22 * m.m33 - m.m23 * m.m32) -
		m.m02 * (m.m21 * m.m33 - m.m23 * m.m31) +
		m.m03 * (m.m21 * m.m32 - m.m22 * m.m31)) *
		invDet;
	result.m02 = (m.m01 * (m.m12 * m.m33 - m.m13 * m.m32) -
		m.m02 * (m.m11 * m.m33 - m.m13 * m.m31) +
		m.m03 * (m.m11 * m.m32 - m.m12 * m.m31)) *
		invDet;
	result.m03 = -(m.m01 * (m.m12 * m.m23 - m.m13 * m.m22) -
		m.m02 * (m.m11 * m.m23 - m.m13 * m.m21) +
		m.m03 * (m.m11 * m.m22 - m.m12 * m.m21)) *
		invDet;

	result.m10 = -(m.m10 * (m.m22 * m.m33 - m.m23 * m.m32) -
		m.m12 * (m.m20 * m.m33 - m.m23 * m.m30) +
		m.m13 * (m.m20 * m.m32 - m.m22 * m.m30)) *
		invDet;
	result.m11 = (m.m00 * (m.m22 * m.m33 - m.m23 * m.m32) -
		m.m02 * (m.m20 * m.m33 - m.m23 * m.m30) +
		m.m03 * (m.m20 * m.m32 - m.m22 * m.m30)) *
		invDet;
	result.m12 = -(m.m00 * (m.m12 * m.m33 - m.m13 * m.m32) -
		m.m02 * (m.m10 * m.m33 - m.m13 * m.m30) +
		m.m03 * (m.m10 * m.m32 - m.m12 * m.m30)) *
		invDet;
	result.m13 = (m.m00 * (m.m12 * m.m23 - m.m13 * m.m22) -
		m.m02 * (m.m10 * m.m23 - m.m13 * m.m20) +
		m.m03 * (m.m10 * m.m22 - m.m12 * m.m20)) *
		invDet;

	result.m20 = (m.m10 * (m.m21 * m.m33 - m.m23 * m.m31) -
		m.m11 * (m.m20 * m.m33 - m.m23 * m.m30) +
		m.m13 * (m.m20 * m.m31 - m.m21 * m.m30)) *
		invDet;
	result.m21 = -(m.m00 * (m.m21 * m.m33 - m.m23 * m.m31) -
		m.m01 * (m.m20 * m.m33 - m.m23 * m.m30) +
		m.m03 * (m.m20 * m.m31 - m.m21 * m.m30)) *
		invDet;
	result.m22 = (m.m00 * (m.m11 * m.m33 - m.m13 * m.m31) -
		m.m01 * (m.m10 * m.m33 - m.m13 * m.m30) +
		m.m03 * (m.m10 * m.m31 - m.m11 * m.m30)) *
		invDet;
	result.m23 = -(m.m00 * (m.m11 * m.m23 - m.m13 * m.m21) -
		m.m01 * (m.m10 * m.m23 - m.m13 * m.m20) +
		m.m03 * (m.m10 * m.m21 - m.m11 * m.m20)) *
		invDet;

	result.m30 = -(m.m10 * (m.m21 * m.m32 - m.m22 * m.m31) -
		m.m11 * (m.m20 * m.m32 - m.m22 * m.m30) +
		m.m12 * (m.m20 * m.m31 - m.m21 * m.m30)) *
		invDet;
	result.m31 = (m.m00 * (m.m21 * m.m32 - m.m22 * m.m31) -
		m.m01 * (m.m20 * m.m32 - m.m22 * m.m30) +
		m.m02 * (m.m20 * m.m31 - m.m21 * m.m30)) *
		invDet;
	result.m32 = -(m.m00 * (m.m11 * m.m32 - m.m12 * m.m31) -
		m.m01 * (m.m10 * m.m32 - m.m12 * m.m30) +
		m.m02 * (m.m10 * m.m31 - m.m11 * m.m30)) *
		invDet;
	result.m33 = (m.m00 * (m.m11 * m.m22 - m.m12 * m.m21) -
		m.m01 * (m.m10 * m.m22 - m.m12 * m.m20) +
		m.m02 * (m.m10 * m.m21 - m.m11 * m.m20)) *
		invDet;

	return result;
}

SPARKAPI SparkMat4 SparkMat4Identity() {
	SparkMat4 result = { 0 };
	result.m00 = 1.0f;
	result.m11 = 1.0f;
	result.m22 = 1.0f;
	result.m33 = 1.0f;
	return result;
}

SPARKAPI SparkMat4 SparkMat4Translate(SparkVec3 translation) {
	SparkMat4 result = SparkMat4Identity();
	result.m03 = translation.x;
	result.m13 = translation.y;
	result.m23 = translation.z;
	return result;
}

SPARKAPI SparkMat4 SparkMat4ScaleVec3(SparkVec3 scale) {
	SparkMat4 result = SparkMat4Identity();
	result.m00 = scale.x;
	result.m11 = scale.y;
	result.m22 = scale.z;
	return result;
}

SPARKAPI SparkMat4 SparkMat4ScaleScalar(SparkScalar scale) {
	SparkMat4 result = SparkMat4Identity();
	result.m00 = scale;
	result.m11 = scale;
	result.m22 = scale;
	return result;
}

SPARKAPI SparkMat4 SparkMat4Rotate(SparkScalar angle, SparkVec3 axis) {
	SparkMat4 result = { 0 };
	SparkScalar c = SparkCos(angle);
	SparkScalar s = SparkSin(angle);
	SparkScalar one_c = 1.0f - c;

	axis = SparkVec3Normalize(axis);

	result.m00 = c + axis.x * axis.x * one_c;
	result.m01 = axis.x * axis.y * one_c - axis.z * s;
	result.m02 = axis.x * axis.z * one_c + axis.y * s;
	result.m10 = axis.y * axis.x * one_c + axis.z * s;
	result.m11 = c + axis.y * axis.y * one_c;
	result.m12 = axis.y * axis.z * one_c - axis.x * s;
	result.m20 = axis.z * axis.x * one_c - axis.y * s;
	result.m21 = axis.z * axis.y * one_c + axis.x * s;
	result.m22 = c + axis.z * axis.z * one_c;
	result.m33 = 1.0f;
	return result;
}

SPARKAPI SparkMat4 SparkMat4RotateX(SparkScalar angle) {
	SparkMat4 result = SparkMat4Identity();
	SparkScalar c = SparkCos(angle);
	SparkScalar s = SparkSin(angle);

	result.m11 = c;
	result.m12 = -s;
	result.m21 = s;
	result.m22 = c;
	return result;
}

SPARKAPI SparkMat4 SparkMat4RotateY(SparkScalar angle) {
	SparkMat4 result = SparkMat4Identity();
	SparkScalar c = SparkCos(angle);
	SparkScalar s = SparkSin(angle);

	result.m00 = c;
	result.m02 = s;
	result.m20 = -s;
	result.m22 = c;
	return result;
}

SPARKAPI SparkMat4 SparkMat4RotateZ(SparkScalar angle) {
	SparkMat4 result = SparkMat4Identity();
	SparkScalar c = SparkCos(angle);
	SparkScalar s = SparkSin(angle);

	result.m00 = c;
	result.m01 = -s;
	result.m10 = s;
	result.m11 = c;
	return result;
}

SPARKAPI SparkMat4 SparkMat4LookAt(SparkVec3 eye, SparkVec3 center,
	SparkVec3 up) {
	SparkVec3 f = SparkVec3Normalize(SparkVec3Subtract(center, eye));
	SparkVec3 s = SparkVec3Normalize(SparkVec3Cross(f, up));
	SparkVec3 u = SparkVec3Cross(s, f);

	SparkMat4 result = SparkMat4Identity();
	result.m00 = s.x;
	result.m01 = s.y;
	result.m02 = s.z;
	result.m10 = u.x;
	result.m11 = u.y;
	result.m12 = u.z;
	result.m20 = -f.x;
	result.m21 = -f.y;
	result.m22 = -f.z;
	result.m03 = -SparkVec3Dot(s, eye);
	result.m13 = -SparkVec3Dot(u, eye);
	result.m23 = SparkVec3Dot(f, eye);
	return result;
}

SPARKAPI SparkMat4 SparkMat4Perspective(SparkScalar fovy, SparkScalar aspect,
	SparkScalar near, SparkScalar far) {
	SparkScalar f = 1.0f / SparkTan(fovy / 2.0f);
	SparkMat4 result = { 0 };
	result.m00 = f / aspect;
	result.m11 = f;
	result.m22 = (far + near) / (near - far);
	result.m23 = (2.0f * far * near) / (near - far);
	result.m32 = -1.0f;
	return result;
}

SPARKAPI SparkMat4 SparkMat4Ortho(SparkScalar left, SparkScalar right,
	SparkScalar bottom, SparkScalar top,
	SparkScalar near, SparkScalar far) {
	SparkMat4 result = { 0 };
	result.m00 = 2.0f / (right - left);
	result.m11 = 2.0f / (top - bottom);
	result.m22 = -2.0f / (far - near);
	result.m03 = -(right + left) / (right - left);
	result.m13 = -(top + bottom) / (top - bottom);
	result.m23 = -(far + near) / (far - near);
	result.m33 = 1.0f;
	return result;
}

/* Vector transformations */
SPARKAPI SparkVec3 SparkMat4MultiplyVec3(SparkMat4 m, SparkVec3 v) {
	SparkVec3 result;
	result.x = m.m00 * v.x + m.m01 * v.y + m.m02 * v.z + m.m03;
	result.y = m.m10 * v.x + m.m11 * v.y + m.m12 * v.z + m.m13;
	result.z = m.m20 * v.x + m.m21 * v.y + m.m22 * v.z + m.m23;
	return result;
}

SPARKAPI SparkVec4 SparkMat4MultiplyVec4(SparkMat4 m, SparkVec4 v) {
	SparkVec4 result;
	result.x = m.m00 * v.x + m.m01 * v.y + m.m02 * v.z + m.m03 * v.w;
	result.y = m.m10 * v.x + m.m11 * v.y + m.m12 * v.z + m.m13 * v.w;
	result.z = m.m20 * v.x + m.m21 * v.y + m.m22 * v.z + m.m23 * v.w;
	result.w = m.m30 * v.x + m.m31 * v.y + m.m32 * v.z + m.m33 * v.w;
	return result;
}

/* Quaternion functions */
SPARKAPI SparkQuat SparkQuatMultiply(SparkQuat a, SparkQuat b) {
	SparkQuat result;
	result.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
	result.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
	result.y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x;
	result.z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w;
	return result;
}

SPARKAPI SparkQuat SparkQuatConjugate(SparkQuat q) {
	SparkQuat result;
	result.w = q.w;
	result.x = -q.x;
	result.y = -q.y;
	result.z = -q.z;
	return result;
}

SPARKAPI SparkQuat SparkQuatInverse(SparkQuat q) {
	SparkScalar norm = q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z;
	if (norm > 0.0f) {
		SparkScalar invNorm = 1.0f / norm;
		SparkQuat conjugate = SparkQuatConjugate(q);
		SparkQuat result;
		result.w = conjugate.w * invNorm;
		result.x = conjugate.x * invNorm;
		result.y = conjugate.y * invNorm;
		result.z = conjugate.z * invNorm;
		return result;
	}
	else {
		// Return zero quaternion
		return (SparkQuat) { 0 };
	}
}

SPARKAPI SparkQuat SparkQuatNormalize(SparkQuat q) {
	SparkScalar length = SparkSqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
	if (length != 0) {
		SparkScalar invLength = 1.0f / length;
		SparkQuat result;
		result.w = q.w * invLength;
		result.x = q.x * invLength;
		result.y = q.y * invLength;
		result.z = q.z * invLength;
		return result;
	}
	else {
		return (SparkQuat) { 0 };
	}
}

SPARKAPI SparkQuat SparkQuatFromAxisAngle(SparkVec3 axis, SparkScalar angle) {
	SparkQuat result;
	SparkScalar halfAngle = angle / 2.0f;
	SparkScalar s = SparkSin(halfAngle);
	result.w = SparkCos(halfAngle);
	result.x = axis.x * s;
	result.y = axis.y * s;
	result.z = axis.z * s;
	return result;
}

SPARKAPI SparkVoid SparkQuatToAxisAngle(SparkQuat q, SparkVec3* axis,
	SparkScalar* angle) {
	if (q.w > 1.0f)
		q = SparkQuatNormalize(q);
	*angle = 2.0f * SparkACos(q.w);
	SparkScalar s = SparkSqrt(1.0f - q.w * q.w);
	if (s < 0.001f) {
		axis->x = q.x;
		axis->y = q.y;
		axis->z = q.z;
	}
	else {
		axis->x = q.x / s;
		axis->y = q.y / s;
		axis->z = q.z / s;
	}
}

SPARKAPI SparkMat4 SparkQuatToMat4(SparkQuat q) {
	SparkMat4 result = SparkMat4Identity();
	SparkScalar xx = q.x * q.x;
	SparkScalar yy = q.y * q.y;
	SparkScalar zz = q.z * q.z;
	SparkScalar xy = q.x * q.y;
	SparkScalar xz = q.x * q.z;
	SparkScalar yz = q.y * q.z;
	SparkScalar wx = q.w * q.x;
	SparkScalar wy = q.w * q.y;
	SparkScalar wz = q.w * q.z;

	result.m00 = 1.0f - 2.0f * (yy + zz);
	result.m01 = 2.0f * (xy - wz);
	result.m02 = 2.0f * (xz + wy);

	result.m10 = 2.0f * (xy + wz);
	result.m11 = 1.0f - 2.0f * (xx + zz);
	result.m12 = 2.0f * (yz - wx);

	result.m20 = 2.0f * (xz - wy);
	result.m21 = 2.0f * (yz + wx);
	result.m22 = 1.0f - 2.0f * (xx + yy);
	return result;
}

SPARKAPI SparkQuat SparkQuatSlerp(SparkQuat a, SparkQuat b, SparkScalar t) {
	SparkQuat result;
	SparkScalar cosHalfTheta = a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
	if (fabsf(cosHalfTheta) >= 1.0f) {
		result = a;
		return result;
	}
	SparkScalar halfTheta = SparkACos(cosHalfTheta);
	SparkScalar sinHalfTheta = SparkSqrt(1.0f - cosHalfTheta * cosHalfTheta);
	if (fabsf(sinHalfTheta) < 0.001f) {
		result.w = (a.w * 0.5f + b.w * 0.5f);
		result.x = (a.x * 0.5f + b.x * 0.5f);
		result.y = (a.y * 0.5f + b.y * 0.5f);
		result.z = (a.z * 0.5f + b.z * 0.5f);
		return result;
	}
	SparkScalar ratioA = SparkSin((1 - t) * halfTheta) / sinHalfTheta;
	SparkScalar ratioB = SparkSin(t * halfTheta) / sinHalfTheta;
	result.w = a.w * ratioA + b.w * ratioB;
	result.x = a.x * ratioA + b.x * ratioB;
	result.y = a.y * ratioA + b.y * ratioB;
	result.z = a.z * ratioA + b.z * ratioB;
	return result;
}

#pragma endregion

#pragma region ALLOCATOR

SPARKAPI SparkHandle SparkAllocate(SparkSize size) {
	return malloc(size);
}

SPARKAPI SparkVoid SparkFree(SparkHandle handle) {
	free(handle);
}

SPARKAPI SparkHandle SparkReallocate(SparkHandle handle, SparkSize size) {
	return realloc(handle, size);
}

SPARKAPI SparkHandle SparkCallocate(SparkSize count, SparkSize size) {
	return calloc(count, size);
}

SPARKAPI SparkAllocator SparkDefaultAllocator() {
	static SparkAllocator allocator = SPARK_NULL;
	if (!allocator) {
		allocator = SparkAllocate(sizeof(struct SparkAllocatorT));
		allocator->allocate = SparkAllocate;
		allocator->reallocate = SparkReallocate;
		allocator->free = SparkFree;
		allocator->ref_count = 0;
	}
	allocator->ref_count++;
	return allocator;
}

SPARKAPI SparkAllocator SparkCreateAllocator(SparkAllocateFunction allocate,
	SparkReallocateFunction reallocate,
	SparkFreeFunction free) {
	SparkAllocator allocator = allocate(sizeof(struct SparkAllocatorT));
	allocator->allocate = allocate;
	allocator->reallocate = reallocate;
	allocator->free = free;
	allocator->ref_count = 1;
	return allocator;
}

SPARKAPI SparkVoid SparkDestroyAllocator(SparkAllocator allocator) {
	if (allocator)
		allocator->ref_count--;

	if (!allocator->ref_count) 
		allocator->free(allocator);
}

SPARKAPI SparkAllocator SparkCopyAllocator(SparkAllocator allocator) {
	++allocator->ref_count;
	return allocator;
}

#pragma endregion

#pragma region PAIR

SPARKAPI SparkPair* SparkCreatePair(SparkHandle first, SparkHandle second) {
	SparkPair* pair = SparkAllocate(sizeof(struct SparkPairT));
	pair->first = first;
	pair->second = second;
	return pair;
}

SPARKAPI SparkVoid SparkDestroyPair(SparkPair* pair) { SparkFree(pair); }

#pragma endregion

#pragma region VECTOR

SPARKAPI SparkVector SparkDefaultVector() {
	SparkVector vector = SparkAllocate(sizeof(struct SparkVectorT));
	vector->allocator = SparkDefaultAllocator();
	vector->capacity = 1;
	vector->size = 0;
	vector->destructor = SPARK_NULL; // Default destructor is SPARK_NULL
	vector->elements =
		vector->allocator->allocate(vector->capacity * sizeof(SparkHandle));
	return vector;
}

SPARKAPI SparkVector SparkCreateVector(SparkSize capacity,
	SparkAllocator allocator,
	SparkFreeFunction destructor) {
	if (!allocator) {
		allocator = SparkDefaultAllocator();
	}

	SparkVector vector = allocator->allocate(sizeof(struct SparkVectorT));
	vector->allocator = allocator;
	vector->capacity = capacity;
	vector->size = 0;
	vector->destructor = destructor;
	vector->elements =
		allocator->allocate(vector->capacity * sizeof(SparkHandle));
	return vector;
}

SPARKAPI SparkVector SparkMemcpyIntoVector(SparkSize size, SparkHandle* elements, SparkAllocator allocator, SparkFreeFunction destructor) {
	if (!allocator) {
		allocator = SparkDefaultAllocator();
	}

	SparkVector vector = allocator->allocate(sizeof(struct SparkVectorT));
	vector->allocator = allocator;
	vector->capacity = size * 2;
	vector->size = size;
	vector->destructor = destructor;

	vector->elements =
		allocator->allocate(vector->capacity * sizeof(SparkHandle));

	memcpy(vector->elements, elements, size * sizeof(SparkHandle));

	return vector;
}

SPARKAPI SparkVoid SparkDestroyVector(SparkVector vector) {
	if (!vector) {
		return;
	}

	SparkAllocator allocator = vector->allocator;

	// Call destructor on each element if destructor is not SPARK_NULL
	if (vector->destructor != SPARK_NULL) {
		for (SparkSize i = 0; i < vector->size; i++) {
			vector->destructor(vector->elements[i]);
		}
	}

	if (vector->elements)
		allocator->free(vector->elements);

	allocator->free(vector);

	// Should be ref counted so this should be ok
	SparkDestroyAllocator(allocator);
}

SPARKAPI SparkVector SparkCopyVector(SparkVector vector) {
	// Null for destructor as we are only shallow copying the vectors elements,
	// not the elements themselves
	SparkVector copy =
		SparkCreateVector(vector->capacity, vector->allocator, SPARK_NULL);
	for (SparkSize i = 0; i < vector->size; i++) {
		SparkPushBackVector(copy, vector->elements[i]);
	}
	return copy;
}

SPARKAPI SparkHandle SparkGetElementVector(SparkVector vector,
	SparkSize index) {
	if (index >= vector->size || index < 0) {
		SPARK_LOG_ERROR("Index out of bounds!");
		return SPARK_NULL;
	}
	return vector->elements[index];
}

SPARKAPI SparkResult SparkPushBackVector(SparkVector vector,
	SparkHandle element) {
	if (vector->size >= vector->capacity) {
		vector->capacity *= 2;
		vector->elements = vector->allocator->reallocate(
			vector->elements, vector->capacity * sizeof(SparkHandle));
		if (vector->elements == SPARK_NULL) {
			SPARK_LOG_ERROR("Failed to reallocate vector!");
			return SPARK_ERROR_INVALID_STATE;
		}
	}
	vector->elements[vector->size++] = element;
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkPopBackVector(SparkVector vector) {
	if (vector->size == 0) {
		SPARK_LOG_ERROR("Vector is empty!");
		return SPARK_ERROR_INVALID_STATE;
	}
	vector->size--;

	// Call destructor on the element if destructor is not SPARK_NULL
	if (vector->destructor != SPARK_NULL) {
		vector->destructor(vector->elements[vector->size]);
	}

	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkInsertVector(SparkVector vector, SparkSize index,
	SparkHandle element) {
	if (index >= vector->size || index < 0) {
		SPARK_LOG_ERROR("Index out of bounds!");
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	if (vector->size >= vector->capacity) {
		vector->capacity *= 2;
		vector->elements = vector->allocator->reallocate(
			vector->elements, vector->capacity * sizeof(SparkHandle));
		if (vector->elements == SPARK_NULL) {
			SPARK_LOG_ERROR("Failed to reallocate vector!");
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
	if (!vector) {
		SPARK_LOG_ERROR("Invalid vector!");
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	if (index >= vector->size || index < 0) {
		SPARK_LOG_ERROR("Index out of bounds!");
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	// Call destructor on the element if destructor is not SPARK_NULL
	if (vector->destructor != SPARK_NULL) {
		vector->destructor(vector->elements[index]);
	}

	// Move elements to fill the gap
	for (SparkSize i = index; i < vector->size - 1; i++) {
		vector->elements[i] = vector->elements[i + 1];
	}
	vector->size--;
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkRemoveNoShiftVector(SparkVector vector,
	SparkSize index) {
	if (!vector) {
		SPARK_LOG_ERROR("Invalid vector!");
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	if (index >= vector->size || index < 0) {
		SPARK_LOG_ERROR("Index out of bounds!");
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	// Call destructor on the element if destructor is not SPARK_NULL
	if (vector->destructor != SPARK_NULL) {
		vector->destructor(vector->elements[index]);
	}

	vector->elements[index] = SPARK_NULL;

	vector->size--;
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkEraseVector(SparkVector vector, SparkSize begin,
	SparkSize end) {
	if (!vector) {
		SPARK_LOG_ERROR("Invalid vector!");
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	for (SparkSize i = begin; i < end; i++) {
		if (i >= vector->size) {
			SPARK_LOG_ERROR("Index out of bounds!");
			return SPARK_ERROR_INVALID_ARGUMENT;
		}

		// Call destructor on the element if destructor is not SPARK_NULL
		if (vector->destructor != SPARK_NULL) {
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

SPARKAPI SparkResult SparkSetVector(SparkVector vector, SparkSize index,
	SparkHandle element) {
	if (!vector) {
		SPARK_LOG_ERROR("Invalid vector!");
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	if (index >= vector->size) {
		SPARK_LOG_ERROR("Index out of bounds!");
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	// Call destructor on the existing element if destructor is not SPARK_NULL
	if (vector->destructor != SPARK_NULL) {
		vector->destructor(vector->elements[index]);
	}

	vector->elements[index] = element;
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkResizeVector(SparkVector vector, SparkSize capacity) {
	if (capacity < vector->size) {
		// If new capacity is less than current size, need to destroy extra elements
		if (vector->destructor != SPARK_NULL) {
			for (SparkSize i = capacity; i < vector->size; i++) {
				vector->destructor(vector->elements[i]);
			}
		}
		vector->size = capacity;
	}
	vector->capacity = capacity;
	vector->elements = vector->allocator->reallocate(
		vector->elements, vector->capacity * sizeof(SparkHandle));
	if (vector->elements == SPARK_NULL) {
		SPARK_LOG_ERROR("Failed to reallocate vector!");
		return SPARK_ERROR_INVALID_STATE;
	}
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkCompressVector(SparkVector vector) {
	if (!vector) {
		SPARK_LOG_ERROR("Invalid vector!");
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	SparkSize new_size = 0;

	// Iterate through the vector and move non-null elements to fill gaps
	for (SparkSize i = 0; i < vector->size; i++) {
		if (vector->elements[i]) {
			vector->elements[new_size] = vector->elements[i];
			new_size++;
		}
	}

	// If any null elements were found and compressed, adjust the size
	vector->size = new_size;

	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkClearVector(SparkVector vector) {
	if (!vector) {
		SPARK_LOG_ERROR("Invalid vector!");
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	// Call destructor on each element if destructor is not SPARK_NULL
	if (vector->destructor != SPARK_NULL) {
		for (SparkSize i = 0; i < vector->size; i++) {
			vector->destructor(vector->elements[i]);
		}
	}
	vector->size = 0;
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkPushBackBufferVector(SparkVector vector,
	SparkConstBuffer buffer,
	SparkSize buffer_size) {
	if (!vector) {
		SPARK_LOG_ERROR("Invalid vector!");
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	if (vector->size + buffer_size >= vector->capacity) {
		vector->capacity = (vector->size + buffer_size) * 2;
		vector->elements = vector->allocator->reallocate(
			vector->elements, vector->capacity * sizeof(SparkHandle));
		if (vector->elements == SPARK_NULL) {
			SPARK_LOG_ERROR("Failed to reallocate vector!");
			return SPARK_ERROR_INVALID_STATE;
		}
	}

	memcpy(vector->elements + vector->size, buffer, buffer_size);

	vector->size += buffer_size;

	return SPARK_SUCCESS;
}

#pragma endregion

#pragma region LIST

SPARKAPI SparkList SparkDefaultList() {
	SparkList list = SparkAllocate(sizeof(struct SparkListT));
	list->allocator = SparkDefaultAllocator();
	list->destructor = SPARK_NULL; // Default destructor is SPARK_NULL
	list->head = SPARK_NULL;
	list->tail = SPARK_NULL;
	list->size = 0;
	return list;
}

SPARKAPI SparkList SparkCreateList(SparkAllocator allocator,
	SparkFreeFunction destructor) {
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
	return list;
}

SPARKAPI SparkVoid SparkDestroyList(SparkList list) {
	if (!list) {
		return;
	}
	SparkAllocator allocator = list->allocator;

	// Call destructor on each element if destructor is not SPARK_NULL
	SparkListNode node = list->head;
	while (node != SPARK_NULL) {
		if (list->destructor != SPARK_NULL) {
			list->destructor(node->data);
		}
		SparkListNode temp = node;
		node = node->next;
		allocator->free(temp);
	}

	allocator->free(list);

		SparkDestroyAllocator(allocator);
}

SPARKAPI SparkHandle SparkGetElementList(SparkList list, SparkIndex index) {
	if (index >= list->size) {
		SPARK_LOG_ERROR("Index out of bounds!");
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
		SPARK_LOG_ERROR("List is empty!");
		return SPARK_ERROR_INVALID_STATE;
	}

	SparkListNode node = list->head;
	SparkListNode prev = SPARK_NULL;

	while (node->next != SPARK_NULL) {
		prev = node;
		node = node->next;
	}

	// Call destructor on the element if destructor is not SPARK_NULL
	if (list->destructor != SPARK_NULL) {
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

SPARKAPI SparkResult SparkInsertList(SparkList list, SparkIndex index,
	SparkHandle element) {
	if (index > list->size) {
		SPARK_LOG_ERROR("Index out of bounds!");
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
		SPARK_LOG_ERROR("Index out of bounds!");
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

	// Call destructor on the element if destructor is not SPARK_NULL
	if (list->destructor) {
		list->destructor(node_to_remove->data);
	}

	list->allocator->free(node_to_remove);
	list->size--;
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkSetList(SparkList list, SparkIndex index,
	SparkHandle element) {
	if (index >= list->size) {
		SPARK_LOG_ERROR("Index out of bounds!");
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	SparkListNode node = list->head;
	for (SparkIndex i = 0; i < index; i++) {
		node = node->next;
	}

	// Call destructor on the existing element if destructor is not SPARK_NULL
	if (list->destructor != SPARK_NULL) {
		list->destructor(node->data);
	}

	node->data = element;
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkClearList(SparkList list) {
	SparkListNode node = list->head;
	while (node != SPARK_NULL) {
		if (list->destructor != SPARK_NULL) {
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
#define PRIME32_4 668265263U
#define PRIME32_5 374761393U

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
			v1 += *((const SparkU32*)data) * PRIME32_2;
			data += 4;
			v1 = (v1 << 13) | (v1 >> 19); // Rotate left 13 bits
			v1 *= PRIME32_1;

			v2 += *((const SparkU32*)data) * PRIME32_2;
			data += 4;
			v2 = (v2 << 13) | (v2 >> 19); // Rotate left 13 bits
			v2 *= PRIME32_1;

			v3 += *((const SparkU32*)data) * PRIME32_2;
			data += 4;
			v3 = (v3 << 13) | (v3 >> 19); // Rotate left 13 bits
			v3 *= PRIME32_1;

			v4 += *((const SparkU32*)data) * PRIME32_2;
			data += 4;
			v4 = (v4 << 13) | (v4 >> 19); // Rotate left 13 bits
			v4 *= PRIME32_1;
		} while (data <= limit);

		hash = ((v1 << 1) | (v1 >> 31)) + ((v2 << 7) | (v2 >> 25)) +
			((v3 << 12) | (v3 >> 20)) + ((v4 << 18) | (v4 >> 14));
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

SparkSize SparkStringHash(SparkConstBuffer key, SparkSize key_size) {
	SparkConstString str = (SparkConstString)key;
	SparkSize hash = 14695981039346656037ULL;
	for (SparkSize i = 0; i < key_size; ++i) {
		hash ^= (SparkSize)str[i];
		hash *= 1099511628211ULL;
	}
	return hash;
}

SparkSize SparkIntegerHash(SparkConstBuffer key, SparkSize key_size) {
	// Simple integer hash function
	return key;
}

SparkI32 SparkStringCompare(SparkConstBuffer a, SparkSize a_size,
	SparkConstBuffer b, SparkSize b_size) {
	if (a_size != b_size)
		return (SparkI32)(a_size - b_size);
	return memcmp(a, b, a_size);
}

SparkI32 SparkIntegerCompare(SparkConstBuffer a, SparkSize a_size,
	SparkConstBuffer b, SparkSize b_size) {
	SparkI32 int_a = a;
	SparkI32 int_b = b;
	return int_a - int_b;
}

#pragma endregion

#pragma region HASHMAP

SPARKAPI SparkHashMap SparkDefaultHashMap() {
	return SparkCreateHashMap(4, SparkStringHash, SparkStringCompare, SPARK_NULL,
		SPARK_NULL, SPARK_NULL);
}

SPARKAPI SparkHashMap SparkCreateHashMap(SparkSize capacity,
	SparkHashFunction hash_function,
	SparkCompareFunction compare_function,
	SparkAllocator allocator,
	SparkFreeFunction key_destructor,
	SparkFreeFunction value_destructor) {
	SparkBool external_allocator = SPARK_TRUE;
	if (!allocator) {
		allocator = SparkDefaultAllocator();
		external_allocator = SPARK_FALSE;
	}
	if (!hash_function || !compare_function)
		return SPARK_NULL;
	SparkHashMap hashmap =
		(SparkHashMap)allocator->allocate(sizeof(struct SparkHashMapT));
	if (!hashmap)
		return SPARK_NULL;
	hashmap->allocator = allocator;
	hashmap->capacity = capacity;
	hashmap->size = 0;
	hashmap->buckets = (SparkHashMapNode*)allocator->allocate(
		capacity * sizeof(SparkHashMapNode));
	if (!hashmap->buckets) {
		allocator->free(hashmap);
		return SPARK_NULL;
	}
	memset(hashmap->buckets, 0, capacity * sizeof(SparkHashMapNode));
	hashmap->hash_function = hash_function;
	hashmap->compare_function = compare_function;
	hashmap->key_destructor = key_destructor;
	hashmap->value_destructor = value_destructor;
	return hashmap;
}

SPARKAPI SparkVoid SparkDestroyHashMap(SparkHashMap hashmap) {
	if (!hashmap)
		return;

	SparkAllocator allocator = hashmap->allocator;

	for (SparkSize i = 0; i < hashmap->capacity; ++i) {
		SparkHashMapNode node = hashmap->buckets[i];
		while (node) {
			SparkHashMapNode next = node->next;
			if (hashmap->key_destructor) {
				hashmap->key_destructor(node->key);
			}
			if (hashmap->value_destructor) {
				hashmap->value_destructor(node->value);
			}
			allocator->free(node);
			node = next;
		}
	}
	allocator->free(hashmap->buckets);
	allocator->free(hashmap);

		SparkDestroyAllocator(allocator);
}

SPARKAPI SparkResult SparkInsertHashMap(SparkHashMap hashmap, SparkHandle key,
	SparkSize key_size, SparkHandle value) {
	if (!hashmap || !key)
		return SPARK_ERROR_INVALID_ARGUMENT;
	SparkSize hash = hashmap->hash_function(key, key_size);
	SparkSize index = hash % hashmap->capacity;
	SparkHashMapNode node = hashmap->buckets[index];
	while (node) {
		if (node->hash == hash &&
			hashmap->compare_function(node->key, node->key_size, key, key_size) ==
			0) {
			// Key already exists, update value
			if (hashmap->value_destructor) {
				hashmap->value_destructor(node->value);
			}
			node->value = value;
			return SPARK_SUCCESS;
		}
		node = node->next;
	}
	// Key not found, insert new node
	node = (SparkHashMapNode)hashmap->allocator->allocate(
		sizeof(struct SparkHashMapNodeT));
	if (!node)
		return SPARK_ERROR_OUT_OF_MEMORY;
	node->key = key;
	node->value = value;
	node->key_size = key_size;
	node->hash = hash;
	node->next = hashmap->buckets[index];
	hashmap->buckets[index] = node;
	hashmap->size++;
	return SPARK_SUCCESS;
}

SPARKAPI SparkHandle SparkGetElementHashMap(SparkHashMap hashmap,
	SparkHandle key,
	SparkSize key_size) {
	if (!hashmap || !key)
		return SPARK_NULL;
	SparkSize hash = hashmap->hash_function(key, key_size);
	SparkSize index = hash % hashmap->capacity;
	SparkHashMapNode node = hashmap->buckets[index];
	while (node) {
		if (node->hash == hash &&
			hashmap->compare_function(node->key, node->key_size, key, key_size) ==
			0) {
			return node->value;
		}
		node = node->next;
	}
	return SPARK_NULL;
}

SPARKAPI SparkBool SparkContainsHashMap(SparkHashMap hashmap, SparkHandle key,
	SparkSize key_size) {
	if (!hashmap || !key)
		return SPARK_FALSE;
	SparkSize hash = hashmap->hash_function(key, key_size);
	SparkSize index = hash % hashmap->capacity;
	SparkHashMapNode node = hashmap->buckets[index];
	while (node) {
		if (node->hash == hash &&
			hashmap->compare_function(node->key, node->key_size, key, key_size) ==
			0) {
			return SPARK_TRUE;
		}
		node = node->next;
	}
	return SPARK_FALSE;
}

SPARKAPI SparkResult SparkRemoveHashMap(SparkHashMap hashmap, SparkHandle key,
	SparkSize key_size) {
	if (!hashmap || !key)
		return SPARK_ERROR_INVALID_ARGUMENT;
	SparkSize hash = hashmap->hash_function(key, key_size);
	SparkSize index = hash % hashmap->capacity;
	SparkHashMapNode* prev = &hashmap->buckets[index];
	SparkHashMapNode node = hashmap->buckets[index];
	while (node) {
		if (node->hash == hash &&
			hashmap->compare_function(node->key, node->key_size, key, key_size) ==
			0) {
			*prev = node->next;
			if (hashmap->key_destructor) {
				hashmap->key_destructor(node->key);
			}
			if (hashmap->value_destructor) {
				hashmap->value_destructor(node->value);
			}
			hashmap->allocator->free(node);
			hashmap->size--;
			return SPARK_SUCCESS;
		}
		prev = &node->next;
		node = node->next;
	}
	return SPARK_ERROR_NOT_FOUND;
}

SPARKAPI SparkVector SparkGetAllKeysHashMap(SparkHashMap hashmap) {
	if (!hashmap)
		return SPARK_NULL;

	SparkVector keys = SparkDefaultVector();
	if (!keys)
		return SPARK_NULL;

	SparkSize index = 0;
	for (SparkSize i = 0; i < hashmap->capacity; ++i) {
		SparkHashMapNode node = hashmap->buckets[i];
		while (node) {
			SparkPushBackVector(keys, node->key);
			node = node->next;
		}
	}
	return keys;
}

SPARKAPI SparkVector SparkGetAllValuesHashMap(SparkHashMap hashmap) {
	if (!hashmap)
		return SPARK_NULL;

	SparkVector values = SparkDefaultVector();
	if (!values)
		return SPARK_NULL;

	SparkSize index = 0;
	for (SparkSize i = 0; i < hashmap->capacity; ++i) {
		SparkHashMapNode node = hashmap->buckets[i];
		while (node) {
			SparkPushBackVector(values, node->value);
			node = node->next;
		}
	}

	return values;
}

SPARKAPI SparkVector SparkGetAllPairsHashMap(SparkHashMap hashmap) {
	if (!hashmap)
		return SPARK_NULL;

	SparkVector pairs = SparkCreateVector(16, SPARK_NULL, SparkDestroyPair);

	for (SparkSize i = 0; i < hashmap->capacity; ++i) {
		SparkHashMapNode node = hashmap->buckets[i];
		while (node) {
			SparkPair* pair = SparkCreatePair(node->key, node->value);
			SparkPushBackVector(pairs, pair);
			node = node->next;
		}
	}

	return pairs;
}

#pragma endregion

#pragma region HASH_SET

SPARKAPI SparkHashSet SparkDefaultHashSet() {
	return SparkCreateHashSet(16, sizeof(SparkHandle), SPARK_NULL, SPARK_NULL,
		SPARK_NULL);
}

SPARKAPI SparkHashSet SparkCreateHashSet(SparkSize capacity,
	SparkSize element_size,
	SparkHashFunction hash,
	SparkAllocator allocator,
	SparkFreeFunction destructor) {
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
		SPARK_LOG_ERROR("Failed to allocate memory for hashset!");
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
	hashset->element_size = element_size;

	hashset->elements =
		allocator->allocate(hashset->capacity * sizeof(SparkHandle));
	if (hashset->elements == SPARK_NULL) {
		SPARK_LOG_ERROR(
			"Failed to allocate memory for hashset elements!");
		allocator->free(hashset);
			SparkDestroyAllocator(allocator);
		return SPARK_NULL;
	}

	hashset->hashes = allocator->allocate(hashset->capacity * sizeof(SparkSize));
	if (hashset->hashes == SPARK_NULL) {
		SPARK_LOG_ERROR(
			"Failed to allocate memory for hashset hashes!");
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

	// Call destructor on each element if destructor is not SPARK_NULL
	if (hashset->destructor != SPARK_NULL) {
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

	allocator->free(hashset);
	hashset = SPARK_NULL;

		SparkDestroyAllocator(allocator);
}

SPARKAPI SPARKSTATIC SparkResult SparkHashSetResize(SparkHashSet hashset,
	SparkSize new_capacity) {
	SparkHandle* old_elements = hashset->elements;
	SparkSize* old_hashes = hashset->hashes;
	SparkSize old_capacity = hashset->capacity;

	hashset->capacity = new_capacity;
	hashset->elements =
		hashset->allocator->allocate(hashset->capacity * sizeof(SparkHandle));
	hashset->hashes =
		hashset->allocator->allocate(hashset->capacity * sizeof(SparkSize));

	if (hashset->elements == SPARK_NULL || hashset->hashes == SPARK_NULL) {
		SPARK_LOG_ERROR(
			"Failed to allocate memory for hashset resizing!");

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
			SparkResult res =
				SparkInsertHashSet(hashset, old_elements[i], hashset->element_size);
			if (res != SPARK_SUCCESS) {
				SPARK_LOG_ERROR(
					"Failed to re-insert element during hashset resizing!");

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

SPARKAPI SparkBool SparkContainsHashSet(SparkHashSet hashset,
	SparkHandle element,
	SparkSize element_size) {
	if (hashset == SPARK_NULL || element == SPARK_NULL) {
		return SPARK_FALSE;
	}
	SparkSize element_hash =
		hashset->hash_function((SparkConstBuffer)element, element_size);
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

SPARKAPI SparkResult SparkInsertHashSet(SparkHashSet hashset,
	SparkHandle element,
	SparkSize element_size) {
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

	SparkSize element_hash =
		hashset->hash_function((SparkConstBuffer)element, element_size);
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

SPARKAPI SparkResult SparkRemoveHashSet(SparkHashSet hashset,
	SparkHandle element,
	SparkSize element_size) {
	if (hashset == SPARK_NULL || element == SPARK_NULL) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	SparkSize element_hash =
		hashset->hash_function((SparkConstBuffer)element, element_size);
	SparkSize index = element_hash % hashset->capacity;

	SparkSize original_index = index;
	while (hashset->elements[index] != SPARK_NULL) {
		if (hashset->hashes[index] == element_hash) {
			// Call destructor on the element if destructor is not SPARK_NULL
			if (hashset->destructor != SPARK_NULL) {
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

	SPARK_LOG_ERROR("Element not found in hashset!");
	return SPARK_ERROR_NOT_FOUND;
}

SPARKAPI SparkResult SparkClearHashSet(SparkHashSet hashset) {
	if (hashset == SPARK_NULL) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	// Call destructor on each element if destructor is not SPARK_NULL
	if (hashset->destructor != SPARK_NULL) {
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
	return SparkCreateQueue(16, SPARK_NULL, SPARK_NULL);
}

SPARKAPI SparkQueue SparkCreateQueue(SparkSize capacity,
	SparkAllocator allocator,
	SparkFreeFunction destructor) {
	SparkBool external_allocator = SPARK_TRUE;

	if (capacity == 0) {
		SPARK_LOG_ERROR("Capacity must be greater than zero!");
		return SPARK_NULL;
	}

	if (!allocator) {
		allocator = SparkDefaultAllocator();
		external_allocator = SPARK_FALSE;
	}

	SparkQueue queue = allocator->allocate(sizeof(struct SparkQueueT));
	if (queue == SPARK_NULL) {
		SPARK_LOG_ERROR("Failed to allocate memory for queue!");
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

	queue->elements = allocator->allocate(queue->capacity * sizeof(SparkHandle));
	if (queue->elements == SPARK_NULL) {
		SPARK_LOG_ERROR(
			"Failed to allocate memory for queue elements!");
		allocator->free(queue);
			SparkDestroyAllocator(allocator);
		return SPARK_NULL;
	}
	return queue;
}

SPARKAPI SparkVoid SparkDestroyQueue(SparkQueue queue) {
	if (queue == SPARK_NULL) {
		return;
	}
	SparkAllocator allocator = queue->allocator;

	// Call destructor on each element if destructor is not SPARK_NULL
	if (queue->destructor != SPARK_NULL) {
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

	allocator->free(queue);

		SparkDestroyAllocator(allocator);
}

SPARKAPI SparkResult SparkEnqueueQueue(SparkQueue queue, SparkHandle element) {
	if (queue == SPARK_NULL || element == SPARK_NULL) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	if (queue->size >= queue->capacity) {
		// Resize the queue
		SparkSize new_capacity = queue->capacity * 2;
		SparkHandle* new_elements =
			queue->allocator->allocate(new_capacity * sizeof(SparkHandle));
		if (new_elements == SPARK_NULL) {
			SPARK_LOG_ERROR(
				"Failed to allocate memory for queue resizing!");
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
		SPARK_LOG_ERROR("Queue is empty!");
		return SPARK_ERROR_INVALID_STATE;
	}

	// Call destructor on the element if destructor is not SPARK_NULL
	if (queue->destructor != SPARK_NULL &&
		queue->elements[queue->front] != SPARK_NULL) {
		queue->destructor(queue->elements[queue->front]);
		queue->elements[queue->front] = SPARK_NULL;
	}

	queue->front = (queue->front + 1) % queue->capacity;
	queue->size--;
	return SPARK_SUCCESS;
}

SPARKAPI SparkHandle SparkGetFrontQueue(SparkQueue queue) {
	if (queue == SPARK_NULL || queue->size == 0) {
		SPARK_LOG_ERROR("Queue is empty or SPARK_NULL!");
		return SPARK_NULL;
	}
	return queue->elements[queue->front];
}

SPARKAPI SparkHandle SparkGetBackQueue(SparkQueue queue) {
	if (queue == SPARK_NULL || queue->size == 0) {
		SPARK_LOG_ERROR("Queue is empty or SPARK_NULL!");
		return SPARK_NULL;
	}
	SparkSize index = (queue->rear == 0) ? queue->capacity - 1 : queue->rear - 1;
	return queue->elements[index];
}

SPARKAPI SparkResult SparkClearQueue(SparkQueue queue) {
	if (queue == SPARK_NULL) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	// Call destructor on each element if destructor is not SPARK_NULL
	if (queue->destructor != SPARK_NULL) {
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
	return SparkCreateStack(16, SPARK_NULL, SPARK_NULL);
}

SPARKAPI SparkStack SparkCreateStack(SparkSize capacity,
	SparkAllocator allocator,
	SparkFreeFunction destructor) {
	SparkBool external_allocator = SPARK_TRUE;

	if (capacity == 0) {
		SPARK_LOG_ERROR("Capacity must be greater than zero!");
		return SPARK_NULL;
	}

	if (!allocator) {
		allocator = SparkDefaultAllocator();
		external_allocator = SPARK_FALSE;
	}

	SparkStack stack = allocator->allocate(sizeof(struct SparkStackT));
	if (stack == SPARK_NULL) {
		SPARK_LOG_ERROR("Failed to allocate memory for stack!");
		if (!external_allocator) {
			SparkDestroyAllocator(allocator);
		}
		return SPARK_NULL;
	}

	stack->allocator = allocator;
	stack->capacity = capacity;
	stack->size = 0;
	stack->destructor = destructor;

	stack->elements = allocator->allocate(stack->capacity * sizeof(SparkHandle));
	if (stack->elements == SPARK_NULL) {
		SPARK_LOG_ERROR(
			"Failed to allocate memory for stack elements!");
		allocator->free(stack);
			SparkDestroyAllocator(allocator);
		return SPARK_NULL;
	}
	return stack;
}

SPARKAPI SparkVoid SparkDestroyStack(SparkStack stack) {
	if (stack == SPARK_NULL) {
		return;
	}
	SparkAllocator allocator = stack->allocator;

	// Call destructor on each element if destructor is not SPARK_NULL
	if (stack->destructor != SPARK_NULL) {
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

	allocator->free(stack);

		SparkDestroyAllocator(allocator);
}

SPARKAPI SparkResult SparkPushStack(SparkStack stack, SparkHandle element) {
	if (stack == SPARK_NULL || element == SPARK_NULL) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	if (stack->size >= stack->capacity) {
		SparkSize new_capacity = stack->capacity * 2;
		SparkHandle* new_elements =
			stack->allocator->allocate(new_capacity * sizeof(SparkHandle));
		if (new_elements == SPARK_NULL) {
			SPARK_LOG_ERROR(
				"Failed to allocate memory for stack resizing!");
			return SPARK_ERROR_OUT_OF_MEMORY;
		}
		// Copy elements to new array
		for (SparkSize i = 0; i < stack->size; i++) {
			new_elements[i] = stack->elements[i];
		}
		// Free the old array
		stack->allocator->free(stack->elements);
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
		SPARK_LOG_ERROR("Stack is empty!");
		return SPARK_ERROR_INVALID_STATE;
	}
	stack->size--;

	// Call destructor on the element if destructor is not SPARK_NULL
	if (stack->destructor != SPARK_NULL &&
		stack->elements[stack->size] != SPARK_NULL) {
		stack->destructor(stack->elements[stack->size]);
		stack->elements[stack->size] = SPARK_NULL;
	}

	return SPARK_SUCCESS;
}

SPARKAPI SparkHandle SparkGetTopStack(SparkStack stack) {
	if (stack == SPARK_NULL || stack->size == 0) {
		SPARK_LOG_ERROR("Stack is empty or SPARK_NULL!");
		return SPARK_NULL;
	}
	return stack->elements[stack->size - 1];
}

SPARKAPI SparkResult SparkClearStack(SparkStack stack) {
	if (stack == SPARK_NULL) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}
	// Call destructor on each element if destructor is not SPARK_NULL
	if (stack->destructor != SPARK_NULL) {
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

#pragma region ITERATOR

SPARKAPI SparkVectorIterator
SparkCreateVectorIterator(SparkIteratorState start_state, SparkVector vector) {
	if (!vector)
		return NULL;

	SparkVectorIterator it =
		(SparkVectorIterator)SparkAllocate(sizeof(struct SparkVectorIteratorT));
	if (!it)
		return NULL;

	it->vector = vector;

	switch (start_state) {
	case SPARK_ITERATOR_STATE_BEGIN:
		it->pos = (vector->size > 0) ? 0 : (size_t)-1;
		it->state = (vector->size > 0) ? SPARK_ITERATOR_STATE_BEGIN
			: SPARK_ITERATOR_STATE_INVALID;
		break;
	case SPARK_ITERATOR_STATE_END:
		it->pos = (vector->size > 0) ? vector->size - 1 : (size_t)-1;
		it->state = (vector->size > 0) ? SPARK_ITERATOR_STATE_END
			: SPARK_ITERATOR_STATE_INVALID;
		break;
	case SPARK_ITERATOR_STATE_INVALID:
	case SPARK_ITERATOR_STATE_ITERATING:
	case SPARK_ITERATOR_STATE_NONE:
	default:
		it->pos = (vector->size > 0) ? 0 : (size_t)-1;
		it->state = (vector->size > 0) ? SPARK_ITERATOR_STATE_BEGIN
			: SPARK_ITERATOR_STATE_INVALID;
		break;
	}

	return it;
}

SPARKAPI SparkVoid SparkDestroyVectorIterator(SparkVectorIterator it) {
	if (it) {
		SparkFree(it);
	}
}

SPARKAPI SparkIteratorState
SparkIterateForwardVectorIterator(SparkVectorIterator it) {
	if (!it || !it->vector)
		return SPARK_ITERATOR_STATE_INVALID;

	if (it->pos < it->vector->size - 1) {
		it->pos++;
		it->state = SPARK_ITERATOR_STATE_ITERATING;
		return it->state;
	}
	else if (it->pos == it->vector->size - 1) {
		it->state = SPARK_ITERATOR_STATE_END;
		return it->state;
	}

	it->state = SPARK_ITERATOR_STATE_INVALID;
	return it->state;
}

SPARKAPI SparkIteratorState
SparkIterateBackwardVectorIterator(SparkVectorIterator it) {
	if (!it || !it->vector)
		return SPARK_ITERATOR_STATE_INVALID;

	if (it->pos > 0 && it->pos < it->vector->size) {
		it->pos--;
		it->state = SPARK_ITERATOR_STATE_ITERATING;
		return it->state;
	}
	else if (it->pos == 0) {
		it->state = SPARK_ITERATOR_STATE_BEGIN;
		return it->state;
	}

	it->state = SPARK_ITERATOR_STATE_INVALID;
	return it->state;
}

SPARKAPI SparkIteratorState
SparkIsAtBeginningVectorIterator(SparkVectorIterator it) {
	if (!it || !it->vector)
		return SPARK_ITERATOR_STATE_INVALID;

	if (it->pos == 0 && it->vector->size > 0) {
		return SPARK_ITERATOR_STATE_BEGIN;
	}
	else if (it->pos == it->vector->size - 1 && it->vector->size > 0) {
		return SPARK_ITERATOR_STATE_END;
	}
	else if (it->pos < it->vector->size && it->pos > 0) {
		return SPARK_ITERATOR_STATE_ITERATING;
	}
	else {
		return SPARK_ITERATOR_STATE_INVALID;
	}
}

SPARKAPI SparkIteratorState SparkIsAtEndVectorIterator(SparkVectorIterator it) {
	// Functionally identical to SparkIsAtBeginningVectorIterator
	return SparkIsAtBeginningVectorIterator(it);
}

SPARKAPI SparkHandle SparkGetCurrentVectorIterator(SparkVectorIterator it) {
	if (!it || !it->vector)
		return NULL;

	if (it->pos < it->vector->size) {
		return SparkGetElementVector(it->vector, it->pos);
	}

	return NULL;
}

SPARKAPI SparkHandle SparkGetPreviousVectorIterator(SparkVectorIterator it) {
	if (!it || !it->vector)
		return NULL;

	if (it->pos > 0 && it->pos <= it->vector->size - 1) {
		return SparkGetElementVector(it->vector, it->pos - 1);
	}

	return NULL;
}

SPARKAPI SparkHandle SparkGetNextVectorIterator(SparkVectorIterator it) {
	if (!it || !it->vector)
		return NULL;

	if (it->pos + 1 < it->vector->size) {
		return SparkGetElementVector(it->vector, it->pos + 1);
	}

	return NULL;
}

SPARKAPI SparkBool SparkHasNextVectorIterator(SparkVectorIterator it) {
	return SparkGetNextVectorIterator(it) != NULL ? SPARK_TRUE : SPARK_FALSE;
}

SPARKAPI SparkBool SparkHasPreviousVectorIterator(SparkVectorIterator it) {
	return SparkGetPreviousVectorIterator(it) != NULL ? SPARK_TRUE : SPARK_FALSE;
}

SPARKAPI SparkListIterator
SparkCreateListIterator(SparkIteratorState start_state, SparkList list) {
	if (!list)
		return NULL;

	SparkListIterator it =
		(SparkListIterator)SparkAllocate(sizeof(struct SparkListIteratorT));
	if (!it)
		return NULL;

	it->list = list;

	switch (start_state) {
	case SPARK_ITERATOR_STATE_BEGIN:
		it->pos = (list->size > 0) ? 0 : (size_t)-1;
		it->state = (list->size > 0) ? SPARK_ITERATOR_STATE_BEGIN
			: SPARK_ITERATOR_STATE_INVALID;
		break;
	case SPARK_ITERATOR_STATE_END:
		it->pos = (list->size > 0) ? list->size - 1 : (size_t)-1;
		it->state = (list->size > 0) ? SPARK_ITERATOR_STATE_END
			: SPARK_ITERATOR_STATE_INVALID;
		break;
	case SPARK_ITERATOR_STATE_INVALID:
	case SPARK_ITERATOR_STATE_ITERATING:
	case SPARK_ITERATOR_STATE_NONE:
	default:
		it->pos = (list->size > 0) ? 0 : (size_t)-1;
		it->state = (list->size > 0) ? SPARK_ITERATOR_STATE_BEGIN
			: SPARK_ITERATOR_STATE_INVALID;
		break;
	}

	return it;
}

SPARKAPI SparkVoid SparkDestroyListIterator(SparkListIterator it) {
	if (it) {
		SparkFree(it);
	}
}

SPARKAPI SparkIteratorState
SparkIterateForwardListIterator(SparkListIterator it) {
	if (!it || !it->list)
		return SPARK_ITERATOR_STATE_INVALID;

	if (it->pos < it->list->size - 1) {
		it->pos++;
		it->state = SPARK_ITERATOR_STATE_ITERATING;
		return it->state;
	}
	else if (it->pos == it->list->size - 1) {
		it->state = SPARK_ITERATOR_STATE_END;
		return it->state;
	}

	it->state = SPARK_ITERATOR_STATE_INVALID;
	return it->state;
}

SPARKAPI SparkIteratorState
SparkIterateBackwardListIterator(SparkListIterator it) {
	if (!it || !it->list)
		return SPARK_ITERATOR_STATE_INVALID;

	if (it->pos > 0 && it->pos < it->list->size) {
		it->pos--;
		it->state = SPARK_ITERATOR_STATE_ITERATING;
		return it->state;
	}
	else if (it->pos == 0) {
		it->state = SPARK_ITERATOR_STATE_BEGIN;
		return it->state;
	}

	it->state = SPARK_ITERATOR_STATE_INVALID;
	return it->state;
}

SPARKAPI SparkIteratorState
SparkIsAtBeginningListIterator(SparkListIterator it) {
	if (!it || !it->list)
		return SPARK_ITERATOR_STATE_INVALID;

	if (it->pos == 0 && it->list->size > 0) {
		return SPARK_ITERATOR_STATE_BEGIN;
	}
	else if (it->pos == it->list->size - 1 && it->list->size > 0) {
		return SPARK_ITERATOR_STATE_END;
	}
	else if (it->pos < it->list->size && it->pos > 0) {
		return SPARK_ITERATOR_STATE_ITERATING;
	}
	else {
		return SPARK_ITERATOR_STATE_INVALID;
	}
}

SPARKAPI SparkIteratorState SparkIsAtEndListIterator(SparkListIterator it) {
	// Functionally identical to SparkIsAtBeginningListIterator
	return SparkIsAtBeginningListIterator(it);
}

SPARKAPI SparkHandle SparkGetCurrentListIterator(SparkListIterator it) {
	if (!it || !it->list)
		return NULL;

	if (it->pos < it->list->size) {
		return SparkGetElementList(it->list, it->pos);
	}

	return NULL;
}

SPARKAPI SparkHandle SparkGetPreviousListIterator(SparkListIterator it) {
	if (!it || !it->list)
		return NULL;

	if (it->pos > 0 && it->pos <= it->list->size - 1) {
		return SparkGetElementList(it->list, it->pos - 1);
	}

	return NULL;
}

SPARKAPI SparkHandle SparkGetNextListIterator(SparkListIterator it) {
	if (!it || !it->list)
		return NULL;

	if (it->pos + 1 < it->list->size) {
		return SparkGetElementList(it->list, it->pos + 1);
	}

	return NULL;
}

SPARKAPI SparkBool SparkHasNextListIterator(SparkListIterator it) {
	return SparkGetNextListIterator(it) != NULL ? SPARK_TRUE : SPARK_FALSE;
}

SPARKAPI SparkBool SparkHasPreviousListIterator(SparkListIterator it) {
	return SparkGetPreviousListIterator(it) != NULL ? SPARK_TRUE : SPARK_FALSE;
}

SPARKAPI SparkHashMapIterator SparkCreateHashMapIterator(
	SparkIteratorState start_state, SparkHashMapIteratorType iterator_type,
	SparkHashMap hash_map) {
	if (!hash_map)
		return NULL;

	SparkHashMapIterator it =
		(SparkHashMapIterator)SparkAllocate(sizeof(struct SparkHashMapIteratorT));
	if (!it)
		return NULL;

	it->hash_map = hash_map;
	it->iterator_type = iterator_type;

	switch (start_state) {
	case SPARK_ITERATOR_STATE_BEGIN:
		it->pos = (hash_map->size > 0) ? 0 : (size_t)-1;
		it->state = (hash_map->size > 0) ? SPARK_ITERATOR_STATE_BEGIN
			: SPARK_ITERATOR_STATE_INVALID;
		break;
	case SPARK_ITERATOR_STATE_END:
		it->pos = (hash_map->size > 0) ? hash_map->size - 1 : (size_t)-1;
		it->state = (hash_map->size > 0) ? SPARK_ITERATOR_STATE_END
			: SPARK_ITERATOR_STATE_INVALID;
		break;
	case SPARK_ITERATOR_STATE_INVALID:
	case SPARK_ITERATOR_STATE_ITERATING:
	case SPARK_ITERATOR_STATE_NONE:
	default:
		it->pos = (hash_map->size > 0) ? 0 : (size_t)-1;
		it->state = (hash_map->size > 0) ? SPARK_ITERATOR_STATE_BEGIN
			: SPARK_ITERATOR_STATE_INVALID;
		break;
	}

	switch (iterator_type) {
	case SPARK_HASHMAP_ITERATOR_TYPE_KEY:
		it->iterator_data = SparkGetAllKeysHashMap(hash_map);
		break;
	case SPARK_HASHMAP_ITERATOR_TYPE_VALUE:
		it->iterator_data = SparkGetAllValuesHashMap(hash_map);
		break;
	case SPARK_HASHMAP_ITERATOR_TYPE_PAIR:
		it->iterator_data = SparkGetAllPairsHashMap(hash_map);
		break;
	default:
		it->iterator_data = NULL;
		it->state = SPARK_ITERATOR_STATE_INVALID;
		SparkFree(it);
		return NULL;
	}

	if (!it->iterator_data && hash_map->size > 0) {
		// Allocation failed
		it->state = SPARK_ITERATOR_STATE_INVALID;
		SparkFree(it);
		return NULL;
	}

	return it;
}

SPARKAPI SparkVoid SparkDestroyHashMapIterator(SparkHashMapIterator it) {
	if (it) {
		if (it->iterator_data) {
			SparkFree(it->iterator_data);
		}
		SparkFree(it);
	}
}

SPARKAPI SparkIteratorState
SparkIterateForwardHashMapIterator(SparkHashMapIterator it) {
	if (!it || !it->iterator_data)
		return SPARK_ITERATOR_STATE_INVALID;

	if (it->pos < it->iterator_data->size - 1) {
		it->pos++;
		it->state = SPARK_ITERATOR_STATE_ITERATING;
		return it->state;
	}
	else if (it->pos == it->iterator_data->size - 1) {
		it->state = SPARK_ITERATOR_STATE_END;
		return it->state;
	}

	it->state = SPARK_ITERATOR_STATE_INVALID;
	return it->state;
}

SPARKAPI SparkIteratorState
SparkIterateBackwardHashMapIterator(SparkHashMapIterator it) {
	if (!it || !it->iterator_data)
		return SPARK_ITERATOR_STATE_INVALID;

	if (it->pos > 0 && it->pos < it->iterator_data->size) {
		it->pos--;
		it->state = SPARK_ITERATOR_STATE_ITERATING;
		return it->state;
	}
	else if (it->pos == 0) {
		it->state = SPARK_ITERATOR_STATE_BEGIN;
		return it->state;
	}

	it->state = SPARK_ITERATOR_STATE_INVALID;
	return it->state;
}

SPARKAPI SparkIteratorState
SparkIsAtBeginningHashMapIterator(SparkHashMapIterator it) {
	if (!it || !it->iterator_data)
		return SPARK_ITERATOR_STATE_INVALID;

	if (it->pos == 0 && it->iterator_data->size > 0) {
		return SPARK_ITERATOR_STATE_BEGIN;
	}
	else if (it->pos == it->iterator_data->size - 1 &&
		it->iterator_data->size > 0) {
		return SPARK_ITERATOR_STATE_END;
	}
	else if (it->pos < it->iterator_data->size && it->pos > 0) {
		return SPARK_ITERATOR_STATE_ITERATING;
	}
	else {
		return SPARK_ITERATOR_STATE_INVALID;
	}
}

SPARKAPI SparkIteratorState
SparkIsAtEndHashMapIterator(SparkHashMapIterator it) {
	// Functionally identical to SparkIsAtBeginningHashMapIterator
	return SparkIsAtBeginningHashMapIterator(it);
}

SPARKAPI SparkHandle SparkGetCurrentHashMapIterator(SparkHashMapIterator it) {
	if (!it || !it->iterator_data)
		return NULL;

	if (it->pos < it->iterator_data->size) {
		return SparkGetElementVector(it->iterator_data, it->pos);
	}

	return NULL;
}

SPARKAPI SparkHandle SparkGetPreviousHashMapIterator(SparkHashMapIterator it) {
	if (!it || !it->iterator_data)
		return NULL;

	if (it->pos > 0 && it->pos <= it->iterator_data->size - 1) {
		return SparkGetElementVector(it->iterator_data, it->pos - 1);
	}

	return NULL;
}

SPARKAPI SparkHandle SparkGetNextHashMapIterator(SparkHashMapIterator it) {
	if (!it || !it->iterator_data)
		return NULL;

	if (it->pos + 1 < it->iterator_data->size) {
		return SparkGetElementVector(it->iterator_data, it->pos + 1);
	}

	return NULL;
}

SPARKAPI SparkBool SparkHasNextHashMapIterator(SparkHashMapIterator it) {
	return SparkGetNextHashMapIterator(it) != NULL ? SPARK_TRUE : SPARK_FALSE;
}

SPARKAPI SparkBool SparkHasPreviousHashMapIterator(SparkHashMapIterator it) {
	return SparkGetPreviousHashMapIterator(it) != NULL ? SPARK_TRUE : SPARK_FALSE;
}

#pragma endregion

#pragma region THREAD

#ifdef _WIN32
#define SparkInitMutex(mutex) InitializeCriticalSection(&(mutex))
#define SparkLockMutex(mutex) EnterCriticalSection(&(mutex))
#define SparkUnlockMutex(mutex) LeaveCriticalSection(&(mutex))
#define SparkDestroyMutex(mutex) DeleteCriticalSection(&(mutex))
#define SparkInitCondition(cond) InitializeConditionVariable(&(cond))
#define SparkWaitCondition(cond, mutex)                                        \
  SleepConditionVariableCS(&(cond), &(mutex), INFINITE)
#define SparkSignalCondition(cond) WakeConditionVariable(&(cond))
#define SparkDestroyCondition(cond) /* No-op */
#define SparkBroadcastCondition(cond) WakeAllConditionVariable(&(cond))
#else
#define SparkInitMutex(mutex) pthread_mutex_init(&(mutex), SPARK_NULL)
#define SparkLockMutex(mutex) pthread_mutex_lock(&(mutex))
#define SparkUnlockMutex(mutex) pthread_mutex_unlock(&(mutex))
#define SparkDestroyMutex(mutex) pthread_mutex_destroy(&(mutex))
#define SparkInitCondition(cond) pthread_cond_init(&(cond), SPARK_NULL)
#define SparkWaitCondition(cond, mutex) pthread_cond_wait(&(cond), &(mutex))
#define SparkSignalCondition(cond) pthread_cond_signal(&(cond))
#define SparkDestroyCondition(cond) pthread_cond_destroy(&(cond))
#define SparkBroadcastCondition(cond) pthread_cond_broadcast(&(cond))
#endif

#ifdef _WIN32
DWORD WINAPI __SparkThreadPoolWorker(LPVOID arg) {
#else
SPARKAPI SPARKSTATIC SparkHandle __SparkThreadPoolWorker(SparkHandle arg) {
#endif
	SparkThreadPool pool = (SparkThreadPool)arg;
	SparkTaskHandle task;

	while (SPARK_TRUE) {
		SparkLockMutex(pool->mutex);

		while (pool->task_queue_head == NULL && !pool->stop) {
			SparkWaitCondition(pool->condition, pool->mutex);
		}

		if (pool->stop && pool->task_queue_head == NULL) {
			SparkUnlockMutex(pool->mutex);
			break;
		}

		// Get the task from the queue
		task = pool->task_queue_head;
		pool->task_queue_head = task->next;
		if (pool->task_queue_head == SPARK_NULL) {
			pool->task_queue_tail = SPARK_NULL;
		}

		SparkUnlockMutex(pool->mutex);

		if (task != SPARK_NULL) {
			// Perform the task
			task->function(task->arg);

			// Decrement pending task count and signal if zero
			if (task->wait_on_update) {
				SparkLockMutex(pool->pending_task_mutex);
				pool->pending_task_count--;
				if (pool->pending_task_count == 0) {
					SparkSignalCondition(pool->pending_task_cond);
				}
				SparkUnlockMutex(pool->pending_task_mutex);
			}

			// Destroy the task
			SparkTaskDestroy(task);
		}
	}

	return 0;
}

SPARKAPI SparkThreadPool SparkCreateThreadPool(SparkSize thread_count) {
	SparkThreadPool pool =
		(SparkThreadPool)SparkAllocate(sizeof(struct SparkThreadPoolT));
	if (pool == SPARK_NULL)
		return SPARK_NULL;

	pool->thread_count = thread_count;
	pool->threads =
		(SparkThread*)SparkAllocate(thread_count * sizeof(SparkThread));
	pool->task_queue_head = SPARK_NULL;
	pool->task_queue_tail = SPARK_NULL;
	pool->stop = SPARK_FALSE;
	pool->pending_task_count = 0;
	pool->shutdown = SPARK_FALSE;
	pool->shutdown_callbacks = SparkDefaultVector();
	pool->shutdown_callback_args = SparkDefaultVector();

	SparkInitMutex(pool->mutex);
	SparkInitCondition(pool->condition);

	SparkInitMutex(pool->pending_task_mutex);
	SparkInitCondition(pool->pending_task_cond);

	for (SparkSize i = 0; i < thread_count; ++i) {
#ifdef _WIN32
		unsigned threadID;
		pool->threads[i] = (HANDLE)_beginthreadex(
			SPARK_NULL, 0, __SparkThreadPoolWorker, pool, 0, &threadID);
		if (pool->threads[i] == 0) {
			SPARK_LOG_ERROR("Failed to create thread %zu", i);
			// Handle error (e.g., clean up and return)
		}
#else
		pthread_create(&pool->threads[i], SPARK_NULL, __SparkThreadPoolWorker,
			pool);
#endif
		}

	return pool;
	}

SPARKAPI SparkVoid SparkDestroyThreadPool(SparkThreadPool pool) {
	if (pool == SPARK_NULL)
		return;

	for (SparkSize i = 0; i < pool->shutdown_callbacks->size; ++i) {
		SparkThreadPoolShutdownCallback callback =
			SparkGetElementVector(pool->shutdown_callbacks, i);
		SparkHandle arg = SparkGetElementVector(pool->shutdown_callback_args, i);
		callback(arg);
	}

	/* Stop all threads */
	SparkLockMutex(pool->mutex);
	pool->stop = 1;
	SparkBroadcastCondition(pool->condition);
	SparkUnlockMutex(pool->mutex);

	/* Join all threads */
	for (SparkSize i = 0; i < pool->thread_count; ++i) {
#ifdef _WIN32
		DWORD wait_result = WaitForSingleObject(pool->threads[i], INFINITE);
		if (wait_result != WAIT_OBJECT_0) {
			SPARK_LOG_ERROR(
				"WaitForSingleObject failed on thread %zu", i);
		}
		CloseHandle(pool->threads[i]);
#else
		pthread_join(pool->threads[i], SPARK_NULL);
#endif
		}

	SparkDestroyVector(pool->shutdown_callbacks);
	SparkDestroyVector(pool->shutdown_callback_args);

	/* Clean up */
	SparkDestroyMutex(pool->mutex);
	SparkDestroyMutex(pool->pending_task_mutex);
	SparkDestroyCondition(pool->condition);
	SparkDestroyCondition(pool->pending_task_cond);
	SparkFree(pool->threads);
	SparkFree(pool);
	}

SPARKAPI SparkVoid SparkWaitThreadPool(SparkThreadPool pool) {
	SparkLockMutex(pool->pending_task_mutex);
	while (pool->pending_task_count > 0) {
		SparkWaitCondition(pool->pending_task_cond, pool->pending_task_mutex);
	}
	SparkUnlockMutex(pool->pending_task_mutex);
}

SPARKAPI SparkTaskHandle SparkAddTaskThreadPool(SparkThreadPool pool,
	SparkThreadFunction function,
	SparkHandle arg,
	SparkBool wait_on_update) {

	if (!pool || !function)
		return SPARK_NULL;

	SparkLockMutex(pool->mutex);
	if (pool->shutdown) {
		SparkUnlockMutex(pool->mutex);
		return SPARK_NULL;
	}
	SparkUnlockMutex(pool->mutex);

	SparkTaskHandle task = SparkAllocate(sizeof(struct SparkTaskT));
	if (task == SPARK_NULL)
		return SPARK_NULL;

	task->function = function;
	task->arg = arg;
	task->next = SPARK_NULL;
	task->wait_on_update = wait_on_update;

	SparkInitMutex(task->mutex);
	SparkInitCondition(task->cond);

	if (wait_on_update) {
		SparkLockMutex(pool->pending_task_mutex);
		pool->pending_task_count++;
		SparkUnlockMutex(pool->pending_task_mutex);
	}

	SparkLockMutex(pool->mutex);

	// Add the task to the queue
	if (!pool->task_queue_tail) {
		pool->task_queue_head = pool->task_queue_tail = task;
	}
	else {
		pool->task_queue_tail->next = task;
		pool->task_queue_tail = task;
	}

	SparkSignalCondition(pool->condition);
	SparkUnlockMutex(pool->mutex);

	return task;
}

SPARKAPI SparkVoid SparkAddShutdownCallbackThreadPool(
	SparkThreadPool pool, SparkThreadPoolShutdownCallback callback,
	SparkHandle arg) {
	if (!pool || !callback)
		return;

	SparkPushBackVector(pool->shutdown_callbacks, callback);
	SparkPushBackVector(pool->shutdown_callback_args, arg);
}

SPARKAPI SparkResult SparkWaitTask(SparkTaskHandle task) {
	if (task == SPARK_NULL)
		return SPARK_FAILURE;

	SparkLockMutex(task->mutex);
	while (!task->is_done) {
		SparkWaitCondition(task->cond, task->mutex);
	}
	SparkUnlockMutex(task->mutex);

	SparkTaskDestroy(task);

	return SPARK_SUCCESS;
}

SPARKAPI SparkBool SparkIsTaskDone(SparkTaskHandle task) {
	if (task == SPARK_NULL)
		return SPARK_FALSE;

	SparkLockMutex(task->mutex);
	SparkBool is_done = task->is_done;
	SparkUnlockMutex(task->mutex);

	return is_done;
}

SPARKAPI SparkVoid SparkTaskDestroy(SparkTaskHandle task) {
	if (!task)
		return;
	SparkDestroyMutex(task->mutex);
	SparkDestroyCondition(task->cond);
	SparkFree(task);
}

#pragma endregion

#pragma region NETWORKING

/* Platform-specific definitions */
#ifdef _WIN32
#define close closesocket
#define SOCKET_TYPE SOCKET
#else
#define SOCKET_TYPE SparkI32
#endif

/* Server and Client Structures */
struct SparkClientConnectionT {
	SOCKET_TYPE socket;
	struct sockaddr_in address;
	SparkServer server;
};

struct SparkServerT {
	SOCKET_TYPE listen_socket;
	SparkU16 port;
	SparkThreadPool thread_pool;
	SparkBool running;
	SparkMutex mutex;
	SparkVector clients; /* Vector of SparkClientConnection */
	SparkServerReceiveCallback receive_callback;
};

struct SparkClientT {
	SOCKET_TYPE socket;
	struct sockaddr_in server_address;
	SparkThreadPool thread_pool;
	SparkBool connected;
	SparkClientReceiveCallback receive_callback;
};

/* Utility functions for networking */
SPARKAPI SPARKSTATIC SparkResult __SparkInitNetworking() {
#ifdef _WIN32
	WSADATA wsa_data;
	int result;
	if ((result = WSAStartup(MAKEWORD(2, 2), &wsa_data)) != 0) {
		printf("WSAStartup failed: %d\n", result);
		return SPARK_FAILURE;
	}
#endif
	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkVoid __SparkCleanupNetworking() {
#ifdef _WIN32
	WSACleanup();
#endif
}

/* Serialize and Deserialize Envelopes */
SPARKAPI SparkResult SparkSerializeEnvelope(SparkEnvelope * envelope,
	SparkBuffer * buffer,
	SparkSize * size) {
	if (!envelope || !buffer || !size) {
		return SPARK_FAILURE;
	}

	SparkSize total_size =
		sizeof(SparkU32) + sizeof(SparkSize) + envelope->packet.size;
	*buffer = (SparkBuffer)SparkAllocate(total_size);
	if (!*buffer) {
		return SPARK_FAILURE;
	}

	SparkU32 type_net = htonl(envelope->type);
	SparkSize size_net = htonl(envelope->packet.size);

	memcpy(*buffer, &type_net, sizeof(SparkU32));
	memcpy(*buffer + sizeof(SparkU32), &size_net, sizeof(SparkSize));
	memcpy(*buffer + sizeof(SparkU32) + sizeof(SparkSize), envelope->packet.data,
		envelope->packet.size);

	*size = total_size;
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkDeserializeEnvelope(SparkBuffer buffer,
	SparkSize size,
	SparkEnvelope * envelope) {
	if (!buffer || !envelope || size < sizeof(SparkU32) + sizeof(SparkSize)) {
		return SPARK_FAILURE;
	}

	SparkU32 type_net;
	SparkSize size_net;
	memcpy(&type_net, buffer, sizeof(SparkU32));
	memcpy(&size_net, buffer + sizeof(SparkU32), sizeof(SparkSize));

	envelope->type = ntohl(type_net);
	envelope->packet.size = ntohl(size_net);

	if (size < sizeof(SparkU32) + sizeof(SparkSize) + envelope->packet.size) {
		return SPARK_FAILURE;
	}

	envelope->packet.data = (SparkBuffer)SparkAllocate(envelope->packet.size);
	if (!envelope->packet.data) {
		return SPARK_FAILURE;
	}

	memcpy(envelope->packet.data, buffer + sizeof(SparkU32) + sizeof(SparkSize),
		envelope->packet.size);
	return SPARK_SUCCESS;
}

/* Client Handler Function */
SPARKAPI SPARKSTATIC SparkHandle __SparkClientHandler(SparkHandle arg) {
	SparkClientConnection client = (SparkClientConnection)arg;
	SparkServer server = client->server;
	SparkI8 recv_buffer[SPARK_PACKET_MAX_SIZE];
	SparkI32 bytes_received;

	while (SPARK_TRUE) {
		bytes_received =
			recv(client->socket, recv_buffer, SPARK_PACKET_MAX_SIZE, 0);
		if (bytes_received > 0) {
			SparkEnvelope envelope;
			if (SparkDeserializeEnvelope((SparkBuffer)recv_buffer, bytes_received,
				&envelope) == SPARK_SUCCESS) {
				/* Call the receive callback */
				server->receive_callback(server, client, &envelope);
				/* Clean up envelope data */
				SparkFree(envelope.packet.data);
			}
		}
		else if (bytes_received == 0) {
			// Connection closed by the client
			break;
		}
		else {
#ifdef _WIN32
			SparkI32 error = WSAGetLastError();
			if (error == WSAEWOULDBLOCK) {
				// No data available, sleep briefly and continue
				Sleep(10);
				continue;
			}
			else {
				/* Failed to receive, could be for a multitude of reasons, probably the
				 * server shutting down */
				break;
			}
#else
			if (errno == EWOULDBLOCK || errno == EAGAIN) {
				// No data available, sleep briefly and continue
				usleep(10000);
				continue;
			}
			else {
				/* Failed to receive, could be for a multitude of reasons, probably the
				 * server shutting down */
				break;
			}
#endif
		}
	}

	///* Remove client from server's client list */
	// SparkLockMutex(server->mutex);
	// for (SparkSize i = 0; i < server->clients->size; ++i) {
	//	SparkClientConnection conn =
	//(SparkClientConnection)SparkGetElementVector(server->clients, i); 	if (conn
	//== client) { 		SparkRemoveVector(server->clients, i); 		break;
	//	}
	// }
	// SparkUnlockMutex(server->mutex);

	//// Clean up client resources
	// close(client->socket);
	// SparkFree(client);

	return SPARK_NULL;
}

/* Server Functions */
SPARKAPI SparkServer SparkCreateServer(SparkThreadPool tp, SparkU16 port,
	SparkServerReceiveCallback callback) {
	if (__SparkInitNetworking() != SPARK_SUCCESS) {
		return SPARK_NULL;
	}

	SparkServer server = (SparkServer)SparkAllocate(sizeof(struct SparkServerT));
	if (!server) {
		return SPARK_NULL;
	}

	server->port = port;
	server->running = SPARK_FALSE;
	server->receive_callback = callback;
	server->clients = SparkDefaultVector();

	SparkInitMutex(server->mutex);

	/* Create ThreadPool */
	server->thread_pool = tp;

	SparkAddShutdownCallbackThreadPool(
		server->thread_pool, (SparkThreadPoolShutdownCallback)SparkDestroyServer,
		server);

	return server;
}

SPARKAPI SparkVoid SparkDestroyServer(SparkServer server) {
	if (!server) {
		return;
	}

	SparkStopServer(server);
	SparkDestroyVector(server->clients);
	SparkDestroyMutex(server->mutex);
	SparkFree(server);

	__SparkCleanupNetworking();
}

SPARKAPI SPARKSTATIC SparkHandle __SparkAcceptConnections(SparkHandle arg) {
	SparkServer srv = (SparkServer)arg;
	while (srv->running) {
		struct sockaddr_in client_addr;
		socklen_t addr_len = sizeof(client_addr);
		SOCKET_TYPE client_socket =
			accept(srv->listen_socket, (struct sockaddr*)&client_addr, &addr_len);
		if (client_socket == -1) {
#ifdef _WIN32
			SparkI32 error = WSAGetLastError();
			if (error == WSAEWOULDBLOCK || error == WSAEINTR) {
				// No incoming connection, sleep briefly and continue
				Sleep(10); // Sleep for 10 milliseconds
				continue;
			}
			else {
				/* Failed to accept, could be for a multitude of reasons, probably the
				 * server shutting down */
				break;
			}
#else
			if (errno == EWOULDBLOCK || errno == EAGAIN || errno == EINTR) {
				// No incoming connection, sleep briefly and continue
				usleep(10000); // Sleep for 10 milliseconds
				continue;
			}
			else {
				/* Failed to accept, could be for a multitude of reasons, probably the
				 * server shutting down */
				break;
			}
#endif
		}
		// Handle the new client connection
		SparkClientConnection client = (SparkClientConnection)SparkAllocate(
			sizeof(struct SparkClientConnectionT));
		client->socket = client_socket;
		client->address = client_addr;
		client->server = srv;

		/* Add client to server's client list */
		SparkLockMutex(srv->mutex);
		SparkPushBackVector(srv->clients, client);
		SparkUnlockMutex(srv->mutex);

		/* Handle client in a separate thread */
		SparkAddTaskThreadPool(srv->thread_pool, __SparkClientHandler, client,
			SPARK_FALSE);
	}
	return SPARK_NULL;
}

SPARKAPI SparkResult SparkStartServer(SparkServer server) {
	if (!server) {
		return SPARK_FAILURE;
	}

	SOCKET_TYPE listen_socket;
	struct sockaddr_in server_addr;

	/* Create socket */
	/* Create socket */
	if ((listen_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket creation failed");
		return SPARK_FAILURE;
	}

	/* Set socket to non-blocking mode */
#ifdef _WIN32
	u_long mode = 1; // 1 to enable non-blocking socket
	ioctlsocket(listen_socket, FIONBIO, &mode);
#else
	SparkI32 flags = fcntl(listen_socket, F_GETFL, 0);
	fcntl(listen_socket, F_SETFL, flags | O_NONBLOCK);
#endif

	/* Set socket options */
	SparkI32 opt = 1;
	if (
#ifdef _WIN32
		setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, (SparkString)&opt,
			sizeof(opt))
#else
		setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
			sizeof(opt))
#endif
		< 0) {
		perror("Setsockopt failed");
		return SPARK_FAILURE;
	}

	/* Bind socket */
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(server->port);
	memset(&(server_addr.sin_zero), 0, 8);

	if (bind(listen_socket, (struct sockaddr*)&server_addr,
		sizeof(server_addr)) < 0) {
		perror("Bind failed");
		return SPARK_FAILURE;
	}

	/* Listen */
	if (listen(listen_socket, 5) < 0) {
		perror("Listen failed");
		return SPARK_FAILURE;
	}

	server->listen_socket = listen_socket;
	server->running = SPARK_TRUE;

	/* Accept connections in a separate thread */
	SparkAddTaskThreadPool(server->thread_pool, __SparkAcceptConnections, server,
		SPARK_FALSE);

	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkStopServer(SparkServer server) {
	if (!server) {
		return SPARK_FAILURE;
	}

	server->running = SPARK_FALSE;
	close(server->listen_socket);

	/* Close all client connections */
	SparkLockMutex(server->mutex);
	for (SparkSize i = 0; i < server->clients->size; ++i) {
		SparkClientConnection client =
			(SparkClientConnection)SparkGetElementVector(server->clients, i);
		close(client->socket);
	}
	SparkUnlockMutex(server->mutex);

	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkSendToClient(SparkServer server,
	SparkClientConnection client,
	SparkEnvelope * envelope) {
	if (!server || !client || !envelope) {
		return SPARK_FAILURE;
	}

	SparkBuffer buffer;
	SparkSize size;
	if (SparkSerializeEnvelope(envelope, &buffer, &size) != SPARK_SUCCESS) {
		return SPARK_FAILURE;
	}

	SparkI32 bytes_sent = send(client->socket, buffer, size, 0);
	SparkFree(buffer);
	if (bytes_sent < 0) {
		perror("Send to client failed");
		return SPARK_FAILURE;
	}

	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkBroadcast(SparkServer server,
	SparkEnvelope * envelope) {
	if (!server || !envelope) {
		return SPARK_FAILURE;
	}

	SparkLockMutex(server->mutex);
	for (SparkSize i = 0; i < server->clients->size; ++i) {
		SparkClientConnection client =
			(SparkClientConnection)SparkGetElementVector(server->clients, i);
		SparkSendToClient(server, client, envelope);
	}
	SparkUnlockMutex(server->mutex);

	return SPARK_SUCCESS;
}

/* Client Receive Handler */
SPARKAPI SPARKSTATIC SparkHandle __SparkClientReceiveHandler(SparkHandle arg) {
	SparkClient client = (SparkClient)arg;
	SparkI8 recv_buffer[SPARK_PACKET_MAX_SIZE];
	SparkI32 bytes_received;

	while ((bytes_received = recv(client->socket, recv_buffer,
		SPARK_PACKET_MAX_SIZE, 0)) > 0) {
		SparkEnvelope envelope;
		if (SparkDeserializeEnvelope((SparkBuffer)recv_buffer, bytes_received,
			&envelope) == SPARK_SUCCESS) {
			/* Call the receive callback */
			client->receive_callback(client, &envelope);
			/* Clean up envelope data */
			SparkFree(envelope.packet.data);
		}
	}

	if (bytes_received == 0) {
		// Connection closed by the server
		printf("Server has closed the connection.\n");
	}
	else if (bytes_received < 0) {
		// An error occurred
		perror("recv failed");
	}

	client->connected = SPARK_FALSE;
	close(client->socket);
	return SPARK_NULL;
}

/* Client Functions */
SPARKAPI SparkClient SparkCreateClient(SparkThreadPool tp,
	SparkConstString address, SparkU16 port,
	SparkClientReceiveCallback callback) {
	if (__SparkInitNetworking() != SPARK_SUCCESS) {
		return SPARK_NULL;
	}

	SparkClient client = (SparkClient)SparkAllocate(sizeof(struct SparkClientT));
	if (!client) {
		return SPARK_NULL;
	}

	client->connected = SPARK_FALSE;
	client->receive_callback = callback;

	memset(&client->server_address, 0, sizeof(client->server_address));
	client->server_address.sin_family = AF_INET;
	client->server_address.sin_port = htons(port);

#ifdef _WIN32
	// Use InetPtonA to handle ANSI strings explicitly
	if (InetPtonA(AF_INET, address, &client->server_address.sin_addr) <= 0) {
		SPARK_LOG_ERROR(
			"Invalid address / Address not supported\n");
		SPARK_LOG_ERROR("InetPtonA failed with error: %d\n",
			WSAGetLastError()); // Detailed error
		SparkFree(client);
		return SPARK_NULL;
	}
#else
	if (inet_pton(AF_INET, address, &client->server_address.sin_addr) <= 0) {
		perror("inet_pton failed");
		SparkFree(client);
		return SPARK_NULL;
	}
#endif

	/* Create ThreadPool */
	client->thread_pool = tp;

	return client;
}

SPARKAPI SparkVoid SparkDestroyClient(SparkClient client) {
	if (!client) {
		return;
	}

	SparkDisconnectClient(client);
	SparkFree(client);

	__SparkCleanupNetworking();
}

SPARKAPI SparkResult SparkConnectClient(SparkClient client) {
	if (!client) {
		return SPARK_FAILURE;
	}

	SOCKET_TYPE sockfd;
	/* Create socket */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket creation failed");
		return SPARK_FAILURE;
	}

	/* Connect to server */
	if (connect(sockfd, (struct sockaddr*)&client->server_address,
		sizeof(client->server_address)) < 0) {
		perror("Connection Failed");
		return SPARK_FAILURE;
	}

	client->socket = sockfd;
	client->connected = SPARK_TRUE;

	/* Start receiving data in a separate thread */
	SparkAddTaskThreadPool(client->thread_pool, __SparkClientReceiveHandler,
		client, SPARK_FALSE);

	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkDisconnectClient(SparkClient client) {
	if (!client || !client->connected) {
		return SPARK_FAILURE;
	}

	client->connected = SPARK_FALSE;
	close(client->socket);
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkSendToServer(SparkClient client,
	SparkEnvelope * envelope) {
	if (!client || !envelope || !client->connected) {
		return SPARK_FAILURE;
	}

	SparkBuffer buffer;
	SparkSize size;
	if (SparkSerializeEnvelope(envelope, &buffer, &size) != SPARK_SUCCESS) {
		return SPARK_FAILURE;
	}

	SparkI32 bytes_sent = send(client->socket, buffer, size, 0);
	SparkFree(buffer);
	if (bytes_sent < 0) {
		perror("Send to server failed");
		return SPARK_FAILURE;
	}

	return SPARK_SUCCESS;
}

#pragma endregion

#pragma region ECS

#define MAX_COMPONENT_TYPES 64
static SparkHashMap COMPONENT_BITS = NULL;

SPARKAPI SparkVector SparkPerformQuery(SparkEcs ecs, SparkQuery query) {
	// Check if query result is cached
	for (SparkSize i = 0; i < ecs->query_caches->size; ++i) {
		SparkQueryCache cache = ecs->query_caches->elements[i];
		if (cache->query->signature == query->signature && cache->version == ecs->version)
			return cache->entities; // Return cached result
	}

	// Perform the query
	SparkVector matching_entities = SparkCreateVector(ecs->entity_count, SPARK_NULL, SPARK_NULL);
	for (SparkEntity entity = 0; entity < ecs->entity_count; ++entity) {
		if ((ecs->signatures[entity] & query->signature) == query->signature) {
			SparkPushBackVector(matching_entities, (SparkHandle)(uintptr_t)entity);
		}
	}

	// Cache the result
	SparkQueryCache new_cache = SparkAllocate(sizeof(struct SparkQueryCacheT));
	new_cache->query = query;
	new_cache->entities = matching_entities;
	new_cache->version = ecs->version;
	SparkPushBackVector(ecs->query_caches, new_cache);

	return matching_entities;
}

SPARKAPI SparkU64 GetComponentBit(SparkConstString component_type) {
	static SparkU64 next_bit = 1;

	if (!COMPONENT_BITS)
		COMPONENT_BITS = SparkCreateHashMap(16, SparkStringHash, SparkStringCompare, NULL, NULL, NULL);

	SparkU64 bit = SparkGetElementHashMap(COMPONENT_BITS, (SparkHandle)component_type, strlen(component_type));
	if (bit)
		return bit;

	SparkU64 new_bit = next_bit;
	next_bit <<= 1;

	SparkInsertHashMap(COMPONENT_BITS, (SparkHandle)component_type, strlen(component_type), new_bit);

	return new_bit;
}

SPARKAPI SparkVoid SparkInvalidateQueryCaches(SparkEcs ecs) {
	for (SparkSize i = 0; i < ecs->query_caches->size; ++i) {
		SparkQueryCache cache = ecs->query_caches->elements[i];
		SparkDestroyVector(cache->entities);
		SparkFree(cache);
	}
	SparkClearVector(ecs->query_caches);
}

SPARKAPI SparkQuery SparkCreateQuery(SparkConstString * component_types, SparkSize component_count) {
	SparkQuery query = SparkAllocate(sizeof(struct SparkQueryT));
	query->signature = 0;
	for (SparkSize i = 0; i < component_count; ++i) {
		query->signature |= GetComponentBit(component_types[i]);
	}
	return query;
}

SPARKAPI SparkComponentArray SparkCreateComponentArray(SparkSize initial_sparse_capacity) {
	SparkComponentArray array = SparkAllocate(sizeof(struct SparkComponentArrayT));
	array->dense = SparkAllocate(sizeof(SparkComponent) * 16); // Initial dense capacity
	array->entities = SparkAllocate(sizeof(SparkEntity) * 16);
	array->dense_capacity = 16;
	array->sparse = SparkAllocate(sizeof(SparkSize) * initial_sparse_capacity);
	array->sparse_capacity = initial_sparse_capacity;
	array->size = 0;
	for (SparkSize i = 0; i < initial_sparse_capacity; ++i)
		array->sparse[i] = INVALID_INDEX;
	return array;
}

SPARKAPI SparkVoid __SparkDestroyComponentArray(SparkHandle handle) {
	SparkComponentArray arr = (SparkComponentArray)handle;
	if (!arr)
		return;

	// Destroy components
	for (SparkSize i = 0; i < arr->size; ++i) {
		if (arr->dense[i]->destructor)
			arr->dense[i]->destructor(arr->dense[i]->data);
		SparkFree(arr->dense[i]);
	}

	SparkFree(arr->dense);
	SparkFree(arr->entities);
	SparkFree(arr->sparse);
	SparkFree(arr);
}

SPARKAPI SparkVoid __SparkDestroyQueryCache(SparkQueryCache query_cache)
{
	SparkFree(query_cache->query);
	SparkDestroyVector(query_cache->entities);
	SparkFree(query_cache);
}

SPARKAPI SparkEcs SparkCreateEcs(SparkEventHandler event_handler) {
	SparkEcs ecs = SparkAllocate(sizeof(struct SparkEcsT));
	if (!ecs)
		return SPARK_NULL;

	ecs->allocator = SparkDefaultAllocator();
	ecs->entities = SparkCreateVector(16, ecs->allocator, SparkFree);
	ecs->systems = SparkCreateVector(8, ecs->allocator, SPARK_NULL);
	ecs->recycled_ids = SparkCreateStack(16, ecs->allocator, SPARK_NULL);
	ecs->components = SparkCreateHashMap(
		16, SparkStringHash, SparkStringCompare, ecs->allocator,
		SPARK_NULL, // No key destructor needed for string literals
		__SparkDestroyComponentArray // Value destructor for component arrays
	);
	ecs->event_handler = event_handler;
	ecs->signatures = SparkAllocate(sizeof(SparkSignature));
	ecs->entity_count = 0;
	ecs->version = 0;
	ecs->query_caches = SparkCreateVector(4, ecs->allocator, __SparkDestroyQueryCache);
	return ecs;
}

SPARKAPI SparkVoid SparkDestroyEcs(SparkEcs ecs) {
	if (!ecs)
		return;

	SparkStopEcs(ecs);
	SparkDestroyHashMap(ecs->components);
	SparkDestroyVector(ecs->entities);
	SparkDestroyVector(ecs->systems);
	SparkDestroyStack(ecs->recycled_ids);
	SparkDestroyVector(ecs->query_caches);
	SparkFree(ecs->signatures);
	SparkDestroyAllocator(ecs->allocator);
	SparkFree(ecs);
	SparkDestroyHashMap(COMPONENT_BITS);
}

SPARKAPI SparkEntity SparkCreateEntity(SparkEcs ecs) {
	if (!ecs)
		return SPARK_INVALID;

	SparkEntity entity_id;
	if (ecs->recycled_ids->size > 0) {
		entity_id = (SparkEntity)(intptr_t)SparkGetTopStack(ecs->recycled_ids);
		SparkPopStack(ecs->recycled_ids);
	}
	else {
		entity_id = ecs->entities->size;
	}

	// Ensure capacity for signatures
	if (entity_id >= ecs->entity_count) {
		ecs->entity_count = entity_id + 1;
		ecs->signatures = SparkReallocate(ecs->signatures, sizeof(SparkSignature) * ecs->entity_count);
		ecs->signatures[entity_id] = 0;

		// Resize sparse arrays in component arrays
		SparkHashMapIterator iterator = SparkCreateHashMapIterator(SPARK_ITERATOR_STATE_BEGIN, SPARK_HASHMAP_ITERATOR_TYPE_VALUE, ecs->components);
		while (SparkHasNextHashMapIterator(iterator)) {
			SparkIterateForwardHashMapIterator(iterator);
			SparkComponentArray component_array = (SparkComponentArray)SparkGetCurrentHashMapIterator(iterator);

			if (ecs->entity_count > component_array->sparse_capacity) {
				SparkSize new_capacity = ecs->entity_count;
				component_array->sparse = SparkReallocate(component_array->sparse, sizeof(SparkSize) * new_capacity);
				for (SparkSize i = component_array->sparse_capacity; i < new_capacity; ++i)
					component_array->sparse[i] = INVALID_INDEX;
				component_array->sparse_capacity = new_capacity;
			}
		}
		SparkDestroyHashMapIterator(iterator);
	}

	SparkEntity* entity = ecs->allocator->allocate(sizeof(SparkEntity));
	if (!entity)
		return SPARK_INVALID;

	*entity = entity_id;
	SparkPushBackVector(ecs->entities, entity);

	SparkEventDataEntityCreated event_data = SparkAllocate(sizeof(struct SparkEventDataEntityCreatedT));
	event_data->ecs = ecs;
	event_data->entity = entity_id;

	SparkEvent event = SparkCreateEvent(SPARK_EVENT_ENTITY_CREATED, event_data, SparkFree);
	SparkDispatchEvent(ecs->event_handler, event);

	return entity_id;
}

SPARKAPI SparkResult SparkDestroyEntity(SparkEcs ecs, SparkEntity entity_id) {
	if (!ecs || entity_id == SPARK_INVALID)
		return SPARK_ERROR_INVALID_ARGUMENT;

	SparkRemoveAllEntityComponents(ecs, entity_id);
	for (SparkSize i = 0; i < ecs->entities->size; ++i) {
		SparkEntity* entity = (SparkEntity*)SparkGetElementVector(ecs->entities, i);
		if (*entity == entity_id) {
			SparkRemoveVector(ecs->entities, i);
			break;
		}
	}

	SparkPushStack(ecs->recycled_ids, (SparkHandle)(intptr_t)entity_id);
	ecs->signatures[entity_id] = 0;
	ecs->version++;

	// Dispatch event
	SparkEventDataEntityDestroyed event_data = SparkAllocate(sizeof(struct SparkEventDataEntityDestroyedT));
	event_data->ecs = ecs;
	event_data->entity = entity_id;

	SparkEvent event = SparkCreateEvent(SPARK_EVENT_ENTITY_DESTROYED, event_data, SparkFree);
	SparkDispatchEvent(ecs->event_handler, event);

	return SPARK_SUCCESS;
}

SPARKAPI SparkComponent SparkCreateComponent(SparkConstString type,
	SparkConstString name,
	SparkHandle data,
	SparkFreeFunction destructor) {
	if (!type)
		return SPARK_NULL;
	SparkComponent component =
		(SparkComponent)SparkAllocate(sizeof(struct SparkComponentT));
	if (!component)
		return SPARK_NULL;
	component->type = type;
	component->name = name;
	component->data = data;
	component->destructor = destructor;
	return component;
}

SPARKAPI SparkResult SparkAddComponent(SparkEcs ecs, SparkEntity entity_id, SparkComponent component) {
	if (!ecs || !component || entity_id == SPARK_INVALID)
		return SPARK_ERROR_INVALID_ARGUMENT;

	component->entity = entity_id;

	// Get or create component array
	SparkComponentArray component_array = SparkGetElementHashMap(
		ecs->components,
		(SparkHandle)component->type,
		strlen(component->type)
	);

	if (!component_array) {
		component_array = SparkCreateComponentArray(ecs->entity_count);
		if (!component_array)
			return SPARK_ERROR_OUT_OF_MEMORY;

		SparkInsertHashMap(ecs->components, (SparkHandle)component->type, strlen(component->type), component_array);
	}

	// Ensure the sparse array can accommodate entity_id
	if (entity_id >= component_array->sparse_capacity) {
		// Resize the sparse array
		SparkSize new_capacity = entity_id + 1;
		component_array->sparse = SparkReallocate(component_array->sparse, sizeof(SparkSize) * new_capacity);
		for (SparkSize i = component_array->sparse_capacity; i < new_capacity; ++i)
			component_array->sparse[i] = INVALID_INDEX;
		component_array->sparse_capacity = new_capacity;
	}

	if (component_array->sparse[entity_id] != INVALID_INDEX)
		return SPARK_ERROR_INVALID;

	// Resize dense arrays if necessary
	if (component_array->size >= component_array->dense_capacity) {
		component_array->dense_capacity *= 2;
		component_array->dense = SparkReallocate(component_array->dense, sizeof(SparkComponent) * component_array->dense_capacity);
		component_array->entities = SparkReallocate(component_array->entities, sizeof(SparkEntity) * component_array->dense_capacity);
	}

	// Add component to dense array
	SparkSize index = component_array->size++;
	component_array->dense[index] = component;
	component_array->entities[index] = entity_id;
	component_array->sparse[entity_id] = index;

	// Update entity's signature
	ecs->signatures[entity_id] |= GetComponentBit(component->type);
	ecs->version++; // Increment ECS version
	SparkInvalidateQueryCaches(ecs); // Invalidate outdated caches

	SparkEventDataComponentAdded event_data = SparkAllocate(sizeof(struct SparkEventDataComponentAddedT));
	event_data->ecs = ecs;
	event_data->entity = entity_id;
	event_data->component = component;

	SparkEvent event = SparkCreateEvent(SPARK_EVENT_COMPONENT_ADDED, event_data, SparkFree);
	SparkDispatchEvent(ecs->event_handler, event);

	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkRemoveComponent(SparkEcs ecs, SparkEntity entity_id, SparkConstString component_type, SparkConstString component_name) {
	if (!ecs || !component_type || entity_id == SPARK_INVALID)
		return SPARK_ERROR_INVALID_ARGUMENT;

	SparkComponentArray component_array = (SparkComponentArray)SparkGetElementHashMap(
		ecs->components,
		(SparkHandle)component_type,
		strlen(component_type)
	);

	if (!component_array)
		return SPARK_ERROR_NOT_FOUND;

	if (entity_id >= component_array->sparse_capacity)
		return SPARK_ERROR_NOT_FOUND;

	SparkSize index = component_array->sparse[entity_id];
	if (index == INVALID_INDEX)
		return SPARK_ERROR_NOT_FOUND;

	// Swap with last component
	SparkSize last_index = component_array->size - 1;
	if (index != last_index) {
		component_array->dense[index] = component_array->dense[last_index];
		component_array->entities[index] = component_array->entities[last_index];
		component_array->sparse[component_array->entities[index]] = index;
	}

	component_array->sparse[entity_id] = INVALID_INDEX;
	component_array->size--;

	// Update entity's signature
	ecs->signatures[entity_id] &= ~GetComponentBit(component_type);
	ecs->version++; // Increment ECS version
	SparkInvalidateQueryCaches(ecs); // Invalidate outdated caches

	// Destroy the component
	SparkComponent component_to_destroy = component_array->dense[last_index];
	if (component_to_destroy->destructor)
		component_to_destroy->destructor(component_to_destroy->data);

	SparkFree(component_to_destroy);

	SparkEventDataComponentRemoved event_data = SparkAllocate(sizeof(struct SparkEventDataComponentRemovedT));
	event_data->ecs = ecs;
	event_data->entity = entity_id;
	event_data->type = component_type;
	event_data->name = component_name;

	SparkEvent event = SparkCreateEvent(SPARK_EVENT_COMPONENT_REMOVED, event_data, SparkFree);
	SparkDispatchEvent(ecs->event_handler, event);

	return SPARK_SUCCESS;
}

SPARKAPI SparkComponent SparkGetComponent(SparkEcs ecs, SparkEntity entity_id, SparkConstString component_type, SparkConstString component_name) {
	if (!ecs || !component_type || entity_id == SPARK_INVALID)
		return SPARK_NULL;

	SparkComponentArray component_array = (SparkComponentArray)SparkGetElementHashMap(
		ecs->components,
		(SparkHandle)component_type,
		strlen(component_type)
	);

	if (!component_array)
		return SPARK_NULL;

	if (entity_id >= component_array->sparse_capacity)
		return SPARK_NULL;

	SparkSize index = component_array->sparse[entity_id];
	if (index == INVALID_INDEX)
		return SPARK_NULL;

	SparkComponent component = component_array->dense[index];
	return component;
}

SPARKAPI SparkResult SparkAddSystem(SparkEcs ecs, SparkSystem system) {
	if (!ecs || !system)
		return SPARK_ERROR_INVALID_ARGUMENT;
	SparkPushBackVector(ecs->systems, system);
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkRemoveSystem(SparkEcs ecs, SparkSystem system) {
	if (!ecs || !system)
		return SPARK_ERROR_INVALID_ARGUMENT;
	for (SparkSize i = 0; i < ecs->systems->size; ++i) {
		if (SparkGetElementVector(ecs->systems, i) == system) {
			SparkRemoveVector(ecs->systems, i);
			return SPARK_SUCCESS;
		}
	}
	return SPARK_ERROR_NOT_FOUND;
}

SPARKAPI SparkResult SparkStartEcs(SparkEcs ecs) {
	if (!ecs)
		return SPARK_ERROR_INVALID_ARGUMENT;
	for (SparkSize i = 0; i < ecs->systems->size; ++i) {
		SparkSystem system = (SparkSystem)SparkGetElementVector(ecs->systems, i);
		if (system->start) {
			SparkResult res = system->start(ecs);
			if (res != SPARK_SUCCESS) {
				return res;
			}
		}
	}
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkUpdateEcs(SparkEcs ecs, SparkF32 delta) {
	if (!ecs)
		return SPARK_ERROR_INVALID_ARGUMENT;
	for (SparkSize i = 0; i < ecs->systems->size; ++i) {
		SparkSystem system = (SparkSystem)SparkGetElementVector(ecs->systems, i);
		if (system->update) {
			SparkResult res = system->update(ecs, delta);
			if (res != SPARK_SUCCESS) {
				return res;
			}
		}
	}
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkStopEcs(SparkEcs ecs) {
	if (!ecs)
		return SPARK_ERROR_INVALID_ARGUMENT;
	for (SparkSize i = 0; i < ecs->systems->size; ++i) {
		SparkSystem system = (SparkSystem)SparkGetElementVector(ecs->systems, i);
		if (system->stop) {
			SparkResult res = system->stop(ecs);
			if (res != SPARK_SUCCESS) {
				return res;
			}
		}
	}
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkRemoveAllEntityComponents(SparkEcs ecs, SparkEntity entity_id) {
	if (!ecs || entity_id == SPARK_INVALID)
		return SPARK_ERROR_INVALID_ARGUMENT;

	SparkHashMapIterator iterator = SparkCreateHashMapIterator(SPARK_ITERATOR_STATE_BEGIN, SPARK_HASHMAP_ITERATOR_TYPE_VALUE, ecs->components);

	while (SparkHasNextHashMapIterator(iterator)) {
		SparkIterateForwardHashMapIterator(iterator);
		SparkComponentArray component_array = (SparkComponentArray)SparkGetCurrentHashMapIterator(iterator);

		SparkSize index = component_array->sparse[entity_id];
		if (index != INVALID_INDEX) {
			SparkConstString component_type = (SparkConstString)iterator->hash_map->buckets[iterator->pos]->key;
			SparkRemoveComponent(ecs, entity_id, component_type, SPARK_NULL);
		}
	}

	SparkDestroyHashMapIterator(iterator);
	return SPARK_SUCCESS;
}

SPARKAPI SparkVector SparkGetAllComponentsByType(SparkEcs ecs, SparkConstString component_type) {
	if (!ecs || !component_type)
		return SPARK_NULL;

	SparkComponentArray component_array = (SparkComponentArray)SparkGetElementHashMap(
		ecs->components,
		(SparkHandle)component_type,
		strlen(component_type)
	);

	if (!component_array)
		return SPARK_NULL;

	return SparkMemcpyIntoVector(component_array->size, component_array->dense, SPARK_NULL, SPARK_NULL);
}

#pragma endregion

#pragma region COMPONENT

SPARKAPI SparkComponent SPARKCALL SparkDefaultTransformComponent(SparkConstString name) {
	SparkTransformComponent tcomp = SparkAllocate(sizeof(struct SparkTransformComponentT));
	tcomp->position = SPARK_DEFAULT_POSITION;
	tcomp->rotation = SPARK_DEFAULT_ROTATION;
	tcomp->scale = SPARK_DEFAULT_SCALE;

	return SparkCreateComponent(SPARK_TRANSFORM_COMPONENT, name, tcomp, SparkDestroyTransformComponent);
}

SPARKAPI SparkComponent SPARKCALL SparkCreateTransformComponent(SparkConstString name, SparkVec3 pos, SparkQuat rot, SparkVec3 scale) {
	SparkTransformComponent tcomp = SparkAllocate(sizeof(struct SparkTransformComponentT));
	tcomp->position = pos;
	tcomp->rotation = rot;
	tcomp->scale = scale;

	return SparkCreateComponent(SPARK_TRANSFORM_COMPONENT, name, tcomp, SparkDestroyTransformComponent);
}

SPARKAPI SparkComponent SPARKCALL SparkCreateTransformComponentPos(SparkConstString name, SparkVec3 pos) {
	SparkTransformComponent tcomp = SparkAllocate(sizeof(struct SparkTransformComponentT));
	tcomp->position = pos;
	tcomp->rotation = (SparkQuat){ 0.0f, 0.0f, 0.0f, 1.0f };
	tcomp->scale = (SparkVec3){ 1.0f, 1.0f, 1.0f };

	return SparkCreateComponent(SPARK_TRANSFORM_COMPONENT, name, tcomp, SparkDestroyTransformComponent);
}

SPARKAPI SparkComponent SPARKCALL SparkCreateTransformComponentRot(SparkConstString name, SparkVec3 pos, SparkQuat rot) {
	SparkTransformComponent tcomp = SparkAllocate(sizeof(struct SparkTransformComponentT));
	tcomp->position = pos;
	tcomp->rotation = rot;
	tcomp->scale = (SparkVec3){ 1.0f, 1.0f, 1.0f };

	return SparkCreateComponent(SPARK_TRANSFORM_COMPONENT, name, tcomp, SparkDestroyTransformComponent);
}

SPARKAPI SparkVoid SPARKCALL SparkDestroyTransformComponent(SparkTransformComponent comp) {
	SparkFree(comp);
}

SPARKAPI SparkComponent SPARKCALL SparkCreateStaticModelComponent(SparkConstString name, SparkConstString model_name) {
	SparkDynamicModelComponent mcomp = SparkAllocate(sizeof(struct SparkStaticModelComponentT));
	mcomp->model_name = model_name;

	return SparkCreateComponent(SPARK_STATIC_MODEL_COMPONENT, name, mcomp, SparkDestroyStaticModelComponent);
}

SPARKAPI SparkVoid SPARKCALL SparkDestroyStaticModelComponent(SparkStaticModelComponent comp) {
	SparkFree(comp);
}

SPARKAPI SparkComponent SPARKCALL SparkCreateDynamicModelComponent(SparkConstString name, SparkConstString model_name) {
	SparkDynamicModelComponent mcomp = SparkAllocate(sizeof(struct SparkDynamicModelComponentT));
	mcomp->model_name = model_name;

	return SparkCreateComponent(SPARK_DYNAMIC_MODEL_COMPONENT, name, mcomp, SparkDestroyDynamicModelComponent);
}

SPARKAPI SparkVoid SPARKCALL SparkDestroyDynamicModelComponent(SparkDynamicModelComponent comp) {
	SparkFree(comp);
}


#pragma endregion

#pragma region VULKAN

#ifdef NDEBUG
const SparkBool ENABLE_VALIDATION_LAYERS = SPARK_FALSE;
#else
const SparkBool ENABLE_VALIDATION_LAYERS = SPARK_TRUE;
#endif

const SparkConstString VALIDATION_LAYERS[] = { "VK_LAYER_KHRONOS_validation" };

const SparkConstString DEVICE_EXTENSIONS[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

const VkDynamicState DYNAMIC_STATES[] = { VK_DYNAMIC_STATE_VIEWPORT,
										 VK_DYNAMIC_STATE_SCISSOR };


const SparkI32 MAX_FRAMES_IN_FLIGHT = 3;

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

typedef struct VulkanMemoryAllocationT {
	VkDevice device;
	VkBuffer buffer;
	VkDeviceMemory memory;
	SparkHandle raw_data;
	SparkU32 size;
} *VulkanMemoryAllocation;

struct VulkanUniformBufferObject {
	SparkMat4 model;
	SparkMat4 view;
	SparkMat4 proj;
};

SPARKAPI SPARKSTATIC VkCommandBuffer __SparkBeginSingleTimeCommands(SparkWindow window) {
	VkCommandBufferAllocateInfo alloc_info = { 0 };
	alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	alloc_info.commandPool = window->command_pool;
	alloc_info.commandBufferCount = 1;

	VkCommandBuffer command_buffer;
	vkAllocateCommandBuffers(window->device, &alloc_info, &command_buffer);

	VkCommandBufferBeginInfo begin_info = { 0 };
	begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(command_buffer, &begin_info);

	return command_buffer;
}

SPARKAPI SPARKSTATIC SparkVoid __SparkEndSingleTimeCommands(SparkWindow window, VkCommandBuffer command_buffer) {
	vkEndCommandBuffer(command_buffer);

	VkSubmitInfo submit_info = { 0 };
	submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submit_info.commandBufferCount = 1;
	submit_info.pCommandBuffers = &command_buffer;

	vkQueueSubmit(window->graphics_queue, 1, &submit_info, VK_NULL_HANDLE);
	vkQueueWaitIdle(window->graphics_queue);

	vkFreeCommandBuffers(window->device, window->command_pool, 1, &command_buffer);
}

/*
* input_rate: VK_VERTEX_INPUT_RATE_VERTEX or VK_VERTEX_INPUT_RATE_INSTANCE
*/
SPARKAPI SPARKSTATIC VkVertexInputBindingDescription __SparkGetBindingDescription(VkVertexInputRate input_rate) {
	VkVertexInputBindingDescription binding_description = { 0 };
	binding_description.binding = 0;
	binding_description.stride = sizeof(SparkVertex);
	binding_description.inputRate = input_rate;
	return binding_description;
}

SPARKAPI SPARKSTATIC VkVertexInputAttributeDescription* __SparkGetAttributeDescriptions() {
	VkVertexInputAttributeDescription* attribute_descriptions =
		SparkAllocate(3 * sizeof(VkVertexInputAttributeDescription));

	attribute_descriptions[0].binding = 0;
	attribute_descriptions[0].location = 0;
	attribute_descriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
	attribute_descriptions[0].offset = offsetof(SparkVertex, position);

	attribute_descriptions[1].binding = 0;
	attribute_descriptions[1].location = 1;
	attribute_descriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	attribute_descriptions[1].offset = offsetof(SparkVertex, normal);

	attribute_descriptions[2].binding = 0;
	attribute_descriptions[2].location = 2;
	attribute_descriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
	attribute_descriptions[2].offset = offsetof(SparkVertex, texcoord);

	return attribute_descriptions;
}

SPARKAPI SPARKSTATIC SparkBool
__SparkIndicesComplete(struct VulkanQueueFamilyIndices* indices) {
	return indices->valid_graphics && indices->valid_present;
}

SPARKAPI SPARKSTATIC SparkBool __SparkCheckValidationLayerSupport() {
	SparkU32 layer_count;
	vkEnumerateInstanceLayerProperties(&layer_count, SPARK_NULL);

	VkLayerProperties* available_layers =
		SparkAllocate(layer_count * sizeof(VkLayerProperties));
	vkEnumerateInstanceLayerProperties(&layer_count, available_layers);

	for (SparkU32 i = 0; i < sizeof(VALIDATION_LAYERS) / sizeof(SparkConstString);
		i++) {
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
	SparkConstString* glfw_extensions =
		glfwGetRequiredInstanceExtensions(&glfw_extension_count);

	SparkU32 extension_count = glfw_extension_count;
	if (ENABLE_VALIDATION_LAYERS) {
		extension_count++;
	}

	SparkConstString* extensions =
		SparkAllocate(extension_count * sizeof(SparkConstString));
	for (SparkU32 i = 0; i < glfw_extension_count; i++) {
		extensions[i] = glfw_extensions[i];
	}

	if (ENABLE_VALIDATION_LAYERS) {
		extensions[glfw_extension_count] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
	}

	return (struct VulkanExtensions) { extension_count, extensions };
}

SPARKAPI SPARKSTATIC struct VulkanQueueFamilyIndices
__SparkFindQueueFamilies(SparkWindow window, VkPhysicalDevice device) {
	struct VulkanQueueFamilyIndices indices = { 0 };

	SparkU32 queue_family_count = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count,
		SPARK_NULL);

	VkQueueFamilyProperties* queue_families =
		SparkAllocate(queue_family_count * sizeof(VkQueueFamilyProperties));
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count,
		queue_families);

	for (SparkU32 i = 0; i < queue_family_count; i++) {
		if (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphics_family = i;
			indices.valid_graphics = SPARK_TRUE;
		}

		VkBool32 present_support = SPARK_FALSE;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, window->surface,
			&present_support);
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

SPARKAPI SPARKSTATIC VKAPI_ATTR SparkBool VKAPI_CALL
__SparkDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
	VkDebugUtilsMessageTypeFlagsEXT message_type,
	const VkDebugUtilsMessengerCallbackDataEXT * callback_data,
	SparkHandle user_data) {
	if (message_severity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
		SPARK_LOG_ERROR(callback_data->pMessage);
	}
	else {
		SPARK_LOG_INFO(callback_data->pMessage);
	}
	return VK_FALSE;
}

SPARKAPI SPARKSTATIC VkResult __SparkCreateDebugUtilsMessengerEXT(
	VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT * create_info,
	const VkAllocationCallbacks * allocator,
	VkDebugUtilsMessengerEXT * debug_messenger) {
	PFN_vkCreateDebugUtilsMessengerEXT func =
		(PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
			instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != SPARK_NULL) {
		return func(instance, create_info, allocator, debug_messenger);
	}
	else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

SPARKAPI SPARKSTATIC SparkVoid __SparkDestroyDebugUtilsMessengerEXT(
	VkInstance instance, VkDebugUtilsMessengerEXT debug_messenger,
	const VkAllocationCallbacks * allocator) {
	PFN_vkDestroyDebugUtilsMessengerEXT func =
		(PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
			instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != SPARK_NULL) {
		func(instance, debug_messenger, allocator);
	}
}

SPARKAPI SPARKSTATIC VkDebugUtilsMessengerCreateInfoEXT
__SparkPopulateDebugMessengerCreateInfo() {
	VkDebugUtilsMessengerCreateInfoEXT create_info = { 0 };
	create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	create_info.messageSeverity =
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	create_info.pfnUserCallback = __SparkDebugCallback;
	return create_info;
}

SPARKAPI SPARKSTATIC SparkResult
__SparkSetupDebugMessenger(SparkWindow window) {
	if (!ENABLE_VALIDATION_LAYERS) {
		return SPARK_SUCCESS;
	}

	VkDebugUtilsMessengerCreateInfoEXT create_info =
		__SparkPopulateDebugMessengerCreateInfo();
	if (__SparkCreateDebugUtilsMessengerEXT(window->instance, &create_info,
		SPARK_NULL,
		&window->debug_messenger)) {
		return SPARK_ERROR_INVALID;
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult
__SparkCreateVulkanInstance(VkInstance * instance, SparkConstString title) {
	if (ENABLE_VALIDATION_LAYERS && !__SparkCheckValidationLayerSupport()) {
		SPARK_LOG_ERROR(
			"Validation layers requested, but not available!");
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
		create_info.enabledLayerCount =
			sizeof(VALIDATION_LAYERS) / sizeof(SparkConstString);
		create_info.ppEnabledLayerNames = VALIDATION_LAYERS;

		VkDebugUtilsMessengerCreateInfoEXT debug_create_info =
			__SparkPopulateDebugMessengerCreateInfo();
		create_info.pNext =
			(VkDebugUtilsMessengerCreateInfoEXT*)&debug_create_info;
	}
	else {
		create_info.enabledLayerCount = 0;
		create_info.pNext = SPARK_NULL;
	}

	VkResult result = vkCreateInstance(&create_info, SPARK_NULL, instance);
	if (result != VK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create Vulkan instance!");
		return SPARK_ERROR_INVALID;
	}

	SparkFree(extensions.names);

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkBool __SparkCheckDeviceExtensionSupport(
	SparkWindow window, VkPhysicalDevice device) {
	SparkU32 extension_count;
	vkEnumerateDeviceExtensionProperties(device, SPARK_NULL, &extension_count,
		SPARK_NULL);

	VkExtensionProperties* available_extensions =
		SparkAllocate(sizeof(VkExtensionProperties) * extension_count);
	vkEnumerateDeviceExtensionProperties(device, SPARK_NULL, &extension_count,
		available_extensions);

	SparkBool all_extensions = SPARK_TRUE;

	for (SparkU32 i = 0; i < sizeof(DEVICE_EXTENSIONS) / sizeof(SparkConstString);
		i++) {
		SparkBool extension_found = SPARK_FALSE;
		for (SparkU32 j = 0; j < extension_count; j++) {
			if (strcmp(DEVICE_EXTENSIONS[i], available_extensions[j].extensionName) ==
				0) {
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

SPARKAPI SPARKSTATIC struct VulkanSwapChainSupportDetails
__SparkQuerySwapChainSupport(SparkWindow window, VkPhysicalDevice device) {
	struct VulkanSwapChainSupportDetails details = { 0 };

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, window->surface,
		&details.capabilities);

	SparkU32 format_count;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, window->surface, &format_count,
		SPARK_NULL);
	if (format_count != 0) {
		details.formats = SparkAllocate(format_count * sizeof(VkSurfaceFormatKHR));
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, window->surface, &format_count,
			details.formats);
	}

	SparkU32 present_mode_count;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, window->surface,
		&present_mode_count, SPARK_NULL);
	if (present_mode_count != 0) {
		details.present_modes =
			SparkAllocate(present_mode_count * sizeof(VkPresentModeKHR));
		vkGetPhysicalDeviceSurfacePresentModesKHR(
			device, window->surface, &present_mode_count, details.present_modes);
	}

	details.formats_size = format_count;
	details.present_modes_size = present_mode_count;

	return details;
}

SPARKAPI SPARKSTATIC VkSurfaceFormatKHR
__SparkChooseSwapSurfaceFormat(const VkSurfaceFormatKHR * available_formats,
	const SparkSize available_formats_size) {
	for (SparkSize i = 0; i < available_formats_size; i++) {
		if (available_formats[i].format == VK_FORMAT_B8G8R8A8_SRGB &&
			available_formats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return available_formats[i];
		}
	}

	return available_formats[0];
}

SPARKAPI SPARKSTATIC VkPresentModeKHR __SparkChooseSwapPresentMode(
	SparkWindow window,
	const VkPresentModeKHR * available_present_modes,
	const SparkSize available_present_modes_size) {
	for (SparkSize i = 0; i < available_present_modes_size; i++) {
		if (available_present_modes[i] == window->window_data->present_mode) {
			return available_present_modes[i];
		}
	}

	return VK_PRESENT_MODE_FIFO_KHR;
}

SPARKAPI SPARKSTATIC VkExtent2D __SparkChooseSwapExtent(
	const SparkWindow window, VkSurfaceCapabilitiesKHR * capabilities) {
	if (capabilities->currentExtent.width != UINT32_MAX) {
		return capabilities->currentExtent;
	}
	else {
		SparkI32 width, height;
		glfwGetFramebufferSize(window->window, &width, &height);

		VkExtent2D actual_extent = { width, height };
		actual_extent.width =
			SparkClampS((SparkScalar)actual_extent.width,
				(SparkScalar)capabilities->minImageExtent.width,
				(SparkScalar)capabilities->maxImageExtent.width);
		actual_extent.height =
			SparkClampS((SparkScalar)actual_extent.height,
				(SparkScalar)capabilities->minImageExtent.height,
				(SparkScalar)capabilities->maxImageExtent.height);
		return actual_extent;
	}
}

SPARKAPI SPARKSTATIC SparkBool
__SparkIsDeviceSuitable(SparkWindow window, VkPhysicalDevice device) {
	struct VulkanQueueFamilyIndices indices =
		__SparkFindQueueFamilies(window, device);
	SparkBool extensions_supported =
		__SparkCheckDeviceExtensionSupport(window, device);

	SparkBool swap_chain_adequete = SPARK_FALSE;
	if (extensions_supported) {
		struct VulkanSwapChainSupportDetails swap_chain_support =
			__SparkQuerySwapChainSupport(window, device);
		swap_chain_adequete =
			swap_chain_support.formats && swap_chain_support.present_modes;

		SparkFree(swap_chain_support.formats);
		SparkFree(swap_chain_support.present_modes);
	}

	VkPhysicalDeviceFeatures supported_features;
	vkGetPhysicalDeviceFeatures(device, &supported_features);

	return __SparkIndicesComplete(&indices) && extensions_supported &&
		swap_chain_adequete && supported_features.samplerAnisotropy;
}

SPARKAPI SPARKSTATIC SparkI32
__SparkRateDeviceSuitability(VkPhysicalDevice device) {
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
		SPARK_LOG_ERROR("Failed to find GPUs with Vulkan support!");
		return SPARK_ERROR_INVALID;
	}

	VkPhysicalDevice* devices =
		SparkAllocate(device_count * sizeof(VkPhysicalDevice));
	vkEnumeratePhysicalDevices(window->instance, &device_count, devices);

	for (SparkU32 i = 0; i < device_count; i++) {
		if (__SparkIsDeviceSuitable(window, devices[i])) {
			physical_device = devices[i];
			break;
		}
	}

	if (physical_device == VK_NULL_HANDLE) {
		SPARK_LOG_ERROR("Failed to find a suitable GPU!");
		SparkFree(devices);
		return SPARK_ERROR_INVALID;
	}

	VkPhysicalDevice* candidates =
		SparkAllocate(device_count * sizeof(VkPhysicalDevice));
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
		SPARK_LOG_ERROR("Failed to find a suitable GPU!");
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
	if (glfwCreateWindowSurface(window->instance, window->window, SPARK_NULL,
		&window->surface) != VK_SUCCESS) {
		return SPARK_ERROR_INVALID;
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult
__SparkCreateLogicalDevice(SparkWindow window) {
	struct VulkanQueueFamilyIndices indices =
		__SparkFindQueueFamilies(window, window->physical_device);

	const SparkU32 indices_size = 2;
	VkDeviceQueueCreateInfo* queue_create_infos =
		SparkAllocate(sizeof(VkDeviceQueueCreateInfo) * indices_size);
	SparkU32* unique_queue_families =
		SparkAllocate(sizeof(SparkU32) * indices_size);

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

	device_features.samplerAnisotropy = SPARK_TRUE;

	queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queue_create_info.queueFamilyIndex = indices.graphics_family;
	queue_create_info.queueCount = 1;
	queue_create_info.pQueuePriorities = &queue_priority;

	create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	create_info.pQueueCreateInfos = queue_create_infos;
	create_info.queueCreateInfoCount = indices_size;
	create_info.pEnabledFeatures = &device_features;
	create_info.enabledExtensionCount =
		sizeof(DEVICE_EXTENSIONS) / sizeof(SparkConstString);
	create_info.ppEnabledExtensionNames = DEVICE_EXTENSIONS;

	if (ENABLE_VALIDATION_LAYERS) {
		create_info.enabledLayerCount =
			sizeof(VALIDATION_LAYERS) / sizeof(SparkConstString);
		create_info.ppEnabledLayerNames = VALIDATION_LAYERS;
	}
	else {
		create_info.enabledLayerCount = 0;
	}

	if (vkCreateDevice(window->physical_device, &create_info, SPARK_NULL,
		&window->device) != VK_SUCCESS) {
		SparkFree(queue_create_infos);
		SparkFree(unique_queue_families);
		SPARK_LOG_ERROR("Failed to create logical device!");
		return SPARK_ERROR_INVALID;
	}

	vkGetDeviceQueue(window->device, indices.graphics_family, 0,
		&window->graphics_queue);
	vkGetDeviceQueue(window->device, indices.present_family, 0,
		&window->present_queue);

	SparkFree(queue_create_infos);
	SparkFree(unique_queue_families);

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkCreateSwapChain(SparkWindow window) {
	struct VulkanSwapChainSupportDetails swap_chain_support =
		__SparkQuerySwapChainSupport(window, window->physical_device);

	VkSurfaceFormatKHR surface_format = __SparkChooseSwapSurfaceFormat(
		swap_chain_support.formats, swap_chain_support.formats_size);
	VkPresentModeKHR present_mode = __SparkChooseSwapPresentMode(
		window,
		swap_chain_support.present_modes, swap_chain_support.present_modes_size);
	VkExtent2D extent =
		__SparkChooseSwapExtent(window, &swap_chain_support.capabilities);

	SparkU32 image_count = swap_chain_support.capabilities.minImageCount + 1;

	if (swap_chain_support.capabilities.maxImageCount > 0 &&
		image_count > swap_chain_support.capabilities.maxImageCount) {
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

	struct VulkanQueueFamilyIndices indices =
		__SparkFindQueueFamilies(window, window->physical_device);
	SparkU32 queue_family_indices[] = { indices.graphics_family,
									   indices.present_family };

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

	if (vkCreateSwapchainKHR(window->device, &create_info, SPARK_NULL,
		&window->swap_chain) != VK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create swap chain!");
		return SPARK_ERROR_INVALID;
	}

	vkGetSwapchainImagesKHR(window->device, window->swap_chain, &image_count,
		SPARK_NULL);
	window->swap_chain_images = SparkAllocate(image_count * sizeof(VkImage));
	vkGetSwapchainImagesKHR(window->device, window->swap_chain, &image_count,
		window->swap_chain_images);

	window->swap_chain_images_size = image_count;
	window->swap_chain_image_format = surface_format.format;

	window->swap_chain_extent = SparkAllocate(sizeof(VkExtent2D));
	if (!window->swap_chain_extent) {
		SPARK_LOG_ERROR(
			"Failed to allocate memory for swap_chain_extent!");
		return SPARK_ERROR_NULL;
	}

	*(window->swap_chain_extent) = extent;

	SparkFree(swap_chain_support.formats);
	SparkFree(swap_chain_support.present_modes);

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC VkImageView __SparkCreateImageView(SparkWindow window, VkImage image, VkFormat format) {
	VkImageViewCreateInfo view_info = { 0 };
	view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	view_info.image = image;
	view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
	view_info.format = format;
	view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	view_info.subresourceRange.baseMipLevel = 0;
	view_info.subresourceRange.levelCount = 1;
	view_info.subresourceRange.baseArrayLayer = 0;
	view_info.subresourceRange.layerCount = 1;

	VkImageView image_view;
	if (vkCreateImageView(window->device, &view_info, SPARK_NULL, &image_view) != VK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create texture image view!");
		return SPARK_ERROR_INVALID;
	}

	return image_view;
}

SPARKAPI SPARKSTATIC SparkResult __SparkCreateImageViews(SparkWindow window) {
	window->swap_chain_image_views =
		SparkAllocate(window->swap_chain_images_size * sizeof(VkImageView));
	window->swap_chain_image_views_size = window->swap_chain_images_size;

	for (SparkSize i = 0; i < window->swap_chain_images_size; i++) {
		window->swap_chain_image_views[i] = __SparkCreateImageView(window, window->swap_chain_images[i], window->swap_chain_image_format);
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC VkShaderModule __SparkCreateShaderModule(
	SparkWindow window, SparkConstBuffer code, SparkSize code_size) {
	VkShaderModuleCreateInfo create_info = { 0 };
	create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	create_info.codeSize = code_size;
	create_info.pCode = (SparkU32*)code;

	VkShaderModule shader_module;
	if (vkCreateShaderModule(window->device, &create_info, SPARK_NULL,
		&shader_module) != VK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create shader module!");
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

	if (vkCreateRenderPass(window->device, &render_pass_info, SPARK_NULL,
		&window->render_pass) != VK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create render pass!");
		return SPARK_ERROR_INVALID;
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkCreateGraphicsPipeline(SparkApplication app, SparkGraphicsPipelineConfig config) {
	SparkWindow window = app->window;
	VkVertexInputBindingDescription binding_description = __SparkGetBindingDescription(VK_VERTEX_INPUT_RATE_VERTEX);
	VkVertexInputAttributeDescription* attribute_descriptions = __SparkGetAttributeDescriptions();

	VkPipelineShaderStageCreateInfo shader_stages[5];
	uint32_t shader_stage_count = 0;

	// Vertex Shader
	VkPipelineShaderStageCreateInfo vert_shader_stage_info = { 0 };
	vert_shader_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vert_shader_stage_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vert_shader_stage_info.module = config->vertex_shader->module;
	vert_shader_stage_info.pName = config->vertex_shader->entry_point;
	shader_stages[shader_stage_count++] = vert_shader_stage_info;

	// Tessellation Control Shader (Optional)
	if (config->tess_control_shader) {
		VkPipelineShaderStageCreateInfo tess_control_shader_stage_info = { 0 };
		tess_control_shader_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		tess_control_shader_stage_info.stage = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
		tess_control_shader_stage_info.module = config->tess_control_shader->module;
		tess_control_shader_stage_info.pName = config->tess_control_shader->entry_point;
		shader_stages[shader_stage_count++] = tess_control_shader_stage_info;
	}

	// Tessellation Evaluation Shader (Optional)
	if (config->tess_evaluation_shader) {
		VkPipelineShaderStageCreateInfo tess_eval_shader_stage_info = { 0 };
		tess_eval_shader_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		tess_eval_shader_stage_info.stage = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
		tess_eval_shader_stage_info.module = config->tess_evaluation_shader->module;
		tess_eval_shader_stage_info.pName = config->tess_evaluation_shader->entry_point;
		shader_stages[shader_stage_count++] = tess_eval_shader_stage_info;
	}

	// Geometry Shader (Optional)
	if (config->geometry_shader) {
		VkPipelineShaderStageCreateInfo geom_shader_stage_info = { 0 };
		geom_shader_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		geom_shader_stage_info.stage = VK_SHADER_STAGE_GEOMETRY_BIT;
		geom_shader_stage_info.module = config->geometry_shader->module;
		geom_shader_stage_info.pName = config->geometry_shader->entry_point;
		shader_stages[shader_stage_count++] = geom_shader_stage_info;
	}

	// Fragment Shader
	VkPipelineShaderStageCreateInfo frag_shader_stage_info = { 0 };
	frag_shader_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	frag_shader_stage_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	frag_shader_stage_info.module = config->fragment_shader->module;
	frag_shader_stage_info.pName = config->fragment_shader->entry_point;
	shader_stages[shader_stage_count++] = frag_shader_stage_info;

	VkPipelineVertexInputStateCreateInfo vertex_input_info = { 0 };
	vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertex_input_info.vertexBindingDescriptionCount = 1;
	vertex_input_info.vertexAttributeDescriptionCount = 3;
	vertex_input_info.pVertexBindingDescriptions = &binding_description;
	vertex_input_info.pVertexAttributeDescriptions = attribute_descriptions;

	VkPipelineInputAssemblyStateCreateInfo input_assembly = { 0 };
	input_assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	input_assembly.primitiveRestartEnable = VK_FALSE;

	VkPipelineViewportStateCreateInfo viewport_state = { 0 };
	viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewport_state.viewportCount = 1;
	viewport_state.scissorCount = 1;

	VkPipelineDynamicStateCreateInfo dynamic_state = { 0 };
	dynamic_state.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamic_state.dynamicStateCount = sizeof(DYNAMIC_STATES) / sizeof(DYNAMIC_STATES[0]);
	dynamic_state.pDynamicStates = DYNAMIC_STATES;

	VkPipelineRasterizationStateCreateInfo rasterizer = { 0 };
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.lineWidth = 1.0f;
	rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	rasterizer.depthBiasEnable = VK_FALSE;

	VkPipelineMultisampleStateCreateInfo multisampling = { 0 };
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	VkPipelineColorBlendAttachmentState color_blend_attachment = { 0 };
	color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
		VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	color_blend_attachment.blendEnable = VK_FALSE;

	VkPipelineColorBlendStateCreateInfo color_blending = { 0 };
	color_blending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	color_blending.logicOpEnable = VK_FALSE;
	color_blending.attachmentCount = 1;
	color_blending.pAttachments = &color_blend_attachment;

	if (config->pipeline_layout == VK_NULL_HANDLE) {
		VkPipelineLayoutCreateInfo pipeline_layout_info = { 0 };
		pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipeline_layout_info.setLayoutCount = 1;
		pipeline_layout_info.pSetLayouts = &window->descriptor_set_layout;

		if (vkCreatePipelineLayout(window->device, &pipeline_layout_info, SPARK_NULL, &config->pipeline_layout) != VK_SUCCESS) {
			SPARK_LOG_ERROR("Failed to create pipeline layout!");
			SparkFree(attribute_descriptions);
			return SPARK_ERROR_INVALID;
		}
		config->owns_pipeline_layout = SPARK_TRUE;
	}
	else {
		config->owns_pipeline_layout = SPARK_FALSE;
	}

	VkGraphicsPipelineCreateInfo pipeline_info = { 0 };
	pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipeline_info.stageCount = shader_stage_count;
	pipeline_info.pStages = shader_stages;
	pipeline_info.pVertexInputState = &vertex_input_info;
	pipeline_info.pInputAssemblyState = &input_assembly;
	pipeline_info.pViewportState = &viewport_state;
	pipeline_info.pRasterizationState = &rasterizer;
	pipeline_info.pMultisampleState = &multisampling;
	pipeline_info.pColorBlendState = &color_blending;
	pipeline_info.pDynamicState = &dynamic_state;
	pipeline_info.layout = config->pipeline_layout;
	pipeline_info.renderPass = config->render_pass;
	pipeline_info.subpass = 0;

	// Handle tessellation state
	VkPipelineTessellationStateCreateInfo tessellation_state = { 0 };
	if (config->tess_control_shader && config->tess_evaluation_shader) {
		tessellation_state.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
		tessellation_state.patchControlPoints = config->patch_control_points;
		pipeline_info.pTessellationState = &tessellation_state;
	}
	else {
		pipeline_info.pTessellationState = NULL;
	}

	if (vkCreateGraphicsPipelines(window->device, VK_NULL_HANDLE, 1, &pipeline_info, SPARK_NULL, &config->pipeline) != VK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create graphics pipeline!");
		SparkFree(attribute_descriptions);
		return SPARK_ERROR_INVALID;
	}

	SparkFree(attribute_descriptions);

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkCreateFramebuffers(SparkWindow window) {
	window->swap_chain_framebuffers = SparkAllocate(
		window->swap_chain_image_views_size * sizeof(VkFramebuffer));

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

		if (vkCreateFramebuffer(window->device, &framebuffer_info, SPARK_NULL,
			&window->swap_chain_framebuffers[i]) !=
			VK_SUCCESS) {
			SPARK_LOG_ERROR("Failed to create framebuffer!");
			return SPARK_ERROR_INVALID;
		}
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkCreateCommandPool(SparkWindow window) {
	struct VulkanQueueFamilyIndices queue_family_indices =
		__SparkFindQueueFamilies(window, window->physical_device);

	VkCommandPoolCreateInfo pool_info = { 0 };
	pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	pool_info.queueFamilyIndex = queue_family_indices.graphics_family;

	if (vkCreateCommandPool(window->device, &pool_info, SPARK_NULL,
		&window->command_pool) != VK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create command pool!");
		return SPARK_ERROR_INVALID;
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkRecordCommandBuffer(
	SparkApplication app,
	VkCommandBuffer command_buffer,
	SparkU32 image_index,
	SparkVector gps
) {
	SparkWindow window = app->window;
	VkCommandBufferBeginInfo begin_info = { 0 };
	begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

	if (vkBeginCommandBuffer(command_buffer, &begin_info) != VK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to begin recording command buffer!");
		return SPARK_ERROR_INVALID;
	}

	VkRenderPassBeginInfo render_pass_info = { 0 };
	render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	render_pass_info.renderPass = window->render_pass;
	render_pass_info.framebuffer = window->swap_chain_framebuffers[image_index];
	render_pass_info.renderArea.offset = (VkOffset2D){ 0, 0 };
	render_pass_info.renderArea.extent = *window->swap_chain_extent;

	SparkResourceManager scene_manager = SparkGetElementHashMap(app->resource_manager, SPARK_RESOURCE_TYPE_SCENE, strlen(SPARK_RESOURCE_TYPE_SCENE));
	SparkResourceManager smesh_manager = SparkGetElementHashMap(app->resource_manager, SPARK_RESOURCE_TYPE_STATIC_MESH, strlen(SPARK_RESOURCE_TYPE_STATIC_MESH));

	SparkScene scene = scene_manager->current_resource->data;
	SparkVec4 sky_color = scene->sky_color;
	VkClearValue clear_color = { sky_color.x, sky_color.y, sky_color.z, sky_color.w };
	render_pass_info.clearValueCount = 1;
	render_pass_info.pClearValues = &clear_color;

	vkCmdBeginRenderPass(command_buffer, &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);

	SparkVector smeshes = SparkGetAllValuesHashMap(smesh_manager->resources);
	SparkStaticMesh mesh = ((SparkResource)smeshes->elements[0])->data;

	for (SparkSize i = 0; i < gps->size; i++) {
		SparkResource resource = gps->elements[i];

		SparkGraphicsPipelineConfig gp = resource->data;

		vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, gp->pipeline);

		VkViewport viewport = { 0 };
		viewport.width = (SparkF32)window->swap_chain_extent->width;
		viewport.height = (SparkF32)window->swap_chain_extent->height;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		vkCmdSetViewport(command_buffer, 0, 1, &viewport);

		VkRect2D scissor = { 0 };
		scissor.offset = (VkOffset2D){ 0, 0 };
		scissor.extent = *window->swap_chain_extent;
		vkCmdSetScissor(command_buffer, 0, 1, &scissor);

		VkBuffer vertex_buffers[] = { mesh->vertex_buffer->buffer };
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(command_buffer, 0, 1, vertex_buffers, offsets);

		vkCmdBindIndexBuffer(command_buffer, mesh->index_buffer->buffer, 0, VK_INDEX_TYPE_UINT16);

		vkCmdBindDescriptorSets(
			command_buffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			gp->pipeline_layout,
			0,
			1,
			&window->descriptor_sets[window->current_frame],
			0,
			SPARK_NULL
		);

		vkCmdDrawIndexed(command_buffer, mesh->index_count, 1, 0, 0, 0);
	}

	SparkDestroyVector(smeshes);

	vkCmdEndRenderPass(command_buffer);

	if (vkEndCommandBuffer(command_buffer) != VK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to record command buffer!");
		return SPARK_ERROR_INVALID;
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkU32 __SparkFindMemoryType(SparkWindow window, SparkU32 type_filter, VkMemoryPropertyFlags properties) {
	VkPhysicalDeviceMemoryProperties mem_properties = { 0 };
	vkGetPhysicalDeviceMemoryProperties(window->physical_device, &mem_properties);

	for (SparkU32 i = 0; i < mem_properties.memoryTypeCount; i++) {
		if ((type_filter & (1 << i)) && (mem_properties.memoryTypes[i].propertyFlags & properties) == properties) {
			return i;
		}
	}

	SPARK_LOG_ERROR("Failed to find suitable memory type!");
	return UINT32_MAX;
}

SPARKAPI SPARKSTATIC VulkanMemoryAllocation __SparkCreateBuffer(SparkWindow window, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkDeviceSize size) {
	VulkanMemoryAllocation vk_alloc = SparkAllocate(sizeof(struct VulkanMemoryAllocationT));

	vk_alloc->size = size;
	vk_alloc->device = window->device;

	VkBufferCreateInfo buffer_info = { 0 };
	buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	buffer_info.size = size;
	buffer_info.usage = usage;
	buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(window->device, &buffer_info, SPARK_NULL, &vk_alloc->buffer) != VK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create vertex buffer!");
		return SPARK_NULL;
	}

	VkMemoryRequirements mem_requirements = { 0 };
	vkGetBufferMemoryRequirements(window->device, vk_alloc->buffer, &mem_requirements);

	VkMemoryAllocateInfo alloc_info = { 0 };
	alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	alloc_info.allocationSize = mem_requirements.size;
	alloc_info.memoryTypeIndex = __SparkFindMemoryType(window, mem_requirements.memoryTypeBits, properties);

	if (vkAllocateMemory(window->device, &alloc_info, SPARK_NULL, &vk_alloc->memory) != VK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to allocate vertex buffer memory!");
		return SPARK_NULL;
	}

	vkBindBufferMemory(window->device, vk_alloc->buffer, vk_alloc->memory, 0);

	return vk_alloc;
}

SPARKAPI SPARKSTATIC SparkResult __SparkCopyBuffer(SparkWindow window, VkBuffer srcbuff, VkBuffer dstbuff, VkDeviceSize size) {
	VkCommandBuffer command_buffer = __SparkBeginSingleTimeCommands(window);

	VkBufferCopy copy_region = { 0 };
	copy_region.size = size;
	vkCmdCopyBuffer(command_buffer, srcbuff, dstbuff, 1, &copy_region);

	__SparkEndSingleTimeCommands(window, command_buffer);
}

SPARKAPI SPARKSTATIC VulkanMemoryAllocation __SparkCreateVertexBuffer(SparkWindow window, SparkHandle vertices, SparkSize vertices_size) {
	VulkanMemoryAllocation staging_alloc = __SparkCreateBuffer(
		window,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		vertices_size
	);

	SparkHandle data;
	vkMapMemory(window->device, staging_alloc->memory, 0, vertices_size, 0, &data);
	memcpy(data, vertices, vertices_size);
	vkUnmapMemory(window->device, staging_alloc->memory);

	// Create Vertex Buffer
	VulkanMemoryAllocation alloc = __SparkCreateBuffer(
		window,
		VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		vertices_size
	);

	alloc->raw_data = data;

	__SparkCopyBuffer(window, staging_alloc->buffer, alloc->buffer, vertices_size);

	vkDestroyBuffer(window->device, staging_alloc->buffer, SPARK_NULL);
	vkFreeMemory(window->device, staging_alloc->memory, SPARK_NULL);

	SparkFree(staging_alloc);

	return alloc;
}

SPARKAPI SPARKSTATIC VulkanMemoryAllocation __SparkCreateIndexBuffer(SparkWindow window, SparkHandle indices, SparkSize indices_size) {
	VulkanMemoryAllocation staging_alloc = __SparkCreateBuffer(
		window,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		indices_size
	);

	SparkHandle data;
	vkMapMemory(window->device, staging_alloc->memory, 0, indices_size, 0, &data);
	memcpy(data, indices, indices_size);
	vkUnmapMemory(window->device, staging_alloc->memory);

	VulkanMemoryAllocation alloc = __SparkCreateBuffer(
		window,
		VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		indices_size
	);

	alloc->raw_data = data;

	__SparkCopyBuffer(window, staging_alloc->buffer, alloc->buffer, indices_size);

	vkDestroyBuffer(window->device, staging_alloc->buffer, SPARK_NULL);
	vkFreeMemory(window->device, staging_alloc->memory, SPARK_NULL);

	SparkFree(staging_alloc);

	return alloc;
}

SPARKAPI SPARKSTATIC SparkResult __SparkCreateCommandBuffers(SparkWindow window) {
	window->command_buffers =
		SparkAllocate(MAX_FRAMES_IN_FLIGHT * sizeof(VkCommandBuffer));
	window->command_buffers_size = MAX_FRAMES_IN_FLIGHT;

	VkCommandBufferAllocateInfo alloc_info = { 0 };
	alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	alloc_info.commandPool = window->command_pool;
	alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	alloc_info.commandBufferCount = window->command_buffers_size;

	if (vkAllocateCommandBuffers(window->device, &alloc_info,
		window->command_buffers) != VK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to allocate command buffers!");
		return SPARK_ERROR_INVALID;
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkCreateSyncObjects(SparkWindow window) {
	window->image_available_semaphores =
		SparkAllocate(MAX_FRAMES_IN_FLIGHT * sizeof(VkSemaphore));
	window->render_finished_semaphores =
		SparkAllocate(MAX_FRAMES_IN_FLIGHT * sizeof(VkSemaphore));
	window->in_flight_fences =
		SparkAllocate(MAX_FRAMES_IN_FLIGHT * sizeof(VkFence));
	window->image_available_semaphores_size = MAX_FRAMES_IN_FLIGHT;
	window->render_finished_semaphores_size = MAX_FRAMES_IN_FLIGHT;
	window->in_flight_fences_size = MAX_FRAMES_IN_FLIGHT;

	VkSemaphoreCreateInfo semaphore_info = { 0 };
	semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VkFenceCreateInfo fence_info = { 0 };
	fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (SparkSize i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		window->image_available_semaphores[i] = VK_NULL_HANDLE;
		window->render_finished_semaphores[i] = VK_NULL_HANDLE;
		window->in_flight_fences[i] = VK_NULL_HANDLE;
		if (vkCreateSemaphore(window->device, &semaphore_info, SPARK_NULL,
			&window->image_available_semaphores[i]) !=
			VK_SUCCESS ||
			vkCreateSemaphore(window->device, &semaphore_info, SPARK_NULL,
				&window->render_finished_semaphores[i]) !=
			VK_SUCCESS ||
			vkCreateFence(window->device, &fence_info, SPARK_NULL,
				&window->in_flight_fences[i]) != VK_SUCCESS) {
			SPARK_LOG_ERROR(
				"Failed to create synchronization objects!");
			return SPARK_ERROR_INVALID;
		}
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkCleanupSwapChain(SparkWindow window) {
	for (SparkSize i = 0; i < window->swap_chain_image_views_size; i++) {
		vkDestroyFramebuffer(window->device, window->swap_chain_framebuffers[i],
			SPARK_NULL);
	}

	for (SparkSize i = 0; i < window->swap_chain_image_views_size; i++) {
		vkDestroyImageView(window->device, window->swap_chain_image_views[i],
			SPARK_NULL);
	}

	vkDestroySwapchainKHR(window->device, window->swap_chain, SPARK_NULL);

	SparkFree(window->swap_chain_framebuffers);
	SparkFree(window->swap_chain_image_views);
	SparkFree(window->swap_chain_images);
	SparkFree(window->swap_chain_extent);

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkRecreateSwapChain(SparkWindow window) {
	SparkI32 width = 0;
	SparkI32 height = 0;

	glfwGetFramebufferSize(window->window, &width, &height);

	while (width == 0 || height == 0) {
		glfwGetFramebufferSize(window->window, &width, &height);
		glfwWaitEvents();
	}

	vkDeviceWaitIdle(window->device);

	__SparkCleanupSwapChain(window);

	__SparkCreateSwapChain(window);
	__SparkCreateImageViews(window);
	__SparkCreateFramebuffers(window);
}

SPARKAPI SPARKSTATIC SparkResult __SparkCreateDescriptorSetLayout(SparkWindow window) {
	VkDescriptorSetLayoutBinding ubo_layout_binding = { 0 };
	ubo_layout_binding.binding = 0;
	ubo_layout_binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	ubo_layout_binding.descriptorCount = 1;
	ubo_layout_binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

	VkDescriptorSetLayoutBinding sampler_layout_binding = { 0 };
	sampler_layout_binding.binding = 1;
	sampler_layout_binding.descriptorCount = 1;
	sampler_layout_binding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	sampler_layout_binding.pImmutableSamplers = SPARK_NULL;
	sampler_layout_binding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

	VkDescriptorSetLayoutBinding bindings[2] = { ubo_layout_binding, sampler_layout_binding };

	VkDescriptorSetLayoutCreateInfo layout_info = { 0 };
	layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layout_info.bindingCount = sizeof(bindings) / sizeof(bindings[0]);
	layout_info.pBindings = bindings;

	if (vkCreateDescriptorSetLayout(window->device, &layout_info, SPARK_NULL, &window->descriptor_set_layout) != VK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create descriptor set layout!");
		return SPARK_ERROR_INVALID;
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkCreateUniformBuffersForWindow(SparkWindow window) {
	VkDeviceSize buffer_size = sizeof(struct VulkanUniformBufferObject);

	window->uniform_buffers = SparkAllocate(sizeof(VkBuffer) * MAX_FRAMES_IN_FLIGHT);
	window->uniform_buffers_size = MAX_FRAMES_IN_FLIGHT;

	window->uniform_buffers_memory = SparkAllocate(sizeof(VkDeviceMemory) * MAX_FRAMES_IN_FLIGHT);
	window->uniform_buffers_memory_size = MAX_FRAMES_IN_FLIGHT;

	window->uniform_buffers_mapped = SparkAllocate(sizeof(SparkHandle) * MAX_FRAMES_IN_FLIGHT);
	window->uniform_buffers_mapped_size = MAX_FRAMES_IN_FLIGHT;

	for (SparkSize i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		VulkanMemoryAllocation alloc = __SparkCreateBuffer(window, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, buffer_size);

		window->uniform_buffers[i] = alloc->buffer;
		window->uniform_buffers_memory[i] = alloc->memory;

		vkMapMemory(window->device, alloc->memory, 0, buffer_size, 0, &window->uniform_buffers_mapped[i]);

		SparkFree(alloc);
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkCreateDescriptorPool(SparkWindow window) {
	VkDescriptorPoolSize pool_sizes[2];
	pool_sizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	pool_sizes[0].descriptorCount = MAX_FRAMES_IN_FLIGHT;
	pool_sizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	pool_sizes[1].descriptorCount = MAX_FRAMES_IN_FLIGHT;

	VkDescriptorPoolCreateInfo pool_info = { 0 };
	pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	pool_info.poolSizeCount = sizeof(pool_sizes) / sizeof(pool_sizes[0]);
	pool_info.pPoolSizes = pool_sizes;
	pool_info.maxSets = MAX_FRAMES_IN_FLIGHT;

	if (vkCreateDescriptorPool(window->device, &pool_info, SPARK_NULL, &window->descriptor_pool) != VK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create descriptor pool!");
		return SPARK_ERROR_INVALID;
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkCreateDescriptorSets(SparkWindow window) {
	VkDescriptorSetLayout* layouts = SparkAllocate(sizeof(VkDescriptorSetLayout) * MAX_FRAMES_IN_FLIGHT);
	for (SparkSize i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		layouts[i] = window->descriptor_set_layout;
	}

	VkDescriptorSetAllocateInfo alloc_info = { 0 };
	alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	alloc_info.descriptorPool = window->descriptor_pool;
	alloc_info.descriptorSetCount = MAX_FRAMES_IN_FLIGHT;
	alloc_info.pSetLayouts = layouts;

	window->descriptor_sets = SparkAllocate(sizeof(VkDescriptorSet) * MAX_FRAMES_IN_FLIGHT);

	if (vkAllocateDescriptorSets(window->device, &alloc_info, window->descriptor_sets) != VK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to allocate descriptor sets!");
		SparkFree(layouts);
		return SPARK_ERROR_INVALID;
	}

	SparkFree(layouts);
	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkUpdateDescriptorSets(SparkWindow window) {
	for (SparkSize i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		VkDescriptorBufferInfo buffer_info = { 0 };
		buffer_info.buffer = window->uniform_buffers[i];
		buffer_info.offset = 0;
		buffer_info.range = sizeof(struct VulkanUniformBufferObject);

		VkWriteDescriptorSet descriptor_write = { 0 };
		descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptor_write.dstSet = window->descriptor_sets[i];
		descriptor_write.dstBinding = 0;
		descriptor_write.dstArrayElement = 0;
		descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptor_write.descriptorCount = 1;
		descriptor_write.pBufferInfo = &buffer_info;

		vkUpdateDescriptorSets(window->device, 1, &descriptor_write, 0, SPARK_NULL);
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkCreateImage(
	SparkApplication app,
	SparkU32 width,
	SparkU32 height,
	VkFormat format,
	VkImageTiling tiling,
	VkImageUsageFlags usage,
	VkMemoryPropertyFlags properties,
	VkImageType image_type,
	VkSampleCountFlagBits samples,
	SparkU32 mip_levels,
	VkImage * image,
	VkDeviceMemory * image_memory
) {
	VkDevice device = app->window->device;

	VkImageCreateInfo image_info = { 0 };
	image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	image_info.imageType = image_type;
	image_info.extent.width = width;
	image_info.extent.height = height;
	image_info.extent.depth = 1;
	image_info.mipLevels = mip_levels;
	image_info.arrayLayers = 1;
	image_info.format = format;
	image_info.tiling = tiling;
	image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	image_info.usage = usage;
	image_info.samples = samples;
	image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateImage(device, &image_info, SPARK_NULL, image) != VK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create image!");
		return SPARK_ERROR_INVALID;
	}

	VkMemoryRequirements mem_requirements;
	vkGetImageMemoryRequirements(device, *image, &mem_requirements);

	VkMemoryAllocateInfo alloc_info = { 0 };
	alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	alloc_info.allocationSize = mem_requirements.size;
	alloc_info.memoryTypeIndex = __SparkFindMemoryType(app->window, mem_requirements.memoryTypeBits, properties);

	if (vkAllocateMemory(device, &alloc_info, SPARK_NULL, image_memory) != VK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to allocate memory for image!");
		return SPARK_ERROR_INVALID;
	}

	vkBindImageMemory(device, *image, *image_memory, 0);

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkTransitionImageLayout(SparkWindow window, VkImage image, VkFormat format, VkImageLayout old_layout, VkImageLayout new_layout) {
	VkCommandBuffer command_buffer = __SparkBeginSingleTimeCommands(window);

	VkImageMemoryBarrier barrier = { 0 };
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.oldLayout = old_layout;
	barrier.newLayout = new_layout;
	barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.image = image;
	barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;

	VkPipelineStageFlags src_stage;
	VkPipelineStageFlags dst_stage;

	if (old_layout == VK_IMAGE_LAYOUT_UNDEFINED && new_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
		barrier.srcAccessMask = 0;
		barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

		src_stage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		dst_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
	}
	else if (old_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && new_layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
		barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

		src_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		dst_stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
	}
	else {
		SPARK_LOG_ERROR("Unsupported layout transition!");
		return SPARK_ERROR_INVALID;
	}

	vkCmdPipelineBarrier(command_buffer, src_stage, dst_stage, 0, 0, SPARK_NULL, 0, SPARK_NULL, 1, &barrier);

	__SparkEndSingleTimeCommands(window, command_buffer);

	return SPARK_SUCCESS;
}


SPARKAPI SPARKSTATIC SparkResult __SparkCreateTextureImageView(SparkWindow window, SparkTexture texture) {
	texture->image_view = __SparkCreateImageView(window, texture->image, VK_FORMAT_R8G8B8A8_SRGB);
	return SPARK_SUCCESS;
}

/*
* Repeat Mode:
* VK_SAMPLER_ADDRESS_MODE_REPEAT: Repeat the texture when going beyond the image dimensions.
* VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT: Like repeat, but inverts the coordinates to mirror the image when going beyond the dimensions.
* VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE: Take the color of the edge closest to the coordinate beyond the image dimensions.
* VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE: Like clamp to edge, but instead uses the edge opposite to the closest edge.
* VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER: Return a solid color when sampling beyond the dimensions of the image.

* Border Color:
* VK_BORDER_COLOR_INT_OPAQUE_BLACK: Black border color beyond image
*/
SPARKAPI SPARKSTATIC SparkResult __SparkCreateTextureSampler(
	SparkWindow window,
	SparkTexture texture,
	VkSamplerAddressMode repeat_mode,
	SparkBool enable_anisotropy,
	VkBorderColor border_color,
	SparkTextureFilter mip_map_mode,
	SparkF32 mip_lod_bias,
	SparkF32 min_lod,
	SparkF32 max_lod
) {
	VkSamplerCreateInfo sampler_info = { 0 };
	sampler_info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	sampler_info.magFilter = VK_FILTER_LINEAR;
	sampler_info.minFilter = VK_FILTER_LINEAR;
	sampler_info.addressModeU = repeat_mode;
	sampler_info.addressModeV = repeat_mode;
	sampler_info.addressModeW = repeat_mode;
	sampler_info.anisotropyEnable = enable_anisotropy;

	if (enable_anisotropy) {
		VkPhysicalDeviceProperties properties = { 0 };
		vkGetPhysicalDeviceProperties(window->physical_device, &properties);

		sampler_info.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
	}

	sampler_info.borderColor = border_color;
	sampler_info.unnormalizedCoordinates = VK_FALSE;
	sampler_info.compareEnable = VK_FALSE;
	sampler_info.compareOp = VK_COMPARE_OP_ALWAYS;
	sampler_info.mipmapMode = mip_map_mode;
	sampler_info.mipLodBias = mip_lod_bias;
	sampler_info.minLod = min_lod;
	sampler_info.maxLod = max_lod;

	if (vkCreateSampler(window->device, &sampler_info, SPARK_NULL, &texture->texture_sampler) != VK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create texture sampler!");
		return SPARK_ERROR_INVALID;
	}
}

SPARKAPI SPARKSTATIC SparkResult __SparkCopyBufferToImage(SparkWindow window, VkBuffer buffer, VkImage image, SparkU32 width, SparkU32 height) {
	VkCommandBuffer command_buffer = __SparkBeginSingleTimeCommands(window);

	VkBufferImageCopy region = { 0 };
	region.bufferOffset = 0;
	region.bufferRowLength = 0;
	region.bufferImageHeight = 0;
	region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	region.imageSubresource.mipLevel = 0;
	region.imageSubresource.baseArrayLayer = 0;
	region.imageSubresource.layerCount = 0;
	region.imageOffset = (VkOffset3D){ 0, 0, 0 };
	region.imageExtent = (VkExtent3D){ width, height, 1 };

	vkCmdCopyBufferToImage(command_buffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

	__SparkEndSingleTimeCommands(window, command_buffer);

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkInitializeVulkan(SparkApplication app) {
	SparkWindow window = app->window;

	if (__SparkCreateVulkanInstance(
		&window->instance, window->window_data->title) != SPARK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create Vulkan instance!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkSetupDebugMessenger(window) != SPARK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to setup debug messenger!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkCreateSurface(window) != SPARK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to setup window surface!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkPickPhysicalDevice(window) != SPARK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to pick physical device!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkCreateLogicalDevice(window) != SPARK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create logical device!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkCreateSwapChain(window) != SPARK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create swap chain!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkCreateImageViews(window) != SPARK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create image views!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkCreateRenderPass(window) != SPARK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create render pass!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkCreateDescriptorSetLayout(window) != SPARK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create descriptor set!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkCreateFramebuffers(window) != SPARK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create framebuffers!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkCreateCommandPool(window) != SPARK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create command pool!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkCreateUniformBuffersForWindow(window) != SPARK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create uniform buffers!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkCreateDescriptorPool(window) != SPARK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create descriptor pool!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkCreateDescriptorSets(window) != SPARK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create descriptor sets!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkUpdateDescriptorSets(window) != SPARK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to update descriptor sets!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkCreateCommandBuffers(window) != SPARK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create command buffer!");
		return SPARK_ERROR_INVALID;
	}

	if (__SparkCreateSyncObjects(window) != SPARK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create sync objects!");
		return SPARK_ERROR_INVALID;
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkVoid __SparkDestroyVulkan(SparkWindow window) {
	vkDeviceWaitIdle(window->device);


	__SparkCleanupSwapChain(window);

	for (SparkSize i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		vkDestroyBuffer(window->device, window->uniform_buffers[i], SPARK_NULL);
		vkFreeMemory(window->device, window->uniform_buffers_memory[i], SPARK_NULL);
	}

	vkDestroyDescriptorPool(window->device, window->descriptor_pool, SPARK_NULL);

	vkDestroyDescriptorSetLayout(window->device, window->descriptor_set_layout, SPARK_NULL);

	vkDestroyRenderPass(window->device, window->render_pass, SPARK_NULL);

	for (SparkSize i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		vkDestroySemaphore(window->device, window->image_available_semaphores[i],
			SPARK_NULL);
		vkDestroySemaphore(window->device, window->render_finished_semaphores[i],
			SPARK_NULL);
		vkDestroyFence(window->device, window->in_flight_fences[i], SPARK_NULL);
	}

	vkDestroyCommandPool(window->device, window->command_pool, SPARK_NULL);

	vkDestroyDevice(window->device, SPARK_NULL);

	if (ENABLE_VALIDATION_LAYERS) {
		__SparkDestroyDebugUtilsMessengerEXT(window->instance,
			window->debug_messenger, SPARK_NULL);
	}

	vkDestroySurfaceKHR(window->instance, window->surface, SPARK_NULL);

	vkDestroyInstance(window->instance, SPARK_NULL);


	SparkFree(window->uniform_buffers);
	SparkFree(window->uniform_buffers_memory);
	SparkFree(window->uniform_buffers_mapped);

	SparkFree(window->image_available_semaphores);
	SparkFree(window->render_finished_semaphores);
	SparkFree(window->in_flight_fences);

	SparkFree(window->command_buffers);
	SparkFree(window->descriptor_sets);
}

SPARKAPI SPARKSTATIC SparkResult __SparkUpdateUniformBuffer(SparkWindow window, SparkU32 current_image) {

	struct VulkanUniformBufferObject ubo = { 0 };

	static SparkF32 rotx = 0.01f;
	static SparkF32 roty = 0.01f;
	static SparkF32 rotz = 0.01f;
	rotx += 0.01f;
	roty += 0.01f;
	rotz += 0.01f;

	SparkMat4 rotationX = SparkMat4Rotate(rotx, (SparkVec3) { 1.0f, 0.0f, 0.0f });
	SparkMat4 rotationY = SparkMat4Rotate(roty, (SparkVec3) { 0.0f, 1.0f, 0.0f });
	SparkMat4 rotationZ = SparkMat4Rotate(rotz, (SparkVec3) { 0.0f, 0.0f, 1.0f });

	ubo.model = SparkMat4Multiply(SparkMat4Multiply(rotationX, rotationY), rotationZ);

	ubo.view = SparkMat4LookAt((SparkVec3) { 2.0f, 2.0f, 2.0f }, (SparkVec3) { 0.0f, 0.0f, 0.0f }, (SparkVec3) { 0.0f, 0.0f, 1.0f });
	ubo.proj = SparkMat4Perspective(SparkRadians(45.0f), window->swap_chain_extent->width / (SparkF32)window->swap_chain_extent->height, 0.1f, 100.0f);
	ubo.proj.m11 *= -1;

	memcpy(window->uniform_buffers_mapped[current_image], &ubo, sizeof(ubo));

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkDrawFrame(SparkApplication app) {
	SparkWindow window = app->window;
	SparkU32 current_frame = window->current_frame;
	vkWaitForFences(window->device, 1, &window->in_flight_fences[current_frame],
		VK_TRUE, UINT64_MAX);
	SparkU32 image_index;
	VkResult result =
		vkAcquireNextImageKHR(window->device, window->swap_chain, UINT64_MAX,
			window->image_available_semaphores[current_frame],
			VK_NULL_HANDLE, &image_index);

	if (result == VK_ERROR_OUT_OF_DATE_KHR) {
		return __SparkRecreateSwapChain(window);
	}
	else if (result != VK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to acquire swap chain image!");
		return SPARK_ERROR_INVALID;
	}

	vkResetFences(window->device, 1, &window->in_flight_fences[current_frame]);

	vkResetCommandBuffer(window->command_buffers[current_frame], 0);

	SparkResourceManager rm = SparkGetElementHashMap(app->resource_manager, SPARK_RESOURCE_TYPE_GRAPHICS_PIPELINE_CONFIG, strlen(SPARK_RESOURCE_TYPE_GRAPHICS_PIPELINE_CONFIG));
	SparkVector gps = SparkGetAllValuesHashMap(rm->resources);

	__SparkRecordCommandBuffer(app, window->command_buffers[current_frame], image_index, gps);
	SparkDestroyVector(gps);

	VkSemaphore wait_semaphores[] = {
		window->image_available_semaphores[current_frame] };
	VkSemaphore signal_semaphores[] = {
		window->render_finished_semaphores[current_frame] };
	VkPipelineStageFlags wait_stages[] = {
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

	__SparkUpdateUniformBuffer(window, current_frame);

	VkSubmitInfo submit_info = { 0 };
	submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submit_info.waitSemaphoreCount = 1;
	submit_info.pWaitSemaphores = wait_semaphores;
	submit_info.pWaitDstStageMask = wait_stages;
	submit_info.commandBufferCount = 1;
	submit_info.pCommandBuffers = &window->command_buffers[current_frame];
	submit_info.signalSemaphoreCount = 1;
	submit_info.pSignalSemaphores = signal_semaphores;

	if (vkQueueSubmit(window->graphics_queue, 1, &submit_info,
		window->in_flight_fences[current_frame]) != VK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to submit draw command buffer!");
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

	result = vkQueuePresentKHR(window->present_queue, &present_info);

	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR ||
		window->framebuffer_resized) {
		window->framebuffer_resized = SPARK_FALSE;
		return __SparkRecreateSwapChain(window);
	}
	else if (result != VK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to present swap chain image!");
		return SPARK_ERROR_INVALID;
	}

	window->current_frame = (current_frame + 1) % MAX_FRAMES_IN_FLIGHT;

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkWaitIdle(SparkWindow window) {
	vkDeviceWaitIdle(window->device);
}

#pragma endregion

#pragma region EVENT

typedef struct SparkQueryEventTaskArgT {
	SparkApplication app;
	SparkVector entities;
	SparkApplicationQueryEventFunction function;
	SparkEvent event;
} *SparkQueryEventTaskArg;

SPARKAPI SparkEventHandler SparkCreateEventHandler() {
	SparkEventHandler event_handler =
		SparkAllocate(sizeof(struct SparkEventHandlerT));
	event_handler->event_functions = SparkCreateVector(2, SPARK_NULL, SparkFree);
	event_handler->query_functions =
		SparkCreateHashMap(4, SparkIntegerHash, SparkIntegerCompare, SPARK_NULL,
			SPARK_NULL, SparkDestroyVector);
	return event_handler;
}

SPARKAPI SparkResult SparkDestroyEventHandler(SparkEventHandler event_handler) {
	SparkDestroyVector(event_handler->event_functions);
	SparkDestroyHashMap(event_handler->query_functions);
	SparkFree(event_handler);
}

SPARKAPI SparkResult SparkAddEventListener(
	SparkEventHandler event_handler, SparkEventType event_type,
	SparkApplicationEventFunction function, SparkPair thread_settings) {
	SparkEventHandlerFunction event_handler_function =
		SparkAllocate(sizeof(struct SparkEventHandlerFunctionT));
	if (!event_handler_function)
		return SPARK_ERROR_INVALID_STATE;
	event_handler_function->event_type = event_type;
	event_handler_function->function = function;
	event_handler_function->thread_settings = thread_settings;
	SparkPushBackVector(event_handler->event_functions,
		(SparkHandle)event_handler_function);
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkRemoveEventListener(
	SparkEventHandler event_handler, SparkEventType event_type,
	SparkApplicationEventFunction function) {
	for (SparkSize i = 0; i < event_handler->event_functions->size; i++) {
		SparkEventHandlerFunction event_handler_function =
			(SparkEventHandlerFunction)SparkGetElementVector(
				event_handler->event_functions, i);
		if (!event_handler_function) {
			return SPARK_ERROR_NULL;
		}
		if (event_handler_function->event_type == event_type &&
			event_handler_function->function == function) {
			SparkRemoveVector(event_handler->event_functions, i);
			SparkFree(event_handler_function);
			return SPARK_SUCCESS;
		}
	}
	return SPARK_ERROR_NOT_FOUND;
}

// Helper function to register the handler for a specific event type
SPARKAPI SPARKSTATIC SparkResult __SparkAddQueryEventListenerForEventType(
	SparkEventHandler event_handler,
	SparkEventType single_event_type,
	SparkQuery query,
	SparkApplicationQueryEventFunction function,
	SparkPair thread_settings) {

	SparkQueryEventHandlerFunction query_event_handler =
		SparkAllocate(sizeof(struct SparkQueryEventHandlerFunctionT));
	if (!query_event_handler)
		return SPARK_ERROR_NULL;

	query_event_handler->event_type = single_event_type;
	query_event_handler->query = query;
	query_event_handler->function = function;
	query_event_handler->thread_settings = thread_settings;

	// Use the integer value directly as the key
	SparkVector handlers = SparkGetElementHashMap(
		event_handler->query_functions,
		(SparkHandle)(uintptr_t)single_event_type,
		sizeof(SparkEventType)
	);

	if (!handlers) {
		handlers = SparkCreateVector(4, SPARK_NULL, SparkFree);
		if (!handlers) {
			SparkFree(query_event_handler);
			return SPARK_ERROR_NULL;
		}
		SparkInsertHashMap(
			event_handler->query_functions,
			(SparkHandle)(uintptr_t)single_event_type,
			sizeof(SparkEventType),
			handlers
		);
	}

	SparkPushBackVector(handlers, query_event_handler);
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkAddQueryEventListener(
	SparkEventHandler event_handler,
	SparkEventType event_type,
	SparkQuery query,
	SparkApplicationQueryEventFunction function,
	SparkPair thread_settings) {

	if (!function || !query)
		return SPARK_ERROR_INVALID_ARGUMENT;

	// Iterate over all bits in event_type
	SparkEventType bit = 1;
	while (bit != 0) {
		if (event_type & bit) {
			SparkResult result = __SparkAddQueryEventListenerForEventType(
				event_handler, bit, query, function, thread_settings);
			if (result != SPARK_SUCCESS) {
				return result;
			}
		}
		// Shift to the next bit
		bit <<= 1;
	}

	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkRemoveQueryEventListener(
	SparkEventHandler event_handler,
	SparkEventType event_type,
	SparkQuery query,
	SparkApplicationQueryEventFunction function) {

	SparkVector handlers = SparkGetElementHashMap(
		event_handler->query_functions,
		(SparkHandle)(uintptr_t)event_type,
		sizeof(event_type)
	);

	if (!handlers) {
		return SPARK_ERROR_NOT_FOUND;
	}

	for (SparkSize i = 0; i < handlers->size; ++i) {
		SparkQueryEventHandlerFunction query_event_handler = handlers->elements[i];
		if (query_event_handler->function == function && query_event_handler->query == query) {
			SparkRemoveVector(handlers, i);
			SparkFree(query_event_handler);
			return SPARK_SUCCESS;
		}
	}

	return SPARK_ERROR_NOT_FOUND;
}


typedef struct SparkEventTaskT {
	SparkApplication app;
	SparkApplicationEventFunction function;
	SparkEvent event;
} *SparkEventTask;

SPARKAPI SPARKSTATIC SparkVoid __SparkEventTask(SparkHandle task) {
	SparkEventTask task_arg = task;

	SparkLockMutex(task_arg->app->mutex);
	task_arg->function(task_arg->app, task_arg->event);
	SparkUnlockMutex(task_arg->app->mutex);

	if (SparkAtomicDecrement(task_arg->event.ref_count) == 0) {
		SparkDestroyEvent(task_arg->event);
	}

	SparkFree(task_arg);
}

SPARKAPI SPARKSTATIC SparkVoid __SparkQueryEventTaskFunction(SparkHandle arg) {
	SparkQueryEventTaskArg task_arg = (SparkQueryEventTaskArg)arg;
	task_arg->function(task_arg->app, task_arg->entities, task_arg->event);

	// Clean up
	SparkDestroyVector(task_arg->entities);

	if (SparkAtomicDecrement(task_arg->event.ref_count) == 0) {
		SparkDestroyEvent(task_arg->event);
	}

	SparkFree(task_arg);
}

SPARKAPI SparkResult SparkDispatchEvent(SparkEventHandler event_handler,
	SparkEvent event) {
	for (SparkSize i = 0; i < event_handler->event_functions->size; i++) {
		SparkEventHandlerFunction function =
			SparkGetElementVector(event_handler->event_functions, i);
		if (function->event_type & event.type) {
			if (function->thread_settings.first) {
				// Increment ref_count for the asynchronous handler
				SparkAtomicIncrement(event.ref_count);
				SparkEventTask task = SparkAllocate(sizeof(struct SparkEventTaskT));
				task->app = event_handler->application;
				task->function = function->function;
				task->event = event;
				SparkAddTaskThreadPool(task->app->thread_pool,
					(SparkThreadFunction)__SparkEventTask, task,
					function->thread_settings.second);
			}
			else {
				// Synchronous handler; no need to adjust ref_count
				function->function(event_handler->application, event);
			}
		}
	}

	SparkVector handlers = SparkGetElementHashMap(
		event_handler->query_functions,
		(SparkHandle)(uintptr_t)event.type,
		sizeof(event.type)
	);

	if (handlers) {
		for (SparkSize i = 0; i < handlers->size; ++i) {
			SparkQueryEventHandlerFunction query_handler = handlers->elements[i];
			SparkQuery query = query_handler->query;
			SparkVector matching_entities = SparkPerformQuery(event_handler->ecs, query);

			if (query_handler->thread_settings.first) {
				// Asynchronous handling
				SparkQueryEventTaskArg task_arg = SparkAllocate(sizeof(struct SparkQueryEventTaskArgT));
				task_arg->app = event_handler->application;
				task_arg->entities = matching_entities;
				task_arg->function = query_handler->function;
				task_arg->event = event;

				// Increment event ref_count for asynchronous handling
				SparkAtomicIncrement(event.ref_count);

				SparkAddTaskThreadPool(
					event_handler->application->thread_pool,
					(SparkThreadFunction)__SparkQueryEventTaskFunction,
					task_arg,
					query_handler->thread_settings.second
				);
			}
			else {
				// Synchronous handling
				query_handler->function(event_handler->application, matching_entities, event);
				SparkDestroyVector(matching_entities);
			}
		}
	}

	// Decrement event ref_count
	if (SparkAtomicDecrement(event.ref_count) == 0) {
		SparkDestroyEvent(event);
	}

	return SPARK_SUCCESS;
}


SPARKAPI SparkEvent SparkCreateEvent(SparkEventType event_type,
	SparkHandle event_data,
	SparkFreeFunction destructor) {
	SparkEvent event;
	event.type = event_type;
	event.data = event_data;
#ifndef NDEBUG
	event.timestamp = SparkGetTime();
#else
	event.timestamp = SPARK_NULL;
#endif
	event.destructor = destructor;
	event.ref_count = SparkAllocate(sizeof(SparkSize));
	*event.ref_count = 1;
	return event;
}

SPARKAPI SparkEvent SparkCreateEventT(SparkEventType event_type,
	SparkHandle event_data,
	SparkFreeFunction destructor,
	SparkConstString time_stamp) {
	SparkEvent event;
	event.type = event_type;
	event.data = event_data;
	event.timestamp = time_stamp;
	event.destructor = destructor;
	event.ref_count = SparkAllocate(sizeof(SparkSize));
	*event.ref_count = 1;
	return event;
}

SPARKAPI SparkResult SparkDestroyEvent(SparkEvent event) {
	if (event.destructor && event.data) {
		event.destructor(event.data);
	}

	if (event.timestamp) {
		SparkFree(event.timestamp);
	}
		
	if (event.ref_count) {
		SparkFree(event.ref_count);
	}
	return SPARK_SUCCESS;
}

#pragma endregion

#pragma region FILE

SPARKAPI SPARKSTATIC SparkResult __SparkInitializeBuffer(SparkBuffer * buffer,
	SparkSize * capacity) {
	if (!buffer || !capacity) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	*capacity = 1024; // Starting with 1KB
	*buffer = (SparkBuffer)SparkAllocate(*capacity);
	if (!*buffer) {
		return SPARK_ERROR_OUT_OF_MEMORY;
	}
	return SPARK_SUCCESS;
}

// Ensure the buffer has enough capacity to hold additional data
SPARKAPI SPARKSTATIC SparkResult
__SparkEnsureCapacity(SparkBuffer * buffer, SparkSize * capacity,
	SparkSize current_size, SparkSize additional_size) {
	if (!buffer || !capacity) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	if (current_size + additional_size > *capacity) {
		SparkSize new_capacity = *capacity * 2;
		while (current_size + additional_size > new_capacity) {
			new_capacity *= 2;
		}
		SparkBuffer temp = (SparkBuffer)SparkReallocate(*buffer, new_capacity);
		if (!temp) {
			return SPARK_ERROR_OUT_OF_MEMORY;
		}
		*buffer = temp;
		*capacity = new_capacity;
	}
	return SPARK_SUCCESS;
}

// Create File Serializer
SPARKAPI SparkFileSerializer SparkCreateFileSerializer(SparkConstString path) {
	if (!path)
		return SPARK_NULL;

	SparkFileSerializer serializer =
		(SparkFileSerializer)SparkAllocate(sizeof(struct SparkFileSerializerT));
	if (!serializer)
		return SPARK_NULL;

	serializer->path = path;
	serializer->size = 0;
	serializer->capacity = 0;
	serializer->data = SPARK_NULL;

	// Initialize buffer
	SparkResult res =
		__SparkInitializeBuffer(&serializer->data, &serializer->capacity);
	if (res != SPARK_SUCCESS) {
		SparkFree(serializer);
		return SPARK_NULL;
	}

	// Open file for writing in binary mode
	serializer->file = fopen(path, "wb");
	if (!serializer->file) {
		SparkFree(serializer->data);
		SparkFree(serializer);
		return SPARK_NULL;
	}

	return serializer;
}

// Destroy File Serializer
SPARKAPI SparkVoid SparkDestroyFileSerializer(SparkFileSerializer serializer) {
	if (!serializer)
		return;

	if (serializer->file) {
		fclose(serializer->file);
	}

	if (serializer->data) {
		SparkFree(serializer->data);
	}

	SparkFree(serializer);
}

// Helper Function to Serialize Raw Data Without Size Prefix
SPARKAPI SparkResult SparkSerializeRawData(SparkFileSerializer serializer,
	SparkHandle data, SparkSize size) {
	if (!serializer || !data || size == 0) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	// Ensure buffer capacity
	SparkResult res = __SparkEnsureCapacity(
		&serializer->data, &serializer->capacity, serializer->size, size);
	if (res != SPARK_SUCCESS) {
		return res;
	}

	// Copy data to buffer
	memcpy(serializer->data + serializer->size, data, size);
	serializer->size += size;

	// Write to file
	SparkSize written = fwrite(data, 1, size, serializer->file);
	if (written != size) {
		return SPARK_ERROR_INVALID;
	}

	return SPARK_SUCCESS;
}

// Serialize Data with Size Prefix
SPARKAPI SparkResult SparkSerializeData(SparkFileSerializer serializer,
	SparkHandle data, SparkSize size) {
	if (!serializer || !data || size == 0) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	// Serialize the size first
	SparkResult res = SparkSerializeRawData(serializer, &size, sizeof(SparkSize));
	if (res != SPARK_SUCCESS) {
		return res;
	}

	// Serialize the actual data
	res = SparkSerializeRawData(serializer, data, size);
	if (res != SPARK_SUCCESS) {
		return res;
	}

	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkSerializeTrivial(SparkFileSerializer serializer,
	SparkHandle data, SparkSize size) {
	if (!serializer || !data || size == 0) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	// Write the data directly without size prefix
	return SparkSerializeRawData(serializer, data, size);
}

// Serialize Header (Magic Number and Version)
SPARKAPI SparkResult SparkSerializeHeader(SparkFileSerializer serializer) {
	if (!serializer) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	// Serialize Magic Number
	SparkResult res =
		SparkSerializeData(serializer, SPARK_SERIALIZER_MAGIC, sizeof(SparkSize));
	if (res != SPARK_SUCCESS) {
		return res;
	}

	// Serialize Version
	res = SparkSerializeData(serializer, SPARK_SERIALIZER_VERSION,
		sizeof(SparkSize));
	if (res != SPARK_SUCCESS) {
		return res;
	}

	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkSerializeVector(SparkFileSerializer serializer,
	SparkVector vector) {
	if (!serializer || !vector) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	// Serialize the size of the vector
	SparkSize size = vector->size;

	SparkResult res = SparkSerializeTrivial(serializer, &size, sizeof(SparkSize));

	if (res != SPARK_SUCCESS) {
		return res;
	}

	// Serialize the elements of the vector
	for (SparkSize i = 0; i < size; i++) {
		SparkHandle element = SparkGetElementVector(vector, i);
		res = SparkSerializeData(serializer, element, sizeof(SparkHandle));
		if (res != SPARK_SUCCESS) {
			return res;
		}
	}

	return SPARK_SUCCESS;
}

// Create File Deserializer
SPARKAPI SparkFileDeserializer
SparkCreateFileDeserializer(SparkConstString path) {
	if (!path)
		return SPARK_NULL;

	SparkFileDeserializer deserializer = (SparkFileDeserializer)SparkAllocate(
		sizeof(struct SparkFileDeserializerT));
	if (!deserializer)
		return SPARK_NULL;

	deserializer->path = path;
	deserializer->size = 0;
	deserializer->capacity = 0;
	deserializer->curr_off = 0;
	deserializer->data = SPARK_NULL;

	// Open file for reading in binary mode
	FILE* file = fopen(path, "rb");
	if (!file) {
		SparkFree(deserializer);
		return SPARK_NULL;
	}

	// Determine file size
	if (fseek(file, 0, SEEK_END) != 0) {
		fclose(file);
		SparkFree(deserializer);
		return SPARK_NULL;
	}

	SparkI32 file_size = ftell(file);
	if (file_size < 0) {
		fclose(file);
		SparkFree(deserializer);
		return SPARK_NULL;
	}
	rewind(file); // Equivalent to fseek(file, 0, SEEK_SET);

	deserializer->size = (SparkU64)file_size;

	// Initialize buffer with file size
	deserializer->capacity = deserializer->size;
	deserializer->data = (SparkBuffer)SparkAllocate(deserializer->capacity);
	if (!deserializer->data) {
		fclose(file);
		SparkFree(deserializer);
		return SPARK_NULL;
	}

	SparkSize read_bytes = fread(deserializer->data, 1, deserializer->size, file);
	if (read_bytes != deserializer->size) {
		fclose(file);
		SparkFree(deserializer->data);
		SparkFree(deserializer);
		return SPARK_NULL;
	}

	fclose(file);
	deserializer->file = SPARK_NULL; // Not used in deserializer

	return deserializer;
}

// Destroy File Deserializer
SPARKAPI SparkVoid
SparkDestroyFileDeserializer(SparkFileDeserializer deserializer) {
	if (!deserializer)
		return;

	if (deserializer->file) {
		fclose(deserializer->file);
	}

	if (deserializer->data) {
		SparkFree(deserializer->data);
	}

	SparkFree(deserializer);
}

// Helper Function to Deserialize Raw Data Without Size Prefix
SPARKAPI SparkResult SparkDeserializeRawData(SparkFileDeserializer deserializer,
	SparkHandle data, SparkSize size) {
	if (!deserializer || !deserializer->data || !data) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	if (deserializer->curr_off + size > deserializer->size) {
		return SPARK_ERROR_OVERFLOW;
	}

	memcpy(data, deserializer->data + deserializer->curr_off, size);
	deserializer->curr_off += size;

	return SPARK_SUCCESS;
}

// Deserialize Data with Size Prefix
SPARKAPI SparkResult SparkDeserializeData(SparkFileDeserializer deserializer,
	SparkHandle * data, SparkSize * size) {
	if (!deserializer || !deserializer->data || !data) {
		return SPARK_ERROR_INVALID_ARGUMENT; // Indicate invalid argument
	}

	SparkSize temps;

	if (!size) {
		size = &temps;
	}

	// Deserialize the size first
	SparkResult res =
		SparkDeserializeRawData(deserializer, size, sizeof(SparkSize));
	if (res != SPARK_SUCCESS) {
		return res;
	}

	// Allocate memory for the actual data
	*data = SparkAllocate(*size);
	if (!*data) {
		return SPARK_ERROR_OUT_OF_MEMORY;
	}

	// Deserialize the actual data
	res = SparkDeserializeRawData(deserializer, *data, *size);
	if (res != SPARK_SUCCESS) {
		SparkFree(*data);
		return res;
	}

	return SPARK_SUCCESS;
}

// Deserialize Header (Magic Number and Version)
SPARKAPI SparkResult
SparkDeserializeHeader(SparkFileDeserializer deserializer) {
	if (!deserializer) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	// Deserialize Magic Number
	SparkSize magic;
	SparkResult res =
		SparkDeserializeData(deserializer, &magic, sizeof(SparkSize));
	if (res != SPARK_SUCCESS) {
		return res;
	}

	if (magic != SPARK_SERIALIZER_MAGIC) {
		SparkFree(magic);
		return SPARK_ERROR_INVALID;
	}
	SparkFree(magic);

	// Deserialize Version
	SparkSize version;
	res = SparkDeserializeData(deserializer, &version, sizeof(SparkSize));
	if (res != SPARK_SUCCESS) {
		return res;
	}

	if (version != SPARK_SERIALIZER_VERSION) {
		SparkFree(version);
		return SPARK_ERROR_INVALID;
	}
	SparkFree(version);

	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkDeserializeTrivial(SparkFileDeserializer deserializer,
	SparkHandle data, SparkSize size) {
	if (!deserializer || !deserializer->data || !data) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	if (deserializer->curr_off + size > deserializer->size) {
		return SPARK_ERROR_OVERFLOW;
	}

	memcpy(data, deserializer->data + deserializer->curr_off, size);
	deserializer->curr_off += size;

	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkDeserializeString(SparkFileDeserializer deserializer,
	SparkBuffer * data,
	SparkSize * size) {
	if (!deserializer || !deserializer->data || !data) {
		return SPARK_ERROR_INVALID_ARGUMENT; // Indicate invalid argument
	}

	SparkSize temps;

	if (!size) {
		size = &temps;
	}

	// Deserialize the size first
	SparkResult res =
		SparkDeserializeRawData(deserializer, size, sizeof(SparkSize));
	if (res != SPARK_SUCCESS) {
		return res;
	}

	// Allocate memory for the actual data
	*data = SparkAllocate(*size + 1);
	if (!*data) {
		return SPARK_ERROR_OUT_OF_MEMORY;
	}

	// Deserialize the actual data
	res = SparkDeserializeRawData(deserializer, *data, *size);
	if (res != SPARK_SUCCESS) {
		SparkFree(*data);
		return res;
	}

	(*data)[*size] = '\0';

	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkDeserializeVector(SparkFileDeserializer deserializer,
	SparkVector * vector) {
	if (!deserializer || !deserializer->data || !vector) {
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	if (!*vector) {
		*vector = SparkDefaultVector();
	}

	SparkSize vec_size;
	SparkResult res =
		SparkDeserializeTrivial(deserializer, &vec_size, sizeof(vec_size));

	if (res != SPARK_SUCCESS) {
		return res;
	}

	for (SparkSize i = 0; i < vec_size; i++) {
		SparkHandle element = SPARK_NULL;
		res = SparkDeserializeRawData(deserializer, element, sizeof(SparkHandle));
		if (res != SPARK_SUCCESS) {
			return res;
		}
	}

	return SPARK_SUCCESS;
}

#pragma endregion

#pragma region AUDIO

// Helper function to determine OpenAL format
SPARKAPI SPARKSTATIC SparkI32 __SparkGetOpenALFormat(SparkI32 channels,
	SparkI32 bits_per_sample) {
	if (bits_per_sample == 16) {
		if (channels == 1)
			return AL_FORMAT_MONO16;
		else if (channels == 2)
			return AL_FORMAT_STEREO16;
	}
	else if (bits_per_sample == 8) {
		if (channels == 1)
			return AL_FORMAT_MONO8;
		else if (channels == 2)
			return AL_FORMAT_STEREO8;
	}
	return 0;
}

static ALCdevice* SPARK_AUDIO_DEVICE = SPARK_NULL;
static ALCcontext* SPARK_AUDIO_CONTEXT = SPARK_NULL;

SPARKAPI SparkBool SparkInitAudio() {
	// These are already initialized, so we will exit early
	if (SPARK_AUDIO_DEVICE && SPARK_AUDIO_CONTEXT)
		return SPARK_SUCCESS;
	SPARK_AUDIO_DEVICE = alcOpenDevice(SPARK_NULL); // Open default device
	if (!SPARK_AUDIO_DEVICE) {
		fprintf(stderr, "Failed to open OpenAL device.\n");
		return SPARK_FALSE;
	}

	SPARK_AUDIO_CONTEXT = alcCreateContext(SPARK_AUDIO_DEVICE, SPARK_NULL);
	if (!SPARK_AUDIO_CONTEXT ||
		alcMakeContextCurrent(SPARK_AUDIO_CONTEXT) == ALC_FALSE) {
		fprintf(stderr, "Failed to create or set OpenAL context.\n");
		if (SPARK_AUDIO_CONTEXT)
			alcDestroyContext(SPARK_AUDIO_CONTEXT);
		alcCloseDevice(SPARK_AUDIO_DEVICE);
		return SPARK_FALSE;
	}

	return SPARK_TRUE;
}

SPARKAPI SparkVoid SparkShutdownAudio() {
	alcMakeContextCurrent(SPARK_NULL);
	if (SPARK_AUDIO_CONTEXT)
		alcDestroyContext(SPARK_AUDIO_CONTEXT);
	if (SPARK_AUDIO_DEVICE)
		alcCloseDevice(SPARK_AUDIO_DEVICE);
}

SPARKAPI SparkAudioBuffer SparkCreateAudioBuffer(SparkConstString file_path) {
	if (SparkInitAudio() != SPARK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to initialize audio.");
		return SPARK_NULL;
	}
	if (!file_path) {
		SPARK_LOG_ERROR("Invalid file path.");
		return SPARK_NULL;
	}

	SparkAudioBuffer buffer =
		(SparkAudioBuffer)SparkAllocate(sizeof(struct SparkAudioBufferT));
	if (!buffer) {
		SPARK_LOG_ERROR(
			"Failed to allocate memory for audio buffer.\n");
		return SPARK_NULL;
	}

	memset(buffer, 0, sizeof(struct SparkAudioBufferT));

	SparkConstString extension = SparkGetFileExtension(file_path);
	SparkHandle data = SPARK_NULL;
	SparkI32 format = 0;
	SparkI32 frequency = 0;
	SparkI32 size = 0;

	if (strcmp(extension, "wav") == 0) {
		// Load WAV file using dr_wav
		drwav wav;
		if (!drwav_init_file(&wav, file_path, SPARK_NULL)) {
			SPARK_LOG_ERROR("Failed to load WAV file: %s", file_path);
			SparkFree(buffer);
			return SPARK_NULL;
		}

		SparkSize total_sample_count = wav.totalPCMFrameCount * wav.channels;
		SparkI16* sample_data =
			(int16_t*)SparkAllocate(total_sample_count * sizeof(SparkI16));
		SparkSize samples_read =
			drwav_read_pcm_frames_s16(&wav, wav.totalPCMFrameCount, sample_data);

		drwav_uninit(&wav);

		if (samples_read == 0) {
			SPARK_LOG_ERROR(
				"Failed to read samples from WAV file: %s", file_path);
			SparkFree(sample_data);
			SparkFree(buffer);
			return SPARK_NULL;
		}

		format = __SparkGetOpenALFormat(wav.channels, 16);
		if (format == 0) {
			SPARK_LOG_ERROR("Unsupported WAV format in file: %s",
				file_path);
			SparkFree(sample_data);
			SparkFree(buffer);
			return SPARK_NULL;
		}

		data = sample_data;
		frequency = wav.sampleRate;
		size = (SparkI32)(total_sample_count * sizeof(SparkI16));
	}
	else if (strcmp(extension, "flac") == 0) {
		// Load FLAC file using dr_flac
		drflac* flac = drflac_open_file(file_path, SPARK_NULL);
		if (!flac) {
			SPARK_LOG_ERROR("Failed to load FLAC file: %s",
				file_path);
			SparkFree(buffer);
			return SPARK_NULL;
		}

		SparkSize total_sample_count = flac->totalPCMFrameCount * flac->channels;
		SparkI16* sample_data =
			(SparkI16*)SparkAllocate(total_sample_count * sizeof(SparkI16));
		SparkSize samples_read =
			drflac_read_pcm_frames_s16(flac, flac->totalPCMFrameCount, sample_data);

		drflac_close(flac);

		if (samples_read == 0) {
			SPARK_LOG_ERROR(
				"Failed to read samples from FLAC file: %s", file_path);
			SparkFree(sample_data);
			SparkFree(buffer);
			return SPARK_NULL;
		}

		format = __SparkGetOpenALFormat(flac->channels, 16);
		if (format == 0) {
			SPARK_LOG_ERROR("Unsupported FLAC format in file: %s",
				file_path);
			SparkFree(sample_data);
			SparkFree(buffer);
			return SPARK_NULL;
		}

		data = sample_data;
		frequency = flac->sampleRate;
		size = (SparkI32)(total_sample_count * sizeof(SparkI16));
	}
	else if (strcmp(extension, "mp3") == 0) {
		// Load MP3 file using dr_mp3
		drmp3 mp3;
		if (!drmp3_init_file(&mp3, file_path, SPARK_NULL)) {
			SPARK_LOG_ERROR("Failed to load MP3 file: %s", file_path);
			SparkFree(buffer);
			return SPARK_NULL;
		}

		SparkU64 total_pcm_frame_count = drmp3_get_pcm_frame_count(&mp3);
		SparkSize total_sample_count =
			(SparkSize)(total_pcm_frame_count * mp3.channels);
		SparkI16* sample_data =
			(SparkI16*)SparkAllocate(total_sample_count * sizeof(SparkI16));
		SparkSize samples_read =
			drmp3_read_pcm_frames_s16(&mp3, total_pcm_frame_count, sample_data);

		drmp3_uninit(&mp3);

		if (samples_read == 0) {
			SPARK_LOG_ERROR(
				"Failed to read samples from MP3 file: %s", file_path);
			SparkFree(sample_data);
			SparkFree(buffer);
			return SPARK_NULL;
		}

		format = __SparkGetOpenALFormat(mp3.channels, 16);
		if (format == 0) {
			SPARK_LOG_ERROR("Unsupported MP3 format in file: %s",
				file_path);
			SparkFree(sample_data);
			SparkFree(buffer);
			return SPARK_NULL;
		}

		data = sample_data;
		frequency = mp3.sampleRate;
		size = (SparkI32)(total_sample_count * sizeof(SparkI16));
	}
	else {
		SPARK_LOG_ERROR("Unsupported file extension: %s",
			extension);
		SparkFree(buffer);
		return SPARK_NULL;
	}

	// Generate OpenAL buffer
	alGenBuffers(1, &buffer->bufferid);
	if (alGetError() != AL_NO_ERROR) {
		SPARK_LOG_ERROR("Failed to generate OpenAL buffer.");
		SparkFree(data);
		SparkFree(buffer);
		return SPARK_NULL;
	}

	// Buffer the audio data into OpenAL
	alBufferData(buffer->bufferid, format, data, size, frequency);
	if (alGetError() != AL_NO_ERROR) {
		SPARK_LOG_ERROR("Failed to buffer audio data into OpenAL.");
		alDeleteBuffers(1, &buffer->bufferid);
		SparkFree(data);
		SparkFree(buffer);
		return SPARK_NULL;
	}

	buffer->format = format;
	buffer->frequency = frequency;
	buffer->size = size;
	buffer->data = SPARK_NULL; // Data has been passed to OpenAL

	// Free the sample data as OpenAL has its own copy
	SparkFree(data);

	return buffer;
}

SPARKAPI SparkVoid SparkDestroyAudioBuffer(SparkAudioBuffer buffer) {
	if (!buffer)
		return;

	alDeleteBuffers(1, &buffer->bufferid);
	SparkFree(buffer);
}

SPARKAPI SparkAudio SparkCreateAudio(SparkAudioBuffer buffer) {
	if (!buffer) {
		SPARK_LOG_ERROR("Invalid audio buffer.");
		return SPARK_NULL;
	}

	SparkAudio source = (SparkAudio)SparkAllocate(sizeof(struct SparkAudioT));
	if (!source) {
		SPARK_LOG_ERROR(
			"Failed to allocate memory for audio source.");
		return SPARK_NULL;
	}

	memset(source, 0, sizeof(struct SparkAudioT));

	alGenSources(1, &source->sourceid);
	if (alGetError() != AL_NO_ERROR) {
		SPARK_LOG_ERROR("Failed to generate OpenAL source.");
		SparkFree(source);
		return SPARK_NULL;
	}

	// Attach buffer to source
	alSourcei(source->sourceid, AL_BUFFER, buffer->bufferid);
	if (alGetError() != AL_NO_ERROR) {
		SPARK_LOG_ERROR("Failed to attach buffer to source.");
		alDeleteSources(1, &source->sourceid);
		SparkFree(source);
		return SPARK_NULL;
	}

	source->buffer = buffer;
	source->looping = SPARK_FALSE;
	source->gain = 1.0f;
	source->pitch = 1.0f;
	source->position.x = source->position.y = source->position.z = 0.0f;
	source->velocity.x = source->velocity.y = source->velocity.z = 0.0f;
	source->direction.x = source->direction.y = source->direction.z = 0.0f;

	// Set initial source properties in OpenAL
	alSourcef(source->sourceid, AL_GAIN, source->gain);
	alSourcef(source->sourceid, AL_PITCH, source->pitch);
	alSourcei(source->sourceid, AL_LOOPING, source->looping ? AL_TRUE : AL_FALSE);

	alSource3f(source->sourceid, AL_POSITION, source->position.x,
		source->position.y, source->position.z);
	alSource3f(source->sourceid, AL_VELOCITY, source->velocity.x,
		source->velocity.y, source->velocity.z);
	alSource3f(source->sourceid, AL_DIRECTION, source->direction.x,
		source->direction.y, source->direction.z);

	return source;
}

SPARKAPI SparkVoid SparkDestroyAudio(SparkAudio source) {
	if (!source)
		return;

	SparkDestroyAudioBuffer(source->buffer);
	alDeleteSources(1, &source->sourceid);
	SparkFree(source);
}

SPARKAPI SparkVoid SparkPlayAudio(SparkAudio source) {
	if (!source)
		return;
	alSourcePlay(source->sourceid);
}

SPARKAPI SparkVoid SparkRewindAudio(SparkAudio source) {
	if (!source)
		return;
	alSourceRewind(source->sourceid);
}

SPARKAPI SparkVoid SparkStopAudio(SparkAudio source) {
	if (!source)
		return;
	alSourceStop(source->sourceid);
}

SPARKAPI SparkVoid SparkPauseAudio(SparkAudio source) {
	if (!source)
		return;
	alSourcePause(source->sourceid);
}

SPARKAPI SparkVoid SparkSetAudioPosition(SparkAudio source, SparkVec3 pos) {
	if (!source)
		return;
	source->position.x = pos.x;
	source->position.y = pos.y;
	source->position.z = pos.z;
	alSource3f(source->sourceid, AL_POSITION, pos.x, pos.y, pos.z);
}

SPARKAPI SparkVoid SparkSetAudioGain(SparkAudio source, SparkF32 gain) {
	if (!source)
		return;
	source->gain = gain;
	alSourcef(source->sourceid, AL_GAIN, gain);
}

SPARKAPI SparkVoid SparkSetAudioPitch(SparkAudio source, SparkF32 pitch) {
	if (!source)
		return;
	source->pitch = pitch;
	alSourcef(source->sourceid, AL_PITCH, pitch);
}

SPARKAPI SparkVoid SparkSetAudioLooping(SparkAudio source, SparkBool looping) {
	if (!source)
		return;
	source->looping = looping;
	alSourcei(source->sourceid, AL_LOOPING, looping ? AL_TRUE : AL_FALSE);
}

#pragma endregion

#pragma region TEXTURE

SPARKAPI SparkTexture SparkCreateTexture(SparkApplication app, SparkConstString image_path) {
	VkDevice device = app->window->device;
	SparkI32 tex_width, tex_height, tex_channels;

	stbi_uc* pixels = stbi_load(image_path, &tex_width, &tex_height, &tex_channels, STBI_rgb_alpha);

	if (!pixels) {
		SPARK_LOG_ERROR("Failed to load texture from file: %s", image_path);
		return SPARK_ERROR_INVALID;
	}

	VkDeviceSize image_size = tex_width * tex_height * 4;

	VulkanMemoryAllocation staging_alloc = __SparkCreateBuffer(app->window, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, image_size);

	SparkHandle data;
	vkMapMemory(device, staging_alloc->memory, 0, image_size, 0, &data);
	memcpy(data, pixels, image_size);
	vkUnmapMemory(device, staging_alloc->memory);

	stbi_image_free(pixels);

	SparkTexture texture = SparkAllocate(sizeof(struct SparkTextureT));
	texture->device = device;
	texture->width = tex_width;
	texture->height = tex_height;
	texture->channels = tex_channels;

	__SparkCreateImage(
		app,
		tex_width,
		tex_height,
		VK_FORMAT_R8G8B8A8_SRGB,
		VK_IMAGE_TILING_OPTIMAL,
		VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		VK_IMAGE_TYPE_2D,
		VK_SAMPLE_COUNT_1_BIT,
		1,
		&texture->image,
		&texture->image_memory);
	__SparkTransitionImageLayout(app->window, texture->image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	__SparkCopyBufferToImage(app->window, staging_alloc->buffer, texture->image, tex_width, tex_height);
	__SparkTransitionImageLayout(app->window, texture->image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
	__SparkCreateTextureImageView(app->window, texture);

	vkDestroyBuffer(device, staging_alloc->buffer, SPARK_NULL);
	vkFreeMemory(device, staging_alloc->memory, SPARK_NULL);

	SparkFree(staging_alloc);

	return texture;
}

SPARKAPI SparkVoid SparkDestroyTexture(SparkTexture texture) {
	vkDestroySampler(texture->device, texture->texture_sampler, SPARK_NULL);
	vkDestroyImageView(texture->device, texture->image_view, SPARK_NULL);
	vkDestroyImage(texture->device, texture->image, SPARK_NULL);
	vkFreeMemory(texture->device, texture->image_memory, SPARK_NULL);
	SparkFree(texture);
}

#pragma endregion

#pragma region WINDOW

SPARKAPI SparkWindowData SparkCreateWindowData(SparkConstString title,
	SparkI32 width, SparkI32 height,
	SparkBool vsync,
	SparkPresentMode present) {
	SparkWindowData window_data = SparkAllocate(sizeof(struct SparkWindowDataT));
	window_data->title = SparkAllocate(strlen(title) + 1);
	strcpy(window_data->title, title);
	window_data->width = width;
	window_data->height = height;
	window_data->vsync = vsync;
	window_data->present_mode = present;
	window_data->event_handler = SparkCreateEventHandler();
	return window_data;
}

SPARKAPI SparkVoid SparkDestroyWindowData(SparkWindowData window_data) {
	SparkFree(window_data->title);
	SparkFree(window_data);
}

SPARKAPI SPARKSTATIC SparkVoid
__GlfwErrorCallback(SparkI32 error, SparkConstString description) {
	SPARK_LOG_ERROR("GLFW Error (%d): %s", error, description);
}

SPARKAPI SPARKSTATIC SparkVoid __GlfwSetKeyCallback(GLFWwindow * window,
	SparkI32 key,
	SparkI32 scancode,
	SparkI32 action,
	SparkI32 mods) {
	SparkWindow data = glfwGetWindowUserPointer(window);

	switch (action) {
	case GLFW_PRESS: {
		SparkEventDataKeyPressed event_data =
			SparkAllocate(sizeof(struct SparkEventDataKeyPressedT));
		event_data->key = key;
		event_data->repeat = SPARK_FALSE;
		SparkEvent event = SparkCreateEvent(SPARK_EVENT_KEY_PRESSED,
			(SparkHandle)event_data, SparkFree);
		SparkDispatchEvent(data->window_data->event_handler, event);
		break;
	}
	case GLFW_RELEASE: {
		SparkEventDataKeyReleased event_data =
			SparkAllocate(sizeof(struct SparkEventDataKeyReleasedT));
		event_data->key = key;
		SparkEvent event = SparkCreateEvent(SPARK_EVENT_KEY_RELEASED,
			(SparkHandle)event_data, SparkFree);
		SparkDispatchEvent(data->window_data->event_handler, event);
		break;
	}
	case GLFW_REPEAT: {
		SparkEventDataKeyPressed event_data =
			SparkAllocate(sizeof(struct SparkEventDataKeyPressedT));
		event_data->key = key;
		event_data->repeat = SPARK_TRUE;
		SparkEvent event = SparkCreateEvent(SPARK_EVENT_KEY_PRESSED,
			(SparkHandle)event_data, SparkFree);
		SparkDispatchEvent(data->window_data->event_handler, event);
		break;
	}
	}
}

SPARKAPI SPARKSTATIC SparkVoid __GlfwSetCursorPosCallback(GLFWwindow * window,
	double xpos,
	double ypos) {
	SparkWindow data = glfwGetWindowUserPointer(window);

	SparkEventDataMouseMoved event_data =
		SparkAllocate(sizeof(struct SparkEventDataMouseMovedT));
	event_data->xpos = xpos;
	event_data->ypos = ypos;
	SparkEvent event = SparkCreateEvent(SPARK_EVENT_MOUSE_MOVED,
		(SparkHandle)event_data, SparkFree);
	SparkDispatchEvent(data->window_data->event_handler, event);
}

SPARKAPI SPARKSTATIC SparkVoid __GlfwSetMouseButtonCallback(GLFWwindow * window,
	SparkI32 button,
	SparkI32 action,
	SparkI32 mods) {
	SparkWindow data = glfwGetWindowUserPointer(window);

	switch (action) {
	case GLFW_PRESS: {
		SparkEventDataMouseButtonPressed event_data =
			SparkAllocate(sizeof(struct SparkEventDataMouseButtonPressedT));
		event_data->button = button;
		SparkEvent event = SparkCreateEvent(SPARK_EVENT_MOUSE_BUTTON_PRESSED,
			(SparkHandle)event_data, SparkFree);
		SparkDispatchEvent(data->window_data->event_handler, event);
		break;
	}
	case GLFW_RELEASE: {
		SparkEventDataMouseButtonReleased event_data =
			SparkAllocate(sizeof(struct SparkEventDataMouseButtonReleasedT));
		event_data->button = button;
		SparkEvent event = SparkCreateEvent(SPARK_EVENT_MOUSE_BUTTON_RELEASED,
			(SparkHandle)event_data, SparkFree);
		SparkDispatchEvent(data->window_data->event_handler, event);
		break;
	}
	}
}

SPARKAPI SPARKSTATIC SparkVoid __GlfwSetScrollCallback(GLFWwindow * window,
	SparkF64 xoffset,
	SparkF64 yoffset) {
	SparkWindow data = glfwGetWindowUserPointer(window);

	SparkEventDataMouseScrolled event_data =
		SparkAllocate(sizeof(struct SparkEventDataMouseScrolledT));
	event_data->x = xoffset;
	event_data->y = yoffset;
	SparkEvent event = SparkCreateEvent(SPARK_EVENT_MOUSE_SCROLLED,
		(SparkHandle)event_data, SparkFree);
	SparkDispatchEvent(data->window_data->event_handler, event);
}

SPARKAPI SPARKSTATIC SparkVoid __GlfwSetFramebufferResizeCallback(
	GLFWwindow * window, SparkI32 width, SparkI32 height) {
	SparkWindow data = window;
	data->framebuffer_resized = SPARK_TRUE;
}

SPARKAPI SparkWindow SparkCreateWindow(SparkWindowData window_data) {
	SparkWindow window = SparkAllocate(sizeof(struct SparkWindowT));
	memset(window, 0, sizeof(struct SparkWindowT));
	window->window_data = window_data;
	window->current_frame = 0;
	window->should_close = SPARK_FALSE;

	if (!glfwInit()) {
		SPARK_LOG_FATAL("Failed to initialize GLFW!");
		SparkFree(window);
		return SPARK_NULL;
	}

	glfwSetErrorCallback(__GlfwErrorCallback);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	window->window = glfwCreateWindow(window_data->width, window_data->height,
		window_data->title, SPARK_NULL, SPARK_NULL);

	if (!window->window) {
		SPARK_LOG_FATAL("Failed to create GLFW window!");
		SparkDestroyWindowData(window->window_data);
		SparkFree(window);
		glfwTerminate();
		return SPARK_NULL;
	}

	glfwSetWindowUserPointer(window->window, window);

	glfwSetFramebufferSizeCallback(window->window,
		__GlfwSetFramebufferResizeCallback);
	glfwSetKeyCallback(window->window, __GlfwSetKeyCallback);
	glfwSetCursorPosCallback(window->window, __GlfwSetCursorPosCallback);
	glfwSetMouseButtonCallback(window->window, __GlfwSetMouseButtonCallback);
	glfwSetScrollCallback(window->window, __GlfwSetScrollCallback);


	return window;
}

SPARKAPI SparkVoid SparkDestroyWindow(SparkWindow window) {
	glfwDestroyWindow(window->window);
	glfwTerminate();
	__SparkWaitIdle(window);
	__SparkDestroyVulkan(window);
	SparkDestroyWindowData(window->window_data);
	SparkFree(window);
}

SPARKAPI SPARKSTATIC SparkVoid __SparkUpdateWindow(SparkApplication app) {
	SparkWindow window = app->window;
	window->should_close = glfwWindowShouldClose(window->window);
	glfwPollEvents();
	__SparkDrawFrame(app);
}

#pragma endregion

#pragma region RESOURCE

SPARKAPI SparkVoid SPARKSTATIC __SparkFreeResource(SparkResource resource) {
	resource->destructor(resource->data);
	SparkFree(resource);
}

SPARKAPI SparkResourceManager SparkCreateResourceManager(
	SparkConstString type, SparkFreeFunction resource_free) {
	SparkResourceManager manager =
		SparkAllocate(sizeof(struct SparkResourceManagerT));
	manager->type = type;
	manager->resource_destructor = resource_free;
	manager->resources =
		SparkCreateHashMap(4, SparkStringHash, SparkStringCompare, SPARK_NULL,
			SPARK_NULL, __SparkFreeResource);
	manager->current_resource = SPARK_NULL;
	return manager;
}

SPARKAPI SparkVoid SparkDestroyResourceManager(SparkResourceManager manager) {
	SparkDestroyHashMap(manager->resources);
	SparkFree(manager);
}

SPARKAPI SparkResult SparkAddResource(SparkResourceManager manager,
	SparkResource resource) {
	if (!manager) {
		SPARK_LOG_ERROR("Invalid resource manager.");
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	// Will overwrite the resource if it already exists
	SparkResult res = SparkInsertHashMap(manager->resources, resource->name,
		strlen(resource->name), resource);

	if (!manager->current_resource) {
		manager->current_resource = SparkGetElementHashMap(manager->resources, resource->name, strlen(resource->name));
	}

	return res;
}

SPARKAPI SparkResult SparkSetCurrentResource(SparkResourceManager manager, SparkConstString resource_name) {
	if (!manager) {
		SPARK_LOG_ERROR("Invalid resource manager.");
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	SparkResource resource = SparkGetElementHashMap(manager->resources, resource_name, strlen(resource_name));

	if (resource) {
		manager->current_resource = resource;
		return SPARK_SUCCESS;
	}

	SPARK_LOG_ERROR("Can not set current resource that does not exist!");
	return SPARK_ERROR_INVALID;
}

SPARKAPI SparkResult SparkRemoveResource(SparkResourceManager manager,
	SparkConstString name) {
	if (!manager) {
		SPARK_LOG_ERROR("Invalid resource manager.");
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	return SparkRemoveHashMap(manager->resources, name, strlen(name));
}

/*
SPARKAPI SparkHandle SparkCreateResourceData(SparkConstString type, ...) {
	va_list args;
	va_start(type, args);

	SparkHandle handle = SPARK_NULL;

	if (strcmp(type, SPARK_RESOURCE_TYPE_STATIC_MESH) == 0) {
		SparkF32* vertices = va_arg(args, SparkF32*);
		SparkU32 vertices_size = va_arg(args, SparkU32);
		SparkU32* indices = va_arg(args, SparkU32*);
		SparkU32 indices_size = va_arg(args, SparkU32);

		handle =
			SparkCreateStaticMeshI(vertices, vertices_size, indices, indices_size);
	}
	else if (strcmp(type, SPARK_RESOURCE_TYPE_DYNAMIC_MESH) == 0) {
		SparkF32* vertices = va_arg(args, SparkF32*);
		SparkU32 vertices_size = va_arg(args, SparkU32);
		SparkU32* indices = va_arg(args, SparkU32*);
		SparkU32 indices_size = va_arg(args, SparkU32);

		handle =
			SparkCreateDynamicMeshI(vertices, vertices_size, indices, indices_size);
	}

	va_end(args);

	return handle;
}
*/

SPARKAPI SparkResource SparkCreateResource(SparkResourceManager manager,
	SparkConstString name,
	SparkHandle data) {
	if (!manager) {
		SPARK_LOG_ERROR("Invalid resource manager.");
		return SPARK_ERROR_INVALID_ARGUMENT;
	}

	SparkResource resource = SparkAllocate(sizeof(struct SparkResourceT));
	resource->name = name;
	resource->data = data;
	resource->type = manager->type;
	resource->destructor = manager->resource_destructor;

	if (SparkAddResource(manager, resource) != SPARK_SUCCESS) {
		SPARK_LOG_ERROR("Adding resource: %s", name);
	}

	return resource;
}

SPARKAPI SparkResource SparkGetResource(SparkResourceManager manager,
	SparkConstString name) {
	if (!manager) {
		SPARK_LOG_ERROR("Invalid resource manager.");
		return SPARK_NULL;
	}

	return SparkGetElementHashMap(manager->resources, name, strlen(name));
}

#pragma endregion

#pragma region MESH

SPARKAPI SparkStaticMesh SparkCreateStaticMesh(SparkApplication app, SparkVertex vertices[],
	SparkU32 vertices_size) {
	return SparkCreateStaticMeshI(app, vertices, vertices_size, SPARK_NULL, 0);
}

SPARKAPI SparkDynamicMesh SparkCreateDynamicMesh(SparkApplication app, SparkVertex vertices[],
	SparkU32 vertices_size) {
	return SparkCreateDynamicMeshI(app, vertices, vertices_size, SPARK_NULL, 0);
}

SPARKAPI SparkStaticMesh SparkCreateStaticMeshI(
	SparkApplication app,
	SparkVertex vertices[],
	SparkU32 vertices_size,
	SparkU32 indices[],
	SparkU32 indices_size) {
	SparkStaticMesh mesh = SparkAllocate(sizeof(struct SparkStaticMeshT));
	mesh->vertices = vertices;
	mesh->vertex_count = vertices_size;
	mesh->indices = indices;
	mesh->index_count = indices_size;

	mesh->vertex_buffer = __SparkCreateVertexBuffer(app->window, vertices, sizeof(SparkVertex) * vertices_size);

	if (indices_size > 0)
		mesh->index_buffer = __SparkCreateIndexBuffer(app->window, indices, sizeof(SparkU32) * indices_size);
	else
		mesh->index_buffer = SPARK_NULL;

	return mesh;
}

SPARKAPI SparkDynamicMesh SparkCreateDynamicMeshI(
	SparkApplication app,
	SparkVertex vertices[],
	SparkU32 vertices_size,
	SparkU32 indices[],
	SparkU32 indices_size) {
	SparkDynamicMesh mesh = SparkAllocate(sizeof(struct SparkDynamicMeshT));
	mesh->vertices = vertices;
	mesh->vertex_count = vertices_size;
	mesh->indices = indices;
	mesh->index_count = indices_size;

	mesh->vertex_buffer = __SparkCreateVertexBuffer(app->window, vertices, sizeof(SparkVertex) * vertices_size);

	if (indices_size > 0)
		mesh->index_buffer = __SparkCreateIndexBuffer(app->window, indices, sizeof(SparkU32) * indices_size);
	else
		mesh->index_buffer = SPARK_NULL;

	return mesh;
}

SPARKAPI SparkVoid SparkDestroyStaticMesh(SparkStaticMesh mesh) {
	if (mesh->vertex_buffer) {
		vkDestroyBuffer(mesh->vertex_buffer->device, mesh->vertex_buffer->buffer, SPARK_NULL);
		vkFreeMemory(mesh->vertex_buffer->device, mesh->vertex_buffer->memory, SPARK_NULL);
		SparkFree(mesh->vertex_buffer);
	}
	if (mesh->index_buffer) {
		vkDestroyBuffer(mesh->index_buffer->device, mesh->index_buffer->buffer, SPARK_NULL);
		vkFreeMemory(mesh->index_buffer->device, mesh->index_buffer->memory, SPARK_NULL);
		SparkFree(mesh->index_buffer);
	}
	SparkFree(mesh);
}

SPARKAPI SparkVoid SparkDestroyDynamicMesh(SparkDynamicMesh mesh) {
	if (mesh->vertex_buffer) {
		vkDestroyBuffer(mesh->vertex_buffer->device, mesh->vertex_buffer->buffer, SPARK_NULL);
		vkFreeMemory(mesh->vertex_buffer->device, mesh->vertex_buffer->memory, SPARK_NULL);
		SparkFree(mesh->vertex_buffer);
	}
	if (mesh->index_buffer) {
		vkDestroyBuffer(mesh->index_buffer->device, mesh->index_buffer->buffer, SPARK_NULL);
		vkFreeMemory(mesh->index_buffer->device, mesh->index_buffer->memory, SPARK_NULL);
		SparkFree(mesh->index_buffer);
	}
	SparkFree(mesh);
}


#pragma endregion

#pragma region MATERIAL

SPARKAPI SparkMaterial SparkCreateMaterial() { return SPARK_NULL; }

SPARKAPI SparkVoid SparkDestroyMaterial(SparkMaterial material) {
	SparkFree(material);
}

#pragma endregion

#pragma region MODEL

SPARKAPI SparkStaticModel SparkCreateStaticModel(SparkStaticMesh mesh,
	SparkMaterial material) {
	SparkStaticModel model = SparkAllocate(sizeof(struct SparkStaticModelT));
	model->mesh = mesh;
	model->material = material;
	return model;
}

SPARKAPI SparkVoid SparkDestroyStaticModel(SparkStaticModel model) {
	SparkFree(model);
}

SPARKAPI SparkDynamicModel SparkCreateDynamicModel(SparkDynamicMesh mesh,
	SparkMaterial material) {
	SparkDynamicModel model = SparkAllocate(sizeof(struct SparkDynamicModelT));
	model->mesh = mesh;
	model->material = material;
	return model;
}

SPARKAPI SparkVoid SparkDestroyDynamicModel(SparkDynamicModel model) {
	SparkFree(model);
}

#pragma endregion

#pragma region SHADER

SPARKAPI SparkShader SparkCreateShader(SparkApplication app,
	SparkShaderType type,
	SparkConstString filename) {
	return SparkCreateShaderE(app, type, filename, "main");
}

SPARKAPI SparkShader SPARKCALL SparkCreateShaderE(SparkApplication app,
	SparkShaderType type,
	SparkConstString filename,
	SparkConstString entry) {
	SparkShader shader = SparkAllocate(sizeof(struct SparkShaderT));
	shader->type = type;
	shader->entry_point = entry;
	shader->device = app->window->device;
	shader->filename = filename;

	SparkCompileShaderToSpirv(filename,
		type,
		&shader->code,
		&shader->code_size);

	VkShaderModuleCreateInfo create_info = { 0 };
	create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	create_info.codeSize = shader->code_size;
	create_info.pCode = (SparkU32*)shader->code;

	if (vkCreateShaderModule(shader->device, &create_info, SPARK_NULL, &shader->module) != VK_SUCCESS) {
		SPARK_LOG_ERROR("Failed to create shader module for %s!", filename);
		SparkFree(shader->code);
		SparkFree(shader);
		return SPARK_NULL;
	}

	return shader;
}

SPARKAPI SparkVoid SPARKCALL SparkDestroyShader(SparkShader shader) {
	if (!shader) return;

	vkDestroyShaderModule(shader->device, shader->module, SPARK_NULL);
	SparkFree(shader->code);
	SparkFree(shader);
}


#pragma endregion

#pragma region FONT

SPARKAPI SparkFont SparkCreateFont(SparkConstString file_path, SparkU32 size) {
	return SPARK_NULL;
}

SPARKAPI SparkVoid SparkDestroyFont(SparkFont font) { SparkFree(font); }

#pragma endregion

#pragma region SCENE

SPARKAPI SparkScene SPARKCALL SparkCreateScene(SparkVec4 sky_color) {
	SparkScene scene = SparkAllocate(sizeof(struct SparkSceneT));
	scene->sky_color = sky_color;

	return scene;
}

SPARKAPI SparkVoid SPARKCALL SparkDestroyScene(SparkScene scene) {
	SparkFree(scene);
}

#pragma endregion

#pragma region AI

SPARKAPI SparkAIBehavior SPARKCALL
SparkCreateAIBehavior(SparkConstString type) {
	return SparkAllocate(sizeof(struct SparkAIBehaviorT));
}

SPARKAPI SparkVoid SPARKCALL SparkDestroyAIBehavior(SparkAIBehavior behavior) {
	SparkFree(behavior);
}

#pragma endregion

#pragma region APPLICATION

typedef struct SparkQueryTaskArgT {
	SparkApplication app;
	SparkApplicationQueryFunction function;
	SparkVector entities;
} *SparkQueryTaskArg;

typedef struct SparkApplicationTaskArgT {
	SparkApplication app;
	SparkApplicationUpdateFunction function;
} *SparkApplicationTaskArg;

SPARKAPI SPARKSTATIC SparkVoid __SparkQueryTaskFunction(SparkHandle arg) {
	SparkQueryTaskArg task_arg = (SparkQueryTaskArg)arg;
	task_arg->function(task_arg->app, task_arg->entities);
	SparkFree(task_arg);
}

SPARKAPI SPARKSTATIC SparkVoid
__SparkApplicationTaskFunction(SparkHandle task) {
	SparkApplicationTaskArg task_arg = task;

	SparkLockMutex(task_arg->app->mutex);

	task_arg->function(task_arg->app);

	SparkUnlockMutex(task_arg->app->mutex);

	SparkFree(task_arg);
}

SPARKAPI SPARKSTATIC SparkBool
__SparkApplicationKeepOpen(SparkApplication app) {
	SparkBool should_close = app->window->should_close || app->should_close;
	app->closing = should_close;
	return !should_close;
}

SPARKAPI SPARKSTATIC SparkResult
__SparkRunStartFunctions(SparkApplication app) {
	for (SparkSize i = 0; i < app->start_functions->size; i++) {
		SparkStartHandlerFunction function =
			SparkGetElementVector(app->start_functions, i);

		if (function->thread_settings.first) {
			SparkApplicationTaskArg task_arg =
				SparkAllocate(sizeof(struct SparkApplicationTaskArgT));
			task_arg->app = app;
			task_arg->function = function->function;

			SparkAddTaskThreadPool(
				app->thread_pool, (SparkThreadFunction)__SparkApplicationTaskFunction,
				task_arg, function->thread_settings.second);
		}
		else {
			function->function(app);
		}
	}

	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkResult __SparkStopApplication(SparkApplication app) {
	for (SparkSize i = 0; i < app->stop_functions->size; i++) {
		SparkStopHandlerFunction function =
			SparkGetElementVector(app->stop_functions, i);
		if (function->thread_settings.first) {
			SparkApplicationTaskArg task_arg =
				SparkAllocate(sizeof(struct SparkApplicationTaskArgT));
			task_arg->app = app;
			task_arg->function = function->function;

			SparkAddTaskThreadPool(
				app->thread_pool, (SparkThreadFunction)__SparkApplicationTaskFunction,
				task_arg, function->thread_settings.second);
		}
		else {
			function->function(app);
		}
	}
	SparkDestroyApplication(app);
	return SPARK_SUCCESS;
}

SPARKAPI SPARKSTATIC SparkVoid __SparkRunUpdateFunctions(SparkApplication app) {
	// Run update functions
	for (SparkSize i = 0; i < app->update_functions->size; ++i) {
		SparkUpdateHandlerFunction function = app->update_functions->elements[i];
		if (function->thread_settings.first) {
			// Add to thread pool
			SparkApplicationTaskArg task_arg = SparkAllocate(sizeof(struct SparkApplicationTaskArgT));
			task_arg->app = app;
			task_arg->function = function->function;

			SparkAddTaskThreadPool(
				app->thread_pool, (SparkThreadFunction)__SparkApplicationTaskFunction,
				task_arg, function->thread_settings.second);
		}
		else {
			// Run directly
			function->function(app);
		}
	}

	// Run query functions
	for (SparkSize i = 0; i < app->query_functions->size; ++i) {
		SparkQueryHandlerFunction handler = app->query_functions->elements[i];
		SparkQuery query = handler->query;
		SparkVector matching_entities = SparkPerformQuery(app->ecs, query);

		if (handler->thread_settings.first) {
			// Prepare arguments for the thread function
			SparkQueryTaskArg task_arg = SparkAllocate(sizeof(struct SparkQueryTaskArgT));
			task_arg->app = app;
			task_arg->entities = matching_entities;
			task_arg->function = handler->function;

			SparkAddTaskThreadPool(
				app->thread_pool,
				(SparkThreadFunction)__SparkQueryTaskFunction,
				task_arg,
				handler->thread_settings.second
			);
		}
		else {
			// Run directly
			handler->function(app, matching_entities);
		}
	}

	// Wait for tasks that need to be waited upon
	SparkWaitThreadPool(app->thread_pool);
}

SPARKAPI SPARKSTATIC SparkResult
__SparkUpdateApplication(SparkApplication app) {
	while (__SparkApplicationKeepOpen(app)) {
		__SparkRunUpdateFunctions(app);
		__SparkUpdateWindow(app);
	}

	return __SparkStopApplication(app);
}

SPARKAPI SPARKSTATIC SparkVoid __SparkInitializeResourceDefaults(SparkApplication app) {
	SparkCreateResourceApplication(app,
		SPARK_RESOURCE_TYPE_SCENE,
		SPARK_DEFAULT_SCENE,
		SparkCreateScene((SparkVec4) { 0.2f, 0.3f, 0.4f, 1.0f }));
}

SPARKAPI SPARKSTATIC SparkVoid
__SparkInitializeResourceManagerApplication(SparkApplication app) {
	SparkResourceManager smesh_manager = SparkCreateResourceManager(SPARK_RESOURCE_TYPE_STATIC_MESH, SparkDestroyStaticMesh);
	SparkResourceManager dmesh_manager = SparkCreateResourceManager(SPARK_RESOURCE_TYPE_DYNAMIC_MESH, SparkDestroyDynamicMesh);
	SparkResourceManager texture_manager = SparkCreateResourceManager(SPARK_RESOURCE_TYPE_TEXTURE, SparkDestroyTexture);
	SparkResourceManager shader_manager = SparkCreateResourceManager(SPARK_RESOURCE_TYPE_SHADER, SparkDestroyShader);
	SparkResourceManager material_manager = SparkCreateResourceManager(SPARK_RESOURCE_TYPE_MATERIAL, SparkDestroyMaterial);
	SparkResourceManager font_manager = SparkCreateResourceManager(SPARK_RESOURCE_TYPE_FONT, SparkDestroyFont);
	SparkResourceManager audio_manager = SparkCreateResourceManager(SPARK_RESOURCE_TYPE_AUDIO, SparkDestroyAudio);
	SparkResourceManager smodel_manager = SparkCreateResourceManager(SPARK_RESOURCE_TYPE_STATIC_MODEL, SparkDestroyStaticModel);
	SparkResourceManager dmodel_manager = SparkCreateResourceManager(SPARK_RESOURCE_TYPE_DYNAMIC_MODEL, SparkDestroyDynamicModel);
	SparkResourceManager scene_manager = SparkCreateResourceManager(SPARK_RESOURCE_TYPE_SCENE, SparkDestroyScene);
	SparkResourceManager ai_manager = SparkCreateResourceManager(SPARK_RESOURCE_TYPE_AI_BEHAVIOR, SparkDestroyAIBehavior);
	SparkResourceManager gp_manager = SparkCreateResourceManager(SPARK_RESOURCE_TYPE_GRAPHICS_PIPELINE_CONFIG, SparkDestroyGraphicsPipelineConfig);

	SparkInsertHashMap(app->resource_manager, SPARK_RESOURCE_TYPE_STATIC_MESH,
		strlen(SPARK_RESOURCE_TYPE_STATIC_MESH), smesh_manager);
	SparkInsertHashMap(app->resource_manager, SPARK_RESOURCE_TYPE_DYNAMIC_MESH,
		strlen(SPARK_RESOURCE_TYPE_DYNAMIC_MESH), dmesh_manager);
	SparkInsertHashMap(app->resource_manager, SPARK_RESOURCE_TYPE_TEXTURE,
		strlen(SPARK_RESOURCE_TYPE_TEXTURE), texture_manager);
	SparkInsertHashMap(app->resource_manager, SPARK_RESOURCE_TYPE_SHADER,
		strlen(SPARK_RESOURCE_TYPE_SHADER), shader_manager);
	SparkInsertHashMap(app->resource_manager, SPARK_RESOURCE_TYPE_MATERIAL,
		strlen(SPARK_RESOURCE_TYPE_MATERIAL), material_manager);
	SparkInsertHashMap(app->resource_manager, SPARK_RESOURCE_TYPE_FONT,
		strlen(SPARK_RESOURCE_TYPE_FONT), font_manager);
	SparkInsertHashMap(app->resource_manager, SPARK_RESOURCE_TYPE_AUDIO,
		strlen(SPARK_RESOURCE_TYPE_AUDIO), audio_manager);
	SparkInsertHashMap(app->resource_manager, SPARK_RESOURCE_TYPE_STATIC_MODEL,
		strlen(SPARK_RESOURCE_TYPE_STATIC_MODEL), smodel_manager);
	SparkInsertHashMap(app->resource_manager, SPARK_RESOURCE_TYPE_DYNAMIC_MODEL,
		strlen(SPARK_RESOURCE_TYPE_DYNAMIC_MODEL), dmodel_manager);
	SparkInsertHashMap(app->resource_manager, SPARK_RESOURCE_TYPE_SCENE,
		strlen(SPARK_RESOURCE_TYPE_SCENE), scene_manager);
	SparkInsertHashMap(app->resource_manager, SPARK_RESOURCE_TYPE_AI_BEHAVIOR,
		strlen(SPARK_RESOURCE_TYPE_AI_BEHAVIOR), ai_manager);
	SparkInsertHashMap(app->resource_manager, SPARK_RESOURCE_TYPE_GRAPHICS_PIPELINE_CONFIG,
		strlen(SPARK_RESOURCE_TYPE_GRAPHICS_PIPELINE_CONFIG), gp_manager);

	__SparkInitializeResourceDefaults(app);
}

SPARKAPI SparkApplication SparkCreateApplication(SparkWindow window,
	SparkSize thread_count) {
	SparkApplication app = SparkAllocate(sizeof(struct SparkApplicationT));
	app->event_handler = window->window_data->event_handler;
	app->window = window;
	app->ecs = SparkCreateEcs(app->event_handler);
	app->ecs->event_handler = app->event_handler;
	app->start_functions = SparkCreateVector(2, SPARK_NULL, SparkFree);
	app->stop_functions = SparkCreateVector(2, SPARK_NULL, SparkFree);
	app->update_functions = SparkCreateVector(2, SPARK_NULL, SparkFree);
	app->thread_pool = SparkCreateThreadPool(thread_count);
	app->resource_manager =
		SparkCreateHashMap(8, SparkStringHash, SparkStringCompare, SPARK_NULL,
			SPARK_NULL, SparkDestroyResourceManager);
	app->query_functions = SparkCreateVector(2, SPARK_NULL, SparkFree);
	app->event_functions = SparkCreateVector(2, SPARK_NULL, SparkFree);
	app->query_event_functions = SparkCreateHashMap(2, SparkIntegerHash, SparkIntegerCompare, SPARK_NULL, SPARK_NULL, SparkDestroyVector);
	app->event_handler->application = app;
	app->event_handler->ecs = app->ecs;
	app->should_close = SPARK_FALSE;
	app->closing = SPARK_FALSE;
	SparkInitMutex(app->mutex);

	if (__SparkInitializeVulkan(app) != SPARK_SUCCESS) {
		SPARK_LOG_FATAL("Failed to initialize Vulkan!");
		glfwDestroyWindow(window->window);
		SparkDestroyWindowData(window->window_data);
		SparkFree(window);
		glfwTerminate();
		return SPARK_NULL;
	};

	__SparkInitializeResourceManagerApplication(app);

	return app;
}

SPARKAPI SparkVoid SparkDestroyApplication(SparkApplication app) {
	SparkDestroyEcs(app->ecs);
	SparkDestroyEventHandler(app->event_handler);
	SparkDestroyVector(app->start_functions);
	SparkDestroyVector(app->stop_functions);
	SparkDestroyVector(app->update_functions);
	SparkDestroyVector(app->query_functions);
	SparkDestroyVector(app->event_functions);
	SparkDestroyHashMap(app->query_event_functions);
	SparkDestroyHashMap(app->resource_manager);
	SparkDestroyThreadPool(app->thread_pool);
	SparkDestroyWindow(app->window);
	SparkDestroyMutex(app->mutex);
	SparkFree(app);
}

SPARKAPI SparkResult SparkStartApplication(SparkApplication app) {
	if (__SparkRunStartFunctions(app) != SPARK_SUCCESS) {
		return SPARK_ERROR_INVALID;
	}

	if (__SparkUpdateApplication(app) != SPARK_SUCCESS) {
		return SPARK_ERROR_INVALID;
	}

	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkStopApplication(SparkApplication app) {
	app->should_close = SPARK_TRUE;
	app->closing = SPARK_TRUE;
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkAddStartFunctionApplication(
	SparkApplication app, SparkApplicationStartFunction function,
	SparkPair thread_settings) {
	SparkStartHandlerFunction start_function =
		SparkAllocate(sizeof(struct SparkStartHandlerFunctionT));
	start_function->function = function;
	start_function->thread_settings = thread_settings;
	return SparkPushBackVector(app->start_functions, start_function);
}

SPARKAPI SparkResult SparkAddUpdateFunctionApplication(
	SparkApplication app, SparkApplicationUpdateFunction function,
	SparkPair thread_settings) {
	SparkUpdateHandlerFunction update_function =
		SparkAllocate(sizeof(struct SparkUpdateHandlerFunctionT));
	update_function->function = function;
	update_function->thread_settings = thread_settings;
	return SparkPushBackVector(app->update_functions, update_function);
}

SPARKAPI SparkResult SparkAddStopFunctionApplication(
	SparkApplication app, SparkApplicationStopFunction function,
	SparkPair thread_settings) {
	SparkStopHandlerFunction stop_function =
		SparkAllocate(sizeof(struct SparkStopHandlerFunctionT));
	stop_function->function = function;
	stop_function->thread_settings = thread_settings;
	return SparkPushBackVector(app->stop_functions, stop_function);
}

SPARKAPI SparkResult SparkAddEventFunctionApplication(
	SparkApplication app, SparkEventType event_type,
	SparkApplicationEventFunction function, SparkPair thread_settings) {
	return SparkAddEventListener(app->event_handler, event_type, function,
		thread_settings);
}

SPARKAPI SparkResult SparkAddQueryFunctionApplication(
	SparkApplication app,
	SparkQuery query,
	SparkApplicationQueryFunction function,
	SparkPair thread_settings) {
	SparkQueryHandlerFunction handler = SparkAllocate(sizeof(struct SparkQueryHandlerFunctionT));
	handler->query = query;
	handler->function = function;
	handler->thread_settings = thread_settings;

	SparkPushBackVector(app->query_functions, handler);
	return SPARK_SUCCESS;
}

SPARKAPI SparkResult SparkAddQueryEventFunctionApplication(
	SparkApplication app,
	SparkEventType event_type,
	SparkQuery query,
	SparkApplicationQueryEventFunction function,
	SparkPair thread_settings) {
	return SparkAddQueryEventListener(app->event_handler, event_type, query, function, thread_settings);
}

SPARKAPI SparkResult SparkDispatchEventApplication(SparkApplication app,
	SparkEvent event) {
	return SparkDispatchEvent(app->event_handler, event);
}

SPARKAPI SparkResource SparkCreateResourceApplication(SparkApplication app,
	SparkConstString type,
	SparkConstString name,
	SparkHandle data) {
	SparkResourceManager rm =
		SparkGetElementHashMap(app->resource_manager, type, strlen(type));
	return SparkCreateResource(rm, name, data);
}

SPARKAPI SparkResource SparkGetResourceApplication(SparkApplication app,
	SparkConstString type,
	SparkConstString name) {
	SparkResourceManager rm =
		SparkGetElementHashMap(app->resource_manager, type, strlen(type));
	return SparkGetResource(rm, name);
}

SPARKAPI SparkResult SparkAddResourceApplication(SparkApplication app,
	SparkConstString type,
	SparkResource resource) {
	SparkResourceManager rm =
		SparkGetElementHashMap(app->resource_manager, type, strlen(type));
	return SparkAddResource(rm, resource);
}

SPARKAPI SparkResult SparkRemoveResourceApplication(SparkApplication app,
	SparkConstString type,
	SparkConstString name) {
	SparkResourceManager rm =
		SparkGetElementHashMap(app->resource_manager, type, strlen(type));
	return SparkRemoveResource(rm, name);
}

SPARKAPI SparkResult
SparkAddResourceManagerApplication(SparkApplication app, SparkConstString type,
	SparkFreeFunction resource_destructor) {
	SparkResourceManager rm =
		SparkCreateResourceManager(type, resource_destructor);
	return SparkInsertHashMap(app->resource_manager, type, strlen(type), rm);
}

SPARKAPI SparkGraphicsPipelineConfig SparkCreateGraphicsPipelineConfig(
	SparkApplication app,
	SparkShader vert,
	SparkShader frag,
	SparkShader comp,
	SparkShader geom,
	SparkShader tess_cont,
	SparkShader tess_eval
) {
	SparkGraphicsPipelineConfig gp = SparkAllocate(sizeof(struct SparkGraphicsPipelineConfigT));
	gp->application = app;
	gp->vertex_shader = vert;
	gp->fragment_shader = frag;
	gp->compute_shader = comp;
	gp->geometry_shader = geom;
	gp->tess_control_shader = tess_cont;
	gp->tess_evaluation_shader = tess_eval;
	gp->pipeline_layout = VK_NULL_HANDLE;
	gp->pipeline = VK_NULL_HANDLE;
	gp->render_pass = app->window->render_pass;
	gp->owns_pipeline_layout = SPARK_FALSE;
	gp->patch_control_points = 0;

	if (__SparkCreateGraphicsPipeline(app, gp) != SPARK_SUCCESS) {
		SparkFree(gp);
		return NULL;
	}

	return gp;
}

SPARKAPI SparkVoid SparkDestroyGraphicsPipelineConfig(SparkGraphicsPipelineConfig gp) {
	if (!gp) {
		return;
	}

	VkDevice device = gp->application->window->device;

	if (gp->pipeline != VK_NULL_HANDLE) {
		vkDestroyPipeline(device, gp->pipeline, SPARK_NULL);
		gp->pipeline = VK_NULL_HANDLE;
	}

	if (gp->owns_pipeline_layout && gp->pipeline_layout != VK_NULL_HANDLE) {
		vkDestroyPipelineLayout(device, gp->pipeline_layout, SPARK_NULL);
		gp->pipeline_layout = VK_NULL_HANDLE;
	}

	SparkFree(gp);
}

SPARKAPI SparkMaterial SparkGetMaterialApplication(SparkApplication app, SparkConstString name) {
	SparkResourceManager material_manager = SparkGetElementHashMap(app->resource_manager, SPARK_RESOURCE_TYPE_MATERIAL, strlen(SPARK_RESOURCE_TYPE_MATERIAL));
	SparkResource resource = SparkGetResource(material_manager, name);
	if (resource) {
		return (SparkMaterial)resource->data;
	}
	return SPARK_NULL;
}

SPARKAPI SparkStaticMesh SparkGetStaticMeshApplication(SparkApplication app, SparkConstString name) {
	SparkResourceManager mesh_manager = SparkGetElementHashMap(app->resource_manager, SPARK_RESOURCE_TYPE_STATIC_MESH, strlen(SPARK_RESOURCE_TYPE_STATIC_MESH));
	SparkResource resource = SparkGetResource(mesh_manager, name);
	if (resource) {
		return resource->data;
	}
	return SPARK_NULL;
}

SPARKAPI SparkDynamicMesh SparkGetDynamicMeshApplication(SparkApplication app, SparkConstString name) {
	SparkResourceManager mesh_manager = SparkGetElementHashMap(app->resource_manager, SPARK_RESOURCE_TYPE_STATIC_MESH, strlen(SPARK_RESOURCE_TYPE_STATIC_MESH));
	SparkResource resource = SparkGetResource(mesh_manager, name);
	if (resource) {
		return resource->data;
	}
	return SPARK_NULL;
}

#pragma endregion