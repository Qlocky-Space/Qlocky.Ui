FROM ubuntu:plucky

# Update system and add the packages required for Yocto builds.
# Use DEBIAN_FRONTEND=noninteractive, to avoid image build hang waiting
# for a default confirmation [Y/n] at some configurations.
ENV DEBIAN_FRONTEND=noninteractive

# tools for generic development
RUN apt update && apt -y install \
    clang-format clang-tidy \
    wget git-core build-essential ninja-build \
    gdb cmake python3

# tools for application
RUN apt update && apt -y install \
    qt6-base-dev qt6-declarative-dev-tools \
    libgl1-mesa-dev libboost-all-dev \
    librocksdb-dev


# Git configuration
RUN git config --global --add safe.directory /workspaces/build/_deps/*

# Update Path for QT dev tool applications
ENV PATH="$PATH:/opt/qt/6.8.1/gcc_64/bin"