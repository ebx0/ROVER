/** LIBRARIES **/
#include <stdio.h>
#include <stdlib.h>

/** SYSTEM DATA TYPES **/
typedef unsigned int dword;
typedef unsigned char byte;

/** ERROR HANDLING **/
#define UNKNOWN_ERROR_CODE 255;
enum errorCodes {
  NO_ERROR = 0,
  ERR_INVALID_INPUT,
  ERR_last, // Only for indexing, do not use or delete
};

const char *errorMessages[] = {
    "",                                    // 0: NO_ERROR
    "Pozitif bir tam sayı değeri giriniz." // 1: ERR_INVALID_INPUT
};

byte printError(int errorCode) {
  if (errorCode > 0 && errorCode < ERR_last) {
    fprintf(stderr, "Error [%d]: %s\n", errorCode, errorMessages[errorCode]);
    return errorCode;
  } 
  else {
    fprintf(stderr, "Unknown error code: %d\n", errorCode);
    return UNKNOWN_ERROR_CODE;
  }
}

/** PROJECT STRUCTS **/
typedef struct apartment {
  byte flatNo;
  byte flatPower;
} APARTMENT_t;

/** PROJECT CONFIG **/
#define APT_SIZE 32
#define DEFAULT_FLAT_POWER 0

/** SYSTEM FUNCTIONS **/
// Read and dispose of data from stdin until \n or EOF encountered - Return \n or EOF
int clearBuffer(void) {
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF);
  return ch;
}

/** FUNCTION DECLARATIONS **/
byte getPowerData(dword*);
void initApartmentStruct(APARTMENT_t*);
void setApartmentData(APARTMENT_t*, dword);
byte showApartments(APARTMENT_t*);

/** MAIN **/
int main() {
  dword powerData;
  APARTMENT_t rovreApt[APT_SIZE];
  
  initApartmentStruct(rovreApt);
  while (getPowerData(&powerData) != NO_ERROR);
  setApartmentData(rovreApt, powerData);
  showApartments(rovreApt);

  return NO_ERROR;
}


/** PROJECT FUNCTIONS **/
//Take 32-bit power data value and arrange - Return error code
byte getPowerData(dword* powerData) {
  printf("Apartman için 32-bit güç dağıtım bilgisini giriniz: ");
  if (scanf("%u", powerData) != 1) {
    clearBuffer();
    return printError(ERR_INVALID_INPUT);
  }
  printf("\nGirilen sayı: %u\n", *powerData);
  return NO_ERROR;
}

//Initialize the apartment structure by assigning each apartment an index No.
void initApartmentStruct(APARTMENT_t* aprt){
  for(byte i = 0; i < APT_SIZE; i++){
      aprt[i].flatNo = i;
      aprt[i].flatPower = DEFAULT_FLAT_POWER;
  }
}

//Set the struct by given 32-bit power data
void setApartmentData(APARTMENT_t* aprt, dword data){
  printf("İşaretsiz, 32-bit genişliğinde ikilik tabandaki karşılığı: \n");
  for(char i = APT_SIZE-1; i >= 0; i--){
    byte tempStatus = (data & (1u << i)) >> i;
    printf("%d", tempStatus );
    if (i % 8 == 0) printf(" ");
    aprt[i].flatPower = tempStatus;
  }    
}

//Show all information about apartment - Return totalPowerOn
byte showApartments(APARTMENT_t* aprt){
  byte totalPowerOn = 0;
  printf("\n\n---------------- APARTMAN DURUMLARI ----------------\n\n");
  for(byte i = 0; i < APT_SIZE; i++){
      if (aprt[i].flatPower) {
        printf("Apartman No: %2d Elektrik Durumu: Yanik\n", aprt[i].flatNo);
        totalPowerOn++;
      }
      else {
        printf("Apartman No: %2d Elektrik Durumu: Sonuk\n", aprt[i].flatNo);
      }
  }
  printf(" Yanik daire sayisi:%2d   Sonuk daire sayisi:%2d\n", totalPowerOn, APT_SIZE-totalPowerOn);
  printf("---------------------------------------\n");
  return totalPowerOn;
}
