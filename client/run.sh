#!/bin/bash
if [ -n "${CLIENT_PATH}" ]; then
  currentPath=$CLIENT_PATH
else
  currentPath=$PWD
fi

VCPKG_DIR="/opt/vcpkg"

#build
g++ -fdiagnostics-color=always -g ${currentPath}/src/Client.cpp ${VCPKG_DIR}/installed/x64-linux/lib/libactivemq-cpp.a \
 ${VCPKG_DIR}/installed/x64-linux/lib/libapr-1.a ${VCPKG_DIR}/installed/x64-linux/lib/libuuid.a -I${VCPKG_DIR}/installed/x64-linux/include/ \
 -L${VCPKG_DIR}/installed/x64-linux/lib -o ${currentPath}/src/Client -lpthread -Wno-deprecated

#run
${currentPath}/src/Client 