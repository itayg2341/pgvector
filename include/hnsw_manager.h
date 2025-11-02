#ifndef HNSW_MANAGER_H
#define HNSW_MANAGER_H

#include "hnsw.h"

class HnswManager {
public:
    static int HnswGetM(Relation index);
    static int HnswGetEfConstruction(Relation index);
    static FmgrInfo *HnswOptionalProcInfo(Relation index, uint16 procnum);
    static void HnswInitSupport(HnswSupport * support, Relation index);
    static Datum HnswNormValue(const HnswTypeInfo * typeInfo, Oid collation, Datum value);
    static bool HnswCheckNorm(HnswSupport * support, Datum value);
    static Buffer HnswNewBuffer(Relation index, ForkNumber forkNum);
    static void HnswInitPage(Buffer buf, Page page);
    static HnswNeighborArray *HnswInitNeighborArray(int lm, HnswAllocator * allocator);
    static void HnswInitNeighbors(char *base, HnswElement element, int m, HnswAllocator * alloc);
    static void *HnswAlloc(HnswAllocator * allocator, Size size);
    static HnswElement HnswInitElement(char *base, ItemPointer tid, int m, double ml, int maxLevel, HnswAllocator * alloc);
    static void HnswAddHeapTid(HnswElement element, ItemPointer heaptid);
    static HnswElement HnswInitElementFromBlock(BlockNumber blkno, OffsetNumber offno);
    static void HnswGetMetaPageInfo(Relation index, int *m, HnswElement * entryPoint);
    static HnswElement HnswGetEntryPoint(Relation index);
    static void HnswUpdateMetaPage(Relation index, int updateEntry, HnswElement entryPoint, BlockNumber insertPage, ForkNumber forkNum, bool building);
    static bool HnswFormIndexValue(Datum *out, Datum *values, bool *isnull, const HnswTypeInfo * typeInfo, HnswSupport * support);
    static void HnswSetElementTuple(char *base, HnswElementTuple etup, HnswElement element);
    static void HnswSetNeighborTuple(char *base, HnswNeighborTuple ntup, HnswElement e, int m);
    static void HnswLoadElementFromTuple(HnswElement element, HnswElementTuple etup, bool loadHeaptids, bool loadVec);
    static void HnswLoadElement(HnswElement element, double *distance, HnswQuery * q, Relation index, HnswSupport * support, bool loadVec, double *maxDistance);
    static HnswSearchCandidate *HnswEntryCandidate(char *base, HnswElement em, HnswQuery * q, Relation rel, HnswSupport * support, bool loadVec);
    static List *HnswSearchLayer(char *base, HnswQuery * q, List *ep, int ef, int lc, Relation index, HnswSupport * support, int m, bool inserting, HnswElement skipElement, visited_hash * v, pairingheap **discarded, bool initVisited, int64 *tuples);
    static void HnswUpdateConnection(char *base, HnswNeighborArray * neighbors, HnswElement newElement, float distance, int lm, int *updateIdx, Relation index, HnswSupport * support);
    static bool HnswLoadNeighborTids(HnswElement element, ItemPointerData *indextids, Relation index, int m, int lm, int lc);
    static void HnswInitLockTranche(void);
    static const HnswTypeInfo *HnswGetTypeInfo(Relation index);
    static void HnswFindElementNeighbors(char *base, HnswElement element, HnswElement entryPoint, Relation index, HnswSupport * support, int m, int efConstruction, bool existing);

private:
    static void HnswUpdateMetaPageInfo(Page page, int updateEntry, HnswElement entryPoint, BlockNumber insertPage);
    static double HnswGetDistance(Datum a, Datum b, HnswSupport * support);
    static void HnswLoadElementImpl(BlockNumber blkno, OffsetNumber offno, double *distance, HnswQuery * q, Relation index, HnswSupport * support, bool loadVec, double *maxDistance, HnswElement * element);
    static double GetElementDistance(char *base, HnswElement element, HnswQuery * q, HnswSupport * support);
    static HnswSearchCandidate *HnswInitSearchCandidate(char *base, HnswElement element, double distance);
    static int CompareNearestCandidates(const pairingheap_node *a, const pairingheap_node *b, void *arg);
    static int CompareNearestDiscardedCandidates(const pairingheap_node *a, const pairingheap_node *b, void *arg);
    static int CompareFurthestCandidates(const pairingheap_node *a, const pairingheap_node *b, void *arg);
    static void InitVisited(char *base, visited_hash * v, bool inMemory, int ef, int m);
    static void AddToVisited(char *base, visited_hash * v, HnswElementPtr elementPtr, bool inMemory, bool *found);
    static bool CountElement(HnswElement skipElement, HnswElement e);
    static void HnswLoadUnvisitedFromMemory(char *base, HnswElement element, HnswUnvisited * unvisited, int *unvisitedLength, visited_hash * v, int lc, HnswNeighborArray * localNeighborhood, Size neighborhoodSize);
    static void HnswLoadUnvisitedFromDisk(HnswElement element, HnswUnvisited * unvisited, int *unvisitedLength, visited_hash * v, Relation index, int m, int lm, int lc);
    static int CompareCandidateDistances(const ListCell *a, const ListCell *b);
    static int CompareCandidateDistancesOffset(const ListCell *a, const ListCell *b);
    static bool CheckElementCloser(char *base, HnswCandidate * e, List *r, HnswSupport * support);
    static List *SelectNeighbors(char *base, List *c, int lm, HnswSupport * support, bool *closerSet, HnswCandidate * newCandidate, HnswCandidate * *pruned, bool sortCandidates);
    static void AddConnections(char *base, HnswElement element, List *neighbors, int lc);
    static List *RemoveElements(char *base, List *w, HnswElement skipElement);
    static void PrecomputeHash(char *base, HnswElement element);
    static void SparsevecCheckValue(Pointer v);
};

#endif // HNSW_MANAGER_H
