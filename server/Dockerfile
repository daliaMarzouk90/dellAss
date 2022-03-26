#base image
FROM ubuntu:20.04

#update and install prerequists
ENV TZ=Europe/Minsk
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezon
RUN apt-get -y update && apt-get -y install build-essential git curl unzip tar zip autoconf libtool gcc cmake
RUN apt-get -y install wget

#install vcpkg
RUN wget -O vcpkg.tar.gz https://github.com/microsoft/vcpkg/archive/master.tar.gz
RUN mkdir /opt/vcpkg
RUN tar xf vcpkg.tar.gz --strip-components=1 -C /opt/vcpkg
RUN /opt/vcpkg/bootstrap-vcpkg.sh -useSystemBinaries
RUN ln -s /opt/vcpkg/vcpkg /usr/local/bin/vcpkg

#install cmake
RUN apt-get -y purge cmake
RUN apt-get -y update
RUN apt-get -y install libssl-dev
RUN wget https://github.com/Kitware/CMake/releases/download/v3.23.0-rc5/cmake-3.23.0-rc5.tar.gz
RUN tar -xvzf cmake-3.23.0-rc5.tar.gz
RUN rm cmake-3.23.0-rc5.tar.gz
RUN cmake-3.23.0-rc5/bootstrap --parallel=8
RUN make
RUN make install

#install activemq-cpp
RUN vcpkg update
RUN VCPKG_FORCE_SYSTEM_BINARIES=1 vcpkg install --clean-buildtrees-after-build --clean-packages-after-build --clean-downloads-after-build apr activemq-cpp

ENV VCPKG_DIR=/opt/vcpkg/

COPY ./ /server/

CMD [ "bash", "-x", "/serve/run.sh" ]