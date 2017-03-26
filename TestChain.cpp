#include <Chain.h>
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
  Chain<int> a, b; // Two empty Chains are created
	
  cout << a.Size() << ' ' << b.Size() << endl; // yields 0 0
	
  Chain<int> d{7}; // A chain containing 7 should be created 
  cout << d << endl; // Should just print [7]
	
  a.ReadChain(); // User enters a chain, for example [10 30 -1 2] 
  cout << a << endl; // Output should be what user entered
	
  b.ReadChain(); // Same for b.
  cout << b << endl;
	
  cout << "COPY CONSTRUCTOR" << endl;
  Chain<int> c{a}; // Calls copy constructor for c
  cout << c;
  cout << a << endl;
	
  cout << "COPY ASSIGNMENT OPERATOR" << endl;
  a = b; // Should call the copy assignment operator for a
  cout << a;
  cout << b << endl;
	
  cout << "MOVE CONSTRUCTOR" << endl;
  Chain<int> e = move(c); // Move constructor for e
  cout << e;
  cout << c << endl;
		
  cout << "MOVE ASSIGNMENT OEPRATOR" << endl;
  a = move(e); // Move assignment operator for a
  cout << a;
  cout << e;
  cout << endl;
	
  
	Chain<string> f, g;

  f.ReadChain(); // User provides input for Chain a.
  cout << f << endl;
	
  g.ReadChain(); // User provides input for Chain b.
  cout << g << endl;
	
  cout << f + g << endl; // Concatenates the two Chains.

  Chain<string> h = f + g;
  cout << h << endl;
	
  cout << h + "hi_there" << endl; // Adds an element to the end.
	
  cout << f[2] << endl << endl; // Prints the 3rd element.
	
  g[1] = "b_string"; // Should change the 2nd element to "b_string"
  cout << g;
  g[0] = "a_sting";
  cout << g << endl;
	
  return 0;
}

