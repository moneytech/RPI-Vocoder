#include "rpi_midi.h"
#include "../peripherals/rpi_peripherals.h"
#include "../rpi_type.h"
#include "../timer/rpi_timer.h"
#include "../gpio/rpi_gpio.h"

// serial clock(default: 3MHz)
#define SERIAL_CLOCK	3000000

int midi_Init(void){
	
	/****	初期設定開始	***/
	// UART無効化
	*UART0_CR 	= 0;
	
	//ポートの設定
	pinMode(14,INPUT_PULLDOWN);
	pinMode(15,INPUT_PULLDOWN);
	pinMode(14,ALT0);
	pinMode(15,ALT0);

	//3MHz/(16 * 31250) = 6

	// ボーレート設定
	*UART0_IBRD = 6;
	*UART0_FBRD = 0;
	
	// LCRH
	// stick parity dis, 8bit, FIFO en, two stop bit no, odd parity, parity dis, break no
	*UART0_LCRH = 0x70;

	// CR
	// CTS dis, RTS dis, OUT1-2=0, RTS dis, DTR dis, RXE en, TXE en, loop back dis, SIRLP=0, SIREN=0, UARTEN en
	*UART0_CR 	= 0x0301;
	/****	初期設定終了	***/

	return 0;
}

void midi_end(void){
	// UART無効化
	*UART0_CR = 0;
}

int midi_available(void){
	if(!(*UART0_FR & (0x01 << 4))){
		return 1;
	}
	return 0;
}

int midi_recv(void){
	// 読み込み
	int c = *UART0_DR;
	return c & 0xff;
}


