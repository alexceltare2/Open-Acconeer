From preliminary test, it seems Acconeer sends a 2 byte word from Master and reads 4 bytes from Slave. A list of commands, concrete data frame and description is not available. So far only 0x3000 is used to identify the sensor which responds with a 0x00001112. Tests were conducted via sniffing the SPI bus. ENABLE pin needs to be HIGH all the time to drive the sensor.