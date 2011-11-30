#ifndef macros_H_
#define macros_H_

#define BIT(x) (1 << x)
#define bit_get(p,m) ((p) & (m))
#define bit_set(p,m) ((p) |= (m))
#define bit_clear(p,m) ((p) &= ~(m))
#define bit_flip(p,m) ((p) ^= (m))




#endif /*macros_H_*/

