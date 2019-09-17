/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#define OPT 1;
const uint8 Data_Value[]={0xDF,0x03,0x4B,0x4F,0x26,0x2D,0x7D,0x47,0xFF,0x67};
volatile uint8 Flag_Action=1;
volatile uint8 Flag_Auth=0; //Convertidor_INCREMENTO
volatile uint8 data[4];
volatile uint32 Conter=0; //variable de conteo
volatile uint32 select_Num=0;
//Codigo_de_Salida_BCD
void Seg_Conversion(uint8 data);//conversion_7Segmentos
void Dec_BCD_Conversion(uint8 data_Input); //funcion de conversion de datos
void Sequencia(void);
void Contador_Objt(void);
void Contador_Num(void);
void Increase_Flag();
int main(void)
{
    //CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    //Debouncer1 
   
    for(;;)
    {
     CyDelay(90);
     while(Boton_Data_Read()!=1){
       Flag_Auth=1; //AUTORIRZA_EVALUCACION
     } 
     if(Flag_Auth==1){
       Increase_Flag();
     };
    Sequencia();
    
        /* Place your application code here. */
    }
}
/*
void Seg_Conversion(uint8 data[4]){
 

}
*/
void Sequencia(){
  if(Flag_Action==0){
    Contador_Num();
  }else{
    Conter=0;
    Contador_Objt();
  }
}
///
void Increase_Flag(void){
 if(select_Num<2){
  Flag_Action++;
 }else{
  Flag_Action=0;
}
}
#ifdef OPT  
void Contador_Num(){
    if(Conter<=999){
      Conter++;
    }else{
      Conter=0;  
    }
}
#else
void Contador_Num(){
Conter++;
}  
#endif
void Contador_Objt(){
  while(Sensor_Read()!=1){
   CyDelay(10);
   Conter++;
  }
    
}

/* [] END OF FILE */
