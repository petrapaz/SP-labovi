/*LAB 9: 9. Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u čvorove binarnog stabla.
a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za
sve element zadanog niza brojeva stvori stablo kao na slici Slika 1. Funkcije vraća
pokazivač na korijen stabla.
                2
            /       \
           5         1
         /  \      /   \
        7    4   NULL  NULL
       /       \
      8         2
     /  \      /  \
   11     7   3   NULL
   /\     /\    /\
NULL NULL . .   . .

b) Napisati funkciju replace koja će svaki element stabla zamijeniti sumom elemenata u
njegovom lijevom i desnom podstablu (tj. sumom svih potomaka prije zamjene
vrijednosti u tim potomcima). Npr. stablo sa slike Slika 1 transformirat će se u stablo na
slici Slika 2.
c) Prepraviti program na način da umjesto predefiniranog cjelobrojnog polja korištenjem
funkcije rand() generira slučajne brojeve u rasponu <10, 90>. Također, potrebno je
upisati u datoteku sve brojeve u inorder prolasku nakon korištenja funkcije iz a), zatim b)
dijela zadatka.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996) //fopen i fopen_s javljali warnings ... 

typedef struct node* Position;
struct node
{
    int data;
    Position left;
    Position right;
};

// Convert a given tree to a tree where every node contains sum of values of
// nodes in left and right subtrees in the original tree
int toSumTree(struct node* node)
{
    if (node == NULL)
        return 0;
    int lchild = node->left ? node->left->data : 0;
    int rchild = node->right ? node->right->data : 0;
    node->data = lchild + rchild + toSumTree(node->left) + toSumTree(node->right);
    return node->data;
}

void printInorder(struct node* node)
{
    if (node == NULL)
        return;
    printInorder(node->left);
    printf("%d ", node->data);
    printInorder(node->right);
}

struct node* newNode(int data)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

void printTreeToFile(struct node* r, FILE* fp)
{
    if (r != NULL) {
        //store current node and recur for its children
        printTreeToFile(r->left, fp);
        fprintf(fp, "%d ", r->data);
        printTreeToFile(r->right, fp);
    }
}

int main()
{
    printf("\tLABORATORIJSKA VJEZBA 9:");
    struct node* root = NULL;
    
    root = newNode(2);
    root->left = newNode(5);
    root->right = newNode(1);
    root->left->left = newNode(7);
    root->left->right = newNode(4);
    root->left->left->left = newNode(8);
    root->left->right->right = newNode(2);
    root->left->left->left->left = newNode(11);
    root->left->left->left->right = newNode(7);
    root->left->right->right->left = newNode(3);
    
    /*
    //nodes are random generated numbers from 10 to 90
    root = newNode(rand()%10+90);
    root->left = newNode(rand()%10+90);
    root->right = newNode(rand()%10+90);
    root->left->left = newNode(rand()%10+90);
    root->left->right = newNode(rand()%10+90);
    root->left->left->left = newNode(rand()%10+90);
    root->left->right->right = newNode(rand()%10+90);
    root->left->left->left->left = newNode(rand()%10+90);
    root->left->left->left->right = newNode(rand()%10+90);
    root->left->right->right->left = newNode(rand()%10+90);
    */

    //char input[20];
    //puts("\nName of text file you want to save inorder of tree before and after changes:\n");
    //scanf_s("%s", input);

    FILE* fp;
    fp = fopen("tree.txt", "w");
    if (fp == NULL)
    {
        puts("Could not open file");
        return 0;
    }
    
    printf("\nInorder traversal of tree before changes:\n ");
    fprintf(fp, "Inorder traversal before changes:\n");
    printInorder(root);
    printTreeToFile(root, fp); //print unchanged tree to file

    fprintf(fp, "\n\n");
    fprintf(fp, "Inorder traversal after summing nodes:\n");
    toSumTree(root); //summing nodes
    printTreeToFile(root, fp);  //print tree with summed nodes to file
    printf("\n\nInorder traversal of the resultant tree after summing nodes is: \n");
    printInorder(root);

    fclose(fp);
    return 0;
}




