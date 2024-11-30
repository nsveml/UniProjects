#include "unistd.h"
#include "stdio.h"
#include"stdlib.h"

int get_line(char* string, int size){
    char c;
    int n=0;
    while(read(STDIN_FILENO, &c, 1)>0){
        if((c!='\n')&&(n<size)){
        string[n]=c;
        n++;
        }
        else break;
    }
}

int main(){	
    const int MAX_CHAR=256;
    int parenttochild1[2], child1tochild2[2], child2toparent[2];
    const char *child1 = "child1", *child2="child2";
    int std_out = fileno(stdout);
	int std_in = fileno(stdin);
	pipe(parenttochild1);
    pipe(child1tochild2);
    pipe(child2toparent);
    
    int id = fork();
    if(id == -1){
        printf("child1 fork error");
        return -1;
    }else if(id == 0 ){//child1
        close(child2toparent[1]);
        close(child2toparent[0]);
        close(parenttochild1[1]);
		close(child1tochild2[0]);
		if (dup2(parenttochild1[0], std_in) == -1) {
			printf("error copying descriptor to child1's stdin\n");
			return -1;
		}
		if (dup2(child1tochild2[1], std_out) == -1) {
			printf("error copying descriptor to child1's stdout");
			return -1;
		}
		if (execl(child1, child1, NULL) == -1) {
			printf("Failed to exec\n");
			close(parenttochild1[0]);
			close(child1tochild2[1]);
			return -1;
		}
    }
    else{
        int di=fork();
        if(di == -1){
            printf("child2 fork error");
            return -1;
        }
        else if(di == 0){//child2
            close(parenttochild1[1]);
            close(parenttochild1[0]);
            close(child1tochild2[1]);
		    close(child2toparent[0]);
		    if (dup2(child1tochild2[0], std_in) == -1) {
		    	printf("error copying descriptor to child2's stdin\n");
		    	return -1;
		    }
		    if (dup2(child2toparent[1], std_out) == -1) {
		    	printf("error copying descriptor to child2's stdout");
		    	return -1;
		    }
		    if (execl(child2, child2, NULL) == -1) {
		    	printf("Failed to exec\n");
		    	close(child1tochild2[0]);
		    	close(child2toparent[1]);
		    	return -1;
		    }
        }
        else{//parent
            close(parenttochild1[0]);
            close(child2toparent[1]);
            char string[MAX_CHAR];
            //printf("here?");
            while(get_line(string, MAX_CHAR)>0){
                //printf("i get here ");
                write(parenttochild1[1], string, MAX_CHAR);
                //printf("and here ");
                read(child2toparent[0], string, MAX_CHAR);
                //printf("but not here");
                printf("%s\n",string);
            }
            //printf("here i come");
        }
    }    
    
	return 0;
}