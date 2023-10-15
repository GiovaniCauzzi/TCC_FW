/*
 * codec.h
 *
 *  Created on: Oct 9, 2023
 *      Author: giova
 */

#ifndef INC_CODEC_H_
#define INC_CODEC_H_

#include "main.h"
#include <stdint.h>


#define dCODEC_HAL_MAX_DELAY 0xFFFFFFFFU

#define dCODEC_ADDR 0x36

#define dREG_SW_RESET 0x00
#define dREG_HPOUT 0x02
#define dREG_LINE_OUTPUT1 0X03
#define dREG_LINE_OUTPUT2 0X05
#define dREG_MIC_INPUT_MODE_GAIN 0x0D
#define dREG_LINE_INPUT_MODE 0x0f
#define dREG_ADC_MIX_CONTROL 0x27
// #define dREG_
// #define dREG_
// #define dREG_


void codec_init(I2C_HandleTypeDef *i2c_instance);
HAL_StatusTypeDef codec_set_reg(I2C_HandleTypeDef *i2c_instance, unsigned char reg, unsigned char *pdata, unsigned int size);
HAL_StatusTypeDef codec_read_reg(I2C_HandleTypeDef *i2c_instance, uint16_t MemAddress, uint8_t * pdata, uint16_t size);














#endif /* INC_CODEC_H_ */
