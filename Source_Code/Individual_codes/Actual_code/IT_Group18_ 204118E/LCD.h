#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

#define RS PB0                  // Register Select pin on PB0
#define EN PB1                  // Enable pin on PB0

// Function Prototypes
void LCD_Init (void);
void LCD_Command(unsigned char);
void LCD_Print (char *);
void LCD_Clear();
void LCD_SetCursor(unsigned char, unsigned char);


void LCD_Init (void)
{
	DDRB = 0b11111111;
	_delay_ms(15);
	LCD_Command(0x02);          // 4 Bit Mode
	LCD_Command(0x28);          // 2 lines, 5x8 matrix,4-bit mode
	LCD_Command(0x0c);          // Display on, cursor off
	LCD_Command(0x06);          // Shift the cursor to right
	LCD_Command(0x01);          // Clear the display
	_delay_ms(2);
}

void LCD_Command(unsigned char cmnd)
{
	PORTB = (PORTB & 0x0F) | (cmnd & 0xF0);			// Send upper nibble
	PORTB &= ~(1<<RS);									// RS=0, command reg.
	PORTB |= (1<<EN);									// Enable=1
	_delay_us(1);
	PORTB &= ~(1<<EN);									// Enable=0

	_delay_us(200);

	PORTB = (PORTB & 0x0F) | (cmnd << 4);				// Send lower nibble
	PORTB |= (1<<EN);
	_delay_us(1);
	PORTB &= ~ (1<<EN);
	_delay_ms(2);
}

void LCD_Print (char *str)
{
	int i;
	for(i=0; str[i]!=0; i++)
	{
		PORTB = (PORTB & 0x0F) | (str[i] & 0xF0);			// Send upper nibble
		PORTB |= (1<<RS);									// RS=1, data reg.
		PORTB|= (1<<EN);										// Enable=1
		_delay_us(1);
		PORTB &= ~(1<<EN);									// Enable=0
		
		_delay_us(200);
		
		PORTB = (PORTB & 0x0F) | (str[i] << 4);			// Send lower nibble
		PORTB |= (1<<EN);
		_delay_us(1);
		PORTB &= ~(1<<EN);
		_delay_ms(2);
	}
}

void LCD_Clear()
{
	LCD_Command (0x01);         // Clear the display
	_delay_ms(2);
	LCD_Command (0x80);         // Force the cursor to the beginning of the 1st line
}

void LCD_SetCursor(unsigned char x, unsigned char y)			// x=column y=row
{
	unsigned char adr[] = {0x80, 0xC0};
	LCD_Command(adr[y-1] + x-1);
	_delay_us(100);
}

#endif // LCD_H_INCLUDED