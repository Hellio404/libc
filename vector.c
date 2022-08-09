#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "vector.h"

vector_t    *v_create(size_t size) {

    vector_t *ptr;

    ptr = malloc(sizeof(vector_t));
    if (!ptr) return NULL;

    ptr->_end = NULL;
    ptr->_begin = NULL;
    ptr->_end_cap = NULL;
    ptr->_size = size;
    return ptr;
}

void    *v_push(vector_t *vt) {

    if (vt->_end + vt->_size > vt->_end_cap) {
        size_t new_size = (((unsigned char*)vt->_end - (unsigned char *)vt->_begin) / vt->_size) * 2;
        if (new_size == 0)
            new_size = 1;
        if (v_reserve(vt, new_size))
            return NULL;
    }
    void *ret = vt->_end;
    vt->_end += vt->_size;
    return ret;
}

void v_pop(vector_t *vt, void (*fn) (void *)) {
    if (vt->_end <= vt->_begin) 
        return ;
    
    if (fn)
        fn(--vt->_end);
    else
        --vt->_end;
}

int    v_reserve(vector_t *vt, size_t size) {
    if (v_capacity(vt) >= size) return 0;
    size_t new_size = size * vt->_size;
    if (new_size == 0)
        new_size = 1;
    void *replace = malloc(new_size * vt->_size);
    if (!replace)
        return 1;
    memcpy(replace, vt->_begin, ((unsigned char*)vt->_end - (unsigned char *)vt->_begin));
    free(vt->_begin);
    vt->_end_cap = replace + new_size * vt->_size;
    vt->_end = replace + ((unsigned char*)vt->_end - (unsigned char *)vt->_begin);
    vt->_begin = replace;
    return 0;
}

int v_resize(vector_t *vt, size_t size, const void *default_value, void (*fn) (void *)) {
    while (v_size(vt) > size)
        v_pop(vt, fn);
    if (v_size(vt) < size) {
        if (v_reserve(vt, size))
            return 1;
        size_t diff =  size - v_size(vt);
        for (int i = 0; i < diff; ++i) {
            memmove(vt->_end, default_value, vt->_size);
            vt->_end += vt->_size;
        }
    }
    return 0;
}

size_t    v_size(vector_t *vt) {

    return (((unsigned char*)vt->_end - (unsigned char *)vt->_begin) / vt->_size);
}

size_t    v_capacity(vector_t *vt) {

    return (((unsigned char*)vt->_end_cap - (unsigned char *)vt->_begin) / vt->_size);
}

int         v_empty(vector_t *vt) {

    return v_size(vt) == 0;
}

void *v_begin(vector_t *vt) {
    return vt->_begin;
}

void *v_end(vector_t *vt) {
    return vt->_end;
}

void v_clear(vector_t *vt, void (*fn) (void *)) {
    if (fn) {
        for (void *b = vt->_begin; b != vt->_end; b += vt->_size)
            fn(b);
    }
    free(vt->_begin);
    vt->_begin = vt->_end = vt->_end_cap = NULL;
}

void       v_destroy(vector_t *vt, void (*fn) (void *)) {
    if (fn) {
        for (void *b = vt->_begin; b != vt->_end; b += vt->_size)
            fn(b);
    }
    
    free(vt->_begin);
    free(vt);
}
