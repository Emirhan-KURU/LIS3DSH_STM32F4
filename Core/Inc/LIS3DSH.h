/*
 * LIS302DL.H
 *
 *  Created on: Aug 29, 2024
 *      Author: emirhan
 */

#ifndef INC_LIS3DSH_H_
#define INC_LIS3DSH_H_

#include <stdint.h>
#include <stm32f4xx_hal.h>
#include <stdbool.h>



#define _LIS3DHS_CS_ENBALE		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
#define _LIS3DHS_CS_DISABLE		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);

#define _LIS3DHS_OK    1
#define _LIS3DHS_NOT   0



#define OUT_T         0x0C    // ->  Temperature output
#define INFO1         0x0D   // ->  Information register 1
#define INFO2         0x0E  // ->  Information register 2
#define WHO_AM_I      0x0F // ->  Who I am ID

#define OFF_X         0x10   // -> X-axis offset correction
#define OFF_Y         0x11  // -> Y-axis offset correction
#define OFF_Z         0x12 // -> z-axis offset correction

#define CS_X          0x13   // -> Constant shift X
#define CS_Y          0x14  // -> Constant shift Y
#define CS_Z          0x15 // -> Constant shift Z

// Long counter registers
#define LC_L          0x16
#define LC_H          0x17

#define STAT          0x18   // ->  Interrupt synchronization
#define PEAK1         0x19  // ->  Peak value
#define PEAK2         0x1A // -> Peak value

#define VFC_1         0x1B     // -> Vector filter coefficient 1
#define VFC_2         0x1C    // -> Vector filter coefficient 2
#define VFC_3         0x1D   // -> Vector filter coefficient 3
#define VFC_4         0x1E  // -> Vector filter coefficient 4
#define THRS3         0x1F // -> Threshold value 3

#define CTRL_REG4     0x20   // -> Control register
#define CTRL_REG1     0x21  // -> SM1 control register
#define CTRL_REG2     0x22 // -> SM2 control register

// Control registers
#define CTRL_REG3     0x23
#define CTRL_REG5     0x24
#define CTRL_REG6     0x25

#define STATUS        0x27 // -> Status Data Register

// Output Registers
#define OUT_X_L       0x28
#define OUT_X_H       0x29
#define OUT_Y_L       0x2A
#define OUT_Y_H       0x2B
#define OUT_Z_L       0x2C
#define OUT_Z_H       0x2D

// FIFO registers
#define FIFO_CTRL     0x2E
#define FIFO_SRC      0x2F

// SM1 coderegisters (x= 1-16)
// define -> ST1_x
#define ST1_X_L      0x40
#define ST1_X_H      0x4F

// SM1 general timer
#define TIM4_1       0x50
#define TIM3_1       0x51
#define TIM2_1_L     0x52
#define TIM2_1_H     0x53
#define TIM1_1_L     0x54
#define TIM1_1_H     0x55

#define THRS2_1      0x56    // -> SM1 threshold value 1
#define THRS1_1      0x57   // -> SM1 threshold value 2
#define MASK1_B      0x59  // -> SM1 axis and sign mask
#define MASK1_A      0x5A // -> SM1 axis and sign mask

#define SETT1        0x5B  // -> SM1 detection settings
#define PR1          0x5C // ->  Program-reset pointer

// Timer Counter
#define TC1_L        0x5D
#define TC1_H        0x5E

#define OUTS1        0x5F // -> Main set flag

// SM2 coderegisters (x= 1-16)
// define -> ST2_x
#define ST2_X_L      0x60
#define ST2_X_H      0x6F

// SM2 general timer
#define TIM4_2       0x70
#define TIM3_2       0x71
#define TIM2_2_L     0x72
#define TIM2_2_H     0x73
#define TIM1_2_L     0x74
#define TIM1_2_H     0x75

#define THRS2_2      0x76   // -> SM2 threshold value 1
#define THRS1_2      0x77  // -> SM2 threshold value 2

#define DES2         0x78  // ->  Decimation factor

#define MASK2_B      0x79     // ->  SM2 axis and sign mask
#define MASK2_A      0x7A    // ->  SM2 axis and sign mask
#define SETT2        0x7B   // ->  SM2 detection settings
#define PR2          0x7C  // -> Program-reset pointer

// Timer counter
#define TC2_L        0x7D
#define TC2_H        0x7E

#define OUTS2        0x72 // -> Main set flag



// Axis enable
#define LIS3DSH_Select_X_Axis     0x01
#define LIS3DSH_Select_Y_Axis     0x02
#define LIS3DSH_Select_Z_Axis     0x04
#define LIS3DSH_Select_XY_Axis    0x03
#define LIS3DSH_Select_XZ_Axis    0x05
#define LIS3DSH_Select_YZ_Axis    0x06
#define LIS3DSH_Select_XYZ_Axis   0x07

// BDU bit
#define LIS3DSH_BDU_data_continue   0
#define LIS3DSH_BDU_data_stop       1

// ODR Configuration
#define LIS3DSH_ODR_PowerDown     0x00    // Power Down mode
#define LIS3DSH_ODR_3_125_HZ      0x01    // 3.125 Hz Mode
#define LIS3DSH_ODR_6_25_HZ       0x02    // 6.25 Hz  Mode
#define LIS3DSH_ODR_12_5_HZ       0x03    // 12.5 Hz Mode
#define LIS3DSH_ODR_25_HZ         0x04    // 25 Hz Mode
#define LIS3DSH_ODR_50_HZ         0x05    // 50 Hz Mode
#define LIS3DSH_ODR_100_HZ        0x06    // 100 Hz Mode
#define LIS3DSH_ODR_400_HZ        0x07    // 400 Hz Mode
#define LIS3DSH_ODR_800_HZ        0x08    // 800 Hz Mode
#define LIS3DSH_ODR_1600_HZ       0x09    // 1600 Hz Mode

// BW  Anti-aliasing filter bandwidth
#define LIS3DSH_BW_800_HZ         0x00    // 800 Hz
#define LIS3DSH_BW_200_HZ         0x01    // 200 Hz
#define LIS3DSH_BW_400_HZ         0x02    // 400 Hz
#define LIS3DSH_BW_50_HZ          0x04    // 50  Hz

//  Full-scale selection
#define LIS3DSH_FULLSCALE_2       0x00    // 2  g
#define LIS3DSH_FULLSCALE_4       0x01    // 4  g
#define LIS3DSH_FULLSCALE_6       0x02    // 6  g
#define LIS3DSH_FULLSCALE_8       0x03    // 8  g
#define LIS3DSH_FULLSCALE_16      0x04    // 16 g



typedef struct {
	uint8_t SelectAxes;
	uint8_t OdrConfig;
	uint8_t  BDU_select;
	uint8_t FullScale;
	uint8_t bandwidth;
}LIS3DSH_InitTypeDef;


typedef struct
{
	int16_t x;
	int16_t y;
	int16_t z;
}LIS3DSH_DataRaw;



uint8_t LIS3DSH_Read(uint8_t reg,uint8_t size);

uint8_t read_INFO1();

uint8_t read_INFO2();

uint8_t read_who_am_i();

int8_t  read_temperature();

uint8_t read_status();

int LIS3DSH_Init(SPI_HandleTypeDef *mySPI,LIS3DSH_InitTypeDef *SensorInitDef);

LIS3DSH_DataRaw LIS3DSH_GetDataRaw(void);

uint8_t read_stat();

void motion_detection();

void LIS3DSH_FIFO_Init();



void offset_x(uint8_t offsetVal);
void offset_y(uint8_t offsetVal);
void offset_z(uint8_t offsetVal);

void shiftAxis_x(uint8_t shiftVal);
void shiftAxis_y(uint8_t shiftVal);
void shiftAxis_z(uint8_t shiftVal);



void LIS3DSH_Sleep();
void LIS3DSH_Unsleep(LIS3DSH_InitTypeDef *SensorInitDef);

void send_accelerometer_data(int16_t x, int16_t y, int16_t z, UART_HandleTypeDef *myUart);

LIS3DSH_DataRaw ReadFIFOData(LIS3DSH_InitTypeDef *mySensor,UART_HandleTypeDef *myUart);

#endif /* INC_LIS3DSH_H_ */
