/*
 REFERANCE: https://www.microchip.com/stellent/groups/picmicro_sg/documents/devicedoc/cn547043.pdf
 PAGE 292-301
*/

void ADCinit() {
    ADCON1 = 0x00; // use internal referance
    ADCON2 = 0x51; // 0b01010001 -> 01: Right, 010: 4 TAD, 001: Fosc /8
    ADRESH = 0;
    ADRESL = 0;
}

void ADCportInit(byte channel) {
    ANSELA &= (1 << channel); // disable digital buffer
    TRISA &= (1 << channel); // set input
}

word ADCread(byte channel) {
    word digital;
    ADCON0 &= 0xc3; // 0b11000011 -> clear previous channel
    ADCON0 |= (channel << 2) & 0x7c; // 0b01111100 -> select channel
    ADCON0 |= 0x03 ; // 0b00000011

    while ( ADCON0bits.GO_nDONE ) {
    }
    digital = (ADRESH << 2) | (ADRESL >> 6);
    return digital;
}
