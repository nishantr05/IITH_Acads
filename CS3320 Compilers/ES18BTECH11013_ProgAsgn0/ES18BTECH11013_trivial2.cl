(*
 * A simple program which reads a number from the user,
 * and tests whether the number is even or odd.
 *)

class Main inherits IO {

  -- mod function to calculate the remainder when b divides a :
  -- remainder = dividend - divisor*quotient

  mod (a : Int , b : Int) : Int {

    a - b*(a/b) 
  };

  main() : Object {

    {
      out_string("Enter a number: \n");
      let  x : Int <- in_int() in 
        if mod(x,2) = 0 then 
        {
          out_int(x) ;
          out_string(" is an even number \n") ;
        }
        else
        {
          out_int(x) ;
          out_string(" is an odd number \n") ;
        }
        fi; 
    } 
  };
};