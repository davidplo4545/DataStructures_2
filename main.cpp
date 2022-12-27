#include <iostream>
#include "HashTable.h"
#include "Player.h"
#include "Exception.h"
using std::rand;
int main() {
    HashTable hs = HashTable();
    for(int i=100;i<200;i++)
    {

        try{
            auto pl = new Player(rand()%100000,5,0,0,0, false);
            hs.insert(pl->getId(),pl);
            HashNode* tempNode = hs.find(pl->getId());
            std::cout << "Found player:" << tempNode->player << std::endl;
        }
        catch(FailureError &e)
        {
            std::cout <<" Value already exists" << std::endl;
        }
        catch(InvalidInput &e)
        {
            std::cout  <<" Value already exists" << std::endl;
        }

    }
    std::cout << "PRINT TABLE" << std::endl;
    HashNode* tempNode = hs.find(5);
    hs.printTable();

    return 0;
}
