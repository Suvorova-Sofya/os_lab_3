#include <stdio.h>
#include <stdbool.h>
#ifndef _VECTOR_
#define _VECTOR_
typedef struct {
    int *body;
    int size;
} vector;
vector *v_create();
void v_destroy(vector *v);
void v_set(vector *v, int i, int val);
int v_get(vector *v,int i);
bool v_set_size(vector *v,int size);
int v_get_size(vector *v);
bool v_push(vector *v,int val);
#endif