#include "terminal.h"

using namespace omnetpp;

Define_Module(Terminal);

simsignal_t Terminal::arrivalSignal = registerSignal("arrival");
simsignal_t Terminal::fwdSignal = registerSignal("fwd");

Terminal::Terminal()
    : processingDelay(0.0)
    , procDelay(nullptr)
    , pktSize(0)
    , pktNumber(0) {
}

Terminal::~Terminal() {
    cancelAndDelete(procDelay);
}

void Terminal::initialize()
{
    processingDelay = par("processingDelay");
    if (strcmp(getName(), "source") == 0) {
        getSimulation()->getSystemModule()
            ->getSubmodule("relay", 0)->subscribe(fwdSignal, this);
        Pkt* pkt = new Pkt("pkt");
        pktSize = par("pktSize");
        pkt->setBitLength(pktSize);
        pktNumber = par("pktNumber");
        pkt->setNumber(pktNumber);
        scheduleAt(0.0, pkt);
    }
}

void Terminal::handleMessage(cMessage* msg)
{
    if (msg->isSelfMessage()) {
        if (strcmp(getName(), "source") == 0) {
            Pkt* pkt = check_and_cast<Pkt*>(msg);
            pkt->setGenTime(simTime());
            send(pkt, "out");
            pktNumber--;
            if (pktNumber == 0)
                getSimulation()->getSystemModule()->
                    getSubmodule("relay", 0)->unsubscribe(fwdSignal, this);
        }
        else {
            EV << "Packet arrived at " << simTime() << " s" << endl;
        }
    }
    else if (strcmp(getName(), "receptor") == 0) {
        Pkt* pkt = check_and_cast<Pkt*>(msg);
        procDelay = new cMessage("delay");
        auto eedelay = simTime() - pkt->getGenTime() + processingDelay;
        emit(arrivalSignal, eedelay);
        scheduleAt(processingDelay + simTime(), procDelay);
        delete pkt;
    }
    else {
        EV << "Droping packet from " << msg->getName() << endl;
        cancelAndDelete(msg);
    }
}

void Terminal::receiveSignal(
        omnetpp::cComponent* src, omnetpp::simsignal_t id, const omnetpp::SimTime& value, omnetpp::cObject* details
) {
    Enter_Method_Silent();
    Pkt* pkt = new Pkt("pkt");
    pkt->setBitLength(pktSize);
    pkt->setNumber(pktNumber);
    scheduleAt(simTime(), pkt);
}