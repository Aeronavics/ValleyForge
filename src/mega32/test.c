#include <avr32/io.h>
#include "mega32.h"

#define BIT(x) (1 << x)
#define bit_get(p,m) ((p) & (m))
#define bit_set(p,m) ((p) |= (m))
#define bit_clear(p,m) ((p) &= ~(m))
#define bit_flip(p,m) ((p) ^= (m))

#define LED_COL_0	PB1
#define LED_COL_1	PB2
#define LED_COL_2	PB3
#define LED_COL_3	PD0
#define LED_COL_4	PD4

#define LED_ROW_0	PC2
#define LED_ROW_1	PC3
#define LED_ROW_2	PC4
#define LED_ROW_3	PC5
#define LED_ROW_4	PD5
#define LED_ROW_5	PD6
#define LED_ROW_6	PD7

int main (void)
{
 int nothing;
 nothing = 3;
 nothing++;
  
  while (1)
  {
  }
  
  return 0;
}