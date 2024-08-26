#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>  
#include <fcntl.h>
#include <errno.h>


int get_line(char* string, int size){
    char c;
    int n=0;
    while(read(STDIN_FILENO, &c, 1)>0){
        if((c!='\n')&&(n<size)){
        string[n]=c;
        n++;
        }
        else {
            string[n]='\0';
            break;
        }
    }
    return n;
}

int main(){	
    const int MAX_CHAR=256;
    char* mem_map_file = "memmap";
    int fd = shm_open(mem_map_file, O_CREAT | O_RDWR, S_IRWXU);
    if (fd < 0) {
        printf("can't open shared memmory segmeтt\n");
        return 0;
    }
    int page_size = sysconf(_SC_PAGE_SIZE);
    if(ftruncate(fd, page_size) == -1){
        perror("ftruncate fail\n");
        return 0;
    }
    const char *child1_name = "child1", *child2_name="child2";
    void* sh_file = mmap(0, page_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    sem_t* parent = sh_file;
    sem_t* child1 = sh_file + sizeof(sem_t);
    sem_t* child2 = sh_file + 2 * sizeof(sem_t);
    sem_init(parent, 1, 1);
    sem_init(child1, 1, 0);
    sem_init(child2, 1, 0);
    char* string_shared = sh_file + sizeof(sem_t) * 3;
    string_shared[0] = 0;


    int id = fork();
    if(id == -1){
        printf("child1 fork error");
        return -1;
    }else if(id == 0 ){//child1
		if (execl(child1_name, child1_name, mem_map_file, NULL) == -1) {
			printf("Failed to exec\n");
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
		    if (execl(child2_name, child2_name, mem_map_file, NULL) == -1) {
		    	printf("Failed to exec\n");
		    	return -1;
		    }
        }
        else{//parent
            char string[MAX_CHAR];
            int i=0;
            while(get_line(string, MAX_CHAR)>0){
                sem_wait(parent);
                i=0;
                while(string[i]!=0){
                    string_shared[i]=string[i];
                    i++;
                }
                string_shared[i]=string[i];
                sem_post(child1);
            }
            string_shared[0]=-1;
            sem_post(child1);
            sem_post(child2);
            sem_close(parent);
            sem_close(child1);
            sem_close(child2);
            shm_unlink(mem_map_file);
        }
    }    
	return 0;
}