(*
 * ERROR program.  
 * EXCEPT for the constants true and false, keywords are case insensitive. Here 'True' is incorrectly used as it starts with capital 'T'.
 * This is against the rule stated in the manual (Section 10.4, last sentence) : "To conform to the rules for other objects, the first letter 
   of 'true' and 'false' must be lowercase; the trailing letters may be upper or lower case."
 *)

class Main inherits IO {

   main(): Object {

      --Invalid usage of keyword 'true'. Should start with lower case 't'.
      if (True) then 
        out_string("Will always be displayed!\n")
      else
        out_string("Will never be displayed!\n")
      fi
   };
};