#if !defined(PROC_H)
#define PROC_H

#include <omnetpp.h>
#include <queue>
#include "pkt_m.h"

class Relay 
    : public omnetpp::cSimpleModule
{
    private:
        omnetpp::simtime_t processingDelay;
        omnetpp::cMessage* fwdTimer;
        Pkt* packet;
        std::queue<Pkt*> pktQueue;
        static omnetpp::simsignal_t fwdSignal;
    public:
        Relay();
        ~Relay(); 
        virtual void initialize() override;
        virtual void handleMessage(omnetpp::cMessage*) override;
};

#endif // PROC_H
