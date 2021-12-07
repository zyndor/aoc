#!/bin/sh
g++ $1 --std=c++17 -I$(dirname $0) -Wall -Wfatal-errors $CXXFLAGS
