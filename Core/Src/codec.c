/*
 * codec.c
 *
 *  Created on: Oct 9, 2023
 *      Author: giova
 */

#include "codec.h"

void codec_init(I2C_HandleTypeDef *i2c_instance)
{
	uint8_t aux[2];
	uint8_t databuffer[2];
	HAL_StatusTypeDef result;

	/*
	aux[1] = ; // low byte data
	aux[0] = ; // high byte data
	result = codec_set_reg(i2c_instance, dREG_BLABLA, &aux, 2);
	*/

	aux[1] = 0x00;
	aux[0] = 0x00;
	result = codec_set_reg(i2c_instance, dREG_SW_RESET, &aux, 2);


	aux[1] = 0xC8;
	aux[0] = 0xC8;
	result = codec_set_reg(i2c_instance, dREG_HPOUT, &aux, 2);
	result = codec_read_reg(i2c_instance,dREG_HPOUT,databuffer, 2);
	// result = HAL_I2C_Mem_Write(i2c_instance, dCODEC_ADDR, dREG_SW_RESET, I2C_MEMADD_SIZE_8BIT, &aux, 2, dCODEC_HAL_MAX_DELAY);
	// result = HAL_I2C_Mem_Write(i2c_instance, dCODEC_ADDR, dREG_HPOUT, I2C_MEMADD_SIZE_8BIT, &aux, 2, dCODEC_HAL_MAX_DELAY);

	aux[1] = 0b00001000;
	aux[0] = 0b00001000;
	result = codec_set_reg(i2c_instance, dREG_LINE_OUTPUT1, &aux, 2);

	aux[1] = 0x00;
	aux[0] = 0x00;
	result = codec_set_reg(i2c_instance, dREG_LINE_OUTPUT2, &aux, 2);

	aux[1] = 0b00000000;
	aux[0] = 0b00000000;
	result = codec_set_reg(i2c_instance, dREG_MIC_INPUT_MODE_GAIN, &aux, 2);

	aux[1] = 0b00000000; //+12db //0b00001000;
	aux[0] = 0b00000000; //+12db //0b00001000;
	result = codec_set_reg(i2c_instance, dREG_LINE_INPUT_MODE, &aux, 2);

	aux[1] = 0b00000000;
	aux[0] = 0b00000000;
	result = codec_set_reg(i2c_instance, dREG_ADC_MIX_CONTROL, &aux, 2);

	aux[1] = 0b00000000;
	aux[0] = 0b00000000;
	result = codec_set_reg(i2c_instance, dREG_RECMIXL_CTRL1, &aux, 2);

	aux[1] = 0b01001001;//000110; // TUDO UNMUTED 
	aux[0] = 0b00000000;
	result = codec_set_reg(i2c_instance, dREG_RECMIXL_CTRL2, &aux, 2);

	aux[1] = 0b01001001; // TUDO UNMUTED 
	aux[0] = 0b00000000;
	result = codec_set_reg(i2c_instance, dREG_RECMIXR_CTRL2, &aux, 2);

	aux[1] = 0x00;
	aux[0] = 0x00;
	result = codec_set_reg(i2c_instance, dREG_RECMIXR_CTRL1, &aux, 2);

	aux[1] = 0b01111001;
	aux[0] = 0b00000000;
	result = codec_set_reg(i2c_instance, dREG_OUTMIXL_CTRL3, &aux, 2);

	aux[1] = 0b01111001;
	aux[0] = 0b00000000;
	result = codec_set_reg(i2c_instance, dREG_OUTMIXR_CTRL3, &aux, 2);

	aux[1] = 0b00000000;
	aux[0] = 0b01110000;
	result = codec_set_reg(i2c_instance, dREG_LOUTMIX_CTRL, &aux, 2);

	aux[1] = 0b00101111;
	aux[0] = 0b00101111;
	result = codec_set_reg(i2c_instance, dREG_ADC_DIG_VOL_CTRL, &aux, 2);

	aux[1] = 0x00;
	aux[0] = 0x00;
	result = codec_set_reg(i2c_instance, dREG_ADC_DIG_BOOST_CTRL, &aux, 2);

	aux[1] = 0b11000000;
	aux[0] = 0b10000000;
	result = codec_set_reg(i2c_instance, dREG_ADC2DAC_DIG_MIX_CTRL, &aux, 2);

	aux[1] = 0xAF;
	aux[0] = 0xAF;
	result = codec_set_reg(i2c_instance, dREG_DACL1_R1_DIG_VOL, &aux, 2);

	aux[1] = 0b01000010;
	aux[0] = 0b00000010;
	result = codec_set_reg(i2c_instance, dREG_DAC_DIG_MIX_CTRL, &aux, 2);
	
	/*
Target format:
Sample Rate: 48 KHz
Channel Length: 32 bits
LRCK=48KHz
BCLK=3.071MHz (64 * 48KHz)

MCLK clock request:
MCLK=12.288MHz (256 * 48 KHz)

Set MX-FA[0] to “1” // For MCLK input clock getting control
Set MX-61[15] to “1” // Enable I2S-1
Set MX-70[15] to “0” // Enable Master mode
*/

	aux[1] = 0b00001001;
	aux[0] = 0b00000000;
	result = codec_set_reg(i2c_instance, dREG_GENERAL_CTRL1, &aux, 2);

	aux[1] = 0b00000110;
	aux[0] = 0b10011000;
	result = codec_set_reg(i2c_instance, dREG_POWER_MANAGE_CTRL1, &aux, 2);

	aux[1] = 0b00000000;
	aux[0] = 0b10001000;
	result = codec_set_reg(i2c_instance, dREG_POWER_MANAGE_CTRL2, &aux, 2);

	aux[1] = 0b00011001;
	aux[0] = 0b11111000;
	result = codec_set_reg(i2c_instance, dREG_POWER_MANAGE_CTRL3, &aux, 2);

	aux[1] = 0b00000000;
	aux[0] = 0b11001100;
	result = codec_set_reg(i2c_instance, dREG_POWER_MANAGE_CTRL5, &aux, 2);
	
	aux[1] = 0x00;
	aux[0] = 0b00110011;
	result = codec_set_reg(i2c_instance, dREG_POWER_MANAGE_CTRL6, &aux, 2);

	aux[1] = 0b00000110;
	aux[0] = 0b10011000; // config device as slave
	result = codec_set_reg(i2c_instance, dREG_DIG_INTERFACE_CONTROL, &aux, 2);

	aux[1] = 0b00000101;
	aux[0] = 0b00110000;
	result = codec_set_reg(i2c_instance, dREG_ADC_DAC_CLK_CTRL1, &aux, 2);

	aux[1] = 0b00001000;
	aux[0] = 0b00000000;
	result = codec_set_reg(i2c_instance, dREG_GLOBAL_CLK_CTRL, &aux, 2);
}

HAL_StatusTypeDef codec_set_reg(I2C_HandleTypeDef *i2c_instance, unsigned char MemAddress, unsigned char *pdata, unsigned int size)
{
	uint32_t delayTosco = 0;
	uint32_t timer = 50000;

	while(delayTosco++ < timer){}
	return HAL_I2C_Mem_Write(i2c_instance, dCODEC_ADDR, MemAddress, I2C_MEMADD_SIZE_8BIT, pdata, size, dCODEC_HAL_MAX_DELAY);
}

/*
HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c,
uint16_t DevAddress,
uint16_t MemAddress,
uint16_t MemAddSize,
uint8_t *pData,
uint16_t Size,
uint32_t Timeout)*/

HAL_StatusTypeDef codec_read_reg(I2C_HandleTypeDef *i2c_instance, uint16_t MemAddress, uint8_t * pdata, uint16_t size)
{
	return HAL_I2C_Mem_Read(i2c_instance, dCODEC_ADDR, MemAddress, I2C_MEMADD_SIZE_8BIT, pdata, size, dCODEC_HAL_MAX_DELAY);
}

/*
HAL_StatusTypeDef HAL_I2C_Mem_Read(
	I2C_HandleTypeDef *hi2c, uint16_t DevAddress,
	uint16_t MemAddress,
	uint16_t MemAddSize,
	uint8_t *pData,
	uint16_t Size,
	uint32_t Timeout)
*/
