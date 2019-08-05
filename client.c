#include "mytypes.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include <getch.h>
#include "msg_queue.h"

void show_manu(void){
    printf("---------\n");
    printf("1.开户\n");
    printf("2.销户\n");
    printf("3.登录\n");
    printf("4.解锁\n");
    printf("5.退出\n");
}

void show_user_manu(void){
    printf("---------\n");
    printf("1.存钱\n");
    printf("2.取钱\n");
    printf("3.转账\n");
    printf("4.查询\n");
    printf("5.修改密码\n"); 
    printf("6.退出登录\n"); 
}

bool open(void);
bool destroy(void);
bool login(void);
bool unlock(void);
void user_act(void);

bool store(void);
bool withdraw(void);
bool transfer(void);
bool query(void);
bool modpswd(void);

static int msgid_cs;
static int msgid_sc;
Msgbuf msg;
Ackbuf ack;
User use;

int main(){
    //获取消息队列
    msgid_cs = getmsgid_cs();
    msgid_sc = getmsgid_sc();

    msg.pid = getpid();

    while(1){
        show_manu();
        stdin->_IO_read_end = stdin->_IO_read_ptr;
        switch(getch()){
            case 49://开户
                if(open()){
                    printf("开户成功\n");
                }else{
                    printf("开户失败\n");
                }
                break;
            case 50://销户
                if(destroy()){
                    printf("销户成功\n");
                }else{
                    printf("销户失败\n");
                }
                break;
            case 51://登录
                if(login()){
                    user_act();
                }
                break;
            case 52://解锁
                if(unlock()){
                    printf("解锁成功\n");
                }else{
                    printf("解锁失败\n");
                }
                break;
            case 53://退出
                return 0;
            default:
                break;
        }
    }
}




bool open(void){
    printf("请输入身份证号:\n");
    scanf("%s",msg.id);
    printf("请输入密码:\n");
    scanf("%s",msg.pswd);
    msg.mtype = MSG_OPEN;
    msgsnd(msgid_cs,&msg,sizeof(Msgbuf)-sizeof(msg.mtype),0);
    printf("等待服务器响应...\n");
    msgrcv(msgid_sc,&ack,sizeof(Ackbuf),getpid(),0);
    if(ack.tf == false){
        printf("%s\n",ack.msg);
        return false;
    }else{
        printf("你的账号是:%s\n",ack.msg);
        return true;
    }
}


bool destroy(void){
    printf("请输入账号:\n");
    scanf("%ld",&msg.userid);
    printf("请输入密码:\n");
    scanf("%s",msg.pswd);

    msg.mtype = MSG_DESTROY;
    msgsnd(msgid_cs,&msg,sizeof(Msgbuf)-sizeof(msg.mtype),0);
    printf("等待服务器响应...\n");
    msgrcv(msgid_sc,&ack,sizeof(Ackbuf),getpid(),0);
    if(ack.tf == false){
        printf("%s\n",ack.msg);
        return false;
    }else{
        printf("%s\n",ack.msg);
        return true;
    }
}

bool login(void){
    printf("请输入账号\n");
    scanf("%ld",&msg.userid);
    use.userid = msg.userid;
    printf("请输入密码\n");
    scanf("%s",msg.pswd);
    msg.mtype = MSG_LOGIN;
    msgsnd(msgid_cs,&msg,sizeof(Msgbuf)-sizeof(msg.mtype),0);
    printf("等待服务器响应...\n");
    msgrcv(msgid_sc,&ack,sizeof(Ackbuf),getpid(),0);
    if(ack.tf == false){
        printf("%s\n",ack.msg);
        return false;
    }else{
        printf("%s\n",ack.msg);
        return true;
    }

}

bool unlock(void){
    printf("请输入账号\n");
    scanf("%ld",&msg.userid);
    printf("请输入身份证号\n");
    scanf("%s",msg.id);
    msg.mtype = MSG_UNLOCK;
    msgsnd(msgid_cs,&msg,sizeof(Msgbuf)-sizeof(msg.mtype),0);
    printf("等待服务器响应...\n");
    msgrcv(msgid_sc,&ack,sizeof(Ackbuf),getpid(),0);
    if(ack.tf == false){
        printf("%s\n",ack.msg);
        return false;
    }else{
        printf("%s\n",ack.msg);
        return true;
    }

}

void user_act(void){
    while(1){
    show_user_manu();
    stdin->_IO_read_end = stdin->_IO_read_ptr;
        switch(getch()){
            case 49://存钱
                if(store()){

                }else{

                }
                break;
            case 50://取钱
                if(withdraw()){

                }else{

                }
                break;
            case 51://转账
                if(transfer()){

                }else{

                }
                break;
            case 52://查询
                if(query()){

                }else{

                }
                break;
            case 53://修改密码
                if(modpswd()){

                }else{

                }
                break;
            case 54://退出登录
                return;
            default:
                break;
        }
    }
}




bool store(void){
    printf("请输入要存的金额\n");
    scanf("%lf",&msg.money);
    msg.mtype = MSG_STORE;
    msg.userid = use.userid;
    printf("sandid%ld\n",msg.userid);///////////////////
    msgsnd(msgid_cs,&msg,sizeof(Msgbuf)-sizeof(msg.mtype),0);
    printf("等待服务器响应...\n");
    msgrcv(msgid_sc,&ack,sizeof(Ackbuf),getpid(),0);
    if(ack.tf == false){
        printf("%s\n",ack.msg);
        return false;
    }else{
        printf("%s\n",ack.msg);
        return true;
    }
}

bool withdraw(void){
    printf("请输入要取的金额\n");
    scanf("%lf",&msg.money);
    msg.mtype = MSG_WITHDRAW;
    msg.userid = use.userid;
    msgsnd(msgid_cs,&msg,sizeof(Msgbuf)-sizeof(msg.mtype),0);
    printf("等待服务器响应...\n");
    msgrcv(msgid_sc,&ack,sizeof(Ackbuf),getpid(),0);
    if(ack.tf == false){
        printf("%s\n",ack.msg);
        return false;
    }else{
        printf("%s\n",ack.msg);
        return true;
    }
}

bool transfer(void){
    printf("请输入对方账户\n");
    scanf("%ld",&msg.toid);
    printf("请输入转账金额\n");
    scanf("%lf",&msg.money);
    msg.mtype = MSG_TRANSFER;
    msg.userid = use.userid;
    msgsnd(msgid_cs,&msg,sizeof(Msgbuf)-sizeof(msg.mtype),0);
    printf("等待服务器响应...\n");
    msgrcv(msgid_sc,&ack,sizeof(Ackbuf),getpid(),0);
    if(ack.tf == false){
        printf("%s\n",ack.msg);
        return false;
    }else{
        printf("%s\n",ack.msg);
        return true;
    }
}

bool query(void){
    msg.mtype = MSG_QUERY;
    msg.userid = use.userid;
    msgsnd(msgid_cs,&msg,sizeof(Msgbuf)-sizeof(msg.mtype),0);
    printf("等待服务器响应...\n");
    msgrcv(msgid_sc,&ack,sizeof(Ackbuf),getpid(),0);
    if(ack.tf == false){
        printf("%s\n",ack.msg);
        return false;
    }else{
        printf("%s\n",ack.msg);
        return true;
    }
}

bool modpswd(void){
    printf("请输入新密码\n");
    scanf("%s",msg.pswd);
    msg.mtype = MSG_MODPSWD;
    msg.userid = use.userid;
    msgsnd(msgid_cs,&msg,sizeof(Msgbuf)-sizeof(msg.mtype),0);
    printf("等待服务器响应...\n");
    msgrcv(msgid_sc,&ack,sizeof(Ackbuf),getpid(),0);
    if(ack.tf == false){
        printf("%s\n",ack.msg);
        return false;
    }else{
        printf("%s\n",ack.msg);
        return true;
    }
}