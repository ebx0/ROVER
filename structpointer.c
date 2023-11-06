#include <stdio.h>

typedef enum {
  BME,
  EHM,
  MAT,
  bolumID_last
} bolumID_t;

typedef struct {
  int ogrenci;
  char isim[32];
} bolum_t;

typedef struct {
  int butce;
  bolum_t bolum[bolumID_last];
} okul_t;

okul_t ytu;

void butceArttir(okul_t *okul, int miktar) {
  okul->butce += miktar;
}

int main() {
  ytu.butce = 250;

  bolum_t bme = {
    .isim = "Biyomedikal Müh.",
    .ogrenci = 120
  };
  bolum_t ehm = {
    .isim = "Elektronik Haberleşme",
    .ogrenci = 150
  };
  bolum_t mat = {
    .isim = "Matematik",
    .ogrenci = 170
  };

  ytu.bolum[BME] = bme;
  ytu.bolum[EHM] = ehm;
  ytu.bolum[MAT] = mat;

  butceArttir(&ytu, 100);

  printf("Okul Bütçesi: %d TL\n", ytu.butce);
  
  for(int i = 0; i < bolumID_last; i++){
      printf("%s öğrenci sayısı: %d\n", ytu.bolum[i].isim, ytu.bolum[i].ogrenci);
  }

  return 0;
}
