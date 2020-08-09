(*
 * This is a proram to print the Nth Ugly Number.
 * Ugly numbers are positive numbers whose ONLY prime factors are 2,3 or 5.
 * By convention, '1' is considered as the first ugly number.
 *
 * The sequence 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, … shows the first 11 ugly numbers
 * Thus, for N = 10, the 10th Ugly number is '12'. The 4th Ugly number (N = 4) is '4'.
 * 
 *)

class Main inherits IO {

  -- Simple function which returns a%b.

  mod (a : Int , b : Int) : Int {

    a - b*(a/b) 
  };

  -- This method divides 'a' by the greatest possible power of 'b'.
  -- After a call to this method, 'b' is no longer a factor of 'a'.

  remeove_factor(a : Int, b: Int) : Int {

    {
      while (mod(a,b) = 0) loop
        a <- a/b
      pool;
      a;
    }
  };

  --Checks of 'x' is an Ugly number or not

  isUgly(x : Int) : Bool {

    {
      -- 'x' should have only 2,3 or 5 as its factors

      x <- remeove_factor(x,2);
      x <- remeove_factor(x,3);
      x <- remeove_factor(x,5);
      if (x = 1) then
        true
      else
        false
      fi;
    }
  };

  -- returns the Nth Ugly, by checking if every number is Ugly, starting from 1.

  nth_Ugly_Num(n : Int) : Int {

    let i : Int <- 1, count : Int <- 1 in 
    {
      while (count < n) loop
        {
          i <- i+1;
          if (isUgly(i)) then
            count <- count+1
          else
            0       -- do nothing
          fi;
        }
      pool;

      i;
    }
  };

  inp_var : Int;

  main() : Object {

    {
      out_string("Enter a positive number: ");
      inp_var <- in_int();
      out_string("The ");
      out_int(inp_var);
      out_string("th Ugly number is ");
      out_int(nth_Ugly_Num(inp_var));
      out_string("\n");
    } 
  };
};

