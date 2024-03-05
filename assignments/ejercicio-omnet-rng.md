Escuela de Estudios de Postgrado

Facultad de Ingeniería

Universidad de San Carlos de Guatemala

Maestría en Ingeniería para la Industria con Especialidad en Telecomunicaciones

Curso: Fundamentos de Modelado y Simulación

Ejercicio Práctico

# Generadores de Números Aleatorios (GNA) con Omnet++

Basado en el ejercicio 2, implemente generadores de números aleatorios para generar el tiempo entre llegadas T.

1. Implemente un Generador Congruencial Lineal de números aleatorios en OMNeT++ (GCL) basado en el método:

$$d_{i}=16807d_{i-1}mod(2^{31-1})$$

2. Genere la distribución uniforme de tiempo entre llegadas T (e.g. `uniform (0,2`) basado en el GNA GCL).

3. Genere la distribución exponencial T (e.g. `exponencial(1)`)

4. Compare los nuevos resultados de la simulación con los anteriores donde utilizó el GNA de OMNeT++ (Mersenne Twister)

5. ¿Cuales características deberían tener los "buenos" generadores de números aleatorios? ¿Usted cree que el GNA GCL es un "buen" GNA y porque?

6. En un programa de simulación para un sistema radio móvil celular es requerido inicialmente distribuir N estaciones móviles uniformemente distribuidas en un area de un circulo con radio R. Para cada estación móvil el angulo $\phi_{i}$ y el radio $r_{i}$ debe ser generado. Describa el algoritmo.

