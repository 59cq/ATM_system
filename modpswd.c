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
        msgrcv(msgid_cs,&msg,sizeof(Msgbuf),MSG_MODPSWD,0);
        printf("query\n");
        ack.mtype = msg.pid;
        use.userid = msg.userid;
        if(!load(&use)){
            ack.tf = false;
            strcpy(ack.msg,"no account");
        }else{
            strcpy(use.pswd,msg.pswd);
            if(!save(&use)){
                ack.tf = false;
                strcpy(ack.msg,"savedata error");
            }else{
                ack.tf = true;
                strcpy(ack.msg,"modify success");
            }
        }

        msgsnd(msgid_sc,&ack,sizeof(Ackbuf)-sizeof(ack.mtype),0);


    }


}