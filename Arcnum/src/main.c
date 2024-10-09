#define SPARK_DEFINE_ALL_ALIASES
#include <spark.h>
#include <stdio.h>
#include <string.h>

int main()
{
    SPARK_LOG_DEBUG("Testing HashSet");

    // Create a HashSet with an initial capacity of 16
    HashSet hset = SparkCreateHashSet(16, sizeof(string_t), FNV1AHash, SPARK_NULL, Free);

    if (hset == SPARK_NULL) {
        SPARK_LOG_ERROR("Failed to create HashSet");
        return -1;
    }

    SPARK_LOG_DEBUG("HashSet created: %p", hset);

    // Insert 100 strings into the HashSet
    for (i32 i = 0; i < 100; i++) {
        string_t str = FormatString("Value: %d", i);
        if (str == SPARK_NULL) {
            SPARK_LOG_ERROR("Failed to format string");
            SparkDestroyHashSet(hset);
            return -1;
        }

        SparkResult res = InsertHashSet(hset, str, strlen(str) + 1);
        if (res != SPARK_SUCCESS) {
            SPARK_LOG_ERROR("Failed to insert into HashSet");
            Free(str);  // Free the string since it's not stored in the HashSet
            SparkDestroyHashSet(hset);
            return -1;
        }
        // Note: The destructor will free the strings in the HashSet
    }

    SPARK_LOG_DEBUG("Inserted 100 elements into HashSet");

    // Check if the HashSet contains the inserted elements
    for (i32 i = 0; i < 100; i++) {
        string_t str = FormatString("Value: %d", i);
        if (str == SPARK_NULL) {
            SPARK_LOG_ERROR("Failed to format string");
            SparkDestroyHashSet(hset);
            return -1;
        }

        bool_t contains = ContainsHashSet(hset, str, strlen(str) + 1);
        if (!contains) {
            SPARK_LOG_ERROR("HashSet does not contain expected value: %s", str);
            Free(str);  // Free the temporary string
            SparkDestroyHashSet(hset);
            return -1;
        }
        else {
            SPARK_LOG_INFO("HashSet contains: %s", str);
        }
        Free(str);  // Free the temporary string
    }

    SPARK_LOG_DEBUG("Checked existence of all elements in HashSet");

    // Remove 50 elements from the HashSet
    for (i32 i = 0; i < 50; i++) {
        string_t str = FormatString("Value: %d", i);
        if (str == SPARK_NULL) {
            SPARK_LOG_ERROR("Failed to format string");
            SparkDestroyHashSet(hset);
            return -1;
        }

        SparkResult res = RemoveHashSet(hset, str, strlen(str) + 1);
        if (res != SPARK_SUCCESS) {
            SPARK_LOG_ERROR("Failed to remove from HashSet: %s", str);
            Free(str);  // Free the temporary string
            SparkDestroyHashSet(hset);
            return -1;
        }
        else {
            SPARK_LOG_INFO("Removed from HashSet: %s", str);
        }
        Free(str);  // Free the temporary string
    }

    SPARK_LOG_DEBUG("Removed 50 elements from HashSet");

    // Verify the HashSet's contents after removal
    for (i32 i = 0; i < 100; i++) {
        string_t str = FormatString("Value: %d", i);
        if (str == SPARK_NULL) {
            SPARK_LOG_ERROR("Failed to format string");
            SparkDestroyHashSet(hset);
            return -1;
        }

        bool_t contains = ContainsHashSet(hset, str, strlen(str) + 1);
        if (i < 50) {
            if (contains) {
                SPARK_LOG_ERROR("HashSet should not contain: %s", str);
                Free(str);
                SparkDestroyHashSet(hset);
                return -1;
            }
            else {
                SPARK_LOG_INFO("HashSet correctly does not contain: %s", str);
            }
        }
        else {
            if (!contains) {
                SPARK_LOG_ERROR("HashSet is missing expected value: %s", str);
                Free(str);
                SparkDestroyHashSet(hset);
                return -1;
            }
            else {
                SPARK_LOG_INFO("HashSet contains: %s", str);
            }
        }
        Free(str);  // Free the temporary string
    }

    SPARK_LOG_DEBUG("Verified HashSet contents after removal");

    // Clean up
    SparkDestroyHashSet(hset);

    SPARK_LOG_DEBUG("HashSet destroyed");

    return 0;
}
