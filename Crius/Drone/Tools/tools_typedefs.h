/*
 * tools_typedefs.h
 *
 * Created: 28/06/2011 15:55:05
 *  Author: berryer
 */ 


#ifndef TOOLS_TYPEDEFS_H_
#define TOOLS_TYPEDEFS_H_

 #include <avr/interrupt.h> 
  
#ifndef ATOMIC
#define ATOMIC(code)                    \
    {                                   \
    cli();								\
    do{ code }while(0);                 \
    sei();								\
    }
#endif


static inline float SetRange(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

static inline float SetLimits(float val, float min, float max) 
{ 
	if(val > max)
	{
		val = max;
	}
	else if(val < min)
	{
		val = min;
	}
	return val;
}	

static inline void swap_endianness(void *buf, uint8_t size) 
{
  /* we swap in-place, so we only have to
  * place _one_ element on a temporary tray
  */
  uint8_t tray;
  uint8_t *from;
  uint8_t *to;
  /* keep swapping until the pointers have assed each other */
  for (from = (uint8_t*)buf, to = &from[size-1]; from < to; from++, to--) {
    tray = *from;
    *from = *to;
    *to = tray;
  }
}
/*
 * Basic Macros
 */
#define ToDeg(x) (x*(float)(180/M_PI))  
#define ToRad(x) (x*(float)(M_PI/180))  

#define BIT_HIGH( reg , bit )		reg |=  ( 1U << bit );
#define BIT_LOW( reg , bit )		reg &= ~( 1U << bit );
#define BIT_TOGGLE( reg , bit )		reg ^=  ( 1U << bit );
#define BIT_SET( reg , bit , val)							\
									if( val )				\
									{						\
										BIT_HIGH( reg , bit)\
									}						\
									else					\
									{						\
										BIT_LOW( reg , bit)	\
									};

/*
 * Basic types for the microcontroler
 */
#define ABS(X)						((X) > 0 ? (X) : -(X))    
#define MID(X,limitdown,limitup)	((X > limitdown ) && (X < limitup ))
#define MIN(A,B)					(((A)<(B)) ? (A) : (B) )
#define MAX(A,B)					(((A)>(B)) ? (A) : (B) )

// Unsigned 8 bits char
typedef char Char;

// Unsigned 8 bits integer type
typedef unsigned char Int8U;
// Unsigned 16 bits integer type
typedef unsigned int Int16U;
// Unsigned 32 bits integer type
typedef unsigned long Int32U;

// Signed 8 bits integer type
typedef signed char Int8S;
// Signed 16 bits integer type
typedef signed int Int16S;
// Signed 32 bits integer type
typedef signed long Int32S;

// Boolean type
typedef Int8U Boolean;
	#define FALSE       0U
	#define TRUE        1U
	#define	ENABLE		TRUE
	#define	DISABLE		FALSE

// Null pointer
#ifndef NULL
  #define NULL     ((void *)0U)
#endif

//definit un type de pointeur de fonction pour abstraire les interruptions micro
typedef void (*ptrfct_Isr_Callback)(void);
//defini un pointeur vers une fct null, reset du micro
#define RESET_SOFT() ptrfct_Isr_Callback ptrfct_null = NULL; ptrfct_null();


#endif /* TOOLS_TYPEDEFS_H_ */