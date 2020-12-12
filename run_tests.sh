#!/bin/bash
./server/grpc-server&
./client/grpc-client 10
pkill grpc-server
