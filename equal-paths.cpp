#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here


bool equalPaths(Node * root)
{
    // Add your code below
    int path_depth = -1;
    int depth = 0;
    return dfs_depth(root, depth, path_depth);
}


bool dfs_depth(Node * root, int depth, int& path_depth){
    if(root == nullptr) return true;

    if(root->left == nullptr && root->right == nullptr){
        if(path_depth == -1){
            path_depth = depth;
        }
        if(path_depth == depth){
            return true; 
        }
    }

    depth++;
    return dfs_depth(root->left, depth, path_depth) && dfs_depth(root->right, depth, path_depth);
}

