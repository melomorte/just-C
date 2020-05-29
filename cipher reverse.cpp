#include <stdio.h>

int main(int argc, char** argv)
{
	char cipher[] = "picoCTF{w1{1wq80haib767}";
	char text[] = "picoCTF{w1{1wq80haib767}";	
	char newChar;
	
	for(int i = 0x16; i >= 8; i--){
		newChar = cipher[i];
		
		if((i && 1)== 0){
			text[i] = newChar - 5;
		}
		else
		{
			text[i] = newChar + 2;
		}
	}
	
	printf("flag: %s", text);
	printf("\n");	
	
	return 0;
}