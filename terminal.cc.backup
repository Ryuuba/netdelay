#include "terminal.h"

using namespace omnetpp;

Define_Module(Terminal);

void Terminal::initialize()
{
    arrivalSignal = registerSignal("arrival");
    // Module 0 sends the first message
    if (getIndex() == 0) {
        Pkt* pkt = generatePkt();
        pkt->setBitLength(10000000);
        scheduleAt(0.0, pkt);
    }
}

void Terminal::handleMessage(cMessage* msg)
{
    Pkt* pkt = check_and_cast<Pkt*>(msg);

    if (pkt->getDestination() == getIndex()) {

        auto receptionTime = pkt->getReceptionTime();

        // informs the time the packet arrives
        emit(arrivalSignal, receptionTime + simTime());

        EV << "Message " << pkt << " arrived after " << receptionTime << " s.\n";
        bubble("ARRIVED, starting new one!");

        delete pkt;

        // Generate another one.
        EV << "Generating another message: ";
        Pkt* newpkt = generatePkt();
        EV << newpkt << endl;
        forwardPkt(newpkt);
    }
    else {
        // We need to forward the message.
        forwardPkt(pkt);
    }
}

Pkt* Terminal::generatePkt()
{
    // Produce source and destination addresses.
    int src = getIndex();
    int n = getVectorSize();
    int dest = intuniform(0, n-2);
    if (dest >= src)
        dest++;

    char pktname[20];
    sprintf(pktname, "tic-%d-to-%d", src, dest);

    // Create message object and set source and destination field.
    Pkt *pkt = new Pkt(pktname);
    pkt->setSource(src);
    pkt->setDestination(dest);
    return pkt;
}

void Terminal::forwardPkt(Pkt *pkt)
{
    // Increment hop count.
    pkt->setReceptionTime(pkt->getReceptionTime() + simTime());

    // Same routing as before: random gate.
    int n = gateSize("gate");
    int k = intuniform(0, n-1);

    EV << "Forwarding message " << pkt << " on gate[" << k << "]\n";
    send(pkt, "gate$o", k);
}

