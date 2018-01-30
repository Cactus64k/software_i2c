#include "i2c_master.h"


int i2c_init()
{
	I2C_PORT	= I2C_PORT & ~_BV(SCL);
	I2C_PORT	= I2C_PORT & ~_BV(SDA);

	I2C_DDR		= I2C_DDR & ~_BV(SCL);
	I2C_DDR		= I2C_DDR & ~_BV(SDA);

	if(I2C_PIN_STATE(SCL) == 0)
		return EXIT_FAILURE;
	else if(I2C_PIN_STATE(SDA) == 0)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

void i2c_start()
{
	if(I2C_PIN_STATE(SCL) && !I2C_PIN_STATE(SDA))
		I2C_SET_PIN_LOW(SCL);

	I2C_SET_PIN_HIGH(SDA);
	I2C_SET_PIN_HIGH(SCL);

	I2C_SET_PIN_LOW(SDA);
	//I2C_SET_PIN_LOW(SCL);
}

int i2c_send_byte(uint8_t byte)
{
	uint8_t mask = 1<<7;
	while(mask)
	{
		I2C_SET_PIN_LOW(SCL);

		if(byte & mask)
		{
			I2C_SET_PIN_HIGH(SDA);
		}
		else
		{
			I2C_SET_PIN_LOW(SDA);
		}
		I2C_SET_PIN_HIGH(SCL);

		//loop_until_bit_is_set(I2C_PIN, SCL);

		mask = mask >> 1;
	}

	I2C_SET_PIN_LOW(SCL);
	I2C_SET_PIN_HZ(SDA);			// освобождаем линию для слейва
	I2C_SET_PIN_HIGH(SCL);

	if(I2C_PIN_STATE(SDA))
		return NASK;
	else
		return ASK;
}

void i2c_read_byte(uint8_t * byte, bool send_ask)
{
	I2C_SET_PIN_LOW(SCL);
	I2C_SET_PIN_HZ(SDA);
	uint8_t mask = 1<<7;
	while(mask)
	{
		I2C_SET_PIN_LOW(SCL);
		I2C_SET_PIN_HIGH(SCL);

		if(I2C_PIN_STATE(SDA))
			*byte = (*byte) | mask;

		mask = mask >> 1;
	}

	I2C_SET_PIN_LOW(SCL);
	if(send_ask == true)
	{
		I2C_SET_PIN_LOW(SDA);
	}
	I2C_SET_PIN_HIGH(SCL);
}

void i2c_read_16bit(uint16_t * word, bool send_ask)
{
	uint8_t l_byte = 0;
	uint8_t h_byte = 0;

	i2c_read_byte(&h_byte, true);
	i2c_read_byte(&l_byte, send_ask);

	*word = (uint16_t)h_byte << 8 | l_byte;
}

void i2c_stop()
{
	if(!I2C_PIN_STATE(SDA) && I2C_PIN_STATE(SCL))
	{
		I2C_SET_PIN_HIGH(SDA);
	}
	else
	{
		I2C_SET_PIN_LOW(SCL);
		I2C_SET_PIN_LOW(SDA);

		I2C_SET_PIN_HIGH(SCL);
		I2C_SET_PIN_HIGH(SDA);
	}
}
