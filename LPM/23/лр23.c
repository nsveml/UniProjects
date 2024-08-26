#include<stdio.h>
#include<stdlib.h>

typedef struct tree* Tree;

struct tree {
	struct tree* left;
	struct tree* right;
	int value;
};

void lRr(Tree t, int d){
	if(t!=NULL){
		lRr(t->left,d+1);
		printf("%*s%d\n",2*d,"-",t->value);
		lRr(t->right,d+1);
	}
}

void printtree(Tree t){
	lRr(t,0);
	printf("\n");
}

Tree add(int b, Tree it){
	if (it==NULL) {it=(Tree)malloc(sizeof(struct tree)); it->value=b; it->right=NULL; it->left=NULL;}
	else {
		if(b>=(it->value)) {it->right=add(b, it->right);}
		if(b<(it->value)) {it->left=add(b, it->left);}
	}
	return(it);
}

Tree findprev(int b, Tree it){
	Tree d=it;
	if(it!=NULL){
		while(it->value!=b){
			d=it;
			if(it->value<b) {
			it=it->right;
			}
			if(it->value>=b) {
			it=it->left;
			}
		}
	}
	return(d);
}

Tree down(Tree it){
	while(it->left!=NULL) it=it->left;
	return(it);
}

void del(int b, Tree *it){
	Tree that=*it, prev, d;
	prev=that;
	prev = findprev(b, prev);
	if (that->value==b){
		if(that->right!=NULL) {
			*it=that->right;
			d=down(*it);
			d->left=that->left;
		}
		else if(that->left!=NULL) *it=that->left;
		else if(that->left==NULL) *it=NULL;
	}
	else if (b>=prev->value) {
		that = prev->right;
		if (that->right!=NULL) {
			prev->right=that->right;
			d=down(prev->right);
			d->left=that->left;
		}
		else if(that->left!=NULL) prev->right=that->left;
		else if(that->left==NULL) prev->right=NULL;
	}
	else if (b<prev->value) {
		that = prev->left;
		if (that->right!=NULL) {
			prev->left=that->right;
			d=down(prev->left);
			d->left=that->left;
		}
		else if(that->left!=NULL) prev->left=that->left;
		else if(that->left==NULL) prev->left=NULL;
	}
	free(that);
}

int lrr(Tree tl, Tree tr, int b){
	if (tl!= NULL && tr!=NULL){
		b=lrr(tl->left,tr->right, b);
		b=lrr(tl->right, tr->left, b);}
	else if (!((tl!= NULL || tr==NULL)&&(tl== NULL || tr!=NULL))) b++;
	return(b);
}

void option(Tree t){
	Tree tl=t->left, tr=t->right;
	if(lrr(tl,tr, 0)==0) printf("Tree is self-similar\n");
	else printf("Tree isn't self-similar\n");
}

int main(){
	Tree t=NULL;
	char a;
	int b;
	printf("\n p - print \n a - add \n d - delete \n o - option \n q - quit \n\n");
	while(1>0){
	if(a!='\n')printf("Enter command: ");
	scanf("%c",&a);
	if(a!='\n')printf("\n");
	switch(a){
		case 'a':
				printf("Enter value: ");
				scanf("%d",&b);
				t=add(b, t);
				printf("\n");
				break;
		case 'd':
				printf("Enter value: "); 
				scanf("%d",&b);
				del(b, &t);
				printf("\n");
				break;
		case 'p':
				printf("This is tree in lRr:\n");
				printtree(t);
				printf("\n");
				break;
		case 'o':
				option(t);
				break;
		case 'q': return (0);
	}
}
}
