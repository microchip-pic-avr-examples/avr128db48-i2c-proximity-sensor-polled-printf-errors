/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
/**
 * I2C_HOST EXAMPLE Generated Driver File
 * 
 * @file i2c_host example.c
 * 
 * @ingroup i2c_host example
 * 
 * @version I2C_HOST EXAMPLE Example Version 1.0.0
 *
 * @brief Generated file for
 *        Example:           4. I2C Proximity Sensor 
 *        Implementation:    Polled 
 *        Visualization:     Printf with error handling   
 *        MCU Device family: AVR
*/
/* ------------------------------------------------------------------

#include "mcc_generated_files/system/system.h"

// Note:  VCNL4200 - High Sensitivity Long Distance Proximity and Ambient Light Sensor With I2C Interface
//        Reference to the VCNL4200 data sheet:  https://www.vishay.com/docs/84430/vcnl4200.pdf
//        The VCNL4200 command codes are located in Table 1 (page 9) of the VCNL4200 data sheet
#define PROXIMITY_I2C_ADDRESS  ((uint8_t)0x51)
#define PROXIMITY_DATA ((uint8_t)0x08)

extern void DELAY_milliseconds(uint16_t milliseconds);  

uint8_t VCNL4200_Initialize(void);
uint8_t VCNL4200_ProximityRead(uint16_t* proximityValue);
const uint8_t* I2CErrorToString(uint8_t error);

uint16_t proximityValue;           // proximity sensor (VCNL4200) result
uint8_t errorState = I2C_ERROR_NONE;

uint8_t VCNL4200_ProximityRead(uint16_t* proximityValue)
{    
    union
    {
        uint8_t  bytes[2]; 
        uint16_t value;
    } proximityResponse;    
    uint8_t proximityData = PROXIMITY_DATA;  
    
    uint8_t waitCounter = 100;
    if (I2C_Host.WriteRead(PROXIMITY_I2C_ADDRESS, &proximityData, sizeof(proximityData), proximityResponse.bytes, sizeof(proximityResponse))) 
    {
        while (I2C_Host.IsBusy() && waitCounter--) 
        {
            I2C_Host.Tasks();
        }
        *proximityValue = proximityResponse.value;
    }
    errorState = I2C_Host.ErrorGet();
      
    // Error states: 
    // 0x00 = I2C_ERROR_NONE
    // 0x01 = I2C_ERROR_ADDR_NACK
    // 0x02 = I2C_ERROR_DATA_NACK
    // 0x03 = I2C_ERROR_BUS_COLLISION 
    return errorState;  
}

const uint8_t* I2CErrorToString(uint8_t error)
{
    switch (error)
    {
        case I2C_ERROR_NONE:
            return "I2C_ERROR_NONE";
        case I2C_ERROR_ADDR_NACK:
            return "I2C_ERROR_ADDR_NACK";
        case I2C_ERROR_DATA_NACK:
            return "I2C_ERROR_DATA_NACK";
        case I2C_ERROR_BUS_COLLISION:
            return "I2C_ERROR_BUS_COLLISION";
        default:
            return "UNKNOWN_ERROR";
    }
}

uint8_t VCNL4200_Initialize(void)
{
    uint8_t initConfigOne[3] = {0x03, 0x2A, 0x0A};
    uint8_t initConfigTwo[3] = {0x03, 0x70, 0x07};
    uint8_t waitCounter = 100;

    if (I2C_Host.Write(PROXIMITY_I2C_ADDRESS, initConfigOne, sizeof(initConfigOne))) 
    {
        while (I2C_Host.IsBusy() && waitCounter--) 
        {
            I2C_Host.Tasks();
        }
    } 
    waitCounter = 100;
    if (I2C_Host.Write(PROXIMITY_I2C_ADDRESS, initConfigTwo, sizeof(initConfigTwo))) 
    {
        while (I2C_Host.IsBusy() && waitCounter--) 
        {
            I2C_Host.Tasks();
        }
    } 
    errorState = I2C_Host.ErrorGet();
    return errorState;  
}

int main(void)
{
    SYSTEM_Initialize();                                                
    errorState = VCNL4200_Initialize();     // Initializes the proximity sensor (VCNL4200) over the I2C bus
    printf("I2C proximity sensor initialize status: %d - %s\r\n", errorState, I2CErrorToString(errorState));
    
    while(1)
    {
        DELAY_milliseconds(250);
        errorState = VCNL4200_ProximityRead(&proximityValue);
        if (errorState != I2C_ERROR_NONE) 
        {
            printf("The proximity sensor error: %d - %s\r\n", errorState, I2CErrorToString(errorState));
        }
        printf("The proximity value is: %d\r\n", proximityValue); 
        IO_LED_Toggle();
        IO_Debug_Toggle();
    }    
}

------------------------------------------------------------------ */
