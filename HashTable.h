//
// Created by David on 24/12/2022.
//

#ifndef DATASTRUCT2_HASHTABLE_H
#define DATASTRUCT2_HASHTABLE_H
#include "TreeNode.h"

enum NodeType{Empty, Full};
template<class T>
struct HashNode{
    T data;
    int key;
    NodeType nodeType;
    HashNode();
};

template<class T>
HashNode<T>::HashNode() :data(nullptr), key(-1), nodeType(NodeType::Empty){}

template<class T>
class HashTable {
    const int MIN_SIZE = 13;

    HashNode<T>* m_table;
    int m_size;
    int m_currSize;

    bool isFull();

    void increaseArraySize();

    int hash1(int key);
    int hash2(int key);
public:
    HashTable();
    ~HashTable();

    void insert(int key, T data);
    void printTable();
    T find(int key);
};

template<class T>
HashTable<T>::HashTable() : m_size(MIN_SIZE) {
    m_table = new HashNode<T>[m_size];
    for (int i=0; i<m_size; i++)
        m_table[i] = HashNode<T>();
}



template<class T>
HashTable<T>::~HashTable(){
    delete []m_table;
}

template<class T>
bool HashTable<T>::isFull() { return m_size == m_currSize; }

template<class T>
int HashTable<T>::hash1(int key){
    return key%m_size;
}

template<class T>
int HashTable<T>::hash2(int key){
    return key%(m_size - 1) + 1; // MABYE NEEDS TO CHANGE THE SECOND HASH :D
}

template<class T>
void HashTable<T>::insert(int key, T data) {
    if(isFull())
        increaseArraySize();
    int index = hash1(key);
    if(m_table[index].nodeType == NodeType::Full)
    {
        int hashStep = hash2(index);
        int i=1;
        while(true)
        {
            int newIndex = hash1(index + i*hashStep);
            if(m_table[index].nodeType == NodeType::Empty)
            {
                m_table[newIndex].data = data;
                m_table[newIndex].key = key;
                m_table[newIndex].nodeType = NodeType::Full;
                break;
            }
            i++;
        }
    }
    else
    {
        m_table[index].nodeType = NodeType::Full;
        m_table[index].key = key;
        m_table[index].data = data;
    }
    m_currSize++;
}

template<class T>
T HashTable<T>::find(int key) {
    int index = hash1(key);
    int hashStep = hash2(key);
    int i=0;
    while(true)
    {
        int newIndex = hash1(index + i*hashStep);
        if(m_table[newIndex].nodeType == NodeType::Empty) // key does not exist in system
        {
            break;
        }
        if(m_table[newIndex].key == key)
        {
            return m_table[newIndex].data;
        }
        i++;
    }
    return nullptr;
}

template<class T>
void HashTable<T>::increaseArraySize() {
    auto newTable = new HashNode<T>[2*m_size];
    for (int i=0; i<m_size; i++)
        newTable[i] = m_table[i];
    delete [] m_table;
    m_table = newTable;
    m_size *=2;
}

template<class T>
void HashTable<T>::printTable()
{
    for(int i=0;i<m_size;i++)
    {
        std::cout << i << "-->";
        if(m_table[i].nodeType == NodeType::Full)
            std::cout << m_table[i].data << std::endl;
    }
}








#endif //DATASTRUCT2_HASHTABLE_H
