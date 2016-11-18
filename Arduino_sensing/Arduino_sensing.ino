#define SET(x,y) (x |=(1<<y))				        //-Bit set/clear macros
#define CLR(x,y) (x &= (~(1<<y)))       		// |
#define CHK(x,y) (x & (1<<y))           		// |



#define N 160                               //How many frequencies

float results[N];                           //-Filtered result buffer
float freq[N];                              //-Filtered result buffer
int sizeOfArray = N;

 
void setup()
{
  
  
  TCCR1A=0b10000010;                        //-Set up frequency generator
  TCCR1B=0b00011001;                        //-+
  ICR1=110;
  OCR1A=55;

  pinMode(9,OUTPUT);                        //-Signal generator pin
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  Serial.begin(115200);

  for(int i=0;i<N;i++)                       //-Preset results
    results[i]=0;                            //-+
}

void loop()
{
  unsigned int d;

//  int counter = 0;
  for(unsigned int d=0;d<N;d++)
  {
    CLR(TCCR1B,0);                            //-Stop generator
    TCNT1=0;                                  //-Reload new frequency
    ICR1=d;                                   // |
    OCR1A=d/2;                                //-+
    SET(TCCR1B,0);                            //-Restart generator
  }

  int i = 0;
  int u = 0;
  for ( i ; i<100 ; i++ ) {                   //Average of 100 values
    u = u + analogRead(0);
  } 
  u = u/i;                                    
  Serial.println(u);                          //Print of the average of the 100 values

  if( u > 235 && u < 283 ) {                  //Choose of the right LED
    digitalWrite( 7, HIGH );
    digitalWrite( 6, LOW );
    digitalWrite( 5, LOW );
  }
  else {
    digitalWrite( 7, LOW );
  }
  if( u > 285 && u < 295 ) {
    digitalWrite( 7, LOW );
    digitalWrite( 6, HIGH );
    digitalWrite( 5, LOW );
  }
  else {
    digitalWrite( 6, LOW );
  }
  if( u > 300 ) {
    digitalWrite( 7, LOW );
    digitalWrite( 6, LOW );
    digitalWrite( 5, HIGH );
  }
  else {
    digitalWrite( 5, LOW );
  }
}
   
