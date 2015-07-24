#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <msgpack.hpp>
#include "hiredis/hiredis.h"
#include "hiredis/async.h"
#include "hiredis/adapters/libevent.h"

using namespace std;
using namespace msgpack;

int main()
{
    redisContext *c;
    void *reply;
    c = redisConnect("127.0.0.1", 6379);
    if(c!=NULL && c->err) {
        printf("Error: %s\n", c->errstr);
    }

    char str[] = "Hello World!!";
    vector<unsigned char> data;
    for (unsigned i = 0; i < 10; ++i)
        data.push_back(i * 2);
    cout << "The size of array 'data' is: "<<sizeof(str)<<endl;
    sbuffer sbuf;
    //string text = std::to_string(pack(sbuf, str));
    pack(sbuf, data);
    //pack(sbuf, str);
    cout << "The size of packed is: " << sbuf.size() <<endl;

    reply = redisCommand(c,"SET %s %s", "foo", sbuf.data());
    void *size = redisCommand(c, "DBSIZE");
    int size_of_db = *((int *)size);
    cout << "The size of key in RedisDB is: "<< size_of_db << endl;
    //void *al = redisCommand(c,"SET %s %s", to_string(size_of_db), "Aa");
    //printf("SET: %s\n", reply->str);
    freeReplyObject(reply);

    //void *bl = redisCommand(c,"GET foo");
    string getstr = "GET ";
    getstr = getstr + to_String(size_of_db);
    reply = redisCommand(c, getstr);
    //printf("GET foo: %s\n", reply->str);
    freeReplyObject(reply);
    redisFree(c);
    return 0;

    unpacked msg;
    unpack(&msg, sbuf.data(), sbuf.size());

    object obj = msg.get();
    cout<<"The size of unpacked object is: "<<sizeof(obj)<<endl;
    cout << "The object is: "<<endl;
    cout << obj << endl;

}
