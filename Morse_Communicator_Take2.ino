//initialize arrays

int morseCode[26][4]={
{1, 0, 2, 2}, //A
{0, 1, 1, 1}, //B
{0, 1, 0, 1}, //C
{0, 1, 1, 2}, //D
{1, 2, 2, 2}, //E
{1, 1, 0, 1}, //F
{0, 0, 1, 2}, //G
{1, 1, 1, 1}, //H
{1, 1, 2, 2}, //I
{1, 0, 0, 0}, //J
{0, 1, 0, 2}, //K
{1, 0, 1, 1}, //L
{0, 0, 2, 2}, //M
{0, 1, 2, 2}, //N
{0, 0, 0, 2}, //O
{1, 0, 0, 1}, //P
{0, 0, 1, 0}, //Q
{1, 0, 1, 2}, //R
{1, 1, 1, 2}, //S
{0, 2, 2, 2}, //T
{1, 1, 0, 2}, //U
{1, 1, 1, 0}, //V
{1, 0, 0, 2}, //W
{0, 1, 1, 0}, //X
{0, 1, 0, 0}, //Y
{0, 0, 1, 1} //Z
};

char alphabet[26]={'A', 'B', 'C', 'D', 'E', 
'F', 'G','H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 
'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int inputMorse[4]={2,2,2,2};
int inputMorse2[4]={2,2,2,2};
// stores inputted signals
 int w=0;

char outWord[10]={' '};
char outWord2[10]= {' '};
//stores the whole word, to be output to monitor

//initalize variables
volatile int startFlag = LOW;
volatile int endLetter = LOW;
volatile int endWord = LOW;

volatile int startFlag2 = LOW;
volatile int endLetter2 = LOW;
volatile int endWord2 = LOW;

const int morseButton = 3; //number of input pin
const int letterButton = 11; //number of input pin
const int wordButton = 10; //number of input pin
const int morseButton2 = 2; //number of input pin
const int letterButton2 = 4; //number of input pin
const int wordButton2 = 6; //number of input pin
const int speaker1 = 12;

const int speaker2 = 13;

int morseSignal = 2; //dot is 1, dash is 0
int morseSignal2 = 2; //dot is 1, dash is 0
char morseLetter; //where letter is stored after being interpreted from a signal 
long pressTime; //stores how long morseButton was pressed for
long pressTime2;
long startPress; //stores start time of press
long startPress2;
int i = 0;// index/ counter value
int i2 = 0; //for second input loop
int l = 0; // outWord index 
int l2 = 0; //second outWord index
int x = 0; // counter to ensure text is only output once

//Function declarations
void getInput (int inputMorse[], long pressTime, int morseSignal, int &i);//interprets and stores input signals in an array
char getLetter (int inputMorse[],int i); //matches inputted morse array to an alphabet character
void outputWord (char outWord[]); // prints the word to serial monitor

void setup() {
// put your setup code here, to run once:

pinMode(morseButton, INPUT);
pinMode(letterButton, INPUT);
pinMode(wordButton, INPUT);

pinMode(morseButton2, INPUT);
pinMode(letterButton2, INPUT);
pinMode(wordButton2, INPUT);

pinMode(speaker1, OUTPUT);
pinMode(speaker2, OUTPUT);

attachInterrupt(0, firstMorse, RISING);// pin 2, interrupts for morse buttons for first person
attachInterrupt(1, secondMorse, RISING);// pin 3, interrupts for morse buttons

Serial.begin(9600);

}

void loop() {

 if (startFlag == 1 || startFlag2 == 1){
  
  while(digitalRead (morseButton)== HIGH){//if morseButton is pressed update pressTime
  pressTime = millis() - startPress;
  
    if (startFlag2 == 1){// if morseButton2 is pressed while morseButton is pressed also update pressTime2
    pressTime2 = millis() - startPress2;
  }
 }  
 
 while(digitalRead (morseButton2)== HIGH){ //if morseButton2 is pressed update pressTime2
  pressTime2 = millis()- startPress2;
  
  if (startFlag == 1){// if morseButton is pressed while morseButton2 is pressed also update pressTime
    pressTime = millis() - startPress;   
   }
  } 
 }
 
 if (startFlag == 1) {
  getInput (inputMorse, pressTime, morseSignal,i);
  startFlag = 0;
 }

 if (startFlag2 == 1){
  getInput (inputMorse2, pressTime2, morseSignal2, i2);
  startFlag2 = 0;
 }


 if( w == 0){
 for (int i=0; i<4;i++)
 {
  //Serial.println(inputMorse[i]);
 }
 w++;
 }

 
  if (endLetter == 1) {
    i = 0;
    outWord[l] = getLetter(inputMorse,i);
    l++;
     Serial.println ("End Letter");// prints to show end of letter
    endLetter = 0;
  }

 if (endLetter2 == 1) {
  i2 = 0;
  outWord2[l2] = getLetter (inputMorse2, i2);
  Serial.println ("End Letter");// prints to show end of letter
  l2++;
  endLetter2 = 0;
 }
 
 if (endWord == 1){
  startFlag = 0;//reset startFlag
  l = 0;//reset outWord index
  i = 0;
  Serial.print("Person1: ");
  outputWord(outWord);
  endWord = 0;
 }

 if (endWord2 == 1){
  startFlag2 = 0;
  i2 = 0;
  l2 = 0; 
  Serial.print("Person2: ");
  outputWord (outWord2);
  endWord2 = 0;
 }
}// end of main program

void getInput (int inputMorse[], long pressTime, int morseSignal, int &i){
    // determine if input is a dot or dash
   if (pressTime >= 0 && pressTime < 300){
    morseSignal = 1; //dot
   } 
    else if (pressTime >= 300){
      morseSignal = 0; //dash
     }
    if (i == 4){
      i = 0;// once counter increments to 4, reset to 0
     } 
     Serial.print ("i:");
     Serial.println (i);
     Serial.println (pressTime);
      
    inputMorse[i] = morseSignal; //store morseSignal in inputMorse array
      //Serial.print ("i:");
      // Serial.println (i);
    
    i++;
    
     x++;
      if (pressTime!=0){

       //Serial.println(inputMorse[i]);
       x = 0;}  
      
  }

char getLetter (int inputMorse[],int i){
  
 int j = 0; //columns of inputMorse array
 int k = 0; //rows '' 
 int match = 0; // counts matching values, if =4 the matching letter is found
   
   for(int g=0; g<4; g++){
    //Serial.println(inputMorse[g]);// prints input (e.g. 1111)
   }
 
  while ( k < 4 && j < 26 && match != 4){ //columns of inputMorse, morseCode
    if (morseCode[j][k]==inputMorse[k]){ //check if k's elements are similar //similarity is not dependent on j
      k++;
      match++;
      }
    else{
      match=0;
      k=0; //go back to first column
      j++; //check the next row
     }
  }  

     for(int g=0; g<4; g++){
    inputMorse[g] = 2;// reset inputMorse array 
    //Serial.print(inputMorse[g]);
    }
    
  if (match!= 4){
  morseLetter=' '; //if no match is found store a space
 }

//then by here, a matching morseCode has been found   
  else if (match == 4){
  //m = j; //row of morseCode = index of alphabet 
  
    morseLetter = alphabet[j]; //store letter into morseLetter variable
    Serial.println (morseLetter);
  } 
  //Serial.println ("End Letter");// prints to show end of letter
  // Serial.println (outWord[l]);
   delay (1000);
   return morseLetter;  
  }

void outputWord (char outWord[]){
  for (int i=0; i< 10; i++){
    Serial.print (outWord[i]); // prints the inputted word
      }   
  for(int g=0; g<10; g++){
     outWord[g]=' '; //resets outWord array
    } 
  delay(1000); // delay to reduce errors caused by the button bouncing
}


//interrupt handler functions 

void secondMorse() //pin 3
{
  if (digitalRead (letterButton2) == HIGH){
    endLetter2 = 1;
  }
  else if (digitalRead (wordButton2) == HIGH){
      endWord2 = 1;
    }
  else {
    startFlag2 = 1;
    startPress2 = millis ();
  }
}

void firstMorse()// pin 2
{
  if (digitalRead (letterButton) == HIGH) {
     endLetter = 1;
   }
  else if (digitalRead(wordButton)==HIGH) //if pin 10 is high 
    {
     endWord = 1;
    }
  else {
    startFlag = 1;
    startPress = millis ();
  }
}



