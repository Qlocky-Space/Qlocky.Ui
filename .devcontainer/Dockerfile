FROM ubuntu:plucky

# Update system and add the packages required for Yocto builds.
# Use DEBIAN_FRONTEND=noninteractive, to avoid image build hang waiting
# for a default confirmation [Y/n] at some configurations.
ENV DEBIAN_FRONTEND=noninteractive

# tools for generic development
RUN apt update && apt -y install \
    clang-format clang-tidy \
    wget git-core build-essential ninja-build \
    gdb cmake python3 \
    libstdc++-13-dev

# tools for application
RUN apt update && apt -y install \
    qt6-base-dev \
    qt6-declarative-dev qt6-declarative-dev-tools \
    qt6-multimedia-dev qt6-shadertools-dev \
    qt6-virtualkeyboard-dev \
    qt6-tools-dev qt6-tools-dev-tools \
    libxkbcommon-dev libxkbcommon-x11-dev \
    libgl1-mesa-dev libboost-all-dev \
    librocksdb-dev libssl-dev \
    libpulse-dev \
    libpulse0 pulseaudio-utils \
    gstreamer1.0-plugins-base \
    gstreamer1.0-plugins-good \
    gstreamer1.0-plugins-bad \
    gstreamer1.0-libav

# Git configuration
RUN git config --global --add safe.directory /workspaces/build/_deps/*

# Ensure gdb has correct formatter for debugging c++ variables
COPY .devcontainer/gdbinit /home/ubuntu/.gdbinit

# Update Path for QT dev tool applications
ENV PATH="$PATH:/opt/qt/6.8.1/gcc_64/bin"