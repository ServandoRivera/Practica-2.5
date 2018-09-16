#include <xc.h>
#include "CONFIG.h"//Configuration words
#include <stdio.h>//librereria lcd
#define _XTAL_FREQ 32000000// fosc
#include "flex_lcd.h"// libreria lcd

void main(void) {
    int adc = 0;
    int ADC = 0;
    float volt,temp,VOLT,TEMP;
    
    unsigned char buffer1[16];
    //configuracion del oscilador a 32MHz OSC = HFINT DIV 1:1
    OSCFRQbits.HFFRQ = 0b110; //HFINT a 32MHz
    
    //PUERTOS***********************
    ANSELD = 0; //Puerto D como digital
    ANSELE = 0; //Puerto E como digital
    ANSELAbits.ANSA3=1; //RA3 como analogico
    ANSELAbits.ANSA5=1; //RA5 como analogico
    TRISAbits.TRISA3=1; //RA3 como entrada
    TRISAbits.TRISA5=1; //RA5 como entrada

    //INICIALIZAR LCD*****************
    Lcd_Init();
    Lcd_Cmd(1);
    Lcd_Cmd(12);
    __delay_ms(100);
    
     //convertidor analogico digital************
    ADCON0bits.ADON = 1;
    ADCON0bits.ADCS=1;
    ADREFbits.ADNREF=0;
    ADREFbits.ADNREF=0b00; //Vref-------->vdd
    ADCON0bits.ADFRM=1; //JUSTIFICACION DERECHA
    
    //ciclo infinito*****************
    while(1){
        ADPCH=0b000101; //canal ANA
        __delay_ms(50);
        ADCON0bits.GO=1; //Inicia la converción
        while(ADCON0bits.GO); //esperar a que termine la conversion 
        adc=ADRESH; //PARA LEER EL RESULTADO 
        adc=adc<<8; //leer el resultado
        adc=adc+ADRESL; //leer el resultado tambien 
        volt =adc*5.0/1024.0;
        sprintf(buffer1, "volt=% 0.2f",volt);
        Lcd_Out2(2,1, buffer1);
        __delay_ms(500);
     
        ADPCH=0b000011; //canal ANA5
        __delay_ms(50);
        ADCON0bits.GO=1; //Inicia la converción
        while(ADCON0bits.GO); //esperar a que termine la conversion 
        ADC=ADRESH; //PARA LEER EL RESULTADO 
        ADC=ADC<<8; //leer el resultado
        ADC=ADC+ADRESL; //leer el resultado tambien 
        VOLT =ADC*5.0/1024.0;
        TEMP = VOLT*100;
        sprintf(buffer1,"Temp% 4.2f", TEMP);
        Lcd_Out2(1,1, buffer1);
        __delay_ms(500);
        
   }
            
    return;
}
