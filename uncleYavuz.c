/** LIBRARIES **/
#include <stdio.h>
#include <stdlib.h>

/** SYSTEM DATA TYPES **/
#define dword unsigned int 
#define byte unsigned char

/** SYSTEM FUNCTIONS **/
// Read and dispose of data from stdin until \n or EOF encountered
// Return \n or EOF
int clearBuffer(void) {
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF)
  return ch;
}

/** PROJECT DEFINITIONS **/
#define MIN_MASS_LIMIT 50 // Define your minimum mass limit

/** PROJECT ERROR CODES **/
#define ERR_INVALID_INPUT 1
#define ERR_INVALID_LIMIT 2
#define ERR_CONVEYOR_ERROR 3
#define ERR_LIMIT_EXCEEDED 4

/** PROJECT VARIABLES **/
int massLimit;
dword count = 0; // total count of products
dword massTotal = 0; // total mass value of products
int massLast = 0; // mass value of last product

/** PROJECT FUNCTIONS **/
//Shows product line info with a monitor screen when function called
void showMonitor(){
    printf("\n\n//===============[BANT MONITOR]=============//");
    printf("\n//\tKabul Edilen Maksimum Kütle\t=\t%5d\t//",massLimit);
    printf("\n//\tSistemden Geçen Ürün Sayisi\t=\t%5d\t//",count);
    printf("\n//\tÜrünlerin Toplam Kütlesi\t=\t%5d\t//",massTotal);
    printf("\n//==========================================//\n\n");
}
//Shows info of last product with a product screen when function called
void showProduct(){
    printf("\n\n/---------------URUN MONITOR----------------/");
    printf("\n/\tSon Gecen Ürünün Sirasi\t\t=\t%5d\t/",count);
    printf("\n/\tSon Gecen Ürünün Kütlesi\t=\t%5d\t/",massLast);
    printf("\n/-------------------------------------------/\n\n");
}


//Project error message sent function - Error Handling
void errorMessage(byte errorID){
    switch (errorID){
        case ERR_CONVEYOR_ERROR: // SISTEM BANT HATASI (FATAL)
            showMonitor();
            fprintf(stderr, "HATA | Sistem Bant Hatasi!\n");
            break;
        case ERR_LIMIT_EXCEEDED: // MAX LIMIT HATASI (FATAL)
            massTotal += massLast;
            count++;
            showMonitor();
            fprintf(stderr, "HATA | Maximum Limit Asildi Hatasi!\n");
            break;
        case ERR_INVALID_INPUT: // INPUT ERROR
            printf("UYARI | Pozitif tam sayı olmayan hatali bir deger girdiniz.\n\n");
            clearBuffer();
            break;
        case ERR_INVALID_LIMIT: // HATALI LIMIT
            printf("UYARI | Kütle Limiti en az %d gram olmalıdır. Girdiğiniz limit = %d gram\n\n", MIN_MASS_LIMIT, massLimit);
            break;
    }
}

// Ask the user to enter a valid mass limit that does not exceed MIN_MASS_LIMIT
// Set the massLimit as a legitimate value input
void askMassLimit() {
    do {
        printf("Maksimum Kütle Limitini Giriniz: ");
        if (scanf("%d", &massLimit) != 1 || massLimit < 1) { // Handle invalid input
            errorMessage(ERR_INVALID_INPUT);// INPUT ERROR
            continue;
        }
        else if (massLimit < MIN_MASS_LIMIT) {
            errorMessage(ERR_INVALID_LIMIT);
        }
    } while (massLimit < MIN_MASS_LIMIT);
    printf("Gecerli bir kütle limiti girildi.\n");
}


/** INITIALIZATION **/
void init(){
    askMassLimit();
    printf("Belirlenen en fazla kütle degeri = %d gram\n", massLimit);
    printf("Sistem Baslatildi.\n");
}

/** LOOP **/
void loop(){
    while (1) {
        printf("\n[Ürün No #%d]\nBanttan gececek ürünün kütlesini giriniz: ", count+1);
        // Controls the validity of product mass
        if (scanf("%d", &massLast)) {
            if (massLast < massLimit && massLast > 0) {
                massTotal += massLast;
                count++;
                showProduct();
            }
            else if (massLast <= 0){ // If mass negative or zero:
            
                errorMessage(ERR_CONVEYOR_ERROR);// SISTEM BANT HATASI
                break;
            }
            else if (massLast > massLimit){// If mass limir exceeded:
                errorMessage(ERR_LIMIT_EXCEEDED);// MAX LIMIT HATASI
                break;
            }
        }
        else {
            errorMessage(ERR_INVALID_INPUT);// INPUT ERROR
            printf("%u",massLast);
        }
        
    }
}

int main() {
    init();
    loop();
    printf("Program kapatıldı.");
    return 0;
}
