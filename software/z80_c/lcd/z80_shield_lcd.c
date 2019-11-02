
#include "../pio/z80_shield_pio.h"

int lcd_a_shadow = 0;
int lcd_b_shadow = 0;


void lcd_rs_low(void)
{
  lcd_b_shadow &= 0xfe;
  IO_PIO1_B_DATA = lcd_b_shadow;
}

void lcd_e_low(void)
{
  lcd_b_shadow &= 0xfd;
  IO_PIO1_B_DATA = lcd_b_shadow;
}

void lcd_rs_high(void)
{
  lcd_b_shadow |= 0x01;
  IO_PIO1_B_DATA = lcd_b_shadow;
}

void lcd_e_high(void)
{
  lcd_b_shadow |= 0x02;
  IO_PIO1_B_DATA = lcd_b_shadow;
}

void lcd_send_s_data_4bits(char data)
{
  lcd_rs_low();
  lcd_e_high();
  IO_PIO1_A_DATA = (data << 4) & 0xf0;
  lcd_e_low();
  lcd_rs_high();
}

void lcd_send_s_data_8bits(char data)
{
  lcd_rs_low();
  lcd_e_high();

  IO_PIO1_A_DATA =  data;
  lcd_e_low();
  lcd_e_high();
  
  IO_PIO1_A_DATA = (data << 4) & 0xf0;
  lcd_e_low();
  lcd_rs_high();
}

void lcd_send_d_data_8bits(char data)
{
  lcd_rs_high();
  lcd_e_high();

  IO_PIO1_A_DATA =  data;
  lcd_e_low();
  lcd_e_high();
  
  IO_PIO1_A_DATA =(data << 4) & 0xf0;
  lcd_e_low();
  lcd_rs_high();
}


void lcd_delay(int delay)
{
  int i,j;

  return;
  for(i=0;i<delay;i++)
    {
        for(j=0;j<10000;j++)
	  {
	  }
    }
  
}

void lcd_initialise(void)
{
  // We have to initialise the PIOs
  z80_shield_pio_init(PIO1, PIO_PORT_A, 0x00, 0x0F);
  z80_shield_pio_init(PIO1, PIO_PORT_B, 0x00, 0xFC);
  z80_shield_pio_init(PIO0, PIO_PORT_A, 0x01, 0xFB);  //AD_CS
  
  lcd_rs_low();
  lcd_e_low();
  lcd_delay(1);
  
  lcd_send_s_data_4bits(0x03);
  lcd_send_s_data_4bits(0x03);
  lcd_send_s_data_4bits(0x03);

  lcd_send_s_data_4bits(0x02);
  lcd_send_s_data_8bits(0x0e);
  lcd_send_s_data_8bits(0x06);

  lcd_send_s_data_8bits(0x01);

}

void lcd_display(char *text)
{
    while(*text != '\0' )
    {
      lcd_send_d_data_8bits(*text++);
    }
}
