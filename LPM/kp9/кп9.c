//Simple Insertion
//Real type, 4 bytes (key is float variable), apart (two files), 8 to 10 strings


#include<stdio.h>
#include<stdlib.h>

typedef struct record record;

struct record{
	float key;
	char * value;
};

char * readname(){
	int i=0;
	char b=' ', *a=(char*)malloc(sizeof(char)*256);
	scanf("%c",&b);
	while((b!='\n')&&(i!=256)){
		a[i]=b;
		i++;
		scanf("%c",&b);
	}
	a[i]='\0';
	return(a);
}

char * readstring(FILE* file, int length, int j){
	int i=0, eof;
	char b=' ', *a=(char*)malloc(sizeof(char)*(length+1));
	eof=fscanf(file,"%c",&b);
	do{
		a[i]=b;
		i++;
		eof=fscanf(file,"%c",&b);
	}while((b!='\n')&&(i!=length)&&(eof>=0));
	a[i]='\0';
	return(a);
}

void InsertionSort(record * table, int TableSize){
	record rec;
	int j;
	for (int i=1; i<TableSize; i++){
		rec.key = table[i].key;
		rec.value=table[i].value;
	    j = i-1;
   		while ((j >= 0) && (table[j].key > rec.key)){
	        table[j+1].key=table[j].key;
	        table[j+1].value=table[j].value;
    	    j = j - 1;
    	}
    	table[j+1].key = rec.key;
    	table[j+1].value=rec.value;
	}
}

void mix(record * table, int TableSize){
	int RandPosition;
	record rec;
	for(int i=0; i<TableSize; i++){
		RandPosition=rand()%TableSize;
		table[i].key+=table[RandPosition].key;
		table[RandPosition].key=table[i].key-table[RandPosition].key;
		table[i].key-=table[RandPosition].key;
		rec.value=table[i].value;
		table[i].value=table[RandPosition].value;
		table[RandPosition].value=rec.value;
	}
}

void reverse(record *table, int TableSize){
	record rec;
	for(int i=0; i<TableSize/2; i++){
		table[i].key+=table[TableSize-i-1].key;
		table[TableSize-i-1].key=table[i].key-table[TableSize-i-1].key;
		table[i].key-=table[TableSize-i-1].key;
		rec.value=table[i].value;
		table[i].value=table[TableSize-i-1].value;
		table[TableSize-i-1].value=rec.value;
	}
}

void PrintTable(record * table, int TableSize){
	for(int i=0; i<TableSize; i++){
		printf("%.2f  ", table[i].key);
		printf("%s\n", table[i].value);
	}
}

void bs(record *table, int TableSize){
	float key, eps;
	char ctrl;
	TableSize--;
	int check=1, i=TableSize/2;
	printf("Enter key:");
	scanf("%f",&key);
	for(int i=1; i<TableSize; i++){
		if(table[i].key<table[i-1].key) check=0;
	}
	if(check){
		check=0;
		while(key!=table[i].key){
			if(key<table[i].key){
				TableSize=i;
				i=check+(TableSize-check)/2;
			}
			else{
				check=i;
				i=check+(TableSize-check)/2;
			}
			if(TableSize-check==1){
				if(table[TableSize].key!=key){
					check=-1;
					printf("There isn't key %.2f",key);
					break;
				}
				else i=TableSize;
			}
		}
		if(check!=-1) printf("%f %s",table[i].key, table[i].value);
	}
	else{
		printf("Binary search doesn't work because record isn't sorted");
	}
}

int main(){
	char menu=' ', c;
	int eof, j=0, maxstring=0;
	float k;
	int TableSize = 0;
	printf("Enter name of file with keys: ");
	FILE *f1=fopen(readname(),"rt"), *f2;
	if(f1==NULL){
		printf("There is no such file");
		return -1;
	}
	printf("\nEnter name of file with values: ");
	f2=fopen(readname(), "rt");
	if(f2==NULL){
		printf("There is no such file");
		return -1;
	}
	eof=fscanf(f2,"%c", &c);
	while(eof>=0){
		if(c=='\n') {
			j++;
			TableSize++;
			if(j>maxstring) maxstring=j;
			j=0;
		}
		else j++;
		eof=fscanf(f2,"%c", &c);
	}
	if(c!='\n') TableSize++;
	j=0;
	eof=fscanf(f1,"%c", &c);
	while(eof>=0){
		if(c=='\n') {
			j++;
		}
		eof=fscanf(f1,"%c", &c);
	}
	if(c!='\n') j++;
	if(j<TableSize){
		printf("Too few keys.\nNumber of keys: %d\nNumber of values: %d\n",j, TableSize);
		return -1;
	}
	record *table=(record *)malloc(TableSize*(sizeof(record)));
	fseek(f1, 0, SEEK_SET);
	fseek(f2, 0, SEEK_SET);
	for(int i=0; i<TableSize; i++){
		table[i].value=(char *)malloc(maxstring*sizeof(char));
	}
	for(int i=0; i<TableSize; i++){
		fscanf(f1, "%f", &table[i].key);
		table[i].value=readstring(f2, maxstring, i);
	}
	fclose(f1);
	fclose(f2);
	printf("	m - Mix records\n\
	r - Reverse records\n\
	s - Sort records\n\
	p - Print records\n\
	b - Binary search by the key\n\
	q -Quit\n");
	while(menu!='q'){
		if(menu!='\n')printf("Enter operation:");
		scanf("%c", &menu);
		switch(menu){
			case 'm':
				mix(table, TableSize);
				PrintTable(table, TableSize);
				break;
			case 'r':
				reverse(table, TableSize);
				PrintTable(table, TableSize);
				break;
			case 's':
				InsertionSort(table, TableSize);
				PrintTable(table, TableSize);
				break;
			case 'b':
				bs(table, TableSize);
				break;
			case 'p':
				PrintTable(table, TableSize);
				break;
		}
		if(menu!='\n') printf("\n\n");
	}
}
