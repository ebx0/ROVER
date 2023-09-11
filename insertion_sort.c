/** LIBRARIES **/
#include <stdio.h>
#include <stdlib.h>

/** SYSTEM DATA TYPES **/
typedef unsigned int dword;
typedef unsigned char byte;

/** PROJECT VARIABLES **/
int arr[] = { 8, 15, 2, 4, 20, -7, 5, 0, 14, 14 };
size_t arrLength = (sizeof(arr) / sizeof(arr[0]));

/** ERROR HANDLING **/
#define UNKNOWN_ERROR_CODE 255;
enum errorCodes {
    ERR_EMPTY_ARRAY = 1,
    ERR_last, // Only for indexing, do not use or delete
};

const char *errorMessages[] = {
    "",                 // 0: No error
    "Array is empty.",  // 1: ERR_EMPTY_ARRAY
};

byte printError(byte errorCode) {
    if (errorCode > 0 && errorCode < ERR_last) {
        fprintf(stderr, "Error [%d]: %s\n", errorCode, errorMessages[errorCode]);
        return errorCode;
    } else {
        fprintf(stderr, "Unknown error code: %d\n", errorCode);
        return UNKNOWN_ERROR_CODE;
    }
}

/** FUNCTION DECLARATIONS **/
void shift_element(int *pElement);
void insertion_sort();
void print_array();

/** MAIN **/
int main() {
  // Error Handling
  if (!arrLength) return printError(ERR_EMPTY_ARRAY);

  print_array();
  insertion_sort();
  print_array();

  return 0;
}

/** PROJECT FUNCTIONS **/

// Takes one element and shifts until there is no higher value in its left
void shift_element(int *pElement) {
  for (int *e = pElement; e > arr && *e < *(e - 1); e--) {
    // XOR Swap Algorithm
    *e ^= *(e - 1);
    *(e - 1) ^= *e;
    *e ^= *(e - 1);
    //Generic Swap (Alternative)
    //byte tempVal = *(e - 1);
    //*(e - 1) = *e;
    //*e = tempVal;
  }
}

// Sorts the array with insertion algorithm
void insertion_sort() {
  for (int *e = arr; e < arr + arrLength; e++) {
    if (*e < *(e - 1))
      shift_element(e);
  }
}

// Prints the elements of array
void print_array() {
  printf("Array: ");
  for (int *e = arr; e < arr + arrLength; e++) {
    printf(" %d,", *e);
  }
  printf("\b \n");
}
