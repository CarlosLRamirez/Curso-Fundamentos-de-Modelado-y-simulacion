#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

//definimos la clase TX
class TX: public cSimpleModule
{
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;

    private:
        cMessage *mensaje_retardo=nullptr;

    public:
        virtual ~TX();

};

Define_Module(TX);

TX::~TX()
{
    //cancelAndDelete(delayEvent);
}

//este es el metodo que se utiliza al inicializar la simulaci[on
void TX::initialize()
{

    EV << "Soy TX y estoy inicializandome...\n";

    EV << "Enviando mensaje inicial\n";

    cMessage *msg = new cMessage("tictocMsg");
    send(msg,"salida");

    //Enviar el mensaje de retardo, despues de iniciada la simulacion

    mensaje_retardo = new cMessage("Intervalo entre envios");
    scheduleAt(simTime()+0.3,mensaje_retardo);


}

//este es el metodo que se utiliza al recibir un mensaje
void TX::handleMessage(cMessage *msg)
{
    if (msg==mensaje_retardo){

        simtime_t intervalo=par("intervalo");


        cMessage *msg = new cMessage("tictocMsg");
        send(msg, "salida");

        EV << "Generando el retardo nuevamente:\n";
        scheduleAt(simTime()+intervalo,mensaje_retardo);
    }




}



//============================================================================================


//definimos la clase RX
class RX: public cSimpleModule
{
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;


    public:
        virtual ~RX();

};

Define_Module(RX);

RX::~RX()
{
    //cancelAndDelete(delayEvent);
}

//este es el metodo que se utiliza al inicializar la simulaci[on
void RX::initialize()
{

    EV << "Soy RX y estoy inicializandome...\n";


}

//este es el metodo que se utiliza al recibir un mensaje
void RX::handleMessage(cMessage *msg)
{

    EV << "recibi el mensaje...\n";
    delete msg;

}


