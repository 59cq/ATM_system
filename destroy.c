#include "msg_queue.h"
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
        msgrcv(msgid_cs,&msg,sizeof(Msgbuf),MSG_DESTROY,0);
        ack.mtype = msg.pid;

        use.userid = msg.userid;
        if(load(&use) == false){
            ack.tf = false;
            strcpy(ack.msg,"no this account");
        }else{
            if(0 != strcmp(use.pswd,msg.pswd)){
                ack.tf = false;
                strcpy(ack.msg,"wrong pswd");
            }else{
                if(delete(use.userid)){
                    ack.tf = true;
                    strcpy(ack.msg,"successful delete");
                }else{
                    ack.tf = false;
                    strcpy(ack.msg,"unknow wrong");
                }
            }
        }
        msgsnd(msgid_sc,&ack,sizeof(Ackbuf)-sizeof(ack.mtype),0);

    }


}