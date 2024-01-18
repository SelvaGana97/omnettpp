
// SELVA GANAPATHY A/L MUTHU KUMAR
// YOGANATHAN SHUNMUGAM
// PAGITHEREN A/L UMABATHY
// NESHADRAJ A/L SASIDHARAN


#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class WirelessHost : public cSimpleModule{
    private:
        simtime_t timeout;
        cMessage *timeoutEvent; int seq;
        cMessage *message;

    public:
            WirelessHost();
            virtual ~WirelessHost();
    protected:
            virtual cMessage *generateNewMessage();
            virtual void sendCopyOf(cMessage *msg);
            virtual void initialize() override;
            virtual void handleMessage(cMessage *msg) override;
};
Define_Module(WirelessHost);
WirelessHost::WirelessHost(){
    timeoutEvent = message = nullptr;
}
WirelessHost::~WirelessHost(){
    cancelAndDelete(timeoutEvent); delete message;
}
void WirelessHost::initialize(){
    seq = 0; timeout = 1.0;
    timeoutEvent = new cMessage("timeoutEvent");
    EV << "Sending initial message\n";
    message = generateNewMessage(); sendCopyOf(message);
    scheduleAt(simTime()+timeout, timeoutEvent);
}
void WirelessHost::handleMessage(cMessage *msg){
    if (msg == timeoutEvent) {
        EV << "Timeout expired, resending message and restarting timer\n";
        sendCopyOf(message);
        scheduleAt(simTime()+timeout, timeoutEvent);
    }
    else {
        EV << "Received: " << msg->getName() << "\n";
        delete msg; EV << "Timer cancelled.\n";
        cancelEvent(timeoutEvent); delete message;
        message = generateNewMessage();
        sendCopyOf(message);
        scheduleAt(simTime()+timeout, timeoutEvent);
    }
}
cMessage *WirelessHost::generateNewMessage(){
    char msgname[20];
    sprintf(msgname, "msg-%d", ++seq);
    cMessage *msg = new cMessage(msgname);
    return msg;
}
void WirelessHost::sendCopyOf(cMessage *msg){
    cMessage *copy = (cMessage *)msg->dup();
    send(copy, "out");
}




