// C++ program to insert an element at a specific position 
// in a vector 
#include <iostream> 
#include <vector> 
  
int main() 
{ 
    // Initialize the vector 
    std::vector<int> myVector = { 1, 2, 3, 4, 5 }; 
  
    // Position at which to insert 
    int position = 1; 
  
    // Element to insert 
    int newElement = 6;

    myVector.insert(myVector.begin() + position, newElement);
  
    // Print the vector 
    for (int i = 0; i < myVector.size(); i++) 
        std::cout << myVector[i] << " "; 
  
    return 0; 
}
