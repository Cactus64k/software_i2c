#include "chunks.h"
#include "suart/suart.h"
#include "i2c_master/i2c_master.h"

int main()
{
	SUART_tx_init();
	SUART_init_tx_stdio();

	sei();

	_delay_ms(4000);


	#define LM75_ADDR (0b10011110)




	while(1)
	{
		printf("start SDA = %d, SCL=%d\n", !!I2C_PIN_STATE(SDA),  !!I2C_PIN_STATE(SCL));
		if(i2c_init() == EXIT_SUCCESS)
		{
			i2c_start();
			int res = i2c_send_byte(LM75_ADDR | I2C_ADDR_WRITE_FLAG);		// addr
			printf("addr %s\n", (res == ASK)? "OK": "FAIL");
			res = i2c_send_byte(0x00);	//reg
			printf("reg %s\n", (res == ASK)? "OK": "FAIL");


			i2c_start();
			res = i2c_send_byte(LM75_ADDR | I2C_ADDR_READ_FLAG);
			printf("addr %s\n", (res == ASK)? "OK": "FAIL");
			uint16_t temp = 0;
			i2c_read_16bit(&temp, false);
			i2c_stop();

			printf("byte = 0x%X, %f\n", temp, (temp>>5)*0.125);
		}
		_delay_ms(1000);
	}

	return EXIT_SUCCESS;
}

