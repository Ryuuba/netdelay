import inet.node.ethernet.Eth10M;
import Terminal;
import Relay;

network Pipeline
{
    submodules:
        source: Terminal {
            pktNumber = 10;
            isSource = true;
        }
        receptor: Terminal;
        relay[4]: Relay;
    connections:
        source.out   --> Eth10M { length = 100m; } --> relay[0].in;
        relay[0].out --> Eth10M { length = 100m; } --> relay[1].in;
        relay[1].out --> Eth10M { length = 100m; } --> relay[2].in;
        relay[2].out --> Eth10M { length = 100m; } --> relay[3].in;
        relay[3].out --> Eth10M { length = 100m; } --> receptor.in;
}
