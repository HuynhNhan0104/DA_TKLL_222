/*
 * dht20.c
 *
 *  Created on: May 9, 2023
 *      Author: NHAN
 */

#include "dht20.h"
static void DHT20_I2C_Delay(uint16_t time){
	HAL_Delay(time);
}
void DHT20_I2C_Init( DHT20_I2C_DEVICE* DHT20,I2C_HandleTypeDef* hi2c ,uint8_t address){
	DHT20_I2C_Delay(150);
	DHT20->hi2c = hi2c;
	DHT20->address = address;
	uint8_t dataBuffer[4];
	dataBuffer[0] = 0x70;
	dataBuffer[1] = 0xA8;
	dataBuffer[2] = 0x00;
	dataBuffer[3] = 0x00;
	HAL_I2C_Master_Transmit(DHT20->hi2c , DHT20->address<<1 | DHT20_Write, dataBuffer, sizeof(dataBuffer) , 100);
	DHT20_I2C_Delay(10);
	dataBuffer[0] = 0x70;
	dataBuffer[1] = 0xBE;
	dataBuffer[2] = 0x08;
	dataBuffer[3] = 0x00;
	HAL_I2C_Master_Transmit(DHT20->hi2c , DHT20->address<<1 | DHT20_Write, dataBuffer, sizeof(dataBuffer) , 100);
	DHT20_I2C_Delay(10);
}

uint8_t DHT20_I2C_ReadStatusByte(DHT20_I2C_DEVICE* DHT20){
	uint8_t status = 0;
	uint8_t dataBuffer = DHT20_GET_STATUS;
	HAL_I2C_Master_Transmit(DHT20->hi2c,  DHT20->address<<1 | DHT20_Write, &dataBuffer, 1, 100);
	HAL_I2C_Master_Receive(DHT20->hi2c,  DHT20->address<<1 | DHT20_READ, &status, 1, 100);
	return status;
}

void DHT20_I2C_TriggerMeasurement(DHT20_I2C_DEVICE* DHT20){
	uint8_t dataBuffer[4];
	dataBuffer[0] = 0x70;
	dataBuffer[1] = 0xAC;
	dataBuffer[2] = 0x33;
	dataBuffer[3] = 0x00;
	HAL_I2C_Master_Transmit(DHT20->hi2c , DHT20->address<<1  | DHT20_Write, dataBuffer, sizeof(dataBuffer) , 100);
}

void DHT20_I2C_Read(DHT20_I2C_DEVICE* DHT20, float* temp, float* humi){
	uint8_t   dataBuffer[7] ={0};
	uint32_t temp_data = 0;
	uint32_t humi_data = 0;
	// send request to Dht20 in order to trigger measurement
	DHT20_I2C_TriggerMeasurement(DHT20);
	DHT20_I2C_Delay(80);
	// if(status == 0x80 it means dht20 is complete measurement)

	HAL_I2C_Master_Receive(DHT20->hi2c,  DHT20->address<<1 | DHT20_READ, dataBuffer,sizeof(dataBuffer)  , 100);

	// get bytes of humi
	humi_data = (humi_data | dataBuffer[1]) << 8;
	humi_data = (humi_data | dataBuffer[2]) << 8;
	humi_data = (humi_data | dataBuffer[3]) >> 4;
	//get bytes of data
	temp_data = (temp_data | dataBuffer[3]) << 8;
	temp_data = (temp_data | dataBuffer[4]) << 8;
	temp_data = (temp_data | dataBuffer[5]);
	temp_data = temp_data & 0x000FFFFF;

	*temp = (float) temp_data*200/1024/1024 - 50;
	*humi = (float) humi_data*100/1024/1024;
}
