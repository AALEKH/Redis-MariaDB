# Redis-Mysql
Test Code for Redis interaction with C/C++. 

## To run example.c:
* gcc example.c -lhiredis -levent -std=c99

## To run allCluster.cpp:
* g++ allCluster.cpp -std=gnu++11 -lhiredis -levent -o atg
* ./atg

## To run redis.c
* gcc redis.c -lhiredis -levent -std=c99

## Dependencies
* [Hiredis](https://github.com/redis/hiredis)
This library provides basic support for running Redis over C/C++. **example.c** and **redis.c** are the two files that demostrate working of redis over c.

* [cpp-hiredis-cluster](https://github.com/AALEKH/cpp-hiredis-cluster.git)
This library (coupled with hiredis) is required for Redis-Cluster support for C/C++. **allCluster.cpp** file         demostrated a simple implementation Redis-Cluster.

* [Redis](http://redis.io)
