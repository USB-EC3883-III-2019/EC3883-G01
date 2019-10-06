/* ###################################################################
**     Filename    : main.c
**     Project     : Solindar
**     Processor   : MC9S08QE128CLK
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2019-10-02, 11:33, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.12
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "AD1.h"
#include "TimerMotor.h"
#include "AS1.h"
#include "Lidar.h"
#include "TimerData.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
char	motor = 0;
char	datos = 0;
/* User includes (#include below this line is not maintained by Processor Expert) */

void main(void)
{
  /* Write your local variable definition here */
	char Data[4] = {0 ,0 ,0 ,0};
	char Secuencia[4] = {0 ,0 ,0 ,0};
	char Sonar = 0;
	char ADC = 0;
	char Posicion = 0;
	char Sentido = 0;
	int Lidar = 0;
	char error = 0;
	char A = 0;
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  while (1){
	  if (motor == 1){
		  //secuencia del motor controlada por timer para desplazarlo
		  //falta tabla del motor
		  if (Posicion < 30 & Sentido == 0)
			  Posicion++;
		  if (Posicion > 0 & Sentido == 1)
			  Posicion--;
		  // cambio de sentido
		  if (Posicion == 30)
			  Sentido = 1;
		  if (Posicion == 0)
			  Sentido = 0;
		  motor = 0;
	  }
	  if (datos ==1){
		  //recoleccion de datos 
		  // timer para evitar tomar medidas en movimiento
		  datos = 0;
	  }
	  //empaquetamiento
	   			  		do{
	   			  			        error = 0;
	   			  		 		    error = AD1_GetChanValue16(0,&ADC);	 
	   			  		 			 }while(error!=ERR_OK);
	   			  		Lidar = ADC;
	   			  		Sonar = Sonar / 58; //conversion a cm
	   			  		Data[0] = Posicion;
	   			  		Data[1] = (Sonar >> 2) + 128;
	   			  		Data[2] = ((Sonar & 0b00000011) << 5)+ ((Lidar & 0b111110000000) >> 7) + 128;
	   			  		Data[4] = Lidar & 0b000001111111;
	   			  		do{												//enviado del paquete ya codificado
	   			  	 		  	 	error = 0;
	   			  	  		 	    error = AS1_SendBlock(Data,4,&A);
	   			  		 		 }while(error!=ERR_OK);
  }
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
