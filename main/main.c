/*start of main.c-------------------------------------------------------------------------------------*/
/* 
 * Included Modules 
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

/*
 * Local Constants 
 */
static const char *TAG = "RTOS_TEST";
static const TickType_t S_DELAY = pdMS_TO_TICKS(1000); 

/* 
 * Local Variables 
*/
TaskHandle_t xTask1Handle = NULL;
TaskHandle_t xTask2Handle = NULL;
TaskHandle_t xTask3Handle = NULL;

/* 
 * Private Function Prototypes 
 */
static void vTask1(void *pvParameters);
static void vTask2(void *pvParameters);
static void vTask3(void *pvParameters);


/*
* Local Define
*/
//shorthand macro
#define LOGI(...) ESP_LOGI(TAG, __VA_ARGS__)
#define LOGD(...) ESP_LOGD(TAG, __VA_ARGS__)
#define LOGW(...) ESP_LOGW(TAG, __VA_ARGS__)
#define LOGE(...) ESP_LOGE(TAG, __VA_ARGS__)

void app_main(void)
{
    BaseType_t result;
    LOGI("\r\n\r\n\r\n");
    LOGI("-----Start of the program-----");
    LOGI("Initializing FreeRTOS test....");

    result = xTaskCreate(vTask1, "Task_1", 2048, NULL, 5, &xTask1Handle);
    configASSERT((pdPASS == result) && (NULL != xTask1Handle));

    result = xTaskCreate(vTask2, "Task_2", 2048, NULL, 5, &xTask2Handle);
    configASSERT((pdPASS == result) && (NULL != xTask2Handle));

    result = xTaskCreate(vTask3, "Task_3", 2048, NULL, 5, &xTask3Handle);
    configASSERT((pdPASS == result) && (NULL != xTask3Handle));

    LOGI("Starting FreeRTOS test....");
    xTaskNotifyGive(xTask1Handle);

}


/* 
 * Private Functions 
 */
static void vTask1(void *pvParameters)
{
    for(;;)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        
        LOGI("Task #1 is executing...");

        vTaskDelay(S_DELAY); //delay between task
        
        xTaskNotifyGive(xTask2Handle);
    }
}

static void vTask2(void *pvParameters)
{
    for(;;)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        
        LOGI("Task #2 is executing...");

        vTaskDelay(S_DELAY); //delay between task
        
        xTaskNotifyGive(xTask3Handle);        
    }
}

static void vTask3(void *pvParameters)
{
    for(;;)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        
        LOGI("Task #3 is executing...\r\n--Task Complete--\r\n");

        vTaskDelay(S_DELAY); //delay between task
        
        xTaskNotifyGive(xTask1Handle);          
    }
}
/*end of main.c-------------------------------------------------------------------------------------*/