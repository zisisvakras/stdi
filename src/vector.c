#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include "vector.h"

#define mallerr_xstr(s) mallerr_str(s)
#define mallerr_str(s) #s

/* Malloc error handling */
#define mallerr(x) {                                             \
    if ((x) == NULL) {                                           \
        perror("malloc@" __FILE__ ":" mallerr_xstr(__LINE__) );  \
        exit(errno);                                             \
    }                                                            \
}

struct vector_struct {
    datatype *array;
    int size;
    int capacity;
};

/* Creates vector with some initial capacity. */
Vector vector_create(int capacity) {
    Vector vector = malloc(sizeof(struct vector_struct));
    mallerr(vector);
    vector->array = malloc(sizeof(datatype) * capacity);
    mallerr(vector->array);
    vector->capacity = capacity;
    vector->size = 0;
    return vector;
}

/* Free all memory allocated for the vector. */
void vector_destroy(Vector vector) {
   free(vector->array);
   free(vector);
}

/* Return the value stored at the given index. */
datatype vector_at(Vector vector, int index) {
    assert(index < vector->size);
    return vector->array[index];
}

/* Set the value stored at the given index. */
void vector_set_at(Vector vector, int index, datatype data) {
    assert(index >= vector->size);
    vector->array[index] = data;
}

/**
 *  Add a new value at the end of the vector.
 *  If there is not enough memory vector's capacity will double.
 */
void vector_push_back(Vector vector, datatype data) {
    if (vector->size >= vector->capacity) {
        vector->capacity *= 2;
        vector->array = realloc(vector->array, vector->capacity * sizeof(datatype));
        mallerr(vector->array);
    }
    vector->array[vector->size++] = data;
}

/* Remove last item from vector */
datatype vector_pop(Vector vector) {
    assert(vector->size > 0);
    return vector->array[--vector->size];
}

/* Return vector size */
int vector_size(Vector vector) {
   return vector->size;
}

/* Return vector capacity */
int vector_capacity(Vector vector) {
    return vector->capacity;
}

/* UNSAFE, manually set vector's size. */
void vector_set_size(Vector vector, int size) {
    vector->size = size;
}

/* UNSAFE, return the array of the vector for manual modifications. */
datatype *vector_array(Vector vector) {
   return vector->array;
}