(*
 *  A simple program which reads two numbers from the user,
 *  and prints which one is greater by comparing them.
 *)

class Main inherits IO {

  main() : Object {
    {
      out_string("Enter two numbers: \n");
      let  a : Int <- in_int(), b : Int <- in_int() in 
        if a <= b then 
        {
          out_int(b) ;
          out_string(" is the larger number \n") ;
        }
        else
        {
          out_int(a) ;
          out_string(" is the larger number \n") ;
        }
        fi; 
    }

  };
};