/*
 * iic.h
 *
 *  Created on: 2021Äê3ÔÂ20ÈÕ
 *      Author: Woodman
 */

#ifndef IIC_H_
#define IIC_H_
//----------------------------------------
#include <driverlib.h>

#define SCREEN_ADDRESS_SENT 0x78

#define IIC_OUT P4OUT
#define IIC_SCL BIT1
#define IIC_SDA BIT2

#define SCL_H IIC_OUT |= IIC_SCL
#define SCL_L IIC_OUT &= ~IIC_SCL
#define SDA_H IIC_OUT |= IIC_SDA
#define SDA_L IIC_OUT &= ~IIC_SDA
#define SDA_val GPIO_getInputPinValue(GPIO_PORT_P4,GPIO_PIN2)

void IIC_START()
{
    SDA_H;
    SCL_H;
    SDA_L;
    SCL_L;
}

void IIC_STOP()
{
    SDA_L;
    SCL_H;
    SDA_H;
}

//write 8 bit
void IIC_W(uint8_t data)
{
    uint8_t i;
    for(i=0; i<8; i++)
    {
        if((data << i) & 0x80)  //get bit from Byte
            SDA_H;
        else
            SDA_L;

        SCL_H;
        SCL_L;
    }
    SCL_H;  //ack
    SCL_L;
}

void Write_Command(uint8_t cmd)
{
    IIC_START();
    IIC_W(SCREEN_ADDRESS_SENT);
    IIC_W(0x00);  //command to write command(tell the device the next Byte is a command)
    IIC_W(cmd);
    IIC_STOP();
}

void Write_Data(uint8_t data)
{
    IIC_START();
    IIC_W(SCREEN_ADDRESS_SENT);
    IIC_W(0x40);    //command to write data(tell the device the next Byte is a data)
    IIC_W(data);
    IIC_STOP();
}


void Init()
{
    __delay_cycles(50000);

    Write_Command(0xAE); //Set Display Off
    Write_Command(0x00);
    Write_Command(0x10);
    Write_Command(0xd5); //display divide ratio/osc. freq. mode
    Write_Command(0x80); //
    Write_Command(0xA8); //multiplex ration mode:63
    Write_Command(0x3F);
    Write_Command(0xD3); //Set Display Offset
    Write_Command(0x00);
    Write_Command(0x40); //Set Display Start Line
    Write_Command(0xAD); //Set DC-DC
    Write_Command(0x8B);
    Write_Command(0xA1); //Segment Remap
    Write_Command(0xC8); //Sst COM Output Scan Direction
    Write_Command(0xDA); //common pads hardware: alternative
    Write_Command(0x12);
    Write_Command(0x81); //contrast control //
    Write_Command(0xCF);
    Write_Command(0xD9); //set pre-charge period
    Write_Command(0xF1);
    Write_Command(0xDB); //VCOM deselect level mode
    Write_Command(0x40); //set Vvcomh=0.83*Vcc
    Write_Command(0xA4); //Set Entire Display On/Off
    Write_Command(0xA6); //Set Normal Display
    Write_Command(0xAF); //Set Display On

    Write_Command(0x20); // set memory addressing mode
    Write_Command(0x01); // page addressing mode
}

void ScreenPrint(uint8_t show[][8])
{
    uint8_t i, j, k;
    for(i=0; i<8; i++)
      {
          Write_Command(0xb0+i);
          Write_Command(0x02);
          Write_Command(0x10);
          IIC_START();
          IIC_W(SCREEN_ADDRESS_SENT);
          IIC_W(0x40);
          for(k=0; k<8; k++)
          {
              for(j=0; j<16; j++)
              {
                 IIC_W(show[16*k+j][i]);
              }
          }
          IIC_STOP();
      }
}

#endif /* IIC_H_ */
