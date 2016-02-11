CC = avr-gcc
MMCU = atmega8

# Flags required by both the C compiler and the linker.
# It seems obvious that device type must be known during the compilation, for
# example to include proper SFR definitions.
# However, it is also requierd by the linker -- to include device-specific
# startup code, link appropriate functions, etc.
COMMON_FLAGS = -mmcu=${MMCU}

CFLAGS = -Wall -Os ${COMMON_FLAGS}
LDFLAGS = ${COMMON_FLAGS}

volatility.s: volatility.c
	${CC} ${CFLAGS} ${CPPFLAGS} -S -o $@ $<
