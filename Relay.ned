simple Relay
{
    parameters:
        @display("i=device/switch");
        double processingDelay @unit(us) = default(50us);
        @signal[fwd](type="simtime_t");
    gates:
        input in;
        output out; 
}