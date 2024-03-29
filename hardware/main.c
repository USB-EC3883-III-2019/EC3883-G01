/* ###################################################################
**     Filename    : main.c
**     Project     : Solindar2
**     Processor   : MC9S08QE128CLK
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2019-10-23, 12:27, # CodeGen: 0
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
#include "TimerMotor.h"
#include "TimerDatos.h"
#include "AS1.h"
#include "Q1.h"
#include "Q2.h"
#include "Q3.h"
#include "Q4.h"
#include "AD1.h"
#include "Cap1.h"
#include "Trigger.h"
#include "TriggerTimer.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
char motor = 0;
char datos = 0;
char cap = 0;
/* User includes (#include below this line is not maintained by Processor Expert) */

void main(void)
{
  /* Write your local variable definition here */
char error = 0;
char Data[4] = {0, 0, 0, 0};
char A = 0;
char B = 0;
char Posicion = 0;
char Sentido = 0;
char Paso = 0;
int Lidar = 0;
char Sonar = 0;

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
	while (1){
		if (motor == 1){
				  //secuencia del motor controlada por timer para desplazarlo	 
				  if (Posicion < 72 & Sentido == 0)
					  Posicion++;
				  if (Posicion > 0 & Sentido == 1)
					  Posicion--;
				  if (Sentido == 0)
					  Paso = Posicion % 8;
				  else			  
					  Paso = (Posicion + 1) % 8;
				  	  	  if (Paso == 0 || Paso == 3)
				 			  Q1_NegVal();
				 		  if (Paso == 4 || Paso == 7)
				 			  Q2_NegVal();
				 		  if (Paso == 1 || Paso == 6)
				 			  Q3_NegVal();
				 		  if (Paso == 2 || Paso == 5)
				 			  Q4_NegVal();
				  // cambio de sentido
				  if (Posicion == 72)
					  Sentido = 1;
				  if (Posicion == 0)
					  Sentido = 0;
				  motor = 0;
			  }
		if (cap == 1){
					  		if (Cap1_GetPinValue()){
					  			Cap1_Reset();
					  		}
					  		else{
					  			Cap1_GetCaptureValue(&B);
					  			Sonar = B;
					  		}
					  		cap = 0;
	 }
		if (datos == 1){	
			 datos = 0;
			 Trigger_NegVal();
			 TriggerTimer_Enable();
			 AD1_Measure(1);
			 do{
			 			  			        error = 0;
			 			  		 		    error = AD1_GetChanValue16(0, &Lidar);
			 			  		 			 }while(error!=ERR_OK);
			 
	  	  	 Data[0] = Posicion;							
 		 	 Data[1] = (Sonar >> 2 ) + 128;
 		 	 Data[2] = ((Sonar & 0b00000011) << 5) + ((Lidar >> 11)& 0b00011111) + 128;
			 Data[3] = ((Lidar >> 4) & 0b01111111) + 128;
			  		do{												
			  	 		  	 	error = 0;
			  	 		  	 	error = AS1_SendBlock(Data, 4, &A);
			  		 		 }while(error!=ERR_OK);	
	}
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
