#include "unity/unity.h"
#include "../include/find.h"


void setUp(void) {
    // Code to run before each test
}

void tearDown(void) {
    // Code to run after each test
}

void test_strstr_w_option_case_insensitive_found(void) {
    flags options = CASE;
    char* result = strstr_w_option("Hello world", "World", options);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING("world", result);
}

void test_strstr_w_option_case_insensitive_found(void) {
    
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_strstr_w_option_case_insensitive_found);
    return UNITY_END();
}
