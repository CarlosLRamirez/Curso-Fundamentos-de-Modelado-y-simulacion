#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class nodo: public cSimpleModule
{
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        virtual void finish() override;

    private:
        cMessage *delayEvent = nullptr;
        simtime_t lastArrivalTime;
        cHistogram histograma_tiempo_entre_llegadas;

    public:
        virtual ~nodo();
};

Define_Module(nodo);

nodo::~nodo()
{
    cancelAndDelete(delayEvent);
}

void nodo::initialize()
{



    // Creando el mensaje delayEvent
    delayEvent = new cMessage("Intervalo entre envios");

    lastArrivalTime = -1;
    histograma_tiempo_entre_llegadas.setName("Tiempo entre llegadas");

    // enviar mensaje (nodo tx)
    if (strcmp("tx", getName()) == 0) {
        // create and send first message on gate "out". "tictocMsg" is an
        // arbitrary string which will be the name of the message object.
        EV << "Enviando mensaje inicial...\n";
        cMessage *msg = new cMessage("tictocMsg");
        send(msg, "salida");

        EV << "Generando el retardo inicial de 1s\n";
        scheduleAt(simTime()+1,delayEvent);

    }
}

void nodo::handleMessage(cMessage *msg)
{
    if (msg==delayEvent){
        if (strcmp("tx", getName()) == 0) {
                // create and send first message on gate "out". "tictocMsg" is an
                // arbitrary string which will be the name of the message object.
                EV << "Enviando mensaje nuevamente...\n";
                cMessage *msg = new cMessage("tictocMsg");
                send(msg, "salida");

                simtime_t intervalo=par("intervalo");

                EV << "Generando el retardo nuevamente:\n";
                scheduleAt(simTime()+intervalo,delayEvent);
            }

    }
    else {

        simtime_t currentArrivalTime = simTime();

        EV << "mensaje recibido...\n";

        if (lastArrivalTime >= 0) { // Check if this is not the first message
                simtime_t interArrivalTime = currentArrivalTime - lastArrivalTime;
                EV << "Inter-arrival time: " << interArrivalTime << "s\n";
                // Optionally, record the inter-arrival time for analysis
                recordScalar("interArrivalTime", interArrivalTime);
                histograma_tiempo_entre_llegadas.collect(interArrivalTime);
            }



        lastArrivalTime = currentArrivalTime;


        delete msg;
    }

}

void nodo::finish() {
    histograma_tiempo_entre_llegadas.recordAs("Inter-Arrival Time Histogram");
}
