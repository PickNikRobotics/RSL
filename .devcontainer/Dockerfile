# syntax=docker/dockerfile:1.2
ARG ROS_DISTRO="rolling"
FROM ros:${ROS_DISTRO}-ros-base AS upstream
# Restate for later use
ARG ROS_DISTRO
RUN rm /ros_entrypoint.sh

# prevent interactive messages in apt install
ARG DEBIAN_FRONTEND=noninteractive

# install build dependencies
RUN --mount=type=cache,target=/var/cache/apt,id=apt \
    apt-get update && apt-get upgrade -y --with-new-pkgs \
    && apt-get install -q -y --no-install-recommends \
    build-essential \
    ccache \
    clang-14 \
    clang-format-14 \
    clang-tidy-14 \
    cmake \
    curl \
    git \
    lcov \
    lld \
    ninja-build \
    openssh-client \
    python3-colcon-common-extensions \
    python3-colcon-coveragepy-result \
    python3-colcon-lcov-result \
    python3-colcon-mixin \
    python3-pip \
    python3-pytest \
    python3-pytest-cov \
    python3-pytest-repeat \
    python3-pytest-rerunfailures \
    python3-rosdep \
    python3-setuptools \
    python3-vcstool \
    wget \
    && rosdep update \
    && colcon mixin update default \
    && rm -rf /var/lib/apt/lists/*

# setup ssh
RUN mkdir /root/.ssh \
    && ssh-keyscan -t rsa github.com >> ~/.ssh/known_hosts

# install dependencies of this project
WORKDIR /root/ws
COPY ../ ./src/rsl
RUN --mount=type=cache,target=/var/cache/apt,id=apt \
    . /opt/ros/${ROS_DISTRO}/setup.sh \
    && rosdep update && apt-get update \
    && rosdep install -q -y \
    --from-paths src \
    --ignore-src \
    --rosdistro ${ROS_DISTRO} \
    && rm -rf /var/lib/apt/lists/*
RUN rm -rf /root/ws

FROM upstream AS devcontainer

ARG USER=dev
ARG UID=1000
ARG GID=$UID

# Setup user home directory
RUN groupadd --gid $GID $USER \
    && useradd --uid $UID --gid $GID -m $USER --groups sudo \
    && echo $USER ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USER \
    && chmod 0440 /etc/sudoers.d/$USER \
    && echo "source /opt/ros/${ROS_DISTRO}/setup.bash" >> /home/${USER}/.profile \
    && touch /home/${USER}/.bashrc \
    && chown -R ${UID}:${GID} /home/${USER}

# install pre-commit
RUN python3 -m pip install -U \
    pre-commit

# install development tooling
RUN --mount=type=cache,target=/var/cache/apt,id=apt \
    apt-get update && apt-get upgrade -y \
    && apt-get install -q -y --no-install-recommends \
    gdb \
    lldb-14 \
    && rm -rf /var/lib/apt/lists/*

USER $USER
ENV SHELL /bin/bash
ENTRYPOINT []

# Setup mixin
WORKDIR /home/${USER}/ws
RUN colcon mixin add default https://raw.githubusercontent.com/colcon/colcon-mixin-repository/master/index.yaml \
    && colcon mixin update default
