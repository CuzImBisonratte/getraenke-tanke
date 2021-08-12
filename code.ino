//Getränketanke-Projekt von Findus_Friedrich und CuzImBisonbisonratte
//https://bit.ly/getränketanke
//Code verwendbar nach der MIT-License (https://bit.ly/getränketankelizenz)

//Definieren aller Motor-Pins an die die Rohdaten gesendet werden
int MotorPinA = 8;
int MotorPinB = 9;
int MotorPinC = 10;
int MotorPinD = 11;

//Definieren der Pins des Drehwinkelgeber aus denen die Rohdaten gelesen werden können
int rotaryA = 6;
int rotaryB = 5;
int rotaryPress = 7;

//Erstellen einer Variable, die später zum Schrittgeben der Motoren genutzt wird
int Durchlaeufe;

//Erstellen eines zählers, der durch die Getränke durchwechselbare Nummern speichert
int counter = 2; 

//Erstellen von Variable, die später zum einfacheren Rechnen der Getränkeanzeige funktioniert
int getraenk = 1;
int altGetraenk = 1;

//Erstellen von Variablen, die später für die Werte des Drehwinkelgebers genutzt werden
int rotaryState;
int rotaryLastState;

void setup() { 
  //Einstellen aller Pin-modi
  pinMode(rotaryA,INPUT);
  pinMode(rotaryB,INPUT);
  pinMode(rotaryPress,INPUT_PULLUP);
  pinMode(MotorPinA,OUTPUT);
  pinMode(MotorPinB,OUTPUT);
  pinMode(MotorPinC,OUTPUT);
  pinMode(MotorPinD,OUTPUT);
  rotaryLastState = digitalRead(rotaryA);   
} 

//Die Funktion, die die Rohdaten an den Motor weitergibt
void turnMotor(int a,int b,int c,int d){
  digitalWrite(MotorPinA,a);
  digitalWrite(MotorPinB,b);
  digitalWrite(MotorPinC,c);
  digitalWrite(MotorPinD,d);
}

//Die Funktionen die benötigt werden um ein Segment weiter zu drehen
void onestep(){
    turnMotor(1,0,0,0);
    delay(5);
    turnMotor(1,1,0,0);
    delay(5);
    turnMotor(0,1,0,0);
    delay(5);
    turnMotor(0,1,1,0);
    delay(5);
    turnMotor(0,0,1,0);
    delay(5);
    turnMotor(0,0,1,1);
    delay(5);
    turnMotor(0,0,0,1);
    delay(5);
    turnMotor(1,0,0,1);
    delay(5);
}

//Der Loop, damit der Motor genau [STEPS] Schritte weiterdreht
void controlmotor(int steps){
    Durchlaeufe=steps;
    while(Durchlaeufe>=0){
        onestep();
        Durchlaeufe--;
    }
}

void loop() { 
    //Zustand von Pin "A" einlesen und abspeichern
    rotaryState = digitalRead(rotaryA); 

    //Überprüfung ob der Zustand am Drehwinkelwinkelgeber geändert wurde
    if (rotaryState != rotaryLastState){

        // Wenn der Zustand an Pin "B" anders ist als an Pin "A", wird der wert nach Oben gesetzt,
        // denn dies bedeutet, dass mit dem Uhrzeigersinn gedreht wurde
        if (digitalRead(rotaryB) != rotaryState) {

            //Setze den Counter niedriger, damit das getränk berechnet werden kann
            counter --;
        } else {

            //Setze den Counter höher, damit das getränk berechnet werden kann
            counter ++;
        }

        //Endmöglichkeiten bestimmen, damit niemals aus der Schleife ausgebrochen wird
        if(counter==0){
            counter=6;
        }
        if(counter==8){
            counter=2;
        }
    }
    //Wenn der Drehwinkelgeber gedrückt wird
    if(digitalRead(rotaryPress)==LOW){ 

        //Getränk ausrechnen
        getraenk = counter/2;
            
        //Motor immer passend drehen
        if(getraenk==1){
            if(altGetraenk==2){
                    
                //Drehen um 2/3 drehen
                controlmotor(341);
            }
            if(altGetraenk==3){
                
                //Drehen um 1/3 drehen
                controlmotor(170);
            }
        }
        if(getraenk==2){
            if(altGetraenk==1){
                
                //Drehen um 1/3 drehen
                controlmotor(170);
            }
            if(altGetraenk==3){
                
                //Drehen um 2/3 drehen
                controlmotor(341);
            }
        }
        if(getraenk==3){
            if(altGetraenk==1){
                
                //Drehen um 2/3 drehen
                controlmotor(341);
            }
            if(altGetraenk==2){
                
                //Drehen um 1/3 drehen
                controlmotor(170);
            }
        }

        //Stromzufuhr trennen, damit nichts passiert
        turnMotor(0,0,0,0);

        //Gleichtsetzen von beiden Getränkevariablen
        altGetraenk = getraenk;

        //Warten bis nicht mehr gedrückt
        while (digitalRead(rotaryPress)==LOW){}
    }

    //Gleichsetzen von beiden Drehwinkelgebervariblen
    rotaryLastState = rotaryState;
}
