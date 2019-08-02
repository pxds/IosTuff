#include <module1.h>

void module1_init(module1_s *obj) {
    obj->a = 0;
}

void module1_set_a(module1_s *obj, int a) {
    obj->a = a;
}

int  module1_get_a(module1_s *obj) {
    return obj->a;
}

void module1_process(module1_s *obj) {
	obj->a++;
}