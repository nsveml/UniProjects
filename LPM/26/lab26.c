#include "deq.h"

int main(){
	Deque deq=NewDeq();
	char a;
	int b;
	printf("\n B - PushBack \n F - PushFront \n b - PopBack \n f - PopFront \n s - Sort \n p - Print \n i - Is empty \n c - Clear \n q - quit \n\n");
	while(1>0){
	if(a!='\n')printf("Enter command: ");
	scanf("%c",&a);
	if(a!='\n')printf("\n");
	switch(a){
		case 'B':
				printf("Enter value: ");
				scanf("%d",&b);
				PushBack(deq, b);
				printf("\n");
				break;
		case 'F':
				printf("Enter value: "); 
				scanf("%d",&b);
				PushFront(deq, b);
				printf("\n");
				break;
		case 'b':
				if(deq->key!=NULL){
				printf("%d",PopBack(deq));
				}else printf("\nIt is empty");
				printf("\n");
				break;
		case 'f':
				if(deq->key!=NULL){
				printf("%d",PopFront(deq));
				}else printf("\nIt is empty");
				printf("\n");
				break;
		case 's':
				print(deq);
				Sort(deq);
				printf("\n");
				print(deq);
				printf("\n");
				break;
		case 'p':
				print(deq);
				printf("\n");
				break;
		case 'c':
				Clear(deq);
				printf("\nDequeue size is %d\n",deq->size);
				break;
		case 'i':
				printf("\n");
				if(IsEmpty(deq)) printf("Deque is empty");
				else printf("Deque isn't empty");
				printf("\n");
				break;
		case 'q': return (0);
	}
	}
}
