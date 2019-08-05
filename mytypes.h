#ifndef MYTYPES_H
#define MYTYPES_H

#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

#define keysc 123
#define keycs 321


#define MSG_OPEN        111L
#define MSG_DESTROY     112L
#define MSG_UNLOCK      113L
#define MSG_LOGIN       114L
#define MSG_STORE       115L
#define MSG_WITHDRAW    116L
#define MSG_TRANSFER    117L
#define MSG_QUERY       118L
#define MSG_MODPSWD     119L



typedef struct User{
	char lock;
	long userid;
	char id[20];
	char pswd[20];
	double money;
}User;

typedef struct Msgbuf{
	long mtype;
	pid_t pid;
    long userid;
	char pswd[20];
    long toid;
    char id[20];
    int times;
    double money;
}Msgbuf;

typedef struct Ackbuf{
    long mtype;
    pid_t pid;
    bool tf;
    char msg[20];
}Ackbuf;











#endif
