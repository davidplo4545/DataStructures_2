//
// Created by david on 12/27/2022.
//

#ifndef DATASTRUCT2_UNIONNODE_H
#define DATASTRUCT2_UNIONNODE_H

#include "wet2util.h"
#include "Player.h"
#include "Team.h"

class Team;
struct UnionNode{
    UnionNode* m_parent;
    Player* m_player;
    Team* m_team;
    permutation_t m_totalPermutation;
    int m_gamesPlayed;
    permutation_t m_extraPermutation;
    int m_extraGamesPlayed;
    UnionNode();
    ~UnionNode();

};


#endif //DATASTRUCT2_UNIONNODE_H
