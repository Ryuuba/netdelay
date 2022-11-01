#if !defined(TERMINAL_H)
#define TERMINAL_H

#include <string.h>
#include <omnetpp.h>
#include "pkt_m.h"

class Terminal 
    : public omnetpp::cSimpleModule
    , public omnetpp::cListener
{
    private:
        static omnetpp::simsignal_t arrivalSignal;
        static omnetpp::simsignal_t fwdSignal;
        omnetpp::simtime_t processingDelay;
        long pktSize;
        long pktNumber;
    public:
        Terminal();
        ~Terminal();
        virtual void initialize() override;
        virtual void handleMessage(omnetpp::cMessage*) override;
        virtual void receiveSignal (omnetpp::cComponent*, omnetpp::simsignal_t, const omnetpp::SimTime&, omnetpp::cObject*);
};

#endif // TERMINAL_H