#include <avr/io.h>
#include <avr/sleep.h>
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

int main(void)
{
  DDRB = 0xFF;
  DDRD = 0b10000000;
  for(;;){
    LED0_ON();
    LED1_OFF();
    _delay_ms(1000);
    LED0_OFF();
    LED1_ON();
    _delay_ms(1000);
  }
  return 0;
}
