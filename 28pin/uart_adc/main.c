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
  UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0); // 送受信許可、受信完了割り込み許可
  UCSR0C = (0<<UMSEL00)|(3<<UCSZ00)|(1<<USBS0)|(0<<UPM00); // async 8bit 1stopbit 0parity  
}

void usart_send_str(char *str){
  while(*str != '\0'){
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = *str++;
  }
}

void adc_init(void){
  ADMUX = (0<<REFS0); // 外部基準電圧
  ADCSRA =(1<<ADEN)|(1<<ADSC)|(0<<ADPS0); // A/D変換許可、1回目変換開始(調整)、分周率2
}

// return 1-1023
int adc_read(char pin){
  ADMUX = pin; // AD変換入力ピン
  cbi(ADCSRA, ADIF);
  sbi(ADCSRA, ADSC); // 変換開始
  loop_until_bit_is_set(ADCSRA, ADIF); // 変換完了まで待つ
  return ADCL + (ADCH<<8);
}

int main(void)
{
  sbi(DDRB, PB0);
  sbi(DDRD, PD7);
  usart_init(9600);
  adc_init();
  usart_send_str("start\n");

  int ad, ad_p;
  char buf[10];
  for(;;){
    ad = adc_read(5);
    usart_send_str(itoa(ad, buf, 10));
    usart_send_str("\n");
    if(ad-ad_p > 5){
      LED0_ON();
      LED1_OFF();
    }
    else if(ad_p-ad > 5){
      LED0_OFF();
      LED1_ON();
    }
    _delay_ms(100);
    ad_p = ad;
  }
  return 0;
}
