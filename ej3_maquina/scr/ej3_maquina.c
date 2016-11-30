
#include "ej3_maquina.h"
#include "funciones.h"
#include "sAPI.h"
#ifndef CPU
#error CPU shall be defined
#endif

int main(void)
{



	/* Inicializar la placa */
		boardConfig();
		/* Inicializar DigitalIO */
		digitalConfig( 0, ENABLE_DIGITAL_IO);

		/* Configuración de pines de entrada para
		   Teclas de la CIAA-NXP */
		digitalConfig( TEC1, INPUT );
		digitalConfig( TEC2, INPUT );
		digitalConfig( TEC3, INPUT );
		digitalConfig( TEC4, INPUT );
		/* DESDE MAPA DE PERIFERICOS   GPIO0 = DIO32*/
		digitalConfig( DIO32, INPUT_PULLUP ); //PARA CONECTAR CON PULLUP..segun facu es mas interesante
		/* Configuración de pines de salida para
		   Leds de la CIAA-NXP */
		digitalConfig( LEDR, OUTPUT );
		digitalConfig( LEDG, OUTPUT );
		digitalConfig( LEDB, OUTPUT );
		digitalConfig( LED1, OUTPUT );
		digitalConfig( LED2, OUTPUT );
		digitalConfig( LED3, OUTPUT );





	while(1){

		maquina_estado();

	}
}

