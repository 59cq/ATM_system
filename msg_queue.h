#ifndef MSG_QUEUE_H
#define MSG_QUEUE_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include "mytypes.h"



int getmsgid_sc();
int getmsgid_cs();
int creat_msgid_cs();
int creat_msgid_sc();


#endif//MSG_QUEUE_H