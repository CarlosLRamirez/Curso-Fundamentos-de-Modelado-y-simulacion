simple nodo
{
	parameters:
	    int semilla = default(123456789);
	    double mediaIntervalo = default (1.0);
	
    gates:
        input entrada;
        output salida;
        
}

network ejercicio_gna
{
    submodules:
        tx: nodo {
            parameters:
                 @display("i=block/source");
                 
        }
        rx: nodo {
            parameters:
                 @display("i=block/sink");
        }
    connections:
        tx.salida -->  { }--> rx.entrada;
        tx.entrada <-- { } <-- rx.salida;

}
