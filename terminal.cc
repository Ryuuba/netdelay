#include "terminal.h"

using namespace omnetpp;

Define_Module(Terminal);

simsignal_t Terminal::arrivalSignal = registerSignal("arrival");

void Terminal::initialize()
{
    processingDelay = par("processingDelay");
    if (strcmp(getName(), "source") == 0) {
        Pkt* pkt = new Pkt("pkt");
        int pktSize = par("pktSize");
        pkt->setBitLength(pktSize);
        scheduleAt(0.0, pkt);
    }
}

void Terminal::handleMessage(cMessage* msg)
{
    Pkt* pkt = check_and_cast<Pkt*>(msg);
    if (pkt->isSelfMessage()) {
        pkt->setGenTime(simTime());
        send(pkt, "out");
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
        delete pkt;
    }
}
