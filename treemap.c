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
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    if (tree == NULL || key == NULL || value == NULL)
    {
        return;
    }
    TreeNode * new = createTreeNode(key, value);
    if (tree->root == NULL){
        tree->root = new;
        tree->current = new;
        return;
    }
    else {
        TreeNode * aux = tree->root;
        while (aux != NULL) {
            if (is_equal(tree, key, aux->pair->key)){
                tree->current = aux;
                return;
            }
            else if (tree->lower_than(key, aux->pair->key)) {
                if (aux->left == NULL) {
                    new->parent = aux;
                    aux->left = new;
                    tree->current = new;
                    break;
                }
                else {
                    aux = aux->left;
                }
            }
            else {
                if (aux->right == NULL) {
                    new->parent = aux;
                    aux->right = new;
                    tree->current = new;
                    break;
                }
                else {
                    aux = aux->right;
                }
            }
        }
    }
    
}

TreeNode * minimum(TreeNode * x){
    while(x->left != NULL) x=x->left;
    return x;
    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {
        TreeNode * aux = tree->root;
        TreeNode * parent = NULL;
        while (aux != NULL && !is_equal(tree, aux->pair->key,node->pair->key))
            {
                parent = aux;
                if (tree->lower_than(node->pair->key, aux->pair->key))
                {
                    aux = aux->left;
                }
                else
                {
                    aux = aux->right;
                }
            }
        if (aux == NULL) return;

        if (aux->left == NULL && aux->right == NULL)
        {
            if (aux != tree->root)
            {
                if (parent->left == aux)
                {
                    parent->left = NULL;
                }
                else
                {
                    parent->right = NULL;
                }
            }
            else
            {
                tree->root = NULL;
            }
        }
        else if (aux->left == NULL || aux->right == NULL)
        {
            TreeNode * child;
            if (aux->left != NULL)
            {
                child = aux->left;
            }
            else
            {
                child = aux->right;
            }

            if (aux != tree->root)
            {
                if (parent->left == aux)
                {
                    parent->left = child;
                }
                else
                {
                    parent->right = child;
                }
            }
            else
            {
                tree->root = child;
            }
            child->parent = parent;
            free(aux);
        }
        else
        {
            TreeNode * successor = minimum(aux->right);
            void *succKey = successor->pair->key;
            void *succValue = successor->pair->value;
            removeNode(tree, successor);
            aux->pair->key = succKey;
            aux->pair->value = succValue;

        }
    }

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode * aux = tree->root;
    while (aux != NULL)
        {
            if (is_equal(tree,key, aux->pair->key))
            {
                tree->current = aux;
                return aux->pair;
            }
            else if (tree->lower_than(key,aux->pair->key))
            {
                aux = aux->left;
            }
            else
                aux = aux->right;
        }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    TreeNode * aux = tree->root;
    if (aux == NULL) return NULL;
    while (aux->left != NULL) aux = aux->left;
    tree->current = aux;
    return aux->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    TreeNode * aux = tree->root;
    if (tree->current == NULL) return NULL;
    if (tree->current->right != NULL)
    {
        tree->current = minimum(tree->current->right);
        return tree->current->pair;
    }
    else
    {
        while (aux != NULL)
            {
                if (tree->current->parent == NULL) return NULL;
                if (tree->current->parent->left == tree->current)
                {
                    tree->current = tree->current->parent;
                    return tree->current->pair;
                }
                else
                {
                    tree->current = tree->current->parent;
                    aux = aux->parent;
                }
            }
    }
    return NULL;
}
