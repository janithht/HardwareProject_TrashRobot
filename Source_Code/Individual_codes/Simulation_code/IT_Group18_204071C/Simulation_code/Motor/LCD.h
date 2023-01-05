#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

#define LCD_Port PORTB          // we have connected the LCD on port D
#define LCD_DIR  DDRB			// we're defining the direction of the pins, weather it is input or output
#define RS PB0                  // we need total six pin to show output on the LCD. Data pin 4, 5, 6, and 7 for sending the data to the LCD and Enable and RS pin for controlling the behavior of the LCD we have connected RS pin of LCD to port D pin 0
#define EN PB1                  // we have connected Enable pin of LCD to port D pin 1

void LCD_Command(unsigned char);

void LCD_Init (void)
{
	LCD_DIR = 0xFF;
	_delay_ms(15);
	LCD_Command(0x02);          // 4 Bit Mode
	LCD_Command(0x28);          // 2 lines, 5x8 matrix,4-bit mode
	LCD_Command(0x0c);          //Display on, cursor off
	LCD_Command(0x06);          //Shift the cursor to right
	LCD_Command(0x01);          //Clear the display
	_delay_ms(2);
}

void LCD_Command(unsigned char cmnd)
{
	LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0);
	LCD_Port &= ~(1<<RS);
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~(1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}

void LCD_Clear()
{
	LCD_Command (0x01);         //Clear the display
	_delay_ms(2);
	LCD_Command (0x80);         //Force the cursor to the beginning of the 1st line
}


void LCD_Print (char *str)
{
	int i;
	for(i=0; str[i]!=0; i++)
	{
		LCD_Port = (LCD_Port & 0x0F) | (str[i] & 0xF0);
		LCD_Port |= (1<<RS);
		LCD_Port|= (1<<EN);
		_delay_us(1);
		LCD_Port &= ~ (1<<EN);
		_delay_us(200);
		LCD_Port = (LCD_Port & 0x0F) | (str[i] << 4);
		LCD_Port |= (1<<EN);
		_delay_us(1);
		LCD_Port &= ~(1<<EN);
		_delay_ms(2);
	}
}


void LCD_SetCursor(unsigned char x, unsigned char y)
{
	unsigned char adr[] = {0x80, 0xC0};
	LCD_Command(adr[y-1] + x-1);
	_delay_us(100);
}

#endif // LCD_H_INCLUDED
