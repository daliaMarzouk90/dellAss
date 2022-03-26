#include <decaf/lang/Thread.h>
#include <decaf/lang/Runnable.h>
#include <decaf/util/concurrent/CountDownLatch.h>
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/core/ActiveMQConnection.h>
#include <activemq/transport/DefaultTransportListener.h>
#include <activemq/library/ActiveMQCPP.h>
#include <decaf/lang/Integer.h>
#include <activemq/util/Config.h>
#include <decaf/util/Date.h>
#include <cms/Connection.h>
#include <cms/Session.h>
#include <cms/TextMessage.h>
#include <cms/BytesMessage.h>
#include <cms/MapMessage.h>
#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace activemq;
using namespace activemq::core;
using namespace activemq::transport;
using namespace decaf::lang;
using namespace decaf::util;
using namespace decaf::util::concurrent;
using namespace cms;
using namespace std;

////////////////////////////////////////////////////////////////////////////////
class SimpleConsumer{
private:

    Connection* connection;
    Session* session;
    Destination* destination;
    MessageConsumer* consumer;
    bool useTopic;
    std::string brokerURI;
    std::string destURI;
    bool clientAck;

private:

    SimpleConsumer( const SimpleConsumer& );
    SimpleConsumer& operator= ( const SimpleConsumer& );

public:

    SimpleConsumer( const std::string& brokerURI,
                         const std::string& destURI,
                         bool useTopic = true,
                         bool clientAck = false ) :
        useTopic(useTopic),
        brokerURI(brokerURI),
        destURI(destURI),
        clientAck(clientAck) {
             activemq::library::ActiveMQCPP::initializeLibrary();
            // Create a ConnectionFactory
            auto_ptr<ActiveMQConnectionFactory> connectionFactory(
                new ActiveMQConnectionFactory( brokerURI ) );

            // Create a Connection
            try{
                connection = connectionFactory->createConnection();
                connection->start();
            } catch( CMSException& e ) {
                e.printStackTrace();
                throw e;
            }

            // Create a Session
            if( clientAck ) {
                session = connection->createSession( Session::CLIENT_ACKNOWLEDGE );
            } else {
                session = connection->createSession( Session::AUTO_ACKNOWLEDGE );
            }

            // Create the destination (Topic or Queue)
            if( useTopic ) {
                destination = session->createTopic( destURI );
            } else {
                destination = session->createQueue( destURI );
            }

            // Create a MessageProducer from the Session to the Topic or Queue
            consumer = session->createConsumer( destination );
    }

    virtual ~SimpleConsumer() {
        this->cleanup();
    }

    void close() {
        this->cleanup();
    }

    // Called from the consumer since this class is a registered MessageListener.
    float consume() {
        float sensorValue;
        try
        {
            Message* message = nullptr;
            while (message == nullptr)
                message = consumer->receive(2000);
            
            
            const BytesMessage* bytesMessage = dynamic_cast< const BytesMessage* >( message );
            

            if( bytesMessage != NULL ) {
                sensorValue = *(float*)bytesMessage->getBodyBytes();
            } else {
                sensorValue = 0;
            }

            if( clientAck ) {
                message->acknowledge();
            }

        } catch (CMSException& e) {
            e.printStackTrace();
        }

        return sensorValue;
    }


private:

    void cleanup(){

        try {
            if( connection != NULL ) {
                connection->close();
            }
        } catch ( CMSException& e ) { 
            e.printStackTrace(); 
        }

        delete destination;
        delete consumer;
        delete session;
        delete connection;
    }
};