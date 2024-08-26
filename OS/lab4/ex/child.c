#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>  
#include <fcntl.h>
#include <errno.h>

const int MAX_STR_SIZE = 256;
int rule(char* str) {
    if (str[0] >= 'A' && str[0] <= 'Z') {
        return 1;
    }
    return 0;
}
int main(int argc, char* argv[]){
    FILE *file = fopen(argv[1], "w");
    if (file == NULL){
        printf("fopen error\n");
        return -1;
    }
    char* mem_name = argv[2];
    int fd = shm_open(mem_name, O_RDWR, S_IRWXU);
    if (errno == EACCES) {
        printf("EACCES\n");
    }
    if (fd < 0) {
        printf("Fucker\n");
        return 0;
    }
    int pg_size = sysconf(_SC_PAGE_SIZE);
    if (ftruncate(fd, pg_size) == -1) {
        perror("ftruncate failure\n");
        return 0;
    }
    void* sh_file = mmap(0, pg_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    sem_t* sem_par = sh_file;
    sem_t* sem_chil = sh_file + sizeof(sem_t);
    char* string_shared = sh_file + sizeof(sem_t) * 2;
    string_shared[0] = 0;
    while (1){
        sem_wait(sem_chil);
        if (string_shared[0] == -1) {
            break;
        }
        if (string_shared[0] != 0) {
            if (rule(string_shared)) {
                printf ("%s\n", string_shared);
                fwrite (string_shared, 1, strlen(string_shared), file);
                fwrite ("\n", 1, 1, file);
            }
            else {
                printf ("%s does not begin with capital\n", string_shared);
            }
        }
        sem_post(sem_par); 
    }
    sem_close(sem_par);
    sem_close(sem_chil);
    fclose(file);
    return 0;
}