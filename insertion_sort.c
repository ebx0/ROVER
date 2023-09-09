/** LIBRARIES **/
#include <stdio.h>

/** SYSTEM DATA TYPES **/
typedef unsigned int dword;
typedef unsigned char byte;

/** PROJECT VARIABLES **/
int arr[] = { 8, 15, 2, 4, 20, 7, 5, 9, 14, 11 };

/** PROJECT DEFINES **/
#define arrLenght (sizeof(arr) / sizeof(arr[0]))

/** FUNCTION DECLARATIONS **/
void shiftElement(int* pElement);
void insertionSort();
void printArray();

/** PROJECT FUNCTIONS **/

// Takes one element and shifts until there is no higher value in its left
void shift_element(int* pElement){ 
  for(int* e = pElement; e > arr && *e < *(e-1); e--){
      *e ^= *(e-1); //XOR Swap Algorithm
      *(e-1) ^= *e;
      *e ^= *(e-1);
  }
}

// Sorts the array with insertion algorithm
void insertion_sort(){
    for(int* e = arr; e < arr + arrLenght; e++){
        if (*e < *(e-1)) shift_element(e);
    }
}

//Prints the elements of array
void print_array(){
    printf("Array: ");
    for(int* e = arr; e < arr + arrLenght; e++){
        printf(" %d,", *e);
    }
    printf("\b \n");
} 
  
/** MAIN **/
int main() 
{ 
    print_array();
    insertion_sort();
    print_array();
    
    return 0; 
}
