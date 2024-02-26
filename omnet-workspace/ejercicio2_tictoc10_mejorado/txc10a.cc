//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003 Ahmet Sekercioglu
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
 * Let's make it more interesting by using several (n) `tic' modules,
 * and connecting every module to every other. For now, let's keep it
 * simple what they do: module 0 generates a message, and the others
 * keep tossing it around in random directions until it arrives at
 * module 2.
 */
class Txc10a : public cSimpleModule
{
  protected:
    virtual void forwardMessage(cMessage *msg, int gateIndex);
    virtual void justforwardMessage(cMessage *msg);
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Txc10a);

void Txc10a::initialize()
{
    if (getIndex() == 0) {
        // Boot the process scheduling the initial message as a self-message.
        char msgname[20];
        sprintf(msgname, "tic-%d", getIndex());
        cMessage *msg = new cMessage(msgname);
        EV << "sending message " << msg << " at boot.\n";
        scheduleAt(0.0, msg);
    }
}

void Txc10a::handleMessage(cMessage *msg)
{

    cGate* arrivalGate = msg->getArrivalGate(); //por donde vino?

    if (arrivalGate != nullptr) { // si vino de un puerto

        if (getIndex() == 3) {
            // Message arrived.
            EV << "Message " << msg << " finally arrived arrived.\n";
            delete msg;
        }
        else {
            int gateIndex = arrivalGate->getIndex(); // cual fue el numero de puerto
            EV << "Message " << msg << " arrived at gate " << gateIndex << ".\n";
            forwardMessage(msg,gateIndex); //reenviamos el mensaje, evitando el puerto donde vino
        }
    }
    else {
           justforwardMessage(msg);
    }
}

void Txc10a::forwardMessage(cMessage *msg, int gateIndex)
{
    // In this example, we just pick a random gate to send it on.
    // We draw a random number between 0 and the size of gate `out[]'.
    int n = gateSize("out");

    if (n <= 1) {
           send(msg, "out", gateIndex); // Enviandolo de regreso por el mismo puerto donde vino
           return;
    }

    int k;
    do {
        k = intuniform(0, n-1); // generar un numero aleatorio entre 0 y n-1
    } while (k == gateIndex); // seguir probando hasta que k sea diferente al puerto donde entro


    EV << "Forwarding message " << msg << " on port out[" << k << "]\n";
    send(msg, "out", k);
}

void Txc10a::justforwardMessage(cMessage *msg)
{
    // In this example, we just pick a random gate to send it on.
    // We draw a random number between 0 and the size of gate `out[]'.
    int n = gateSize("out");
    int k = intuniform(0, n-1);

    EV << "Forwarding message " << msg << " on port out[" << k << "]\n";
    send(msg, "out", k);
}

