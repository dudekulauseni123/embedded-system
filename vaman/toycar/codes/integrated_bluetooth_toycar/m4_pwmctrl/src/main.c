/*==========================================================
Code by G V V Sharma
March 7, 2021,
Released under GNU/GPL
https://www.gnu.org/licenses/gpl-3.0.en.html
/*==========================================================
 *
 *    File   : main.c
 *    Purpose: main for Pygmy blink onboard led
 *                                                          
 *=========================================================*/

#include "Fw_global_config.h"   // This defines application specific charactersitics

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"
#include "RtosTask.h"

/*    Include the generic headers required for QORC */
#include "eoss3_hal_gpio.h"
#include "eoss3_hal_rtc.h"
#include "eoss3_hal_timer.h"
#include "eoss3_hal_fpga_usbserial.h"
#include "ql_time.h"
#include "s3x_clock_hal.h"
#include "s3x_clock.h"
#include "s3x_pi.h"
#include "dbg_uart.h"

#include "hal_fpga_onion.h"
#include "hal_fpga_onion_pwmctrl.h"

#include "cli.h"


extern const struct cli_cmd_entry my_main_menu[];


const char *SOFTWARE_VERSION_STR;
extern void qf_hardwareSetup();
static void nvic_init(void);
typedef struct{
uint8_t shape_buttom_status[4];
//int16_t pwm_value[4]
}dabble_joystick_t;

void sevenseg(int a,int b,int c,int d,int e,int f,int g)
{
  digitalWrite(32, a); 
  digitalWrite(33, b); 
  digitalWrite(25, c); 
  digitalWrite(26, d); 
  digitalWrite(27, e); 
  digitalWrite(14, f);     
  digitalWrite(12, g); 
}
void _setup() 
{
   Serial.begin(115200);

    pinMode(32, OUTPUT);  
    pinMode(33, OUTPUT);
    pinMode(25, OUTPUT);
    pinMode(26, OUTPUT);
    pinMode(27, OUTPUT);
    pinMode(14, OUTPUT);
    pinMode(12, OUTPUT);            
      Dabble.begin("Esp32");

}
int main(void)
{
    uint32_t i=0,j=0,k=0;
    //volatile dabble_joystick_t joystick_data;  
    //uint8_t* init_ptr = (uint8_t*)&joystick_data;
    //int16_t* pwm_value = (int16_t*)&joystick_data.pwm_value;
	
    // Data initialization
    for(i=0; i<sizeof(joystick_data); i++) init_ptr[i] = 0;

    SOFTWARE_VERSION_STR = "qorc-onion-apps/qf_hello-fpga-gpio-ctlr";
    
    qf_hardwareSetup();
    nvic_init();

    S3x_Clk_Enable(S3X_M4_S12_S15_CLK);

    dbg_str("\n\n");
    dbg_str( "##########################\n");
    dbg_str( "Quicklogic QuickFeather FPGA GPIO CONTROLLER EXAMPLE\n");
    dbg_str( "SW Version: ");
    dbg_str( SOFTWARE_VERSION_STR );
    dbg_str( "\n" );
    dbg_str( __DATE__ " " __TIME__ "\n" );
    dbg_str( "##########################\n\n");

    dbg_str( "\n\nHello GPIO!!\n\n");	// <<<<<<<<<<<<<<<<<<<<<  Change me!

    CLI_start_task( my_main_menu );
	HAL_Delay_Init();

    // Write to mailbox, memory address of joystick data
    MISC_CTRL->SW_MB_1 = (uint32_t)&joystick_data;

    while(1)
    {
        if(joystick_data.shape_button_status[0]){
		//if(joystick_data.pwm_value[0] < 0){
			Serial.println("0");
                       sevenseg(0,0,0,0,0,0,1);	
		}
         else if(joystick_data.shape_button_status[1]){
		//if(joystick_data.pwm_value[0] < 0){
			Serial.println("1");
                       sevenseg(1,0,0,1,1,1,1);	
		}
         else if(joystick_data.shape_button_status[2]){
		//if(joystick_data.pwm_value[0] < 0){
			Serial.println("2");
                       sevenseg(0,0,1,0,0,1,0);	
		}
		 else if(joystick_data.shape_button_status[3]){
		//if(joystick_data.pwm_value[0] < 0){
			 Serial.println("3");
                sevenseg(0,0,0,0,1,1,0);	
		}				
		else if(joystick_data.shape_button_status[4]){
		//if(joystick_data.pwm_value[0] < 0){
			 Serial.println("4");
                sevenseg(1,0,0,1,1,0,0);	
		}
	else{
		sevenseg(1,1,1,1,1,1,1);	
	}
    }
    /* Start the tasks and timer running. */
    vTaskStartScheduler();
    dbg_str("\n");

    while(1);
}

static void nvic_init(void)
 {
    // To initialize system, this interrupt should be triggered at main.
    // So, we will set its priority just before calling vTaskStartScheduler(), not the time of enabling each irq.
    NVIC_SetPriority(Ffe0_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(SpiMs_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(CfgDma_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(Uart_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(FbMsg_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
 }    

//needed for startup_EOSS3b.s asm file
void SystemInit(void)
{

}
