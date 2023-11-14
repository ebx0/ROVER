// Enable clock for GPIOA
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

// Set mode = 01 (output mode) for pins PA0 and PA1
GPIOA->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1); // Reset bits
GPIOA->MODER |= (GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0); // Set bits

// Set mode = 00 (input mode) for pin PA2
GPIOA->MODER &= ~GPIO_MODER_MODER2; // Reset bits

// Set mode = 00 (input mode) for pins PA3 to PA15
GPIOA->MODER &= 0x00000007; // Reset bits



// Set PA0 to 0 and PA1 to 1
GPIOA->ODR &= ~GPIO_ODR_ODR_0; // Reset bit
GPIOA->ODR |= GPIO_ODR_ODR_1; // Set bit

// Set PA0 to 0 and PA1 to 1 (No constant)
GPIOA->ODR &= ~(1 << 0); // Reset bit
GPIOA->ODR |= (1 << 1); // Set bit

// Set PA0 to 0 and PA1 to 1 (HEX
GPIOA->ODR &= ~0x0001; // Reset bit
GPIOA->ODR |= 0x0002; // Set bit

// Set PA0 to 0 and PA1 to 1 using BSRR
GPIOA->BSRR = GPIO_BSRR_BR_0 | GPIO_BSRR_BS_1;

// Set PA0 to 0 and PA1 to 1 using BSRR (No constant)
GPIOA->BSRR = (1 << 16) | (1 << 1);

// Set PA0 to 0 and PA1 to 1 using BSRR (HEX)
GPIOA->BSRR = 0x00020001;


//LOCKING
// Lock PA0 and PA1
GPIOA->LCKR = GPIO_LCKR_LCK0 | GPIO_LCKR_LCK1 | GPIO_LCKR_LCKK;
GPIOA->LCKR = GPIO_LCKR_LCK0 | GPIO_LCKR_LCK1;
GPIOA->LCKR = GPIO_LCKR_LCK0 | GPIO_LCKR_LCK1 | GPIO_LCKR_LCKK;
(void)GPIOA->LCKR;
// Lock PA0 and PA1 (No constant)
GPIOA->LCKR = (1 << 16) | (1 << 0) | (1 << 1); // Set LCKK, LCK0 and LCK1
GPIOA->LCKR = (0 << 16) | (1 << 0) | (1 << 1); // Set LCK0 and LCK1
GPIOA->LCKR = (1 << 16) | (1 << 0) | (1 << 1); // Set LCKK, LCK0 and LCK1
(void)GPIOA->LCKR; // Dummy read to ensure the lock is active


// Check if PA2 is 1 or 0
if(GPIOA->IDR & GPIO_IDR_IDR_2)
{
    // PA2 is 1, do something
}
else
{
    // PA2 is 0, do something else
}

// Check if any of PA3 to PA15 are high
if(GPIOA->IDR & 0xFFFFFFF8)
{
    // At least one of PA3 to PA15 is high, do something
}



// EXAMPLES (OUTPUT REGISTERS)

// Enable GPIOA clock
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
RCC->AHB1ENR |= 1;

// Set the PIN PA5 as output
GPIOA->MODER &= ~(GPIO_MODER_MODER5); // Reset bits
GPIOA->MODER |= GPIO_MODER_MODER5_0; // Set bits for output mode
GPIOA->MODER &= ~0x00000C00; // Reset bits
GPIOA->MODER |= 0x00000400; // Set bits for output mode

// Configure the output type
GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_5); // Reset bits
GPIOA->OTYPER |= 0; // Set bits for push-pull output type
GPIOA->OTYPER &= ~0x20; // Reset bits
GPIOA->OTYPER |= 0x00; // Set bits for push-pull output type

// Configure the output speed
GPIOA->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR5); // Reset bits
GPIOA->OSPEEDR &= ~0x00000C00; // Reset bits

// Low speed
GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_0; // Set bits for low speed
GPIOA->OSPEEDR |= 0x00000400; // Set bits for low speed
// Medium speed
GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_1; // Set bits for medium speed
GPIOA->OSPEEDR |= 0x00000800; // Set bits for medium speed
// High speed
GPIOA->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR5_0 | GPIO_OSPEEDER_OSPEEDR5_1); // Set bits for high speed
GPIOA->OSPEEDR |= 0x00000C00; // Set bits for high speed

// Configure the pull-up/pull-down resistors
GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR5); // Reset bits
GPIOA->PUPDR |= GPIO_PUPDR_PUPDR5_0; // Set bits for pull-up
GPIOA->PUPDR &= ~0x00000C00; // Reset bits
GPIOA->PUPDR |= 0x00000400; // Set bits for pull-up

