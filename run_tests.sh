#!/bin/bash
./server/grpc-server &
./client/grpc-client 10 &
./client/health-check ""
pkill grpc-server
