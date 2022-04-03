#ifndef NODE_H
#define NODE_H

#include <cstddef>
#include <cstdint>
#include <stdint.h>
#include <vector>
#include <algorithm>

class Node
{
public:

    //members
    int val;
    Node *left, *right;

    //member functions
    Node(int val = 0);
    Node* insert(Node* root, int val);
    Node* delete_node(Node* root, int val);
    void inorder(Node* root, std::vector<int> &preorderList, std::vector<int> &levelList, int level);
};


void optimal_bts
(
    std::vector<int> key,
    std::vector<int> freq,
    std::vector<std::vector<int>> &cost,
    std::vector<std::vector<int>> &root
);

int sum_freq(std::vector<int> freq, int i, int j);
int treeHeight(Node* root);
Node* buildTree_wrap(std::vector<int> key, std::vector<int> freq);
Node* buildTree(Node* root, std::vector<int> key, std::vector<std::vector<int>> best, int start, int end);

#endif // NODE_H
