/* Code borrowed from hiredis examples */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "hiredis/hiredis.h"
#include "hiredis/async.h"
#include "hiredis/adapters/ae.h"

static aeEventLoop *loop;

void getCallback2(redisAsyncContext *c, void *r, void *privdata) {
    redisReply *reply = r;
    if (reply == NULL) return;
    printf("argv[%s]: %s\n", (char*)privdata, reply->str);

    redisAsyncDisconnect(c);
}

void getCallback1(redisAsyncContext *c, void *r, void *privdata) {
    redisReply *reply = r;
    if (reply == NULL) return;
    printf("argv[%s]: %s\n", (char*)privdata, reply->str);

    redisAsyncCommand(c, NULL, NULL, "HINCRBY key field %d", 5 );
    redisAsyncCommand(c, NULL, NULL, "HINCRBY key field %d", 5 );
    redisAsyncCommand(c, NULL, NULL, "HINCRBY key field %d", 5 );
    redisAsyncCommand(c, getCallback2, (char *)"end", "HGET key field");
}

void connectCallback(const redisAsyncContext *c) {
    ((void)c);
    printf("connected...\n");
}

void disconnectCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
        printf("Error: %s\n", c->errstr);
    }
    printf("disconnected...\n");
    aeStop(loop);
}

int main ( int argc, char *argv[] ) {
    signal(SIGPIPE, SIG_IGN);

    redisAsyncContext *c = redisAsyncConnect("127.0.0.1", 6379);
    if (c->err) {
        /* Let *c leak for now... */
        printf("Error: %s\n", c->errstr);
        return 1;
    }

    loop = aeCreateEventLoop();
    redisAeAttach(loop, c);
    redisAsyncSetConnectCallback(c,connectCallback);
    redisAsyncSetDisconnectCallback(c,disconnectCallback);
    redisAsyncCommand(c, NULL, NULL, "HSET key field %d", 0 );
    redisAsyncCommand(c, NULL, NULL, "HINCRBY key field %d", 5 );
    redisAsyncCommand(c, NULL, NULL, "HINCRBY key field %d", 5 );
    redisAsyncCommand(c, getCallback1, (char *)"end", "HGET key field");
    aeMain(loop);
    return 0;
}
