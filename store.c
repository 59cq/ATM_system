#include "msg_queue.h"
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>

int main(){

    int msgid_sc = getmsgid_sc();
    int msgid_cs = getmsgid_cs();
    Ackbuf ack;
    Msgbuf msg;
    User use;
    while(1){
        msgrcv(msgid_cs,&msg,sizeof(Msgbuf),MSG_STORE,0);
        printf("store\n");
        ack.mtype = msg.pid;
        use.userid = msg.userid;

        if(!load(&use)){
            ack.tf = false;
            strcpy(ack.msg,"load error");
        }else{
            use.money += msg.money;
            if(!save(&use)){
                ack.tf = false;
                strcpy(ack.msg,"save error");
            }else{
                ack.tf = true;
                strcpy(ack.msg,"store success");
            }
        }

        msgsnd(msgid_sc,&ack,sizeof(Ackbuf)-sizeof(ack.mtype),0);


    }


}