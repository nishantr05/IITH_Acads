#include <iostream>
#include <cstdio>
using namespace std ;
  
struct node 
{ 
    int key ;
    node* left ;
    node* right ;
    node* parent ; 
}; 
 
node* root = NULL ;

node* search (int val)
{
    node* x = root ;
    while (x != NULL)
    {
        if (val == (x -> key))
            return x ;

        else if (val > (x -> key))
            x = x -> right ;

        else 
            x = x -> left ;
    }
    //If the node containing the key is not found, we return a NULL pointer.
    if (x == NULL)
        return x ;
}

node* Max(int val)
{
    node* x = search(val) ;
    while ((x -> right)!= NULL)
        x = x -> right ;

    return x ;
}

node* Min(int val)
{
    node* x = search(val) ;
    while ((x -> left)!= NULL)
        x = x -> left ;

    return x ;
}

node* successor(int val)
{
    node* x = search(val) ;
    if ((x -> right) != NULL)
        return Min((x -> right)-> key) ;

    node* y = x -> parent ;
    while (x == (y -> right) && y != NULL ) //Keep traversing up the tree, TILL x is a left child of y .
    {
        x = y ;
        y = y -> parent ;
    }

    return y ;
}

node* predecessor(int val)
{
    node* x = search(val) ;
    if ((x -> left) != NULL)
        return Max((x -> left)-> key) ;

    node* y = x -> parent ;
    while (x == (y -> left) && y != NULL ) //Keep traversing up the tree, TILL x is a right child of y .
    {
        x = y ;
        y = y -> parent ;
    }

    return y ;
}

node* LCA (int val1, int val2)
{
    node* x = root ;
    while(x != NULL)
    {
        if (val1 > (x -> key) && val2 > (x -> key))
            x = x -> right ;

        else if (val1 < (x -> key) && val2 < (x -> key))
            x = x -> left ;

        //The first instance wherein the key value of x lies between val1 and val2, node x is the LCA.
        //Also, we assume a node is allowed to be a ancestor of itself.
        else
            break ; 
    }
    return x ;
}

void insert(int val) 
{ 
    //Allocating memory for the new node
    node* new_node = new node ;
    new_node -> key = val ; 
    new_node -> left = new_node -> right = new_node -> parent = NULL ; 
    //The first node which is inserted is the root node
    if (root == NULL)
    {
      root = new_node ;
      return ;
    }
    //Inserting the node at the correct position
    node* y = NULL ;
    node* x = root ;
    while(x != NULL)
    {
        y = x ;
        if (val > (x -> key))
            x = x -> right ;
        else
            x = x -> left ;
    }
    if (val > (y -> key))
        y -> right = new_node ;
    else
        y -> left = new_node ;

    new_node -> parent = y ;
     
} 
  
// A utility function to do inorder traversal of BST 
void inorder(node* root) 
{ 
    if (root != NULL) 
    { 
        inorder(root->left); 
        printf("%d \n", root->key); 
        inorder(root->right); 
    } 
} 

int main()
{
    int T, N, value, val2 ;
    char ch = ' ';
    cout << "Enter list of keys (enter new-line to terminate) : " << endl ;
    // Inputting the nodes to be inserted in the BST
    while(ch != '\n')
    {
        cin >> value ;
        insert(value) ;
        ch = getchar() ;
    }
    cout << "Functionality input (enter two successive new line characters to terminate) :" << endl ;
    while(true)
    {
        ch = getchar() ;
        if (ch == '\n')
            break ;
        switch(ch)
        {
            case 'M' :
                cin >> value ;
                cout << Min(value) -> key << " " << Max(value) -> key << endl ;
                break ;

            case 'P' :
                cin >> value ;
                if (predecessor(value) != NULL )
                    cout << (predecessor(value) -> key) << endl ;
                else
                    cout << "NO predecessor exists" << endl ;
                break ;

            case 'S' :
                cin >> value ;
                if (successor(value) != NULL )
                    cout << (successor(value) -> key) << endl ;
                else
                    cout << "NO successor exists" << endl ;
                break ;

            case 'C' :
                cin >> value >> val2 ;
                cout << LCA(value, val2) -> key << endl ;
                break ;
        } 
        getchar() ;
    }
    return 0;
}