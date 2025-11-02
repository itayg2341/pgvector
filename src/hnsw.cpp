#include "postgres.h"

#include "access/amapi.h"
#include "catalog/pg_am.h"
#include "hnsw_index.h"

static HnswIndex hnswIndex;

static IndexBuildResult *hnsw_build_wrapper(Relation heap, Relation index, IndexInfo *indexInfo) {
    return hnswIndex.build(heap, index, indexInfo);
}

static void hnsw_buildempty_wrapper(Relation index) {
    hnswIndex.buildempty(index);
}

static bool hnsw_insert_wrapper(Relation index, Datum *values, bool *isnull, ItemPointer heap_tid, Relation heap, IndexUniqueCheck checkUnique, bool indexUnchanged, IndexInfo *indexInfo) {
    return hnswIndex.insert(index, values, isnull, heap_tid, heap, checkUnique, indexUnchanged, indexInfo);
}

static IndexBulkDeleteResult *hnsw_bulkdelete_wrapper(IndexVacuumInfo *info, IndexBulkDeleteResult *stats, IndexBulkDeleteCallback callback, void *callback_state) {
    return hnswIndex.bulkdelete(info, stats, callback, callback_state);
}

static IndexBulkDeleteResult *hnsw_vacuumcleanup_wrapper(IndexVacuumInfo *info, IndexBulkDeleteResult *stats) {
    return hnswIndex.vacuumcleanup(info, stats);
}

static IndexScanDesc hnsw_beginscan_wrapper(Relation index, int nkeys, int norderbys) {
    return hnswIndex.beginscan(index, nkeys, norderbys);
}

static void hnsw_rescan_wrapper(IndexScanDesc scan, ScanKey keys, int nkeys, ScanKey orderbys, int norderbys) {
    hnswIndex.rescan(scan, keys, nkeys, orderbys, norderbys);
}

static bool hnsw_gettuple_wrapper(IndexScanDesc scan, ScanDirection dir) {
    return hnswIndex.gettuple(scan, dir);
}

static void hnsw_endscan_wrapper(IndexScanDesc scan) {
    hnswIndex.endscan(scan);
}

extern "C" PG_FUNCTION_INFO_V1(hnswhandler);
Datum
hnswhandler(PG_FUNCTION_ARGS)
{
IndexAmRoutine *amroutine = makeNode(IndexAmRoutine);

amroutine->amstrategies = 0;
amroutine->amsupport = 5;
amroutine->amoptsprocnum = 0;
amroutine->amcanorder = false;
amroutine->amcanorderbyop = true;
amroutine->amcanbackward = false;
amroutine->amcanunique = false;
amroutine->amcanmulticol = false;
amroutine->amoptionalkey = true;
amroutine->amsearcharray = false;
amroutine->amsearchnulls = false;
amroutine->amstorage = false;
amroutine->amclusterable = false;
amroutine->ampredlocks = false;
amroutine->amcanparallel = false;
amroutine->amcaninclude = false;
amroutine->amusemaintenanceworkmem = false;
amroutine->amparallelvacuumoptions = VACUUM_OPTION_PARALLEL_BULKDEL;
amroutine->amkeytype = InvalidOid;

amroutine->ambuild = hnsw_build_wrapper;
amroutine->ambuildempty = hnsw_buildempty_wrapper;
amroutine->aminsert = hnsw_insert_wrapper;
amroutine->ambulkdelete = hnsw_bulkdelete_wrapper;
amroutine->amvacuumcleanup = hnsw_vacuumcleanup_wrapper;
amroutine->amcanreturn = NULL;
amroutine->amcostestimate = hnswcostestimate;
amroutine->amoptions = hnswoptions;
amroutine->amproperty = NULL;
amroutine->ambuildphasename = NULL;
amroutine->amvalidate = hnswvalidate;
amroutine->ambeginscan = hnsw_beginscan_wrapper;
amroutine->amrescan = hnsw_rescan_wrapper;
amroutine->amgettuple = hnsw_gettuple_wrapper;
amroutine->amgetbitmap = NULL;
amroutine->amendscan = hnsw_endscan_wrapper;
amroutine->ammarkpos = NULL;
amroutine->amrestrpos = NULL;
amroutine->amestimateparallelscan = NULL;
amroutine->aminitparallelscan = NULL;
amroutine->amparallelrescan = NULL;

PG_RETURN_POINTER(amroutine);
}
