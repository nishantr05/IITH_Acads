#include <iostream>
#include <string>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cctype>
using namespace std;

//Node for a singly linked list
struct node
{
    char value ;
    node* next ; 
};

node* head_ptr = NULL ;
node* tail_ptr = NULL ;

struct info
{
    char ch ;       // Stores the alphabet (in uppercase)
    int count ;     //to keep count of the number of occurences of a given character
    int idx ;       //stores the index of the first occurence of a character in the string
    int printed ;   //Flag variable to check if the character and its number of occurences is printed or not.

} A[26] ;

bool compare(info a, info b) 
{ 
    if (a.count != b.count ) 
        return a.count> b.count; 
    else
        return (a.idx < b.idx); //If number of occurences of an alphabet is same, then alphabet which comes first in orginal string is preferred
} 

//Inserting the character values into the linked list
void insert(char val) 
{
    node* new_node = new node;
    new_node -> value = toupper(val);       
    new_node -> next = NULL ; // new node is inserted in the end so will have next link as null.
    if (head_ptr == NULL)
    {
      head_ptr = new_node ; 
      tail_ptr = new_node ;
      return ;
    }
    tail_ptr -> next = new_node ;
    tail_ptr = new_node ;
}

//Traversing the linked llist and printing the character frequencies.
void traverse()
{
    int pos = 0 ;
    for (int i = 0; i < 26; ++i)
    {
        A[i].ch = i+65 ;        //A[0] stores the char 'A', A[1] stores 'B' and so on.
        A[i].count = 0 ;
        A[i].idx = -1 ;
    }    
    //Updating the count of number of occurences of the character value
    node* temp = head_ptr ;
    while(temp != NULL)
    {   
        if (A[(temp -> value)%65].count == 0)
            A[(temp -> value)%65].idx = pos ;

        A[(temp -> value)%65].count += 1 ; 
        temp = temp -> next ;
        pos++ ;
    } 
    //Printing the count of each character
    temp = head_ptr ;
    while(temp != NULL)
    {   
        if (A[(temp -> value)%65].printed == 0)
        {
            cout << A[(temp -> value)%65].ch << " " << A[(temp -> value)%65].count << " " ;
            A[(temp -> value)%65].printed = 1 ;
        }
        temp = temp -> next ;
    }  
    cout << endl ; 

}

void Sort()
{
    // Sorting using the in-built 'sort' function (implemented using the quicksort algo, with O(nlogn) runtime).
    // Takes an additional 'compare' function as argument
    sort(A, A+26, compare) ;
    for (int i = 0; i < 26; ++i)
    {
        if (A[i].count== 0)
            break ;
        cout << A[i].ch ;
    }
    cout << endl ;
}

//Removes multpile occurences of a character occuring more than 'count_max' times consecutively
void remove(int count_max)
{
    int occurences = 1 ;
    node* current = head_ptr -> next ;
    node* prev = head_ptr ;
    while(current != NULL)
    {
        if (current -> value == prev -> value)
            occurences++ ;
        else
            occurences = 1 ;

        if (occurences > count_max)
        {
            prev -> next = current -> next ;
            delete current ;
            current = prev -> next ;
            //resetting the tail pointer if the last element is deleted
            if (current == NULL)
                tail_ptr = prev ;
        }
        else
        {
            prev = current ;
            current = current -> next ;
        }
    
    }
    node* temp = head_ptr ;
    while(temp != NULL)
    {
        cout << temp -> value ;
        temp = temp -> next ;
    }
    cout << endl ;
}

int main()
{
    int x ; 
    char ch, c; 
    string ign ;
    //Taking user INPUT starts here 
    cout << "Enter the string :" << endl ;
    while ((ch = getchar())!= '\n')
        insert(ch) ;
    cout << "Functionality input (enter two successive new line characters to terminate) :" << endl ;
    while(true)
    {
        ch = getchar() ;
        if (ch == '\n')
            break ;
        switch(ch)
        {
            //Functionality input 'Store' and 'Sort'
            case 'S' :
            case 's' :
                c = getchar() ;
                cin >> ign ;
                if(c == 't')
                    cout << head_ptr -> value << " " << tail_ptr -> value << endl ;
                else
                    Sort() ;
                break ;
            //Functionality input 'Print'
            case 'P' :
            case 'p' :
                cin >> ign ;
                traverse() ;
                break ;
            //Functionality input 'Remove'
            case 'R' :
            case 'r' :
                cin >> ign ;
                cin >> x ;
                remove(x) ;
                break ;
        } 
        getchar() ;
    }
    return 0 ; 
}