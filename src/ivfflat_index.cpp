#include "ivfflat_index.h"
#include "ivfflat.h"

IndexBuildResult *IvfflatIndex::build(Relation heap, Relation index, IndexInfo *indexInfo) {
    return ivfflatbuild(heap, index, indexInfo);
}

void IvfflatIndex::buildempty(Relation index) {
    ivfflatbuildempty(index);
}

bool IvfflatIndex::insert(Relation index, Datum *values, bool *isnull, ItemPointer heap_tid, Relation heap, IndexUniqueCheck checkUnique, bool indexUnchanged, IndexInfo *indexInfo) {
    return ivfflatinsert(index, values, isnull, heap_tid, heap, checkUnique, indexUnchanged, indexInfo);
}

IndexBulkDeleteResult *IvfflatIndex::bulkdelete(IndexVacuumInfo *info, IndexBulkDeleteResult *stats, IndexBulkDeleteCallback callback, void *callback_state) {
    return ivfflatbulkdelete(info, stats, callback, callback_state);
}

IndexBulkDeleteResult *IvfflatIndex::vacuumcleanup(IndexVacuumInfo *info, IndexBulkDeleteResult *stats) {
    return ivfflatvacuumcleanup(info, stats);
}

IndexScanDesc IvfflatIndex::beginscan(Relation index, int nkeys, int norderbys) {
    return ivfflatbeginscan(index, nkeys, norderbys);
}

void IvfflatIndex::rescan(IndexScanDesc scan, ScanKey keys, int nkeys, ScanKey orderbys, int norderbys) {
    ivfflatrescan(scan, keys, nkeys, orderbys, norderbys);
}

bool IvfflatIndex::gettuple(IndexScanDesc scan, ScanDirection dir) {
    return ivfflatgettuple(scan, dir);
}

void IvfflatIndex::endscan(IndexScanDesc scan) {
    ivfflatendscan(scan);
}
