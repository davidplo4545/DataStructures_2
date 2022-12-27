#include "UnionFind.h"




UnionFind::UnionFind() : m_hashTable(new HashTable())
{}


HashTable* UnionFind::getTable() {
    return m_hashTable;
}

Team* UnionFind::find(int id) { //update during shrink
    UnionNode *uf = m_hashTable->find(id)->uniNode;
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
        return root->m_team;
    }
    return nullptr;
}
void UnionFind::unite(int p, int q) {
    UnionNode* node1 = m_hashTable->find(p)->uniNode;
    UnionNode* node2 = m_hashTable->find(q)->uniNode;

    if(node1 && node2){
        node1->m_playersNum > node2->m_playersNum ?
        node2->m_parent = node1 : node1->m_parent = node2;
    }
}

void UnionFind::insertPlayer(Player *player, Team *team) {
    HashNode* hashNode;
    try{
        hashNode = m_hashTable->insert(player, team);
    }
    catch(FailureError &e)
    {
        throw FailureError();
    }
}