#include "mbed.h"
#include "TextLCD.h"

#define MAXIMUM_BUFFER_SIZE 6

static DigitalOut led1(LED1); // led1 = PA_5
static DigitalOut led2(LED2); // led2 = PB_14

Thread thread1;
Thread thread2;

static BufferedSerial device2(D1, D0);  // tx, rx   D1:tx   D0:rx
static BufferedSerial serial_port(USBTX, USBRX);

I2C i2c_lcd(D14, D15); // SDA, SCL

//TextLCD_SPI lcd(&spi_lcd, p8, TextLCD::LCD40x4);   // SPI bus, 74595 expander, CS pin, LCD Type
TextLCD_I2C lcd(&i2c_lcd, 0x4E, TextLCD::LCD16x2);   // I2C bus, PCF8574 Slaveaddress, LCD Type
                                                     //TextLCD_I2C lcd(&i2c_lcd, 0x42, TextLCD::LCD16x2, TextLCD::WS0010);
                                                     // I2C bus, PCF8574 Slaveaddress, LCD Type, Device Type
                                                     //TextLCD_SPI_N lcd(&spi_lcd, p8, p9);
                                                     // SPI bus, CS pin, RS pin, LCDType=LCD16x2, BL=NC, LCDTCtrl=ST7032_3V3
//TextLCD_I2C_N lcd(&i2c_lcd, ST7032_SA, TextLCD::LCD16x2, NC, TextLCD::ST7032_3V3);
// I2C bus, Slaveaddress, LCD Type, BL=NC, LCDTCtrl=ST7032_3V3

FileHandle *mbed::mbed_override_console(int fd)
{
   return &serial_port;
}

void slave_thread() {
  while (1) {
    char buf2[MAXIMUM_BUFFER_SIZE];
    int temp;
    if (serial_port.readable()) {
      serial_port.read(buf2, 1);

      if (buf2[0] == '1') {
        lcd.locate(1, 1);
      } else if (buf2[0] == '2') {
        lcd.cls();
      } else if (buf2[0] == '3') {
          temp = lcd.columns();
          printf("Columns: %d\r\n", temp);
      } else if (buf2[0] == '4') {
          temp = lcd.rows();
          printf("Rows: %d\r\n", temp);
      } else if (buf2[0] == '5') {
          lcd.putc('x');
      } else {
      }
    }
  }
}

int main() {
  // Set desired properties (9600-8-N-1).
  device2.set_baud(9600);
  device2.set_format(
      /* bits */ 8,
      /* parity */ BufferedSerial::None,
      /* stop bit */ 1);

  //thread1.start(master_thread);
  thread2.start(slave_thread);
}
