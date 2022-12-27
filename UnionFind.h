#ifndef DATASTRUCT2_UNIONFIND_H
#define DATASTRUCT2_UNIONFIND_H
//#include <hash_map>
#include "wet2util.h"
#include "Team.h"
#include "Player.h"
#include "HashTable.h"
#include "UnionNode.h"



class UnionFind {
private:
    HashTable* m_hashTable; //hashtable

public:
    UnionFind(); //done
    HashTable* getTable(); //done
    Team* find(int id); //not finished
    void unite(int p, int q); //not finished
    int getGamesPlayedNum(int id);
    void insertPlayer(Player* player, Team* team);





};


#endif //DATASTRUCT2_UNIONFIND_H
