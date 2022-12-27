//
// Created by David on 24/12/2022.
//

#ifndef DATASTRUCT2_HASHTABLE_H
#define DATASTRUCT2_HASHTABLE_H
#include "Player.h"
#include "Team.h"
#include "Exception.h"
#include "wet2util.h"
#include "UnionNode.h"

struct HashNode{
    Player* m_player;
    int m_playerKey;
    HashNode* chainNext;
    UnionNode* uniNode;
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
    void insertToNewTable(HashNode* newNode, HashNode** newTable) const;
    void createUnionNode(HashNode* newHashNode, Player* player, Team* team);

    static int hash(int key, int mod);
public:
    HashTable();
    ~HashTable();

    static void initTable(HashNode** newTable, int size);

    HashNode* insert(Player *player, Team* team);
    void printTable();
    HashNode* find(int key);
};


#endif //DATASTRUCT2_HASHTABLE_H
