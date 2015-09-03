///////////////////////////////
/*
Program for dinamo-initation.
2 Inputs from encoder,
1 output to moc3021 optotriac thyristor driver
PORTB.5 is a board RED LED sync with output thyristor pin
1 output to CPU 
*/
///////////////////////////////

 #include <mega328p.h>
 #include <delay.h>
 
 #define COUNT_MAX 10 //число тиков энкодера до старта серии разрядов
 #define SPARKS 4     //число разрядов в серии
 
 int count=0, i; //счетчик тиков энкодера

 void main(void) {
 
 DDRD.2=DDRD.3=0;   //encoder inputs
 PORTD.2=PORTD.3=1; //pull-up
 
 DDRB.5=1;  //конфигурации для
 PORTB.5=0; //штатного светодиода на плате   

 DDRB.1=1;  //выход управления тиристором
 PORTB.1=0;
 
 DDRB.0=1;  //выход сигнала на ЦП
 PORTB.0=0;
                         
  while(1) {
    //считаем тики энкодера, по достижению цели - обнуляем и даем разряды
    while (count < COUNT_MAX) {
      if (!(PIND.2||PIND.3)) {
      count++; 
      PORTB.0=1;                //выход на ЦП - высокий уровень
      delay_us(50);             //пропускаем дребезг
      while(!(PIND.2&&PIND.3)); //ожидаем выхода из залипания энкодера
      PORTB.0=0;                //выход на ЦП - низкий уровень
      }   
    }  
    count=0;
    
    //далее цикл - несколько разрядов подряд
    for (i=0; i<SPARKS; i++) {
    PORTB.1=1;   //ставим высокий уровень на тиристоре
    PORTB.5=1;   //зажигаем светодиод
    delay_ms(10);//ждем 10мс
    PORTB.1=0;   //отпускаем управление тиристора
    PORTB.5=0;   //гасим светодиод
    delay_ms(15);
    }
  }
 }