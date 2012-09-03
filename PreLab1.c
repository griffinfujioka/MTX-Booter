#include<stdio.h>

int main()
{
	char name[36]; 

	printf("\nPress enter when prompted for name to end program\n"); 
	while(1)
	{
		printf("What is your name? "); 
		fgets(name,36,stdin); 	// Read input into name buffer 
		if(strncmp(name,"\n", strlen(name))==0)
		{ 
			printf("Bye bye!\n"); 
			return 1; 
		} 
		else
		{
			if(name[strlen(name)-1] == '\n')	// If the last character is a new line
				name[strlen(name)-1] = '\0'; 
			printf("Welcome, %s!\n", name); 
			int i=0; 
			for(i=0; i<36; i++)
				name[i] = NULL; 
		} 
	}
}
