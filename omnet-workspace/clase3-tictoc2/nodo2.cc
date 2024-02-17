#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Nodo2: public cSimpleModule
{
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;

    private:
        cMessage *timeoutEvent = nullptr;
        cMessage *delayEvent = nullptr;
        cMessage *mensaje = nullptr;
        simtime_t timeout;


    public:
        virtual ~Nodo2();

};

Define_Module(Nodo2);

Nodo2::~Nodo2()
{
    cancelAndDelete(delayEvent);
    cancelAndDelete(timeoutEvent);
    delete mensaje;
}


void Nodo2::initialize()
{
    // Creando el mensaje delayEvent
    delayEvent = new cMessage("Delay");

    // Definiendo el timeout y creando el timeoutEvent
    timeout = par("timeout");

    timeoutEvent = new cMessage("Timeout");

    //el mensaje inicial de la red todavia no existe
    mensaje = nullptr;

    // el nodo 0 se autoenviará un mensaje de delayEvent inicial en t=0.1s
    if (getIndex()==0){
        //delayEvent ya existe y es "mensaje de delayEvent"
        EV << "Generando el mensaje inicial: "<< delayEvent <<"en t=1s\n";
        scheduleAt(1,delayEvent);

        //aqui creamos el mensaje que estara dando vueltas en la red
        char msgname[20];
        sprintf(msgname,"tic-%d",getIndex());
        mensaje = new cMessage(msgname);
        EV << "Mensaje : "<< mensaje <<"creado\n";

    }
    else {
        //el resto de nodos inicia su timeoutEvent
        EV << "iniciando mi timeoutEvent de " << timeout << "segundos\n";
        scheduleAt(simTime()+timeout,timeoutEvent);
    }

}

void Nodo2::handleMessage(cMessage *msg)
{

    //Si se recibe el delayEvent, el tiempo de retardo expiró,
    //y se envía el mensaje a la red
    if (msg==delayEvent){
        EV << "delayEvent expirado, reenviando el mensaje\n";
        send (mensaje,"salida",0);
        //elimino el mensaje enviado
        mensaje=nullptr;

        //se resetea el timeout
        //EV << "Reiniciando el timeout\n";
        //cancelEvent(timeoutEvent);
        scheduleAt(simTime()+timeout,timeoutEvent);


    }

    // si se recibe el timeoutEvent,
    // el mensaje se perdió y se debe enviar un nuevo mensaje
    else if (msg==timeoutEvent){
        EV << "Ohh no recibi ningun mensaje y expiero el tiempo de espera\n";
        EV << "Generando nuevo mensaje\n";
        char msgname[20];
        sprintf(msgname,"tic-%d",getIndex());
        mensaje = new cMessage(msgname);
        EV << "Enviando nuevo mensaje\n";
        send (mensaje,"salida",0);

        //elimino el mensaje enviado
        mensaje=nullptr;

        //inicio un nuevo timeout
        cancelEvent(timeoutEvent);
        scheduleAt(simTime()+timeout,timeoutEvent);


    }
    // si se recibe el mensaje, se inicia el tiempo de retardo,
    // si es que no lo "pierde"
    // y se cancela el timeoutEvent
    else {
        double taPerdida=par("tazaPerdida").doubleValue()/100;
        //si lo pierdo lo borro
        if (uniform(0,1)<taPerdida){
            EV << "Perdí el mensaje\n";
            bubble("message lost");  // making animation more informative...
            delete msg;

            //inicio un nuevo timeout
            cancelEvent(timeoutEvent);

            //scheduleAt(simTime()+timeout*5,timeoutEvent);


        }
        // si no lo pierdo, inicio el delayEvent
        else {
            simtime_t delay = par("tiempoRetardo");
            EV << "Mensaje recibido, iniciando espera de " << delay << " seg...\n";
            //lo capturo en mensaje, cuando termine el tiempo de delayEvent, me va servir
            mensaje = msg;

            //ahora si envio el delayEvent
            scheduleAt(simTime()+delay,delayEvent);

            //se resetea el timeout
            //EV << "Reiniciando el timeout\n";
            cancelEvent(timeoutEvent);
            //scheduleAt(simTime()+timeout,timeoutEvent);

        }
    }
}

