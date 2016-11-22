/* Copyright 2014, 2015, 2016 Mariano Cerdeiro
 * Copyright 2014, Gustavo Muro
 * Copyright 2014, Pablo Ridolfi
 * Copyright 2014, Juan Cecconi
 * Copyright 2014, Fernando Beunza
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief ADC DAC example source file
 **
 ** This is a mini example of the CIAA Firmware
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup ADC_DAC ADC & DAC example source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 * GMuro        Gustavo Muro
 * PR           Pablo Ridolfi
 * JuCe         Juan Cecconi
 * FB           Fernando Beunza
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20140805 v0.0.1   GMuro first functional version
 */

/*==================[inclusions]=============================================*/
#include "os.h"
//#include "ciaaPOSIX_stdio.h"
//#include "ciaaPOSIX_stdlib.h"
#include "ciaak.h"            /* <= ciaa kernel header */
#include "adc_dac_RTOS.h"
//#include "chip.h"
#include "sAPI.h"

uint16_t analogValue = 0;
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/




/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */
int main(void)
{
   /* Starts the operating system in the Application Mode 1 */
   /* This example has only one Application Mode */
   StartOS(AppMode1);

   /* StartOs shall never returns, but to avoid compiler warnings or errors
    * 0 is returned */
   return 0;
}

/** \brief Error Hook function
 *
 * This fucntion is called from the os if an os interface (API) returns an
 * error. Is for debugging proposes. If called this function triggers a
 * ShutdownOs which ends in a while(1).
 *
 * The values:
 *    OSErrorGetServiceId
 *    OSErrorGetParam1
 *    OSErrorGetParam2
 *    OSErrorGetParam3
 *    OSErrorGetRet
 *
 * will provide you the interface, the input parameters and the returned value.
 * For more details see the OSEK specification:
 * http://portal.osek-vdx.org/files/pdf/specs/os223.pdf
 *
 */
void ErrorHook(void)
{
   ciaaPOSIX_printf("ErrorHook was called\n");
   ciaaPOSIX_printf("Service: %d, P1: %d, P2: %d, P3: %d, RET: %d\n", OSErrorGetServiceId(), OSErrorGetParam1(), OSErrorGetParam2(), OSErrorGetParam3(), OSErrorGetRet());
   ShutdownOS(0);
}

/** \brief Initial task
 *
 * This task is started automatically in the application mode 1.
 */
TASK(inicio)
{


   /* init the ciaa kernel
   ciaak_start();*/

	 /* Inicializar la placa */
		   boardConfig();

		   /* Configuración de pines de entrada para Teclas de la CIAA-NXP */
		      digitalConfig( TEC1, INPUT );
		      digitalConfig( TEC2, INPUT );
		      digitalConfig( TEC3, INPUT );
		      digitalConfig( TEC4, INPUT );

		      /* Configuración de pines de salida para Leds de la CIAA-NXP */
		         digitalConfig( LEDR, OUTPUT );
		         digitalConfig( LEDG, OUTPUT );
		         digitalConfig( LEDB, OUTPUT );
		         digitalConfig( LED1, OUTPUT );
		         digitalConfig( LED2, OUTPUT );
		         digitalConfig( LED3, OUTPUT );

		      /* Inicializar UART_USB a 115200 baudios */
		          uartConfig( UART_USB, 115200 );


		          analogConfig( ENABLE_ANALOG_INPUTS );  /* ADC */
		          analogConfig( ENABLE_ANALOG_OUTPUTS ); /* DAC */

		          ActivateTask(medida_analogica);

   TerminateTask();
}

/** \brief Read ADC values
 *
 * This task is activated every 1ms by the AnalogicAlarm configured in
 * adc_dac.oil
 */


TASK (salida_digital){
	 WaitEvent(mostrar_medida);
	 ClearEvent(mostrar_medida);
	 GetResource(res_adc);

	if(digitalRead(TEC2)==OFF){
			 digitalWrite( LEDB, OFF ); //enciendo led azul
			 /* Escribo la muestra en la Salida AnalogicaAO - DAC */
			 	analogWrite( AO, analogValue );
	}
	ReleaseResource(res_adc);
	    ActivateTask(medida_analogica);
		TerminateTask();
	//ChainTask(medida_analogica);

}

TASK(medida_analogica)
{

		/* Leo la Entrada Analogica AI0 - ADC0 CH1 */

		         if(digitalRead(TEC1)==OFF){
		        	 analogValue = analogRead( AI0 );
		             digitalWrite( LEDB, ON ); //enciendo led azul
		             ActivateTask(salida_digital);
		             SetEvent(salida_digital,mostrar_medida);

		             TerminateTask();
		         }
		         ChainTask(medida_analogica);
}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

