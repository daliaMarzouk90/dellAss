#!/bin/bash
if [[ -z "${WORKDIR}" ]]; then
  currentPath="${WORKDIR}"
else
  currentPath="/home/dalia/dellAss/server"
fi
currentPath="/home/dalia/dellAss/server"
#build
g++-7 -fdiagnostics-color=always -g ${currentPath}/src/Server.cpp ${currentPath}/src/AMQProducer.cpp ${currentPath}/src/Sensor.cpp \
${VCPKG_DIR}installed/x64-linux/lib/libactivemq-cpp.a ${VCPKG_DIR}installed/x64-linux/lib/libapr-1.a /opt/vcpkg/installed/x64-linux/lib/libuuid.a \
-I${VCPKG_DIR}installed/x64-linux/include/ -L${VCPKG_DIR}installed/x64-linux/lib -o ${currentPath}/src/Server -lpthread -Wno-deprecated

#run
${currentPath}/src/Server 