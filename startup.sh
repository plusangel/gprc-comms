#!/bin/bash

# Runs your runme.sh in background
./build/server &

# Gets the PID of runme.sh
RUN_ME_PID=$!

# Sleeps how much time you need:
sleep 10s 

# Kills the process:
kill -9 $RUN_ME_PID