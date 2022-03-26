#base image
FROM rikorose/gcc-cmake

#update and install prerequists
RUN apt-get update && apt-get -y install build-essential git curl unzip tar zip autoconf libtool  g++
RUN apt-get update 

#install vcpkg
RUN wget -O vcpkg.tar.gz https://github.com/microsoft/vcpkg/archive/master.tar.gz
RUN mkdir /opt/vcpkg
RUN tar xf vcpkg.tar.gz --strip-components=1 -C /opt/vcpkg
RUN /opt/vcpkg/bootstrap-vcpkg.sh -useSystemBinaries
RUN ln -s /opt/vcpkg/vcpkg /usr/local/bin/vcpkg

#install activemq-cpp
RUN vcpkg update
RUN VCPKG_FORCE_SYSTEM_BINARIES=1 vcpkg install --clean-buildtrees-after-build --clean-packages-after-build --clean-downloads-after-build apr activemq-cpp

ENV VCPKG_DIR=/opt/vcpkg/

COPY ./ /server/

CMD [ "bash", "-x", "/serve/run.sh" ]