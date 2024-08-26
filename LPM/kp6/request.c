#include "kp6.h"

int main(){
char a = ' ';
printf("h - Help\np - Print\nr - Request\no - Find \n\nEnter q to quit\n\n");
while( a != 'q' ){
if(a != '\n') printf("Enter command:");
scanf("%c",&a);
switch(a){
	case 'h':
		help(1);
		break;
	case 'p':
		print();
		break;
	case 'r':
		req();
		break;
	case 'o':
		var16();
		break;
	case 'q':
		return 0;
}
if(a!='\n')printf("\nOperation %c done!\n\n", a);
}	
}
