#include "stm32f4xx_hal.h" // Include the HAL library

GPIO_InitTypeDef GPIO_InitStruct; // Define a GPIO_InitTypeDef structure

void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE(); // Enable the clock for GPIOA

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); // Set the output level of pin PA5 to HIGH

    /*Configure GPIO pin : PA5 */
    GPIO_InitStruct.Pin = GPIO_PIN_5; // We are configuring pin PA5
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Set the mode as output
    GPIO_InitStruct.Pull = GPIO_NOPULL; // No pull-up or pull-down resistor
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // Set the speed as low
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); // Initialize GPIOA with the settings stored in GPIO_InitStruct

    /*Configure GPIO pin : PA6 */
    GPIO_InitStruct.Pin = GPIO_PIN_6; // We are configuring pin PA6
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT; // Set the mode as input
    GPIO_InitStruct.Pull = GPIO_PULLUP; // Pull-up resistor
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM; // Set the speed as medium
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); // Initialize GPIOA with the settings stored in GPIO_InitStruct

    /*Configure GPIO pin : PA7 */
    GPIO_InitStruct.Pin = GPIO_PIN_7; // We are configuring pin PA7
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Set the mode as output
    GPIO_InitStruct.Pull = GPIO_PULLDOWN; // Pull-down resistor
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // Set the speed as high
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); // Initialize GPIOA with the settings stored in GPIO_InitStruct

    /*Configure GPIO pin : PA8 */
    GPIO_InitStruct.Pin = GPIO_PIN_8; // We are configuring pin PA8
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT; // Set the mode as input
    GPIO_InitStruct.Pull = GPIO_NOPULL; // No pull-up or pull-down resistor
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH; // Set the speed as very high
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); // Initialize GPIOA with the settings stored in GPIO_InitStruct

}

GPIO_PinState PinState_PA6;
GPIO_PinState PinState_PA8;

void Read_Input_Pins(void)
{
    PinState_PA6 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
    PinState_PA8 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8);

    if(PinState_PA6 == GPIO_PIN_SET)
    {
        // If pin PA6 is HIGH, do something here
    }

    if(PinState_PA8 == GPIO_PIN_SET)
    {
        // If pin PA8 is HIGH, do something here
    }
}

// GPIO_InitStruct.Pin: This field is used to select the GPIO pin to be configured. 
// You can select any combination of GPIO pins with a bitwise OR of the selected GPIO pins.  (GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;)
// Each pin number is represented by a bit in the binary format. The possible values are:
// GPIO_PIN_x
// GPIO_PIN_All

// GPIO_InitStruct.Mode: This field is used to select the operating mode for the selected pins. 
// GPIO_MODE_INPUT: Input Mode
// GPIO_MODE_OUTPUT_PP: General Purpose Output Mode
// GPIO_MODE_OUTPUT_OD: Output Open Drain Mode

// GPIO_InitStruct.Pull: This field is used to select the Pull-up/Pull-down activation for the selected pins. 
// GPIO_NOPULL: No Pull-up or Pull-down activation
// GPIO_PULLUP: Pull-up activation
// GPIO_PULLDOWN: Pull-down activation

// GPIO_InitStruct.Speed: This field is used to select the speed for the selected pins. 
// GPIO_SPEED_FREQ_LOW: Low speed
// GPIO_SPEED_FREQ_MEDIUM: Medium speed
// GPIO_SPEED_FREQ_HIGH: High speed
// GPIO_SPEED_FREQ_VERY_HIGH: Very high speed


// FUNCTION

#include "stm32f4xx_hal.h" // Include the HAL library

void Configure_Pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t Mode, uint32_t Pull, uint32_t Speed)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /*Configure GPIO pin */
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = Mode;
    GPIO_InitStruct.Pull = Pull;
    GPIO_InitStruct.Speed = Speed;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);

    /* Error handling */
    if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) != GPIO_PIN_RESET)
    {
        Error_Handler();
    }
}

void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE(); // Enable the clock for GPIOA

    /*Configure GPIO pins */
    Configure_Pin(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW);
    Configure_Pin(GPIOA, GPIO_PIN_6, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_MEDIUM);
    Configure_Pin(GPIOA, GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_PULLDOWN, GPIO_SPEED_FREQ_HIGH);
    Configure_Pin(GPIOA, GPIO_PIN_8, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH);

    /* Set the output level of pin PA5 to HIGH */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	GPIO_PinState PinState_PA6 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
}

void Error_Handler(void)
{
    /* User can add his own implementation to report the HAL error return state */
    while(1)
    {
        // Error handling code goes here
    }
}
