#include<stdio.h>
#include<stdlib.h>

typedef struct matrix matrix;


struct matrix{
	int *M, *A, m, a, b;
};

void printmatrix(matrix m){
	int l=0;
	for(int i=0; i<m.m; i++){
		l=m.M[i]-1;
		for(int j=0; j<m.b; j++){
			if((l>=0)){
				if(m.A[l]==j+1){
				printf("%d ", m.A[l+1]);
				l+=2;
				}
				else printf("0 ");
			}
			else printf("0 ");
		}
		printf("\n");
	}
}

void readmatrix(matrix *M){
	int a, k=1, c;
	(*M).a=0;
	if((*M).m<0){
		printf("Enter number of lines: ");
		scanf("%d", &(*M).m);
		printf("Enter number of columns: ");
		scanf("%d",&(*M).b);
	}
	(*M).M=(int *)malloc(sizeof(int)*(*M).m);
	(*M).M[0]=1;
	(*M).A=(int *)malloc(sizeof(int)*k);
	printf("Enter matrix:\n");
	for(int i=0; i<(*M).m; i++){
		(*M).M[i]=(*M).a+1;
		for(int l=0; l<(*M).b; l++){
			scanf("%d",&c);
			if(c!=0){
				if(k-(*M).a<=2){
					(*M).A=(int *)realloc((*M).A, (k*2)*sizeof(int));
					k*=2;
				}
				(*M).A[(*M).a]=l+1;
				(*M).A[(*M).a+1]=c;
				(*M).a+=2;
			}
			if(l==(*M).b-1){
				if((*M).M[i]==(*M).a+1) (*M).M[i]=0;
				if(((*M).A[(*M).a-1]!=0)&&((*M).a>0)) {
					(*M).A[(*M).a]=0;
					(*M).a++;
				}
				if((i==(*M).m-1)&&((*M).a==0)) (*M).A[0]=0;
			}
		}
		if((*M).a==0){
			(*M).a=1;
			(*M).A[0]=0;
		}
	}
	(*M).A=(int *)realloc((*M).A, sizeof(int)*(*M).a);
}

matrix sum(matrix m1, matrix m2){
	matrix m;
	m.b=m2.b;
	m.m=m2.m;
	int i1=0, i2=0, k=1;
	m.M=(int *)malloc(sizeof(int)*m.m);
	m.A=(int *)malloc(sizeof(int)*k);
	m.a=0;
	for(int l=0; l<m.m; l++){
		i1=m1.M[l]-1;
		i2=m2.M[l]-1;
		m.M[l]=m.a+1;
		while((i1!=-1)||(i2!=-1)){
			if(k-m.a<=2){
				k*=2;
				m.A=(int *)realloc(m.A, sizeof(int)*k);
			}
			if (i1>=0) if (m1.A[i1]==0) i1=-1;
			if (i2>=0) if (m2.A[i2]==0) i2=-1;
			if((i1!=-1)){
				if(i2!=-1){
					if(m1.A[i1]==m2.A[i2]){
						if(m1.A[i1+1]+m2.A[i2+1]!=0){
							m.A[m.a]=m1.A[i1];
							m.A[m.a+1]=m1.A[i1+1]+m2.A[i2+1];
							m.a+=2;
							i1+=2;	
							i2+=2;
						}
						else{
							i1+=2;
							i2+=2;
						}
					}
					else if(m1.A[i1]<m2.A[i2]){
						m.A[m.a]=m1.A[i1];
						m.A[m.a+1]=m1.A[i1+1];
						m.a+=2;
						i1+=2;
					}
					else if(m2.A[i2]<m1.A[i1]){
						m.A[m.a]=m2.A[i2];
						m.A[m.a+1]=m2.A[i2+1];
						m.a+=2;
						i2+=2;
					}
				}
				else{
					m.A[m.a]=m1.A[i1];
					m.A[m.a+1]=m1.A[i1+1];
					m.a+=2;
					i1+=2;
				}
			}
			else if(i2!=-1){
				m.A[m.a]=m2.A[i2];
				m.A[m.a+1]=m2.A[i2+1];
				m.a+=2;
				i2+=2;
			}
			else{
				if(m.a>0){
					if(m.A[m.a-1]!=0){
						m.A[m.a]=0;
						m.a++;
					}
				}
				
			}
		}
		if(m.M[l]==m.a+1) m.M[l]=0;
	}
	if(m.a==0){
		m.a=1;
		m.A[0]=0;
	}
	m.A=(int*)realloc(m.A, sizeof(int)*m.a);
	return m;
}

int SymVal(int v, int i, int j, matrix *m){
	int a=1,l;
	l=m->M[j-1]-1;
	if(l==-1) a=0;
	else{
		while(m->A[l]!=0){
			if(m->A[l]==i){
				if(m->A[l+1]!=v){
					a=0;
				}
				break;
			}
			else if(m->A[l]>i){
				a=0;
				break;
			}
			l+=2;
		}
	}
	return a;
}

int sym(matrix *m){
	int s=1, l;
	for(int i=0; i<m->m; i++){
		l=m->M[i]-1;
		if(l!=-1){
			while(m->A[l]!=0){
				s=SymVal(m->A[l+1], i+1, m->A[l], m);
				l+=2;
				if(s==0) break;
			}
			if(s==0) break;
		}
	}
	return s;
}



int main(){
	//Вывод информации о матрицах
	int *a, *b;
	matrix m1, m2, m3;
	m1.m=-1;
	readmatrix(&m1);
	printf("\nArray A:\n");
	for(int i=0; i<m1.a; i++) printf("%d ", m1.A[i]);
	printf("\nArray M:\n");
	for(int i=0; i<m1.m; i++) printf("%d ", m1.M[i]);
	printf("\n");
	printf("\n");
	printf("\n\n");
	m2.m=m1.m;
	m2.b=m1.b;
	readmatrix(&m2);
	printf("\nArray A:\n");
	for(int i=0; i<m2.a; i++) printf("%d ", m2.A[i]);
	printf("\nArray M:\n");
	for(int i=0; i<m2.m; i++) printf("%d ", m2.M[i]);
	//Распечатка в стандартном виде
	printf("\n\nFirst matrix:\n");
	printmatrix(m1);
	printf("\n\nSecond matrix:\n");
	printmatrix(m2);
	//Сумма матриц и вывод информации о ней, распечатка
	printf("\n\nSum:\n\n");
	m3=sum(m1, m2);
	printmatrix(m3);
	printf("\n\nArray A:\n");
	for(int i=0; i<m3.a; i++) printf("%d ", m3.A[i]);
	printf("\n\nArray M:\n");
	for(int i=0; i<m3.m; i++) printf("%d ", m3.M[i]);
	//Проверка симметричности
	printf("\n\n");
	if(sym(&m3)) printf("Sum is symmetrical\n");
	else printf("Sum isn't symmetrical\n");
	free(m1.A);
	free(m1.M);
	free(m2.A);
	free(m2.M);
	free(m3.A);
	free(m3.M);
}
