#pragma once

// paper: Simone Faro et al., On the longest common Cartesian substring problem
// method: Tree-Extend-Right(T,e), Build-Cartesian-Tree(x,m), p.4, and Longest-Common-Suffix(Tx, Ty), p.9

#include <string_view>

struct treeNode {
    treeNode* parent;
    treeNode* left;
    treeNode* right;
    treeNode* prevRightmost;
    int index;
    int value;
    int leftSubtreeSize;
};

class CartesianTree {
private:
    treeNode* root;
    treeNode* rightmost;
    int numNodes;
    int rplen;
    void dfsdelete(treeNode* cur);
    int dfsprint(treeNode* cur, int depth, int width);

public:
    CartesianTree(std::string_view targetString);       // Build-Cartesian-Tree
    ~CartesianTree();
    void append(int newValue);                          // Tree-Extend-Right
    int longestCommonSuffix(CartesianTree* otherTree);  // Longest-Common-Suffix   !!modifies both trees!!
    void printTree();
};