// MAIN
char rxBuffer[BUFFER_SIZE];
byte rxBufferHead = 0;
byte bufferState = 0; // 0: ready, 1: writing, 2: stopped.

void rcScan(char* receivedData) {
    /*
     İç haberleşme protokolünüze uygun şekilde kodunuzu doldurabilirsiniz.
    */
}

// INTERRUPT
void __interrupt() ISR(void) {
    else if ( PIR1bits.RC1IF ) { // USART1 RC
        rcScan(RC1REG);
        PIR1bits.RC1IF = 0;
    }
}

// LIBRARY
void usart1Init(dword baud_rate) {
    TRISC6 = 0; /* Make Tx pin as output*/
    TRISC7 = 1; /* Make Rx pin as input*/
    ANSELCbits.ANSC6 = 0;
    ANSELCbits.ANSC7 = 0;
    __delay_ms(1);
    SPBRG1 = (_XTAL_FREQ / (64UL * baud_rate)) - 1;
    TXSTA1 = 0x20; /* Enable Transmit(TX) */
    RCSTA1 = 0x90; /* Enable Receive(RX) & Serial */

    PIE1bits.RC1IE = 1; /* Enable Receive Interrupt */
}

void usart1TX(char data) {
    while ( !TX1IF ); // Wait for the transmit buffer to be empty
    TXREG1 = data; // Transmit the data
}

char usart1RX(void) {
    while ( !RC1IF ); // Wait for the receive buffer to be full
    return RCREG1; // Return the received data
}

// To write unkown bytes of char arrat with UART protocol
void usart1WriteString(char* text) {
    for ( int i = 0; i < 128; i++ ) {
        if ( text[i] == 0 ) {
            return;
        }
        usart1TX(text[i]);
    }
}

// To write INTEGER values with UART protocol.
void usart1WriteInt(qword integer, byte n) {
    byte temp;
    byte isStart = 0;
    for ( byte i = 1; i <= n; i++ ) {
        temp = (integer / power(10, n - i)) % 10; /* int/10^n-i  */
        temp += 0x30; /* '0' = 48*/
        if ( n == 0 ) {
            if ( temp != 0x30 || isStart ) {
                isStart = 1;
                usart1TX(temp);
            }
        }
        else {
            usart1TX(temp);
        }
    }
}
