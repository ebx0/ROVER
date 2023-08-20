// page 252 gibi açıklamalar datasheet referansıdır: https://www.microchip.com/stellent/groups/picmicro_sg/documents/devicedoc/cn547043.pdf

/* ---- LIBRARY ---- */
void I2C_Init(dword baudrate) {
    systemPortInit('C', 3, 'D', 'I', 0);
    systemPortInit('C', 4, 'D', 'I', 0);

    // MSSP Control - page 252
    SSP1STAT = 0x00; // All clear
    SSP1STATbits.SMP = 1; // Slew rate disabled. (Standart Speed 100kHz)

    // SSP1 CONTROL REGISTER 1 - page 253
    SSP1CON1 = 0x00; // All clear
    SSP1CON1bits.SSPEN1 = 1; // Enable Serial Port and Config SDA SCL
    SSP1CON1bits.SSPM = 0b1000; // I2C Master mode, clock = FOSC / (4 * (SSPxADD+1))


    // BAUD RATE REGISTER - page 258
    SSP1ADD = ((_XTAL_FREQ / baudrate) - 1) / 4; // SCLx pin clock freq = FOSC/((ADD<7:0> + 1) *4)


    PIE1bits.SSP1IE = 0; /* Enable SSPIF interrupt */
    PIR1bits.SSP1IF = 0;
}

void I2C_Stop() {
    SSP1CON2bits.PEN = 1;
    while ( SSP1CON2bits.PEN );
}

void I2C_Start() {
    while ( SSP1STATbits.BF );
    SSP1CON2bits.SEN = 1;
    while ( SSP1CON2bits.SEN );
}

void I2C_Ack() {
    SSP1CON2bits.ACKDT = 0; /* Acknowledge data 1:NACK,0:ACK */
    SSP1CON2bits.ACKEN = 1; /* Enable ACK to send */
    while ( SSP1CON2bits.ACKEN );
}

void I2C_Nack() {
    SSP1CON2bits.ACKDT = 1; /* Acknowledge data 1:NACK,0:ACK */
    SSP1CON2bits.ACKEN = 1; /* Enable ACK to send */
    while ( SSP1CON2bits.ACKEN );
}

void I2C_Write(byte data) {
    SSP1BUF = data; // Load data into SSPBUF register
    while ( SSP1STATbits.BF ); // Data transmit complete, SSPxBUF is empty (does not include the ACK and Stop bits)
    __delay_ms(1);
}

byte I2C_Read(byte flag) {
    while ( SSP1STATbits.BF );
    SSP1CON2bits.RCEN = 1; // Enable I2C receive mode
    while ( !SSP1STATbits.BF ); // Wait until data is received
    byte data = SSP1BUF; // Read received data from SSPBUF register

    if ( flag == 1 ) {
        I2C_Ack();
    }
    else {
        I2C_Nack();
    }
    __delay_ms(1);
    return data;
}

void I2C_Send2(byte data0, byte data1) {
    I2C_Start(); // START Condition
    I2C_Write(0xA0); // write data 0, usually control/address
    I2C_Write(0x00); // write data 1
    I2C_Stop(); // STOP Condition
}

void I2C_Send3(byte data0, byte data1, byte data2) {
    I2C_Start(); // START Condition
    I2C_Write(data0); // write data 0, usually control/address
    I2C_Write(data1); // write data 1
    I2C_Write(data2); // write data 2
    I2C_Stop(); // STOP Condition
}

void I2C_Send4(byte data0, byte data1, byte data2, byte data3) {
    I2C_Start(); // START Condition
    I2C_Write(data0); // write data 0, usually control/address
    I2C_Write(data1); // write data 1
    I2C_Write(data2); // write data 2
    I2C_Write(data3); // write data 3
    I2C_Stop(); // STOP Condition
}

byte I2C_Receive(byte data0) {
    I2C_Start(); // START Condition
    I2C_Write(data0); // write data 0, usually control/address
    byte tempBuffer = I2C_Read(0);
    __delay_ms(20);
    I2C_Stop(); // STOP Condition
    return tempBuffer;
}
