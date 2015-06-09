#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "hiredis/hiredis.h"
#include "hiredis/async.h"
#include "hiredis/adapters/libevent.h"

int main(){
redisContext *c;
redisReply *reply;
c = redisConnect("127.0.0.1", 6379);
if(c!=NULL && c->err){
	printf("Error: %s\n", c->errstr);
}
reply = redisCommand(c,"SET %s %s", "foo", "hello world");
printf("SET: %s\n", reply->str);
freeReplyObject(reply);

reply = redisCommand(c,"GET foo");
printf("GET foo: %s\n", reply->str);
freeReplyObject(reply);
redisFree(c);
return 0;
}  
