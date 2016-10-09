#include <stdio.h>
#include <wiringPi.h>


#define	LED	17                      // Declaraciòn de pin # 17 de la Raspberry

int parpadeo ()
{
  int x;                            // varaible que controla si ocurre un error
  wiringPiSetup () ;                // Funciòn para poder utilizar los gpios de la Raspberry  
  pinMode (LED, OUTPUT) ;           // Se declara que el pin "LED" es una salida de la Raspberry
if x==1{                            // si ocurre algùn error un led parpadea
  for (;;)
  {
    digitalWrite (LED, HIGH) ;	    // se enciende el led
    delay (500) ;		            // se mantiene la acciòn del led encendido por 500 ms
    digitalWrite (LED, LOW) ;	    // se apaga el led
    delay (500) ;                   // se mantiene la acciòn del led encendido por 500 ms
  }
}
// si se notifica que se sabe del error o que no existe error alguno
else
{ 	digitalWrite (LED, LOW);        // se apaga el led
}
  return 0 ;                        // Fin del programa
}
