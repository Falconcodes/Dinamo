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
 
 #define COUNT_MAX 10 //����� ����� �������� �� ������ ����� ��������
 #define SPARKS 4     //����� �������� � �����
 
 int count=0, i; //������� ����� ��������

 void main(void) {
 
 DDRD.2=DDRD.3=0;   //encoder inputs
 PORTD.2=PORTD.3=1; //pull-up
 
 DDRB.5=1;  //������������ ���
 PORTB.5=0; //�������� ���������� �� �����   

 DDRB.1=1;  //����� ���������� ����������
 PORTB.1=0;
 
 DDRB.0=1;  //����� ������� �� ��
 PORTB.0=0;
                         
  while(1) {
    //������� ���� ��������, �� ���������� ���� - �������� � ���� �������
    while (count < COUNT_MAX) {
      if (!(PIND.2||PIND.3)) {
      count++; 
      PORTB.0=1;                //����� �� �� - ������� �������
      delay_us(50);             //���������� �������
      while(!(PIND.2&&PIND.3)); //������� ������ �� ��������� ��������
      PORTB.0=0;                //����� �� �� - ������ �������
      }   
    }  
    count=0;
    
    //����� ���� - ��������� �������� ������
    for (i=0; i<SPARKS; i++) {
    PORTB.1=1;   //������ ������� ������� �� ���������
    PORTB.5=1;   //�������� ���������
    delay_ms(10);//���� 10��
    PORTB.1=0;   //��������� ���������� ���������
    PORTB.5=0;   //����� ���������
    delay_ms(15);
    }
  }
 }