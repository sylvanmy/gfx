#include "stm32f4xx.h"
#include "demo_app.h"

static volatile uint32_t ticks_ms;
void SysTick_Handler(void){ticks_ms++;}

int main(void)
{
    SystemCoreClockUpdate();
    DemoApp_Init();
    if(SysTick_Config(SystemCoreClock/1000U)!=0U)while(1){}
    while(1)DemoApp_Update(ticks_ms);
}
