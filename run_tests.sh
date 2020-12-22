#!/bin/bash
./server/grpc-server&
./client/grpc-client 10
./client/health-check Health AddressBook
pkill grpc-server
