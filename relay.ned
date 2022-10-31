import proc;
import org.omnetpp.queueing.Queue;

module Relay
{
    submodules:
        processor: proc {
            @display("p=165.0,160.0");
        }
        queue: Queue {
            @display("p=165.0,80.0");
        }
    gates:
        input in;
        output out; 
    connections:
        queue.in++ <-- in;
        proc.in <-- queue.out++;
        out <-- proc.out;
}