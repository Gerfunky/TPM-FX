#include <Arduino.h>
#include <FastLED.h>
#include <TPM-FX.h>

#define LED_DATA_PIN 18
#define LED_CLK_PIN 5

#define NUM_LEDS    11
#define START_LED   0

#define UPDATES_PER_SECOND 30


CRGB leds[NUM_LEDS];

CRGB TempLedArray[NUM_LEDS];

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

tpm_fx tpm_fx;   // init the TPM_FX

void setup() {
  
  
    delay( 3000 ); // power-up safety delay

   // FastLED.addLeds<WS2812, LED_PIN, RGB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<APA102,LED_DATA_PIN ,  LED_CLK_PIN, BGR,DATA_RATE_MHZ(1 )>  (leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;

}

void loop()
{
    static uint8_t startIndex = 0;  
    
    uint8_t index_add_led = 6; // how much to compress the palette
    
    // lets fill the array with Colors from a Palette. 
     
    MixModeType mix_mode = MIX_REPLACE; // We will replace the values in the Output Array.
    boolean mirror = false;
    boolean reversed = false;
    uint8_t mix_level = 255;
    
    tpm_fx.PalFill( leds, TempLedArray, RainbowColors_p, START_LED, NUM_LEDS , startIndex++ ,index_add_led , mix_mode, NOBLEND ,  reversed ,mirror, mix_level );
    
    uint16_t rotateFFrames = 1000;                                          // In how many frames should it do a full rotation?
    static uint16_t framePos = 0;                                           // we need to keep track of the frame

    tpm_fx.rotate(leds , NUM_LEDS, START_LED, rotateFFrames ,  framePos );  // This verion rotates the led array as an animation
    //tpm_fx.rotate(leds , NUM_LEDS, START_LED,   5 );                     // This version rotates the leds by a fixed amount for example if some lines a missaligned to each other 

    framePos++;                                                             // increment the frame
    if (framePos >= rotateFFrames ) { framePos = framePos-rotateFFrames; }  // reset the fremapos when we hit the end
    
    FastLED.show();                                                         // Show the Leds
    FastLED.delay(1000 / UPDATES_PER_SECOND);                               // delay for FPS
}
