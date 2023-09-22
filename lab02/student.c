#include <stdio.h>

//define a struct Student
struct Student {
  char *name;
  int id;
  int age;
};

//static inline function with integer return type
static inline int square(int num) {
  return num * num;
}

int main(int argc, char *argv[])
{
  struct Student student1;

  student1.name = "Jahanzaib";
  student1.id = 36;
  student1.age = 30;

  //Print Student Information
  printf("Student Information\n");
  printf("Name: %s\n", student1.name);
  printf("ID: %d\n", student1.id);
  printf("Age: %d\n", student1.age);

  //Using static inline function
  int num = 5;
  int result = square(num);
  printf("\nSquare of %d is %d\n", num, result);
  
  return 0;
}
