#include "SPI.h"



void main() {
     short int  d=0xFF;
     begin();
     SPI1_SetMasterSlave('m');

     beginTransaction(LSB_FIRST, data_format_8, SPI_SCALER_256, SPI_MODE_2);
     slaveSelectEnable();
     while(1){
      d=0xFF;
      transfer(&d);
      delay(2000);
     }


}