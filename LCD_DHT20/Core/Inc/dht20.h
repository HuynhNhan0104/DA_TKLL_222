/*
 * DHT20.h
 *
 *  Created on: May 9, 2023
 *      Author: NHAN
 */

#ifndef INC_DHT20_H_
#define INC_DHT20_H_
#include "stm32f1xx_hal.h"

#define DHT20_ADDRESS 		0x38
#define DHT20_READ 		 		0x01
#define DHT20_Write				0x00
#define DHT20_GET_STATUS		0x71


typedef struct {
	I2C_HandleTypeDef* hi2c;
	uint8_t address;
} DHT20_I2C_DEVICE ;


void DHT20_I2C_Init( DHT20_I2C_DEVICE* DHT20, I2C_HandleTypeDef* hi2c ,uint8_t address);
uint8_t DHT20_I2C_ReadStatusByte(DHT20_I2C_DEVICE* DHT20);
void DHT20_I2C_TriggerMeasurement(DHT20_I2C_DEVICE* DHT20);
void DHT20_I2C_Read(DHT20_I2C_DEVICE* DHT20, float* temp, float* humi);

#endif /* INC_DHT20_H_ */
