#ifndef HW3_202_HASHTABLE_H
#define HW3_202_HASHTABLE_H

class HashTable {
public:
    HashTable(int size);
    void makeEmpty();
    int insertElement(int x);
    int getValue(int pos) const;
    void setValue(int pos, int val);

private:
    int *array;
    int tableSize;
    int myhash(int x) const;
};

#endif
