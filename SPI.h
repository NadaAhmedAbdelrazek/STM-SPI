#ifndef SPI_H
#define SPI_H



// Memory addresses of important peripherals
#define GPIOA 0x40020000
#define RCC   0x40023800
#define TIM2  0x40000000
#define SPI1  0x40013000
// GPIO Registers for port A
#define GPIOA_MODER (*(volatile unsigned long*)(GPIOA + 0x00))
#define GPIOA_OTYPER (*(volatile unsigned long*)(GPIOA + 0x04))
#define GPIOA_OSPEEDR (*(volatile unsigned long*)(GPIOA + 0x08))
#define GPIOA_AFRL (*(volatile unsigned long*)(GPIOA + 0x20))
#define GPIOA_BSRR  (*(volatile unsigned long*)(GPIOA + 0x18))
#define GPIOA_PUPDR (*(volatile unsigned long*)(GPIOA + 0x0C))
#define GPIOA_ODR  (*(volatile unsigned long*)(GPIOA + 0x14))
// ... (other GPIO A registers)



// RCC (Reset and Clock Control) Registers
//#define RCC_PLLCFGR (*(volatile unsigned long*)(0x40023800 + 0x04))
#define RCC_CR (*(volatile unsigned long*)(RCC + 0x00))
#define RCC_AHB1ENR (*(volatile unsigned long*)(RCC + 0x30))
#define RCC_APB2ENR (*(volatile unsigned long*)(RCC + 0x44))
#define RCC_APB1ENR  (*(volatile unsigned long*)(RCC + 0x40))
// ... (other RCC registers)

// timer2 registers

#define TIM2_CR1 (*(volatile unsigned long*)(TIM2 + 0x00000000))
#define TIM2_CR2 (*(volatile unsigned long*)(TIM2 + 0x00000004))
#define TIM2_CNT (*(volatile unsigned long*)(TIM2 + 0x00000024))
#define TIM2_PSC (*(volatile unsigned long*)(TIM2 + 0x00000028))
#define TIM2_ARR (*(volatile unsigned long*)(TIM2 + 0x0000002C))
#define TIM2_SR (*(volatile unsigned long*)(TIM2 + 0x00000010))
#define TIM2_EGR (*(volatile unsigned long*)(TIM2 + 0x00000014))
// ... (other TIM2 registers)

// SPI (Serial Peripheral Interface) Registers
#define SPI1_CR1 (*(volatile unsigned long*)(SPI1 + 0x00000000))
#define SPI1_CR2 (*(volatile unsigned long*)(SPI1 + 0x00000004))
#define SPI_SR (*(volatile unsigned long*)(SPI1 + 0x00000008))
#define SPI_DR (*(volatile unsigned long*)(SPI1 + 0x0000000C))
#define SPI_CRCPR (*(volatile unsigned long*)(SPI1 + 0x00000010))
#define SPI_RXCRCR (*(volatile unsigned long*)(SPI1 + 0x00000014))
#define SPI_TXCRCR (*(volatile unsigned long*)(SPI1 + 0x00000018))
// ... (other SPI1 registers)

// // // // // // // // // // // // // // // // // // // // // // // // // // // //

// Definition of macros/functions needed
#define set_bit(reg, bitNumber) ((reg) |= (1U << (bitNumber)))    // macro to set a specified bit
#define clear_bit(reg,bitNumber) (reg&=~(1U<<bitNumber)) //macro to clear a specified bit

  //macros

         #define LSB_FIRST 0
         #define MSB_FIRST 1
         
         #define SPI_SCALER_2 2
         #define SPI_SCALER_4 4
         #define SPI_SCALER_8 8
         #define SPI_SCALER_16 16
         #define SPI_SCALER_32 32
         #define SPI_SCALER_64 64
         #define SPI_SCALER_128 128
         #define SPI_SCALER_256 256

         #define data_format_8 8
         #define data_format_16 16
         
         #define SPI_MODE_0 0
         #define SPI_MODE_1 1
         #define SPI_MODE_2 2
         #define SPI_MODE_3 3


    void GPIOA_config(void);
    void SPI_config(void );
    void slaveManagementMode(void );
    void SPI_enable(void );
    void slaveSelectEnable(void );
    void slaveSelectDisable(void );
    void SPI1_SetMasterSlave(char );
// // // // // // // // // // // // // // // // // // // // // // // // // // // //
    void begin(void );
    void setDataMode(int , int);
    void setClockDivider(unsigned int );
    void setBitOrder(int);
    void transfer(short int* );
    void beginTransaction(int ,int ,unsigned int , int );
    void end(void);
    void endTransaction(void);
    void transmition(short int*);
    void recieve(short int*);
// // // // // // // // // // // // // // // // // // // // // // // // // // // //

 //functions
 
//SPI initialization functions
 // this functions sets whether the board is master or slave




  
  
/*

void SPI1_initialize(){
  //enable SPI1 clock
  RCC_APB2ENR |= (1<<12);
 //setting clock polarity and phase
  SPI1_CR1 &= ~(1 << 1); // Clear bit 1 (CPOL)
  SPI1_CR1 &= ~(1 << 0); // Clear bit 0 (CPHA)
  // Configure baud rate
  SPI1_CR1 |= (4 << 3); // Set BR bits to divide the clock by 256 (for an 8MHz clock)
  SPI1_CR1 &= ~(1 << 7); // put LSBFIRST bit to 0 for MSB first
  
  SPI1_CR1 |= (1<<8) | (1<<9); // SSM = 1 , SSI = 1 -> software slave management
  SPI1_CR1 &=~ (1<<10); // clear RXONLY for full duplex mode

  SPI1_CR2 = 0 ;        //clear since we are not using interrupt
} 

*/
  //this function enables the clock for the SPI1 register
void SPI_enable_clock(void);

 //this function initializes the timer (TIM2) register
void TIM2_Initialize(void);

//delay function makes a delay in milliseconds with the value of its argument
void delay(unsigned int );


#endif /* SPI_H */