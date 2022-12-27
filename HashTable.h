//
// Created by David on 24/12/2022.
//

#ifndef DATASTRUCT2_HASHTABLE_H
#define DATASTRUCT2_HASHTABLE_H
#include "UnionFind.h"
#include "Player.h"
#include "Exception.h"
struct HashNode{

    Player* player;

    int playerKey;
    HashNode* chainNext;
    // UnionNode* node;
    HashNode();
};


class HashTable {
    const int MIN_SIZE = 13;
    const int LOAD_FACTOR = 2;

    HashNode** m_table;
    int m_size;
    int m_currSize;

    bool shouldExpand() const;

    void increaseArraySize();
    void insertToNewTable(HashNode* newNode, HashNode** newTable);

    int hash(int key, int mod);
public:
    HashTable();
    ~HashTable();

    static void initTable(HashNode** newTable, int size);

    void insert(int id, Player *player);
    void printTable();
    HashNode* find(int key);
};


#endif //DATASTRUCT2_HASHTABLE_H
