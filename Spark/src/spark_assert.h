#ifndef __SPARK_ASSERT_H__
#define __SPARK_ASSERT_H__

#include <assert.h>
#include "spark_types.h"

#define SPARK_ASSERT(condition, message)                                       \
  if (!(condition)) {                                                          \
    assert(SPARK_FALSE &&message);                                             \
  }

#define SPARK_ASSERT_NULL(pointer)                                             \
  SPARK_ASSERT(pointer != SPARK_NULL, "Pointer is null")
#define SPARK_ASSERT_NOT_NULL(pointer)                                         \
  SPARK_ASSERT(pointer != SPARK_NULL, "Pointer is not null")
#define SPARK_ASSERT_SUCCESS(result)                                           \
  SPARK_ASSERT(result == SPARK_SUCCESS, "Result is success")
#define SPARK_ASSERT_FAILURE(result)                                           \
  SPARK_ASSERT(result == SPARK_FAILURE, "Result is failure")
#define SPARK_ASSERT_VALID(result)                                             \
  SPARK_ASSERT(result == SPARK_VALID, "Result is valid")
#define SPARK_ASSERT_INVALID(result)                                           \
  SPARK_ASSERT(result == SPARK_INVALID, "Result is invalid")
#define SPARK_ASSERT_NOT_IMPLEMENTED(result)                                   \
  SPARK_ASSERT(result == SPARK_NOT_IMPLEMENTED, "Result is not implemented")
#define SPARK_ASSERT_NULL_OR_VALID(result)                                     \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_VALID,                  \
               "Result is null or valid")
#define SPARK_ASSERT_NULL_OR_INVALID(result)                                   \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_INVALID,                \
               "Result is null or invalid")
#define SPARK_ASSERT_NULL_OR_SUCCESS(result)                                   \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_SUCCESS,                \
               "Result is null or success")
#define SPARK_ASSERT_NULL_OR_FAILURE(result)                                   \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_FAILURE,                \
               "Result is null or failure")
#define SPARK_ASSERT_NULL_OR_PENDING(result)                                   \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_PENDING,                \
               "Result is null or pending")
#define SPARK_ASSERT_NULL_OR_IN_PROGRESS(result)                               \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_IN_PROGRESS,            \
               "Result is null or in progress")
#define SPARK_ASSERT_NULL_OR_COMPLETE(result)                                  \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_COMPLETE,               \
               "Result is null or complete")
#define SPARK_ASSERT_NULL_OR_TIMEOUT(result)                                   \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_TIMEOUT,                \
               "Result is null or timeout")
#define SPARK_ASSERT_NULL_OR_CANCELLED(result)                                 \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_CANCELLED,              \
               "Result is null or cancelled")
#define SPARK_ASSERT_NULL_OR_NOT_IMPLEMENTED(result)                           \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_NOT_IMPLEMENTED,        \
               "Result is null or not implemented")
#define SPARK_ASSERT_NULL_OR_ACCESS_DENIED(result)                             \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_ACCESS_DENIED,          \
               "Result is null or access denied")
#define SPARK_ASSERT_NULL_OR_NOT_FOUND(result)                                 \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_NOT_FOUND,              \
               "Result is null or not found")
#define SPARK_ASSERT_NULL_OR_BUSY(result)                                      \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_BUSY,                   \
               "Result is null or busy")
#define SPARK_ASSERT_NULL_OR_OVERLOADED(result)                                \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_OVERLOADED,             \
               "Result is null or overloaded")
#define SPARK_ASSERT_NULL_OR_DISCONNECTED(result)                              \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_DISCONNECTED,           \
               "Result is null or disconnected")
#define SPARK_ASSERT_NULL_OR_CONNECTED(result)                                 \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_CONNECTED,              \
               "Result is null or connected")
#define SPARK_ASSERT_NULL_OR_RETRY(result)                                     \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_RETRY,                  \
               "Result is null or retry")
#define SPARK_ASSERT_NULL_OR_DEPRECATED(result)                                \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_DEPRECATED,             \
               "Result is null or deprecated")
#define SPARK_ASSERT_NULL_OR_UNSUPPORTED(result)                               \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_UNSUPPORTED,            \
               "Result is null or unsupported")
#define SPARK_ASSERT_NULL_OR_UNINITIALIZED(result)                             \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_UNINITIALIZED,          \
               "Result is null or uninitialized")
#define SPARK_ASSERT_NULL_OR_DISABLED(result)                                  \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_DISABLED,               \
               "Result is null or disabled")
#define SPARK_ASSERT_NULL_OR_READ_ONLY(result)                                 \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_READ_ONLY,              \
               "Result is null or read only")
#define SPARK_ASSERT_NULL_OR_WRITE_ONLY(result)                                \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_WRITE_ONLY,             \
               "Result is null or write only")
#define SPARK_ASSERT_NULL_OR_OUT_OF_MEMORY(result)                             \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_OUT_OF_MEMORY,          \
               "Result is null or out of memory")
#define SPARK_ASSERT_NULL_OR_OVERFLOW(result)                                  \
  SPARK_ASSERT(result == SPARK_NULL || result == SPARK_OVERFLOW,               \
               "Result is null or overflow")

#define SPARK_CRASH_PROGRAM(reason)                                            \
  SPARK_ASSERT(SPARK_FALSE, "Program was forcibly closed for: " #reason)

#define SPARK_UNIMPLIMENTED SPARK_CRASH_PROGRAM("Unimplemented function!");

#endif