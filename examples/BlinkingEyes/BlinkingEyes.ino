#include <Arduino.h>
#include <FastLED.h>
#include <TPM-FX.h>

#define LED_PIN_WS2812 19
//#define LED_DATA_PIN 18
//#define LED_CLK_PIN 5

#define NUM_LEDS    241
#define START_LED   0

#define UPDATES_PER_SECOND 30

    int16_t EyeWidth = 2 ;          // the With of the Eye
    uint16_t EyeSpace = 3 ;         // Space between eyes
    
    uint16_t on_frames  = 60  ;     // how many frmeas befor we start to fade it out     with 30FPS this is 2 seconds.
    uint8_t  off_frames = 120 ;     // reset to new position after on_frames+off_frames
    uint8_t fade_speed = 5;        // how much to fade down by after onframes.

    uint16_t eye_pos ;              // where to position the eye, = random in setup


CRGB leds[NUM_LEDS];                // the Output Led Array

uint16_t frame_position = 0;        // Where are we in the Animation

CRGB color = { 255,0,0};            // The Color


tpm_fx tpm_fx;   // init the TPM_FX

void setup() {
  
  
    delay( 3000 ); // power-up safety delay

    FastLED.addLeds<WS2812, LED_PIN_WS2812, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
   // FastLED.addLeds<APA102,LED_DATA_PIN ,  LED_CLK_PIN, BGR,DATA_RATE_MHZ(1 )>  (leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    


    // reset the Array to Black
    fadeToBlackBy(leds,NUM_LEDS,255);  

    uint16_t eye_pos = random16(START_LED, START_LED+NUM_LEDS   - (2*EyeWidth) - EyeSpace  )  ;   // init the first Eye Position
}



void loop()
{
    
    
    tpm_fx.BlinkingEyes(leds, START_LED, NUM_LEDS, color ,EyeWidth , EyeSpace, eye_pos, on_frames ,  frame_position , fade_speed,  MIX_REPLACE , 255 );
    
  

    frame_position++;

    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);                   // Delay to FPS

  

    if (frame_position >= on_frames + off_frames   ) {frame_position = 0 ; eye_pos = random8(START_LED, NUM_LEDS- (2*EyeWidth) - EyeSpace );}  // Restart The sequene

    
}




