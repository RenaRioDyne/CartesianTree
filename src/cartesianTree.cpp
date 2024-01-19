// paper: Simone Faro et al., On the longest common Cartesian substring problem
// method: Tree-Extend-Right(T,e) and Build-Cartesian-Tree(x,m), p.4

#include "cartesianTree.h"
#include <iostream>

CartesianTree::CartesianTree(std::string_view targetString){
    root = rightmost = nullptr;
    numNodes = rplen = 0;
    if(targetString.length() == 0) return;

    root = rightmost = new treeNode{nullptr, nullptr, nullptr, nullptr, numNodes++, targetString[0], 0};
    rplen = 1;

    for(int i=1; i<targetString.length(); i++){
        append(targetString[i]);
    }
}


CartesianTree::~CartesianTree(){
    dfsdelete(root);
}

void CartesianTree::dfsdelete(treeNode* cur){
    if(cur == nullptr) return;
    dfsdelete(cur->left);
    dfsdelete(cur->right);
    delete cur;
}

void CartesianTree::append(int newValue){
    treeNode* newnode;
    treeNode* cur;

    newnode = new treeNode{nullptr, nullptr, nullptr, nullptr, numNodes++, newValue, 0};
    cur = rightmost;
    while(cur != nullptr && newnode->value < cur->value){
        newnode->leftSubtreeSize += (cur->leftSubtreeSize + 1);
        cur = cur->parent;
        rplen--;
    }
    if(cur == nullptr){
        newnode->left = root;
        root->parent = newnode;
        root = newnode;
    }else{
        if(cur->right != nullptr){
            cur->right->parent = newnode;
        }
        newnode->left = cur->right;
        cur->right = newnode;
        newnode->parent = cur;
    }
    newnode->prevRightmost = rightmost;
    rightmost = newnode;
    rplen++;
}

void CartesianTree::printTree(){
    std::cout << "printing tree..." << std::endl;
    dfsprint(root,0,0);
    std::cout << "rplen: " << rplen << std::endl;
}

int CartesianTree::dfsprint(treeNode* cur, int depth, int width){
    if(cur == nullptr) return width;
    std::cout << "(" << depth << "," << width << "," << (cur->value) << ")" << std::endl;
    width = dfsprint(cur->left, depth+1, width);
    return dfsprint(cur->right, depth+1, width+1);
}