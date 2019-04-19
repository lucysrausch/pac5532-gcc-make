;/*****************************************************************************
; * @file:    startup_pac55xx_keil.s
; * @purpose: CMSIS Cortex-M4 Core Device Startup File for the 
; *           PAC55XX Device Family
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


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000300

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp
                EXPORT  __initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp                ; Top of Stack
                DCD     Reset_Handler               ; Reset Handler
                DCD     NMI_Handler                 ; NMI Handler
                DCD     HardFault_Handler           ; Hard Fault Handler
                DCD     MemManageFault_Handler      ; Mem Manage Fault Handler
                DCD     BusFault_Handler		    ; Bus Fault Handler
                DCD     UsageFault_Handler		    ; Usage Fault Handler
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     SVC_Handler                 ; SVCall Handler
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     PendSV_Handler              ; PendSV Handler
                DCD     SysTick_Handler             ; SysTick Handler

                ; External Interrupts
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
					
                IF      :LNOT::DEF:NO_CRP
                AREA    |.ARM.__at_0x02FC|, CODE, READONLY
CRP_Key         DCD     0xFFFFFFFF
                ENDIF


                AREA    |.text|, CODE, READONLY
; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler               [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)                

NMI_Handler     PROC
                EXPORT  NMI_Handler                 [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler           [WEAK]
                B       .
                ENDP
MemManageFault_Handler\
                PROC
                EXPORT  MemManageFault_Handler      [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler            [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler          [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                 [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler            [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler              [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler             [WEAK]
                B       .
                ENDP

Default_Handler PROC
				EXPORT  Default_Handler             [WEAK]
				EXPORT  MemCtl_IRQHandler           [WEAK]
				EXPORT  Wdt_IRQHandler        	    [WEAK]
				EXPORT  RTC_IRQHandler              [WEAK]
				EXPORT  ADC_IRQHandler              [WEAK]
				EXPORT  ADC1_IRQHandler             [WEAK]
				EXPORT  ADC2_IRQHandler             [WEAK]
				EXPORT  ADC3_IRQHandler             [WEAK]
				EXPORT  TimerA_IRQHandler           [WEAK]
				EXPORT  TimerB_IRQHandler           [WEAK]
				EXPORT  TimerC_IRQHandler           [WEAK]
				EXPORT  TimerD_IRQHandler           [WEAK]
				EXPORT  QEPA_IRQHandler             [WEAK]
				EXPORT  QEPB_IRQHandler             [WEAK]
				EXPORT  QEPC_IRQHandler             [WEAK]
				EXPORT  QEPD_IRQHandler             [WEAK]
				EXPORT  GpioA_IRQHandler            [WEAK]
				EXPORT  GpioB_IRQHandler            [WEAK]
				EXPORT  GpioC_IRQHandler            [WEAK]
				EXPORT  GpioD_IRQHandler            [WEAK]
				EXPORT  GpioE_IRQHandler            [WEAK]
				EXPORT  GpioF_IRQHandler            [WEAK]
				EXPORT  GpioG_IRQHandler            [WEAK]
				EXPORT  I2C_IRQHandler              [WEAK]
				EXPORT  USARTA_IRQHandler           [WEAK]
				EXPORT  USARTB_IRQHandler           [WEAK]
				EXPORT  USARTC_IRQHandler           [WEAK]
				EXPORT  USARTD_IRQHandler           [WEAK]
				EXPORT  CAN_IRQHandler              [WEAK]
				EXPORT  GPTimerA_IRQHandler         [WEAK]
				EXPORT  GPTimerB_IRQHandler         [WEAK]
				EXPORT  CCS_IRQHandler              [WEAK]
MemCtl_IRQHandler
Wdt_IRQHandler
RTC_IRQHandler
ADC_IRQHandler
ADC1_IRQHandler
ADC2_IRQHandler
ADC3_IRQHandler
TimerA_IRQHandler
TimerB_IRQHandler
TimerC_IRQHandler
TimerD_IRQHandler
QEPA_IRQHandler
QEPB_IRQHandler
QEPC_IRQHandler
QEPD_IRQHandler
GpioA_IRQHandler
GpioB_IRQHandler
GpioC_IRQHandler
GpioD_IRQHandler
GpioE_IRQHandler
GpioF_IRQHandler
GpioG_IRQHandler
I2C_IRQHandler
USARTA_IRQHandler
USARTB_IRQHandler
USARTC_IRQHandler
USARTD_IRQHandler
CAN_IRQHandler
GPTimerA_IRQHandler
GPTimerB_IRQHandler
CCS_IRQHandler
                B       .
                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB
                
                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit
                
                ELSE
                
                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, = (Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem + Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
