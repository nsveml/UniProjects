#include "kp6.h"

int main(){
char a = ' ';
printf("h - Help\na - Add\nd - Delete\nr - Remove base\nc - Create base\n\nEnter q to quit\n\n");
while( a != 'q' ){
if(a != '\n') printf("Enter command:");
scanf("%c",&a);
switch(a){
	case 'h':
		help(0);
		break;
	case 'a':
		add();
		break;
	case 'd':
		del();
		break;
	case 'r':
		delall();
		break;
	case 'c':
		create();
		break;
	case 'q':
		return 0;
}
if(a!='\n')printf("\nOperation %c done!\n\n", a);
}	
}
