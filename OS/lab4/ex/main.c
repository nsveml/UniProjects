#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>  
#include <fcntl.h>
#include <errno.h>
int main()
{
    const int MAX_STR_SIZE = 256;
	char filename[MAX_STR_SIZE];
    const char* child_executable_name = "child";
    char string_local[MAX_STR_SIZE];
	char* mem_name = "memchunk";
	scanf ("%s", filename);
    int fd = shm_open(mem_name, O_CREAT| O_RDWR, S_IRWXU);
    if (fd < 0) {
        printf("shm_open failed\n");
        return 0;
    }
    int pg_size = sysconf(_SC_PAGE_SIZE);
    if (ftruncate(fd, pg_size) == -1) {
        perror("ftruncate failure\n");
        return 0;
    }
    void* sh_file = mmap(0, pg_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    sem_t* sem_par = sh_file;
    sem_t* sem_chil = sh_file + sizeof(sem_t);
    sem_init(sem_par, 1, 1);
    sem_init(sem_chil, 1, 0);
    char* string_shared = sh_file + sizeof(sem_t) * 2;
    string_shared[0] = 0;
    int id = fork();
    if (id == -1) {
        printf("Fork error\n");
        return 0;
    }
    if (id == 0) {
        if (execl(child_executable_name, child_executable_name, filename, mem_name, NULL) == -1) {
            printf("Failed to exec\n");
            return -1;
        } 
        return 0;
    }
    
    while (scanf("%s", string_local) > 0) {
        sem_wait(sem_par);
        int i = 0;
        while(string_local[i] > 0){
            string_shared[i] = string_local[i];
            ++i;
        }
        string_shared[i] = string_local[i];
        sem_post(sem_chil);
    }
    string_shared[0] = -1;
    sem_post(sem_chil);
    shm_unlink(mem_name);
    sem_close(sem_par);
    sem_close(sem_chil);
	return 0;
}