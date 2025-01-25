/** Title: Hashing
Author: Daib Malik
ID: 22201013
Section : 1
Homework: 3
Description : HashTable
**/

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

#endif //HW3_202_HASHTABLE_H
