#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte screenPixels[8][8];
struct vec2{
  float x;
  float y;
};
const int size_x = 20, size_y = 16;

bool soundWave(struct vec2 st, unsigned long long u_time ){
  u_time = u_time /100;
  float myTime = u_time / 10.f;	
  return st.y > (sin(myTime + st.x) * .3f)  + 0.5f ;
}

bool movingSquare(int x,int y, unsigned long long u_time){
  u_time = u_time /100;
  int size_x = 20, size_y = 16;

  x+= sin(u_time/5.f)*5;  
  y+= cos(u_time/5.f)*5;

  bool distance_x = abs((size_x / 2) - x) < 3;
  bool distance_y = abs((size_y / 2) - y) < 3;
  return distance_y && distance_x;
}


bool fshader(int x,int y, unsigned long long u_time){
  struct vec2 st;
  st.x = x/20.f;
  st.y = y/16.f;
  //return soundWave(st,u_time);
  return movingSquare(x,y,u_time);

}

void render(bool repeatWhole){
  if(!repeatWhole){
    for(int i = 0; i < 8; i++){ 
      lcd.createChar(i, screenPixels[i]);
      lcd.setCursor(i % 4, (i >= 4));
      lcd.write((char)i);
    }   
  }else{ 
    for(int j = 0; j < 4; j++){ 
      for(int i = 0; i < 8; i++){ 
        lcd.createChar(i, screenPixels[i]);
        lcd.setCursor((j*4 ) + (i % 4), (i >= 4));
        lcd.write((char)i); 
      } 
    }
  }
}

void setup() {
  lcd.begin(16, 2);
  for(char i =0; i < 8; i++){
    for(char j =0; j < 8; j++){
      screenPixels[i][j] = B00000;
    }
  }
}


void loop() {
  unsigned long long time = millis();
  for(byte i =0; i < 8; i++){ 
    for(byte j =0; j < 8; j++){
      byte row = 0;
      for(byte u =1; u < 6; u++){
        byte val = fshader(
          ((i * 5)+ u) - ((i>3) * (4*5)),
          ((i>3)*8) + j+1, time);
        row += (val << (5 - (u)));
      }
      screenPixels[i][j] = row;
    }
  }

  render(1);
  delay(10);
}


