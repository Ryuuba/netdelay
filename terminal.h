#if !defined(TERMINAL_H)
#define TERMINAL_H

#include <string.h>
#include <omnetpp.h>
#include "pkt_m.h"

class Terminal : public omnetpp::cSimpleModule
{
  private:
    static omnetpp::simsignal_t arrivalSignal;
    omnetpp::simtime_t processingDelay;
    int pktNumber;
  protected:
    virtual void initialize() override;
    virtual void handleMessage(omnetpp::cMessage*) override;
};

#endif // TERMINAL_H