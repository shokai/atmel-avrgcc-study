#include <avr/io.h>
#include <util/delay.h>

#define TRUE 1
#define FALSE 0
#define NULL '\0'
#define sbi(BYTE,BIT) BYTE|=_BV(BIT) // BYTEの指定BITに1をセット
#define cbi(BYTE,BIT) BYTE&=~_BV(BIT) // BYTEの指定BITをクリア

#define LED0_ON() sbi(PORTB, PB0)
#define LED0_OFF() cbi(PORTB, PB0)
#define LED1_ON() sbi(PORTD, PD7)
#define LED1_OFF() cbi(PORTD, PD7)
#define LED2_ON() sbi(PORTB, PB1)
#define LED2_OFF() cbi(PORTB, PB1)

void check_sw(void){
  if(PINB&_BV(PB2)) LED2_ON();
  else LED2_OFF();
}

int main(void)
{
  DDRB = 0b00000011;
  DDRD = 0b10000000;
  LED2_ON();
  for(;;){
    LED0_ON();
    LED1_OFF();
    check_sw();
    _delay_ms(1000);
    LED0_OFF();
    LED1_ON();
    check_sw();
    _delay_ms(1000);
  }
  return 0;
}
