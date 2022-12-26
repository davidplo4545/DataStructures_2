#include "UnionFind.h"

UnionFind::UnionNode::UnionNode():
    m_parent(nullptr),
    m_team(nullptr),
    m_totalPermutation(permutation_t::neutral()),
    m_gamesPlayed(0),
    m_playersNum(0),
    m_extraPermutation(permutation_t::neutral()),
    m_extraGamesPlayed(0)
{}

UnionFind::UnionFind() : m_hashTable(std::hash_map<int,Player>())
{}
std::hash_map<int, Player> UnionFind::getTable() {
    return m_hashTable;
}

int UnionFind::Find(int id) { //update during shrink
    UnionNode *uf = m_hashTable.find(id);
    UnionNode *temp = uf;
    UnionNode *root=nullptr;
    if (uf) {
        while (uf->m_parent) {
            uf = uf->m_parent;
        }
        root = uf;
        uf = temp;
        while (uf->m_parent){
            temp = uf->m_parent;
            uf->m_parent = root;
            uf = temp;
        }
    }
    return root;

}
UnionFind UnionFind::Union(int p, int q) {
    UnionNode* node1 = Find(p);
    UnionNode* node2 = Find(q);

    if(node1 && node2){
        node1->m_playersNum > node2->m_playersNum ?
        node2->m_parent = node1 : node1->m_parent = node2;
    }
}