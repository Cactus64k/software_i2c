#ifndef I2C_MASTER_I2C_MASTER_H_
	#define I2C_MASTER_I2C_MASTER_H_

	#include <avr/io.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <stdint.h>
	#include <avr/interrupt.h>
	#include <stdbool.h>

	#define I2C_PORT				PORTB
	#define I2C_PIN					PINB
	#define I2C_DDR					DDRB
	#define SDA						PB2
	#define SCL						PB1

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
	void i2c_read_byte(uint8_t* byte, bool send_ask);
	void i2c_read_16bit(uint16_t* word, bool send_ask);
	void i2c_start();
	void i2c_stop();

	typedef enum I2C_STATUS
	{
		I2C_TRANSFER_OK = 0,
		I2C_NO_DEVICE,
		I2C_REG_WRITE_FAIL,
		I2C_RESTART_FAIL,
		I2C_WRITE_DATA_FAIL
	} I2C_STATUS;

	I2C_STATUS i2c_write_byte_to_reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t data);
	I2C_STATUS i2c_read_16bit_from_reg(uint8_t dev_addr, uint8_t reg_addr, uint16_t* data);


#endif /* I2C_MASTER_I2C_MASTER_H_ */
