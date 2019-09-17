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
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
volatile uint16 Horas=0;
volatile uint16 Href=0;
volatile uint16 Sref=0;
volatile uint16 Mref=0;
volatile uint16 Minutos=0;
volatile uint16 Segundos=0;
volatile uint8 Flag_Sound=0;
volatile uint8 Register2=1;
volatile uint8 cont_event=1;
volatile uint8 cont_start=0;
volatile uint8 r_visual=0;
volatile char data_s;
volatile char enter;
volatile uint8 Type=0;
volatile uint8 Data=0;
volatile uint8 Unidad=0;
volatile uint8 Decena=0;
volatile uint8 Centena=0;
volatile uint8 Mil=0;
volatile uint8 Data_Value=0; //variable_de_datos
void visualizacion(char *data_print);
//volatile uint8 Centena=0;
void Switch_Counter(){
 if(cont_event<=4){
  cont_event++;
 }else{
  cont_event=1;
 }
switch(cont_event){
  case 1:
     Unidad=Data;
  case 2:
     Decena=Data;
  case 3:
      Centena=Data;
  case 4:
       Mil=Data;
}
}
void Type_Load(int x){
   char *Datos_print="";
   char *time_H="";
   char *time_L=""; 
   uint8 trx=10*Decena+Unidad;
   uint8 trx1=10*Mil+Unidad; 
   switch(r_visual){
   case 1:
     
      //Sref=Mil*1000+Centena*100+Decena*10+Unidad;
      if(x==1){
      Sref=Mil*1000+Centena*100+Decena*10+Unidad;
      itoa( Sref,Datos_print,10);
      }else{
      itoa(Segundos,Datos_print,10);  
      }
   break;
   case 2:
     
      if(x==1){
        if(trx<60 && trx1<60){
         Sref=trx;
         Mref=trx1;
        
       }else if(trx>=60){
          Sref=0;
       }else if(trx1>=60){
          Mref=0;
       }else{
           Mref=0;
           Sref=0;
       }
       itoa(Sref,time_L,10);
       itoa(Mref,time_H,10);
       }else{
       itoa(Segundos,time_L,10);
       itoa(Minutos,time_H,10);
       }
       strcat(Datos_print,time_H);
       strcat(Datos_print,":");
       strcat(Datos_print,time_L);

   
   break;
   case 3:
       
       if(x==1){
        if(trx<60 && trx1<100){
         Mref=trx;
         Sref=trx1;
        
       }else if(trx>=60){
          Mref=0;
       }else if(trx1>=100){
          Href=0;
       }else{
           Mref=0;
           Href=0;
        }
       itoa(Href,time_H,10);
       itoa(Mref,time_L,10);
       }else{
         itoa(Horas,time_H,10);
         itoa(Minutos,time_L,10);
       }
       strcat(Datos_print,time_H);
       strcat(Datos_print,":");
       strcat(Datos_print,time_L);

   break;
   default:
   break;
    }
  visualizacion(Datos_print);    
}

void visualizacion(char *datos){
Led_Display_WriteString7Seg(datos,0);
}


//volatile uint16 Horas_Ref=0;
//rutina de conversion de Valores

//
//
CY_ISR(Cuenta2)
{
   uint16 total_ref=Horas+Segundos+Minutos;
   Type_Load(0);
  //Segundos--;
  if(Segundos>=0){
      Segundos--;
    //Minutos--;
  }else if(total_ref!=0){
     Segundos=59;
  }else if(total_ref==0){
     //pin1_Write(1);
  }
//  if(Conter_Milis_ReadCounter()==60){
    pin1_Write(1);
//    CyDelay(500);
//  }   

isr_Conteo2_ClearPending();
}
//
CY_ISR(Cuenta)
{
    uint16 total_ref=Horas+Segundos+Minutos;
   // Minutos--;
    if(Minutos>0){
      Minutos--;
    }else if(total_ref!=0 && Minutos==0){
      Minutos=59;
      Horas--;
    }
 if(Conter_Milis_ReadCounter()==60){ //INDICA_LA INTERRUPCION
   pin1_Write(0);
    CyDelay(500);
 }   
//  if((total_temp)!=0){
//     Horas=(Minutos==0 && Horas>=0)?Horas--:Horas;
//     Minutos=(Segundos == 0 && Minutos>=0)?Minutos--:59;
//     Segundos=(Conter_Milis_ReadCounter()==60 && Segundos>=0)?Segundos--:59;
//   }else{
//     Flag_Sound=1;
//   }

  isr_Conteo_ClearPending();   
}
//
CY_ISR(C1_Int){
int temp2=0;
//Conter_Milis_Stop();
    pin1_Write(0);
     // Led_Display_PutChar7Seg('e',2);
    while(C1_Read()==1){
      CyDelay(70);
      temp2=1;
    }   

    //temp2=1;
if(temp2==1){
switch(Register2){
  case 0b0001:
     Data=1;
    break;
  case 0b0010:
     Data=4;
    break;
  case 0b0100:
     Data=7;
    break;
   default:
    break;
 }
//pin1_Write(0);
Switch_Counter();
}
C1_ClearInterrupt();

}

//
CY_ISR(C2_Int){
pin1_Write(0);
//CyDelay(100);
int temp2=0;
//Conter_Milis_Stop();
//int temp2=0;
//Pin_1_Write(1);
     // Led_Display_PutChar7Seg('e',2);
    while(C2_Read()==1){
     CyDelay(70);
     temp2=1;
    };
    //temp2=1;
//C2_ClearInterrupt();
if(temp2==1){
  switch(Register2){
  case 0b0001:
     Data=2;
    break;
  case 0b0010:
     Data=5;
    break;
  case 0b0100:
     Data=8;
    break;
  case 0b1000:
     Data=0;
   default:
    break;
 }

Switch_Counter();
}
//LCD_Position(1,2);
//LCD_PutChar(Data);
//pin1_Write(0);
C2_ClearInterrupt();
}
//
CY_ISR(C3_Int){
//Pin_1_Write(1);
int temp2=0;
pin1_Write(0);
     // Led_Display_PutChar7Seg('e',2);
    while(C3_Read()==1){
     CyDelay(70);
     temp2=1;
    };
    //temp2=1;
//C2_ClearInterrupt();
if(temp2==1){
  switch(Register2){
  case 0b0001:
     Data=3;
    break;
  case 0b0010:
     Data=6;
    break;
  case 0b0100:
     Data=9;
    break;
  //case 0b1000:
    // Data='0';
   default:
    break;
 }
Switch_Counter();
}
//pin1_Write(0);
C3_ClearInterrupt();
}

//
CY_ISR(C4_Int){
pin1_Write(1);
int temp2=0;
//Pin_1_Write(1);
     // Led_Display_PutChar7Seg('e',2);
    while(C4_Read()==1){
     CyDelay(70);
     temp2=1;
    };
  //  temp2=1;
 if(temp2==1){
  switch(Register2){
  case 0b0001:
     data_s='S';
     r_visual=1;
    break;
  case 0b0010:
     data_s='M';
     r_visual=2;
    break;
 case 0b0100:
     data_s='H';
     r_visual=3;
   default:
 case 0b1000:
     //enter='A';
     cont_start=~cont_start;
     if(cont_start==1){
        Horas=Href;
        Minutos=Mref;
        Segundos=Sref;
        
        Conter_Milis_Start();
        Conter_Milis_1_Start();
        Conter_Milis_2_Start();
      //  flag_Fresh=1;
    
    }else if(cont_start==0){
        Conter_Milis_Stop();
        Conter_Milis_1_Stop();
        Conter_Milis_2_Stop();
    }
     Type_Load(1);
    
    break;
 }
Switch_Counter();
}
C4_ClearInterrupt();
//pin1_Write(0);
}
//
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    isr_Conteo_StartEx(Cuenta);
    isr_Conteo_SetPriority(3);
    isr_Conteo2_StartEx(Cuenta2);
    isr_Conteo2_SetPriority(3);
    //isr_Conteo3_StartEx(Cuenta3);
    isr_C1_StartEx(C1_Int);
    isr_C1_SetPriority(7);
    isr_C2_StartEx(C2_Int);
    isr_C2_SetPriority(6);
    isr_C3_StartEx(C3_Int);
    isr_C4_SetPriority(5);
    isr_C4_StartEx(C4_Int);
    isr_C4_SetPriority(4);
    Led_Display_Start();
    //Conter_Milis_Start();
    //Conter_Milis_Enable();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
    
    pin1_Write(0);
    F_Write(Register2);
    CyDelay(60);
    Register2=Register2<<1;
    if(Register2>=8){
     Register2=1;
    }
     //Type_Load();

    //uint8 flag_Fresh=0;
//    if(enter=='A'){
//        cont_start=~cont_start;
//    }
//    if(cont_start==1){
//        Horas=Href;
//        Minutos=Mref;
//        Segundos=Sref;
//        
//        Conter_Milis_Start();
//        Conter_Milis_1_Start();
//        Conter_Milis_2_Start();
//      //  flag_Fresh=1;
//    
//    }else if(cont_start==0){
//        Conter_Milis_Stop();
//        Conter_Milis_1_Stop();
//        Conter_Milis_2_Stop();
//    }
   //
    //visualizacion
    
    
    }
}

/* [] END OF FILE */
