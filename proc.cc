#include "proc.h"

using namespace omnetpp;

Define_Module(Proc);

void Proc::initialize() {
    processingDelay = par("processingDelay");
    fwdTimer = new cMessage("timer");
}

void Proc::handleMessage(cMessage* msg) {
    if (msg->isSelfMessage())
        send(packet, "out");
    else {
        packet = check_and_cast<Pkt*>(msg);
        scheduleAt(simTime() + processingDelay, fwdTimer);
    }
}