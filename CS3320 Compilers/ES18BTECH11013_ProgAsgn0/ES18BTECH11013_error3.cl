(*
 * ERROR program.  
 * This program throws a compilation error, because the comment is enclosed in '/*...*/' instead of encloing in (*...*)
 * This is against the rule stated in the manual (Section 10.3, 3rd sentence) : "Comments may also be written by enclosing text in (∗ . . . ∗)."
 *)

class Main inherits IO {

  main(): Object  {

    let dummy : Int <- 0 in
    {
      /* 'dummy' value incremented by one. INVALID comment syntax.*/
      dummy <- dummy+1;   

      (* 'dummy' value printed to screen, VALID comment syntax. *)
      out_int(dummy) ;
    }
      
  };
};