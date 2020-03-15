#include <Arduino.h>
#include <FastLED.h>
#include <TPM-FX.h>

#define LED_PIN_WS2812 19
//#define LED_DATA_PIN 18
//#define LED_CLK_PIN 5

#define NUM_LEDS    241
#define START_LED   0

#define UPDATES_PER_SECOND 30

boolean meteorRandomDecay = true;   // 50% chance to decay if true
uint8_t meteorTrailDecay = 60;      // How much to decay each frame 
uint8_t meteorSize = 3;             // How Big to make the meteor


CRGB leds[NUM_LEDS];                // the Output Led Array
uint16_t frame_position = 0;        // Where are we in the Animation

CRGB color = { 255,0,0};            // The Color


tpm_fx tpm_fx;   // init the TPM_FX

void setup() {
  
  
    delay( 3000 ); // power-up safety delay

    FastLED.addLeds<WS2812, LED_PIN_WS2812, RGB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
   // FastLED.addLeds<APA102,LED_DATA_PIN ,  LED_CLK_PIN, BGR,DATA_RATE_MHZ(1 )>  (leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    


    // reset the glitter Array to Black
    fadeToBlackBy(leds,NUM_LEDS,255);  
}



void loop()
{
    
    tpm_fx.meteorRain(leds , START_LED, NUM_LEDS, color , frame_position ,  meteorSize , meteorTrailDecay , meteorRandomDecay);

    frame_position++;

    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);                   // Delay to FPS

  

    if (frame_position >= NUM_LEDS  ) {frame_position = 0 ; } // Restart The sequene

    
}
