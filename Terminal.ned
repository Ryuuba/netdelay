simple Terminal
{
    parameters:
        int pktNumber = default(0);
        bool isSource = default(false);
        int pktSize @unit(bits) = default(10Mb);
        double processingDelay @unit(s) = default(10us);
        @signal[fwd](type="simtime_t");
        @signal[arrival](type="simtime_t");
        @statistic[delay](title="delay"; source="arrival"; record=vector,stats; interpolationmode=none);
        @display("i=device/laptop");
    gates:
        input in @loose;
        output out @loose;
}


