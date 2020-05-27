#include <stdio.h>

int main(int argc, char** argv)
{
	int eax;
	int ebp = 0xc;
	   
	eax = ebp;
	printf("eax: %x \nebp: %x\n\n", eax, ebp);	
	
	ebp = ebp - 0x4;
	eax = ebp + 0x8;
	printf("eax: %x \nebp: %x\n\n", eax, ebp);
	
	ebp = ebp - 0x8;
	
	while(ebp <= 0xa3d3)
	{
		ebp = (ebp - 0x4) + 0x1;
		ebp = (ebp - 0x8) + 0xaf;
		printf("ebp - %x\n", ebp);
	}
	
	eax = ebp - 0x4;
	printf("flag: %x\n\n", eax);
	
	return 0;
}
