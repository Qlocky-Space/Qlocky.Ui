FROM ubuntu:plucky

# Update system and add the packages required for Yocto builds.
# Use DEBIAN_FRONTEND=noninteractive, to avoid image build hang waiting
# for a default confirmation [Y/n] at some configurations.
ENV DEBIAN_FRONTEND=noninteractive

RUN apt update
RUN apt -y install \
    clang-format clang-tidy \
    wget git-core build-essential ninja-build \
    gdb-multiarch
