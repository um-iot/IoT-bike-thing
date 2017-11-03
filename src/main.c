/*
	Bike Thing

	Sparkfun ESP32-Thing
	https://www.sparkfun.com/products/13907

	Espressif IDF
	https://github.com/espressif/esp-idf

	Unless required by applicable law or agreed to in writing, this
	software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
	CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "./LSM9DS1_accell.c"

xSemaphoreHandle print_mux;

void app_main()
{
	/* Print chip information */
	esp_chip_info_t chip_info;
	esp_chip_info(&chip_info);
	printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
		chip_info.cores,
		(chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
		(chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

	printf("silicon revision %d, ", chip_info.revision);

	printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
		(chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
		print_mux = xSemaphoreCreateMutex();
	xTaskCreate(i2c_task_who_am_i, "i2c_test_task_0", 1024 * 2, (void* ) 0, 10, NULL);
}
