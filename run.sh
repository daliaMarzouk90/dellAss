#!/bin/bash
docker pull rmohr/activemq
docker run -p 61616:61616 -p 8161:8161 rmohr/activemq &

CURRENT_PATH=$PWD
export SERVER_PATH=$CURRENT_PATH/server
export CLIENT_PATH=$CURRENT_PATH/client

bash -x server/run.sh &
bash -x client/run.sh