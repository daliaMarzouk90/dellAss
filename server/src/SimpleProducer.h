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
#include <memory>

using namespace activemq;
using namespace activemq::core;
using namespace decaf;
using namespace decaf::lang;
using namespace decaf::util;
using namespace decaf::util::concurrent;
using namespace cms;
using namespace std;

////////////////////////////////////////////////////////////////////////////////
class SimpleProducer{
private:

    Connection* connection;
    Session* session;
    Destination* destination;
    MessageProducer* producer;
    bool useTopic;
    bool clientAck;
    std::string brokerURI;
    std::string destURI;

private:

    SimpleProducer( const SimpleProducer& );
    SimpleProducer& operator= ( const SimpleProducer& );

public:

    SimpleProducer( const std::string& brokerURI,
                    const std::string& destURI, bool useTopic = true, bool clientAck = false ) :
        session(NULL),
        destination(NULL),
        producer(NULL),
        useTopic(useTopic),
        clientAck(clientAck),
        brokerURI(brokerURI),
        destURI(destURI) 
        {
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
            producer = session->createProducer( destination );
            producer->setDeliveryMode( DeliveryMode::NON_PERSISTENT );
    }

    ~SimpleProducer(){
        cleanup();
    }

    void close() {
        this->cleanup();
    }

    void send(float value) {
        try {
            
            BytesMessage* message = session->createBytesMessage((unsigned char*)&value, sizeof(float));

            producer->send( message );

            delete message;

        }catch ( CMSException& e ) {
            e.printStackTrace();
        }
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
        delete producer;
        delete session;
        delete connection;
        activemq::library::ActiveMQCPP::shutdownLibrary();
    }
};
