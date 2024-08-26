#ifndef DB_H
#define DB_H
#include <stdio.h>
#include <stdlib.h>

typedef struct record record;
typedef struct lst lst;

struct record{
	int number;
	char lname[80];
	char inert[6];
	char sex;
	int group;
	int grades[6];
};

int eq(char* a, char* b){
	int i=0,j=0,l=1;
	while(a[i]!='\0')i++;
	while(b[j]!='\0')j++;
	if (i==j){
		for(int k=0; k<i; k++) if(a[k]!=b[k]) l=0;
	}else l=0;
	return(l);
}

int equal(record a, record b){
	int i=0;
	if(eq(a.lname, b.lname)&&eq(a.inert, b.inert)\
	&&(a.sex==b.sex)&&(a.group==b.group))i=1;
	for(int k=0; k<6; k++) if(a.grades[k]!=b.grades[k]) i=0;
	return(i);
}

void printrec(record rec){
	printf("%d %s %s %c %d"\
	,rec.number, rec.lname, rec.inert, rec.sex, rec.group);
	for(int i=0; i<6;i++){
		printf(" %d", rec.grades[i]);
	}
	printf("\n");
}

void help(int i){
	if(i==1) printf("This program can print database, request records from it and find best female students.\n");
	else printf("This programm can create and delete databases and records in it.\n");
}

char * readname(){
	int i=0;
	char b, *a=(char*)malloc(sizeof(char)*256);
	scanf("%c",&b);
	if(b=='\n'){
		scanf("%c",&b);
	}
	while((b!='\n')&&(i!=256)){
		a[i]=b;
		i++;
		scanf("%c",&b);
	}
	a[i]='\0';
	return(a);
}

void create() {
	record rec;
	printf("Enter name of database:");
	char *name=readname();
	int i=0;
	FILE *file=fopen(name,"wb");
	if(file!=NULL)printf("Database was created");
	else printf("Database wasn't created");
	if (fclose(file)<0) printf("Wasn't closed");
	free(name);
}

void print() {
	int k;
	record rec;
	printf("Enter name of database:");
	char *name = readname();
	int i;
	FILE * file = fopen(name,"rb");
	if(file!=NULL){
		while(fread(&rec,sizeof(record),1,file)) printrec(rec);
		k=fclose(file);
		free(name);
	}
	else printf("Database wasn't created");
}

void add() {
	record rec;
	printf("Enter name of database:");
	char *name=readname();
	int k=0;
	FILE *file=fopen(name,"rb");
	if(file!=NULL){while(fread(&rec,sizeof(record),1,file)) k=rec.number;
	fclose(file);
	rec.number=k+1;
	file=fopen(name,"ab");
	printf("Record should have this structure:\n\
	[last name] [initials] [sex] [number of cgroup] [grade 1] ... [grade 6]\n\
Enter record:");
	scanf("%s %s %c %d",rec.lname,rec.inert, &rec.sex, &rec.group);
	rec.inert[5]='\0';
	for(int i=0; i<6;i++){
		scanf("%d",&rec.grades[i]);
	}
	printrec(rec);
	fwrite(&rec,sizeof(record),1,file);
	if(fclose(file)<0) printf("Wasn't closed");
	free(name);
	}
	else printf("This database wasn't created.");
}

void delall() {
	record rec;
	printf("Enter name of database:");
	char *name=readname();
	int i=0;
	remove(name);
	FILE *f=fopen(name,"rb");
	if(f==NULL) printf("Data base was deleted");
	else printf("Database wasn't deleted");
	free(name);
}

int * increase(int * a, int k){
	int *b=(int*)malloc((k+10)*sizeof(int));
	for(int i; i<k; i++){
		b[i]=a[i];
	}
	return(b);
}

int findgroup(int * groups, int group, int k){
	int i=0;
	while((groups[i]!=group)&&(i<k)) i++;
	if(groups[i]!=group)i=-1;
	return(i);
}

void var16() {
	record rec;
	printf("Enter name of database:");
	char *name = readname();
	int i=-1,k=10,g;
	int *groups, *grades;
	groups=(int*)malloc(sizeof(int)*10);
	grades=(int*)malloc(sizeof(int)*10);
	FILE *file=fopen(name,"rb");
	if(file!=NULL){
		while(fread(&rec,sizeof(record),1,file)){
			g=findgroup(groups, rec.group, k);
			if(g<0) {
				i++;
				groups[i]=rec.group;
				grades[i]=0;
				g=i;
				if(i+1==k){
					groups=increase(groups, k);
					grades=increase(grades, k);
					k+=10;
				}
			}
			for(int j=1; j<6;j++) rec.grades[0]+=rec.grades[j];
			if(rec.grades[0]>grades[g]) grades[g]=rec.grades[0];
		}
		fseek(file, 0, SEEK_SET);
		while(fread(&rec,sizeof(record),1,file)){
			i=0;
			g=findgroup(groups, rec.group, k);
			for(int j=1; j<6; j++){
				rec.grades[0]+=rec.grades[j];
				if (rec.grades[j]<4) i=1;
			}
			if((i==0)&&(rec.grades[0]>=grades[g])&&\
			((rec.sex=='F')||(rec.sex=='f')))\
			printf("%s\n", rec.lname);
		}
		fclose(file);
		free(name);
	}
	else printf("This file wasn't created");
	
}

struct lst{
	int *list;
	int l;
	int j;
};

lst request(char *name) {
	record rec;
	lst L;
	L.list=(int*)malloc(10*sizeof(int));
	L.l=9;
	L.j=0;
	int i=0, n=0, v=0;
	char p;
	FILE *file=fopen(name,"rb");
	if(file!=NULL){
			printf("Parameters:\ng - Grades\n\
l - lname\ni - initials\nn - number\n\
s - Sex\nG - Group\nEnter type of parameter:");
		scanf("%c",&p);
		switch(p){
			case 'l':
				printf("Enter student's name:");
				name=readname();
				i=1;
				break;
			case 'g':
				i=2;
				printf("Enter subject's number:");
				scanf("%d",&n);
				printf("Enter value:");
				scanf("%d",&v);
				break;
			case 'i':
				i=3;
				printf("Enter student's initials:");
				name=readname();
				break;
			case 'n':
				i=4;
				printf("Enter student's number:");
				scanf("%d",&n);
				break;
			case 's':
				i=5;
				printf("Enter student's sex (F or M):");
				scanf("\n%c",&p);
				break;
			case 'G':
				i=6;
				printf("Enter group's number:");
				scanf("%d",&n);
				break;
		}
		while(fread(&rec,sizeof(record),1,file)){
			if(L.l==L.j){
				L.list=increase(L.list, L.l);
				L.l+=10;
			}
			switch(i){
				case 1:
					if(eq(name, rec.lname)){
						L.list[L.j]=rec.number;
						L.j++;
					}
					break;
				case 2:
					if(rec.grades[n-1]==v){
						L.list[L.j]=rec.number;
						L.j++;
					}
					break;
				case 3:
					if(eq(name, rec.inert)){
						L.list[L.j]=rec.number;
						L.j++;
					}
					break;
				case 4:
					if(n==rec.number){
						L.list[L.j]=rec.number;
						L.j++;
					}
					break;
				case 5:
					if(p==rec.sex){
						L.list[L.j]=rec.number;
						L.j++;
					}
					break;
				case 6:
					if(n==rec.group){
						L.list[L.j]=rec.number;
						L.j++;
					}
					break;
			}
		}
		fclose(file);
	}
	else printf("Database wasn't created");
	return L;
}

void printlist(int * list, int l){
	for(int i=0; i<l; i++){
		printf("%d ",list[i]);
	}
	printf("\n");
}

void req(){
	int i=0;
	record rec;
	printf("Enter name of database:");
	char* name=readname();
	FILE *file=fopen(name,"rb");
	if(file!=NULL){
		fclose(file);
		lst L=request(name);
		file=fopen(name,"rb");
		while(fread(&rec,sizeof(record),1,file)){
			if((rec.number==L.list[i])&&(i<=L.j)){
				i++;
				printrec(rec);
			}
		}
		free(name);
		free(L.list);
		fclose(file);
	}
	else printf("File wasn't created");

}

void del() {
	record rec;
	rec.number=0;
	printf("Enter name of database:");
	char *name = readname();
	int i=0, j=0;
	char q;
	lst L=request(name);
	FILE *file=fopen(name,"rb");
	if(file!=NULL){
		FILE *tmp=tmpfile();
		while(fread(&rec, sizeof(record),1,file)){
			if(rec.number==L.list[j]){
				printrec(rec);
				printf("Do you want to delete this record? (Y or N)");
				scanf("\n%c", &q);
				printf("%c",q);
				if(q=='Y') {
					printf("continue");
					continue;
				}
				if(j<L.j)j++;
			}
			i++;
			rec.number=i;
			fwrite(&rec, sizeof(record),1,tmp);
		}
		fclose(file);
		rewind(tmp);
		file=fopen(name,"wb");
		while(fread(&rec, sizeof(record),1,tmp)){
			fwrite(&rec,sizeof(record),1,file);
		}
		fclose(file);
		fclose(tmp);
		free(name);
	}
	else printf("Database wasn't created");
}

#endif
