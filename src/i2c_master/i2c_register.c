#include "i2c_master.h"

I2C_STATUS i2c_write_byte_to_reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t data)
{
	I2C_STATUS status = I2C_TRANSFER_OK;
	i2c_start();

	if(i2c_send_byte(dev_addr | I2C_ADDR_WRITE_FLAG) == NASK)		{status = I2C_NO_DEVICE;			goto end;}
	if(i2c_send_byte(reg_addr) == NASK)								{status = I2C_REG_WRITE_FAIL;		goto end;}
	if(i2c_send_byte(data) == NASK)									{status = I2C_WRITE_DATA_FAIL;	goto end;}

	end:

	i2c_stop();
	return status;
}

I2C_STATUS i2c_read_16bit_from_reg(uint8_t dev_addr, uint8_t reg_addr, uint16_t* data)
{
	I2C_STATUS status = I2C_TRANSFER_OK;
	i2c_start();

	if(i2c_send_byte(dev_addr | I2C_ADDR_WRITE_FLAG) == NASK)		{status = I2C_NO_DEVICE;			goto end;}
	if(i2c_send_byte(reg_addr) == NASK)								{status = I2C_REG_WRITE_FAIL;		goto end;}

	i2c_start();
	if(i2c_send_byte(dev_addr | I2C_ADDR_READ_FLAG) == NASK)			{status = I2C_RESTART_FAIL;		goto end;}

	i2c_read_16bit(data, false);

	end:

	i2c_stop();
	return status;
}
