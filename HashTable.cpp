//
// Created by David on 24/12/2022.
//

#include "HashTable.h"

HashNode::HashNode() :player(nullptr), playerKey(-1), chainNext(nullptr){}


HashTable::HashTable() : m_size(HashTable::MIN_SIZE), m_currSize(0) {
    m_table = new HashNode*[m_size];
    initTable(m_table, m_size);
}


HashTable::~HashTable(){
    HashNode* nodeToDelete;
    HashNode* temp;
    for(int i=0;i<m_size;i++)
    {
        nodeToDelete = m_table[i];
        while(nodeToDelete != nullptr)
        {
            temp = nodeToDelete->chainNext;
            // TODO: Call UnionNode Delete here and check if team is out of
            // TODO: the game to delete it too, delete Player inside of UnionNode
            delete nodeToDelete;
            nodeToDelete = temp;
        }
    }
    delete []m_table;
}

bool HashTable::shouldExpand() const { return m_size* LOAD_FACTOR == m_currSize; }

int HashTable::hash(int key, int mod){
    return key%mod;
}


void HashTable::insert(int id, Player* player) {
    if(shouldExpand())
        increaseArraySize();
    int index = hash(id, m_size);
    HashNode* currNode = m_table[index];
    // Starting a "new chain"
    if(currNode->playerKey == -1)
    {
        currNode->playerKey = id;
        currNode->player = player;
        // TODO: add union node
    }
    else
    {
        // Adding to an existing chain
        while(currNode->chainNext != nullptr)
        {
            if(currNode->playerKey == id)
                throw FailureError();
            currNode = currNode->chainNext;
        }
        currNode->chainNext = new HashNode();
        currNode->chainNext->player = player;
        currNode->chainNext->playerKey = id;
        // TODO: add to union find
    }
    m_currSize++;
}

void HashTable::initTable(HashNode** newTable, int size)
{
    for(int i=0;i<size;i++)
    {
        newTable[i] = new HashNode();
    }
}
void HashTable::insertToNewTable(HashNode* newNode, HashNode** newTable)
{
    int newIndex;
    newIndex = hash(newNode->playerKey, m_size*2);
    HashNode* currNode = newTable[newIndex];
    if(currNode->playerKey == -1)
    {
        newTable[newIndex] = newNode;
        return;
    }
    while(currNode->chainNext != nullptr)
    {
        currNode = currNode->chainNext;
    }
    currNode->chainNext = newNode;
}

HashNode* HashTable::find(int id) {
    int index = hash(id, m_size);
    HashNode* currNode = m_table[index];
    while(currNode != nullptr)
    {
        if(currNode->playerKey == id)
            return currNode;
        currNode = currNode->chainNext;
    }
    return nullptr;
}

void HashTable::increaseArraySize() {
    auto newTable = new HashNode*[2*m_size];
    initTable(newTable, 2*m_size);
    HashNode* currNode;
    HashNode* temp;
    for(int i=0;i<m_size;i++)
    {
        currNode = m_table[i];
        while(currNode != nullptr && currNode->playerKey != -1)
        {
            temp = currNode->chainNext;
            currNode->chainNext = nullptr;
            insertToNewTable(currNode, newTable);
            currNode = temp;
        }
    }
    m_size *=2;
    delete [] m_table;
    m_table = newTable;
}

void HashTable::printTable()
{
    HashNode* currNode;
    for(int i=0;i<m_size;i++)
    {
        std::cout << i << " || ";
        currNode = m_table[i];
        while(currNode != nullptr)
        {
            if(currNode->playerKey != -1)
                std::cout << currNode->playerKey << "-->";
            currNode = currNode->chainNext;
        }
        std::cout << "" << std::endl;

    }
}








