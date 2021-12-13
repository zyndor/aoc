#!/bin/bash
ext=${1##*.}

case $ext in
	cpp)
	g++ $1 --std=c++17 -I$(dirname $0) -Wall -Wfatal-errors $CXXFLAGS
	;;

	cs)
	mcs $1 -out:a.out
	;;

	*)
	echo Failed to match extension: $ext
	exit 1
	;;
esac
