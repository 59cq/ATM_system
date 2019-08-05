#include "msg_queue.h"


int creat_msgid_cs(){
    int msgid_cs = msgget(ftok(".",keycs),IPC_CREAT|IPC_EXCL|0644);
    if(0 > msgid_cs){
        perror("msgget");
        return -1;
    }
    return msgid_cs;
}

int creat_msgid_sc(){
    int msgid_sc = msgget(ftok(".",keysc),IPC_CREAT|IPC_EXCL|0644);
    if(0 > msgid_sc){
        perror("msgget");
        return -1;
    }
    return msgid_sc;
}

int getmsgid_cs(){
    int msgid_cs = msgget(ftok(".",keycs),0);
    if(0 > msgid_cs){
        perror("msgget");
        return -1;
    }
    return msgid_cs;
}

int getmsgid_sc(){
    int msgid_sc = msgget(ftok(".",keycs),0);
    if(0 > msgid_sc){
        perror("msgget");
        return -1;
    }
    return msgid_sc;

}