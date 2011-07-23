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

void usart_init(unsigned int bps){
  unsigned int ubrr;
  ubrr = F_CPU/16/bps-1;
  UBRR0H = (unsigned char)(ubrr>>8); // ボーレート上位8bit
  UBRR0L = (unsigned char)ubrr; // ボーレート下位8bit
  UCSR0A = (0<<U2X0); // 等速
  UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0); // 送信許可、受信完了割り込みしない
  UCSR0C = (0<<UMSEL00)|(3<<UCSZ00)|(1<<USBS0)|(0<<UPM00); // async 8bit 1stopbit 0parity
}

void usart_send_str(char *str){
while(*str != NULL){
  loop_until_bit_is_set(UCSR0A,UDRE0);
  UDR0 = *str++;
 }
}

int main(void)
{
  sbi(DDRB, PB0);
  sbi(DDRD, PD7);
  usart_init(9600);
  usart_send_str("start\n");

  for(;;){
    LED0_ON();
    LED1_OFF();
    usart_send_str("muho\n");
    _delay_ms(100);

    LED0_OFF();
    LED1_ON();
    usart_send_str("homuhomu\n");
    _delay_ms(100);
  }
  return 0;
}
