
#include "TPM-fx.h"



// Mixing

// mixes a color onto a led in the OutputLedArray
// formulas from http://www.simplefilter.de/en/basics/mixmods.html
void tpm_fx::mixOntoLed(CRGB *OutputLedArray, uint16_t led_nr, CRGB color, MixModeType mode)
{
			
			float botRed = 255 / OutputLedArray[led_nr].red ;
			float topRed = 255 / color.red;
			float botGreen = 255 / OutputLedArray[led_nr].green ;
			float topGreen = 255 / color.green;
			float botBlue = 255 / OutputLedArray[led_nr].blue ;
			float topBlue = 255 / color.blue;
			

	switch(mode)
	{
        case MIX_REPLACE:
                OutputLedArray[led_nr] = color;
        break;
		case MIX_ADD:
			OutputLedArray[led_nr].red   =  qadd8(OutputLedArray[led_nr].red ,    color.red );
			OutputLedArray[led_nr].green =  qadd8(OutputLedArray[led_nr].green ,  color.green );
			OutputLedArray[led_nr].blue   =  qadd8(OutputLedArray[led_nr].blue  ,  color.blue );
		break;

		case MIX_SUBTRACT:
			OutputLedArray[led_nr].red   =  qsub8(OutputLedArray[led_nr].red ,    color.red );
			OutputLedArray[led_nr].green =  qsub8(OutputLedArray[led_nr].green ,  color.green );
			OutputLedArray[led_nr].blue   =  qsub8(OutputLedArray[led_nr].blue  ,  color.blue );
		break;

		case MIX_MASK:
			OutputLedArray[led_nr].red   =   scale8(OutputLedArray[led_nr].red ,    color.red );
			OutputLedArray[led_nr].green =   scale8(OutputLedArray[led_nr].green ,  color.green );
			OutputLedArray[led_nr].blue   =  scale8(OutputLedArray[led_nr].blue  ,  color.blue );
		break;

		case MIX_OR:
			OutputLedArray[led_nr].red  	 =  OutputLedArray[led_nr].red 	| color.red ;
			OutputLedArray[led_nr].green	 =  OutputLedArray[led_nr].green | color.green ;
			OutputLedArray[led_nr].blue   	=  OutputLedArray[led_nr].blue  | color.blue ;
		break;
		case MIX_XOR:
			OutputLedArray[led_nr].red  	 =  OutputLedArray[led_nr].red 	^ color.red ;
			OutputLedArray[led_nr].green	 =  OutputLedArray[led_nr].green ^ color.green ;
			OutputLedArray[led_nr].blue      =  OutputLedArray[led_nr].blue  ^ color.blue ;
		break;
		case MIX_AND:
			OutputLedArray[led_nr].red  	 =  OutputLedArray[led_nr].red 	& color.red ;
			OutputLedArray[led_nr].green	 =  OutputLedArray[led_nr].green & color.green ;
			OutputLedArray[led_nr].blue      =  OutputLedArray[led_nr].blue  & color.blue ;
		break;

		case MIX_DIFF:
			if( OutputLedArray[led_nr].red  >  color.red )  		OutputLedArray[led_nr].red =  	qsub8(OutputLedArray[led_nr].red ,  	color.red );
			else 											        OutputLedArray[led_nr].red =  	qsub8(color.red,		 		OutputLedArray[led_nr].red );
			if( OutputLedArray[led_nr].green  >  color.green )  	OutputLedArray[led_nr].green =  	qsub8(OutputLedArray[led_nr].green ,  color.green );
			else 											        OutputLedArray[led_nr].green =  	qsub8(color.green,			 	OutputLedArray[led_nr].green );
			if( OutputLedArray[led_nr].blue  >  color.blue )  	    OutputLedArray[led_nr].blue =  	qsub8(OutputLedArray[led_nr].blue ,  color.blue );
			else 											        OutputLedArray[led_nr].blue =  	qsub8(color.blue,			 	OutputLedArray[led_nr].blue );
		break;
		case MIX_HARD:
			if (color.red < 255 - OutputLedArray[led_nr].red  ) 	OutputLedArray[led_nr].red  = 0;
			else 													OutputLedArray[led_nr].red  = 255;	
		break;
/*		case MIX_HARD:
			if( (OutputLedArray[led_nr].red +	color.red ) /2 		>= HARD_MIX_TRIGGER )  		OutputLedArray[led_nr].red =  	255 ; else OutputLedArray[led_nr].red = 0;
			if( (OutputLedArray[led_nr].green + color.green ) /2  	>= HARD_MIX_TRIGGER )  		OutputLedArray[led_nr].green =  	255 ; else OutputLedArray[led_nr].green = 0;
			if( (OutputLedArray[led_nr].blue +  color.blue ) /2  	>= HARD_MIX_TRIGGER )  		OutputLedArray[led_nr].blue =  	255 ; else OutputLedArray[led_nr].blue = 0;			
		break; //*/
		case MIX_MULTIPLY:

			OutputLedArray[led_nr].red =    OutputLedArray[led_nr].red  *   color.red /255  ;
			OutputLedArray[led_nr].green =  OutputLedArray[led_nr].green  *   color.green /255  ;
			OutputLedArray[led_nr].blue =   OutputLedArray[led_nr].blue  *   color.blue  /255 ;
			

		//	OutputLedArray[led_nr].red =    constrain(OutputLedArray[led_nr].red  *   color.red, 0,255) ;
		//	OutputLedArray[led_nr].green =  constrain(OutputLedArray[led_nr].green  *   color.green, 0,255) ;
		//	OutputLedArray[led_nr].blue =   constrain(OutputLedArray[led_nr].blue  *   color.blue, 0,255) ;
		break;
	#ifdef NOKDUDE
		case MIX_HARD_LIGHT:


			if (color.red <= 128 )  					 	OutputLedArray[led_nr].red =    255 * 2 * topRed * botRed ;
			else 											OutputLedArray[led_nr].red =    255 * ( 1 - 2 * ( 1 - topRed) * (1 - botRed));
			if (color.green <= 128 )  	 					OutputLedArray[led_nr].green =  255 * 2 * topGreen * botGreen ;
			else 											OutputLedArray[led_nr].green =  255 * ( 1 - 2 * ( 1 - topGreen) * (1 - botGreen));
			if (color.red <= 128 )  	 					OutputLedArray[led_nr].blue =   255 * 2 * topBlue * botBlue ;
			else 											OutputLedArray[led_nr].blue =   255 * ( 1 - 2 * ( 1 - topBlue) * (1 - botBlue));
		break;

/*		case MIX_HARD_LIGHT:
			if (color.getLuma() >= 128)
			{
					OutputLedArray[led_nr].red =  	qadd8(OutputLedArray[led_nr].red ,  	color.red );
					OutputLedArray[led_nr].green =  	qadd8(OutputLedArray[led_nr].green , color.green );
					OutputLedArray[led_nr].blue =  	qadd8(OutputLedArray[led_nr].blue ,  color.blue );

			}
			else
			{
					OutputLedArray[led_nr].red =  	qsub8(OutputLedArray[led_nr].red,	color.red  );
					OutputLedArray[led_nr].green =  	qsub8(OutputLedArray[led_nr].green,	color.green  );
					OutputLedArray[led_nr].blue =  	qsub8(OutputLedArray[led_nr].blue,	color.blue  );
			}
		break;
/*		case MIX_OVERLAY:
			if (color.getLuma() < 128)
			{
				OutputLedArray[led_nr].red =  	constrain(OutputLedArray[led_nr].red  *   color.red, 0,255) ; 
				OutputLedArray[led_nr].green =  	constrain(OutputLedArray[led_nr].green  *   color.green, 0,255) ; 
				OutputLedArray[led_nr].blue =  	constrain(OutputLedArray[led_nr].blue  *   color.blue, 0,255) ; 

			}
			else
			{
				OutputLedArray[led_nr].red =  	constrain(OutputLedArray[led_nr].red  *   (255-color.red), 0,255) ;
				OutputLedArray[led_nr].green =  	constrain(OutputLedArray[led_nr].green  *  (255 -color.green ), 0,255) ;
				OutputLedArray[led_nr].blue =  	constrain(OutputLedArray[led_nr].blue  *   (255-color.blue), 0,255) ; 

			}
		break;  //*/
		
		case MIX_OVERLAY:
	

			if (OutputLedArray[led_nr].red <= 128 )  	 	OutputLedArray[led_nr].red =    255 * 2 * topRed * botRed ;
			else 											OutputLedArray[led_nr].red =    255 * ( 1 - 2 * ( 1 - topRed) * (1 - botRed));
			if (OutputLedArray[led_nr].green <= 128 )  	 	OutputLedArray[led_nr].green =  255 * 2 * topGreen * botGreen ;
			else 											OutputLedArray[led_nr].green =  255 * ( 1 - 2 * ( 1 - topGreen) * (1 - botGreen));
			if (OutputLedArray[led_nr].red <= 128 )  	 	OutputLedArray[led_nr].blue =   255 * 2 * topBlue * botBlue ;
			else 											OutputLedArray[led_nr].blue =   255 * ( 1 - 2 * ( 1 - topBlue) * (1 - botBlue));
		break;

	#endif 


		case MIX_TADA:
			if( OutputLedArray[led_nr].red  >=  color.red )  	OutputLedArray[led_nr].red =  	OutputLedArray[led_nr].red - (OutputLedArray[led_nr].red - color.red) ;
			else 											OutputLedArray[led_nr].red =  	OutputLedArray[led_nr].red + (OutputLedArray[led_nr].red - color.red);
			if( OutputLedArray[led_nr].green  >=  color.green )  OutputLedArray[led_nr].green =  	OutputLedArray[led_nr].green - (OutputLedArray[led_nr].green - color.green);
			else 											OutputLedArray[led_nr].green =  	OutputLedArray[led_nr].green + (OutputLedArray[led_nr].green - color.green);
			if( OutputLedArray[led_nr].blue  >=  color.blue )  	OutputLedArray[led_nr].blue =  	OutputLedArray[led_nr].blue - (OutputLedArray[led_nr].blue - color.blue) ;
			else 											OutputLedArray[led_nr].blue =  	OutputLedArray[led_nr].blue + (OutputLedArray[led_nr].blue - color.blue);

			OutputLedArray[led_nr].red =  		constrain(OutputLedArray[led_nr].red  *  	color.red, 0,255) ;
			OutputLedArray[led_nr].green =  		constrain(OutputLedArray[led_nr].green  *   	color.green, 0,255) ; 
			OutputLedArray[led_nr].blue =  		constrain(OutputLedArray[led_nr].blue  *   	color.blue, 0,255) ; 
		break;
		
		case MIX_DARKEN:
			if( OutputLedArray[led_nr].red  <  color.red )  		OutputLedArray[led_nr].red =  	OutputLedArray[led_nr].red ;
			else 											OutputLedArray[led_nr].red =  	color.red;
			if( OutputLedArray[led_nr].green  <  color.green )  	OutputLedArray[led_nr].green =  	OutputLedArray[led_nr].green ;
			else 											OutputLedArray[led_nr].green =  	color.green;
			if( OutputLedArray[led_nr].blue  <  color.blue )  	OutputLedArray[led_nr].blue =  	OutputLedArray[led_nr].blue ;
			else 											OutputLedArray[led_nr].blue =  	color.blue;
		break;
		case MIX_LIGHTEN:
			if( OutputLedArray[led_nr].red  >=  color.red )  	OutputLedArray[led_nr].red =  	OutputLedArray[led_nr].red ;
			else 											OutputLedArray[led_nr].red =  	color.red;
			if( OutputLedArray[led_nr].green  >=  color.green )  OutputLedArray[led_nr].green =  	OutputLedArray[led_nr].green ;
			else 											OutputLedArray[led_nr].green =  	color.green;
			if( OutputLedArray[led_nr].blue  >=  color.blue )  	OutputLedArray[led_nr].blue =  	OutputLedArray[led_nr].blue ;
			else 											OutputLedArray[led_nr].blue =  	color.blue;
		break;
	
		case MIX_SCREEN:
			OutputLedArray[led_nr].red   = 255 * (1 - (1 - topRed)   * (1 - botRed  ));
			OutputLedArray[led_nr].green = 255 * (1 - (1 - topGreen) * (1 - botGreen) );
			OutputLedArray[led_nr].blue  = 255 * (1 - (1 - topBlue)  * (1 - botBlue ));
		break;
		case MIX_COLOR_DODGE:
			OutputLedArray[led_nr].red   = color.red   / (255 - OutputLedArray[led_nr].red );
			OutputLedArray[led_nr].green = color.green / (255 - OutputLedArray[led_nr].green );
			OutputLedArray[led_nr].blue  = color.blue  / (255 - OutputLedArray[led_nr].blue );
		break;
		case MIX_COLOR_BURN:
			OutputLedArray[led_nr].red = 255 - (255   - OutputLedArray[led_nr].red)   / color.red ;
			OutputLedArray[led_nr].green = 255 - (255 - OutputLedArray[led_nr].green) / color.green ;
			OutputLedArray[led_nr].blue = 255 - (255  - OutputLedArray[led_nr].blue)  / color.blue;
		break;
		case MIX_LINEAR_BURN:
			OutputLedArray[led_nr].red   = OutputLedArray[led_nr].red    + color.red    - 255   ;
			OutputLedArray[led_nr].green = OutputLedArray[led_nr].green  + color.green  - 255  ;
			OutputLedArray[led_nr].blue  = OutputLedArray[led_nr].blue   + color.blue   - 255 ;
		break;
/*		case MIX_LINEAR_BURN:
			if( qadd8(OutputLedArray[led_nr].red ,  	color.red ) 	== 255 )  		OutputLedArray[led_nr].red =  	255 ; else OutputLedArray[led_nr].red = 0;
			if( qadd8(OutputLedArray[led_nr].green ,  color.green ) 	== 255 )  		OutputLedArray[led_nr].green =  	255 ; else OutputLedArray[led_nr].green = 0;
			if( qadd8(OutputLedArray[led_nr].blue ,  color.blue ) 	== 255 )  		OutputLedArray[led_nr].blue =  	255 ; else OutputLedArray[led_nr].blue = 0;			
		break;   //*/


		default: Serial.println("noMix");
		break; 
	}

}


void tpm_fx::mixOntoLedArray(CRGB *InputLedArray, CRGB *OutputLedArray , uint16_t nr_leds, uint16_t start_led, boolean reversed, boolean mirror ,MixModeType mix_mode, uint8_t mix_level, boolean onecolor )
{
	CRGB color;

	if(nr_leds != 0)
	{
			
        for(uint16_t led_num = start_led; led_num < start_led + nr_leds  ; led_num ++ )
        {
            if(onecolor)
                tpm_fx::mixOntoLed(OutputLedArray, led_num, InputLedArray[start_led], mix_mode);
            else if(!mirror)
            {
                    uint16_t get_led_nr = led_num;
                    if (reversed)  get_led_nr = (start_led + nr_leds) -  (led_num - start_led) -1 ;

                    color.red  = 	map(InputLedArray[get_led_nr].red   ,	0,255,0,mix_level );
                    color.green = 	map(InputLedArray[get_led_nr].green ,	0,255,0,mix_level );
                    color.blue = 	map(InputLedArray[get_led_nr].blue ,	0,255,0,mix_level );
                    tpm_fx::mixOntoLed(OutputLedArray, led_num, color, mix_mode);
               
                
            }
            else  // we are mirroring
            {
                if(!reversed)
               {
                    if(led_num < start_led + nr_leds/2)
                    {
                        color.red  = 	map(InputLedArray[led_num].red   ,	0,255,0,mix_level );
                        color.green = 	map(InputLedArray[led_num].green ,	0,255,0,mix_level );
                        color.blue = 	map(InputLedArray[led_num].blue ,	0,255,0,mix_level );
                        tpm_fx::mixOntoLed(OutputLedArray, led_num, color, mix_mode);
                    }
                    else
                    {
                        uint16_t hist_led_num = (start_led + nr_leds) -  (led_num - start_led) -1   ;	

                        color.red  = 	map(InputLedArray[hist_led_num].red   ,	0,255,0,mix_level );
                        color.green = 	map(InputLedArray[hist_led_num].green ,	0,255,0,mix_level );
                        color.blue = 	map(InputLedArray[hist_led_num].blue ,	0,255,0,mix_level );
                        tpm_fx::mixOntoLed(OutputLedArray, led_num, color, mix_mode);
                    }
               }
               else
               {
                   if(led_num > start_led + nr_leds/2)
                    {
                        color.red  = 	map(InputLedArray[led_num].red   ,	0,255,0,mix_level );
                        color.green = 	map(InputLedArray[led_num].green ,	0,255,0,mix_level );
                        color.blue = 	map(InputLedArray[led_num].blue ,	0,255,0,mix_level );
                        tpm_fx::mixOntoLed(OutputLedArray, led_num, color, mix_mode);
                    }
                    else
                    {
                        uint16_t hist_led_num = (start_led + nr_leds) -  (led_num - start_led) -1   ;	

                        color.red  = 	map(InputLedArray[hist_led_num].red   ,	0,255,0,mix_level );
                        color.green = 	map(InputLedArray[hist_led_num].green ,	0,255,0,mix_level );
                        color.blue = 	map(InputLedArray[hist_led_num].blue ,	0,255,0,mix_level );
                        tpm_fx::mixOntoLed(OutputLedArray, led_num, color, mix_mode);
                    }
               }
               
                
                
            }
        }
			
	} 
}


// Mixes a History Array for example FFT data where every frame a new color is inserted on position 0. 
// So the Input color will allways start at 0 + offset (default 0)
void tpm_fx::mixHistoryOntoLedArray(CRGB *InputLedArray, CRGB *OutputLedArray , uint16_t nr_leds, uint16_t start_led, boolean reversed, boolean mirror ,MixModeType mix_mode, uint8_t mix_level, boolean onecolor, uint16_t offset )
{
	CRGB color;

	if(nr_leds != 0)
	{
			
        for(uint16_t post_led_num = start_led; post_led_num < start_led + nr_leds  ; post_led_num ++ )
        {
			uint16_t get_led_nr = post_led_num - start_led;

            if(onecolor)
                mixOntoLed(OutputLedArray, post_led_num, InputLedArray[ offset], mix_mode);
            else if(!mirror) // we are not mirroring
            {
                    
                    if (reversed)  get_led_nr = ( nr_leds) -  (post_led_num - start_led) -1 ;
					// if (reversed)  get_led_nr = (start_led + nr_leds) -  (led_num - start_led) -1 ;

                    color.red  = 	map(InputLedArray[get_led_nr + offset].red   ,	0,255,0,mix_level );
                    color.green = 	map(InputLedArray[get_led_nr + offset].green ,	0,255,0,mix_level );
                    color.blue = 	map(InputLedArray[get_led_nr + offset].blue ,	0,255,0,mix_level );
                    tpm_fx::mixOntoLed(OutputLedArray, post_led_num, color, mix_mode);
               
                
            }
            else  // we are mirroring
            {
                if(!reversed)
               {
                    if(get_led_nr <  nr_leds/2)
                    {
                        color.red  = 	map(InputLedArray[get_led_nr + offset].red   ,	0,255,0,mix_level );
                        color.green = 	map(InputLedArray[get_led_nr + offset].green ,	0,255,0,mix_level );
                        color.blue = 	map(InputLedArray[get_led_nr + offset].blue ,	0,255,0,mix_level );
                        tpm_fx::mixOntoLed(OutputLedArray, post_led_num, color, mix_mode);
                    }
                    else
                    {
                        //uint16_t hist_led_num = (start_led + nr_leds) -  (led_num - start_led) -1   ;	

						uint16_t hist_led_num =  nr_leds -  (post_led_num - start_led) -1 + offset  ;	

                        color.red  = 	map(InputLedArray[hist_led_num].red   ,	0,255,0,mix_level );
                        color.green = 	map(InputLedArray[hist_led_num].green ,	0,255,0,mix_level );
                        color.blue = 	map(InputLedArray[hist_led_num].blue ,	0,255,0,mix_level );
                        tpm_fx::mixOntoLed(OutputLedArray, post_led_num, color, mix_mode);
                    }
               }
               else // we are reversed 
               {
                   //if(get_led_nr > nr_leds/2)
				   if (post_led_num < start_led + nr_leds /2 )
                    {
						uint16_t hist_led_num =  nr_leds/2  -  (post_led_num - start_led)  + offset ;   // -1

                        color.red  = 	map(InputLedArray[hist_led_num].red   ,	0,255,0,mix_level );
                        color.green = 	map(InputLedArray[hist_led_num].green ,	0,255,0,mix_level );
                        color.blue = 	map(InputLedArray[hist_led_num].blue ,	0,255,0,mix_level );
                        tpm_fx::mixOntoLed(OutputLedArray, post_led_num, color, mix_mode);
                    }
                    else
                    {
						uint16_t hist_led_num =  (post_led_num -start_led) - nr_leds/2  + offset ;	 // -1
                        //uint16_t hist_led_num = (start_led + nr_leds) -  (led_num - start_led) -1   ;	

                        color.red  = 	map(InputLedArray[hist_led_num].red   ,	0,255,0,mix_level );
                        color.green = 	map(InputLedArray[hist_led_num].green ,	0,255,0,mix_level );
                        color.blue = 	map(InputLedArray[hist_led_num].blue ,	0,255,0,mix_level );
                        tpm_fx::mixOntoLed(OutputLedArray, post_led_num, color, mix_mode);
                    }
               }
               
                
                
            }
        }
			
	} 
}






// Basic Palette Functions
// made a new fuction to spread out the 255 index/color  pallet to 16*256 = 4096 colors
CRGB tpm_fx::PalGetFromLongPal( 
    CRGBPalette16 currentPalette,
	uint16_t longIndex,
	uint8_t brightness,
	TBlendType blendType) 
{
	uint8_t indexC1 = 0;
	uint8_t indexC2 = 0;

	if (255 < longIndex)
	while (255 < longIndex)
	{
		longIndex = longIndex - 256;
		indexC1++;
	}

	if (indexC1 != 15)
		indexC2 = indexC1 + 1;
	
	CRGB color1;
	CRGB color2;
    
    color1 = ColorFromPalette(currentPalette, 			indexC1 * 16, brightness , blendType); 	
    color2 = ColorFromPalette(currentPalette, 			indexC2 * 16, brightness , blendType);
	
	
	CRGB outcolor = blend(color1, color2, longIndex);

	if (blendType == NOBLEND)
		return color1;
	else 
		return outcolor;


}




// Get the color from the pallete and write it to the OutputLedArray
// index goes from 0 to 255
void tpm_fx::PalFill( CRGB *OutputLedArray, CRGBPalette16 currentPalette , uint16_t StartLed, uint16_t numberOfLeds , uint8_t colorIndex, uint8_t indexAddLed, MixModeType mix_mode, uint8_t brightness, TBlendType blending )
{
    
    for( uint16_t i = StartLed; i < StartLed + numberOfLeds ; i++) {
        
        tpm_fx::mixOntoLed(OutputLedArray, i, ColorFromPalette( currentPalette, colorIndex, brightness, blending) , mix_mode);
        colorIndex += indexAddLed;
       
    }
}

// Pal Fill and mix/reverse/onecolor in one step.
void tpm_fx::PalFill(CRGB *OutputLedArray,CRGB *TempLedArray, CRGBPalette16 currentPalette, uint16_t StartLed, uint16_t numberOfLeds , uint16_t colorIndex ,uint16_t indexAddLed, MixModeType mix_mode , TBlendType blending , boolean reversed , boolean mirror  , uint8_t mix_level , boolean onecolor )
{
    
    tpm_fx::PalFill( TempLedArray, currentPalette , StartLed, numberOfLeds , colorIndex, indexAddLed, mix_mode, 255,  blending );
	tpm_fx::mixOntoLedArray(TempLedArray, OutputLedArray , numberOfLeds, StartLed , reversed , mirror , mix_mode , mix_level , onecolor );
}




// Get the color from the pallete and write it to the OutputLedArray
// index goes from 0 to 4095
void tpm_fx::PalFillLong( CRGB *OutputLedArray, CRGBPalette16 currentPalette, uint16_t StartLed, uint16_t numberOfLeds , uint16_t colorIndexLong , uint16_t indexAddLed, MixModeType mix_mode, uint8_t brightness, TBlendType blending )
{    
    for( uint16_t i = StartLed; i < StartLed + numberOfLeds ; i++)
    {
        tpm_fx::mixOntoLed(OutputLedArray, i, PalGetFromLongPal(currentPalette,colorIndexLong,brightness,blending) , mix_mode);
        colorIndexLong += indexAddLed;
        if (colorIndexLong >= 4096) colorIndexLong = colorIndexLong-4096;
    }
}

// Pal Fill and mix/reverse/onecolor in one step.
void tpm_fx::PalFillLong(CRGB *OutputLedArray,CRGB *TempLedArray, CRGBPalette16 currentPalette, uint16_t StartLed, uint16_t numberOfLeds , uint16_t colorIndexLong ,uint16_t indexAddLed, MixModeType mix_mode , TBlendType blending , boolean reversed , boolean mirror  , uint8_t mix_level , boolean onecolor )
{
	tpm_fx::PalFillLong( TempLedArray, currentPalette , StartLed, numberOfLeds , colorIndexLong, indexAddLed, mix_mode, 255,  blending );
	tpm_fx::mixOntoLedArray(TempLedArray, OutputLedArray , numberOfLeds, StartLed , reversed , mirror , mix_mode , mix_level , onecolor );
}







// Fire2012 by Mark Kriegsman, July 2012
// as part of "Five Elements" shown here: http://youtu.be/knWiGsmgycY
////   Modded to acept vaiabled for strip / form selection
////	
// This basic one-dimensional 'fire' simulation works roughly as follows:
// There's a underlying array of 'heat' cells, that model the temperature
// at each point along the line.  Every cycle through the simulation, 
// four steps are performed:
//  1) All cells cool down a little bit, losing heat to the air
//  2) The heat from each cell drifts 'up' and diffuses a little
//  3) Sometimes randomly new 'sparks' of heat are added at the bottom
//  4) The heat from each cell is rendered as a color into the leds array
//     The heat-to-color mapping uses a black-body radiation approximation.
//
// Temperature is in arbitrary units from 0 (cold black) to 255 (white hot).
//
// This simulation scales it self a bit depending on NUM_LEDS; it should look
// "OK" on anywhere from 20 to 100 LEDs without too much tweaking. 
//
// I recommend running this simulation at anywhere from 30-100 frames per second,
// meaning an interframe delay of about 10-35 milliseconds.
//
// Looks best on a high-density LED setup (60+ pixels/meter).
//
//
// There are two main parameters you can play with to control the look and
// feel of your fire: COOLING (used in step 1 above), and SPARKING (used
// in step 3 above).
//
// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 55, suggested range 20-100 
//#define COOLING  55

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
//#define SPARKING 120
// Array of temperature readings at each simulation cell
//static 



void tpm_fx::Fire2012WithPalette(CRGB *OutputLedArray, byte heat[],CRGBPalette16 currentPalette,  uint16_t start_led, uint16_t Nr_leds, uint8_t level, uint8_t cooling , uint8_t sparking, MixModeType mix_mode  ) 
{
	
		// Step 1.  Cool down every cell a little
		for (int i = start_led; i < start_led + Nr_leds; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling * 10) / Nr_leds) + 2));
		}



		// Step 2.  Heat from each cell drifts 'up' and diffuses a little
		
			for (int k = (start_led + Nr_leds - 1); k >= (start_led + 2) ; k--) {
				heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
			}
		
		
		// Step 3.  Randomly ignite new 'sparks' of heat near the bottom
		// needs to spark at every strip / form start if selected
		
			if (random8() < sparking) {
				int y = random8(7) + start_led;
				heat[y] = qadd8(heat[y], random8(160, 255));
			}
		
		// Step 4.  Map from heat cells to LED colors
		for (int j = start_led; j < Nr_leds + start_led; j++) {
			// Scale the heat value from 0-255 down to 0-240
			// for best results with color palettes.
			//CRGB color = HeatColor(heat[j]);
			byte colorindex = scale8(heat[j], 240);
			CRGB color;

			color = ColorFromPalette(currentPalette,colorindex,level,LINEARBLEND); 
            mixOntoLed(OutputLedArray, j, color, mix_mode);
		}

	
}

void tpm_fx::Fire2012WithPalette(CRGB *OutputLedArray,CRGB *TempLedArray, byte heat[],CRGBPalette16 currentPalette,  uint16_t start_led, uint16_t Nr_leds, uint8_t cooling , uint8_t sparking, MixModeType mix_mode , TBlendType blending , boolean reversed , boolean mirror  , uint8_t mix_level , boolean onecolor ) 
{
	tpm_fx::Fire2012WithPalette(TempLedArray, heat , currentPalette,  start_led, Nr_leds, 255, cooling , sparking, MIX_REPLACE  ) ;
	tpm_fx::mixOntoLedArray(TempLedArray, OutputLedArray , Nr_leds, start_led , reversed , mirror , mix_mode , mix_level , onecolor );

}




void tpm_fx::fadeLedArray(CRGB *OutputLedArray, uint16_t start_led, uint16_t nr_leds, uint8_t fadyBy)
{
    for( int i = start_led; i < start_led + nr_leds ; i++) 
    {
        OutputLedArray[i] = OutputLedArray[i].fadeToBlackBy(fadyBy);
        
    }

}




// Glitter effect origional code from  FastLed library examples DemoReel100
void tpm_fx::AddGlitter(CRGB *OutputLedArray,CRGBPalette16 currentPalette,fract8 chanceOfGlitter, uint16_t start_led, uint16_t nr_leds)
{	

		if (random8() < chanceOfGlitter)
		{
			OutputLedArray[start_led + (random16(nr_leds))] += ColorFromPalette(currentPalette,random8(),255,LINEARBLEND);
		}


}
void tpm_fx::AddGlitter(CRGB *OutputLedArray,CRGB color,fract8 chanceOfGlitter, uint16_t start_led, uint16_t nr_leds)
{	

		if (random8() < chanceOfGlitter)
		{
			OutputLedArray[start_led + (random16(nr_leds))] += color;
		}


}

// Dot Sine
// Make a dot  run  a sine wave over the leds normal speed = bpm additional leds = bpm +1
// origional code from  FastLed library examples DemoReel100
void tpm_fx::DotSine(CRGB *OutputLedArray, uint8_t inputhue, uint8_t nr_dots, uint16_t start_led, uint16_t nr_leds, uint8_t bpm, uint8_t brightness, uint8_t Saturation)		// sine dots speed = BPM
{	
    	byte dothue = 0;
		for (int i = 0; i < nr_dots; i++)
		{
            OutputLedArray[beatsin16(i + bpm, start_led, start_led + nr_leds - 1)] |= CHSV( inputhue + dothue, Saturation, brightness);
			dothue += (255 / nr_dots);
		}
}

void tpm_fx::DotSine(CRGB *OutputLedArray, CRGBPalette16 currentPalette, uint8_t nr_dots, uint16_t start_led, uint16_t nr_leds, uint8_t bpm, uint8_t brightness)		// sine dots speed = BPM
{	
	for (int i = 0; i < nr_dots; i++)   OutputLedArray[beatsin16(i + bpm, start_led, start_led + nr_leds - 1)] |= ColorFromPalette(currentPalette, i* 16 ,brightness, LINEARBLEND) ;   //CHSV( inputhue + dothue, 255, 255);
}

void tpm_fx::DotSine(CRGB *OutputLedArray, CRGB inputcolor, uint8_t nr_dots, uint16_t start_led, uint16_t nr_leds, uint8_t bpm, uint8_t brightness)		// sine dots speed = BPM
{	
     inputcolor.nscale8(brightness); 
	for (int i = 0; i < nr_dots; i++)   OutputLedArray[beatsin16(i + bpm, start_led, start_led + nr_leds - 1)] |= inputcolor ;   //CHSV( inputhue + dothue, 255, 255);
}



// Dot SAW 
// Make a dot  run  a SAW wave over the leds normal speed = bpm additional leds = bpm +1
void tpm_fx::DotSaw(CRGB *OutputLedArray, uint8_t inputhue, uint8_t nr_dots, uint16_t start_led, uint16_t nr_leds, uint8_t bpm, uint8_t brightness, uint8_t Saturation  )  // Saw Dots that run in cirles in the form
{	

		byte dothue = 64;
		for (int i = 0; i < nr_dots; i++)
		{
			OutputLedArray[map(beat16(i + bpm), 0, 65535, start_led , start_led + nr_leds - 1)] |= CHSV(inputhue + dothue, Saturation, brightness);
			dothue += (255 / nr_dots);
		}

}

void tpm_fx::DotSaw(CRGB *OutputLedArray,  CRGBPalette16 currentPalette, uint8_t nr_dots, uint16_t start_led, uint16_t nr_leds, uint8_t bpm , uint8_t brightness )  // Saw Dots that run in cirles in the form
{	
	for (int i = 0; i < nr_dots; i++)	OutputLedArray[map(beat16(i + bpm), 0, 65535, start_led , start_led + nr_leds - 1)] |= ColorFromPalette(currentPalette, i* 16 ,brightness,LINEARBLEND) ;

}

void tpm_fx::DotSaw(CRGB *OutputLedArray,CRGB inputcolor, uint8_t nr_dots, uint16_t start_led, uint16_t nr_leds, uint8_t bpm , uint8_t brightness )  // Saw Dots that run in cirles in the form
{	
    inputcolor.nscale8(brightness); 
	for (int i = 0; i < nr_dots; i++) 	OutputLedArray[map(beat16(i + bpm), 0, 65535, start_led , start_led + nr_leds - 1)] |= inputcolor;
  

}



void tpm_fx::Shimmer(CRGB *OutputLedArray,  CRGBPalette16 currentPalette, uint16_t StartLed, uint16_t NrLeds, uint16_t xscale , uint16_t yscale , uint8_t beater, MixModeType mix_mode ,uint8_t level , TBlendType blend  ) 
{          // A time (rather than loop) based demo sequencer. This gives us full control over the length of each sequence.

   static int16_t dist = random8();

	CRGB color;

  for(int i = StartLed ; i < StartLed + NrLeds ; i++)    // Just ONE loop to fill up the LED array as all of the pixels change.
  {                                     
    uint8_t index = inoise8(i*xscale, dist+i*yscale) % 255; 			 // Get a value from the noise function. I'm using both x and y axis. 
    
	color = ColorFromPalette(currentPalette,index,level,blend);

	
	mixOntoLed(OutputLedArray, i, color, mix_mode);
	//led_FX_out[i] = ColorFromPalette(LEDS_pal_cur[pal], index, 255, currentBlendingTB);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.
  }
  
  //dist += beatsin8(beater,1,4);                                                // Moving along the distance (that random number we started out with). Vary it a bit with a sine wave.
 dist += beater;

} // shimmer()





// from Fastled examples NoisePlusPalette.ino
// Fill the x/y array of 8-bit noise values using the inoise8 function.
void tpm_fx::noiseSimple(CRGB *OutputLedArray,  CRGBPalette16 currentPalette, uint16_t StartLed, uint16_t NrLeds  ,uint8_t octaves, uint16_t x, int scale,
            uint8_t hue_octaves, uint16_t hue_x, int hue_scale,
            uint16_t time) 
{
        fill_noise8(&OutputLedArray[StartLed],NrLeds,octaves,x,scale,hue_octaves,hue_x,hue_scale,time); 

}

void tpm_fx::noise16fromPalette(CRGB *OutputLedArray,  CRGBPalette16 currentPalette, uint16_t StartLed, uint16_t NrLeds , uint8_t speed,  uint16_t scale, uint8_t trip, MixModeType mix_mode,  TBlendType blend) 
{  
  // uint8_t scale = 100;                                       // the "zoom factor" for the noise

  for (uint16_t i = StartLed; i < StartLed+NrLeds; i++) 
  {

    uint16_t shift_x = millis() / speed;                         // x as a function of time
    uint16_t shift_y = 1;

    uint32_t real_x = (i + shift_x) * scale;                  // calculate the coordinates within the noise field
    uint32_t real_y = (i + shift_y) * scale;                  // based on the precalculated positions
    uint32_t real_z = 4242;
    
    uint8_t noise = inoise16(real_x, real_y, real_z) >> 8;    // get the noise data and scale it down
    //uint8_t compression = 10;
    uint8_t index = sin8(noise*trip);                            // map led color based on noise data
    uint8_t bri   = noise;


    mixOntoLed(OutputLedArray, i, ColorFromPalette(currentPalette, index, bri, blend), mix_mode);

  }
  
} // noise16_2()

void tpm_fx::threeSinPalette(CRGB *OutputLedArray,  CRGBPalette16 currentPalette, uint16_t StartLed, uint16_t NrLeds  , uint8_t distance , uint8_t bmpWave1  ,uint8_t bmpWave2  ,uint8_t bmpWave3 , int lowWave1 ,int hiWave1 ,int lowWave2 ,int hiWave2 ,int lowWave3 ,int hiWave3, MixModeType mix_mode, uint8_t brightness, TBlendType  blend  ) 
{
    static int wave1 = 0;
    static int wave2 = 0;
    static int wave3 = 0;
 

    wave1 += beatsin8(bmpWave1,lowWave1,hiWave1);
    wave2 += beatsin8(bmpWave2,lowWave2,hiWave2);
    wave3 += beatsin8(bmpWave3,lowWave3, hiWave3);

  for (uint16_t i = StartLed; i < StartLed+NrLeds; i++) 
  {
 
    uint8_t tmp = sin8(distance*i + wave1) + sin8(distance*i + wave2) + sin8(distance*i + wave3);

    mixOntoLed(OutputLedArray, i, ColorFromPalette(currentPalette, tmp, brightness, blend), mix_mode);
 
    
  }

} 



void tpm_fx::noise8(CRGB *OutputLedArray,  CRGBPalette16 currentPalette, uint16_t StartLed, uint16_t NrLeds , uint16_t scale , uint16_t dist,  MixModeType mix_mode, uint8_t brightness, TBlendType  blend)
{
    //EFFECT NOISE
    for (int i = StartLed; i < StartLed + NrLeds; i++)                                      // Just onE loop to fill up the LED array as all of the pixels change.
      {  
		uint8_t index = inoise8(i * scale, dist + i * scale) % 255;            // Get a value from the noise function. I'm using both x and y axis.
		mixOntoLed(OutputLedArray, i, ColorFromPalette(currentPalette, index, brightness, blend), mix_mode);
        //OutputLedArray[i] = ColorFromPalette(currentPalette, index, brightness, LINEARBLEND);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.
      }
      dist += beatsin8(10, 1, 4);                                              // Moving along the distance (that random number we started out with). Vary it a bit with a sine wave.    
 }

