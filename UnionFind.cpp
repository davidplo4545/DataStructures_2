#include "UnionFind.h"




UnionFind::UnionFind() : m_hashTable(new HashTable())
{
    testingChain = new TestNode(); // Create dummy node
    lastNode = testingChain;
}


HashTable* UnionFind::getTable() {
    return m_hashTable;
}

UnionNode* UnionFind::find(int id) { //update during shrink
    UnionNode *uf = m_hashTable->find(id)->uniNode;
    UnionNode *temp = uf;
    UnionNode *root=nullptr;
    int sum=0;
    if (uf) {
        while (uf->m_parent) {
            sum+=uf->m_extraGamesPlayed;
            uf = uf->m_parent;
        }
        root = uf;
        uf = temp;
        int currGamesPlayed = 0;
        int currSum = 0;
        while (uf->m_parent){
            temp = uf->m_parent;
            uf->m_parent = root;
            currGamesPlayed = uf->m_extraGamesPlayed;
            uf->m_extraGamesPlayed = sum - currSum;
            currSum += currGamesPlayed;
            uf = temp;
        }
        return root;
    }
    return nullptr;
}
void UnionFind::unite(UnionNode* buyerNode, UnionNode* boughtNode) {

    if(buyerNode->m_team->getPlayersCount() >= boughtNode->m_team->getPlayersCount())
    {
        boughtNode->m_parent = buyerNode;
        boughtNode->m_extraGamesPlayed=boughtNode->m_team->getGamesPlayed() - buyerNode->m_team->getGamesPlayed();
        // TODO: Update Spirit here
    }
    else
    {
        buyerNode->m_parent = boughtNode;
        boughtNode->m_extraGamesPlayed=boughtNode->m_team->getGamesPlayed() - buyerNode->m_team->getGamesPlayed();

        boughtNode->m_team = buyerNode->m_team;
        buyerNode->m_team->setRootUnionNode(boughtNode);
        // TODO: Update Spirit here
    }
}


void UnionFind::buyTeam(Team* buyer, Team* bought)
{
    UnionNode* uniNodeBuyer = buyer->getRootUnionNode();
    UnionNode* uniNodeBought = bought->getRootUnionNode();

    if(uniNodeBought && uniNodeBuyer)
    {
        unite(uniNodeBuyer, uniNodeBought);
    }
    else{
        if(uniNodeBuyer == nullptr)
        {
            buyer->setRootUnionNode(uniNodeBought);
            buyer->setGamesPlayed(bought->getGamesPlayed());
            ///// TESTING PURPOSES
            lastNode->next = new TestNode();
            lastNode->next->team = buyer;
            lastNode=lastNode->next;
            ////////
            // TODO: Update spirit (maybe inside unite)
            if(uniNodeBought != nullptr)
                uniNodeBought->m_team = buyer;
        }
    }

}

void UnionFind::createUnionNode(HashNode* newHashNode, Player* player, Team* team)
{
    UnionNode* newUniNode = new UnionNode();
    newHashNode->uniNode = newUniNode;
    newUniNode->m_player = player;
    // check if team has no players
    if(team->getPlayersCount() == 0)
    {
        newUniNode->m_team=team;
        team->setRootUnionNode(newUniNode);
        newUniNode->m_extraGamesPlayed=0;
        player->updateGamesPlayedByFactor(team->getGamesPlayed());
        ///// TESTING PURPOSES
        lastNode->next = new TestNode();
        lastNode->next->team = team;
        lastNode=lastNode->next;
        ////////
        // TODO:Update permutation REQUIRED
    }
    else{
        UnionNode* rootUniNode = team->getRootUnionNode();
        newUniNode->m_parent=rootUniNode;
        newUniNode->m_extraGamesPlayed=-team->getGamesPlayed();

        // TODO:Update permutation REQUIRED

    }
}

int UnionFind::calculateGamesPlayed(int id)
{
    HashNode* hsNode =  m_hashTable->find(id);
    if(hsNode == nullptr) throw FailureError();

    UnionNode* currNode = hsNode->uniNode;
    Player* player = hsNode->m_player;
    int result = player->getGamesPlayed();

    while(currNode->m_parent)
    {
        result += currNode->m_extraGamesPlayed;
        currNode= currNode->m_parent;
    }
    result+=currNode->m_extraGamesPlayed;
    result+=currNode->m_team->getGamesPlayed();
    return result;
}

permutation_t UnionFind::calculateSpirit(int id)
{
    HashNode* hsNode =  m_hashTable->find(id);
    if(hsNode == nullptr) throw FailureError();

    UnionNode* currNode = hsNode->uniNode;
    Player* player = hsNode->m_player;
    // TODO: Check how the calculation will be made
//    int result = player->getGamesPlayed();
    permutation_t result;
    while(currNode->m_parent)
    {
        result = result*currNode->m_extraPermutation;
        currNode= currNode->m_parent;
    }
//    result+=currNode->m_extraGamesPlayed;
//    result+=currNode->m_team->getGamesPlayed();
    return result;
}

void UnionFind::insertPlayer(Player *player, Team *team) {
    HashNode* hashNode;
    try{
        hashNode = m_hashTable->insert(player, team);
        createUnionNode(hashNode, player, team);
        team->increasePlayerCount();
        if(player->isGoalKeeper())
            team->increaseGoalKeepers(1);
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
                    UnionNode* uniNode = find(currNode->m_playerKey);
                    if(uniNode->m_team ==testNode->team)
                        std::cout << currNode->m_player->getId() << ",";
                }
                currNode = currNode->chainNext;

            }
        }
        std::cout << "" << std::endl;
        testNode = testNode->next;
    }

};

