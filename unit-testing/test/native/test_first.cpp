#ifdef UNIT_TEST

#include <unity.h>

#include "module1.h"

void test_module1() {
    module1_s  o;
    module1_init(&o);

    module1_set_a(&o, 17);
    TEST_ASSERT_EQUAL(module1_get_a(&o), 17);

    module1_process(&o);
    TEST_ASSERT_EQUAL(module1_get_a(&o), 18);
}

int main( int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_module1);

    UNITY_END();
}

#endif