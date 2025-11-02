#ifndef INDEX_H
#define INDEX_H

#include "postgres.h"
#include "access/amapi.h"
#include "access/generic_xlog.h"
#include "access/reloptions.h"
#include "access/table.h"
#include "catalog/index.h"
#include "storage/bufmgr.h"

class Index {
public:
    virtual ~Index() {}

    virtual IndexBuildResult *build(Relation heap, Relation index, IndexInfo *indexInfo) = 0;
    virtual void buildempty(Relation index) = 0;
    virtual bool insert(Relation index, Datum *values, bool *isnull, ItemPointer heap_tid, Relation heap, IndexUniqueCheck checkUnique, bool indexUnchanged, IndexInfo *indexInfo) = 0;
    virtual IndexBulkDeleteResult *bulkdelete(IndexVacuumInfo *info, IndexBulkDeleteResult *stats, IndexBulkDeleteCallback callback, void *callback_state) = 0;
    virtual IndexBulkDeleteResult *vacuumcleanup(IndexVacuumInfo *info, IndexBulkDeleteResult *stats) = 0;
    virtual IndexScanDesc beginscan(Relation index, int nkeys, int norderbys) = 0;
    virtual void rescan(IndexScanDesc scan, ScanKey keys, int nkeys, ScanKey orderbys, int norderbys) = 0;
    virtual bool gettuple(IndexScanDesc scan, ScanDirection dir) = 0;
    virtual void endscan(IndexScanDesc scan) = 0;
};

#endif // INDEX_H
