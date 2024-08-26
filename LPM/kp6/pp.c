#include "κο6.h"

int main(){
	char a[5];
	scanf("%c.%c.",a);
	printf("%c",(char)3);
	printf("%d",a[1]);
	int k=-1;
	record rec,re;
	rec.number=1;
	scanf("%s %s %c %d", rec.lname, rec.inert, &rec.sex, &rec.group);
	printf("%s %s %c %d\n", rec.lname, rec.inert, rec.sex, rec.group);
	for(int i=0; i<6; i++) rec.grades[i]=i;
	printrec(rec);
	
	char *name=readname();
	FILE *file=fopen(name,"ab");
	
	for(int i=0; i<6;i++){
		rec.number=i;
		fwrite(&rec,sizeof(record),1,file);
	}
	
	fclose(file);
	
	file=fopen(name,"rb");
	while(fread(&re,sizeof(record),1,file)) {
		printrec(re);
		k=re.number;
	}
	printf("%d",k);
	fclose(file);
}
