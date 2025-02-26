FROM ubuntu:plucky

# Update system and add the packages required for Yocto builds.
# Use DEBIAN_FRONTEND=noninteractive, to avoid image build hang waiting
# for a default confirmation [Y/n] at some configurations.
ENV DEBIAN_FRONTEND=noninteractive

# tools for generic development
RUN apt update && apt -y install \
    clang-format clang-tidy \
    wget git-core build-essential ninja-build \
    gdb cmake

# tools for application
RUN apt update && apt -y install \
    qt6-base-dev libgl1-mesa-dev


# Git configuration
RUN git config --global --add safe.directory /workspaces/build/_deps/*