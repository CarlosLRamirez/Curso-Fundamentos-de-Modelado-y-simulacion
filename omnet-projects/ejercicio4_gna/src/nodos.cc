#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <cmath>


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

        //Parametros del GCL
        unsigned long a = 1664525;
        unsigned long c = 1013904223;
        unsigned long m = 4294967296; // 2^32
        unsigned long seed; // Initial seed

        double lambda;

    public:
        virtual ~nodo();
        double lcgRandom();
        double exponential(double lambda);
        double uniforme(double a, double b);
        double triangular();
        double weibull(double lambda, double k);
};

Define_Module(nodo);

nodo::~nodo()
{
    cancelAndDelete(delayEvent);
}

void nodo::initialize()
{

    seed = (unsigned long)par("semilla").intValue();

    lambda = 1.0 / par("mediaIntervalo").doubleValue();

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

        simtime_t intervalo=exponential(lambda);

        EV << "Generando el retardo inicial\n";
        scheduleAt(simTime()+3,delayEvent);

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


                //simtime_t intervalo=exponential(lambda);
                //simtime_t intervalo=uniforme(2.0,5.0);
                //simtime_t intervalo=triangular();
                simtime_t intervalo=weibull(lambda,2.0);


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

double nodo::lcgRandom() {
    seed = (a * seed + c) % m;
    return static_cast<double>(seed) / m;
}

double nodo::exponential(double l) {
    double u = lcgRandom();
    return -log(1 - u) / l;
}

double nodo::uniforme(double a, double b){
    double u = lcgRandom();
    return a + (b - a)*u;
}


double nodo::triangular(){
    double R = lcgRandom();
    if (R < 0.5) {
            return sqrt(2 * R);
        } else {
            return 2 - sqrt(2 * (1 - R));
        }

}

double nodo::weibull(double lambda, double k) {
    // Generate a uniform random number between 0 and 1
    double R = lcgRandom();

    // Apply the inverse CDF of the Weibull distribution to transform R
    return lambda * pow(-log(1 - R), 1/k);
}


void nodo::finish() {
    histograma_tiempo_entre_llegadas.recordAs("Inter-Arrival Time Histogram");
}
