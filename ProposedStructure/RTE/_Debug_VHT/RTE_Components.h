
/*
 * Auto generated Run-Time-Environment Configuration File
 *      *** Do not modify ! ***
 *
 * Project: 'AWS_MQTT_Proposed.Debug+VHT' 
 * Target:  'Debug+VHT' 
 */

#ifndef RTE_COMPONENTS_H
#define RTE_COMPONENTS_H


/*
 * Define the Device Header File: 
 */
#define CMSIS_device_header "CMSDK_CM7_DP.h"

/* ARM.FreeRTOS::RTOS:Config:CMSIS RTOS2:10.4.6 */
#define RTE_RTOS_FreeRTOS_CONFIG_RTOS2  /* RTOS FreeRTOS Config for CMSIS RTOS2 API */
/* ARM.FreeRTOS::RTOS:Core:Cortex-M:10.4.6 */
#define RTE_RTOS_FreeRTOS_CORE          /* RTOS FreeRTOS Core */
/* ARM.FreeRTOS::RTOS:Event Groups:10.4.6 */
#define RTE_RTOS_FreeRTOS_EVENTGROUPS   /* RTOS FreeRTOS Event Groups */
/* ARM.FreeRTOS::RTOS:Heap:Heap_5:10.4.6 */
#define RTE_RTOS_FreeRTOS_HEAP_5        /* RTOS FreeRTOS Heap 5 */
/* ARM.FreeRTOS::RTOS:Stream Buffer:10.4.6 */
#define RTE_RTOS_FreeRTOS_STREAM_BUFFER /* RTOS FreeRTOS Stream Buffers */
/* ARM.FreeRTOS::RTOS:Timers:10.4.6 */
#define RTE_RTOS_FreeRTOS_TIMERS        /* RTOS FreeRTOS Timers */
/* ARM::CMSIS:RTOS2:FreeRTOS:Cortex-M:10.4.6 */
#define RTE_CMSIS_RTOS2                 /* CMSIS-RTOS2 */
        #define RTE_CMSIS_RTOS2_FreeRTOS        /* CMSIS-RTOS2 FreeRTOS */
/* ARM::Security:mbed TLS:2.24.0 */
#define RTE_Security_mbedTLS            /* Security mbed TLS */
/* Keil.ARM Compiler::Compiler:Event Recorder:DAP:1.4.0 */
#define RTE_Compiler_EventRecorder
          #define RTE_Compiler_EventRecorder_DAP
/* Keil.ARM Compiler::Compiler:I/O:STDERR:User:1.2.0 */
#define RTE_Compiler_IO_STDERR          /* Compiler I/O: STDERR */
          #define RTE_Compiler_IO_STDERR_User     /* Compiler I/O: STDERR User */
/* Keil.ARM Compiler::Compiler:I/O:STDIN:User:1.2.0 */
#define RTE_Compiler_IO_STDIN           /* Compiler I/O: STDIN */
          #define RTE_Compiler_IO_STDIN_User      /* Compiler I/O: STDIN User */
/* Keil.ARM Compiler::Compiler:I/O:STDOUT:User:1.2.0 */
#define RTE_Compiler_IO_STDOUT          /* Compiler I/O: STDOUT */
          #define RTE_Compiler_IO_STDOUT_User     /* Compiler I/O: STDOUT User */
/* Keil::CMSIS Driver:USART:1.0.3 */
#define RTE_Drivers_USART
/* MDK-Packs::IoT Utility:Socket:Custom:1.0.0 */
#define RTE_IoT_Socket                  /* IoT Socket */


#endif /* RTE_COMPONENTS_H */
