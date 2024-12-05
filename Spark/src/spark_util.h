#ifndef __SPARK_UTIL_H__
#define __SPARK_UTIL_H__

#ifndef __SPARK_H__
#error "spark.h must be included before spark_util.h!"
#endif

#if !defined(SPARK_NO_DEBUG) && !defined(NDEBUG) && !defined(RELEASE)
#define SPARK_LOG_DEBUG(message, ...)                                          \
  SparkLogImpl(SPARK_LOG_LEVEL_DEBUG, message, ##__VA_ARGS__)
#else
#define SPARK_LOG_DEBUG(message, ...)
#endif
#ifndef SPARK_NO_INFO
#define SPARK_LOG_INFO(message, ...)                                           \
  SparkLogImpl(SPARK_LOG_LEVEL_INFO, message, ##__VA_ARGS__)
#else
#define SPARK_LOG_INFO(message, ...)
#endif
#ifndef SPARK_NO_WARN
#define SPARK_LOG_WARN(message, ...)                                           \
  SparkLogImpl(SPARK_LOG_LEVEL_WARN, message, ##__VA_ARGS__)
#else
#define SPARK_LOG_WARN(message, ...)
#endif
#ifndef SPARK_NO_ERROR
#define SPARK_LOG_ERROR(message, ...)                                          \
  SparkLogImpl(SPARK_LOG_LEVEL_ERROR, message, ##__VA_ARGS__)
#else
#define SPARK_LOG_ERROR(message, ...)
#endif
#define SPARK_LOG_FATAL(message, ...)                                          \
  SparkLogImpl(SPARK_LOG_LEVEL_FATAL, message, ##__VA_ARGS__)

#if __STDC_VERSION__ >= 201112L

#define SparkSerializeString(serializer, data)                                 \
  SparkSerializeData(serializer, (const char *)(unsigned long long)data,       \
                     strlen((const char *)(unsigned long long)data))

#define SparkSerializeTrivialType(serializer, data)                            \
  SparkSerializeTrivial(serializer, &(data), sizeof(data))

// SparkSerializeDefault Macro Using _Generic
#define SparkSerializeDefault(serializer, data)                                \
  _Generic((data),                                                             \
      const char *: SparkSerializeString(serializer, data),                    \
      char *: SparkSerializeString(serializer, data),                          \
      SparkVector: SparkSerializeVector(                                       \
               serializer, (const char *)(unsigned long long)data),            \
      default: SparkSerializeTrivialType(serializer, data))

// Serialization Function When Size is Provided
#define SparkSerializeWithSize(serializer, data, size)                         \
  SparkSerializeData(serializer, data, size)

// Helper Macro to Select the Appropriate Serialization Function Based on
// Argument Count
#define GET_SPARKSERIALIZE(_1, _2, _3, NAME, ...) NAME

// Main SparkSerialize Macro
#define SparkSerialize(...)                                                    \
  GET_SPARKSERIALIZE(__VA_ARGS__, SparkSerializeWithSize,                      \
                     SparkSerializeDefault)                                    \
  (__VA_ARGS__)

#define SparkDeserializeDefault(deserializer, data)                            \
  _Generic((data),                                                             \
      SparkVector: SparkDeserializeVector(deserializer, &(data)),              \
      default: SparkDeserializeTrivial(deserializer, &(data), sizeof(data)))

#define SparkDeserializeWithSize(deserializer, data, size)                     \
  _Generic((data),                                                             \
      char *: SparkDeserializeString(deserializer, &(data), &(size)),          \
      const char *: SparkDeserializeString(deserializer, &(data), &(size)),    \
      default: SparkDeserializeData(deserializer, &(data), &(size)))
#define GET_SPARKDESERIALIZE(_1, _2, _3, NAME, ...) NAME

#define SparkDeserialize(...)                                                  \
  GET_SPARKDESERIALIZE(__VA_ARGS__, SparkDeserializeWithSize,                  \
                       SparkDeserializeDefault)                                \
  (__VA_ARGS__)

#endif

/* Clear mask bits */
#define SPARK_COLOR_BUFFER_BIT 0x00004000
#define SPARK_DEPTH_BUFFER_BIT 0x00000100
#define SPARK_STENCIL_BUFFER_BIT 0x00000400

#define SPARK_PACKET_MAX_SIZE 4096

#define SPARK_DEFAULT_POSITION (SparkVec3){0.0f, 0.0f, 0.0f}
#define SPARK_DEFAULT_ROTATION (SparkQuat){0.0f, 0.0f, 0.0f, 1.0f}
#define SPARK_DEFAULT_SCALE (SparkVec3){0.0f, 0.0f, 0.0f}

#endif