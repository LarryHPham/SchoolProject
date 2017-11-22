#include <stdio.h>

int main()
{
        int lpage[10], pagetab[10], pframe[2][2], I,j;
        int size, msize, cnt, t,k,pos,logadd,m=0;
        int frameno;
        long int l;
        int i;
        printf("\nEnter the memory size:");
        scanf("%d", &msize);
        printf("Enter the pase size:");
        scanf("%d", &size);
//         unsigned long page;
//         unsigned long offset;
//         unsigned long address;
//
//
//         address= atoll(argv[1]);
// /* Page Number =  quotient of  address / 4KB and offset = remainder*/
// /*Below is the faster method of calculating the same*/
//
//         page = address >> 12; /* Since page size is 4KB => 12 bits holding the virtual address*/
//         offset = address & 0xfff;
//
//         printf("The address %lu contains: \n", address);
//         printf("page number = %lu\n",page);
//         printf("offset = %lu\n", offset);
//
//
//         return 0;
}
