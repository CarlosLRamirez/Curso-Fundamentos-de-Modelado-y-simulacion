//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

/**
 * Let us take a step back, and remove random delaying from the code.
 * We'll leave in, however, losing the packet with a small probability.
 * And, we'll we do something very common in telecommunication networks:
 * if the packet doesn't arrive within a certain period, we'll assume it
 * was lost and create another one. The timeout will be handled using
 * (what else?) a self-message.
 */
class Tic8 : public cSimpleModule
{
  private:
    simtime_t timeout;  // tiempo de espera
    cMessage *timeoutEvent = nullptr;  // holds pointer to the timeout self-message

  public:
    virtual ~Tic8();

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Tic8);

Tic8::~Tic8()
{
    cancelAndDelete(timeoutEvent);
}

void Tic8::initialize()
{
    // Initialize variables.
    timeout = 1.0;
    timeoutEvent = new cMessage("timeoutEvent");

    // Generar y enviar el mensaje a la red, inmediatamente iniciada la simulación (t=0)
    EV << "Sending initial message\n";
    cMessage *msg = new cMessage("tictocMsg");
    send(msg, "out");

    //Enviar el mensaje de timeout en t=1s
    scheduleAt(simTime()+timeout, timeoutEvent);
}

void Tic8::handleMessage(cMessage *msg)
{
    if (msg == timeoutEvent) {
        // If we receive the timeout event, that means the packet hasn't
        // arrived in time and we have to re-send it.
        EV << "Timeout expired, resending message and restarting timer\n";

        //se vuelve a generar un nuevo mensaje y se envia a la red
        cMessage *newMsg = new cMessage("tictocMsg");
        send(newMsg, "out");

        //se enviará un mensaje de timeout 1seg despues.
        scheduleAt(simTime()+timeout, timeoutEvent);
    }
    else {  // message arrived
            // Acknowledgement received -- delete the received message and cancel
            // the timeout event.
        EV << "Timer cancelled.\n";
        cancelEvent(timeoutEvent); //cancelamos el timer
        delete msg; //y borramos el mensaje de la red.

        // Ready to send another one.
        cMessage *newMsg = new cMessage("tictocMsg"); //se genera un nuevo mensaje
        send(newMsg, "out"); //se envía a la red
        scheduleAt(simTime()+timeout, timeoutEvent); //se envia el mensaje de timeout 1s despues.
    }
}

/**
 * Sends back an acknowledgement -- or not.
 */
class Toc8 : public cSimpleModule
{
  protected:
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Toc8);

void Toc8::handleMessage(cMessage *msg)
{

    //cuando Toc recibe el mensaje, existe la probabilidad que lo pierda
    if (uniform(0, 1) < 0.1) {
        EV << "\"Losing\" message.\n";
        bubble("message lost");  // making animation more informative...
        delete msg; //aqui borra el mensaje
    }

    //o que lo reciba y lo envíe de regreso
    else {
        EV << "Sending back same message as acknowledgement.\n";
        send(msg, "out"); //envia el mismo mensaje de regreso
    }
}
