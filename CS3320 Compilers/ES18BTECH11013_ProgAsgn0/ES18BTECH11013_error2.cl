(*
 * ERROR program.  
 * In this program we try printing a string which starts on one line and goes on to the next line. 
 * Here the newline character (\n) in NOT escaped.
 * This is against the rule stated in the manual (Section 10.2, 7th line) : "A non-escaped newline character may not appear in a string"
 * Results in compilation error.
 *)

class Main inherits IO {

  main() : Object {

    out_string("Is this 
    a valid cool string?") 

    --correct usage, with escaped newline character :
    --out_string("Is this \
    --  a valid cool string?") 
      
  };
};