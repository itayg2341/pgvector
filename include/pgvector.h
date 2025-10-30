#ifndef PGVECTOR_H
#define PGVECTOR_H

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
#define AssertVariableIsOfTypeMacro(var, type)
#endif
#include "postgres.h"
#include "fmgr.h"

#include "bitutils.h"
#include "bitvec.h"
#include "halfutils.h"
#include "halfvec.h"
#include "ivfflat.h"
#include "sparsevec.h"
#include "vector.h"

#ifdef __cplusplus
}
#endif

#endif // PGVECTOR_H
