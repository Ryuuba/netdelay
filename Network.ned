import inet.node.ethernet.Eth10M;
import Terminal;

network Pipeline
{
    parameters:
        int numCentralNodes = default(2);
    submodules:
        tic[numCentralNodes+4]: Terminal;
    connections:
        // connect the 2 nodes in one side to the central nodes
        tic[0].gate++ <--> Eth10M {  length = 100m; } <--> tic[2].gate++;
        tic[1].gate++ <--> Eth10M {  length = 100m; } <--> tic[2].gate++;
        // connect the central nodes together
        for i=2..numCentralNodes+1 {
            tic[i].gate++ <--> Eth10M {  length = 100m; } <--> tic[i+1].gate++;
        }
        // connect the 2 nodes on the other side to the central nodes
        tic[numCentralNodes+2].gate++ <--> Eth10M {  length = 100m; } <--> tic[numCentralNodes+1].gate++;
        tic[numCentralNodes+3].gate++ <--> Eth10M {  length = 100m; } <--> tic[numCentralNodes+1].gate++;
}
