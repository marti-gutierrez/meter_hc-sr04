# Metro digital con sensor HC-SR04

Este proyecto se trata de crear un metro digital con ayuda del sensor ultrasonico
**HC-SR04**, y para ayudarnos de controlar usaremos el uC *ATmega328p* del **Arduino Uno**, debido a que
fue fácil la prototipación, pero el algoritmo se puede ocupar en otras familias de microcontroladores.

## Algoritmo

1. Asignamos el pin conectado a **trigger** como salida.
2. Asignamos el pin conectado a **echo** como entrada y generaremos una interrupción para flanco de subida.
3. Iniciamos el timer en cero.

## Elección de timer(contador de echo).

En los uC de la familia AVR, el ciclo de instrucción es igual al periodo del oscilador, en este caso $$ciclo = \dfrac{1}{F_{osc}}= \dfrac{1}{16 MHz}= 62.5 ns$$.

Considerando que el máximo tiempo que debe de contar es *38 mseg*, que nos indica que no detecto ningún objeto, debemos usar un prescalador que nos ayude a retardar el timer.
Al usar el *timer0* obtenemos que $$t=255\cdot\dfrac{prescalador}{F_{osc}}$$ creamos una desigualdad para saber que tan grande tiene que ser el prescalador
$$prescalador\geq\dfrac{F_{osc}\cdot t}{255}\rightarrow\dfrac{16 MHz\times 38mseg}{255}$$ 

$$prescalador\geq 2385$$
el problema es que el maximo prescalador que tenemos es de 1024, por lo cual usaremos el timer1 el cual realiza $2^{16}-1=65535$ cuentas, cambiando este valor del 255.

$$prescalador\geq\dfrac{F_{osc}\cdot t}{65535}\rightarrow\dfrac{16 MHz\times 38mseg}{65535}$$ 
$$prescalador\geq 10$$

Como el prescalador debe ser mayor a 10 usaremos el *prescalador 64*, obteniendo un tiempo máximo de 262.14ms 
