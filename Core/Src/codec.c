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
	aux[0] = ;
	aux[1] = ;
	result = codec_set_reg(i2c_instance, dREG_BLABLA, &aux, 2);
	*/

	aux[0] = 0x00;
	aux[1] = 0x00;
	result = codec_set_reg(i2c_instance, dREG_SW_RESET, &aux, 2);

	aux[0] = 0xC8;
	aux[1] = 0xC8;
	result = codec_set_reg(i2c_instance, dREG_HPOUT, &aux, 2);
	result = codec_read_reg(i2c_instance,dREG_HPOUT,databuffer, 2);
	// result = HAL_I2C_Mem_Write(i2c_instance, dCODEC_ADDR, dREG_SW_RESET, I2C_MEMADD_SIZE_8BIT, &aux, 2, dCODEC_HAL_MAX_DELAY);
	// result = HAL_I2C_Mem_Write(i2c_instance, dCODEC_ADDR, dREG_HPOUT, I2C_MEMADD_SIZE_8BIT, &aux, 2, dCODEC_HAL_MAX_DELAY);

	aux[0] = 0b00001000;
	aux[1] = 0b00001000;
	result = codec_set_reg(i2c_instance, dREG_LINE_OUTPUT1, &aux, 2);

	aux[0] = 0x00;
	aux[1] = 0x00;
	result = codec_set_reg(i2c_instance, dREG_LINE_OUTPUT2, &aux, 2);

	aux[0] = 0b00000000;
	aux[1] = 0x00;
	result = codec_set_reg(i2c_instance, dREG_MIC_INPUT_MODE_GAIN, &aux, 2);

	aux[0] = 0b00001000;
	aux[1] = 0b00001000;
	result = codec_set_reg(i2c_instance, dREG_LINE_INPUT_MODE, &aux, 2);

	aux[0] = 0b00000000;
	aux[1] = 0b00000000;
	result = codec_set_reg(i2c_instance, dREG_ADC_MIX_CONTROL, &aux, 2);

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

	aux[0] = 0b00000001;
	aux[1] = 0b00000000;
	result = codec_set_reg(i2c_instance, dREG_GENERAL_CTRL1, &aux, 2);

	aux[0] = 0b00000110;
	aux[1] = 0b10011000;
	result = codec_set_reg(i2c_instance, dREG_POWER_MANAGE, &aux, 2);

	aux[0] = 0b00000000;
	aux[1] = 0b00000000;
	result = codec_set_reg(i2c_instance, dREG_DIG_INTERFACE_CONTROL, &aux, 2);

	aux[0] = 0b00000100;
	aux[1] = 0b00000000;
	result = codec_set_reg(i2c_instance, dREG_ADC_DAC_CLK_CTRL1, &aux, 2);

	
}

HAL_StatusTypeDef codec_set_reg(I2C_HandleTypeDef *i2c_instance, unsigned char MemAddress, unsigned char *pdata, unsigned int size)
{
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