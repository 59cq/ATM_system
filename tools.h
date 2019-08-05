#ifndef TOOLS_H
#define TOOLS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include "msg_queue.h"
#include "mytypes.h"



bool add(User* use);
bool load(User* use);
bool save(User* use);
bool delete(long userid);




#endif//TOOLS_H