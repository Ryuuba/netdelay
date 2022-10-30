#include <string.h>
#include <omnetpp.h>
#include "pkt_m.h"

class Terminal : public omnetpp::cSimpleModule
{
  private:
    omnetpp::simsignal_t arrivalSignal;

  protected:
    virtual Pkt* generatePkt();
    virtual void forwardPkt(Pkt*);
    virtual void initialize() override;
    virtual void handleMessage(omnetpp::cMessage*) override;
};