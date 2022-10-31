#if !defined(PROC_H)
#define PROC_H

#include <omnetpp.h>
#include "pkt_m.h"

class Proc : public omnetpp::cSimpleModule
{
private:
    omnetpp::simtime_t processingDelay;
    omnetpp::cMessage* fwdTimer;
    Pkt* packet;
public:
    ~Proc() { cancelAndDelete(fwdTimer); } 
    virtual void initialize() override;
    virtual void handleMessage(omnetpp::cMessage*) override;
};

#endif // PROC_H
