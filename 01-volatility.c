#include <stdint.h>
#include <avr/io.h>

////////////////////////////////////////////////////////////////////////////////
// WARNING: This method will not work as expected. It will not print 80 space //
//	    characters unless you append the 'volatile' keyword to 'asm'.     //
////////////////////////////////////////////////////////////////////////////////
int8_t _80spaces(void) {
	uint8_t space = ' ';
	int8_t i;
	int8_t result = 0;
	for (i = 0; i < 80; i++) {
		//asm volatile (
		asm (
			// This code will appear in compiler's output between
			// #APP and #NOAPP tags.
			"1:" "\n\t"
			"sbis %[ucsra], %[udre]" "\n\t"
			"rjmp 1b" "\n\t"
			"out %[udr], %[space]" "\n\t"
			"ldi %[result], 1" "\n\t"

			// some diagnostic information
			"/* result: %[result]" "\n\t"
			"   ucsra: %[ucsra]" "\n\t"
			"   udre: %[udre]" "\n\t"
			"   udr: %[udr]" "\n\t"
			"   space: %[space] */"

			// the output operands
			// Without any output operands this asm statement would
			// be implicitly volatile so I've added one.
			// It's interesting that this operand can (and probably
			// will) be assigned to the same register as %[space],
			// because by default GCC assumes that all input values
			// will have been consumed by the time the first output
			// operand is written to.
			: [result] "=d" (result)

			// the input operands
			: [ucsra] "I" (_SFR_IO_ADDR(UCSRA)),
			  [udre] "I" (UDRE),
			  [udr] "I" (_SFR_IO_ADDR(UDR)),
			  [space] "r" (space)
		);
	}
	return result;
}
