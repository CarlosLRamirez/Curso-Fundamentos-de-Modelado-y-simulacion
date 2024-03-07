# Generación de Variables Aleatorias

Ahora que hemos aprendido a generar una variable aleatoria uniformemente distribuida, estudiaremos cómo producir variables aleatorias de otra distribución utilizando la variable aleatoria uniformemente distribuida.

Se asume que se tiene una fuente de números aleatorios uniformes entre $(0,1)$, $R_1, R_2, ...$, en donde se tienen las siguientes funciones:

Función de Densidad de Probabilidad

$$f_R(x)=\begin{cases}
0, & 0 \leq x \leq 1  \\
1, & \text{ de lo contrario } 
\end{cases}$$

Función de Probabilidad Acumulada

$$f_R(x)=\begin{cases}
0, & x < 0  \\
x, & 0 \leq x \leq 1  \\ 
1, & x > 0 
\end{cases}$$

## Técnica de la transformación inversa

- La técnica de la transformación inversa puede utilizarse para tomar muestras de las distribuciones exponenciales, uniformes, Weibulll y triangulares.
- El principio básico es encontrar la función inversa de $F$, $F^{-1}$ tal que $FF^{-1}=F^{-1}F=1$
- $F^{-1}$ denota la solución a la ecuación $r=F(x)$ en términos de $r$, no $1/F$. 
- Por ejemplo, la inversa de $y=x$ es $x=y$, la inversa de $y=2x+1$ es $x=(y-1)/2$, la inversa de $y=x^{2}-1$ es $x=\sqrt{y+1}$

## Generación de una Distribución Exponencial

Recordemos la distribución exponencial

- Función de densidad de probabilidad:

$$f(x)=\begin{cases}
\lambda e^{-\lambda x}, & x \geq 0  \\
0, & x < 0  \\ 
\end{cases}$$


- Función de probabilidad acumulada

$$F(x)=\int_{-\infty}^x f(t) d t=\begin{cases}
1-e^{-\lambda x}, & x \geq 0  \\
0, & x < 0  \\ 
\end{cases}$$

Este método puede ser utilizado para cual distribución en teoría. Pero es particularmente util para variables aleatorias cuyo función inversa puede ser resuelta con facilidad.

Los pasos son los siguientes:

**Paso 1:**

- Obtenga la función de probabilidad acumulada para la variable aleatoria $X$.
- Para la distribución exponencial, la función de probabilidad acumulada es $F(X)=1-e^{-\lambda x}$

**Paso 2**

- Definir $R=F(X)$ en el rango de $X$
- Para la distribución exponencial, $R=1-e^{-\lambda x}$ en el rango de $x \geqslant 0$.

**Paso 3**

- Resolver la ecuación $F(X) = R$ para $X$ en términos de $R$.
- Para la distribución exponencial, la solución es la siguiente:
  
$$\begin{align} 
1-e^{-\lambda X} & =R \\ 
e^{-\lambda X} & =1-R \\
-\lambda X & =\ln (1-R) \\
X & =-\frac{1}{\lambda} \ln (1-R)
\end{align}$$

  A la ultima ecuación se le llama generador de la variable aleatoria para la distribución exponencial. En general se escribe como $X=F^{-1}(R)$.

**Paso 4**

Generar (según sea necesario) los números aleatorios $R_1, R_2, ...$ y calcular las variables aleatorias deseadas mediante.

$$X_i=F^{-1}(R_i)$$

En el caso de la distribución exponencial

$$X_i=\frac{-1}{\lambda}\ln{(1-R_i)}$$

para $i=1,2,3...$ donde $R_i$ es un numero aleatorio uniformemente distribuido entre $(0,1)$.

En la práctica, dado que tanto $R_i$ como $1-R_i$, son números aleatorios uniformemente distribuidos, el calculo puede simplificarse según:

$$X_i=\frac{-1}{\lambda}\ln{(R_i)}$$

Una vez tenemos este procedimiento establecido, podemos proceder a resolver otras distribuciones similares para las cuales la función inversa es relativamente fácil de obtener y tiene una formula cerrada.

## Generación de una Distribución Uniforme

Si $X$ es una variable aleatoria uniformemente distribuida entre el intervalo $[a,b]$, la función para generar $X$ esta dada por $X = a + (b-a)R$. Veamos el paso a paso:

La función de densidad de probabilidad de X esta dada por:

$$f_(x)=\begin{cases}
\frac{1}{b-a} & a \leq x \leq b \\
0 & \text { de lo contrario }
\end{cases}$$

**Paso 1**: La función de densidad acumulada es:

$$F(x)=\begin{cases}
0 & x < a \\
\frac{x-a}{b-a} & a \leq x \leq b \\
1 & x>b
\end{cases}$$ 

**Paso 2**: Definimos $F(X)=(X-a)/(b-a)=R$

**Paso 3**: Resolvemos $X$ en términos de $R$ obtenemos

$$X=a+(b-a)R$$

**Paso 4**: Generamos $R_i$ según sea necesario, calculamos $X_i$ utilizando la función obtenida.

## Generación de una Distribución Weibull

La función de densidad de probabilidad es:

$$f(x)= \begin{cases}
\frac{\beta}{\alpha^\beta} x^{\beta-1} e^{-(x / \alpha)^\beta}, & x \geq 0 \\ 
0, & \text { otherwise }
\end{cases}$$

**Paso 1** 

Obtenemos la función de probabilidad acumulada:

$$F(x)=1-e^{-(x / \alpha)^\beta}, x \geqslant 0$$

**Paso 2**

Definimos $F(x)=1-e^{-(x / \alpha)^\beta} = R$

**Paso 3**

Resolvemos para $X$ en términos de $R$, obtenemos:

$$X=\alpha[-\ln (1-R)]^{1 / \beta}$$

**Paso 4**

Generar valores de $R_i$ uniformemente distribuidos entre $(0,1)$, para calcular valores de $X$, según la función del paso 3.

## Generación de una Distribución Triangular

Función de densidad de probabilidad

$$f(x)=\begin{cases}
x & 0 \leq x \leq 1\\
2-x & 1 < x \leq 2 \\ 
0 & \text{de lo contrario}
\end{cases}$$

**Paso 1**

Función de probabilidad acumulada

$$F(x)= \begin{cases}
0 & x \leq 0 \\
\frac{x^2}{2} & 0 < x \leq 1 \\
1 - \frac{(2-x)^2}{2} & 1 < x \leq 2 \\
1 & x > 2
\end{cases}$$

**Paso 2**

Para $0 < X \leq 1$

$$R=\frac{X^2}{2}$$

y para $1< X \leq 2$

$$R=1-\frac{(2-X)^{2}}{2}$$

**Paso 3**

Resolver $X$ en términos de $R$

$$X= \begin{cases}
\sqrt{2R} & 0 < R \leq \frac{1}{2}
\\ 2 - \sqrt{2(1-R)} & \frac{1}{2} < R \leq 1
\end{cases}$$

**Paso 4**

Generar valores de $R_i$ uniformemente distribuidos entre $(0,1)$, para calcular valores de $X$, según la función del paso 3.

### Ejercicio 1

- Mediante una hoja de calculo o cualquier lenguaje de programación, genere una secuencia de 1000 números pseudo-aleatorios mediante un generador congruencial lineal con los siguientes parámetros $m = 2^{32}$ , $a = 1664525$ , $c = 1013904223$ , $X0 = 123456789$.

- A partir de dicha secuencia, genere variables aleatorias con una distribución exponencial, con un valor de $\lambda=1$
- Genere gráficos tipo histograma tanto de la secuencia de número aleatorios como de la variable aleatoria calculada.
- Calcule la media y desviación estándar de los valores calculados para la variable aleatoria.
- Compare los histogramas empíricos y los valores estadísticos con los valores teóricos para una distribución exponencial.


### Ejercicio 2

- Mediante una hoja de calculo o cualquier lenguaje de programación, genere una secuencia de 1000 números pseudo-aleatorios mediante un generador congruencial lineal con los siguientes parámetros $m = 2^{32}$ , $a = 1664525$ , $c = 1013904223$ , $X0 = 123456789$.

- A partir de dicha secuencia, genere variables aleatorias con una distribución uniforme entre 0 y 5.
- Genere gráficos tipo histograma tanto de la secuencia de número aleatorios como de la variable aleatoria calculada.
- Calcule la media y desviación estándar de los valores calculados para la variable aleatoria.
- Compare los histogramas empíricos y los valores estadísticos con los valores teóricos para una distribución exponencial.
