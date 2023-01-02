#include "UnionFind.h"




UnionFind::UnionFind() : m_hashTable(new HashTable())
{
    testingChain = new TestNode(); // Create dummy node
    lastNode = testingChain;
}

UnionFind::~UnionFind() {
    delete m_hashTable;

    //// TESTING PURPOSES
    TestNode* tempNode;
    while(testingChain)
    {
        tempNode = testingChain->next;
        delete testingChain;
        testingChain = tempNode;
    }

    ////
}


HashTable* UnionFind::getTable() {
    return m_hashTable;
}

UnionNode* UnionFind::find(int id) { //update during shrink
    HashNode* hsNode = m_hashTable->find(id);
    if(hsNode == nullptr) return nullptr;
    UnionNode *uf = hsNode->uniNode;
    UnionNode *temp = uf;
    UnionNode *root=nullptr;
    int sum=0;
    permutation_t totalPermutation = permutation_t::neutral();
    if (uf) {
        while (uf->m_parent) {
            sum+=uf->m_extraGamesPlayed;
            totalPermutation = totalPermutation * uf->m_extraPermutation.inv();
            uf = uf->m_parent;
        }
        root = uf;
        uf = temp;
        int currGamesPlayed = 0;
        int currSum = 0;

        totalPermutation = totalPermutation.inv();
        permutation_t currPermutation = permutation_t::neutral();
        permutation_t currTotalPermutation = permutation_t::neutral();
        while (uf->m_parent){
            temp = uf->m_parent;
            uf->m_parent = root;
            currPermutation = uf->m_extraPermutation;
            currGamesPlayed = uf->m_extraGamesPlayed;
            uf->m_extraGamesPlayed = sum - currSum;
            uf->m_extraPermutation = currTotalPermutation.inv() * totalPermutation;
            currSum += currGamesPlayed;
            currTotalPermutation = currTotalPermutation * currPermutation.inv();
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
        boughtNode->m_extraPermutation=(buyerNode->m_extraPermutation.inv())*buyerNode->m_team->getTeamSpirit()*boughtNode->m_extraPermutation;
        boughtNode->m_team=nullptr;
    }
    else
    {
        buyerNode->m_parent = boughtNode;
        buyerNode->m_extraGamesPlayed += buyerNode->m_team->getGamesPlayed() - boughtNode->m_team->getGamesPlayed();
//        boughtNode->m_extraGamesPlayed=boughtNode->m_team->getGamesPlayed() - buyerNode->m_team->getGamesPlayed();
        boughtNode->m_extraPermutation=buyerNode->m_team->getTeamSpirit()*boughtNode->m_extraPermutation;
        buyerNode->m_extraPermutation=boughtNode->m_extraPermutation.inv()*buyerNode->m_extraPermutation;

        buyerNode->m_team->setGamesPlayed(boughtNode->m_team->getGamesPlayed());
        boughtNode->m_team = buyerNode->m_team;

        buyerNode->m_team->setRootUnionNode(boughtNode);
        buyerNode->m_team = nullptr;

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
            buyer->updateTeamSpirit(bought->getTeamSpirit());
            ///// TESTING PURPOSES
            lastNode->next = new TestNode();
            lastNode->next->team = buyer;
            lastNode=lastNode->next;
            ////////
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
        newUniNode->m_extraPermutation=player->getSpirit();
        player->updateGamesPlayedByFactor(team->getGamesPlayed());
        ///// TESTING PURPOSES
        lastNode->next = new TestNode();
        lastNode->next->team = team;
        lastNode=lastNode->next;
        ////////
    }
    else{
        UnionNode* rootUniNode = team->getRootUnionNode();
        newUniNode->m_parent=rootUniNode;
        newUniNode->m_extraGamesPlayed=-team->getGamesPlayed();
        newUniNode->m_extraPermutation=rootUniNode->m_extraPermutation.inv()*team->getTeamSpirit()*player->getSpirit();
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

    permutation_t result = permutation_t::neutral();
    while(currNode)
    {
        result = result*((currNode->m_extraPermutation).inv());
        currNode= currNode->m_parent;
    }
    return result.inv();
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

}

