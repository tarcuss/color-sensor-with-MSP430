//Frequency ranges of colors can be determined according to your own sensor
//yunus dinc

#include <msp430.h>
#include <stdint.h>
#include <stdio.h>

#define LED_R BIT0 // P1.0
#define LED_G BIT1 // P1.1
#define LED_B BIT2 // P1.2


unsigned int Sayac_Degeri = 0;
unsigned long Saklanan_Deger = 0;
unsigned long Kirmizi = 0;
unsigned long Yesil = 0;
unsigned long Mavi = 0;

void sayac(long sure){while(sure--);}
void rgb(){
if(Kirmizi<2950 && Kirmizi>2000)
        {
          if(Yesil<5300 && Yesil>4400)
          {
            if(Mavi<16000&&Mavi>7800)
            {
              
              P1OUT |= LED_B; //mavi
             
            }
            else if(Mavi<4200&&Mavi>2900)
            {
              
              P1OUT |= LED_G; //yesil
             
            }  
          } 
          else if(Yesil<3500 && Yesil>1900)
            {
              P1OUT |= (LED_R | LED_B); //mor
             
            }
        }
     else if(Kirmizi<4800 && Kirmizi>3300)
        {
          if(Yesil<5300 && Yesil>2000)
          {
            if(Mavi<5200&&Mavi>2200)
            {
              
              P1OUT |= (LED_B | LED_G); // kahverengi
             
            }
          } 
          
        }
     else if(Kirmizi<8000 && Kirmizi>6400)
        {
          if(Yesil<5300 && Yesil>2500)
          {
            if(Mavi<4200&&Mavi>2800)
            {
              
              P1OUT |= LED_R; //kirmizi
             
            }
          } 
          
        }
     else if(Kirmizi<13000 && Kirmizi>9000)
        {
          if(Yesil<10300 && Yesil>8500)
          {
            if(Mavi<6000&&Mavi>3000)
            {
              
              P1OUT |= (LED_R | LED_G); //sari
             
            }
          }
          else if (Yesil>10500){
            P1OUT |= (LED_R | LED_G | LED_B); //beyaz
          }
        }
     else if (Kirmizi<2000){
       P1OUT &= ~(LED_R | LED_G | LED_B); //siyah
      
     }
}
void oku(){
while(1)                    //Kirmizi Degeri için
        {
        P2OUT=0x02;
        TA0CTL |= MC0;              // Timer_0 baslat
        TA1CTL |= MC1;              // Timer_1 baslat
        while(Sayac_Degeri != 400); // Sayac_Degeri 400 olana kadar bekle
        TA0CTL &= ~MC0;             // Timer_0 durdur
        TA1CTL &= ~MC1;             // Timer_1 durdur
        Kirmizi = Saklanan_Deger;   // Saklanan_Deger Kirmizi'ya atiliyor
        Sayac_Degeri = 0;           // Sayac_Degeri sifirlaniyor
        Saklanan_Deger = 0;         // Saklanan_Deger sifirlaniyor
        TA0R = 0;                   // Timer_A0 registeri sifirlaniyor
        TA1R = 0;                   // Timer_A1 registeri sifirlaniyor        
        break;
        }
        __delay_cycles(200000);    
        while(1)                    //Yesil Degeri için
        {
        P2OUT=0x1A;
        TA0CTL |= MC0;              // Timer_0 baslatiliyor
        TA1CTL |= MC1;              // Timer_1 baslatiliyor
        while(Sayac_Degeri != 400); // Sayac_Degeri 400 olana kadar bekle
        TA0CTL &= ~MC0;             // Timer_0 durduruluyor
        TA1CTL &= ~MC1;             // Timer_1 durduruluyor
        Yesil = Saklanan_Deger;     // Saklanan_Deger Yesil'e atiliyor
        Sayac_Degeri = 0;           // Sayac_Degeri sifirlaniyor
        Saklanan_Deger = 0;         // Saklanan_Deger sifirlaniyor
        TA0R = 0;                   // Timer_A0 registeri sifirlaniyor
        TA1R = 0;                   // Timer_A1 registeri sifirlaniyor         
        break;
        }
       __delay_cycles(200000);
        while(1)                    //Mavi Degeri için
        {
        P2OUT=0x12;
        TA0CTL |= MC0;              // Timer_0 baslatiliyor
        TA1CTL |= MC1;              // Timer_1 baslatiliyor
        while(Sayac_Degeri != 400); // Sayac_Degeri 400 olana kadar bekle
        TA0CTL &= ~MC0;             // Timer_0 durduruluyor
        TA1CTL &= ~MC1;             // Timer_1 durduruluyor
        Mavi = Saklanan_Deger;      // Saklanan_Deger Mavi'ye atiliyor
        Sayac_Degeri = 0;           // Sayac_Degeri sifirlaniyor
        Saklanan_Deger = 0;         // Saklanan_Deger sifirlaniyor
        TA0R = 0;                   // Timer_A0 registeri sifirlaniyor
        TA1R = 0;                   // Timer_A1 registeri sifirlaniyor        
        break;
        }
}


int main(void) {

    /* Watchdog timer ve clocku ayarladim */
    WDTCTL = WDTPW + WDTHOLD;      // Watchdog timer durdu
    BCSCTL1 = CALBC1_16MHZ;          // 16 Mhzde çalisacagini belirttim
    DCOCTL = CALDCO_16MHZ;           // SMCLK = DCO = 16MHz
    
    __delay_cycles(20000); //20000ms bekleme
    
    
   P2DIR = 0x1E;             // P2.0 i input yaptim sensörden çikan out pinini buraya bagladim 
   P2SEL |= BIT0;           //P2.1 den 2.4 e kadar çikis 

   P1DIR |= (LED_R | LED_G | LED_B);  //
   P1OUT &= ~(LED_R | LED_G | LED_B); // Port çikislarini sifirlama (ledler kapali)
   
   
    TA0CCR0 = 20000;            // 20000*400 = 8000000 20ms
    TA0CCTL0 |= CCIE;           // Interrupti aktif hale getirdim
    TA0CTL |= TASSEL_2;         //SMCLK ile çalis

    TA1CCTL0 |= CCIE + CCIS_0 + CM_2 + CAP; // Interrupt, capture mod CCIxA,düsen kenar için sayma yap,capture modla çalis
    TA1CTL |= TASSEL_2;                     // SMCLK ile çalis
    //1. timerdan zaman tutulup 2. timerdan frekans saydirdim
    _BIS_SR(GIE);                              
    __delay_cycles(20000);
    
           
    while(1)
    {    

      oku();  
      P1OUT &= ~(LED_R | LED_G | LED_B);
      rgb();
      
    }  
}




//interruptlar
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0(void)
{
    Sayac_Degeri++;
}


#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_A0(void)
{
     Saklanan_Deger++;
    
}
