#include <stdio.h>
#define NO_WORDS 2
#define SIZE_WORDS NO_WORDS<<3

typedef struct {
   unsigned long long double_word[NO_WORDS];
} arr_t __attribute__ ((aligned (SIZE_WORDS) ));

void store_data (arr_t arr[8], unsigned long long data[8]){
  arr[0].double_word[0] = data[0];
  arr[0].double_word[1] = 0;
  for (int i = 1; i < 8; i++) {
    arr[i].double_word[0] = data[i] << (i * 8);
    arr[i].double_word[1] = data[i] >> (64 - (i * 8));
  }
}

arr_t store_byte_data[8] =
       {
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 }
       };


arr_t store_byte_expected_data[8] =
       {    // double_word0         double_word1
          { 0x00000000000000EF, 0x0000000000000000 },
          { 0x000000000000BE00, 0x0000000000000000 },
          { 0x0000000000AD0000, 0x0000000000000000 },
          { 0x00000000DE000000, 0x0000000000000000 },
          { 0x000000EF00000000, 0x0000000000000000 },
          { 0x0000BE0000000000, 0x0000000000000000 },
          { 0x00AD000000000000, 0x0000000000000000 },
          { 0xDE00000000000000, 0x0000000000000000 }
       };

arr_t store_half_word_data[8] =
       {
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 }
       };


arr_t store_half_word_expected_data[8] =
       {
          { 0x000000000000BEEF, 0x0000000000000000 },
          { 0x0000000000ADBE00, 0x0000000000000000 },
          { 0x00000000DEAD0000, 0x0000000000000000 },
          { 0x000000EFDE000000, 0x0000000000000000 },
          { 0x0000BEEF00000000, 0x0000000000000000 },
          { 0x00ADBE0000000000, 0x0000000000000000 },
          { 0xDEAD000000000000, 0x0000000000000000 },
          { 0xDE00000000000000, 0x00000000000000EF }
       };


arr_t store_word_data[8] =
       {
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 }
       };


arr_t store_word_expected_data[8] =
       {
          { 0x00000000DEADBEEF, 0x0000000000000000 },
          { 0x000000DEADBEEF00, 0x0000000000000000 },
          { 0x0000DEADBEEF0000, 0x0000000000000000 },
          { 0x00DEADBEEF000000, 0x0000000000000000 },
          { 0xF00DC0DE00000000, 0x0000000000000000 },
          { 0x0DC0DE0000000000, 0x00000000000000F0 },
          { 0xC0DE000000000000, 0x000000000000F00D },
          { 0xDE00000000000000, 0x0000000000F00DC0 }
       };


arr_t store_double_word_data[8] =
       {
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 }
       };


arr_t store_double_word_expected_data[8] =
       {
          { 0xDEADBEEFF00DC0DE, 0x0000000000000000 },
          { 0xADBEEFF00DC0DE00, 0x00000000000000DE },
          { 0xBEEFF00DC0DE0000, 0x000000000000DEAD },
          { 0xEFF00DC0DE000000, 0x0000000000DEADBE },
          { 0xF00DC0DE00000000, 0x00000000DEADBEEF },
          { 0x0DC0DE0000000000, 0x000000DEADBEEFF0 },
          { 0xC0DE000000000000, 0x0000DEADBEEFF00D },
          { 0xDE00000000000000, 0x00DEADBEEFF00DC0 }
       };


const size_t size = sizeof(arr_t);

int store_byte_test ( ) {

// EF, BE, AD, DE, EF, BE, AD, DE
  unsigned long long arr_test[] = {0xEF, 0xBE, 0xAD, 0xDE, 0xEF, 0xBE, 0xAD, 0xDE};
  store_data(store_byte_data, arr_test);
  for (int i = 0; i < 8; i++) {
    if (store_byte_expected_data[i].double_word[0] != store_byte_data[i].double_word[0] || store_byte_data[i].double_word[1] != store_byte_expected_data[i].double_word[1]){
      return 1;
    }
  }
  return 0;
} // store_byte_test


int store_half_word_test ( ) {

// BEEF, ADBE, DEAD, EFDE, BEEF, ADBE, DEAD, EFDE
  unsigned long long arr_test[] = {0xBEEF, 0xADBE, 0xDEAD, 0xEFDE, 0xBEEF, 0xADBE, 0xDEAD, 0xEFDE};
  store_data(store_half_word_data, arr_test);
  for (int i = 0; i < 8; i++) {
    if (store_half_word_data[i].double_word[0] != store_half_word_expected_data[i].double_word[0] || store_half_word_data[i].double_word[1] != store_half_word_expected_data[i].double_word[1]) {
      return 1;
    }
  }
  return 0;
} // store_half_word_test


int store_word_test ( ) {

// DEADBEEF, F00DC0DE
  unsigned long long arr_test[] = {0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF, 0xF00DC0DE, 0xF00DC0DE, 0xF00DC0DE, 0xF00DC0DE};
  store_data(store_word_data, arr_test);
  for (int i = 0; i < 8; i++) {
    if (store_word_data[i].double_word[0] != store_word_expected_data[i].double_word[0] || 
    store_word_data[i].double_word[1] != store_word_expected_data[i].double_word[1]) {
      return 1;
    }
  }
return 0;
} // store_word_test


int store_double_word_test ( ) {

// DEADBEEFF00DC0DE
  unsigned long long arr_test[] = {0xDEADBEEFF00DC0DE, 0xDEADBEEFF00DC0DE, 0xDEADBEEFF00DC0DE, 0xDEADBEEFF00DC0DE, 0xDEADBEEFF00DC0DE, 0xDEADBEEFF00DC0DE, 0xDEADBEEFF00DC0DE, 0xDEADBEEFF00DC0DE};
  store_data(store_double_word_data, arr_test);
  for (int i = 0; i < 8; i++) {
    if (store_double_word_data[i].double_word[0] != store_double_word_expected_data[i].double_word[0] || store_double_word_data[i].double_word[1] != store_double_word_expected_data[i].double_word[1])
    {
      return 1;
    }
  }
  return 0;
} // store_double_word_test


int main() {
 if (store_byte_test()) {
    printf("Store Byte Test Failed\n");
  }
  else printf("Store Byte Test Passed\n");
 if (store_half_word_test()) {
    printf("Store Half Word Test Failed\n");
  }
  else printf("Store Half Word Test Passed\n");
  if (store_word_test()) {
    printf("Store Word Test Failed\n");
  }
  else printf("Store Word Test Passed\n");
  if (store_double_word_test()) {
    printf("Store Double Word Test Failed\n");
  }
  else printf("Store Double Word Test Passed\n");
} // main
