simple Proc
{
    parameters:
        @display("i=block/cogwheel");
        simtime_t processingDelay @unit(us) = default(50us);
    gates:
        input in;
        output out; 
}