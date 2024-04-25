#ifndef VECTOR_H_
#define VECTOR_H_

typedef struct vector_struct *Vector;
typedef double datatype;

/* Creates vector with some initial capacity. */
Vector vector_create(int capacity);

/* Free all memory allocated for the vector. */
void vector_destroy(Vector vector);

/* Return the value stored at the given index. */
datatype vector_at(Vector vector, int index);

/* Set the value stored at the given index. */
void vector_set_at(Vector vector, int index, datatype data);

/**
 *  Add a new value at the end of the vector.
 *  If there is not enough memory vector's capacity will double.
 */
void vector_push_back(Vector vector, datatype data);

/* Remove last item from vector */
datatype vector_pop(Vector vector);

/* Return vector size */
int vector_size(Vector vector);

/* Return vector capacity */
int vector_capacity(Vector vector);

/* UNSAFE, manually set vector's size. */
void vector_set_size(Vector vector, int size);

/* UNSAFE, return the array of the vector for manual modifications. */
datatype *vector_array(Vector vector);

#endif