#!/bin/bash

echo "Starting..."

# Runs your server executable in background
./build/comm &

# Gets the PID of proccess
RUN_ME_PID=$!

declare -i time=30
echo "Spinning for $time seconds"

# Sleeps how much time you need:
sleep $time

echo "Terminating..."

# Kills the process:
kill -9 $RUN_ME_PID

echo "enjoy life!"