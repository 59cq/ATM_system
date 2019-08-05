#include "msg_queue.h"
#include "mytypes.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>

static int msgid_sc;
static int msgid_cs;
static pid_t sub_pid[9];

void sigint_closemsgque(int signum){
    msgctl(msgid_cs,IPC_RMID,NULL);
    msgctl(msgid_sc,IPC_RMID,NULL);
    int i;
    for(i=0;i<9;i++){
        kill(sub_pid[i],SIGINT);
    }
}



int main(){
    signal(SIGINT,sigint_closemsgque);
    //创建消息队列
    msgid_cs = creat_msgid_cs();
    msgid_sc = creat_msgid_sc();

	sub_pid[0] = vfork();
	if(0 == sub_pid[0])
	{
		execl("open","open",NULL);
        exit(0);
	}

	sub_pid[1] = vfork();
	if(0 == sub_pid[1])
	{
		execl("destroy","destroy",NULL);
        exit(0);
	}
    
	sub_pid[2] = vfork();
	if(0 == sub_pid[2])
	{
		execl("unlock","unlock",NULL);
        exit(0);
	}
	
	sub_pid[3] = vfork();
	if(0 == sub_pid[3])
	{
		execl("login","login",NULL);
        exit(0);
	}
	
	sub_pid[4] = vfork();
	if(0 == sub_pid[4])
	{
		execl("store","store",NULL);
        exit(0);
	}

	sub_pid[5] = vfork();
	if(0 == sub_pid[5])
	{
		execl("withdraw","withdraw",NULL);
        exit(0);
	}
    
	sub_pid[6] = vfork();
	if(0 == sub_pid[6])
	{
		execl("query","query",NULL);
        exit(0);
	}

	sub_pid[7] = vfork();
	if(0 == sub_pid[7])
	{
		execl("transfer","transfer",NULL);
        exit(0);
	}

	sub_pid[8] = vfork();
	if(0 == sub_pid[8])
	{
		execl("modpswd","modpswd",NULL);
        exit(0);
	}
	while(-1 != wait(NULL));




}

