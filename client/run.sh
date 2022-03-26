#!/bin/bash
if [[ -z "${WORKDIR}" ]]; then
  currentPath="${WORKDIR}"
else
  currentPath="/home/dalia/dellAss/server"
fi
currentPath="/home/dalia/dellAss/server"

#build
g++ -fdiagnostics-color=always -g ${currentPath}/client/src/Client.cpp ${VCPKG_DIR}/installed/x64-linux/lib/libactivemq-cpp.a \
 ${VCPKG_DIR}/installed/x64-linux/lib/libapr-1.a ${VCPKG_DIR}/installed/x64-linux/lib/libuuid.a -I${VCPKG_DIR}/installed/x64-linux/include/ \
 -L${VCPKG_DIR}/installed/x64-linux/lib -o ${currentPath}/src/Client -lpthread -Wno-deprecated

#run
${currentPath}/src/Client 