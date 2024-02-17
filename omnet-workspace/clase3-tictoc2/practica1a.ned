//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

simple Nodo2
{
    parameters:
        volatile double tiempoRetardo @unit(s)=  default(1s);
      	volatile double tazaPerdida = default(1);
       
        //Timeout para generar nuevos mensajes (aplica para todo los nodos), default 10s
        //este valor debe tomar en cuenta la suma de: el tiempo de transmision, el tiempo de retardo, por la cantidad de nodos en la red.
        //10s es un valor optimo para una red de 3 nodos, con delay de transmision de 2s, y tiempos de retardo de 1s
        double timeout @unit(s) = default(10s); 
    gates:
        input entrada[];
        output salida[];
}

network Practica1a
{
   
    
    types:
        channel Canal extends ned.DelayChannel
        {
            delay = 2s;
        }
    submodules:
        nodo[4]: Nodo2;
    connections:
        nodo[0].salida++ --> Canal --> nodo[1].entrada++;
//        nodo[0].entrada++ <-- Canal <-- nodo[1].salida++;

        nodo[1].salida++ --> Canal --> nodo[2].entrada++;
//       nodo[1].entrada++ <-- Canal <-- nodo[2].salida++; 
               
        nodo[2].salida++ --> Canal --> nodo[3].entrada++;
//        nodo[2].entrada++ <-- Canal <-- nodo[0].salida++;

        nodo[3].salida++ --> Canal --> nodo[0].entrada++;
//        nodo[2].entrada++ <-- Canal <-- nodo[0].salida++;
}
