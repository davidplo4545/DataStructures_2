#include "UnionFind.h"




UnionFind::UnionFind() : m_hashTable(new HashTable())
{
    testingChain = new TestNode(); // Create dummy node
    lastNode = testingChain;
}


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
        node1->m_team->getGamesPlayed() > node2->m_team->getGamesPlayed() ?
        node2->m_parent = node1 : node1->m_parent = node2;
    }
}

void UnionFind::createUnionNode(HashNode* newHashNode, Player* player, Team* team)
{
    UnionNode* newUniNode = new UnionNode();
    newHashNode->uniNode = newUniNode;
    // check if team has no players
    if(team->getPlayersCount() == 0)
    {
        newUniNode->m_team=team;
        ///// TESTING PURPOSES
        lastNode->next = new TestNode();
        lastNode->next->team = team;
        lastNode=lastNode->next;
        ////////
        team->setRootUnionNode(newUniNode);
        // TODO:Update permutation/gamesPlayed REQUIRED
    }
    else{
        UnionNode* rootUniNode = team->getRootUnionNode();
        newUniNode->m_parent=rootUniNode;
        // TODO:Update permutation/gamesPlayed REQUIRED

    }
}

int UnionFind::calculateGamesPlayed(Player* player)
{
    int result = player->getGamesPlayed();
    UnionNode* currNode = m_hashTable->find(player->getId())->uniNode;
    if(currNode == nullptr) throw FailureError();
    while(currNode)
    {
        if(currNode->m_team)
            result += currNode->m_team->getGamesPlayed();
        currNode= currNode->m_parent;
    }
    return result;
}

void UnionFind::insertPlayer(Player *player, Team *team) {
    HashNode* hashNode;
    try{
        hashNode = m_hashTable->insert(player, team);
        createUnionNode(hashNode, player, team);
        team->increasePlayerCount();
    }
    catch(FailureError &e)
    {
        throw FailureError();
    }
}

void UnionFind::print()
{
    TestNode* testNode=testingChain->next;
    HashNode* currNode;
    while(testNode)
    {
        std::cout<< "Team ID: " << testNode->team->getId() << " players are: ";
        for(int i=0;i<m_hashTable->getSize();i++)
        {
            currNode = m_hashTable->m_table[i];
            while(currNode != nullptr)
            {
                if(currNode->m_playerKey != -1)
                {
                    Team* team = find(currNode->m_playerKey);
                    if(team ==testNode->team)
                        std::cout << currNode->m_player->getId() << ",";
                    currNode = currNode->chainNext;
                }
            }
        }
        std::cout << "" << std::endl;
        testNode = testNode->next;
    }

};

