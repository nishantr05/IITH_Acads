(*
 *  This program calculates the length of string WITHOUT using the existing 'length()' function.
 *  The other functions of the String class, 'concat' and 'substr' are used.
 *)

class Main inherits IO {

  strlen(s : String) : Int {

    -- 'temp' is a String object, which ends with '`', to mark the end of the string.

    let temp : String <- s.concat("`"), i : Int <- 0 in 
    {
      while (not temp.substr(i,1) = "`") loop
        i <- i+1
      pool;

      i;
    }
  };

  main() : Object {

    let len : Int in
    {
      out_string("Enter any string :\n") ;
      len <- strlen(in_string());
      out_string("The length of the string is : ");
      out_int(len);
      out_string("\n");
    }
  };
};