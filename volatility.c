#include <stdint.h>
#include <avr/io.h>

int8_t _80spaces(void) {
	uint8_t space = ' ';
	int8_t i;
	int8_t result = 0;
	for (i = 0; i < 80; i++) {
		asm (
			"1:" "\n\t"
			"sbis %[ucsra], %[udre]" "\n\t"
			"rjmp 1b" "\n\t"
			"out %[udr], %[space]" "\n\t"
			"ldi %[result], 1" "\n\t"
			"/* result: %[result]" "\n\t"
			"   ucsra: %[ucsra]" "\n\t"
			"   udre: %[udre]" "\n\t"
			"   udr: %[udr]" "\n\t"
			"   space: %[space] */"
			: [result] "=d" (result)
			: [ucsra] "I" (_SFR_IO_ADDR(UCSRA)),
			  [udre] "I" (UDRE),
			  [udr] "I" (_SFR_IO_ADDR(UDR)),
			  [space] "r" (space)
		);
	}
	return result;
}
