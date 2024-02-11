#include "unity/unity.h"
#include "../include/find.h"


void setUp(void) {
    // Code to run before each test
}

void tearDown(void) {
    // Code to run after each test
}

void test_add(void) {
    TEST_ASSERT_EQUAL(7, 7);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_add);
    return UNITY_END();
}
