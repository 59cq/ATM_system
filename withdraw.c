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
        msgrcv(msgid_cs,&msg,sizeof(Msgbuf),MSG_WITHDRAW,0);
        printf("withdraw\n");
        ack.mtype = msg.pid;
        use.userid = msg.userid;
        if(!load(&use)){
            ack.tf = false;
            strcpy(ack.msg,"no account");
        }else{
            if(use.money < msg.money){
                ack.tf = false;
                strcpy(ack.msg,"Insufficient Golds");
            }else{
                use.money -= msg.money;
                save(&use);
                strcpy(ack.msg,"Your money, Take it");
            }
        }

        msgsnd(msgid_sc,&ack,sizeof(Ackbuf)-sizeof(ack.mtype),0);


    }


}