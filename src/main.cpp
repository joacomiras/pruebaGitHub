#include <Arduino.h>
/* Diseñar una solucion programable de tal manera que las salidas a0 a2 a4 y a6 se activen si b0=1;
y las salidas impares(a1:a7) se activen si B0=0*/
void setup() {
    
  RCC->APB2ENR|=RCC_APB2ENR_IOPAEN|RCC_APB2ENR_IOPBEN;


  GPIOA -> CRL = 0x11111111; // output push-pull
  
  /* POR ENMASCARAMIENTO */
  
  GPIOB -> CRL |= GPIO_CRL_CNF0_0| GPIO_CRL_MODE0 ; 
  
  /* DESPLAZAMIENTO DE BITS */
  /* N:NUMERO DE PIN */
  
  GPIOB -> CRL |= (1<<n*4)  & (1<<n*4+1) //MODE
  |  (1<<n*4+2)|(1<<n*4+3)  // CNF
}

void loop() {
    uint est=GPIOB->IDR&(1<<0);
    if(est){
        
        
        /* DESPLAZAMIENTO DE BITS */
        GPIOA-> BSRR |= (1<<0); 
        GPIOA-> BSRR |= (1<<2); 
        GPIOA-> BSRR |= (1<<4); 
        GPIOA-> BSRR |= (1<<6);
        
        GPIOA-> BSRR |= (1<<1+16); 
        GPIOA-> BSRR |= (1<<3+16); 
        GPIOA-> BSRR |= (1<<5+16); 
        GPIOA-> BSRR |= (1<<7+16);
        /* POR ENMASCARAMIENTO */
        //SET
        GPIOA-> BSRR|= GPIO_BSRR_BS0;
        GPIOA-> BSRR|= GPIO_BSRR_BS2;
        GPIOA-> BSRR|= GPIO_BSRR_BS4;
        GPIOA-> BSRR|= GPIO_BSRR_BS6;
        //RESET
        GPIOA-> BSRR|= GPIO_BSRR_BR1|GPIO_BSRR_BR2|GPIO_BSRR_BR3|GPIO_BSRR_BR4;


    }else  GPIOA-> BSRR|= GPIO_BSRR_BS1|GPIO_BSRR_BS3|GPIO_BSRR_BS5|GPIO_BSRR_BS7
                        | GPIO_BSRR_BR0|GPIO_BSRR_BR2|GPIO_BSRR_BR4|GPIO_BSRR_BR6;

    
}

