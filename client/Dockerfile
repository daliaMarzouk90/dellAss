FROM ubuntu:20.04

ENV TZ=Europe/London
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update && apt-get -y install build-essential git curl unzip tar zip


RUN apt-get autoremove -y
RUN apt-get -y install wget
RUN wget -O cmake.sh https://github.com/Kitware/CMake/releases/download/v3.23.0-rc5/cmake-3.23.0-rc5-linux-x86_64.sh && sh ./cmake.sh --prefix=/usr/local --skip-license

ENV CC clang
ENV CXX clang++

RUN apt-get -y install libapr1 libapr1-dev libssl-dev

RUN git clone https://gitbox.apache.org/repos/asf/activemq-cpp.git 
RUN cd activemq-cpp/activemq-cpp
RUN ./autogen.sh
RUN ./configure
RUN make
RUN make install

COPY ./ /client/

CMD [ "bash", "-x", "/client/run.sh" ]