simple Terminal
{
    parameters:
        int pktNumber = default(0);
        bool isSource = default(false);
        int pktSize @unit(Mb) = default(10Mb);
        simtime_t processingDelay @unit(us) = default(50us);
        @signal[arrival](type="simtime_t");
        @statistic[delay](title="delay"; source="arrival"; record=vector,stats; interpolationmode=none);
        @display("i=device/laptop");
    gates:
        input in @loose;
        output out @loose;
}


