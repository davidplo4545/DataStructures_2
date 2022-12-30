//
// Created by david on 12/27/2022.
//
#include "UnionNode.h"

UnionNode::UnionNode():
        m_parent(nullptr),
        m_player(nullptr),
        m_team(nullptr),
        m_gamesPlayed(0),
        m_extraPermutation(permutation_t::neutral()),
        m_extraGamesPlayed(0)
{}

UnionNode::~UnionNode() {
    if(m_team != nullptr)
        delete m_team;
    delete m_player;

}

