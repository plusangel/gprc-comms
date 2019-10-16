#!/bin/bash

echo "Checking the arguments..."
time=30

if [ -z "$1" ];
  then
    echo "No argument supplied - default 30 sesc"
  else 
    time=$1
    echo "Argument supplied - default $time secs"
fi

echo "Starting..."

# Runs your server executable in background
./build/serverBringup . &

# Gets the PID of proccess
RUN_ME_PID=$!

echo "Spinning for $time seconds"

# Sleeps how much time you need:
sleep $time

echo "Terminating..."

# Kills the process:
kill -9 $RUN_ME_PID

echo "enjoy life!"