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

CRGB GlitterArray[NUM_LEDS];


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

    // reset the glitter Array to Black
    fadeToBlackBy(GlitterArray,NUM_LEDS,255);  
}

void loop()
{
    static uint8_t startIndex = 0;  
    
    uint8_t index_add_led = 8; // how much to compress the palette
    
    // lets fill the led array with Colors. 
    // since we want to mirror and reverse it we need to give it a tempLedArray to work with.

    boolean mirror = true;
    boolean reversed = true;
    uint8_t mix_level = 255;
    
    tpm_fx.PalFill( leds, TempLedArray, RainbowStripeColors_p, START_LED, NUM_LEDS , startIndex++ ,index_add_led , MIX_REPLACE, LINEARBLEND , reversed ,mirror, mix_level );
    
    
    // Lets add some glitter to the Glitter Array
    // You can pass it a pallete , a CRGB color or a HUE (uint8_t)
    uint8_t glitterChance = 50; 
    tpm_fx.AddGlitter(GlitterArray,RainbowColors_p,glitterChance,START_LED,NUM_LEDS );

    // Now we will mix the Glitter Array onto the leds.
    tpm_fx.mixOntoLedArray(GlitterArray,leds,NUM_LEDS);
    
    // Now we need to fade down the glitter array or it will go to white as it fills up !
    uint8_t fadeby = 20;
    tpm_fx.fadeLedArray(GlitterArray,START_LED,NUM_LEDS,fadeby);

    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}
