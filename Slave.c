#include "SPI.h"
 //mosi , miso , clock , ss


void main() {

    short int  dummy=0x00;
     begin();
     SPI1_SetMasterSlave('s');

     beginTransaction(LSB_FIRST, data_format_8, SPI_SCALER_256, SPI_MODE_2);
     slaveSelectEnable();
     while(1){
      dummy=0x00;
      transfer(&dummy);
      if(dummy==0xFF){
        set_bit(GPIOA_ODR,0);
        delay(1000);
        clear_bit(GPIOA_ODR,0);
        delay(1000);
      }
     }


}