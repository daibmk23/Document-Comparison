#include "HashTable.h"

HashTable::HashTable(int size) {
    tableSize = size;
    array = new int[tableSize];
    makeEmpty();
}

void HashTable::makeEmpty() {
    for (int i = 0; i < tableSize; i++) {
        array[i] = -1;
    }
}

int HashTable::myhash(int x) const {
    int h = x % tableSize;
    if (h < 0) {
        h += tableSize; //ennh just in case
    }
    return h;
}

int HashTable::insertElement(int x) {
    int start = myhash(x);
    int pos = start;
    for (int i = 0; i < tableSize; i++) {
        if (array[pos] == -1) {
            array[pos] = x;
            return pos;
        }
        pos = (pos + 1) % tableSize;
    }
    return -1;
}

int HashTable::getValue(int pos) const {
    return array[pos];
}

void HashTable::setValue(int pos, int val) {
    array[pos] = val;
}
