#include "mytypes.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include <getch.h>
#include <fcntl.h>
#include "msg_queue.h"
#include "tools.h"





int main(){
    int msgid_cs = getmsgid_cs();
    int msgid_sc = getmsgid_sc();
    Ackbuf ack;
    Msgbuf msg;
    User use_o;
    User use_d; 
    while(1){

        //收client消息
        msgrcv(msgid_cs,&msg,sizeof(Msgbuf),MSG_TRANSFER,0);
        printf("transfer\n");
        ack.mtype = msg.pid;
        use_o.userid = msg.userid;
        use_d.userid = msg.toid;

        //读取两个账户信息
        if(!load(&use_o)||!load(&use_d)){
            ack.tf = false;
            strcpy(ack.msg,"load error");
        }else{
            if(use_o.money < msg.money){
                ack.tf = false;
                strcpy(ack.msg,"insufficient Golds");
            }else{
                use_o.money -= msg.money;
                use_d.money += msg.money;
                if(!save(&use_o)||!save(&use_d)){
                    //只有一方失败需要数据回滚,不会..
                    ack.tf = false;
                    strcpy(ack.msg,"save error");
                }else{
                    ack.tf = true;
                    strcpy(ack.msg,"transfer success");
                }
            }
        }
        msgsnd(msgid_sc,&ack,sizeof(Ackbuf)-sizeof(ack.mtype),0);
    }
}
 
