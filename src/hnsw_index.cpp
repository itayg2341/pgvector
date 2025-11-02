#include "hnsw_index.h"
#include "hnsw.h"

IndexBuildResult *HnswIndex::build(Relation heap, Relation index, IndexInfo *indexInfo) {
    return hnswbuild(heap, index, indexInfo);
}

void HnswIndex::buildempty(Relation index) {
    hnswbuildempty(index);
}

bool HnswIndex::insert(Relation index, Datum *values, bool *isnull, ItemPointer heap_tid, Relation heap, IndexUniqueCheck checkUnique, bool indexUnchanged, IndexInfo *indexInfo) {
    return hnswinsert(index, values, isnull, heap_tid, heap, checkUnique, indexUnchanged, indexInfo);
}

IndexBulkDeleteResult *HnswIndex::bulkdelete(IndexVacuumInfo *info, IndexBulkDeleteResult *stats, IndexBulkDeleteCallback callback, void *callback_state) {
    return hnswbulkdelete(info, stats, callback, callback_state);
}

IndexBulkDeleteResult *HnswIndex::vacuumcleanup(IndexVacuumInfo *info, IndexBulkDeleteResult *stats) {
    return hnswvacuumcleanup(info, stats);
}

IndexScanDesc HnswIndex::beginscan(Relation index, int nkeys, int norderbys) {
    return hnswbeginscan(index, nkeys, norderbys);
}

void HnswIndex::rescan(IndexScanDesc scan, ScanKey keys, int nkeys, ScanKey orderbys, int norderbys) {
    hnswrescan(scan, keys, nkeys, orderbys, norderbys);
}

bool HnswIndex::gettuple(IndexScanDesc scan, ScanDirection dir) {
    return hnswgettuple(scan, dir);
}

void HnswIndex::endscan(IndexScanDesc scan) {
    hnswendscan(scan);
}
