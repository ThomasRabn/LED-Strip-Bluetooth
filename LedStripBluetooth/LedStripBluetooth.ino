// import the necessary libraries
#include "FastLED.h"
#include <SoftwareSerial.h>

//define some variables
#define LEDPIN       6
#define LED_TYPE     WS2812B
#define NUM_LEDS     60
byte brightness = 120;
CRGB leds[NUM_LEDS];
SoftwareSerial mySerial(10, 11); // RX, TX
bool disco = 0;
bool change = 0;
unsigned int addedDelay = 50;
unsigned int rgbColour[3]; // On crée un tableau de 3 cases contenant les valeurs pour R, G et B

//<————————————————————————————SETUP————————————————————————————>
void setup()
{
  Serial.begin(9600);
  // On éteint la pin 13 (qui active la led "L" présente sur la UNO)
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  //start the receiver
  
  mySerial.begin(9600);

  //set up LED strip information
  FastLED.addLeds<LED_TYPE, LEDPIN>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.setBrightness(brightness);

  // On commence en remplissant le rouge
  rgbColour[0] = 255;
  rgbColour[1] = 0;
  rgbColour[2] = 0;  

}

//<—————————————————————————LOOP———————————————————————————————>
void loop() {
  String input;
  char(c);
  delay(addedDelay);

  if (disco == 1) {
    CRGB temp = leds[0];
    for(int i = 0; i < NUM_LEDS; i++) {
      if (i == NUM_LEDS-1) leds[i] = temp;
      else                 leds[i] = leds[i+1];
    }
    FastLED.show();
  }

  else if (change == 1) {
    for (int couleurDescendante = 0; couleurDescendante < 3; couleurDescendante += 1) {
      int couleurMontante = couleurDescendante == 2 ? 0 : couleurDescendante + 1; // Si couleurDescendante vaut 2 : couleurMontante devient 0, sinon il devient couleurDescendante + 1
  
      // On fait un échange entre descendante et montante
      for(int i = 0; i < 255; i += 1) {
        rgbColour[couleurDescendante] -= 1;
        rgbColour[couleurMontante] += 1;
        toutColorer(rgbColour[0], rgbColour[1], rgbColour[2]);
        delay(addedDelay);
        if (mySerial.available()) change=0;
      }
    }
  }
  
  while(mySerial.available())  {
    c = (char)mySerial.read();
    Serial.print(c);
    input += c;
    delay(10);
  }
  
  //FastLED.delay(10);
  input.trim(); // Permet de retirer les caracteres speciaux de la string de caractères
  //Serial.print(input);
  if (input == "white") {
    toutColorer(255, 200, 200);
    disco = 0;
    change = 0;
  }

  else if (input == "max") {
    brightness = 255;
    FastLED.setBrightness(brightness);
    FastLED.show();
  }

  else if (input == "warm white") {
    toutColorer(255, 95, 28);
    disco = 0;
    change = 0;
  }

  else if (input == "up") {
    if(brightness <= 245)   brightness += 10;
    else                    brightness = 255;
    FastLED.setBrightness(brightness);
    FastLED.show();
  }

  else if (input == "down") {
    if(brightness > 10)    brightness -= 10;
    else                    brightness = 5;
    FastLED.setBrightness(brightness);
    FastLED.show();
  }

  else if (input == "delay+") {
    addedDelay+=10;
  }
  
  else if (input == "delay-") {
    if (addedDelay >= 20) addedDelay-=10;
  }

  else if (input == "sunrise") {
    degrade(255, 0, 0, 255, 200, 0);
    disco = 0;
    change = 0;
  }

  else if (input == "toxic") {
    degrade(255, 80, 0, 0, 200, 20);
    disco = 0;
    change = 0;
  }

  else if (input == "night") {
    degrade(255, 0, 200, 0, 0, 150);
    disco = 0;
    change = 0;
  }

  else if (input == "star") {
    ajouterEtoile();
  }

  else if (input == "rainbow") {
    initialize_rainbow();
    disco = 0;
    change = 0;
  }

  else if (input == "off") {
    toutColorer(0,0,0);
    disco = 0;
    change = 0;
  }

  // 1 = rouge
  else if (input == "red") {
    toutColorer(255,0,0);
    disco = 0;
    change = 0;
  }

  // 2 = vert
  else if (input == "green") {
    toutColorer(0,255,0);
    disco = 0;
    change = 0;
  }

  // 3 = bleu
  else if (input  == "blue") {
    toutColorer(0,0,255);
    disco = 0;
    change = 0;
  }

  // 4 = magenta
  else if (input == "pink") {
    toutColorer(255,0,200);
    disco = 0;
    change = 0;
  }

  // 5 = Jaune
  else if (input  == "yellow") {
    toutColorer(255,140,0);
    disco = 0;
    change = 0;
  }

  // 6 = Cyan
  else if (input == "cyan") {
    toutColorer(0,255,255);
    disco = 0;
    change = 0;
  }

  // 7 = orange
  else if (input == "orange") {
    toutColorer(255, 80, 0);
    disco = 0;
    change = 0;
  }

  // 8 = violet
  else if (input == "purple") {
    toutColorer(150,0,200);
    disco = 0;
    change = 0;
  }

  // 9 = Turquoise
  else if (input == "turquoise") {
    toutColorer(0,255,80);
    disco = 0;
    change = 0;
  }

  // Mode couleurs qui se déplacent
  else if (input == "disco") {
    disco = !disco;
  }

  // Mode couleurs qui changent
  else if (input == "change") {
    change = 1;
    rgbColour[0] = 255;
    rgbColour[1] = 0;
    rgbColour[2] = 0;  
  }
}

//<——————————————————————OTHER FUNCTIONS————————————————————>

void toutColorer(int r, int g, int b){
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB(g, r, b);
  }
  FastLED.show();
}

// Permet d'avoir un dégradé orange -> jaune -> bleu
void sunset() {
   static uint8_t starthue = 0;
   fill_rainbow( leds + 5, NUM_LEDS - 5, --starthue, 20);
   FastLED.show();
}


/// Permet d'initialiser toutes les leds à une couleur d'intervalle. Fonctionne uniquement pour 60 LEDs
void initialize_rainbow() {
  int r = 255, g = 0, b = 0;
  leds[NUM_LEDS-1] = CRGB( g, r, b);
  for (int i = NUM_LEDS-2 ; i >= 0; --i) {
    if (i > 39)       {
      r -= 12;
      g += 12;
    }
    else if (i == 39) {
      r = 0;
      g = 255;
      b = 0;
    }
    else if (i > 19)  {
      g -= 12;
      b += 12;
    }
    else if (i == 19) {
      g = 0;
      b = 255 ;
    }
    else              {
      b -= 12;
      r += 12;
    }

    leds[i] = CRGB( g, r, b);
  }
  FastLED.show();
}

void degrade(int r1, int g1, int b1, int r2, int g2, int b2) {
  float diffR, diffG, diffB;
  diffR = (float)((r2-r1)/NUM_LEDS);
  diffG = (float)((g2-g1)/NUM_LEDS);
  diffB = (float)((b2-b1)/NUM_LEDS);

  int r, g, b;
  
  for(int i = NUM_LEDS-1; i >=0 ; i--) {
    leds[i] = CRGB(g1, r1, b1);
    r1+=diffR;
    g1+=diffG;
    b1+=diffB;
  }
  FastLED.show();
}

void ajouterEtoile() {
  long randomValue = 0;
  for(int i = 0; i < NUM_LEDS; i++){
    randomValue = random(0, 15);
    if(randomValue == 5)  leds[i] = CRGB(255,255,255);
  }
  FastLED.show();
}
