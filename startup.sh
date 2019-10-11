#!/bin/bash

# Runs your server executable in background
./build/comm &

# Gets the PID of proccess
RUN_ME_PID=$!

# Sleeps how much time you need:
sleep 10s 

# Kills the process:
kill -9 $RUN_ME_PID

# enjoy life!