/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  zcliang@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission: Winter 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    - jj2park -  test cases
 *****************************************/

#ifndef DYNAMIC_STACK_AS_ARRAY_H
#define DYNAMIC_STACK_AS_ARRAY_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "Exception.h"

class Dynamic_range_stack {
	private:
		int entry_count;
		int max_count;
		int min_count;
		int initial_capacity;
		int current_capacity;

		int *stack_array;
		int *maximum_array;
		int *minimum_array;

		// You may wish to include a number of helper functions
		// in order to abstract out some operations


	public:
		Dynamic_range_stack( int = 10 );
		Dynamic_range_stack( Dynamic_range_stack const & );
		~Dynamic_range_stack();

		int top() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		int maximum() const;
		int minimum() const;
		
		
		void push( int const & );
		int pop();
		void clear();


	// Friends


	friend std::ostream &operator<<( std::ostream &, Dynamic_range_stack const & );
};

//Constructor
Dynamic_range_stack::Dynamic_range_stack( int n ):

//Initializing values as the ones in the brackets
entry_count( 0 ),														//entry_count = 0;
min_count( 0 ),															//min_count = 0;
max_count( 0 ),															//max_count = 0;
initial_capacity( std::max( 1, n ) ),									//initial_capacity = n (if n > 1) else 1
current_capacity( initial_capacity ),									//current_capacity = initial_capacity (the size of the array)
stack_array( new int[current_capacity] ),								//create a new int array with the specified capacity
maximum_array( new int[current_capacity] ),
minimum_array( new int[current_capacity] ) {
	// empty constructor
}

//Deconstructor
Dynamic_range_stack::~Dynamic_range_stack() {
	delete[] stack_array;
	delete[] maximum_array;
	delete[] minimum_array;
}

int Dynamic_range_stack::top() const {
	if(Dynamic_range_stack::empty()){
		throw underflow();
	}
	return stack_array[entry_count - 1];
}

int Dynamic_range_stack::maximum() const {
	if(Dynamic_range_stack::empty()){
		throw underflow();
	}
	return maximum_array[max_count - 1];
}

int Dynamic_range_stack::minimum() const {
	if(Dynamic_range_stack::empty()) {
		throw underflow();
	}
	return minimum_array[min_count - 1];
}

int Dynamic_range_stack::size() const {
	return entry_count;
}

bool Dynamic_range_stack::empty() const {
	return (entry_count <= 0);
}

int Dynamic_range_stack::capacity() const {
	return current_capacity;
}



void Dynamic_range_stack::push( int const &obj ) {
	//There is enough room in the current array
	if(entry_count == 0){
		stack_array[0] = obj;
		maximum_array[0] = obj;
		minimum_array[0] = obj;
			
		entry_count++;
		max_count++;
		min_count++;
		return;
	}
	
	if(entry_count >= current_capacity){		
		int *temp_stack_array = new int[current_capacity * 2];
		int *temp_maximum_array = new int[current_capacity * 2];
		int *temp_minimum_array = new int[current_capacity * 2];
		
		current_capacity *= 2;

		for(int i = 0; i < entry_count - 1; i++){
			temp_stack_array[i] = stack_array[i];
			temp_maximum_array[i] = maximum_array[i];
			temp_minimum_array[i] = minimum_array[i];
		}

		delete[] stack_array;
		delete[] maximum_array;
		delete[] minimum_array;
		
		stack_array = temp_stack_array;
		maximum_array = temp_maximum_array;
		minimum_array = temp_minimum_array;
	}

	stack_array[entry_count] = obj;
	entry_count++;
	
	if(obj > maximum_array[max_count - 1]){
		maximum_array[max_count] = obj;
		max_count++;
	}
	if(obj < minimum_array[min_count - 1]){
		minimum_array[min_count] = obj;
		min_count++;
	}
	return;
}

int Dynamic_range_stack::pop() {
	if(empty()){
		throw underflow();
	}
	
	if(stack_array[entry_count - 1] == maximum_array[max_count - 1]){
		max_count--;
	}
	if(stack_array[entry_count - 1] == minimum_array[min_count - 1]){
		min_count--;
	}

	entry_count--;
	
	return stack_array[entry_count];
}

void Dynamic_range_stack::clear() {
	delete[] stack_array;
	delete[] maximum_array;
	delete[] minimum_array;
	
	current_capacity = initial_capacity;
	entry_count = 0;
	max_count = 0;
	min_count = 0;
		
	stack_array = new int[initial_capacity];
	maximum_array = new int[initial_capacity];
	minimum_array = new int[initial_capacity];

	return;
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Dynamic_range_stack const &stack ) {
	// Print out your stack
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
