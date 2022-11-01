#include "terminal.h"

using namespace omnetpp;

Define_Module(Terminal);

simsignal_t Terminal::arrivalSignal = registerSignal("arrival");
simsignal_t Terminal::fwdSignal = registerSignal("fwd");

Terminal::Terminal()
    : processingDelay(0.0)
    , pktSize(0)
    , pktNumber(0) {
}

Terminal::~Terminal() {

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
    Pkt* pkt = check_and_cast<Pkt*>(msg);
    if (pkt->isSelfMessage()) {
        pkt->setGenTime(simTime());
        send(pkt, "out");
        pktNumber--;
        if (pktNumber == 0)
            getSimulation()->getSystemModule()->
                getSubmodule("relay", 0)->unsubscribe(fwdSignal, this);
    }
    else if (strcmp(getName(), "receptor") == 0) {
        auto delay = simTime() - pkt->getGenTime() + processingDelay;
        emit(arrivalSignal, delay);
        EV << "Message " << pkt << " arrived after " 
           << delay << " s.\n";
        delete pkt;
    }
    else {
        EV << "Droping packet from " << pkt->getName() << endl;
        cancelAndDelete(pkt);
        delete pkt;
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