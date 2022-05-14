
// Sortir et rentrer ecran, allumer et eteindre ecran, fin de course, température + hygrométrie, report moniteur serie + controle via port serie



#include <DHT.h>
#define DHTPIN 13
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#include <SoftwareSerial.h>

const int dirPin = 2;
const int stepPin = 3;
const int enPin = 4;
//const int pcPin = 8;
const int ecranPin = 5;
const int onoffPin = 7;  //sécurité coupe tous sur HIGH


const int switchOne  = 9;
const int switchTwo = 10;
const int switchThree = 11;
const int switchFour = 12;


int p1buttonState = 0;

int p2buttonState = 0;

int p3buttonState = 0;

int p4buttonState = 0;

int buttonPress=0;

void checkbutton(){
  buttonPress=0;
  if (p1buttonState == LOW) buttonPress=1;
  if (p2buttonState == LOW) buttonPress=2;
}

void activeMoteur(){
  for( int x = 0; x < 8900; x++) {
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(650);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(650);
    }
}

void setDirection(int dir){
  if(dir==1){ //sort
    digitalWrite(dirPin,HIGH);
  }else if(dir==2){ //rentre
    digitalWrite(dirPin,LOW);
  }
  delay(5);
  digitalWrite ( onoffPin,LOW);
  delay(100);
}

void rentrerEcran(){
  Serial.println("rentrerEcran()");
  if (p3buttonState == HIGH) {
    Serial.println("Lecran rentre et s'éteint");
    delay(1000);
    digitalWrite ( ecranPin,LOW);
    delay(3000);
    digitalWrite ( ecranPin,HIGH);

    setDirection(1);

    digitalWrite ( enPin,LOW);
    activeMoteur();
    digitalWrite ( enPin,HIGH);
  }else{
    Serial.println("Lecran est déjà rentré");
  }
}

void sortirEcran(){
  Serial.println("sortirEcran()");
  if (p4buttonState == HIGH) {
    Serial.println("Lecran sort et s'allume");
    delay(1000);
    digitalWrite ( ecranPin,LOW);
    delay(3000);
    digitalWrite ( ecranPin,HIGH);
    

    setDirection(2);

    digitalWrite ( enPin,LOW);
    activeMoteur();
    digitalWrite ( enPin,HIGH);
    
  }else{
    Serial.println("Lecran est déjà sorti");
  }
}

void sondedht(){

  // Lire les données
  
  float h = dht.readHumidity(); //lecture de l'humidité.
 
  float t = dht.readTemperature(); //lecture de la température en degrés Celsius.
 
  // Si la lecture ne s'effectue pas
 
  if (isnan(h) || isnan(t)) {
  Serial.println ("Probleme de lecture, verifier votre systeme");
    return;
  }

  Serial.print("Temperature et Hygrometrie de la table :");
  Serial.print("Humidite: ");
  Serial.print(h);
  Serial.println (" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println (" *C ");

  delay(1000);
}
  
void setup() {

  Serial.begin(9600);
  
  pinMode( switchOne, INPUT_PULLUP);
  pinMode( switchTwo, INPUT_PULLUP);
  pinMode( switchThree, INPUT_PULLUP);
  pinMode( switchFour, INPUT_PULLUP);

  pinMode( stepPin,OUTPUT);
  pinMode( dirPin,OUTPUT);
  pinMode( enPin,OUTPUT);
  digitalWrite( enPin,HIGH);
  //pinMode ( pcPin,OUTPUT);
  //digitalWrite ( pcPin,HIGH);
  pinMode ( ecranPin,OUTPUT);
  digitalWrite ( ecranPin,HIGH);
  pinMode ( onoffPin,OUTPUT);
  digitalWrite ( onoffPin,HIGH);

}

void loop() {

  
  char carlu = 0;
  int cardispo =0;

  p1buttonState = digitalRead(switchOne);
  p2buttonState = digitalRead(switchTwo);
  p3buttonState = digitalRead(switchThree);
  p4buttonState = digitalRead(switchFour);

  cardispo=Serial.available();
  while(cspo>0ardi){
    carlu=Serial.read();
    Serial.print(carlu);
    switch(carlu) {
      case 'a':
        sortirEcran();
        break;
      case 'b':
        rentrerEcran();
        break;
      case't':
        sondedht();
        break;  
        default:
        //Serial.print("Probleme");
        break;
    }
    cardispo=Serial.available();
  }

  checkbutton();

  switch(buttonPress) {
    case 1:
        sortirEcran();
        break;
    case 2:
        rentrerEcran();
        break;
    default:
        break;
  }
 
}
