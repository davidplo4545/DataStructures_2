#include <iostream>
#include "HashTable.h"
#include "UnionFind.h"
#include "Player.h"
#include "Team.h"
#include "Exception.h"
#include "wet2util.h"
using std::rand;

void printUnionFindTest()
{
    auto uf = new UnionFind();
    const int TEAMS_NUM = 10;
    Team* teams [TEAMS_NUM];
    for(int i=0;i<TEAMS_NUM;i++)
        teams[i] = new Team(rand()%2000);
    for(int i=100;i<200;i++)
    {
        try{
            auto pl = new Player(i,permutation_t::neutral(),i%TEAMS_NUM,0,0, false);
            uf->insertPlayer(pl,teams[rand()%TEAMS_NUM]);
//            HashNode* tempNode = hs->find(pl->getId());
//            std::cout << "Found player:" << tempNode->m_player << std::endl;
        }
        catch(FailureError &e)
        {
        }
        catch(InvalidInput &e)
        {
        }
    }
    std::cout << "PRINT TABLE" << std::endl;
//    HashNode* tempNode = hs->find(5);
    uf->print();
    delete uf;
}
int main() {
    printUnionFindTest();
    return 0;
}
