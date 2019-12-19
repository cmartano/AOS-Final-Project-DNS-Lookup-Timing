//
// Created by Christian Martano on 12/15/19.
//

#ifndef SRC_HASHMAP_H_
#define SRC_HASHMAP_H_

#include <iostream>
#include "HashNode.h"
#include <string>

template<typename K, typename V>
class HashMap {
private:
    HashNode<K, V> **map;
    int tablesize;
    int nelements;
public:
    HashMap(int tablesize);
    ~HashMap();
    int getNelements();
    int getTablesize();
    bool isEmpty();
    bool checkKey(K keyIN);
    void put(K keyIN, V elementIN);
    V getMapValue(K keyIN);
    void remove(K keyIN);

};

unsigned int Hash(string key, int tablesize) {
    int result = 0;
    int l = key.length();
    for (int i = 0; i < l; i++) {
        result = result + key[i];
    }
    result = result % tablesize;
    return result;
}

template<typename K, typename V>
HashMap<K, V>::HashMap(int tablesize) {
    this->tablesize = tablesize;
    this->map = new HashNode<K, V>*[tablesize];
    for (int i = 0; i < tablesize; i++) {
        map[i] = NULL;
    }
    this->nelements = 0;

}

template<typename K, typename V>
HashMap<K, V>::~HashMap() {
    delete[] map;
}

template<typename K, typename V>
bool HashMap<K, V>::isEmpty() {
    return nelements == 0;
}

template<typename K, typename V>
int HashMap<K, V>::getTablesize() {
    return tablesize;
}
template<typename K, typename V>
int HashMap<K, V>::getNelements() {
    return nelements;
}

template<typename K, typename V>
bool HashMap<K, V>::checkKey(K keyIN) {
    int hashValue = Hash(keyIN, tablesize);
    bool flag = false;

    while (map[hashValue] != NULL) {
        if (map[hashValue]->getKey() == keyIN) {
            flag = true;
        }
        map[hashValue] = map[hashValue]->getNext();

    }

    return flag;
}

template<typename K, typename V>
void HashMap<K, V>::put(K keyIN, V elementIN) {
    unsigned int hashValue = Hash(keyIN, tablesize);
    HashNode<K, V> *prev = NULL;
    HashNode<K, V> *entry = map[hashValue];

    while (entry != NULL && entry->getKey() != keyIN) {
        prev = entry;
        entry = entry->getNext();
    }

    if (entry == NULL) {
        entry = new HashNode<K, V>(keyIN, elementIN);
        if (prev == NULL) {
            map[hashValue] = entry;
        } else {
            prev->setNext(entry);
        }
        nelements++;
    } else {
        entry->setElement(elementIN);
        nelements++;
    }
}

template<typename K, typename V>
V HashMap<K, V>::getMapValue(K keyIN) {
    int hashValue = Hash(keyIN, tablesize);
    HashNode<K, V> *ptr = map[hashValue];
    if (ptr == NULL) {
        return 0;
    } else {
        while (ptr != NULL) {
            if (ptr->getKey() == keyIN) {
                return ptr->getElement();
            } else {
                ptr = ptr->getNext();
            }
        }
    }
}

template<typename K, typename V>
void HashMap<K, V>::remove(K keyIN) {
    int hashvalue = Hash(keyIN, tablesize);
    HashNode<K, V> *ptr = map[hashvalue];
    HashNode<K, V> *prev = NULL;
    if (checkKey(keyIN) == true) {

        while (ptr != NULL && ptr->getKey() != keyIN) {
            prev = ptr;
            ptr = ptr->getNext();
        }
        if (prev == NULL) {
            map[hashvalue] = ptr->getNext();
            nelements--;
        } else {
            prev->setNext(ptr->getNext());
            delete ptr;
            nelements--;

        }
    }

}

#endif /* SRC_HASHMAP_H_ */
