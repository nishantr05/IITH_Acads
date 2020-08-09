(*
 * ERROR program.  
 * The variable 'Num' is an object identifier (or variable) of type 'Int', but it starts with capital 'N'.
 * This is against the rule stated in the manual (Section 10.1, 2nd sentence) : "object identifiers begin with a lower case letter."
 * Results in compilation error.
 *)

class Main inherits IO {

  main() : Object {
    {
      out_string("Enter any number : \n");
      let Num : Int <- in_int() in
      {
        out_int(Num) ;
        out_string(" is the number you entered!\n") ;
      };
    }

  };
};