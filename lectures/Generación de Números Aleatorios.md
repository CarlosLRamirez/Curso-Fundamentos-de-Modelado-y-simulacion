# Generación de Números Aleatorios

La generación de números aleatorios son un ingrediente fundamental en la simulación de la mayoría de sistemas discretos.

La mayoría de lenguajes de computadora tienen subrutinas, objetos o funciones que generan números aleatorios.

## Propiedades de los números aleatorios

Una secuencia de números aleatorios $R_{1},R_{2},...$, debe tener dos propiedades estadísticas importantes: 

1. *uniformidad*, es decir, son igualmente probables en cualquier parte. 
2. *independencia*, es decir, el valor actual de una variable aleatorio no tiene relación con el valor anterior.

Cada numero aleatorio $R_{1}$ es una muestra independiente extraída de una distribución uniforme continua entre cero y uno.

Función de Distribución de Probabilidad

$$f(x)= \begin{cases}1, & 0 \leqslant x \leqslant 1 \\ 0, & \text { de lo contrario }\end{cases}$$

Valor esperado

$$E(R)=\int_0^1 x d x=\left.\frac{x^2}{2}\right|_0 ^1=\frac{1}{2}$$

Varianza

$$V(R)=\int_0^1 x^2 d x-[E(R)]^2=\left.\frac{x^3}{3}\right|_0 ^1-\left(\frac{1}{2}\right)^2=\frac{1}{3}-\frac{1}{4}=\frac{1}{12}$$

Algunas consecuencias de las propiedades de uniformidad e independencia:
1. Si el intervalo $(0,1)$ es dividido en $n$ sub-intervalos de igual longitud, el numero esperado de observaciones de cada intervalo es $N/n$ donde $N$ es el número total de observaciones. Nótese que $N$ tiene que ser lo suficientemente largo para mostrar esta tendencia.
2. La probabilidad de observar un valor en un intervalo particular es independiente del valor previo dibujados.

## Generación de Números Pseudo-aleatorios

- El mero acto de utilizar un *método conocido* para generar números aleatorios remueve el potencial de una aleatoriedad verdadera.

- Si el método es conocido, el conjunto de números aleatorios puede ser repetido, por lo que se puede decir que los números no son verdaderamente aleatorios.

- Generar números verdaderamente aleatorios requiere acceso a un proceso físico aleatorio, lo que puede ser impracticable para muchos usos computacionales debido a la dificultad de acceso y la lentitud del proceso. Los algoritmos para generar números pseudo-aleatorios, por otro lado, pueden producir números a una velocidad mucho mayor.

- El objetivo de cualquier esquema de generación es, sin embargo, producir una secuencia de números entre 0 y 1 que simule o imite las propiedades ideales de distribución uniforme e independencia lo más cercano posible.

- En una simulación por computadora, a menudo nos interesa tener números pseudo-aleatorios, porque nos permiten tener el control de los números aleatorios para poder **repetir** el experimento.

- En general, se utiliza una forma sistemática de generar números pseudo-aleatorios, estos números son completamente predecibles si se conoce el algoritmo y el valor inicial (semilla).

//- Primero generamos los números aleatorios distribuidos uniformemente; después los utilizamos para generar números aleatorios de otra distribución.

- Los métodos utilizados por una computadora para generar números pseudo-aleatorios, deben tener en cuenta las siguientes consideraciones:
    -  El método debe ser rápido.
    - La rutina debe ser portable a través de plataformas de hardware y lenguajes de programación.
    - La rutina debe tener un ciclo suficientemente largo.
- La longitud de un ciclo representa la longitud de la secuencia de números aleatorios antes de que los números anteriores empiecen a repetirse en un orden anterior. Por ejemplo
4,9,5,6,9,3,8, 4,9,5,6,9,3,8, 4,9,5,6,9,3,8, ...
parece tener una longitud de ciclo de 7 (esto es sólo un ejemplo de ciclo, ¡un número aleatorio de ciclo 7 es completamente inaccesible!)
Un caso especial de ciclo es la degeneración, en la que los mismos números aleatorios aparecen repetidamente.
Como utilizamos un algoritmo para generar números aleatorios, los ciclos no se pueden evitar. Pero los ciclos largos (por ejemplo, algunos millones o algunos miles de millones) sirven al propósito de las simulaciones generales.
Los números aleatorios deben poder reproducirse.
Y lo que es más importante, los números aleatorios generados deben aproximarse mucho a las propiedades estadísticas ideales de uniformidad e independencia.