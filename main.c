  
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
volatile uint8 Register1=0;
volatile uint8 cont_event=1;
volatile uint8 cont_start=0;
volatile uint8 r_visual=0;
volatile char data_s;
volatile char enter;
volatile uint8 Type=0;
volatile uint8 Data=0;
volatile char8 datay;
volatile uint8 Unidad=0;
volatile uint8 Decena=0;
volatile uint8 Centena=0;
volatile uint8 Mil=0;
volatile uint8 Data_Value=0; //variable_de_datos
volatile uint8 segmento_7;
volatile uint8 comm=0001;
char Concat4[4];
char Concat1[1];
void Activar_Conteo();
void visualizacion(char *data_print); //isualizacion_de_datos
//char *Numeros(uint8 vector[4]);
//volatile uint8 Centena=0;
uint8 Seg_Conversion(char datay);
void Num_to_Char(uint8 Numero){
   //Concat[4];
     //char *temp;
     char temp1[1];
     temp1[0]=(char)(Numero+48);
     strcpy(Concat1,temp1);
    //return temp;
}
void Num_to_String(uint16 Numero){
   //Concat[4];
   uint8 Temp1=(int)(Numero/1000)+48;
   uint8 Temp2=(int)((Numero-Temp1*1000)/100)+48;
   uint8 Temp3=(int)((Numero-Temp1*1000-Temp2*100)/10)+48;
   uint8 Temp4=Numero-Temp1*1000-Temp2*100-Temp3*10+48;
   char T_Chain[4]={(char)Temp1,(char)Temp2,(char)Temp3,(char)Temp4};
   //char *t_String=""; 
   strcpy(Concat4,T_Chain);
   //return t_String;
}
//char *Numeros()
uint8 Seg_Conversion(char datay){
 switch(datay){
    case '0':
    segmento_7 =0x3F; 
    break;
    case '1':
    segmento_7 =0x06; 
    break;
    case '2':
    segmento_7 =0x5B;
    break;
    case '3':
    segmento_7 =0x4F; 
    break;
    case '4':
    segmento_7 =0x66; 
    break;
    case '5':
    segmento_7 =0x6D; 
    break;
    case '6':
    segmento_7 =0x7D; 
    break;
    case '7':
    segmento_7 =0x07; 
    break;
    case '8':
    segmento_7 =0xFF; 
    break;
    case '9':
    segmento_7 =0x67; 
    break;    
    case '=':
    segmento_7 = 0x68;//0x68
    break;
 }
return segmento_7;
}



void Switch_Counter(){
 if(cont_event<=4){
  cont_event++;
 }else{
  cont_event=1;
 }
//uint8 tr=0;
switch(cont_event){
  case 1:
     Unidad=Data;
  case 2:
    //uint8 tr=0; 
    Decena=Unidad;
  //  tr=Unidad;
    Unidad=Data;
    //Decena=Data;
  case 3:
    //  
      Centena=Decena;
      Decena=Unidad;
     // tr=Centena;
      Unidad=Data;
  case 4:
       Mil=Centena;
       Centena=Decena;
       Decena=Unidad;
       Unidad=Data;
    //char *nj="";
     //visualizacion(itoa(cont_event,nj,10));
}

}
void Type_Load(int x){
   char *Datos_print="";
   char *time_H="";
   char *time_L=""; 
   uint8 trx=10*Decena+Unidad;
   uint8 trx1=10*Mil+Centena; 
   switch(r_visual){
   case 1:
     
      //Sref=Mil*1000+Centena*100+Decena*10+Unidad;
      if(x==1){
      Sref=Mil*1000+Centena*100+Decena*10+Unidad;
      //Datos_print={N_to_Char(Mil),N_to_Char(Centena),N_to_Char(Decena),N_to_Char(Unidad)};
      Num_to_String(Sref);
      strcpy(Datos_print,Concat4);
    //itoa( Sref,Datos_print,10);
      }else{
      Num_to_String(Segundos);
      strcpy(Datos_print,Concat4);
     // itoa(Segundos,Datos_print,10);  
      }
    //visualizacion(Datos_print);
   break;
   case 2:
      
      if(x==1){
        if(trx<60 && trx1<60){
         Sref=trx;
         Mref=trx1;
        
       }else if(trx>60){
          Sref=0;
       }else if(trx1>60){
          Mref=0;
       }else{
           Mref=0;
           Sref=0;
       }
      // Num_to_Char();
      // itoa(Sref,time_L,10);
       //itoa(Mref,time_H,10);
       }else{
       //itoa(Segundos,time_L,10);
       //itoa(Minutos,time_H,10);
       }
       strcat(Datos_print,time_H);
       strcat(Datos_print,":");
       strcat(Datos_print,time_L);
      //  visualizacion(Datos_print);
   
   break;
   case 3:
       
       if(x==1){
        if(trx<60 && trx1<24){
         Mref=trx;
         Href=trx1;
        
       }else if(trx>=60){
          Mref=0;
       }else if(trx1>=24){
          Href=0;
       }else{
           Mref=0;
           Href=0;
        }
     //  char Numero
//       itoa(Href,time_H,10);
//       itoa(Mref,time_L,10);
       }else{
//         itoa(Horas,time_H,10);
//         itoa(Minutos,time_L,10);
       }
       strcat(Datos_print,time_H);
       strcat(Datos_print,":");
       strcat(Datos_print,time_L);
   // visualizacion(Datos_print);
   default:
   break;
} 

    visualizacion(Datos_print);

}
//Activar_Conteo
void Activar_Conteo(){
if(data_s=='A'){
  cont_start=~cont_start;
     if(cont_start==255){
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
}
}
///Visualizacion
void visualizacion(char *datos){//sring
    for (int i =0;i<4;i++){
        char temp2=datos[i];
    uint8 temp=Seg_Conversion(temp2);
    Segmentos_7_Write(temp);     
    
    com_Write(~comm);//cero enciende display
    CyDelayUs(4);
    com_Write(comm);
    comm=comm<<1;
    //comm=comm;
    }
    
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
     pin1_Write(1);
  }
  if(Conter_Milis_1_ReadCounter()==10){
    pin1_Write(1);
    CyDelay(500);
  }   

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
pin1_Write(1);
int temp2=0;
//Conter_Milis_Stop();
    //pin1_Write(0);
     // Led_Display_PutChar7Seg('e',2);

    //temp2=1;
//if(Register2==F_ReadDataReg()){
    //uint8 temp=255;
    
switch(Register1){
   visualizacion("");
   case 0b0001:

     Data=1;
     visualizacion("1");
   // uint8 vector[4]={Mil,Centena,Decena,Unidad};
   
    break;
  case 0b0010:
     Data=4;
     visualizacion("4");
    break;
  case 0b0100:
     Data=7;
     visualizacion("7");
    break;
   default:
    break;
 }
//pin1_Write(0);
Switch_Counter();

//}
//CyDelay(700);

C1_ClearInterrupt();
CyDelay(120);
}

//
CY_ISR(C2_Int){
pin1_Write(1);
visualizacion("");
//CyDelay(4);
if(Register1==Register2){
  switch(Register1){
  case 0b0001:
     Data=0;
     visualizacion("0");
    break;
  case 0b0010:
     Data=2;
     visualizacion("2");
    break;
  case 0b0100:
     Data=5;
     visualizacion("5");
    break;
  case 0b1000:
     visualizacion("8");
     Data=8;
   default:
    break;
    
 }

//Switch_Counter();
}
Switch_Counter();
//LCD_Position(1,2);
C2_ClearInterrupt();
CyDelay(100);
}
//
CY_ISR(C3_Int){
 pin1_Write(1);
 visualizacion("");
  pin1_Write(1);
  switch(Register1){
  case 0b0001:
     Data=3;
     //visualizacion("3");
    break;
  case 0b0010:
     Data=6;
     //visualizacion("6");
    break;
  case 0b0100:
     Data=9;
     //visualizacion("9");
    break;
  //case 0b1000:
    // Data='0';
   default:
    break;
 //}
Switch_Counter();
}
//pin1_Write(0);
C3_ClearInterrupt();
CyDelay(120);
}

//
CY_ISR(C4_Int){
    visualizacion("");
    pin1_Write(1);
    int flag=0;
  switch(Register1){
  case 0b0001:
     //data_s='S';
     r_visual=1;
     //visualizacion("3");
     pin1_Write(0);
     flag=1;
    break;
  case 0b0010:
    
   //  data_s='M';
     r_visual=2;
     pin1_Write(1); 
    flag=1;
    break;
 case 0b0100:
 //    data_s='H';
     r_visual=3;
      pin1_Write(0);
    flag=1;
  // default:
 case 0b1000:
     data_s='A';//enter='A';
    Type_Load(1);
    break;
 //}
 default:
    break;
//Switch_Counter();
}
Activar_Conteo();
CyDelay(5);
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
    isr_Conteo2_SetPriority(4);
    //isr_Conteo3_StartEx(Cuenta3);
    isr_C1_StartEx(C1_Int);
    //isr_C1_SetPriority(7);
    isr_C2_StartEx(C2_Int);
    //isr_C2_SetPriority(6);
    isr_C3_StartEx(C3_Int);
    //isr_C4_SetPriority(5);
    isr_C4_StartEx(C4_Int);
    Register2=1;
    for(;;)
    {
     //Segmentos_7_Write(Seg_Conversion(un));     
 //   visualizacion("H");
 //   pin1_Write(0);
    F_Write(Register2);
    Register1=Register2;
     CyDelay(29);
    Register2=Register2<<1;
    // CyDelay(10);
    //F_Write(Register2);
    if(Register2<9){
     Register2=Register2;
    }else{
      Register2=1;
    }
    CyDelay(4);
    pin1_Write(0);
    //visualizacion("1542");
    
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

