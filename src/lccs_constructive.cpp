// paper: Simone Faro et al., On the longest common Cartesian substring problem
// method: Longest-Common-Suffix(Tx, Ty), p.9 & LcCs-Scan(x,y,m,n,lcs), Constructive-Cartesian-Substring(x,y), p.10

#include "cartesianTree.h"
#include <string_view>
#include <iostream>
#include <cstring>

static int lccsScan(std::string_view x, std::string_view y, int lcs);

int CartesianTree::longestCommonSuffix(CartesianTree* otherTree){
    if(rplen == otherTree->rplen) return numNodes;

    int m = numNodes;
    CartesianTree garbage1(""), garbage2("");


    if(rightmost->left == nullptr || otherTree->rightmost->left == nullptr){ // should be a single node
        treeNode* temp = rightmost;

        //printTree();

        // remove nodes from this
        if(rightmost->parent != nullptr) rightmost->parent->right = rightmost->left;
        else root = rightmost->left;
        if(rightmost->left != nullptr) rightmost->left->parent = rightmost->parent;
        rightmost->parent = rightmost->left = nullptr;
        garbage1.root = root;
        root = rightmost;

        //printTree();

        // remove nodes from otherTree
        if(otherTree->rightmost->parent != nullptr) otherTree->rightmost->parent->right = otherTree->rightmost->left;
        else otherTree->root = otherTree->rightmost->left;
        if(otherTree->rightmost->left != nullptr) otherTree->rightmost->left->parent = otherTree->rightmost->parent;
        otherTree->rightmost->parent = otherTree->rightmost->left = nullptr;
        garbage2.root = otherTree->root;
        otherTree->root = otherTree->rightmost;

        root->prevRightmost = otherTree->root->prevRightmost = nullptr;
        rplen = otherTree->rplen = 1;
        numNodes = otherTree->numNodes = 1;

        //otherTree->printTree();
        
        return 1;
    }

    CartesianTree* this_proxy = this;
    if(rplen <= otherTree->rplen){
        std::swap(this_proxy, otherTree);
    }
    
    if(this_proxy->rightmost->parent != nullptr) this_proxy->rightmost->parent->right = nullptr;
    this_proxy->rightmost->parent = nullptr;
    garbage1.root = this_proxy->root;
    this_proxy->root = this_proxy->rightmost;

    this_proxy->numNodes = this_proxy->root->leftSubtreeSize + 1;
    
    treeNode* cur = otherTree->rightmost->prevRightmost;
    otherTree->numNodes = cur->leftSubtreeSize + 1;
    //std::cerr << otherTree->numNodes+1 << " and " << this_proxy->numNodes << std::endl;

    while(otherTree->numNodes + 1 != this_proxy->numNodes){
        //std::cerr << otherTree->numNodes+1 << " and " << this_proxy->numNodes << std::endl;
        cur = cur->parent;
        otherTree->numNodes += cur->leftSubtreeSize + 1;
    }
    otherTree->rightmost->leftSubtreeSize = otherTree->numNodes++;

    if(otherTree->rightmost->parent != nullptr){
        otherTree->rightmost->parent->right = otherTree->rightmost->left;
    }else{
        otherTree->root = otherTree->rightmost->left;
    }
    otherTree->rightmost->left->parent = otherTree->rightmost->parent;

    otherTree->rightmost->left = cur;
    otherTree->rightmost->parent = nullptr;
    
    cur->parent->right = nullptr;
    cur->parent = otherTree->rightmost;

    otherTree->rplen = this_proxy->rplen = 1;

    garbage2.root = otherTree->root;
    otherTree->root = otherTree->rightmost;

    if(numNodes == 1){
        this_proxy->root->prevRightmost = otherTree->root->prevRightmost = nullptr;
    }

    return numNodes;
}

int lccs_constructive_main(int argc, char** argv){
    if(argc < 3){
        fprintf(stderr, "give 2+ strings to compute their longest common cartesian subsequence.\n");
        return -1;
    }

    int lcs = 1;
    for(int j=0; j<strlen(argv[2]); j++){
        lcs = lccsScan(argv[1], argv[2]+j, lcs);
    }
    for(int i=1; i<strlen(argv[1]); i++){
        lcs = lccsScan(argv[1]+i, argv[2], lcs);
    }
    
    std::cout << "Constructive lccs result: " << lcs << std::endl;

    return 0;
}

static int lccsScan(std::string_view x, std::string_view y, int lcs){
    CartesianTree Tx(x.substr(0,1));
    CartesianTree Ty(y.substr(0,1));
    int r;

    for(int i=1; i<std::min(x.length(), y.length()); i++){
        //std::cerr << i <<"th iter" << std::endl;
        Tx.append(x[i]);
        Ty.append(y[i]);
        
        r = Tx.longestCommonSuffix(&Ty);
        //std::cerr << "hiyaa" << std::endl;
        //Tx.printTree();
        if(r > lcs) lcs = r;
    }

    return lcs;
}