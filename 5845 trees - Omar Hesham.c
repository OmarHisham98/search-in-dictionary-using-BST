#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node
{
    char data[100];
    struct Node *right;
    struct Node *left;
} Node;

Node *newNode(char word[])
{
    Node* newnode = (Node*)malloc(sizeof(Node));
    strcpy(newnode->data,word);
    newnode->left = newnode->right =  NULL;
    return newnode;
}

int max(int first,int second)
{
    if(first>second)
        return first;
    else
        return second;
}

int height(Node *root)
{
    if(root==NULL)
        return -1;
    else
        return 1 + max(height(root->left),height(root->right));
}

int size(Node *root)
{
    if(root==NULL)
        return 0;
    else
        return 1+size(root->left)+size(root->right);
}


Node *Insert(Node *BSTnode,char word[])
{
    if(BSTnode==NULL)
        BSTnode= newNode(word);
    else if(strcmp(word, BSTnode->data)>0)
    {
        BSTnode->right = Insert(BSTnode->right,word);
    }
    else if(strcmp(word, BSTnode->data)<0)
    {
        BSTnode->left = Insert(BSTnode->left,word);
    }
    return BSTnode;
}
Node *Parent(Node *wanted,Node *root)
{
    if(root!= NULL)
    {
        if((wanted==root->right) || (wanted==root->left))
            return root;
        else if(strcmp(wanted->data,root->data) > 0 )
            Parent(wanted->data,root->right);
        else if(strcmp(wanted->data,root->data) < 0)
            Parent(wanted->data,root->left);
    }
    else
    return NULL;
}

Node *Predecessor(Node *BSTroot,Node *wanted)
{
    Node *parent = Parent(wanted,BSTroot);
    Node *child = wanted;
    if(wanted->left != NULL)
    {
        Node *ptr = wanted->left;
        while(ptr->right)
            ptr = ptr->right;
        return ptr;
    }
    else if((wanted->left==NULL) && (Parent(wanted,BSTroot)->left==wanted))
    {
        while(parent->left==child)
        {
            child=parent;
            parent = Parent(parent,BSTroot);

        }
        return parent;
    }
    else
    {
        return Parent(wanted,BSTroot);
    }

}

Node *Successor(Node *BSTroot,Node *wanted)
{
    Node *parent = Parent(wanted,BSTroot);
    Node *child = wanted;
    if(wanted->right != NULL)
    {
        Node *ptr = wanted->right;
        while(ptr->left)
            ptr = ptr->left;
        return ptr;
    }
    else if((wanted->right==NULL) && (Parent(wanted,BSTroot)->right==wanted))
    {
        while(parent->right==child)
        {
            child=parent;
            parent = Parent(parent,BSTroot);

        }
        return parent;
    }
    else
    {
        return Parent(wanted,BSTroot);
    }
}

Node *search(char word[],Node *root)
{
    Node *BSTroot = root,*pred=NULL,*succ=NULL;
    if(root!= NULL)
    {
        if(strcmp(word,root->data) == 0)
        {
            return root;
        }
        else if(strcmp(word,root->data) > 0)
        {
            if(root->right!=NULL)
                search(word,root->right);
            else
                return root;
        }
        else if(strcmp(word,root->data) < 0)
        {
            if(root->left!=NULL)
                search(word,root->left);
            else
                return root;
        }
    }

    //pred = Predecessor(BSTroot,root);
    //succ = Successor(BSTroot,root);
    //printf("%s ?\n%s ?\n",pred->data,succ->data);

}

void BST()
{
    Node *root=NULL;
    char word[100];
    FILE *f;

    f = fopen("randomized.txt","r");
    if (f == NULL)
    {
        printf("error");
        exit(0);
    }
    while(!feof(f))
    {
        fscanf(f,"%s",word);
        root=Insert(root,word);
    }
    printf("%d\t%d\n",size(root),height(root));
    char ch[50];
    while(1)
    {
        printf("Enter the words you want to search for:\n");
        gets(ch);
        char *token;
        token = strtok(ch, " ");
        while( token != NULL ){
        Node *returned = search(token,root);
        if(strcmp(returned->data,token)==0)
        {
            printf("\n\nThe word %s is correct\n\n",token);
        }
        else
        {
            Node *pre = Predecessor(root,returned);
            Node *suc = Successor(root,returned);
            printf("\n\nIs this the word you need : %s\t%s\t%s\n\n",returned->data,pre->data,suc->data);
        }
        token = strtok(NULL, " ");
        }
     }
    fclose(f);
    //  printf("%d",search("lovd",root));
}


int main()

{
    BST();
    return 0;
}
