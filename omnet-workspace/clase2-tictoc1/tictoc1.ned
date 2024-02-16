import ned.IBidirectionalChannel;


simple Txc1
{
    gates:
        input in;
        output out;
}

//
// Two instances (tic and toc) of Txc1 connected both ways.
// Tic and toc will pass messages to one another.
//
network Tictoc1
{
    submodules:
        tic: Txc1 {
            parameters:
            	@display("i=,cyan");
        	
        }
        toc: Txc1 {

            parameters:
            	@display("i=,gold");
        	
        }
    connections:
        tic.out --> {  delay = 100ms; } --> toc.in;
        tic.in <-- {  delay = 100ms; } <-- toc.out;
}
