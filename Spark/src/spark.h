#ifndef __SPARK_H__
#define __SPARK_H__

/*#ifdef __cplusplus
extern "C" {
#endif
*/

typedef unsigned char SparkU8;
typedef char SparkI8;
typedef unsigned short SparkU16;
typedef short SparkI16;
typedef unsigned int SparkU32;
typedef int SparkI32;
typedef unsigned long long SparkU64;
typedef long long SparkI64;
typedef float SparkF32;
typedef double SparkF64;
typedef SparkU8 SparkBool;
typedef SparkI32 SparkResult;
typedef void SparkVoid;
typedef void* SparkHandle;
typedef char* SparkString;
typedef const char* SparkConstString;
typedef SparkU8* SparkBuffer;
typedef const SparkU8* SparkConstBuffer;
typedef SparkU32 SparkSize;
typedef SparkU32 SparkIndex;
typedef SparkU32 SparkCount;
typedef SparkU32 SparkOffset;
typedef SparkU32 SparkLength;
typedef SparkU32 SparkHash;
typedef SparkU32 SparkColor;
typedef SparkU32 SparkTime;
typedef SparkU32 SparkDuration;
typedef SparkU32 SparkFrequency;
typedef SparkU32 SparkRate;

typedef enum SparkType {
    // Boolean values
    SPARK_FALSE = 0,
    SPARK_TRUE = 1,

    // General statuses
    SPARK_SUCCESS = 0,
    SPARK_FAILURE = -1,
    SPARK_ERROR = -2,

    // Validation statuses
    SPARK_VALID = 1,
    SPARK_INVALID = 0,

    // Null and undefined values
    SPARK_NULL = 0,
    SPARK_NONE = 0,
    SPARK_UNKNOWN = -4,

    // Additional statuses
    SPARK_PENDING = -5,
    SPARK_IN_PROGRESS = -6,
    SPARK_COMPLETE = 2,
    SPARK_TIMEOUT = -7,
    SPARK_CANCELLED = -8,
    SPARK_NOT_IMPLEMENTED = -9,
    SPARK_ACCESS_DENIED = -10,
    SPARK_NOT_FOUND = -11,
    SPARK_BUSY = -12,
    SPARK_OVERLOADED = -13,
    SPARK_DISCONNECTED = -14,
    SPARK_CONNECTED = 3,
    SPARK_RETRY = -15,
    SPARK_DEPRECATED = -16,
    SPARK_UNSUPPORTED = -17,
    SPARK_INITIALIZED = 4,
    SPARK_UNINITIALIZED = -18,
    SPARK_ENABLED = 5,
    SPARK_DISABLED = -19,
    SPARK_READ_ONLY = -20,
    SPARK_WRITE_ONLY = -21,
    SPARK_READ_WRITE = 6,
    SPARK_SUCCESS_PARTIAL = -22,
    SPARK_INVALID_ARGUMENT = -23,
    SPARK_OUT_OF_MEMORY = -24,
    SPARK_OVERFLOW = -25,
    SPARK_UNDERFLOW = -26,
    SPARK_END_OF_FILE = -27,
    SPARK_PERMISSION_DENIED = -28,
    SPARK_BAD_REQUEST = -29,
    SPARK_CONFLICT = -30,
    SPARK_PRECONDITION_FAILED = -31
} SparkType;

#define SPARK_ASSERT(condition) if (!(condition)) { return SPARK_INVALID; }
#define SPARK_ASSERT_NULL(pointer) if ((pointer) == SPARK_NULL) { return SPARK_INVALID; }
#define SPARK_ASSERT_NOT_NULL(pointer) if ((pointer) != SPARK_NULL) { return SPARK_INVALID; }
#define SPARK_ASSERT_TRUE(condition) if (!(condition)) { return SPARK_INVALID; }
#define SPARK_ASSERT_FALSE(condition) if ((condition)) { return SPARK_INVALID; }
#define SPARK_ASSERT_SUCCESS(result) if ((result) != SPARK_SUCCESS) { return SPARK_INVALID; }
#define SPARK_ASSERT_FAILURE(result) if ((result) == SPARK_SUCCESS) { return SPARK_INVALID; }
#define SPARK_ASSERT_VALID(result) if ((result) != SPARK_VALID) { return SPARK_INVALID; }
#define SPARK_ASSERT_INVALID(result) if ((result) == SPARK_VALID) { return SPARK_INVALID; }


#define SPARK_INVALID_FUNCTION_CALL SPARK_ASSERT_FALSE(SPARK_TRUE)
#define SPARK_INVALID_FUNCTION_CALL_RETURN SPARK_ASSERT_FALSE(SPARK_TRUE); return SPARK_INVALID
#define SPARK_INVALID_FUNCTION_CALL_RETURN_NULL SPARK_ASSERT_FALSE(SPARK_TRUE); return SPARK_NULL







/*
#ifdef __cplusplus
}
#endif
*/
#endif