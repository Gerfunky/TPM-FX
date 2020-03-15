
#include "TPM-fx.h"


// Tool functions

// return True if OddNumber
boolean isODDNum(uint8_t number) 
{

	//if ( (number % 2) == 0) { do_something(); }
	//if ( (number & 0x01) == 0) 
	if (bitRead(number, 0) == true)
		return true;

	else
		return false;

}

// Rotate animation
void tpm_fx::rotate(CRGB *OutputLedArray , uint16_t nr_leds, uint16_t start_led, uint16_t framesFullRotation, uint16_t framePos)
{		 

	//uint16_t rotatePosition =  ((nr_leds*100) / framesFullRotation)  * framePos /100;
	
	unsigned long rotatePosition =  ((nr_leds*1000) / framesFullRotation)  * framePos / 1000;


	tpm_fx::rotate(OutputLedArray ,  nr_leds,  start_led,  uint16_t(rotatePosition)) ;

}


// Rotate by fixed amount
void tpm_fx::rotate(CRGB *OutputLedArray , uint16_t nr_leds, uint16_t start_led, uint16_t rotateAmount)
{		

	if (rotateAmount > 0)
	{
		constrain(rotateAmount , 0 ,nr_leds );
		CRGB color[nr_leds];


		for(uint16_t post_led_num = 0; post_led_num < rotateAmount  ; post_led_num++ )
		{
			color[post_led_num] = OutputLedArray[ start_led + nr_leds - rotateAmount + post_led_num ];
		}

		for(uint16_t post_led_num = nr_leds -1   ; post_led_num >=  rotateAmount ; post_led_num-- )
		{	
			OutputLedArray[start_led + post_led_num  ] = OutputLedArray[start_led + post_led_num - rotateAmount]  ;
		}
		for(uint16_t post_led_num = 0  ; post_led_num < rotateAmount  ; post_led_num++ )
		{	
			OutputLedArray[start_led + post_led_num] =  color[ post_led_num]  ;
		}
	}
}



// Mixing



// mixes a color onto a led in the OutputLedArray
// formulas from http://www.simplefilter.de/en/basics/mixmods.html
void tpm_fx::mixOntoLed(CRGB *OutputLedArray, uint16_t led_nr, CRGB color, MixModeType mode, uint8_t level)
{
			/* 
			float botRed = 255 / OutputLedArray[led_nr].red ;
			float topRed = 255 / color.red;
			float botGreen = 255 / OutputLedArray[led_nr].green ;
			float topGreen = 255 / color.green;
			float botBlue = 255 / OutputLedArray[led_nr].blue ;
			float topBlue = 255 / color.blue;
			*/
	
	
	//color.nscale8_video(level);

	color.red  = 	map(color.red   ,	0,255,0,level );
	color.green = 	map(color.green ,	0,255,0,level );
	color.blue = 	map(color.blue ,	0,255,0,level );
		

	switch(mode)
	{
        case MIX_REPLACE:
                OutputLedArray[led_nr] = color;
        break;
		case MIX_ADD:
			OutputLedArray[led_nr] =  OutputLedArray[led_nr] + color;

			//OutputLedArray[led_nr].red   =  qadd8(OutputLedArray[led_nr].red ,    color.red );
			//OutputLedArray[led_nr].green =  qadd8(OutputLedArray[led_nr].green ,  color.green );
			//OutputLedArray[led_nr].blue   =  qadd8(OutputLedArray[led_nr].blue  ,  color.blue );
		break;

		case MIX_SUBTRACT:
			OutputLedArray[led_nr] =  OutputLedArray[led_nr] - color;
			//OutputLedArray[led_nr].red   =  qsub8(OutputLedArray[led_nr].red ,    color.red );
			//OutputLedArray[led_nr].green =  qsub8(OutputLedArray[led_nr].green ,  color.green );
			//OutputLedArray[led_nr].blue   =  qsub8(OutputLedArray[led_nr].blue  ,  color.blue );
		break;

		case MIX_MASK:
			//OutputLedArray[led_nr] 		=  scale8_video( OutputLedArray[led_nr] , color);
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
			if( (255 - OutputLedArray[led_nr].red ) 		>= color.red )  		OutputLedArray[led_nr].red =  	0 ; else OutputLedArray[led_nr].red = 255;
			if( (255 - OutputLedArray[led_nr].green )   	>= color.green )  		OutputLedArray[led_nr].green =  0 ; else OutputLedArray[led_nr].green = 255;
			if ((255 - OutputLedArray[led_nr].blue )  		>= color.blue )  		OutputLedArray[led_nr].blue =  	0 ; else OutputLedArray[led_nr].blue = 255;			
		break; //*/
		case MIX_MULTIPLY:

			OutputLedArray[led_nr].red =    constrain(OutputLedArray[led_nr].red  *   color.red /255 ,0,255) ;
			OutputLedArray[led_nr].green =  constrain(OutputLedArray[led_nr].green  *   color.green /255 ,0,255) ;
			OutputLedArray[led_nr].blue =   constrain(OutputLedArray[led_nr].blue  *   color.blue  /255 ,0,255);
			

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
		case MIX_LINEAR_BURN:
			OutputLedArray[led_nr].red   = constrain(OutputLedArray[led_nr].red    + color.red   ,0,255 )  - 255   ;
			OutputLedArray[led_nr].green = constrain(OutputLedArray[led_nr].green  + color.green ,0,255)   - 255  ;
			OutputLedArray[led_nr].blue  = constrain(OutputLedArray[led_nr].blue   + color.blue  ,0,255)   - 255 ;
		break;
		case MIX_SCREEN:  // 255-(255-topLayer)*(255-botLayer)/255;
			OutputLedArray[led_nr].red   = 255 - (255 - color.red     * (255  - OutputLedArray[led_nr].red)	/255);
			OutputLedArray[led_nr].green = 255 - (255 - color.green * (255 - OutputLedArray[led_nr].green) 	/255);
			OutputLedArray[led_nr].blue  = 255 - (255 - color.blue  * (255 - OutputLedArray[led_nr].blue )	/255);
		break;
		case MIX_COLOR_DODGE: // constrain(255*botLayer/(255-topLayer), 0,255);
			OutputLedArray[led_nr].red   = constrain(255 * OutputLedArray[led_nr].red  /(256-color.red ), 0,255);  //  color.red   / (255 - OutputLedArray[led_nr].red );
			OutputLedArray[led_nr].green = constrain(255 * OutputLedArray[led_nr].green  /(256-color.green ), 0,255); 
			OutputLedArray[led_nr].blue  = constrain(255 * OutputLedArray[led_nr].blue  /(256-color.blue ), 0,255); 
		break;
		case MIX_COLOR_BURN:
			OutputLedArray[led_nr].red = 255 - (255   - OutputLedArray[led_nr].red)   / color.red ;
			OutputLedArray[led_nr].green = 255 - (255 - OutputLedArray[led_nr].green) / color.green ;
			OutputLedArray[led_nr].blue = 255 - (255  - OutputLedArray[led_nr].blue)  / color.blue;
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



// Mix the InputArry onto the OutputArray
// InputArray start possiton = start_led
void tpm_fx::mixOntoLedArray(CRGB *InputLedArray, CRGB *OutputLedArray , uint16_t nr_leds, uint16_t start_led, boolean reversed, boolean mirror ,MixModeType mix_mode, uint8_t mix_level, boolean onecolor )
{

	tpm_fx::mixHistoryOntoLedArray( InputLedArray,  OutputLedArray , nr_leds, start_led, reversed, mirror , mix_mode,  mix_level,  onecolor, start_led, 0 );

}


// Mixes a InputArray onto the OutputArray for example FFT data where every frame is a new color is inserted on position 0. 
// InputArray start possiton = 0 + offset(0) 
void tpm_fx::mixHistoryOntoLedArray(CRGB *InputLedArray, CRGB *OutputLedArray , uint16_t nr_leds, uint16_t start_led, boolean reversed, boolean mirror ,MixModeType mix_mode, uint8_t mix_level, boolean onecolor, uint16_t offset, uint8_t extend )
{
	CRGB color;
	uint8_t extend_counter = 0;
	uint16_t get_plus_led_nr = offset;
	uint16_t get_minus_led_nr = offset + nr_leds - 1;
	uint16_t get_led_nr = offset;

	uint16_t real_post_led_num;
	uint8_t oddNumberBump = isODDNum(nr_leds);

	if(nr_leds != 0)
	{
		 for(uint16_t post_led_num = start_led; post_led_num < start_led + nr_leds   ; post_led_num ++ )
        {	

			
			if(onecolor)
			{
				get_led_nr = offset;
				real_post_led_num = post_led_num;
			}
			else if(post_led_num - start_led <  nr_leds/2 + oddNumberBump)
			{
				
				if      (!mirror &&  !reversed )	{get_led_nr = get_plus_led_nr;  real_post_led_num = post_led_num;}
				else if (!mirror &&   reversed )	{get_led_nr = get_minus_led_nr; real_post_led_num = post_led_num;}  
				else if ( mirror &&  !reversed )  	{get_led_nr = get_plus_led_nr;  real_post_led_num = post_led_num;}
				else if ( mirror &&   reversed ) 	{get_led_nr = get_plus_led_nr;  real_post_led_num = (start_led + nr_leds/2 -1 + oddNumberBump) - ( post_led_num -  start_led ) ;}	

			}
			else
			{

				if (post_led_num - start_led ==  nr_leds/2 + oddNumberBump  && mirror && !reversed )  { get_plus_led_nr = offset;   extend_counter = 0;}
				if (post_led_num - start_led ==  nr_leds/2 + oddNumberBump  && mirror &&  reversed )  { get_plus_led_nr = offset + oddNumberBump ;   extend_counter = 0;}
		
				if      (!mirror &&  !reversed )	{get_led_nr = get_plus_led_nr;  real_post_led_num = post_led_num;}
				else if (!mirror &&   reversed )	{get_led_nr = get_minus_led_nr; real_post_led_num = post_led_num;}  
				else if ( mirror &&  !reversed )  	{get_led_nr = get_plus_led_nr;  real_post_led_num = (start_led  + nr_leds -1 + oddNumberBump ) - ( post_led_num - nr_leds/2 - start_led  ) ;}
				else if ( mirror &&   reversed ) 	{get_led_nr = get_plus_led_nr;  real_post_led_num = post_led_num  ;}

			}

			color = InputLedArray[get_led_nr]  ;


			tpm_fx::mixOntoLed(OutputLedArray, real_post_led_num, color, mix_mode ,mix_level );
		
			if (extend_counter >= extend )
			{
				get_plus_led_nr++;
				get_minus_led_nr--;
				

				extend_counter = 0 ;
				
			}
			else extend_counter++;
		}

	}


}






// Basic Palette Functions
// Get the Collor from a long Palette
// Palette spread out to 16*256 = 4096 colors
// Index from 0 to 4095
CRGB tpm_fx::PalGetFromLongPal( 
    CRGBPalette16 currentPalette,
	uint16_t longIndex,
	uint8_t brightness,
	TBlendType blendType) 
{
	uint8_t indexC1 = 0;
	uint8_t indexC2 = 0;

	while (longIndex >= 4096 ) longIndex  = longIndex - 4096;

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

CRGB ColorFromPaletteExtended( const CRGBPalette16& pal, uint16_t index, uint8_t brightness, TBlendType blendType)
{
	// from https://github.com/FastLED/FastLED/pull/202/commits/d900daa730a833b0b57466be07dc53e9c5e68f84
	//	
	//
    // This fucnction has the same intuitive behavior as the other ColorFromPalette
    // functions, except it provides 8-bit interpolation between palette entries.

    // Extract the four most significant bits of the index as a palette index.
    uint8_t index_4bit = (index >> 12);

    // Calculate the 8-bit offset from the palette index.
    // Throws away the 4 least significant bits and uses the middle 8.
    uint8_t offset = (uint8_t)(index >> 4);

    // Get the palette entry from the 4-bit index
    //  CRGB rgb1 = pal[ hi4];
    const CRGB* entry = &(pal[0]) + index_4bit;
    uint8_t red1   = entry->red;
    uint8_t green1 = entry->green;
    uint8_t blue1  = entry->blue;

    uint8_t blend = offset && (blendType != NOBLEND);

    if( blend ) {
        // If palette blending is enabled, use the offset to interpolate between
        // the selected palette entry and the next.

        if( index_4bit == 15 ) {
            entry = &(pal[0]);
        } else {
            entry++;
        }

        // Calculate the scaling factor and scaled values for the lower palette value.

        uint8_t f1 = 256 - offset;

        red1   = scale8_LEAVING_R1_DIRTY( red1,   f1);
        green1 = scale8_LEAVING_R1_DIRTY( green1, f1);
        blue1  = scale8_LEAVING_R1_DIRTY( blue1,  f1);

        // Calculate the scaled values for the neighboring palette value.
        uint8_t red2   = entry->red;
        uint8_t green2 = entry->green;
        uint8_t blue2  = entry->blue;
        red2   = scale8_LEAVING_R1_DIRTY( red2,   offset);
        green2 = scale8_LEAVING_R1_DIRTY( green2, offset);
        blue2  = scale8_LEAVING_R1_DIRTY( blue2,  offset);

        cleanup_R1();

        // These sums can't overflow, so no qadd8 needed.
        red1   += red2;
        green1 += green2;
        blue1  += blue2;

    }

    if( brightness != 255) {
        nscale8x3_video( red1, green1, blue1, brightness);
    }

    return CRGB( red1, green1, blue1);
}




// Get the color from the pallete and write it to the OutputLedArray
// index goes from 0 to 255
void tpm_fx::PalFill( CRGB *OutputLedArray, CRGBPalette16 currentPalette , uint16_t StartLed, uint16_t numberOfLeds , uint8_t colorIndex, uint8_t indexAddLed, MixModeType mix_mode, uint8_t brightness, TBlendType blending )
{
    
    for( uint16_t i = StartLed; i < StartLed + numberOfLeds ; i++) {
        
        tpm_fx::mixOntoLed(OutputLedArray, i, ColorFromPalette( currentPalette, colorIndex, 255, blending) , mix_mode, brightness);
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
        //tpm_fx::mixOntoLed(OutputLedArray, i, ColorFromPaletteExtended(currentPalette,colorIndexLong,brightness,blending) , mix_mode);
		tpm_fx::mixOntoLed(OutputLedArray, i, PalGetFromLongPal(currentPalette,colorIndexLong,255,blending) , mix_mode ,brightness );
        colorIndexLong += indexAddLed;
        if (colorIndexLong >= 4096) colorIndexLong = colorIndexLong-4096;
    }
}

// Pal Fill and mix/reverse/onecolor in one step.
// index goes from 0 to 4095
void tpm_fx::PalFillLong(CRGB *OutputLedArray,CRGB *TempLedArray, CRGBPalette16 currentPalette, uint16_t StartLed, uint16_t numberOfLeds , uint16_t colorIndexLong ,uint16_t indexAddLed, MixModeType mix_mode , TBlendType blending , boolean reversed , boolean mirror  , uint8_t mix_level , boolean onecolor )
{
	tpm_fx::PalFillLong( TempLedArray, currentPalette , StartLed, numberOfLeds , colorIndexLong, indexAddLed, MIX_REPLACE, 255,  blending );
	tpm_fx::mixHistoryOntoLedArray(TempLedArray, OutputLedArray ,  numberOfLeds, StartLed, reversed , mirror , mix_mode , mix_level , onecolor, StartLed,0 );
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
//
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
            mixOntoLed(OutputLedArray, j, color, mix_mode,255);
		}

	
}


// Fire Animation mixed onto OutputArray
void tpm_fx::Fire2012WithPalette(CRGB *OutputLedArray,CRGB *TempLedArray, byte heat[],CRGBPalette16 currentPalette,  uint16_t start_led, uint16_t Nr_leds, uint8_t cooling , uint8_t sparking, MixModeType mix_mode , TBlendType blending , boolean reversed , boolean mirror  , uint8_t mix_level , boolean onecolor ) 
{
	tpm_fx::Fire2012WithPalette(TempLedArray, heat , currentPalette,  start_led, Nr_leds, 255, cooling , sparking, MIX_REPLACE  ) ;
	tpm_fx::mixOntoLedArray(TempLedArray, OutputLedArray , Nr_leds, start_led , reversed , mirror , mix_mode , mix_level , onecolor );

}



// Fade the OutputLedArray by fadeBy
void tpm_fx::fadeLedArray(CRGB *OutputLedArray, uint16_t start_led, uint16_t nr_leds, uint8_t fadeBy)
{
    for( int i = start_led; i < start_led + nr_leds ; i++) 
    {
        OutputLedArray[i] = OutputLedArray[i].fadeToBlackBy(fadeBy);       
    }
}




// Glitter effect origional code from  FastLed library examples DemoReel100
// from palette
void tpm_fx::AddGlitter(CRGB *OutputLedArray,CRGBPalette16 currentPalette,fract8 chanceOfGlitter, uint16_t start_led, uint16_t nr_leds)
{	

		if (random8() < chanceOfGlitter)
		{
			OutputLedArray[start_led + (random16(nr_leds))] += ColorFromPalette(currentPalette,random8(),255,LINEARBLEND);
		}


}

// Glitter effect origional code from  FastLed library examples DemoReel100
// from CRGB Color
void tpm_fx::AddGlitter(CRGB *OutputLedArray,CRGB color,fract8 chanceOfGlitter, uint16_t start_led, uint16_t nr_leds, uint8_t level)
{	

		if (random8() < chanceOfGlitter)
		{
			color.nscale8(level);
			OutputLedArray[start_led + (random16(nr_leds))] += color ;
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



uint16_t  tpm_fx::Shimmer(CRGB *OutputLedArray,  CRGBPalette16 currentPalette, uint16_t StartLed, uint16_t NrLeds, uint16_t dist, uint16_t xscale , uint16_t yscale , uint8_t beater, MixModeType mix_mode ,uint8_t level , TBlendType blend  ) 
{          // A time (rather than loop) based demo sequencer. This gives us full control over the length of each sequence.

   //static int16_t dist = random8();

	CRGB color;

  for(int i = StartLed ; i < StartLed + NrLeds ; i++)    // Just ONE loop to fill up the LED array as all of the pixels change.
  {                                     
    uint8_t index = inoise8(i*xscale, dist+i*yscale) % 255; 			 // Get a value from the noise function. I'm using both x and y axis. 
    
	color = ColorFromPalette(currentPalette,index,level,blend);

	
	mixOntoLed(OutputLedArray, i, color, mix_mode,255);
	//led_FX_out[i] = ColorFromPalette(LEDS_pal_cur[pal], index, 255, currentBlendingTB);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.
  }
  
  //dist += beatsin8(beater,1,4);                                                // Moving along the distance (that random number we started out with). Vary it a bit with a sine wave.
 return  dist + beater;

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


    mixOntoLed(OutputLedArray, i, ColorFromPalette(currentPalette, index, bri, blend), mix_mode,255);

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

    mixOntoLed(OutputLedArray, i, ColorFromPalette(currentPalette, tmp, brightness, blend), mix_mode,255);
 
    
  }

} 



void tpm_fx::noise8(CRGB *OutputLedArray,  CRGBPalette16 currentPalette, uint16_t StartLed, uint16_t NrLeds , uint16_t scale , uint16_t dist,  MixModeType mix_mode, uint8_t brightness, TBlendType  blend)
{
    //EFFECT NOISE
    for (int i = StartLed; i < StartLed + NrLeds; i++)                                      // Just onE loop to fill up the LED array as all of the pixels change.
      {  
		uint8_t index = inoise8(i * scale, dist + i * scale) % 255;            // Get a value from the noise function. I'm using both x and y axis.
		mixOntoLed(OutputLedArray, i, ColorFromPalette(currentPalette, index, brightness, blend), mix_mode,255);
        //OutputLedArray[i] = ColorFromPalette(currentPalette, index, brightness, LINEARBLEND);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.
      }
      dist += beatsin8(10, 1, 4);                                              // Moving along the distance (that random number we started out with). Vary it a bit with a sine wave.    
 }




void tpm_fx::strobe(CRGB *OutputLedArray, uint16_t StartLed, uint16_t NrLeds, CRGB color , uint16_t on_Frames ,uint16_t off_frames, uint16_t frame_position ,MixModeType mix_mode, uint8_t brightness)
{   /* 	Strobe a color	
		Color			// the color to strobe
		frame_position  // We need to pass it the active framecount please add one each frame 
		on_frames		// how many onframes
		off_frames      // howmany off frames
		
	*/


	while(frame_position  >= on_Frames + off_frames)
	{
		frame_position =  frame_position - (on_Frames + off_frames);
	}

	if (frame_position  < on_Frames)
	{

		for( uint16_t i = StartLed; i < StartLed + NrLeds ; i++)
		{
			//tpm_fx::mixOntoLed(OutputLedArray, i, ColorFromPaletteExtended(currentPalette,colorIndexLong,brightness,blending) , mix_mode);
			tpm_fx::mixOntoLed(OutputLedArray, i, color, mix_mode,brightness);

		}
	
		}


}



void tpm_fx::BlinkingEyes(CRGB *OutputLedArray, uint16_t StartLed, uint16_t NrLeds, CRGB color , uint16_t EyeWidth, uint16_t EyeSpace, uint16_t eye_pos, uint16_t on_frames,  uint16_t frame_pos, uint8_t fade_speed,  MixModeType mix_mode, uint8_t brightness)
{		   	// Eyes  
			//origional idea from https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/#LEDStripEffectBlinkingHalloweenEyes


  int StartPoint  = constrain(eye_pos , StartLed, StartLed + NrLeds  - (2*EyeWidth) - EyeSpace  ) ; //sanity check if the eye poss is in the range of the leds.
  int Start2ndEye = StartPoint + EyeWidth + EyeSpace;
 
  if (frame_pos > on_frames)
	fadeToBlackBy(&color,1,   constrain( (frame_pos-on_frames) * fade_speed, 0,255 ));

 
  for(int i = 0; i < EyeWidth; i++) 
  {
	  tpm_fx::mixOntoLed(OutputLedArray, StartPoint + i, color, mix_mode,brightness);
	  tpm_fx::mixOntoLed(OutputLedArray, Start2ndEye + i, color, mix_mode,brightness);
  }
 

  
}


void tpm_fx::meteorRain(CRGB *OutputLedArray, uint16_t StartLed, uint16_t NrLeds, CRGB color ,uint16_t frame_pos,  byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay) {  
  //setAll(0,0,0);
 
  int i = frame_pos; // for(int i = 0; i < NrLeds+NrLeds; i++) 

  
  {
   
   
    // fade brightness all LEDs one step
    for(int j=StartLed; j< StartLed + NrLeds; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) 
	  {
		//fadeToBlackBy(&color,1,   meteorTrailDecay);  
        //fadeToBlack(j, meteorTrailDecay );  
		tpm_fx::fadeLedArray(OutputLedArray, j,1, meteorTrailDecay)   ;   
      }
    }
   
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j < StartLed + NrLeds) && (i-j >= StartLed) ) 
	  {
        //setPixel(i-j, red, green, blue);
		tpm_fx::mixOntoLed(OutputLedArray, i-j, color, MIX_ADD);
      }
    }
   
    //showStrip();
    //delay(SpeedDelay);
  }
}



// KITT Animations
// based on https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/#LEDStripEffectThenewKITT

void tpm_fx::KITT_RightToLeft(CRGB *OutputLedArray, uint16_t StartLed, uint16_t NrLeds, CRGB color ,uint16_t frame_pos, uint8_t EyeSize, MixModeType mix_mode, uint8_t brightness) 
{

	frame_pos = constrain(frame_pos, 0 ,NrLeds -EyeSize-2  ); 			//sanity check 
  	uint16_t i = constrain(StartLed + NrLeds - EyeSize-2 - frame_pos , StartLed, StartLed+ NrLeds -1 );
	CRGB faded_color = color;
		 
	faded_color.fadeLightBy(30);
											tpm_fx::mixOntoLed(OutputLedArray, i			, faded_color , mix_mode,brightness);
		for(int j = 1; j <= EyeSize; j++)  	tpm_fx::mixOntoLed(OutputLedArray, i+j			, color 	  , mix_mode,brightness);
											tpm_fx::mixOntoLed(OutputLedArray, i+EyeSize+1 	, faded_color, mix_mode,brightness);

}

void tpm_fx::KITT_LeftToRight(CRGB *OutputLedArray, uint16_t StartLed, uint16_t NrLeds, CRGB color ,uint16_t frame_pos, uint8_t EyeSize, MixModeType mix_mode, uint8_t brightness)
 {

	 frame_pos = constrain(frame_pos, 0 ,NrLeds -EyeSize-2  ); 			//sanity check 
  	uint16_t i = constrain(StartLed + frame_pos , StartLed, StartLed+ NrLeds - EyeSize-2  );
	
	CRGB faded_color = color;
		 
	faded_color.fadeLightBy(30);
  	
											tpm_fx::mixOntoLed(OutputLedArray, i			, faded_color , mix_mode,brightness);
		for(int j = 1; j <= EyeSize; j++)  	tpm_fx::mixOntoLed(OutputLedArray, i+j			, color 	  , mix_mode,brightness);
											tpm_fx::mixOntoLed(OutputLedArray, i+EyeSize+1 	, faded_color , mix_mode,brightness);
}

/*
void tpm_fx::KITT_CenterToOutside(CRGB *OutputLedArray, uint16_t StartLed, uint16_t NrLeds, CRGB color ,uint16_t frame_pos, uint8_t EyeSize, MixModeType mix_mode, uint8_t brightness)
{
	frame_pos = constrain(frame_pos, 0 ,NrLeds/2 -EyeSize  ); 			//sanity check  -EyeSize-2
  	uint16_t i = constrain(StartLed + frame_pos , StartLed, StartLed+ NrLeds  -EyeSize );

  //for(int i =( StartLed + (NrLeds-EyeSize)/2); i>= StartLed; i--) {
    //setAll(0,0,0);
   
    CRGB faded_color = color;
	faded_color.fadeLightBy(30);


										tpm_fx::mixOntoLed(OutputLedArray, i			, faded_color , mix_mode,brightness);
	for(int j = 1; j <= EyeSize; j++)  	tpm_fx::mixOntoLed(OutputLedArray, i+j			, color 	  , mix_mode,brightness);
										tpm_fx::mixOntoLed(OutputLedArray, i+EyeSize+1 	, faded_color , mix_mode,brightness);
   

										tpm_fx::mixOntoLed(OutputLedArray, i+frame_pos*2			, faded_color , mix_mode,brightness);
	for(int j = 1; j <= EyeSize; j++)  	tpm_fx::mixOntoLed(OutputLedArray, i+j+frame_pos*2 			, color 	  , mix_mode,brightness);
										tpm_fx::mixOntoLed(OutputLedArray, i+frame_pos*2 +EyeSize+1 	, faded_color , mix_mode,brightness);

/*

  for(int i =((NUM_LEDS-EyeSize)/2); i>=0; i--) {
    setAll(0,0,0);
   
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
   


    setPixel(NUM_LEDS-i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(NUM_LEDS-i-j, red, green, blue);
    }
    setPixel(NUM_LEDS-i-EyeSize-1, red/10, green/10, blue/10);
   
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay); 
}

/*
void OutsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i = 0; i<=((NUM_LEDS-EyeSize)/2); i++) {
    setAll(0,0,0);
   
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
   
    setPixel(NUM_LEDS-i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(NUM_LEDS-i-j, red, green, blue);
    }
    setPixel(NUM_LEDS-i-EyeSize-1, red/10, green/10, blue/10);
   
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}


void NewKITT(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){
  RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
}


*/