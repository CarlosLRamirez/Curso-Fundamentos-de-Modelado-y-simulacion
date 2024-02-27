# Generacion de Números Aleatorios

La generación de numeros aleatorios son un ingrediente fundamenteal en la simulación de la mayoria de sistemas discretos.

La mayoria de lenguajes de computadora tienen subrutines, objetos o funciones que generan números aleatorios.

## Propiedades de los números aleatorios

Una sequencia de números aleatorios $R_{1},R_{2},...$, debe tener dos propiedades estadísticas importantes: 

1. *uniformidad*, es decir, son igualmente probables en cualquier parte. 
2. *independencia*, es decir, el valor actual de una variable aleatorio no tiene relación con el valor anterior.

Cada numero aleatorio $R_{1}$ es una muestra independiente extraída de una distribución uniforme contínua entre cero y uno.

Función de Distribución de Probabilidad

$$f(x)= \begin{cases}1, & 0 \leqslant x \leqslant 1 \\ 0, & \text { de lo contrario }\end{cases}$$

Valor esperado

$$E(R)=\int_0^1 x d x=\left.\frac{x^2}{2}\right|_0 ^1=\frac{1}{2}$$

Varianza

$$V(R)=\int_0^1 x^2 d x-[E(R)]^2=\left.\frac{x^3}{3}\right|_0 ^1-\left(\frac{1}{2}\right)^2=\frac{1}{3}-\frac{1}{4}=\frac{1}{12}$$


Inline equation: $\pi \approx 3.14159$

$$\pi \approx 3.14159$$

$\forall \, x \in (1,2)$

$\mathcal A$

Display equation: $$equation$$