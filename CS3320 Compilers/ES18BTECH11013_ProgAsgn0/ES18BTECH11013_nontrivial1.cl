(*
 * This program implements a linked list data structure using concept of 'cons cells'.
 * Implementation details => the list structure is either:
  -> An empty list , that is object of 'void' type, or 
  -> A 'cons pair' whose 'car' is the first element and whose 'cdr' is a list containing rest of the elements
 * Note : 'cons x y' can be looked at as a pair, with the left half (or first element) called 'car' and right half called 'cdr'.
 *
 * Other functionalities :
  -> 'get_min(l : Cons_list)' method to find the least element in a list.
  -> 'append(l1 : Cons_list, l2 : Cons_list) method, returns a new list with 'l2' appended to the tail of 'l1'.
 *) 
 

(*
 * Below is the implementation of class 'Cons_list'
 * The methods used for implementation are :
 *
  -> isempty() : Bool           Returns true if the list is empty, false otherwise.
  -> head()  : Int              Returns the integer at the head of list. (If list is empty, execution aborts.)    
  -> tail() : Cons_list         Returns the remainder of the list (i.e from second element onwards)      
  -> cons(i : Int) : Cons_list  Returns a new list containing i as the frist element, and the previous elements following it.
 * 
 * It has three attributes 'car', 'cdr' and 'non_empty'.  
 *)
 
class Cons_list {

  car : Int;          -- The 1st element (or haed) in this list cell

  cdr : Cons_list;    -- The remaining part of the list (the tail)

  non_empty : Bool;   -- Boolean flag to check if the list is empty or not

  isempty() : Bool { not non_empty };

  head() : Int {

    if(isempty()) then
      {
        abort();
        0;
      }
    else
      car
    fi
  };

  tail() : Cons_list {

    if(isempty()) then
      {
        abort();
        self;
      }
    else
      cdr
    fi
  };

  cons(i : Int) : Cons_list {

    {
      cdr <- self.copy();  --Copies the calling object to cdr  
      car <- i;
      non_empty <- true;
      self;
    }
  };
};

(*
 * The Main class uses the 'Cons_list' class, to create a list of elements entered by the the user.
 * It also finds minimum value of the elements using get_min() function
 *)

class Main inherits IO {

  list_C : Cons_list <- new Cons_list;     -- list created using calls to 'cons' function
  
  list_A : Cons_list <- new Cons_list;   -- list created using the append function
  
  -- Recursive method 'get_min' to obtain the minimum value from the list :

  get_min(l : Cons_list) : Int {
  
    if (l.tail()).isempty() then  -- Base case : We're at the last element of the list, so simply return the head.
      l.head()
    else 
      {
        let temp : Int <- l.head(), min_rest : Int <- get_min(l.tail()) in
        {
          if (temp < min_rest) then 
            temp
          else
            min_rest
          fi;
        };
      }
    fi
  };

  (*
   * The append method is useful if you want to "Retain the order" in which elements are entered by the user.
   * If the 'cons' method is used to repeatedly add elements, the final list will be in 'reversed order'    
   * i.e, the head will be the last element entered and the tail will be the very first element entered.
   * Thus, append method is useful if the ordering is to be maintained.
   *)

  -- Simpele recursive method 'append' to join two lists :

  append(l1 : Cons_list, l2 : Cons_list) : Cons_list {

    if (l1.isempty()) then 
      l2
    else
      let temp : Cons_list <- append(l1.tail(),l2) in
        temp.cons(l1.head())
    fi
  };

  -- This recursive method is used to print the list :

  display_list(l : Cons_list) : Object {

    if l.isempty() then
     out_string("\n")
    else
      {
        out_int(l.head());
        out_string(" ");
        display_list(l.tail());
      }
    fi
  };

  main() : Object {

    let inp : Int, list_len : Int in
    {
      out_string("Enter the number of elements to be present in the list : ");
      list_len <- in_int();
      out_string("Enter the elements : \n");
      inp <- in_int();
      list_C <- list_C.cons(inp);
      list_A <- append(list_C,list_A);
      while (1 < list_len) loop
      {
        inp <- in_int();
        list_C <- list_C.cons(inp);
        list_A <- append(list_A, (new Cons_list).cons(inp));
        list_len <- list_len -1 ;
      }
      pool ;
      out_string("The 'cons' style list is :\n");
      display_list(list_C);
      out_string("The list created using 'append' functionality is :\n");
      display_list(list_A);
      out_string("The least element in the list is :\n");
      out_int(get_min(list_C));
      out_string("\n");
    }
   };
};



 