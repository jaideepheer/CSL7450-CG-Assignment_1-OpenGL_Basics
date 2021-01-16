# https://hub.docker.com/r/mmozeiko/mingw-w64/tags?page=1&ordering=last_updated
FROM mmozeiko/mingw-w64:latest

# https://github.com/thewtex/docker-opengl/blob/master/example/Dockerfile
# FROM thewtex/opengl:latest

# Setup mingw freeglut
COPY ./setup_mingw_glut.sh /setup_mingw_glut.sh
RUN chmod +X /setup_mingw_glut.sh && /setup_mingw_glut.sh && rm -f /setup_mingw_glut.sh

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
  mesa-utils \
  freeglut3-dev \
  libxmu-dev \
  libxi-dev \
  libxxf86vm-dev \
  wine64 \
  sudo \
  \
  && apt-get autoremove --purge -y \
  && apt-get clean

ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Create the user
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    #
    # [Optional] Add sudo support. Omit if you don't need to install software after connecting.
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME