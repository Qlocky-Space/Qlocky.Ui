#!/bin/bash

# Check if QLOCKY_APP_PATH argument is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <APP_PATH>"
    exit 1
fi

# Assign the QLOCKY_APP_PATH argument to the variable
APP_PATH="$1"

# Function to stop QlockyApp if already running
stop_app() {
    echo "Checking if App is running on the remote target..."
    pid=$(ssh ${REMOTE_USER}@${REMOTE_HOST} "pgrep -f ${APP_PATH}")

    if [ -n "$pid" ]; then
        echo "App is running (PID: $pid). Stopping the application..."
        ssh ${REMOTE_USER}@${REMOTE_HOST} "kill -9 $pid"
        if [ $? -eq 0 ]; then
            echo "App stopped successfully."
        else
            echo "Failed to stop App. Exiting..."
            exit 1
        fi
    else
        echo "App is not running."
    fi
}

# Function to start App on the remote target
start_app() {
    echo "Starting $APP_PATH on remote target..."
    # workaround using WAYLAND_DISPLAY because otherwise environemnt variable is not loaded
    ssh ${REMOTE_USER}@${REMOTE_HOST} "WAYLAND_DISPLAY=/run/wayland-0 gdbserver :2000 \"$APP_PATH\""
    if [ $? -eq 0 ]; then
        echo "App started successfully on ${REMOTE_HOST}."
    else
        echo "Failed to start App on ${REMOTE_HOST}. Exiting..."
        exit 1
    fi
}

# Function to copy the debug artifact from remote to local with a timeout
deploy_app() {
    echo "Copying debug artifact to remote target..."
    scp /workspaces/build/QlockyApp ${REMOTE_USER}@${REMOTE_HOST}:$APP_PATH

    if [ $? -eq 0 ]; then
        echo "Debug artifact copied successfully."
    elif [ $? -eq 124 ]; then
        echo "SCP timed out. Exiting..."
        exit 1
    else
        echo "Failed to copy debug artifact. Exiting..."
        exit 1
    fi
}

stop_app
deploy_app
start_app
