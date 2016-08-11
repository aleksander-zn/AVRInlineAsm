#include <avr/io.h>
#include <avr/eeprom.h>

/* To declare an EEPROM variable, use the EEMEM attribute -- it will put it into
 * the '.eeprom' section: EEMEM -> __attribute__((section ".eeprom")).
 * You can give an initial value that will be stored in the '.eeprom' section of
 * the output file and should be burnt into the EEPROM of an AVR chip.
 * Don't declare EEPROM vars as constant as they aren't.
 */
uint8_t EEPROMu8 EEMEM = 20;

int main(void)
{
	/* static locals can reside in EEPROM */
	static uint16_t EEPROMu16 EEMEM = 15;
	uint8_t SRAMu8;

	/* Don't use the assignment operator (i.e. SRAMu8 = EEPROMu8) on EEPROM
	 * variables -- since they reside in different memory space, you need to
	 * use eeprom_read_* instructions just like pgm_read_* with program
	 * space constants.
	 */
	SRAMu8 = eeprom_read_byte(&EEPROMu8);
	SRAMu8++;
	
	/* Similarily -- write using dedicated functions, if possible use
	 * eeprom_update_* function to increase the lifespan.
	 */
	eeprom_write_word(&EEPROMu16, SRAMu8);

	return 0;
}
