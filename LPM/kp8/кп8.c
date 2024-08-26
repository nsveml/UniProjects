#include<stdio.h>
#include<stdlib.h>

struct Item{
	int value;
	struct Item* next;
};


typedef struct Item* List;

//NEXT
List Next(List it){
	if(it->next!=NULL) return it->next; else return it;
}
//FIRST
List first(List m){
	if(m->next!=NULL)return m->next; else return m;
}
//PRINT
void Print(List m){
	List n=m->next;
	while(n!=NULL){
	    printf("%d ",n->value);
	    n=n->next;
	}
}
//ADD
void Add(List *it, int b, List m){
	List n=(List)malloc(sizeof(struct Item));
	n->value=b;
	n->next=(*it)->next;
	(*it)->next=n;	
	if(*it==m) *it=m->next;
}
//DELETE
void Del(List it, List m){
	if(m->next!=NULL){
		List n=m;
		while(n->next!=it){
		    n=n->next;
		}
		n->next=it->next;
		free(it);
		it=n;
	}
}
//INSERT
void Ins(List m, int x){
	List n=m;
	Add(&n, x, m);
}
//CLEAR
void clear(List m){
	if(m->next!= NULL) clear(m->next);
	free(m);
}
//OPTION
void Clear(List *it, List m, int x){
    int i=0;
    if(m->next!=NULL){
    	List n=m->next;
		while(n!=NULL){
		    if(n->value==x) {i++; break;}
		    n=n->next;}
		n=m;
		if(i!=0){
			*it=m;
			clear(m->next);
			m->next=NULL;
		}
	}
	else printf("List is empty\n");
}
//LENGTH
void Length(List m){
	List n=first(m)->next;
	int i=0;
	while(n!=NULL){
	    i++;
	    n=n->next;
	}
	printf("%d\n",i);
}

int main(){
	printf("q - Quit\np - Print\nf - First\n\
a - Add\nd - Delete\nl - Length\nc - Clear\n\
i - Insert to first\nn - Next\n\n");
	int x;
	List m = NULL;
	List it = NULL;
	struct Item bar;
	bar.value=0;
	m=&bar;
	it=m;
	bar.next=NULL;
	char a=' ';
	while(1 > 0){
	if(a!='\n') printf("Enter command:\n");
	scanf("%c",&a);
	if(a!='\n') printf("\n");

	switch(a){
		case 'q':
			return 0;
			break;
		case 'p':
			if(m->next==NULL) printf("List is empty\n");
			else Print(m);
			printf("\n");
			break;
		case 'f':
			it=first(m);
			if(it!=m)printf("%d",it->value);
			else printf("List is empty\n");
			printf("\n");
			break;
		case 'a':
			scanf("%d",&x);
			Add(&it, x, m);
			if(it->next==NULL) printf("%d was added at first place\n", it->value);
			else printf("Added element: %d\n\n",it->next->value);
			break;
		case 'd':
			if(m->next==NULL) printf("List is empty\n");
			else Del(it, m);
			printf("\n");
			break;
		case 'l':
			Length(m);
			printf("\n");
			break;
		case 'c':
			if(m->next==NULL) printf("List is empty\n");
			else{
			printf("Enter value: ");
			scanf("%d",&x);
			Clear(&it, m, x);}
			printf("\n");
			break;
		case 'i':
			printf("Enter value: ");
			scanf("%d",&x);
			Ins(m, x);
			break;
		case 'n':
		    it=Next(it);
		    if(it!=m)printf("%d\n",it->value);
		    else printf("List is empty\n");
		    printf("\n");
	}
}	
}
