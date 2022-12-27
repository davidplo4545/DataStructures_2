#ifndef DATASTRUCT2_UNIONFIND_H
#define DATASTRUCT2_UNIONFIND_H
#include <hash_map>
#include "wet2util.h"
#include "Team.h"
#include "Player.h"

class UnionFind {
//////////////////////////////////////////////////
private:
    std::hash_map<int,Player> m_hashTable; //hashtable
    struct UnionNode{
        UnionNode* m_parent;
        Team* m_team;
        permutation_t m_totalPermutation;
        int m_gamesPlayed;
        int m_playersNum;
        permutation_t m_extraPermutation;
        int m_extraGamesPlayed;
        UnionNode() //done
    };
//////////////////////////////////////////////////
public:
    UnionFind(); //done
    std::hash_map<int, Player> getTable(); //done
    int Find(int id); //not finished
    UnionFind Union(int p, int q); //not finished
    int getGamesPlayedNum(int id);





};


#endif //DATASTRUCT2_UNIONFIND_H
