# LIS3DSH STM32F4Discovery

Data can be received from the sensor in two different modes:

1- Normal Mode
2- FIFO Mode

In Normal Mode, data is received from the x, y and z axes at intervals determined by the selected initial (init) values.

In FIFO Mode, the sensor is operated for a short time, during this time the FIFO buffer is filled and the process is carried out in this way.

# IOC Settings

Configured to spi1 full duplex and dma mode

![image](https://github.com/user-attachments/assets/32e013a9-f4ee-4449-aaae-8dc96e37db3c)

Then opened CS pin (Output) and Interrupt pin (E0)

![image](https://github.com/user-attachments/assets/e313f591-d685-4bd1-8230-d2ca8f7bfc5f)

If data will be sent from uart, uart can be opened

# Code 

Necessary structure definitions are made

```bash
/* USER CODE BEGIN 0 */
LIS3DSH_InitTypeDef mySensor;
LIS3DSH_DataRaw DataRaw;
/* USER CODE END 0 */
```

than added init

```bash
  /* USER CODE BEGIN 2 */
  mySensor.SelectAxes = LIS3DSH_Select_XYZ_Axis;
  mySensor.BDU_select = LIS3DSH_BDU_data_continue;
  mySensor.OdrConfig  = LIS3DSH_ODR_1600_HZ;
  mySensor.FullScale  = LIS3DSH_FULLSCALE_16;
  mySensor.bandwidth  = LIS3DSH_BW_400_HZ;
  LIS3DSH_Init(&hspi1,&mySensor);
  /* USER CODE END 2 */
```

# Modes

1- Normal Mode
```bash
 DataRaw = LIS3DSH_GetDataRaw();
```

2- FIFO Mode
```bash
HAL_Delay(750);
DataRaw = ReadFIFOData(&mySensor,&huart2);
```

# Result

![image](https://github.com/user-attachments/assets/81b18ece-fd4f-4561-924f-6755ae77f1e0)

