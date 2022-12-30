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
        teams[i] = new Team(i);
    for(int i=100;i<200;i++)
    {
        try{
            auto pl = new Player(i,permutation_t::neutral(),i%TEAMS_NUM,0,0, false);
            uf->insertPlayer(pl,teams[i%TEAMS_NUM]);
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
    uf->print();
    uf->unite(160,161);
    uf->unite(162,161);
    uf->unite(164,163);
    uf->unite(165,166);
    uf->unite(101,193);
    uf->unite(101,199);
    uf->unite(105,107);
    uf->unite(124,107);
    std::cout << "PRINT TABLE" << std::endl;
    uf->print();

    delete uf;
}
int main() {
    printUnionFindTest();
    return 0;
}
