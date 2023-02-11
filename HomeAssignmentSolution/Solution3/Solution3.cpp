// Question 3 - implementation
// 
//	without using STL containers implement the following:
//	A class for a dynamic int array, let's call it "CVectorInt" that -
//  1. doubles its size automatically when its full (allocates twice the size and moves the data),
//	2. halves its size when it is half empty (allocates half of the size and moves the data)
//  3. can be told the initial capacity (num of ints) in a constructor
//  4. have a method called "reserve" - that Requests that the vector capacity be at least enough to contain n elements.
//     If n is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to n
//  5. have a method called "capacity" - that returns the number of int elements allocated
//  6. have a method called "size" - that returns the number of elements actually inserted
//  7. have a method called "empty" - that returns true/false according to amount of actual elements in the data
//  8. have a method called "clear" - that frees all the data and resets the size
//  9. have a method called "push_back" - that adds an int elements at the end
// 10. have a method called "pop_back" - that removes an int elements at the end and return it
// 11. have a method called "remove"  - that removes an int elements at specific index
// 12. have an interface to access the data at a specific index using subscript "[]"
//
// make sure to handle edge cases such as memory issues, size issues etc.


#include <iostream>
#include <stdexcept>


class CVectorInt
{
	// TODO: your code here
public:
	CVectorInt(int len);   // constructor
	~CVectorInt();  // destructor 
	void reserve(int num);
	int capacity();
	int size();
	bool empty();
	void clear();
	void push_back(int to_add);
	int pop_back();
	int remove(int index);
	int& operator[](int index);
protected:
private:
	int* array;
	int actual_size;
	int total_capacity;
	void double_array();
	void half_array();

};

CVectorInt::CVectorInt(int len) {
	array = new int[len];
	for (int i = 0; i < len; i++)
		array[i] = 0;
	actual_size = 0;
	total_capacity = len;

}

CVectorInt::~CVectorInt() {
	delete[] array;
}

// doubles its size automatically when its full (allocates twice the size and moves the data)
void CVectorInt::double_array() {
	int* temp_array;
	total_capacity = total_capacity * 2;
	temp_array = new int[total_capacity];
	for (int i = 0; i < actual_size; i++) {
		temp_array[i] = array[i];
	}
	for (int j = actual_size; j < total_capacity; j++) {
		temp_array[j] = 0;
	}
	delete[] array;
	array = temp_array;
}

//halves its size when it is half empty (allocates half of the size and moves the data)
void CVectorInt::half_array() {
	int* temp_array;
	total_capacity = total_capacity/2;
	temp_array = new int[total_capacity];
	for (int i = 0; i < actual_size; i++) {
		temp_array[i] = array[i];
	}
	for (int j = actual_size; j < total_capacity; j++) {
		temp_array[j] = 0;
	}
	delete[] array;
	array = temp_array;
}

// Requests that the vector capacity be at least enough to contain n elements.
void CVectorInt::reserve(int num) {
	while (total_capacity < num) {
		double_array();
	}
}

// returns the number of int elements allocated
int CVectorInt::capacity() {
	return total_capacity;
}

// returns the number of elements actually inserted
int CVectorInt::size() {
	return actual_size;
}

// returns true/false according to amount of actual elements in the data
bool CVectorInt::empty() {
	return (actual_size == 0);
}

// frees all the data and resets the size
void CVectorInt::clear() {
	while (actual_size != 0) {
		actual_size -= 1;
		if (actual_size < total_capacity / 2) {
			half_array();
		}
	}

}

// adds an int elements at the end
void CVectorInt::push_back(int to_add) {
	if (actual_size == total_capacity) {
		double_array();
	}
	array[actual_size] = to_add;
	actual_size += 1;
}

// removes an int elements at the end and return it
int CVectorInt::pop_back() {
	if (empty()) {
		throw("Array is empty");
	}
	int to_pop = array[actual_size - 1];
	array[actual_size - 1] = 0;
	actual_size -= 1;
	if (actual_size < total_capacity/2) {
		half_array();
	}
	return to_pop;
}

// removes an int element at specific index
int CVectorInt::remove(int index) {
	if (index < 0 || index >= actual_size) {
		throw ("Index out of bound");
	}
	int to_remove = array[index];
	for (int i = index; i < actual_size; i++) {
		array[i] = array[i + 1];
	}
	actual_size -= 1;
	if (actual_size < total_capacity/2) {
		half_array();
	}
	return to_remove;
}

// interface to access the data at a specific index using subscript "[]"
int& CVectorInt::operator[](int index) {
	int* new_arr;
	if (index >= total_capacity) {
		double_array();
	}
	if (index > actual_size)
		actual_size = index + 1;
	return *(array + index);
}


int main(int argc, char* argv[])
{
	// some code to use the class
	try
	{
		CVectorInt v(5);
	
		for (int i = 0; i < 5; i++)
		{
			v.push_back(i);
		}
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
		v.push_back(1);
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
		while (!v.empty())
		{
			v.pop_back();
		}
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
		v.reserve(15);
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
		for (int i = 0; i < 15; i++)
		{
			v.push_back(i);
		}
		v[5] = 3;
		for (int i = 0; i < v.size(); i++)
		{
			std::cout << v[i] << " ";
		}
		std::cout << std::endl;
		v.clear();
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}