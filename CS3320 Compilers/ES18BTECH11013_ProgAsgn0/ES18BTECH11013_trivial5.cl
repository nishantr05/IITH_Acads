(*
 * This is a proram to find the largest prime factor of a given (positive) number N.
 * Examples : 
  -> given N = 15, it's largest prime factor is 5.
  -> given N = 14, it's largest prime factor is 7.
 * 
 *)

class Main inherits IO {

  -- Simple function which returns a%b.

  mod (a : Int , b : Int) : Int {

    a - b*(a/b) 
  };

  -- This method goes through all the prime factors (less than sqrt(n)),
  -- n is divided by the largest possible power of each factor at every iteration

  maxPrimeFactor(n : Int) : Int {

    let i : Int <- 2, maxPrime : Int <- 1 in 
    {
      while (i*i <= n) loop
      {
        while(mod(n,i) = 0) loop
        {
          maxPrime <- i;
          n <- n/i;
        }
        pool;
        i <- i+1 ;
      }
      pool;

      if (2 <= n) then n else maxPrime fi;   -- Handles the case when 'n' is a prime.
    }
  };

  inp_var : Int;

  main() : Object {

    {
      out_string("Enter a positive number: ");
      inp_var <- in_int();
      out_string("It's largest prime factor is : ");
      out_int(maxPrimeFactor(inp_var));
      out_string("\n");
    } 
  };
};

