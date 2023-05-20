# Metro digital con sensor HC-SR04

Este proyecto se trata de crear un metro digital con ayuda del sensor ultrasonico
**HC-SR04**, y para ayudarnos de controlar usaremos el uC *ATmega328p* del **Arduino Uno**, debido a que
fue fácil la prototipación, pero el algoritmo se puede ocupar en otras familias de microcontroladores.

## Algoritmo de sensor ultrasonico

1. Asignamos el pin conectado a **trigger** como salida.
2. Asignamos el pin conectado a **echo** como entrada
3. Generamos un pulso alto de 10us en el *pin trigger* y despues lo apagamos.
4. Esperamos 220us a obtener una respuesta del *pin echo*.
5. **mientras** el pin echo este en estado bajo **0 (low)**, esperar en el punto 5, si no pasar al siguiente paso.
6. Activar el **Timer1** cambiando el prescalador a 64.
7. **mientras** el pin echo este en estado alto **1 (high)**, esperar en el punto 7, si no pasar al siguiente paso.
8. Detener el **Timer1**

## Elección de timer(contador de echo).

En los uC de la familia AVR, el ciclo de instrucción es igual al periodo del oscilador, en este caso $$ciclo = \dfrac{1}{F_{osc}}= \dfrac{1}{16 MHz}= 62.5 ns$$.

Considerando que el máximo tiempo que debe de contar es *38 mseg*, que nos indica que no detecto ningún objeto, debemos usar un prescalador que nos ayude a retardar el timer.
Al usar el *timer0* obtenemos que $$t=255\cdot\dfrac{prescalador}{F_{osc}}$$ creamos una desigualdad para saber que tan grande tiene que ser el prescalador
$$prescalador\geq\dfrac{F_{osc}\cdot t}{255}\rightarrow\dfrac{16 MHz\times 38mseg}{255}$$ 

$$prescalador\geq 2385$$
el problema es que el maximo prescalador que tenemos es de 1024, por lo cual usaremos el timer1 el cual realiza $2^{16}-1=65535$ cuentas, cambiando este valor del 255.

$$prescalador\geq\dfrac{F_{osc}\cdot t}{65535}\rightarrow\dfrac{16 MHz\times 38mseg}{65535}$$ 

$$prescalador\geq 10$$

Como el prescalador debe ser mayor a 10 usaremos el *prescalador 64*, obteniendo un tiempo máximo de 262.14ms. Teniendo el valor del prescalador y el oscilador obtenemos el valor por el que tendremos que multiplicar nuestro registro de 16-bits (TCNT1).

$$t=\dfrac{prescalador}{F_{osc}}\cdot TCNT1=\dfrac{64}{16\times 10^6 Hz}\cdot TCNT1$$

$$t=4\mu s\cdot TCNT1$$

## Cálculo para obtener distancia.

El sensor utiliza la formula $v=\dfrac{2\cdot d}{t}$, tomando la velocidad del sonido $340\frac{m}{s}$ pero como vamos a trabajar con cm y $\mu s$ la conversión quedaria como $0.034\frac{cm}{\mu s}$.

Como queremos obtener la distancia el despeja de la formula quedaria como:

$$d=\dfrac{v\cdot t}{2}=\dfrac{0.034\frac{cm}{\mu s}\cdot TCNT1\cdot4\mu s}{2}$$

$$ d = TCNT1\times 0.068 cm$$
