#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>



int main(){
    shmget(IPC_PRIVATE,1,0);
    semget(IPC_PRIVATE,1,0);
    msgget(IPC_PRIVATE,0);
}