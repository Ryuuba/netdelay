simple Relay
{
    parameters:
        @display("i=device/switch");
        double processingDelay @unit(s) = default(10us);
        @signal[fwd](type="simtime_t");
    gates:
        input in;
        output out; 
}