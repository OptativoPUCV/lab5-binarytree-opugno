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

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) 
{
    TreeMap* map = (TreeMap*) malloc(sizeof(TreeMap));
    if (map == NULL)
    {
        return NULL;
    }
    map -> root = NULL;
    map -> current = NULL;
    map -> lower_than = lower_than;
    //new->lower_than = lower_than;
    return map;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) 
{
    TreeNode* newNode = createTreeNode(key, value);

    if (tree -> root == NULL)
    {
        tree -> root = newNode;
        tree -> current = newNode;
    }
    else
    {
        tree -> current = tree -> root;
    }

    while (tree -> current != NULL)
    {
        if (is_equal(tree,key, tree -> current -> pair -> key)) return;
        else if (tree -> lower_than(key, tree -> current -> pair -> key) == 1)
        {
            if (tree -> current -> left == NULL)
            {
                tree -> current -> left = newNode;
                newNode -> parent = tree -> current;
            }
            tree -> current = tree -> current -> left;
        }
        else
        {
            if (tree -> current -> right == NULL)
            {
                tree -> current -> right = newNode;
                newNode -> parent = tree -> current;
            }
            tree -> current = tree -> current -> right;
        }    
    }
}

TreeNode * minimum(TreeNode * x)
{
    while (x -> left != NULL)
    {
        x = x -> left;  
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) 
{
    //CASO SIN HIJOS
    if (node -> left == NULL && node -> right == NULL)
    {
        //cuando no es la raiz
        if (node -> parent != NULL) 
        {
            if (node == node -> parent -> left) node -> parent -> left = NULL;
            else node -> parent -> right = NULL;
        }
    }
    //CASO CON UN HIJO
    else if (node -> left == NULL || node -> right == NULL)
    {
        if (node -> parent != NULL)
        { 
            //es nulo a la izquierda, solo tiene un hijo a la derecha
            if (node -> left == NULL && node -> right != NULL)
            {
                if (node == node -> parent -> left)
                {
                    node -> parent -> left = node -> left;
                    node -> right -> parent = node -> parent;
                }
                else
                {
                    node -> parent -> right = node -> left;
                    node -> right -> parent = node -> parent;
                }
            }
            else
            {
                if (node == node->parent->left)
                {
                  node -> parent -> left = node -> left;
                  node -> left -> parent = node -> parent;
                }
                else
                {
                  node -> parent -> right = node -> left;
                  node -> left -> parent = node -> parent;
                }
            }
        }
    }
    //CASO CON DOS HIJOS
    else
    {
        TreeNode *minimo = minimum(node -> right);  //obtener el minimo del subarbol derecho
        node -> pair  -> key = minimo -> pair -> key;   //actualizar y cambiar los datos
        node -> pair -> value = minimo-> pair -> value;
        removeNode(tree, minimo);                      //eliminar el nodo
    }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}


Pair * searchTreeMap(TreeMap * tree, void* key) 
{
    tree -> current = tree -> root;

    while (tree -> current != NULL)
    {
        if (is_equal(tree, key, tree -> current -> pair -> key)) return tree -> current -> pair;
        else if (tree -> lower_than(key, tree -> current -> pair -> key) == 1) tree -> current = tree -> current -> left;
        else tree -> current = tree -> current -> right;        
    }
    
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) 
{
    TreeNode* node = tree -> root; 
    Pair* minimo = NULL;
    
    while (node != NULL)
    {
        minimo = node -> pair;
        node = node -> left;
    }
    return minimo;
}

Pair * nextTreeMap(TreeMap * tree) 
{
    TreeNode* aux = tree -> current;

    if (tree == NULL)
    {
        return NULL;
    }
        
    if (aux -> right != NULL)
    {
        aux = minimum(tree -> current -> right);
        tree -> current = aux;
        return aux -> pair;
    }
    else 
    {
        while (aux -> parent != NULL)
        {
            if (tree -> lower_than(tree -> current -> pair -> key, aux -> parent -> pair -> key) == 1)
            {
                tree -> current = aux -> parent;
                return aux -> pair;
            }
            else if ()
        }
    }
    
    return NULL;
}
