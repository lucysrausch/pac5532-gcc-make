;/*****************************************************************************
; * @file:    startup_pac55xx_iar.s
; * @purpose: CMSIS Cortex-M4 Core Device Startup File for PAC55XX Devices
; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------
; *
; * Copyright (C) 2017, Active-Semi International
; *
; * THIS SOFTWARE IS SUBJECT TO A SOURCE CODE LICENSE AGREEMENT WHICH PROVIDES, 
; * AMONG OTHER THINGS:  (i) THAT IT CAN BE USED ONLY TO ADAPT THE LICENSEE'S 
; * APPLICATION TO PAC PROCESSORS SUPPLIED BY ACTIVE-SEMI INTERNATIONAL; 
; * (ii) THAT  IT IS PROVIDED "AS IS" WITHOUT WARRANTY;  (iii) THAT 
; * ACTIVE-SEMICONDUCTOR IS NOT LIABLE FOR ANY INDIRECT DAMAGES OR FOR DIRECT
; * DAMAGES EXCEEDING US$1,500;  AND (iv) THAT IT CAN BE DISCLOSED TO AND USED
; * ONLY BY CERTAIN AUTHORIZED PERSONS. 
; *
; *****************************************************************************/


;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start

        PUBLIC  __vector_table
        PUBLIC  __vector_table_0x1c
        DATA
__iar_init$$done:               ; This vector table is not needed until after copy initialization is done
__vector_table
        DCD     sfe(CSTACK)                 ; Top of Stack
        DCD     Reset_Handler         		; Reset Handler
        DCD     NMI_Handler                 ; NMI Handler
        DCD     HardFault_Handler           ; Hard Fault Handler
        DCD     MemManageFault_Handler      ; Mem Manage Fault Handler
        DCD     BusFault_Handler		    ; Bus Fault Handler
        DCD     UsageFault_Handler		    ; Usage Fault Handler
__vector_table_0x1c
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     SVC_Handler                 ; SVCall Handler
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     PendSV_Handler              ; PendSV Handler
        DCD     SysTick_Handler             ; SysTick Handler
        DCD     MemCtl_IRQHandler           ;  0: Memory Controller Handler
        DCD 	Wdt_IRQHandler	            ;  1: Windowed Watchdog Timer Handler
        DCD     RTC_IRQHandler              ;  2: RTC Handler
        DCD     ADC_IRQHandler              ;  3: ADC 0 Handler
        DCD     ADC1_IRQHandler             ;  4: ADC 1 Handler
        DCD     ADC2_IRQHandler             ;  5: ADC 2 Handler
        DCD     ADC3_IRQHandler             ;  6: ADC 3 Handler
        DCD     TimerA_IRQHandler           ;  7: PWM Timer A Handler
        DCD     TimerB_IRQHandler           ;  8: PWM Timer B Handler
        DCD     TimerC_IRQHandler           ;  9: PWM Timer C Handler
        DCD     TimerD_IRQHandler           ; 10: PWM Timer D Handler
        DCD     QEPA_IRQHandler             ; 11: PWM Timer A QEP Handler
        DCD     QEPB_IRQHandler             ; 12: PWM Timer B QEP Handler
        DCD     QEPC_IRQHandler             ; 13: PWM Timer C QEP Handler
        DCD     QEPD_IRQHandler             ; 14: PWM Timer D QEP Handler
        DCD     GpioA_IRQHandler            ; 15: GPIO A Handler
        DCD     GpioB_IRQHandler            ; 16: GPIO B Handler
        DCD     GpioC_IRQHandler            ; 17: GPIO C Handler
        DCD     GpioD_IRQHandler            ; 18: GPIO D Handler
        DCD     GpioE_IRQHandler            ; 19: GPIO E Handler
        DCD     GpioF_IRQHandler            ; 20: GPIO F Handler
        DCD     GpioG_IRQHandler            ; 21: GPIO G Handler
        DCD     I2C_IRQHandler              ; 22: I2C Handler
        DCD     USARTA_IRQHandler           ; 23: UART A Handler
        DCD     USARTB_IRQHandler           ; 24: UART B Handler
        DCD     USARTC_IRQHandler           ; 25: UART C Handler
        DCD     USARTD_IRQHandler           ; 26: UART D Handler
        DCD     CAN_IRQHandler              ; 27: CAN Handler
        DCD     GPTimerA_IRQHandler         ; 28: GP Timer A Handler
        DCD     GPTimerB_IRQHandler         ; 29: GP Timer A Handler
        DCD     CCS_IRQHandler        	    ; 30: Clock Control System Handler

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB
        SECTION .text:CODE:REORDER:NOROOT(1)

        PUBWEAK NMI_Handler
        PUBWEAK HardFault_Handler
        PUBWEAK MemManageFault_Handler
        PUBWEAK BusFault_Handler
        PUBWEAK UsageFault_Handler
        PUBWEAK SVC_Handler
        PUBWEAK DebugMon_Handler
        PUBWEAK PendSV_Handler
        PUBWEAK SysTick_Handler
        PUBWEAK MemCtl_IRQHandler
        PUBWEAK Wdt_IRQHandler
        PUBWEAK RTC_IRQHandler
        PUBWEAK ADC_IRQHandler
        PUBWEAK ADC1_IRQHandler
        PUBWEAK ADC2_IRQHandler
        PUBWEAK ADC3_IRQHandler
        PUBWEAK TimerA_IRQHandler
        PUBWEAK TimerB_IRQHandler
        PUBWEAK TimerC_IRQHandler
        PUBWEAK TimerD_IRQHandler
        PUBWEAK QEPA_IRQHandler
        PUBWEAK QEPB_IRQHandler
        PUBWEAK QEPC_IRQHandler
        PUBWEAK QEPD_IRQHandler
        PUBWEAK GpioA_IRQHandler
        PUBWEAK GpioB_IRQHandler
        PUBWEAK GpioC_IRQHandler
        PUBWEAK GpioD_IRQHandler
        PUBWEAK GpioE_IRQHandler
        PUBWEAK GpioF_IRQHandler
        PUBWEAK GpioG_IRQHandler
        PUBWEAK I2C_IRQHandler
        PUBWEAK USARTA_IRQHandler
        PUBWEAK USARTB_IRQHandler
        PUBWEAK USARTC_IRQHandler
        PUBWEAK USARTD_IRQHandler
        PUBWEAK CAN_IRQHandler
        PUBWEAK GPTimerA_IRQHandler
        PUBWEAK GPTimerB_IRQHandler
        PUBWEAK CCS_IRQHandler
        PUBWEAK Default_Handler

NMI_Handler:
HardFault_Handler:
MemManageFault_Handler:
BusFault_Handler:
UsageFault_Handler:
SVC_Handler:
DebugMon_Handler:
PendSV_Handler:
SysTick_Handler:
MemCtl_IRQHandler:
Wdt_IRQHandler:
RTC_IRQHandler:
ADC_IRQHandler:
ADC1_IRQHandler:
ADC2_IRQHandler:
ADC3_IRQHandler:
TimerA_IRQHandler:
TimerB_IRQHandler:
TimerC_IRQHandler:
TimerD_IRQHandler:
QEPA_IRQHandler:
QEPB_IRQHandler:
QEPC_IRQHandler:
QEPD_IRQHandler:
GpioA_IRQHandler:
GpioB_IRQHandler:
GpioC_IRQHandler:
GpioD_IRQHandler:
GpioE_IRQHandler:
GpioF_IRQHandler:
GpioG_IRQHandler:
I2C_IRQHandler:
USARTA_IRQHandler:
USARTB_IRQHandler:
USARTC_IRQHandler:
USARTD_IRQHandler:
CAN_IRQHandler:
GPTimerA_IRQHandler:
GPTimerB_IRQHandler:
CCS_IRQHandler:
Default_Handler:
        BL Default_Handler

        SECTION .text:CODE:REORDER:NOROOT(2)
        PUBWEAK Reset_Handler
Reset_Handler:
        LDR R0, =__iar_program_start
        BX  R0
        NOP

        END
