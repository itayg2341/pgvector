#ifndef HNSW_INDEX_H
#define HNSW_INDEX_H

#include "index.h"

class HnswIndex : public Index {
public:
    IndexBuildResult *build(Relation heap, Relation index, IndexInfo *indexInfo) override;
    void buildempty(Relation index) override;
    bool insert(Relation index, Datum *values, bool *isnull, ItemPointer heap_tid, Relation heap, IndexUniqueCheck checkUnique, bool indexUnchanged, IndexInfo *indexInfo) override;
    IndexBulkDeleteResult *bulkdelete(IndexVacuumInfo *info, IndexBulkDeleteResult *stats, IndexBulkDeleteCallback callback, void *callback_state) override;
    IndexBulkDeleteResult *vacuumcleanup(IndexVacuumInfo *info, IndexBulkDeleteResult *stats) override;
    IndexScanDesc beginscan(Relation index, int nkeys, int norderbys) override;
    void rescan(IndexScanDesc scan, ScanKey keys, int nkeys, ScanKey orderbys, int norderbys) override;
    bool gettuple(IndexScanDesc scan, ScanDirection dir) override;
    void endscan(IndexScanDesc scan) override;
};

#endif // HNSW_INDEX_H
