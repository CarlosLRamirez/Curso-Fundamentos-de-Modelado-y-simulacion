


simple TX
{
    
    parameters:
        volatile double intervalo @unit(ms)=default(300ms);
        
    gates:
        //input entrada;
        output salida;

}

simple RX
{
    gates:
        input entrada;
        //output salida;

}


network ejercicio4
{
 
    submodules:
        receptor: RX {



        }
        transmisor: TX {

        }

    connections:
        transmisor.salida --> {  delay = 200ms; } --> receptor.entrada;
        //transmisor.salida <-- {  delay = 200ms; } <-- receptor.entrada;


}


