/* maaami98 tarafından repo edilmiştir.
 *  D9 pine 3.3k direnc bağlayıp S-video girişine 
 *  D7 pinine 1k direnc bağlayıp S-video girişine bağlayın,
 *  Arduino Gnd yi S-Video Ground una bağlayın
 *  A5 girişine direk ses veya ses sensoru bağlayabilirsiniz
 */
#include <IRremote.h>
#include "fix_fft.h"
#include <TVout.h>
#include "fontALL.h"
#include "TVOlogo.h"

TVout TV;

#define ses A5



PROGMEM const  unsigned char cizgi[] = {
  7,3,
 0xfc,
 0xfc,
  0xfc,

  
  
};
PROGMEM const  unsigned char bos[] = {
  7,3,
 0x00,
 0x00,
  0x00,

  
  
};
#define x1 0
struct a{
  int x=0;
  int y=0;
  void setCursor(int a,int b)
  {
    x=x1+(a*7);
    
    y=0+40*b;
  }
  void write(int a)
  {
    if(a>16)a=16;
    for(int i=0;i<16;i++)
    {
      TV.bitmap(x,y+(i*3),bos);
    }
    for(int i=0;i<a;i++)
    {
      y=96-((a-i)*3);
    
      TV.bitmap(x,y,cizgi);
    }
    
  }
  void print(const char b[])
  {
    TV.print(x,y,b);
  }
  
}lcd;
void setup() {

 
  TV.begin(NTSC, 120, 96);
  TV.select_font(font6x8);

  TV.println(12,0,"Your Name or Title");
  TV.bitmap(12, 7, TVOlogo);
  lcd.setCursor(0,1);
  lcd.write(8);
  
 
 

}
float sutun[16];int frekans_degeri[7];
void loop() {
  
 

  for (int i = 0; i < 7; i++)
  {
    
    delayMicroseconds(5); 
    frekans_degeri[i] = analogRead(ses)*30;
    
  }

for (int k=0; k<=15; k++)
  {
  switch (k) 
  {
    case 0:
      sutun[k]= frekans_degeri[0]/128;
      break;
    
    case 1:
      sutun[k]= (frekans_degeri[0]/128 + frekans_degeri[1]/128)/2;
      break;

    case 2:
      sutun[k]= frekans_degeri[1]/128;
      break;
   
    case 3:
      sutun[k]= (frekans_degeri[1]/128 + frekans_degeri[2]/128)/2;
      break;

    case 4:
      sutun[k]= frekans_degeri[2]/128;
      break;
    
    case 5:
      sutun[k]= (frekans_degeri[1]/128 + frekans_degeri[2]/128 + frekans_degeri[3]/128)/3;
      break;
        
    case 6:
      sutun[k]= (frekans_degeri[2]/128 + frekans_degeri[3]/128 + frekans_degeri[4]/128)/3;
      break;

    case 7:
      sutun[k]= random(2)+frekans_degeri[3]/128;
      break;
      

    case 8:
      sutun[k]= random(2)+frekans_degeri[3]/128;
      break;

    case 9:
      sutun[k]= (frekans_degeri[2]/128 + frekans_degeri[3]/128 + frekans_degeri[4]/128)/3;
      break;

    case 10:
      sutun[k]= (frekans_degeri[3]/128 + frekans_degeri[4]/128 + frekans_degeri[5]/128)/3;
      break;

    case 11:
      sutun[k]= frekans_degeri[4]/128;
      break;

    case 12:
      sutun[k]= (frekans_degeri[4]/128 + frekans_degeri[5]/128)/2;
      break;

    case 13:
      sutun[k]= frekans_degeri[5]/128;
      break;

    case 14:
      sutun[k]= (frekans_degeri[5]/128 + frekans_degeri[6]/128)/2;
      break;

    case 15:
      sutun[k]= frekans_degeri[6]/128;
      break;
  }

  ciz(k, sutun[k]);
  
  }
  
}

void ciz(int pozisyon, int deger)
{
  lcd.setCursor(pozisyon,1);
 
  lcd.write(deger);
  
}
