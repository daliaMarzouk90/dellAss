FROM ubuntu:20.04
LABEL maintainer="Erwan BERNARD https://github.com/edmBernard/DockerFiles"

ENV TZ=Europe/Paris
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get clean && apt-get update && apt-get upgrade -y && \
    apt-get install -y \
        build-essential software-properties-common cmake git nano \
        curl wget rsync unzip \
        && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*


# Configuration
ENV HOME "/home/dev"
RUN mkdir -p "$HOME"

ENV LIB_DIR "$HOME/lib"
RUN mkdir -p "$LIB_DIR"
ENV VCPKG_DIR "/opt/vcpkg"

# install vcpkg for local folder
RUN cd $HOME/lib && \
    git clone https://github.com/Microsoft/vcpkg.git && cd vcpkg 

RUN apt-get -y update && \
    apt-get -y install curl zip unzip tar
RUN cd $VCPKG_DIR && \
    ./bootstrap-vcpkg.sh && \
    ./vcpkg integrate install

# update cmake
RUN apt-get -y purge cmake
RUN cd /tmp && \
    wget https://github.com/Kitware/CMake/releases/download/v3.23.0-rc5/cmake-3.23.0-rc5.tar.gz && \
    tar xvzf cmake-3.23.0-rc5.tar.gz && \
    rm cmake-3.23.0-rc5.tar.gz
RUN apt-get -y install libssl-dev
RUN cd /tmp/cmake-3.23.0-rc5 && \
    ./bootstrap && \
    make && \
    make install

COPY . /server
ENV SERVER_PATH=/server

RUN cd $VCPKG_DIR && \
     VCPKG_FORCE_SYSTEM_BINARIES=1 ./vcpkg install --no-binarycaching --keep-going apr activemq-cpp

CMD [ "bash", "-x", "/serve/run.sh" ]