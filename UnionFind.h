#ifndef DATASTRUCT2_UNIONFIND_H
#define DATASTRUCT2_UNIONFIND_H
//#include <hash_map>
#include "wet2util.h"
#include "Team.h"
#include "Player.h"
#include "HashTable.h"
#include "UnionNode.h"


struct TestNode
{
    Team* team;
    TestNode* next;
};
class UnionFind {
private:
    HashTable* m_hashTable;

    TestNode* testingChain; // list made for testing purposes
    TestNode* lastNode;
public:
    UnionFind(); //done
    HashTable* getTable(); //done
    UnionNode* find(int id); //not finished
    void unite(int p, int q); //not finished
    int calculateGamesPlayed(int id);
    void buyTeam(Team* buyer, Team* bought);
    void createUnionNode(HashNode* newHashNode, Player* player, Team* team);
    void insertPlayer(Player* player, Team* team);

    void print();

};


#endif //DATASTRUCT2_UNIONFIND_H
