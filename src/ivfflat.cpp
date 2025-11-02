#include "postgres.h"

#include "access/amapi.h"
#include "catalog/pg_am.h"
#include "ivfflat_index.h"

static IvfflatIndex ivfflatIndex;

static IndexBuildResult *ivfflat_build_wrapper(Relation heap, Relation index, IndexInfo *indexInfo) {
    return ivfflatIndex.build(heap, index, indexInfo);
}

static void ivfflat_buildempty_wrapper(Relation index) {
    ivfflatIndex.buildempty(index);
}

static bool ivfflat_insert_wrapper(Relation index, Datum *values, bool *isnull, ItemPointer heap_tid, Relation heap, IndexUniqueCheck checkUnique, bool indexUnchanged, IndexInfo *indexInfo) {
    return ivfflatIndex.insert(index, values, isnull, heap_tid, heap, checkUnique, indexUnchanged, indexInfo);
}

static IndexBulkDeleteResult *ivfflat_bulkdelete_wrapper(IndexVacuumInfo *info, IndexBulkDeleteResult *stats, IndexBulkDeleteCallback callback, void *callback_state) {
    return ivfflatIndex.bulkdelete(info, stats, callback, callback_state);
}

static IndexBulkDeleteResult *ivfflat_vacuumcleanup_wrapper(IndexVacuumInfo *info, IndexBulkDeleteResult *stats) {
    return ivfflatIndex.vacuumcleanup(info, stats);
}

static IndexScanDesc ivfflat_beginscan_wrapper(Relation index, int nkeys, int norderbys) {
    return ivfflatIndex.beginscan(index, nkeys, norderbys);
}

static void ivfflat_rescan_wrapper(IndexScanDesc scan, ScanKey keys, int nkeys, ScanKey orderbys, int norderbys) {
    ivfflatIndex.rescan(scan, keys, nkeys, orderbys, norderbys);
}

static bool ivfflat_gettuple_wrapper(IndexScanDesc scan, ScanDirection dir) {
    return ivfflatIndex.gettuple(scan, dir);
}

static void ivfflat_endscan_wrapper(IndexScanDesc scan) {
    ivfflatIndex.endscan(scan);
}

extern "C" PG_FUNCTION_INFO_V1(ivfflathandler);
Datum
ivfflathandler(PG_FUNCTION_ARGS)
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

amroutine->ambuild = ivfflat_build_wrapper;
amroutine->ambuildempty = ivfflat_buildempty_wrapper;
amroutine->aminsert = ivfflat_insert_wrapper;
amroutine->ambulkdelete = ivfflat_bulkdelete_wrapper;
amroutine->amvacuumcleanup = ivfflat_vacuumcleanup_wrapper;
amroutine->amcanreturn = NULL;
amroutine->amcostestimate = ivfflatcostestimate;
amroutine->amoptions = ivfflatoptions;
amroutine->amproperty = NULL;
amroutine->ambuildphasename = NULL;
amroutine->amvalidate = ivfflatvalidate;
amroutine->ambeginscan = ivfflat_beginscan_wrapper;
amroutine->amrescan = ivfflat_rescan_wrapper;
amroutine->amgettuple = ivfflat_gettuple_wrapper;
amroutine->amgetbitmap = NULL;
amroutine->amendscan = ivfflat_endscan_wrapper;
amroutine->ammarkpos = NULL;
amroutine->amrestrpos = NULL;
amroutine->amestimateparallelscan = NULL;
amroutine->aminitparallelscan = NULL;
amroutine->amparallelrescan = NULL;

PG_RETURN_POINTER(amroutine);
}
