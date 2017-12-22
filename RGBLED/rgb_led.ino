/*
DC416 RGB_LED
Function pointers: http://www.andthinker.com/2017/05/function-pointer-in-c.html
*/

int GENERATIONS = 100;

int redPin = 11;
int greenPin = 10;
int bluePin = 9;

struct RGB {
  byte red;
  byte green;
  byte blue;
};

RGB redguy1 = { 255, 0, 0 };
RGB greenguy1 = { 0, 255, 0};
RGB blueguy1 = {0, 0, 255};
RGB whiteguy1 = {255, 255, 255};
RGB blackguy1 = {0, 0, 0};

//uncomment this line if using a Common Anode LED
//#define COMMON_ANODE

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
}

void printGenerations(int gen) {
    Serial.print("Generation: ");
    Serial.print(gen);
    Serial.print(" of ");
    Serial.print(GENERATIONS);
    Serial.print("\n");
}

void loop()
{
  RGB guy1 = getRandomRGB();
  RGB guy2 = getRandomRGB();

  Serial.println("Guy1");
  setDC416Color(guy1);
  Serial.println("Guy2");
  setDC416Color(guy2);
  for (int i = 0; i <= GENERATIONS; i++) {
    printGenerations(i);
    guy1 = scanRGB(guy1, guy2);
    Serial.println("Guy1");
    setDC416Color(guy1);
    guy2 = scanRGB(guy2, guy1);
    Serial.println("Guy2");
    setDC416Color(guy2);
  }
}

void setDC416Color(RGB rgb)
{
  analogWrite(redPin, rgb.red);
  analogWrite(greenPin, rgb.green);
  analogWrite(bluePin, rgb.blue);
  delay(1000);
}

int jonahsAlgorithm(int rgb1, int rgb2) {
  return (rgb1 + rgb2) / 2;
}

RGB scanRGB(RGB rgb1, RGB rgb2) {
  RGB result = {
    jonahsAlgorithm(rgb1.red, rgb2.red),
    jonahsAlgorithm(rgb1.green, rgb2.green),
    jonahsAlgorithm(rgb1.blue, rgb2.blue),
  };
  return result;
}

RGB getRandomRGB() {
  return RGB {random(255), random(255), random(255)};
}
