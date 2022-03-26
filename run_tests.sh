#!/bin/bash
./examples/server/grpc-server &
sleep 1
./examples/client/grpc-client 10 &
./examples/client/health-check ""
pkill grpc-server
