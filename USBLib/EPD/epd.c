#include "main.h"

//extern SPI_HandleTypeDef hspi1;

#define RST  GPIOA, GPIO_PIN_1
#define DC   GPIOA, GPIO_PIN_2
#define BUSY GPIOA, GPIO_PIN_3
#define CS   GPIOA, GPIO_PIN_4
#define CLK  GPIOA, GPIO_PIN_5
#define DIN  GPIOA, GPIO_PIN_7

#define WritePin(_pin, _value) SPI_WritePin(_pin, (_value) == 0? GPIO_PIN_RESET:GPIO_PIN_SET)
#define ReadPin(_pin) HAL_GPIO_ReadPin(_pin)

//void SPI_WriteByte(uint8_t val) { HAL_SPI_Transmit(&hspi1, &val, 1, 1000); }

//#define SPI_DEBUG
void SPI_WritePin(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t val) {
    HAL_GPIO_WritePin(GPIOx, pin, val);
#ifdef SPI_DEBUG
    HAL_GPIO_WritePin(GPIOB, pin >> 1, val);
#endif
}

//void db_PUT(const char* str);
void db_LED_ON(int i);
void db_LED_OFF(int i);
void db_LED(int i, int val);

#define SPI_LEN 100
#define SPI_Wait() for (int j = 0; j < SPI_LEN; j++) { }

void SPI_WriteByte(uint8_t val) {
    WritePin(CS, 1); 
    SPI_Wait();
    WritePin(CLK, 0);
    SPI_Wait();
    WritePin(CS, 0); 
    for(int i = 7; i >= 0; i--) {
        SPI_Wait();
        WritePin(DIN, val & (1 << i));
        SPI_Wait();
        WritePin(CLK, 1); 
        SPI_Wait();
        WritePin(CLK, 0);
    }
    WritePin(CS, 1); 
    SPI_Wait();
}

void SPI_Command(uint8_t val){
    WritePin(DC, 0); 
    SPI_WriteByte(val);
}

void SPI_Data(uint8_t val) {
    WritePin(DC, 1); 
    SPI_WriteByte(val);
}


void WaitBusy(){ 
    while(ReadPin(BUSY) == GPIO_PIN_SET) {
        db_LED_ON(2);
        HAL_Delay(10);
    } 
}

#include "image.h"

void init_test(){

    //while(1) { WaitBusy(); }

    WritePin(DC, 1);
    WritePin(CS, 1);
    WritePin(RST, 1);
    HAL_Delay(20);

    //db_PUT("hardware reset\n");
    db_LED_ON(0);
    WritePin(RST, 0);
    HAL_Delay(10);
    WritePin(RST, 1);
    HAL_Delay(10);

    // db_PUT("software reset\n");
    WaitBusy();
    SPI_Command(0x12);
    WaitBusy();

    //db_PUT("driver output control\n");
    SPI_Command(0x01);
    SPI_Data(0xc7);
    SPI_Data(0x00);
    SPI_Data(0x00);


    //db_PUT("gate driving voltage\n");
    SPI_Command(0x03);
    SPI_Data(0x00); // VGH

    //db_PUT("source driving voltage\n");
    SPI_Command(0x04);
    SPI_Data(0x41); // VSH1
    SPI_Data(0xA8); // VSH2
    SPI_Data(0x32); // VSL

    //db_PUT("data entry sequence\n");
    SPI_Command(0x11);
    SPI_Data(0x01);

    //db_PUT("Start/End X\n");
    SPI_Command(0x44);
    SPI_Data(0x00);
    SPI_Data(0x18);

    //db_PUT("Start/End Y\n");
    SPI_Command(0x45);
    SPI_Data(0xC7);
    SPI_Data(0x00);
    SPI_Data(0x00);
    SPI_Data(0x00);

    //db_PUT("load LUT from OTP\n");
    SPI_Command(0x22);
    SPI_Data(0xB1);
    SPI_Command(0x20);
    WaitBusy();

    //db_PUT("set X addr counter \n");
    SPI_Command(0x4E);
    SPI_Data(0x00);

    //db_PUT("set Y addr counter\n");
    SPI_Command(0x4F);
    SPI_Data(0xC7);
    SPI_Data(0x00);

    //db_PUT("clear\n");
    SPI_Command(0x24);
    for (int j = 0; j < 200; j++)
        for (int i = 0; i < 25; i++) {
            SPI_Data(mat[25 * j + i]);
        }
    SPI_Command(0x22);
    SPI_Data(0xC7);
    SPI_Command(0x20);
    WaitBusy();
    HAL_Delay(1000);

    // sleep
    //db_PUT("sleep\n");
    SPI_Command(0x10);
    SPI_Data(0x01);
    db_LED_ON(7);
}

