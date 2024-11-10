#define KEYFORSERVER 0x1

struct mymsgN {
    long mtype;//id della coda di messaggi dove inviare il messaggio
    char mtext[256];
};