// *************************************************************************************************
//
//	Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
//	 
//	 
//	  Redistribution and use in source and binary forms, with or without 
//	  modification, are permitted provided that the following conditions 
//	  are met:
//	
//	    Redistributions of source code must retain the above copyright 
//	    notice, this list of conditions and the following disclaimer.
//	 
//	    Redistributions in binary form must reproduce the above copyright
//	    notice, this list of conditions and the following disclaimer in the 
//	    documentation and/or other materials provided with the   
//	    distribution.
//	 
//	    Neither the name of Texas Instruments Incorporated nor the names of
//	    its contributors may be used to endorse or promote products derived
//	    from this software without specific prior written permission.
//	
//	  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//	  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//	  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//	  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//	  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//	  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//	  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//	  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//	  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//	  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//	  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// *************************************************************************************************
// Basic display functions.
// *************************************************************************************************


// *************************************************************************************************
// Include section

// system
#include "project.h"

// driver
#include "display.h"


// *************************************************************************************************
// Prototypes section


// *************************************************************************************************
// Defines section



// *************************************************************************************************
// Global Variable section

// Table with memory bit assignment for digits "0" to "9" and characters "A" to "Z"
//   A
// F   B
//   G
// E   C
//   D
const u8 lcd_font[] =
{
  SEG_A+SEG_B+SEG_C+SEG_D+SEG_E+SEG_F,           // Displays "0"
        SEG_B+SEG_C,                             // Displays "1"
  SEG_A+SEG_B+      SEG_D+SEG_E+      SEG_G,     // Displays "2"
  SEG_A+SEG_B+SEG_C+SEG_D+            SEG_G,     // Displays "3"
        SEG_B+SEG_C+            SEG_F+SEG_G,     // Displays "4"
  SEG_A+      SEG_C+SEG_D+      SEG_F+SEG_G,     // Displays "5"
#ifndef OLD_SCH  
  SEG_A+      SEG_C+SEG_D+SEG_E+SEG_F+SEG_G,     // Displays "6"
#else
	      SEG_C+SEG_D+SEG_E+SEG_F+SEG_G,     // Displays "6" without seg. A
#endif  
#ifndef NEW_CHAR
  SEG_A+SEG_B+SEG_C,                             // Displays "7"
#else
  SEG_A+SEG_B+SEG_C            +SEG_F     ,      // Displays "7"
#endif  
  SEG_A+SEG_B+SEG_C+SEG_D+SEG_E+SEG_F+SEG_G,     // Displays "8"
#ifndef OLD_SCH  
  SEG_A+SEG_B+SEG_C+SEG_D+      SEG_F+SEG_G,     // Displays "9"
#else
  SEG_A+SEG_B+SEG_C+	        SEG_F+SEG_G,     // Displays "9" without seg. D
#endif
  0                                        ,     // Displays " " (:)
  0                                        ,     // Displays " " (;)
#ifndef NEW_CHAR
  SEG_A+                        SEG_F+SEG_G,     // Displays "<" as high c
#else  
  SEG_A+                  SEG_E+SEG_F      ,     // Displays "<" as old, mirrored 7
#endif
                    SEG_D+            SEG_G,     // Displays "="
#ifndef NEW_CHAR
  0                                        ,     // Displays " " (>)
#else  
        SEG_B+SEG_C+SEG_D                  ,     // Displays ">" like mirrored L
#endif  
  SEG_A+SEG_B+            SEG_E+      SEG_G,     // Displays "?"
  0                                        ,     // Displays " " (@)
  SEG_A+SEG_B+SEG_C+      SEG_E+SEG_F+SEG_G,     // Displays "A"
              SEG_C+SEG_D+SEG_E+SEG_F+SEG_G,     // Displays "b"
                    SEG_D+SEG_E+      SEG_G,     // Displays "c"
        SEG_B+SEG_C+SEG_D+SEG_E+      SEG_G,     // Displays "d"
  SEG_A+           +SEG_D+SEG_E+SEG_F+SEG_G,     // Displays "E"
  SEG_A+                  SEG_E+SEG_F+SEG_G,     // Displays "f"
#ifndef NEW_CHAR
  SEG_A+SEG_B+SEG_C+SEG_D+      SEG_F+SEG_G,     // Displays "g" same as 9
#else
  SEG_A+     +SEG_C+SEG_D+SEG_E+SEG_F      ,     // Displays "G"
#endif  
              SEG_C+      SEG_E+SEG_F+SEG_G,     // Displays "h"
                          SEG_E            ,     // Displays "i"
#ifndef NEW_CHAR
  SEG_A+SEG_B+SEG_C+SEG_D                  ,     // Displays "J"
#else
        SEG_B+SEG_C+SEG_D+SEG_E            ,     // Displays "J"
#endif        
        	    SEG_D+      SEG_F+SEG_G,     // Displays "k"
                    SEG_D+SEG_E+SEG_F      ,     // Displays "L"
  SEG_A+SEG_B+SEG_C+      SEG_E+SEG_F      ,     // Displays "M"
              SEG_C+      SEG_E+      SEG_G,     // Displays "n"
              SEG_C+SEG_D+SEG_E+      SEG_G,     // Displays "o"
  SEG_A+SEG_B+            SEG_E+SEG_F+SEG_G,     // Displays "P"
  SEG_A+SEG_B+SEG_C+            SEG_F+SEG_G,     // Displays "q"
                          SEG_E+      SEG_G,     // Displays "r"
#ifndef NEW_CHAR
  SEG_A+      SEG_C+SEG_D+      SEG_F+SEG_G,     // Displays "S" same as 5
#else
  SEG_A+      SEG_C+SEG_D+      SEG_F      ,     // Displays "S"
#endif  
                    SEG_D+SEG_E+SEG_F+SEG_G,     // Displays "t"
              SEG_C+SEG_D+SEG_E            ,     // Displays "u"
#ifndef NEW_CHAR
              SEG_C+SEG_D+SEG_E            ,     // Displays "v" same as u
#else
              SEG_C+SEG_D+SEG_E+SEG_F      ,     // Displays "V"
#endif
        SEG_B+SEG_C+SEG_D+SEG_E+SEG_F+SEG_G,     // Displays "W"
        SEG_B+SEG_C+     +SEG_E+SEG_F+SEG_G,     // Displays "X" as H
        SEG_B+SEG_C+SEG_D+      SEG_F+SEG_G,     // Displays "Y"
#ifndef NEW_CHAR
  SEG_A+SEG_B+      SEG_D+SEG_E+      SEG_G,     // Displays "Z" same as 2
#else  
  SEG_A+SEG_B+      SEG_D+SEG_E            ,     // Displays "Z"
#endif  
};


// Table with memory address for each display element 
const u8 * segments_lcdmem[] =
{
	LCD_SYMB_AM_MEM,
	LCD_SYMB_PM_MEM,
	LCD_SYMB_ARROW_UP_MEM,
	LCD_SYMB_ARROW_DOWN_MEM,
	LCD_SYMB_PERCENT_MEM,
	LCD_SYMB_TOTAL_MEM,
	LCD_SYMB_AVERAGE_MEM,
	LCD_SYMB_MAX_MEM,
	LCD_SYMB_BATTERY_MEM,
	LCD_UNIT_L1_FT_MEM,
	LCD_UNIT_L1_K_MEM,
	LCD_UNIT_L1_M_MEM,
	LCD_UNIT_L1_I_MEM,
	LCD_UNIT_L1_PER_S_MEM,
	LCD_UNIT_L1_PER_H_MEM,
	LCD_UNIT_L1_DEGREE_MEM,
	LCD_UNIT_L2_KCAL_MEM,
	LCD_UNIT_L2_KM_MEM,
	LCD_UNIT_L2_MI_MEM,
	LCD_ICON_HEART_MEM,
	LCD_ICON_STOPWATCH_MEM,
	LCD_ICON_RECORD_MEM,
	LCD_ICON_ALARM_MEM,
	LCD_ICON_BEEPER1_MEM,
	LCD_ICON_BEEPER2_MEM,
	LCD_ICON_BEEPER3_MEM,
	LCD_SEG_L1_3_MEM,
	LCD_SEG_L1_2_MEM,
	LCD_SEG_L1_1_MEM,
	LCD_SEG_L1_0_MEM,
	LCD_SEG_L1_COL_MEM,
	LCD_SEG_L1_DP1_MEM,
	LCD_SEG_L1_DP0_MEM,
	LCD_SEG_L2_5_MEM,
	LCD_SEG_L2_4_MEM,
	LCD_SEG_L2_3_MEM,
	LCD_SEG_L2_2_MEM,
	LCD_SEG_L2_1_MEM,
	LCD_SEG_L2_0_MEM,
	LCD_SEG_L2_COL1_MEM,
	LCD_SEG_L2_COL0_MEM,
	LCD_SEG_L2_DP_MEM,
};


// Table with bit mask for each display element 
const u8 segments_bitmask[] =
{
	LCD_SYMB_AM_MASK,
	LCD_SYMB_PM_MASK,
	LCD_SYMB_ARROW_UP_MASK,
	LCD_SYMB_ARROW_DOWN_MASK,
	LCD_SYMB_PERCENT_MASK,
	LCD_SYMB_TOTAL_MASK,
	LCD_SYMB_AVERAGE_MASK,
	LCD_SYMB_MAX_MASK,
	LCD_SYMB_BATTERY_MASK,
	LCD_UNIT_L1_FT_MASK,
	LCD_UNIT_L1_K_MASK,
	LCD_UNIT_L1_M_MASK,
	LCD_UNIT_L1_I_MASK,
	LCD_UNIT_L1_PER_S_MASK,
	LCD_UNIT_L1_PER_H_MASK,
	LCD_UNIT_L1_DEGREE_MASK,
	LCD_UNIT_L2_KCAL_MASK,
	LCD_UNIT_L2_KM_MASK,
	LCD_UNIT_L2_MI_MASK,
	LCD_ICON_HEART_MASK,
	LCD_ICON_STOPWATCH_MASK,
	LCD_ICON_RECORD_MASK,
	LCD_ICON_ALARM_MASK,
	LCD_ICON_BEEPER1_MASK,
	LCD_ICON_BEEPER2_MASK,
	LCD_ICON_BEEPER3_MASK,
	LCD_SEG_L1_3_MASK,
	LCD_SEG_L1_2_MASK,
	LCD_SEG_L1_1_MASK,
	LCD_SEG_L1_0_MASK,
	LCD_SEG_L1_COL_MASK,
	LCD_SEG_L1_DP1_MASK,
	LCD_SEG_L1_DP0_MASK,
	LCD_SEG_L2_5_MASK,
	LCD_SEG_L2_4_MASK,
	LCD_SEG_L2_3_MASK,
	LCD_SEG_L2_2_MASK,
	LCD_SEG_L2_1_MASK,
	LCD_SEG_L2_0_MASK,
	LCD_SEG_L2_COL1_MASK,
	LCD_SEG_L2_COL0_MASK,
	LCD_SEG_L2_DP_MASK,
};


// Quick integer to array conversion table for most common integer values
const u8 itoa_conversion_table[][2] =
{
	"00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15",
	"16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31",
	"32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47",
	"48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63",
	"64", "65", "66", "67", "68", "69", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79",
	"80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "90", "91", "92", "93", "94", "95",
	"96", "97", "98", "99",
};

