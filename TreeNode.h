//
// Created by david on 11/21/2022.
//
#include <iostream>

#ifndef WET1_TREENODE_H
#define WET1_TREENODE_H

template<class Key, class Value>
struct TreeNode {
    Key m_key;
    Value m_data;
    TreeNode* m_leftSon;
    TreeNode* m_rightSon;
    TreeNode* m_parent;
    int m_height;
    int m_weight;

    TreeNode(Key id, Value data);
    TreeNode()=default;
    ~TreeNode() = default;
    void calculateHeight();
    int getBalanceFactor() const;
    Value getData();
    static int getHeight(const TreeNode* node) {
        if(node == nullptr) return -1;
        else
            return node->m_height;
    }
};


template<class Key, class Value>
Value TreeNode<Key,Value>::getData()
{
    return m_data;
}
template<class Key, class Value>
TreeNode<Key,Value>::TreeNode(Key id, Value data) :m_key(id),m_data(data), m_leftSon(nullptr),m_rightSon(nullptr), m_parent(nullptr), m_height(0), m_weight(1){
}


template<class Key, class Value>
int TreeNode<Key,Value>::getBalanceFactor() const {
    return (getHeight(m_leftSon) - getHeight(m_rightSon));
}

template<class Key, class Value>
void TreeNode<Key,Value>::calculateHeight()
{
    const int leftHeight = getHeight(m_leftSon);
    const int rightHeight = getHeight(m_rightSon);
    if(leftHeight > rightHeight)
        m_height = leftHeight;
    else
        m_height = rightHeight;
    m_height+=1;
}

#endif //WET1_TREENODE_H
