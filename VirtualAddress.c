#include <stdio.h>

//decided not to use (int argc, char *argv[]) so you can personally create input yourself
int main(){
  //declare variables
  unsigned long int virtual_address, page_number, offset;
  long binary = 4096;// 32-bit in binary
  printf("\nVirtual Address: ");
  scanf("%lu", &virtual_address);

  page_number = virtual_address/binary;
  offset = virtual_address%binary;

  printf("\nThe address %lu contains:", virtual_address);
  printf("\npage number = %lu", page_number);
  printf("\noffset = %lu\n", offset);
  return 0;
}
