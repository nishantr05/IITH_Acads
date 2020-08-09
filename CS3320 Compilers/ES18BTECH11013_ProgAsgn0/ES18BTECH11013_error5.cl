(*
 * ERROR program.  
 * A 'zero width' space character is included in the "Hello,  World!!\n" string, which cool doesnt recognize.
 * Section 10.5, 1st sentence states : "White space consists of any sequence of the characters: blank (ascii 32), \n (newline, ascii 10),
  \f (form feed, ascii 12), \r (carriage return, ascii 13), \t (tab, ascii 9), \v (vertical tab, ascii 11)."
 * Results in compilation error.
 *)

class Main inherits IO {

  main(): Object {

    out_string("Hello,  World!!\n")
    ​
    -- A 'Zero Width Space', which is not present in the set of whitespace characters recognized by cool.
   };
};