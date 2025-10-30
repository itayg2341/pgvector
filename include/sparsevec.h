#ifdef __cplusplus
extern "C" {
#endif

#ifndef SPARSEVEC_H
#define SPARSEVEC_H

#define SPARSEVEC_MAX_DIM 1000000000
#define SPARSEVEC_MAX_NNZ 16000

#define DatumGetSparseVector(x)((SparseVector *) PG_DETOAST_DATUM(x))
#define PG_GETARG_SPARSEVEC_P(x)DatumGetSparseVector(PG_GETARG_DATUM(x))
#define PG_RETURN_SPARSEVEC_P(x)PG_RETURN_POINTER(x)

/*
 * Indices use 0-based numbering for the on-disk (and binary) format (consistent with C)
 * and are always sorted. Values come after indices.
 */
#ifdef __cplusplus
class SparseVector
{
public:
int32vl_len_;a header (do not touch directly!) */
int32dim;umber of dimensions */
int32nnz;umber of non-zero elements */
int32unused;t32indices[FLEXIBLE_ARRAY_MEMBER];

static SparseVector *Init(int dim, int nnz);

float L2SquaredDistance(const SparseVector &other) const;
float InnerProduct(const SparseVector &other) const;
int Cmp(const SparseVector &other) const;
};
#else
typedef struct SparseVector
{
int32vl_len_;a header (do not touch directly!) */
int32dim;umber of dimensions */
int32nnz;umber of non-zero elements */
int32unused;t32indices[FLEXIBLE_ARRAY_MEMBER];
}SparseVector;
#endif

/* Use functions instead of macros to avoid double evaluation */

static inline Size
SPARSEVEC_SIZE(int nnz)
{
return offsetof(SparseVector, indices) + (nnz * sizeof(int32)) + (nnz * sizeof(float));
}

static inline float *
SPARSEVEC_VALUES(SparseVector * x)
{
return (float *) (((char *) x) + offsetof(SparseVector, indices) + (x->nnz * sizeof(int32)));
}

#ifdef __cplusplus
#define InitSparseVector(dim, nnz) SparseVector::Init(dim, nnz)
#else
SparseVector *InitSparseVector(int dim, int nnz);
#endif

#endif

#ifdef __cplusplus
}
#endif
