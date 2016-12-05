#include <TimeAlarms.h>

#include <Time.h>
#include <TimeLib.h>



#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);



int hora_alarma = 1;
int minuto_alarma = 1;
int segundo_alarma = 1;
int digPin = 10;


//Varables para leer las teclas y el ADC
int lcd_key     = 0;
int adc_key_in  = 0;
 
//Contantes para identificar las teclas
#define btnDERECHA      0
#define btnARRIBA      1
#define btnABAJO       2
#define btnIZQUIERDA   3
#define btnSELECT      4
#define btnNADA        5
 
//Función que lee las teclas
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // Leer la entrada analógica
 
 //Las teclas se conectan a un divisor resistivo que produce distintos valores de tensión según la tecla pulsada
 
 if (adc_key_in > 1000) return btnNADA; //Si no hay ninguna tecla pulsada
 
 if (adc_key_in < 50)   return btnDERECHA;  
 if (adc_key_in < 195)  return btnARRIBA; 
 if (adc_key_in < 380)  return btnABAJO; 
 if (adc_key_in < 555)  return btnIZQUIERDA; 
 if (adc_key_in < 790)  return btnSELECT;   
 
 return btnNADA;  // retornar por default btnNAda
}
 

void setup() {
  pinMode(13, OUTPUT);
  lcd.begin(16, 2);                 //LCD de 16 columnas y 2 filas
  lcd.clear();                      //Borrar la pantalla
  lcd.setCursor(0, 0);              //Llevar el cursor al inicio
  lcd.print("Soy una alarma !");
  delay(1000);
  setTime(8,28,00,6,11,2016);

  //crear alarma
  

  lcd.clear();
  lcd.print("Ingrese alarma.");
  delay(1000);

  lcd.print("Ingrese hora");
  delay(100);
  while(lcd_key != btnSELECT){
    lcd_key = read_LCD_buttons();
    delay(50);
    lcd.clear();
    lcd.setCursor(0,0);
    if(lcd_key == btnARRIBA){
      hora_alarma++;
      if(hora_alarma == 25){
        hora_alarma = 1;
      }
      delay(200);
    }
    
    if(lcd_key == btnABAJO){
      hora_alarma--;
      if(hora_alarma == 0){
        hora_alarma = 24;
      }
      delay(200);
    }
    lcd.print("hora=");
    lcd.print(+hora_alarma);    
  }
  delay(50);
  lcd.clear();
  lcd.print("Ingrese minutos");
  delay(700);
  lcd_key = btnNADA;
  delay(100);
  while(lcd_key != btnSELECT){
    //capturar boton presionado
    lcd_key = read_LCD_buttons();
    delay(50);
    lcd.clear();
    lcd.setCursor(0,0);
    //verificar precion de boton arriba
    if(lcd_key == btnARRIBA){
      //incremetar minuto
      minuto_alarma++;
      if(minuto_alarma == 60){
        minuto_alarma = 0;
      }
      delay(200);
    }

    //verificar precion de boton abajo
    if(lcd_key == btnABAJO){
      //decremento de minuto
      minuto_alarma--;
      if(minuto_alarma == 0){
        minuto_alarma = 59;
      }
      delay(200);
    }
    lcd.print("minuto=");
    lcd.print(+minuto_alarma);    
  }

  //Set a alarma
  Alarm.alarmRepeat(hora_alarma,minuto_alarma,0, Alarma);
}

void loop() {
  mostrarHora();
  Alarm.delay(1000);
}

//funcion ejecutada al momento de ejecutar la alarma
void Alarma(){
  lcd.clear();
  lcd.print("Alarma sonando!!");
  sonar();
  delay(10000);
}

//fucion para sonar el buzzer
void sonar(){
  analogWrite(digPin, 127);
  delay(10000);
  analogWrite(digPin, 0);
}

//funcion para mostrar la hora
void mostrarHora(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(hour());
  lcd.print(+":");
  lcd.print(minute());
  lcd.print(+":");
  lcd.print(second());
}
