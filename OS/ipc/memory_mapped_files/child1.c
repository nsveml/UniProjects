#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>  
#include <fcntl.h>
#include <errno.h>


int touppercase(char *string){
    int i=0;
    while(string[i]!=0){
        if((string[i]>='a')&&(string[i]<='z')) string[i]+='A'-'a';
        i++;
    }
}

int main(int argc, char*argv[]){
    char* mem_map_file = argv[1];
    int fd = shm_open(mem_map_file, O_RDWR, S_IRWXU);
    if (errno == EACCES) {
        printf("EACCES\n");
    }
    int page_size = sysconf(_SC_PAGE_SIZE);
    if (ftruncate(fd, page_size) == -1) {
        perror("ftruncate failure\n");
        return 0;
    }
    void* sh_file = mmap(0, page_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    sem_t* parent = sh_file;
    sem_t* child1 = sh_file + sizeof(sem_t);
    sem_t* child2 = sh_file + 2 * sizeof(sem_t);
    char* string_shared = sh_file + sizeof(sem_t) * 3;
    string_shared[0] = 0;


    const int MAX_CHAR= 256;
    char string[MAX_CHAR];
    while(1){
        sem_wait(child1);
        if(string_shared[0] == -1){
            break;
        }
        else if(string_shared[0]>0){
            touppercase(string_shared);
        }
        sem_post(child2);
    }
    sem_close(parent);
    sem_close(child2);
    sem_close(child1);
    return 0;
}