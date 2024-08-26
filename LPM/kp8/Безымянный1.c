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

void option(Tree t){
	
}

int main(){
	double a =5.0;
	printf("%d",(a/3.0));
}
