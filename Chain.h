#ifndef CSCI335_HOMEWORK1_CHAIN_
#define CSCI335_HOMEWORK1_CHAIN_
#include <cstddef>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// THE CHAIN CLASS

// Chain has two constructos: one for a declaration with no parameters and another for one parameter
// The user cannot declare a Chain with more than one parameter - must declare and add elemetns after

// Class includes five method functions:
// 	ReadChain() to read in user input and add it to the chain
// 	Size() which returns the size of the chain
//	Resize() to resize the dynamic array if the user inpputs more elements than it is currenlty capable of holding
//	AddObject() which is called internally to add an element to the chain
//	Print() to print out the contents of the chain

//	The output << , plus + , and bracket [] operators are all overloaded


template<typename Object>
class Chain {
 public:
	// Constructors for declarations with no parameters or one parameter, respecctively
	
	// User may not delcare a chain with more than one element
	// Must declare the chain and enter its elements separatley after doing so
	// Contents for chain inputted by user will then be read and added with ReadChain() function
	Chain() {
		arr_size_ = 25;
		array_ = new Object[arr_size_];
		size_ = 0;
	}
	
	Chain(Object x) {
		arr_size_ = 25;
		array_ = new Object[arr_size_];
		array_[0] = x;
		size_ = 1;
	}	
	
	// Destructor
	~Chain() {
		delete[] array_;
	}
	
	// Copy constructor
	Chain(const Chain &rhs) {
		size_ = rhs.size_;
		arr_size_ = rhs.arr_size_;
		array_ = new Object[arr_size_];
		for(int i = 0; i < size_; ++i)
			array_[i] = rhs.array_[i];
	}
	
	// Copy assignment operator
	Chain& operator=(const Chain &rhs) {
		if(this != &rhs) {
			size_ = rhs.size_;
			arr_size_ = rhs.arr_size_;
			for(int i = 0; i < size_; ++ i)
				array_[i] = rhs.array_[i];
		}
		
		return *this;
	}
	
	// Move constructor
	Chain(Chain &&rhs) : size_{rhs.size_}, arr_size_{rhs.arr_size_}, array_{move(rhs.array_)} {
		rhs.size_ = 0;
		rhs.arr_size_ = 0;
		rhs.array_ = nullptr;
	}
	
	// Move assignment operator
	Chain& operator=(Chain &&rhs) {
		swap(array_, rhs.array_);
		swap(size_, rhs.size_);
		swap(arr_size_, rhs.arr_size_);
		return *this;
	}
	
	// Takes user input and adds it to the chain
	void ReadChain() {
		string input;
		getline(cin, input);
		
		// checks that the input is formatted properly (surrounded by brackets)
		while (input[0] != '[' || input[input.size()-1] != ']') {
			cout << "Plese enter the contents of the chain inside of brackets, i.e. [1 2 3 4]" << endl;
			getline(cin, input);
		}
		
		// obtain substring without brackets so they are not added to the chain
		input = input.substr(1, input.size()-2);
		
		istringstream iss(input);
		Object x;
		
		while(iss >> x)
			AddObject(x);
	}
	
	int Size() {
		return size_;
	}
	
	// Used to resize dynamic array if user inputs more elements than it is capable of holding
	void Resize(size_t new_size) {
		Object *prev_array = array_;
		size_t prev_size = size_;
		
		array_ = new Object[new_size];
		for(int i = 0; i < prev_size; ++i)
			array_[i] = prev_array[i];
		
		arr_size_ = new_size;
		if(prev_array)
			delete[] prev_array;
	}
	
	// Adds object to the chain
	// Checks that array is large enough to hold another element, calls Resize() method if it is not
	void AddObject(Object x) {
		if(size_ < arr_size_) {
			array_[size_] = x;
			size_++;
		}
		
		else {
			Resize(arr_size_ * 2);
			array_[size_] = x;
			size_++;
		}
	}
	
	void print(ostream & out) const {
		for(int i = 0; i < size_; ++i) {
			if(i != size_-1)
				out << array_[i] << ' ';
			else
				out << array_[i];
		}
	}
	
	// Overload + operator to concatenate chains
	Chain operator+(const Chain &rhs) const {
		Chain result;
		
		// add contents of the two chains to the new chain result
		for(int i = 0; i < size_; ++i)
			result.AddObject(array_[i]);
		for(int i = 0; i < rhs.size_; ++i)
			result.AddObject(rhs[i]);
		
		return result;		
	}
	
	// Overload + operator to allow adding an element to the end of a chain
	Chain& operator+(Object x) {
		AddObject(x);
		return *this;
	}
	
	// Overload [] operator
	// Prints "OUT OF RANGE" if the index is out of the chain's range and aborts
	Object& operator[](int i) const {
		if(i < 0 || i > size_-1) {
			cout << "OUT OF RANGE" << endl;
			abort();
		}
		
		else
			return array_[i];
	}
	
	// size_t size_ stores the number of elements in the chain
	// size_t arr_size_ stores the capacity (actual size) of the dynamic array
	// Object *array_ is a pointer to a dynamic array of objects that stores the elements in the chain
 private:
	 size_t size_;
	 size_t arr_size_;
	 Object *array_;
 };
 
 // Overload ouptut operator
 template<typename Object>
 ostream& operator<< (ostream& out, const Chain<Object>& rhs) {
	 cout << '[';
	 rhs.print(out);
	 cout << ']' << endl;
	 return out;
 }

#endif // CSCI_335_HOMEWORK1_CHAIN_


