/*
 * LIS302DL.C
 *
 *  Created on: Aug 29, 2024
 *      Author: emirhan
 */

#include "LIS3DSH.h"
#include <stm32f4xx_hal.h>
#include <string.h>
#include <stdio.h>

static SPI_HandleTypeDef LIS3DSHspi;
static UART_HandleTypeDef LIS3DSHuart;

void LIS3DSH_Write(uint8_t reg, uint8_t* Data, uint8_t size)
{
	_LIS3DHS_CS_ENBALE;

	HAL_SPI_Transmit(&LIS3DSHspi, &reg, 1, 10);

	HAL_SPI_Transmit(&LIS3DSHspi, Data, size, 10);

	_LIS3DHS_CS_DISABLE;
}


uint8_t LIS3DSH_Read(uint8_t reg,uint8_t size)
{
	uint8_t reg_addr = reg | 0x80;
	uint8_t retdata;

	_LIS3DHS_CS_ENBALE

	HAL_SPI_Transmit(&LIS3DSHspi, &reg_addr, size, HAL_MAX_DELAY);

	HAL_SPI_Receive(&LIS3DSHspi, &retdata, size, HAL_MAX_DELAY);

	_LIS3DHS_CS_DISABLE

	return retdata;
}


int LIS3DSH_Init(SPI_HandleTypeDef *mySPI,LIS3DSH_InitTypeDef *SensorInitDef)
{
	uint8_t spiDataReg = 0;

	memcpy(&LIS3DSHspi, mySPI, sizeof(*mySPI));

	// Set CTRL_REG_4
	spiDataReg |= (SensorInitDef->SelectAxes << 0);
	spiDataReg |= (SensorInitDef->BDU_select << 3);
	spiDataReg |= (SensorInitDef->OdrConfig  << 4);

	LIS3DSH_Write(CTRL_REG4, &spiDataReg, 1);

	// Set CTRL_REG_5
	spiDataReg = 0;
	spiDataReg |= (SensorInitDef->FullScale  << 3);
	spiDataReg |= (SensorInitDef->bandwidth  << 6);

	LIS3DSH_Write(CTRL_REG5, &spiDataReg, 1);

	_LIS3DHS_CS_DISABLE;

	return _LIS3DHS_OK;
}

void LIS3DSH_FIFO_Init()
{
	uint8_t FifoVal = 0 ;
	uint8_t watermark = 0x1F;

	FifoVal |= (1 << 5);  // FIFO mode
	FifoVal |= (0 << 6);

	/*FifoVal |= (0 << 5);  // Stream mode
	FifoVal |= (1 << 6);*/

	FifoVal |= (watermark & 0x1F); // WTMP[4:0] = 16

	LIS3DSH_Write(FIFO_CTRL, &FifoVal, 1);

}



LIS3DSH_DataRaw LIS3DSH_GetDataRaw(void)
{
	uint8_t spiBuf[2];
	LIS3DSH_DataRaw DataRaw;

	//Read X data
	spiBuf[1] = LIS3DSH_Read(OUT_X_L, 1);
	spiBuf[0] = LIS3DSH_Read(OUT_X_H, 1);
	DataRaw.x = ((spiBuf[0] << 8) + spiBuf[1]);

	//Read Y data
	spiBuf[1] = LIS3DSH_Read(OUT_Y_L, 1);
	spiBuf[0] = LIS3DSH_Read(OUT_Y_H, 1);
	DataRaw.y = ((spiBuf[0] << 8) + spiBuf[1]);

	//Read z data
	spiBuf[1] = LIS3DSH_Read(OUT_Z_L, 1);
	spiBuf[0] = LIS3DSH_Read(OUT_Z_H, 1);
	DataRaw.z = ((spiBuf[0] << 8) + spiBuf[1]);

	return DataRaw;

}

void LIS3DSH_Sleep()
{
	uint8_t sleepDate =0x07;

	LIS3DSH_Write(CTRL_REG4, &sleepDate, 1);

}

void LIS3DSH_Unsleep(LIS3DSH_InitTypeDef *SensorInitDef)
{
	uint8_t sleepDate =0x07;

	sleepDate |= (SensorInitDef->OdrConfig  << 4);

	LIS3DSH_Write(CTRL_REG4, &sleepDate, 1);

}



void motion_detection()
{
	uint8_t mask1_b_value = 0x80;

	LIS3DSH_Write(MASK2_B, &mask1_b_value, 1);

}


void offset_x(uint8_t offsetVal)
{
	LIS3DSH_Write(OFF_X,&offsetVal,1);
}

void offset_y(uint8_t offsetVal)
{
	LIS3DSH_Write(OFF_Y,&offsetVal,1);
}

void offset_z(uint8_t offsetVal)
{
	LIS3DSH_Write(OFF_Z,&offsetVal,1);
}


void shiftAxis_x(uint8_t shiftVal)
{
	LIS3DSH_Write(CS_X,&shiftVal,1);
}

void shiftAxis_y(uint8_t shiftVal)
{
	LIS3DSH_Write(CS_Y,&shiftVal,1);
}

void shiftAxis_z(uint8_t shiftVal)
{
	LIS3DSH_Write(CS_Z,&shiftVal,1);
}



uint8_t read_INFO1(SPI_HandleTypeDef *mySPI)
{
	return LIS3DSH_Read(INFO1,1);
}

uint8_t read_who_am_i()
{
	return LIS3DSH_Read(WHO_AM_I,1);
}

uint8_t read_INFO2()
{
	return LIS3DSH_Read(INFO2,1);
}

int8_t read_temperature()
{
    return LIS3DSH_Read(OUT_T,1);
}

uint8_t read_status()
{
	return LIS3DSH_Read(STATUS,1);
}

uint8_t read_stat()
{
	return LIS3DSH_Read(STAT,1);
}


void send_accelerometer_data(int16_t x, int16_t y, int16_t z, UART_HandleTypeDef *myUart) {
    char buffer[50];

    sprintf(buffer, "%d,%d,%d\r\n", x, y, z);

    memcpy(&LIS3DSHuart, myUart, sizeof(*myUart));

    HAL_UART_Transmit(&LIS3DSHuart, (uint8_t*)buffer, strlen(buffer), 10);
}


LIS3DSH_DataRaw ReadFIFOData(LIS3DSH_InitTypeDef *mySensor,UART_HandleTypeDef *myUart) {

	LIS3DSH_Unsleep(mySensor);
	LIS3DSH_DataRaw DataRaw;
    for (int i = 0; i < 16; i++) {

    	uint8_t spiBuf[2];

    	spiBuf[1] = LIS3DSH_Read(OUT_X_L, 1);
    	spiBuf[0] = LIS3DSH_Read(OUT_X_H, 1);
    	DataRaw.x = ((spiBuf[0] << 8) + spiBuf[1]);

    	//Read Y data
    	spiBuf[1] = LIS3DSH_Read(OUT_Y_L, 1);
    	spiBuf[0] = LIS3DSH_Read(OUT_Y_H, 1);
    	DataRaw.y = ((spiBuf[0] << 8) + spiBuf[1]);

    	//Read z data
    	spiBuf[1] = LIS3DSH_Read(OUT_Z_L, 1);
    	spiBuf[0] = LIS3DSH_Read(OUT_Z_H, 1);
    	DataRaw.z = ((spiBuf[0] << 8) + spiBuf[1]);

        send_accelerometer_data(DataRaw.x, DataRaw.y, DataRaw.z,myUart);
    }
    LIS3DSH_Sleep();

    return DataRaw;
}


