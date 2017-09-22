/* Dominik Loncar
Persistance of vision display
ATMEGA 2560
Version 3.4
*/

//these are all the letters 
//each letter is split into three sections
//the first topmost LED only looks at the first number of each section
//that would be numbers at position 0,5 and 10
//second LED looks at numbers 1, 6 and 11 etc.
int _[] = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0}; //space
int A[] = {0,1,1,1,1, 1,0,1,0,0, 0,1,1,1,1};
int B[] = {1,1,1,1,1, 1,0,1,0,1, 0,1,0,1,0};
int C[] = {0,1,1,1,0, 1,0,0,0,1, 1,0,0,0,1};
int D[] = {1,1,1,1,1, 1,0,0,0,1, 0,1,1,1,0};
int E[] = {1,1,1,1,1, 1,0,1,0,1, 1,0,1,0,1};
int F[] = {1,1,1,1,1, 1,0,1,0,0, 1,0,1,0,0};
int G[] = {0,1,1,1,0, 1,0,1,0,1, 0,0,1,1,0};
int H[] = {1,1,1,1,1, 0,0,1,0,0, 1,1,1,1,1};
int I[] = {0,0,0,0,1, 1,0,1,1,1, 0,0,0,0,1};
int J[] = {1,0,0,0,0, 1,0,0,0,1, 1,1,1,1,1};
int K[] = {1,1,1,1,1, 0,0,1,0,0, 0,1,0,1,1};
int L[] = {1,1,1,1,1, 0,0,0,0,1, 0,0,0,0,1};
int M[] = {1,1,1,1,1, 0,1,1,0,0, 0,1,1,1,1};
int N[] = {1,1,1,1,1, 1,0,0,0,0, 0,1,1,1,1};
int O[] = {0,1,1,1,0, 1,0,0,0,1, 0,1,1,1,0};
int P[] = {1,1,1,1,1, 1,0,1,0,0, 0,1,0,0,0};
int Q[] = {0,1,1,1,1, 1,0,0,1,1, 0,1,1,1,1};
int R[] = {1,1,1,1,1, 1,0,1,0,0, 0,1,0,1,1};
int S[] = {0,1,0,0,1, 1,0,1,0,1, 1,0,0,1,0};
int T[] = {1,0,0,0,0, 1,1,1,1,1, 1,0,0,0,0};
int U[] = {1,1,1,1,1, 0,0,0,0,1, 1,1,1,1,1};
int V[] = {1,1,1,1,0, 0,0,0,0,1, 1,1,1,1,0};
int W[] = {1,1,1,1,0, 0,0,1,1,0, 1,1,1,1,0};
int X[] = {1,1,0,1,1, 0,0,1,0,0, 1,1,0,1,1};
int Y[] = {1,1,0,0,0, 0,0,1,0,0, 1,1,1,1,1};
int Z[] = {1,0,0,1,1, 1,0,1,0,1, 1,1,0,0,1};

//numbers work in exactly like the letters
int ZERO[] = {1,1,1,1,1, 1,0,0,0,1, 1,1,1,1,1};
int ONE[] = {1,0,0,0,1, 1,1,1,1,1, 0,0,0,0,1};
int TWO[] = {0,1,0,1,1, 1,0,1,0,1, 0,1,0,0,1};
int THREE[] = {1,0,1,0,1, 1,0,1,0,1, 1,1,1,1,1};
int FOUR[] = {1,1,1,0,0, 0,0,1,0,0, 1,1,1,1,1};
int FIVE[] = {1,0,1,0,1, 1,0,1,0,1, 1,0,1,1,1};
int SIX[] = {1,0,1,1,1, 1,0,1,0,1, 1,0,1,1,1};
int SEVEN[] = {1,0,0,0,0, 1,0,0,0,0, 1,1,1,1,1};
int EIGHT[] = {1,1,1,1,1, 1,0,1,0,1, 1,1,1,1,1};
int NINE[] = {1,1,1,0,0, 1,0,1,0,0, 1,1,1,1,1};

int sectionDelay = 3; //how long each section of the letter is display in milliseconds
//this number times 3 is how long a letter is displayed
//but due to persistance of vision, it will look like the letter is there for much longer

//array[] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, _, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO};

//hall sensor stuff
#define NOFIELD 505L    // Analog output with no applied field, calibrate this
#define TOMILLIGAUSS 1953L
boolean magnet = false;

//pins of leds for each colour
//from middle to end
//                 1   2   3   4   5   6   7   8 
int redLEDs[] =   {50, 48, 46, 44, 37, 40, 38, 36};
int greenLEDs[] = {52, 41, 43, 45, 42, 49, 51, 53};
int blueLEDs[] =  {39, 34, 32, 35, 47, 33, 31, 30};

void setup(){
  int i; //arduino gets mad if i dont declare i here for some reason
  Serial.begin(9600);
  //set all led pins as outputs, e g and b
  for (int i = 0; i < 8; i++)
    pinMode(redLEDs[i], OUTPUT);
    pinMode(greenLEDs[i], OUTPUT);
    pinMode(blueLEDs[i], OUTPUT);
}

void loop(){
  //this magnet part makes sure the text is always "drawn" in the same area
  //basically, the arduino will start drawing when the magnet is crossed
  magnetPresent();
  if (magnet){
    //print out red, green and blue in their respective colours
    printPhraseRed("red");
//    printPhraseGreen("green");
//    printPhraseBlue("blue");
  }
  
}

//
void magnetPresent(){
  int raw = analogRead(0);   // from 0 to 1023
  long compensated = raw - NOFIELD;                 // adjust relative to no applied field 
  long gauss = compensated * TOMILLIGAUSS / 1000;   // adjust scale to Gauss
Serial.println(gauss);
  if (gauss > 0)
    magnet = false;
  else if(gauss < 0)
    magnet = true;
}

//these three methods take in the letter array and flash the LEDs properly
//they only use 5 of the 8 LEDs because letters look best with 5x3
void printLetterRed(int letter[]){
  //letter
  for (int j = 0; j < 11; j=j+5){
    for (int i = 0; i < 5; i++)
      digitalWrite(redLEDs[i], letter[i+j]);
    delay(sectionDelay);
  }
}

void printLetterGreen(int letter[]){
  //letter
  for (int j = 0; j < 11; j=j+5){
    for (int i = 0; i < 5; i++)
      digitalWrite(greenLEDs[i], letter[i+j]);
    delay(sectionDelay);
  }
}

void printLetterBlue(int letter[]){
  //letter
  for (int j = 0; j < 11; j=j+5){
    for (int i = 0; i < 5; i++)
      digitalWrite(blueLEDs[i], letter[i+j]);
    delay(sectionDelay);
  }
}

//I tried everything under the sun to shorten these three methods into one method
//the problem is, even with an additional parameter that determines the colour, the if statements will make one method just as long as these three
//I also tried calling methods using strings but wasn't able to do it
//But in essence, these 3 methods take in a string and go through each letter then call the appropriate method to draw that specific letter in a specific colour
void printPhraseRed(String phrase){
  for(int i = 0; i < phrase.length(); i++){
    phrase.toLowerCase();
    switch(phrase.charAt(i)){
      case ' ': printLetterRed(_); break; //space
      case 'a': printLetterRed(A); break;
      case 'b': printLetterRed(B); break;
      case 'c': printLetterRed(C); break;
      case 'd': printLetterRed(D); break;
      case 'e': printLetterRed(E); break;
      case 'f': printLetterRed(F); break;
      case 'g': printLetterRed(G); break;
      case 'h': printLetterRed(H); break;
      case 'i': printLetterRed(I); break;
      case 'j': printLetterRed(J); break;
      case 'k': printLetterRed(K); break;
      case 'l': printLetterRed(L); break;
      case 'm': printLetterRed(M); break;
      case 'n': printLetterRed(N); break;
      case 'o': printLetterRed(O); break;
      case 'p': printLetterRed(P); break;
      case 'q': printLetterRed(Q); break;
      case 'r': printLetterRed(R); break;
      case 's': printLetterRed(S); break;
      case 't': printLetterRed(T); break;
      case 'u': printLetterRed(U); break;
      case 'v': printLetterRed(V); break;
      case 'w': printLetterRed(W); break;
      case 'y': printLetterRed(Y); break;
      case '1': printLetterRed(ONE); break;
      case '2': printLetterRed(TWO); break;
      case '3': printLetterRed(THREE); break;
      case '4': printLetterRed(FOUR); break;
      case '5': printLetterRed(FIVE); break;
      case '6': printLetterRed(SIX); break;
      case '7': printLetterRed(SEVEN); break;
      case '8': printLetterRed(EIGHT); break;
      case '9': printLetterRed(NINE); break;
      case '0': printLetterRed(ZERO); break;
    }
  }
}

void printPhraseGreen(String phrase){
  for(int i = 0; i < phrase.length(); i++){
    phrase.toLowerCase();
    switch(phrase.charAt(i)){
      case ' ': printLetterGreen(_); break; //space
      case 'a': printLetterGreen(A); break;
      case 'b': printLetterGreen(B); break;
      case 'c': printLetterGreen(C); break;
      case 'd': printLetterGreen(D); break;
      case 'e': printLetterGreen(E); break;
      case 'f': printLetterGreen(F); break;
      case 'g': printLetterGreen(G); break;
      case 'h': printLetterGreen(H); break;
      case 'i': printLetterGreen(I); break;
      case 'j': printLetterGreen(J); break;
      case 'k': printLetterGreen(K); break;
      case 'l': printLetterGreen(L); break;
      case 'm': printLetterGreen(M); break;
      case 'n': printLetterGreen(N); break;
      case 'o': printLetterGreen(O); break;
      case 'p': printLetterGreen(P); break;
      case 'q': printLetterGreen(Q); break;
      case 'r': printLetterGreen(R); break;
      case 's': printLetterGreen(S); break;
      case 't': printLetterGreen(T); break;
      case 'u': printLetterGreen(U); break;
      case 'v': printLetterGreen(V); break;
      case 'w': printLetterGreen(W); break;
      case 'y': printLetterGreen(Y); break;
      case '1': printLetterGreen(ONE); break;
      case '2': printLetterGreen(TWO); break;
      case '3': printLetterGreen(THREE); break;
      case '4': printLetterGreen(FOUR); break;
      case '5': printLetterGreen(FIVE); break;
      case '6': printLetterGreen(SIX); break;
      case '7': printLetterGreen(SEVEN); break;
      case '8': printLetterGreen(EIGHT); break;
      case '9': printLetterGreen(NINE); break;
      case '0': printLetterGreen(ZERO); break;
    }
  }
}

void printPhraseBlue(String phrase){
  for(int i = 0; i < phrase.length(); i++){
    phrase.toLowerCase();
    switch(phrase.charAt(i)){
      case ' ': printLetterBlue(_); break; //space
      case 'a': printLetterBlue(A); break;
      case 'b': printLetterBlue(B); break;
      case 'c': printLetterBlue(C); break;
      case 'd': printLetterBlue(D); break;
      case 'e': printLetterBlue(E); break;
      case 'f': printLetterBlue(F); break;
      case 'g': printLetterBlue(G); break;
      case 'h': printLetterBlue(H); break;
      case 'i': printLetterBlue(I); break;
      case 'j': printLetterBlue(J); break;
      case 'k': printLetterBlue(K); break;
      case 'l': printLetterBlue(L); break;
      case 'm': printLetterBlue(M); break;
      case 'n': printLetterBlue(N); break;
      case 'o': printLetterBlue(O); break;
      case 'p': printLetterBlue(P); break;
      case 'q': printLetterBlue(Q); break;
      case 'r': printLetterBlue(R); break;
      case 's': printLetterBlue(S); break;
      case 't': printLetterBlue(T); break;
      case 'u': printLetterBlue(U); break;
      case 'v': printLetterBlue(V); break;
      case 'w': printLetterBlue(W); break;
      case 'y': printLetterBlue(Y); break;
      case '1': printLetterBlue(ONE); break;
      case '2': printLetterBlue(TWO); break;
      case '3': printLetterBlue(THREE); break;
      case '4': printLetterBlue(FOUR); break;
      case '5': printLetterBlue(FIVE); break;
      case '6': printLetterBlue(SIX); break;
      case '7': printLetterBlue(SEVEN); break;
      case '8': printLetterBlue(EIGHT); break;
      case '9': printLetterBlue(NINE); break;
      case '0': printLetterBlue(ZERO); break;
    }
  }
}
