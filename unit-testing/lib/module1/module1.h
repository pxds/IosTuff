#ifndef __MODULE1_H
#define __MODULE1_H

typedef struct module1_s {
    int a;
} module1_s;

void module1_init(module1_s *obj);

void module1_set_a(module1_s *obj, int a);
int  module1_get_a(module1_s *obj);

void module1_process(module1_s *obj);

#endif