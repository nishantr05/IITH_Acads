(*
 *  A simple program to swap two numbers, WITHOUT using any extra space
 *)

class Main inherits IO {

  inp1 : Int;

  inp2 : Int;

  main() : Object {

    {
      out_string("Enter two numbers 'a' and 'b' :\n");
      inp1 <- in_int();   --Initially inp1 = a, inp2 = b
      inp2 <- in_int();
      inp1 <- inp1+inp2;  --Here inp1 = a+b
      inp2 <- inp1-inp2;  --Now inp2 = (a+b)-b = a (inp2 swapped)
      inp1 <- inp1-inp2;  --Now inp1 = (a+b)-a = b (inp1 swapped)
      out_string("After swapping the variables: \n");
      out_string("Value of 'a' = ");
      out_int(inp1);
      out_string("\nValue of 'b' = ");
      out_int(inp2);
      out_string("\n");
    }
  };
};
