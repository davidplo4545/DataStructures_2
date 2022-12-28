//
// Created by David on 24/12/2022.
//

#include "HashTable.h"


HashNode::HashNode() :m_player(nullptr),m_playerKey(-1), chainNext(nullptr), uniNode(nullptr){}


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
            delete nodeToDelete->uniNode;
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



HashNode* HashTable::insert(Player* player, Team* team) {
    int id = player->getId();
    if(shouldExpand())
        increaseArraySize();
    int index = hash(id, m_size);
    HashNode* currNode = m_table[index];

    // Starting a "new chain"
    if(currNode->m_playerKey == -1)
    {
        currNode->m_playerKey = id;
        currNode->m_player = player;
        m_currSize++;
    }
    else
    {
        HashNode* prev = currNode;
        // Adding to an existing chain
        while(currNode != nullptr)
        {
            if(currNode->m_playerKey == id)
                throw FailureError();
            prev = currNode;
            currNode = currNode->chainNext;
        }
        prev->chainNext = new HashNode();
        prev->chainNext->m_player = player;
        prev->chainNext->m_playerKey = id;
        m_currSize++;

        return prev->chainNext;
    }
    return currNode;
}

void HashTable::initTable(HashNode** newTable, int size)
{
    for(int i=0;i<size;i++)
    {
        newTable[i] = new HashNode();
    }
}
void HashTable::insertToNewTable(HashNode* newNode, HashNode** newTable) const
{
    int newIndex;
    newIndex = hash(newNode->m_playerKey, m_size*2);
    HashNode* currNode = newTable[newIndex];
    if(currNode->m_playerKey == -1)
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
        if(currNode->m_playerKey == id)
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
        while(currNode != nullptr && currNode->m_playerKey != -1)
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
            if(currNode->m_playerKey != -1)
                std::cout << currNode->m_playerKey << "-->";
            currNode = currNode->chainNext;
        }
        std::cout << "" << std::endl;

    }
}

int HashTable::getSize() const { return m_size;}


