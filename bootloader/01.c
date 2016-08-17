#include <avr/io.h>
#include <inttypes.h>

#ifndef SPMCSR
#define SPMCSR SPMCR
#endif

#ifndef SPMEN
#define SPMEN SELFPRGEN
#endif

#ifndef RWWSB
#define RWWSB ASB
#endif

#ifndef RWWSRE
#define RWWSRE ASRE
#endif

/*
 * the followng assumptions are made:
 * (a) interrupts are globally disabled (the I flag in the SREG is cleared)
 * (b) there's no EEPROM write in progress
 *
 * TODO: support devices with more than 64 kB of memory
 */
static void do_spm(uint8_t op, uint16_t r0r1, uint16_t z)
{
	//op |= _BV(SPMEN);
	
	// wait for ongoing page erase/write to finish
	while ((SPMCSR & _BV(SPMEN)) != 0);
	
	// rigth shift operation (>>) could possibly override r0
	// just to be on the safe side assing a value to r1 first
	register uint8_t r1 asm ("r1") = r0r1 >> 8;
	register uint8_t r0 asm ("r0") = r0r1;
	asm volatile
	(
	 	#pragma push_macro("_SFR_IO8")
	 	#pragma push_macro("_SFR_MEM8")
	 	#undef _SFR_IO8
	 	#undef _SFR_MEM8
	 	#define _SFR_IO8(addr) 1
	 	#define _SFR_MEM8(addr) 0
	 	#if SPMCSR
		"out %[spmcsr], %[op]\n\t"
		#else
		"sts %[spmcsr], %[op]\n\t"
		#endif
		"spm\n\t"
		#if defined(__AVR_ATmega161__) || defined(__AVR_ATmega163__) || defined(__AVR_ATmega323__)
		".word 0xffff\n\t"
		"nop\n\t"
		#endif
		"clr %[r1]"
		: [r1]		"+r"	(r1)
		#if SPMCSR
		#pragma pop_macro("_SFR_IO8")
	 	#pragma pop_macro("_SFR_MEM8")
		: [spmcsr]	"I"	(_SFR_IO_ADDR(SPMCSR)),
		#else
		#pragma pop_macro("_SFR_IO8")
	 	#pragma pop_macro("_SFR_MEM8")
		: [spmcsr]	"i"	(_SFR_MEM_ADDR(SPMCSR)),
		#endif
		  [op]		"r"	(op),
				"r"	(r0),
		//		"r"	(r1),
				"z"	(z)
	);
	r1 = 5;
}

#define boot_page_erase(addr) do_spm(_BV(SPMEN) | _BV(PGERS), 0, (addr))
#define boot_spm_busy_wait() do {} while (0)
#define boot_page_fill(addr, w) do_spm(_BV(SPMEN), (w), (addr))
#define boot_page_write(addr) do_spm(_BV(SPMEN) | _BV(PGWRT), 0, (addr))
#define boot_rww_enable() do_spm(_BV(SPMEN) | _BV(RWWSRE), 0, 0)

//#include <avr/boot.h>

#ifndef EEWE
#define EEWE EEPE
#endif

// disable interrupt before calling this function
void erase_and_write_a_page(uint16_t addr, uint8_t *buf)
{
	// wait for the ongoing EEPROM write to finish
	while ((EECR & EEWE) != 0);
	
	boot_page_erase(addr);
	boot_spm_busy_wait();
	
	#if SPM_PAGESIZE <= UINT8_MAX
	uint8_t i;
	#else
	uint16_t i;
	#endif
	for (i = 0; i < SPM_PAGESIZE; i += 2)
	{
		uint16_t w = buf[i] | (buf[i + 1] << 8);
		/*
		uint16_t w = *buf++;
		w |= (*buf++) << 8;
		*/
		boot_page_fill(addr + i, w);
	}
	
	boot_page_write(addr);
	boot_spm_busy_wait();
	
	boot_rww_enable();
}
