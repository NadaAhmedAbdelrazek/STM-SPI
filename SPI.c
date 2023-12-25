#include "SPI.h"
 
      // PA5 will be used for the clock
      // PA6 will be used for the MISO
      // PA7 will be used for the MOSI
      // PA4 will be used for slave select
 
    //this function initializes the timer (TIM2) register
     void TIM2_Initialize() {
    // Enable TIM2 clock
    set_bit(RCC_APB1ENR , 0); // Set bit 0 (TIM2EN) in RCC_CR

     // Update Timer 2 registers
    set_bit(TIM2_EGR , 0); // Trigger update event to load the prescaler value

    // Set prescaler to run the timer at 1MHz
    TIM2_PSC = 15999; // Assuming a 16MHz clock, PSC = (SystemClock / DesiredClock) - 1

    // Auto-reload preload enable
    set_bit(TIM2_CR1 , 7); // Set bit 7 (ARPE) in TIM2_CR1

}

  //delay function makes a delay in milliseconds with the value of its argument
  void delay(unsigned int milliseconds) {
    // Initialize Timer 2
    TIM2_Initialize();

    TIM2_ARR = milliseconds; // Set ARR to generate the specified delay(maximum counts)

    // Enable the counter
    set_bit(TIM2_CR1 ,0); // Set bit 0 (CEN) in TIM2_CR1
    clear_bit(TIM2_SR ,0);  //clear the event flag bit
    // Wait until the update event (UEV) flag is set
    while (!(TIM2_SR & (1 << 0))) {
        // Wait for the update event flag
    }

    // Clear the update event flag
    clear_bit(TIM2_SR ,0); // Clear bit 0 (UIF) in TIM2_SR

    // Disable the counter
    clear_bit(TIM2_CR1 , 0); // Clear bit 0 (CEN) in TIM2_CR1
}
  
  
   void SPI_enable_clock(){
 //enable SPI1 clock
  set_bit(RCC_APB2ENR ,12);
 }
   //This function configures the GPIOA register

      void GPIOA_config(){
        //Enable the clock for port A
        set_bit(RCC_AHB1ENR ,0);

        //set PA5, PA6, PA7 as an alternate functions
        GPIOA_MODER |= (2<<10)|(2<<12)|(2<<14);
        //set PA4 as an output pin
        set_bit(GPIOA_MODER ,8);

        //Higher speed for PA5, PA6, PA7
        GPIOA_OSPEEDR |= (3<<10)|(3<<12)|(3<<14)|(3<<18);
        //AF5 (SPI1) for PA5, PA6, PA7
        GPIOA_AFRL |= (5<<20)|(5<<24)|(5<<28);

    }
    //this function enables the SPI1 register for communication
    void SPI_enable(){
     set_bit(SPI1_CR1 ,6);
    }
    
    //this function configures the SPI1 register
     void SPI_config(){
        set_bit(RCC_APB2ENR ,12);
        
        clear_bit(SPI1_CR1 ,13); //Disable Hardware CRC calculation enable
        clear_bit(SPI1_CR1 ,10); // clear RXONLY for full duplex mode
        SPI_enable();

        SPI1_CR2 = 0 ;        //clear since we are not using interrupt
        clear_bit(SPI_SR , 7);
    }
    
    //this function sets the slave management mode as software slave management
    void slaveManagementMode(){
        // SSM = 1 , SSI = 1 -> software slave management
        set_bit(SPI1_CR1 ,8);
        set_bit(SPI1_CR1 ,9);
        
    }
 

 
    //this function uses PA9 to select a slave and enables it
    void slaveSelectEnable(){
       //set_bit(GPIOA_BSRR ,25); //reset pin PA9,
       set_bit(GPIOA_BSRR , 20); // reset bit 4 (BR) of BSRR register
     }
     
    //this function uses PA9 to select a slave and disables it
    void slaveSelectDisable(){
       //set_bit(GPIOA_BSRR ,9); //set pin PA9,
       set_bit(GPIOA_BSRR ,4); // Set bit 4 (BS) of BSRR register
     }
 

//  // // // // // // // // // // // // // // // // // // // // // // // // // // // // //
    void begin(){
   set_bit(RCC_APB2ENR ,12); //enable the clock
   GPIOA_config();      //configuration for GPIO
   SPI_config();       //configuration for the SPI1
   slaveManagementMode(); //selecting slave management mode
   SPI_enable();          // enable the SPI
  }
  
  //setting data mode
  void setDataMode(int mode, int clockMode){
      if(mode == 8) clear_bit(SPI1_CR1 ,11);       //clearing bit 11 for 8_bit mode
      else if (mode == 16) set_bit(SPI1_CR1 ,11); //setting bit 11 for 16_bit mode
  
      switch (clockMode)
      {
        case 0:
         clear_bit(SPI1_CR1 , 1); // Clear bit 1 (CPOL)
         clear_bit(SPI1_CR1 , 0); // Clear bit 0 (CPHA)
        break;
        
        case 1:
         clear_bit(SPI1_CR1 , 1); // Clear bit 1 (CPOL)
         set_bit(SPI1_CR1 , 0); // Set bit 0 (CPHA)
        break;
        
        case 2:
         set_bit(SPI1_CR1 , 1); // set bit 1 (CPOL)
         clear_bit(SPI1_CR1 , 0); // clear bit 0 (CPHA)
        break;
        
        case 3:
         set_bit(SPI1_CR1 ,1); // set bit 1 (CPOL)
         set_bit(SPI1_CR1 ,0); // Set bit 0 (CPHA)
        break;
        default:
         clear_bit(SPI1_CR1 , 1); // Clear bit 1 (CPOL)
         clear_bit(SPI1_CR1 , 0); // Clear bit 0 (CPHA)
        break;
      }
  }
  
  //setting the clock devider
   void setClockDivider(unsigned int divider){
        switch (divider)
        {
          case 2:
           clear_bit(SPI1_CR1 ,3);
           clear_bit(SPI1_CR1 ,4);
           clear_bit(SPI1_CR1 ,5);
          break;
          
          case 4:
           set_bit(SPI1_CR1 ,3);
           clear_bit(SPI1_CR1 ,4);
           clear_bit(SPI1_CR1 ,5);
          break;
          
          case 8:
           clear_bit(SPI1_CR1 ,3);
           set_bit(SPI1_CR1 ,4);
           clear_bit(SPI1_CR1 ,5);
          break;
          
          case 16:
           set_bit(SPI1_CR1 ,3);
           set_bit(SPI1_CR1 ,4);
           clear_bit(SPI1_CR1 ,5);
          break;
          
          case 32:
           clear_bit(SPI1_CR1 ,3);
           clear_bit(SPI1_CR1 ,4);
           set_bit(SPI1_CR1 ,5);
          break;
          
          case 64:
           set_bit(SPI1_CR1 ,3);
           clear_bit(SPI1_CR1 ,4);
           set_bit(SPI1_CR1 ,5);
          break;
          
          case 128:
           clear_bit(SPI1_CR1 ,3);
           set_bit(SPI1_CR1 ,4);
           set_bit(SPI1_CR1 ,5);
          break;
          
          case 256:
           set_bit(SPI1_CR1 ,3);
           set_bit(SPI1_CR1 ,4);
           set_bit(SPI1_CR1 ,5);
          break;
          default:
           clear_bit(SPI1_CR1 ,3);
           clear_bit(SPI1_CR1 ,4);
           clear_bit(SPI1_CR1 ,5);
          break;
        }
   
   
   }
   
   //setting bit order
   void setBitOrder(int byteOrder){
     switch (byteOrder)
     {
       case 0:
        set_bit(SPI1_CR1 ,7); //LSB transmitted first
       break;
       case 1:
        clear_bit(SPI1_CR1 ,7); //MSB transmitted first
        break;
        default:
         clear_bit(SPI1_CR1 ,7); //MSB transmitted first
        break;
     }
   }

// Function for simultaneous send and receive via SPI
   void transfer(short int* dataIn ){
   
    // Ensure TX buffer is empty before sending data
    while (~(SPI_SR & (1 << 1))); /* Wait until transmit buffer is empty (TXE flag set)*/
    while ((SPI_SR & (1 << 7))); /* Wait fot busy bit to reset */

    // Write data to be sent into the data register
    SPI_DR = *dataIn ;
    //set_bit(SPI1_CR1,12); //write in CRCNEXT
    // Wait until RX buffer is full (wait for receive data)
    while (~(SPI_SR & (1 << 0))); /* Wait until receive buffer is full (RXNE flag set)*/
    while ((SPI_SR & (1 << 7))); /* Wait fot busy bit to reset */

    // Read received data from data register and save it in the address
     *dataIn = SPI_DR;



}

// Function to disable the SPI1 module
void end() {
    // Wait until RXNE = 1 to receive the last data
    while (!(SPI1_SR & (1 << 0))) ;/* Wait until RXNE flag is set (last data received)*/

    // Wait until TXE = 1
     while (!(SPI_SR & (1 << 1))) ;/* Wait until TXE flag is set*/
    // Wait until BSY = 0
    while (SPI_SR & (1 << 7)) ;/* Wait until BSY flag is cleared (SPI not busy)*/
   // Disable SPI (SPE = 0)
     clear_bit(SPI1_CR1 ,6);

    // Disable peripheral clock
    clear_bit(RCC_APB2ENR ,12); // Disable SPI1 clock

    // Enter halt mode (if required)
    // Example: __WFI(); // Wait for interrupt (halt mode)


}

 void SPI1_SetMasterSlave(char mode) {
    // Enable SPI1 clock
    set_bit(RCC_APB2ENR ,12);

    // Configure SPI1_CR1 based on the mode ('m' for master, 's' for slave)
    if (mode == 'm' || mode == 'M') {
        // Set SPI1_CR1 as master
        set_bit(SPI1_CR1 ,2); // Set bit 2 (MSTR) for master mode
    } else if (mode == 's' || mode == 'S') {
        // Clear SPI1_CR1 to operate as slave
        clear_bit(SPI1_CR1, 2); // Clear bit 2 (MSTR) for slave mode
    }

}
 
 //begin transaction function to prepare for SPI communication
void beginTransaction(int byteOrder,int dataMode,unsigned int baudRate, int clockMode){

 //enable SPI1 clock
      SPI_config();

 // Set byte order (MSB or LSB first)
      setBitOrder(byteOrder);
    
 // set data mode (8_bit or 16_bit mode) and clock mode
      setDataMode(dataMode,clockMode);
    
    //setting baud rate
      setClockDivider(baudRate); // Set BR bits to divide the clock
       
}

 //this function ends the transaction
 void endTransaction(){
     // Wait until RXNE = 1 to receive the last data
    while (!(SPI_SR & (1 << 0))) ;/* Wait until RXNE flag is set (last data received)*/

    // Wait until TXE = 1
    while (!(SPI_SR & (1 << 1))) ;/* Wait until TXE flag is set*/

    // Wait until BSY = 0
    while (SPI_SR & (1 << 7)) ;/* Wait until BSY flag is cleared (SPI not busy)*/
   // Disable SPI (SPE = 0)
     clear_bit(SPI1_CR1 ,6);

 }
 
 void transmition(short int* d){
    slaveSelectEnable();
 // Ensure TX buffer is empty before sending data
    while (~(SPI_SR & (1 << 1))); /* Wait until transmit buffer is empty (TXE flag set)*/
    while ((SPI_SR & (1 << 7))); /* Wait fot busy bit to reset */
    
    // Write data to be sent into the data register
    SPI_DR = *d ;
    }
    
  void recieve(short int* dataIn){
      set_bit(SPI1_CR1 ,6);
      slaveSelectEnable();
      // Wait until RX buffer is full (wait for receive data)
    while (!(SPI_SR & (1 << 0))); /* Wait until receive buffer is full (RXNE flag set)*/
    while ((SPI_SR & (1 << 7))); /* Wait fot busy bit to reset */

    // Read received data from data register and save it in the address
     *dataIn = SPI_DR;
     if(SPI_DR==0xAB){
          while(1){
            set_bit(GPIOA_ODR,0);
            Delay_ms(1000);
            clear_bit(GPIOA_ODR,0);
            Delay_ms(1000);
          }
     }
     
  }