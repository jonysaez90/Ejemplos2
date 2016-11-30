

#include "funciones.h" 
#include "sAPI.h"



void maquina_estado()
{
      static int estado = INICIAL;

      switch(estado)
      {
         case INICIAL:
         
            if(NO_APRETO())
            {
               
               estado = INICIAL;
      
            }
            if(APRETO1())
            {
               
               estado = ESTADO1;
      
            }
            if(APRETO2())
            {
               
               estado = ESTADO2;
      
            }

            break;
         
         case ESTADO1:

            while(1){
         /*Enciendo secuencia de leds*/

         digitalWrite( LEDB, ON );
         displayuno();
         delay(500);
         digitalWrite( LEDB, OFF );
         digitalWrite(LED1,ON);
         displaydos();
         delay (500);
         digitalWrite(LED1, OFF);
         digitalWrite(LED2, ON);
         displaytres();
         delay(500);
         digitalWrite(LED2, OFF);
         digitalWrite(LED3, ON);
         displaycuatro();
         delay(500);
         digitalWrite(LED3, OFF);

         digitalWrite( LEDR, ON );
         displayuno();
         delay(500);
         digitalWrite( LEDR, OFF );
         digitalWrite(LED1,ON);
         displaydos();
         delay (500);
         digitalWrite(LED1, OFF);
         digitalWrite(LED2, ON);
         displaytres();
         delay(500);
         digitalWrite(LED2, OFF);
         digitalWrite(LED3, ON);
         displaycuatro();
         delay(500);
         digitalWrite(LED3, OFF);

         digitalWrite( LEDG, ON );
         displayuno();
         delay(500);
         digitalWrite( LEDG, OFF );
         digitalWrite(LED1,ON);
         displaydos();
         delay (500);
         digitalWrite(LED1, OFF);
         digitalWrite(LED2, ON);
         displaytres();
         delay(500);
         digitalWrite(LED2, OFF);
         digitalWrite(LED3, ON);
         displaycuatro();
         delay(500);
         digitalWrite(LED3, OFF);


       }
            
            if(APRETO2())
            {
               
               estado = ESTADO2;
      
            }
            if(NO_APRETO())
            {
               
               estado = ESTADO1;
      
            }

            break;
         
         case ESTADO2:
            //ACA VA CUANDO APRETAS TEC2
             digitalWrite (LED3,ON);
            if(APRETO1())
            {
               
               estado = ESTADO1;
      
            }
            if(NO_APRETO())
            {
               
               estado = ESTADO2;
      
            }

            break;
         
         default: estado = INICIAL;
      }


}


int NO_APRETO(void)
{
   int res = 0 ;

  if(digitalRead(TEC1) ==OFF){  //apretaste
         res=1;
         return res;
  }
   
  if(digitalRead(TEC2) ==OFF){
      res=1;
       return res;
  }  
   return res;

}



int APRETO1(void)
{
   int res = 0 ;

   if (digitalRead(TEC1)==OFF){
       res=1;        
   }
   else{
      res=0;
   }
   return res;

}



int APRETO2(void)
{
int res = 0 ;

   if (digitalRead(TEC2)==OFF){
       res=1;        
   }
   else{
      res=0;
   }
   return res;

}





