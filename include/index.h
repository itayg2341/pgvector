#ifndef INDEX_H
#define INDEX_H

class Index {
public:
    virtual ~Index() {}

    virtual void build() = 0;
    virtual void insert() = 0;
    virtual void search() = 0;
    virtual void vacuum() = 0;
};

#endif // INDEX_H
