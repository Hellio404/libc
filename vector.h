#ifndef VECTOR_H
#define VECTOR_H
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
typedef struct {
    void*   _end_cap;
    void*   _end;
    size_t  _size;
    void*   _begin;
} vector_t;

vector_t    *v_create(size_t size);
void        *v_push(vector_t *vt);
void        v_pop(vector_t *vt, void (*fn) (void *));
int         v_reserve(vector_t *vt, size_t size);
int         v_resize(vector_t *vt, size_t size, const void *default_value, void (*fn) (void *));
size_t      v_size(vector_t *vt);
size_t      v_capacity(vector_t *vt);
int         v_empty(vector_t *vt);
void        *v_begin(vector_t *vt);
void        *v_end(vector_t *vt);
void        v_clear(vector_t *vt, void (*fn) (void *));
void        v_destroy(vector_t *vt, void (*fn) (void *));
#endif
