# RSL

ROS Support Library

[![codecov](https://codecov.io/github/PickNikRobotics/RSL/branch/main/graph/badge.svg?token=t85cTyvsez)](https://codecov.io/github/PickNikRobotics/RSL)

## Local development in devcontainer

0. Install docker and add yourself to the docker group.

```shell
curl -fsSL https://get.docker.com -o get-docker.sh
sudo sh get-docker.sh

sudo groupadd docker
sudo usermod -aG docker $USER
newgrp docker
```

1. Run these commands to create a directory to mount for ccache and another to mount for the ros directory containing log files.

```bash
mkdir -p ~/.local/.rsl/ccache
mkdir -p ~/.local/.rsl/ros
```

2. Open project in VSCode and follow prompts to open project in devcontainer.
