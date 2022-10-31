#include "relay.h"

using namespace omnetpp;

simsignal_t Relay::fwdSignal = registerSignal("fwd");

Define_Module(Relay);

Relay::Relay () 
    : processingDelay(0.000005)
    , fwdTimer(nullptr)
    , packet(nullptr) {

}

Relay::~Relay() { 
    cancelAndDelete(fwdTimer);
}

void Relay::initialize() {
    fwdTimer = new cMessage("timer");
}

void Relay::handleMessage(cMessage* msg) {
    if (msg->isSelfMessage()) {
        send(pktQueue.front(), "out");
        pktQueue.pop();
        emit(fwdSignal, simTime());
    }
    else {
        packet = check_and_cast<Pkt*>(msg);
        pktQueue.push(packet);
        scheduleAt(processingDelay+simTime(), fwdTimer);
    }
}
