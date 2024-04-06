


#ifndef AVRLIBDEFS_H
#define AVRLIBDEFS_H
#define MEM_TYPE 1
#ifndef outb
	#define	outb(addr, data)	addr = (data)
#endif
#ifndef inb
	#define	inb(addr)			(addr)
#endif
#ifndef outw
	#define	outw(addr, data)	addr = (data)
#endif
#ifndef inw
	#define	inw(addr)			(addr)
#endif
#ifndef BV
	#define BV(bit)			(1<<(bit))
#endif
#ifndef cli
	#define cli()			__asm__ __volatile__ ("cli" ::)
#endif
#ifndef sei
	#define sei()			__asm__ __volatile__ ("sei" ::)
#endif
#ifdef __AVR_ATmega128__
#ifndef PD0
#endif
#endif

#define GNUC_PACKED __attribute__((packed)) 

#define DDR(x) ((x)-1)    
#define PIN(x) ((x)-2)    
#define MIN(a,b)			((a<b)?(a):(b))
#define MAX(a,b)			((a>b)?(a):(b))
#define ABS(x)				((x>0)?(x):(-x))

#define PI		3.14159265359

#endif