#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * newNode = (TreeNode *)malloc(sizeof(TreeNode));
    if (newNode == NULL) return NULL;
    newNode->pair = (Pair *)malloc(sizeof(Pair));
    newNode->pair->key = key;
    newNode->pair->value = value;
    newNode->parent = newNode->left = newNode->right = NULL;
    return newNode;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * newNode = (TreeMap *)malloc(sizeof(TreeMap));
    newNode->root = NULL;
    newNode->current = NULL;
    newNode->lower_than = lower_than;
    return newNode;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    if (tree == NULL || key == NULL || value == NULL)
    {
        return;
    }
    TreeNode * newNode = createTreeNode(key, value);
    
    if (tree->root == NULL)
    {
        tree->root = newNode;
    }
    else
    {
        TreeNode * aux = tree->root;
        while (aux != NULL)
            {
                if (tree->lower_than(key, aux->pair->key) == 1)
                {
                    if (aux->left == NULL)
                    {
                        aux->left = newNode;
                        newNode->parent = aux;
                        break;
                    }
                    else
                    {
                        aux = aux->left;
                    }
                }
                else if (tree->lower_than(key, aux->pair->key) == 0 )
                {
                    if (aux->right == NULL)
                    {
                        aux->right = newNode;
                        newNode->parent = aux;
                        break;
                    }
                    else
                    {
                        aux = aux->right;
                    }
                }
                else
                {
                    free(newNode);
                    break;
                }
            }
    }
    

}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
