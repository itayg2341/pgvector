#ifdef __cplusplus
extern "C" {
#endif

#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

#define VECTOR_MAX_DIM 16000

// Define a layout struct for C and for offsetof in C++
struct VectorLayout {
int32vl_len_;
int16dim;
int16unused;
floatx[FLEXIBLE_ARRAY_MEMBER];
};

#define VECTOR_SIZE(_dim) (offsetof(VectorLayout, x) + sizeof(float)*(_dim))

#ifdef __cplusplus
class Vector {
int32vl_len_;
int16dim;
int16unused;
floatx[FLEXIBLE_ARRAY_MEMBER];

public:
static Vector *Init(int dim);
voidPrint(char *msg);
intCmp(Vector * b);

int16 get_dim() const { return dim; }
int16 get_unused() const { return unused; }
float *get_x() { return x; }
const float *get_x() const { return x; }
};
#else
#define Vector VectorLayout
#endif

#define DatumGetVector(x)((Vector *) PG_DETOAST_DATUM(x))
#define PG_GETARG_VECTOR_P(x)DatumGetVector(PG_GETARG_DATUM(x))
#define PG_RETURN_VECTOR_P(x)PG_RETURN_POINTER(x)

/* TODO Move to better place */
#if PG_VERSION_NUM >= 160000
#define FUNCTION_PREFIX
#else
#define FUNCTION_PREFIX PGDLLEXPORT
#endif

#endif

#ifdef __cplusplus
}
#endif
