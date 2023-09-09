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
    byte indexVal = pElement - &arr[0]; // Find index of pointed item in array
        
    for(byte i = 0; i < indexVal &&  *(pElement-1-i) > *(pElement-i); i++){
        byte temp = *(pElement-i);
        *(pElement-i) = *(pElement-1-i);
        *(pElement-1-i) = temp;
    }
}

// Sorts the array
void insertion_sort(){
    for(byte i = 1; i < arrLenght; i++){
        int* iElement1 = &arr[0]+(i);
        int* iElement2 = &arr[0]+(i-1);
        
        if (*iElement1 < *iElement2) shift_element(iElement1);
    }
}

//Prints the items of array
void print_array(){
    printf("Array: ");
    for(int i=0; i < arrLenght; i++){
        printf(" %d,", arr[i]);
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
