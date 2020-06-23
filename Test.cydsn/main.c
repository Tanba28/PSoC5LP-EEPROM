/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "stdio.h"


void USBUART_Start_Wrapper(){
    USBUART_Start(0, USBUART_DWR_VDDD_OPERATION);
    //500ms TimeOut
    for(uint8_t i=0;i<100;i++){
        if(0u != USBUART_bGetConfiguration()){
            USBUART_CDC_Init(); 
            break;
        } 
        CyDelay(5);
    }
}
void USBUART_Connection_Check(){
    if(0u != USBUART_IsConfigurationChanged()){
        if(0u != USBUART_GetConfiguration()){
            USBUART_CDC_Init();
        }
    }
}

void USBUART_PutString_Wrapper(const char8 string[]){
    if(0u != USBUART_GetConfiguration()){
        USBUART_PutString(string);
    }
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    uint8_t buf[16];
    char debug[64];
    uint16_t count = 0;
    
    USBUART_Start_Wrapper();
    
    EEPROM_Start();
    
    for(;;)
    {
        /* Place your application code here. */
        USBUART_Connection_Check();
        
        buf[count] = EEPROM_ReadByte(count);
        
        sprintf(debug,"%d %x\r\n",count,buf[count]);
        USBUART_PutString_Wrapper(debug);
        
        if(count == 16){
            count = 0;
        }
        
        count++;
        

        CyDelay(1000);
    }
}

/* [] END OF FILE */
