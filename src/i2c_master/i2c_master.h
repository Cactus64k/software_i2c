#ifndef I2C_MASTER_I2C_MASTER_H_
	#define I2C_MASTER_I2C_MASTER_H_

	#include <avr/io.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <stdint.h>
	#include <avr/interrupt.h>
	#include <util/delay.h>
	#include <stdbool.h>

	#define I2C_PORT				PORTB
	#define I2C_PIN					PINB
	#define I2C_DDR					DDRB
	#define SDA						PB1
	#define SCL						PB2

	#define ASK						0
	#define NASK					1

	#define I2C_ADDR_READ_FLAG		0x01
	#define I2C_ADDR_WRITE_FLAG	0x00

	#define I2C_SET_PIN_HIGH(pin)	{I2C_DDR	= I2C_DDR & ~_BV(pin);}		// включается HI-z
	#define I2C_SET_PIN_LOW(pin)		{I2C_DDR	= I2C_DDR | _BV(pin);}		// обычный выход с нулем в PORTB
	#define I2C_SET_PIN_HZ(pin)		{I2C_SET_PIN_HIGH(pin)}

	#define I2C_PIN_STATE(pin)		(I2C_PIN & _BV(pin))

	int i2c_init();
	int i2c_send_byte(uint8_t byte);
	void i2c_read_byte(uint8_t * byte, bool send_ask);
	void i2c_read_16bit(uint16_t * word, bool send_ask);
	void i2c_start();
	void i2c_stop();


#endif /* I2C_MASTER_I2C_MASTER_H_ */
