//
// Created by david on 11/21/2022.
//

#ifndef WET1_AVLTREE_H
#define WET1_AVLTREE_H
#include "TreeNode.h"
#include "Exception.h"
#include <exception>

template<class Key, class Value>
class AVLTree {
public:
    typedef TreeNode<Key,Value> Node;
private:
    Node* m_root;
    Node* searchTree(Node* currNode, Key targetKey);
    void insertAux(Key key, Node* newNode, Node* currNode);
    Node* deleteByKeyAux(Key key, Node* root, bool* hasDataChanged);
    void goBackAndFixTree(Node* node, bool isDeleting=false);
    void goBackAndFixHeights(Node* parent);
    void deleteEntireTree(Node* currNode);
    void deleteEntireTreeDataAux(Node* currNode);
public:
    AVLTree();
    ~AVLTree();
    Node* deleteByKey(Key key, bool* hasDataChanged=nullptr);
    void deleteEntireTreeData();

    Node* insert(Key key, Value data);
    Node* find(Key key);
    Value select(int rank);
    TreeNode<Key,Value>* selectAux(TreeNode<Key,Value> * node, int rank, int counter);
    Node* getRoot();

    void printBT(const std::string& prefix,const Node* node, bool isLeft) const;
    void printBT() const;

    void rotateR(Node* node);
    void rotateL(Node* node);

};



template<class Key, class Value>
TreeNode<Key,Value>* AVLTree<Key,Value>::getRoot() {
    return m_root;
}


template<class Key, class Value>
void AVLTree<Key,Value>::deleteEntireTree(Node* currNode)
{
    if(currNode == nullptr)
        return;
    deleteEntireTree(currNode->m_leftSon);
    deleteEntireTree(currNode->m_rightSon);
    delete currNode;
}

template<class Key, class Value>
void AVLTree<Key,Value>::deleteEntireTreeData()
{
    deleteEntireTreeDataAux(m_root);
}

template<class Key, class Value>
void AVLTree<Key,Value>::deleteEntireTreeDataAux(Node* currNode)
{
    if(currNode == nullptr)
        return;
    deleteEntireTreeDataAux(currNode->m_leftSon);
    deleteEntireTreeDataAux(currNode->m_rightSon);
    delete currNode->m_data;
}

template<class Key, class Value>
AVLTree<Key,Value>::~AVLTree(){

    deleteEntireTree(m_root);
}

template<class Key, class Value>
AVLTree<Key,Value>::AVLTree():m_root(nullptr){
}

template<class Key, class Value>
void AVLTree<Key,Value>::insertAux(Key key, Node* newNode, Node* currNode)
{
    if(currNode->m_key > key)
    {

        if(currNode->m_leftSon != nullptr)
        {
            insertAux(key, newNode, currNode->m_leftSon);
            currNode->m_weight+=1;
        }
        else
        {
            // adding a new node to the left of the current node
            currNode->m_leftSon = newNode;
            currNode->m_weight+=1;
            newNode->m_parent=currNode;
            goBackAndFixTree(currNode);

        }
    }
    else if(currNode->m_key < key)
    {

        if(currNode->m_rightSon != nullptr)
        {
            insertAux(key, newNode, currNode->m_rightSon);
            currNode->m_weight+=1;
        }
        else
        {
            // adding a new node to the right of the current node
            currNode->m_rightSon = newNode;
            newNode->m_parent = currNode;
            currNode->m_weight+=1;
            goBackAndFixTree(currNode);
        }
    }
    else if(currNode->m_key == key)
        throw FailureError();
}

template<class Key, class Value>
TreeNode<Key,Value>* AVLTree<Key,Value>::insert(Key key, Value data) {
    Node*newNode;
    try{
        newNode = new Node(key, data);
    }
    catch(std::bad_alloc &e){
        throw AllocationError();
    }
    if (m_root == nullptr)
    {
        m_root = newNode;
    }
    else {
        try{
            insertAux(key, newNode, m_root);
        }
        catch(FailureError &f){
            throw f;
        }
    }
    return newNode;
}


template<class Key, class Value>
TreeNode<Key,Value>* AVLTree<Key,Value>::deleteByKeyAux(Key key, Node* root, bool* hasDataChanged)
{
    if(!find(key))
        return nullptr;

    Node* prevNode = nullptr;
    Node* currNode = root;
    // searches for the node to be deleted
    while (currNode != nullptr && currNode->m_key != key) {
        prevNode = currNode;
        prevNode->m_weight-=1;
        if (key < currNode->m_key)
            currNode = currNode->m_leftSon;
        else
            currNode = currNode->m_rightSon;
    }
    // couldn't find node to delete
    if (currNode == nullptr) // maybe unnecessary
    {
        return currNode;
    }
    // the node has maximum one child (one son or a leaf)
    if(currNode->m_rightSon == nullptr || currNode->m_leftSon== nullptr)
    {
        Node* newCurr;
        // check which son exists and get the correct one
        if(currNode->m_rightSon != nullptr)
            newCurr = currNode->m_rightSon;
        else
            newCurr = currNode->m_leftSon;

        // check if the current node is the root
        if(prevNode == nullptr)
        {
            m_root = newCurr;
            if(newCurr)
                newCurr->m_parent = nullptr;
            delete currNode;
            return newCurr;
        }

        if(currNode == prevNode->m_leftSon)
        {
            prevNode->m_leftSon =newCurr;
        }
        else
        {
            prevNode->m_rightSon=newCurr;
        }
        delete currNode;

        if(newCurr != nullptr)
            newCurr->m_parent = prevNode;
        goBackAndFixHeights(prevNode);
        return newCurr;
    }
    else //has right and left sons
    {
        // find the closest node from above the about
        // to be deleted node
        Node* parent = nullptr;
        Node* closest = currNode->m_rightSon;
        while(closest->m_leftSon!= nullptr) {
            parent = closest;
            closest = closest->m_leftSon;
        }
        // the current node is the parent of the closest
        Node* closestRightSon = closest->m_rightSon;
        if(parent != nullptr)
        {
            parent->m_leftSon = closestRightSon;
            if(closestRightSon)
                closestRightSon->m_parent = parent;
        }
        else
        {
            currNode->m_rightSon = closestRightSon;
            if(closestRightSon)
                closestRightSon->m_parent = currNode;
        }


        // copy the data from one node to another
        currNode->m_key = closest->m_key;
        currNode->m_data = closest->m_data;
        if(hasDataChanged) *hasDataChanged = true;
        delete closest;
        return currNode;
    }
}

template<class Key, class Value>
void AVLTree<Key,Value>::goBackAndFixHeights(Node* parent)
{
    Node* currNode = parent;
    while (currNode != nullptr)
    {
        currNode->calculateHeight();
        currNode = currNode->m_parent;
    }
    goBackAndFixTree(parent, true);
}

template<class Key, class Value>
TreeNode<Key,Value>* AVLTree<Key,Value>::deleteByKey(Key key, bool* hasDataChanged){
    if (m_root == nullptr)
        return m_root;
    Node* parent = deleteByKeyAux(key, m_root, hasDataChanged);
    return parent;

}

template<class Key, class Value>
TreeNode<Key,Value>* AVLTree<Key,Value>::searchTree(Node* currNode, Key targetKey)
{
    if(currNode == nullptr || currNode->m_key == targetKey) return currNode;

    if(currNode->m_key < targetKey)
        return searchTree(currNode->m_rightSon, targetKey);
    else
        return searchTree(currNode->m_leftSon, targetKey);
}

template<class Key, class Value>
TreeNode<Key,Value>* AVLTree<Key,Value>::find(Key key)
{
    TreeNode<Key,Value>* resultNode =searchTree(m_root, key);
    return resultNode;
}

template<class Key, class Value>
TreeNode<Key,Value>* AVLTree<Key,Value>::selectAux(TreeNode<Key,Value>* node, int rank, int counter)
{
    if(node == nullptr) return nullptr;

    TreeNode<Key,Value>* left = selectAux(node->m_leftSon, rank, counter);
    if(left != nullptr) return left;

    counter++;
    if(counter == rank) return node;

    TreeNode<Key,Value>* right = selectAux(node->m_rightSon, rank, counter);
    if(right != nullptr) return right;

    return nullptr;
}

template<class Key, class Value>
Value AVLTree<Key,Value>::select(int rank)
{
    TreeNode<Key,Value>* resultNode = selectAux(m_root, rank, -1);

    // Used find() before to check if the node even exists
    return resultNode->m_data;
}


template<class Key, class Value>
void AVLTree<Key,Value>::goBackAndFixTree(Node *node, bool isDeleting)
{
    bool isFixed = false;
    Node* currNode = node;
    while(currNode && (!isFixed || isDeleting))
    {
        currNode->calculateHeight();
        int balanceFactor = currNode->getBalanceFactor();
        if(balanceFactor >= 2)
        {
            // LR Check, else doing LL
            if(currNode->m_leftSon && currNode->m_leftSon->getBalanceFactor() < 0)
            {
                rotateL(currNode->m_leftSon);
            }
            rotateR(currNode);
            isFixed = true;
        }
        else if(balanceFactor <= -2)
        {
            // RL check, else doing RR
            if(currNode->m_rightSon && currNode->m_rightSon->getBalanceFactor() > 0)
            {
                rotateR(currNode->m_rightSon);
            }
            rotateL(currNode);
            isFixed = true;
        }
        currNode = currNode->m_parent;
    }

}

template<class Key, class Value>
void AVLTree<Key,Value>::rotateR(Node* node){
    Node* parent = node->m_parent;
    Node* newRoot = node->m_leftSon;
    Node* newRootSon = newRoot->m_rightSon;
    int nodeWeight = 1;
    int newRootWeight = 1;
    if(newRoot != nullptr) {
        if(newRootSon)
        {
            node->m_leftSon = newRootSon;
            newRootSon->m_parent = node;
            nodeWeight += newRootSon->m_weight;
        }
        else
        {
            node->m_leftSon=nullptr;
        }

        newRoot->m_rightSon = node;
        node->m_parent = newRoot;
        if(node->m_rightSon)
            nodeWeight+= node->m_rightSon->m_weight;
        if(newRoot->m_leftSon)
            newRootWeight+= newRoot->m_leftSon->m_weight;

        if(node == m_root)
        {
            m_root = newRoot;
        }
        newRootWeight += nodeWeight;
        node->m_weight = nodeWeight;
        newRoot->m_weight = newRootWeight;
        node->calculateHeight(); // Update height of B
        newRoot->calculateHeight();

        newRoot->m_parent = nullptr;
        if(parent)
        {
            if(parent->m_key < newRoot->m_key)
                parent->m_rightSon = newRoot;
            else
                parent->m_leftSon = newRoot;
            newRoot->m_parent = parent;
            parent->calculateHeight(); // Update height of B
        }


    }
}

template<class Key, class Value>
void AVLTree<Key,Value>::rotateL(Node* node){
    Node* parent = node->m_parent;
    Node* newRoot = node->m_rightSon;
    Node* newRootSon = newRoot->m_leftSon;
    int nodeWeight = 1;
    int newRootWeight = 1;
    if(newRoot != nullptr) {
        if(newRootSon)
        {
            node->m_rightSon=newRootSon;
            newRootSon->m_parent = node;
            nodeWeight += newRootSon->m_weight;
        }
        else
        {
            node->m_rightSon=nullptr;
        }
        newRoot->m_leftSon = node;
        node->m_parent = newRoot;

        if(node->m_leftSon)
            nodeWeight+= node->m_leftSon->m_weight;
        if(newRoot->m_rightSon)
            newRootWeight+= newRoot->m_rightSon->m_weight;

        if(node == m_root)
        {
            m_root = newRoot;
        }
        newRootWeight += nodeWeight;
        node->m_weight = nodeWeight;
        newRoot->m_weight = newRootWeight;
        node->calculateHeight(); // Update height of B
        newRoot->m_parent = nullptr;
        if(parent)
        {
            if(parent->m_key < newRoot->m_key)
                parent->m_rightSon= newRoot;
            else
                parent->m_leftSon = newRoot;
            newRoot->m_parent = parent;
            parent->calculateHeight(); // Update height of B
        }


    }
}


// PRINT THE DAMN TREE
template<class Key, class Value>
void AVLTree<Key,Value>::printBT(const std::string& prefix, const Node* node, bool isLeft) const
{
    if (node != nullptr)
    {
        std::cout << prefix;
        std::cout << (isLeft ? "|--" : "L--");
        // print the value of the node
        std::cout << node->m_key  << " Weight: "<< node->m_weight << std::endl;
        // enter the next tree level - left and right branch
        printBT(prefix + (isLeft ? "|   " : "    "), node->m_rightSon, true);
        printBT(prefix + (isLeft ? "|   " : "    "), node->m_leftSon, false);
    }
}

template<class Key, class Value>
void AVLTree<Key,Value>::printBT() const
{
    printBT("", m_root, false);
}


template<class Key, class Value>
static void merge(TreeNode<Value,Key>* a  [], int na, TreeNode<Value,Key>* b[], int nb, TreeNode<Value,Key>* c []) //key or value
{
    int ia = 0, ib = 0, ic = 0;
    while(ia < na && ib < nb) {
        if (a[ia]->m_key < b[ib]->m_key)
            c[ic++] = a[ia++];
        else
            c[ic++] = b[ib++];
    }
    while(ia < na)
        c[ic++] = a[ia++];
    while(ib < nb)
        c[ic++] = b[ib++];
}



#endif //WET1_AVLTREE_H
