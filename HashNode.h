//
// Created by Christian Martano on 12/15/19.
//


#ifndef HASHNODE_H_
#define HASHNODE_H_

#include <iostream>

using namespace std;

template<typename K, typename V>
class HashNode {
private:
    K key;
    V element;
    HashNode<K, V> *next;
public:
    HashNode(K keyIN, V elementIN);
    ~HashNode();
    void setKey(K keyIN);
    void setElement(V elementIN);
    bool isNULL(HashNode<K,V>* p);
    K getKey();
    V getElement();
    void setNext(HashNode<K, V> *p);
    HashNode<K, V>* getNext();
};

template<typename K, typename V>
HashNode<K, V>::HashNode(K keyIN, V elementIN) {
    this->element = elementIN;
    this->key = keyIN;
    this->next = NULL;
}

template<typename K, typename V>
HashNode<K, V>::~HashNode() {

}

template<typename K, typename V>
void HashNode<K, V>::setKey(K keyIN) {
    this->key = keyIN;
}
template<typename K, typename V>
void HashNode<K, V>::setElement(V elementIN) {
    this->element = elementIN;

}

template<typename K, typename V>
void HashNode<K, V>::setNext(HashNode<K, V> *p) {
    this->next = p;
}

template<typename K, typename V>
K HashNode<K, V>::getKey() {
    return key;
}
template<typename K, typename V>
V HashNode<K, V>::getElement() {
    return element;
}

template<typename K, typename V>
HashNode<K, V>* HashNode<K, V>::getNext() {
    return next;
}


#endif /* HASHNODE_H_ */