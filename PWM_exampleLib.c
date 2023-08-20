/*
 REFERANCE: https://www.microchip.com/stellent/groups/picmicro_sg/documents/devicedoc/cn547043.pdf

 Kullanım kolaylığını sağlayabilmek adına varolan kütüphanelerden farklı şekilde eşleştirmeli bir struct yapısı kullanıyorum.
 Her bir PWM sinyaline tanımlı bir struct, hem PWM için gerekli on-off, freq, duty gibi değerleri topluyor hem de hangi timer'ı ve hangi kanalı kullanacağını seçiyor.
 Kütüphane, ek olarak pwm'in kullanacağı timer'ı da modifiye ederek hassasiyeti arttırmaktadır.

 */ 

/* EXAMPLE CODE */

    // first argument is the ID of PWM channel, 0 in example
    pwmSetDuty(0, 50); // %50 of Freq
    pwmSetFreq(0, 10000); // 10kHz

    pwmSetCh(0, 2); // select 2nd channel as PWM Output
    pwmSetTimer(0, 2); // select 2nd Timer for PWM
    pwmSetStatus(0, 1); // Activate the PWM

/* ---- */




/* ---- LIBRARY.h ---- */
    PWM_t pwms[5] = {

        { // 0 
            .freq = 2000,
            .duty = 50,
            .flag = (1 << pwm_chBitRank) | (2 << pwm_timerBitRank) | (1 << pwm_statusBitRank),
        },
        { // 1
            .freq = 2000,
            .duty = 50,
            .flag = (2 << pwm_chBitRank) | (4 << pwm_timerBitRank) | (1 << pwm_statusBitRank),
        }
        // ... Continue up to 5 PWM
    };

/* ---- STRUCT ---- */
#define pwm_chBitRank 5
#define pwm_timerBitRank 2 
#define pwm_statusBitRank 1

#define pwm_chBitSize 0b111
#define pwm_timerBitSize 0b111
#define pwm_statusBitSize 0b1

typedef struct PWM {
    dword freq;
    byte duty;
    byte flag;
} PWM_t;


/* ---- LIBRARY ---- */
void pwmInit(byte pwmNo) {
    /*
     * pwmFreq min = 2000
     * pwmDuty = 0-100
     * pwmChannel: 1-5
     * pwmTimer: 2/4/6
     */


    // Take data from struct.
    dword pwmFreq = pwms[pwmNo].freq;
    byte pwmDuty = pwms[pwmNo].duty;
    byte pwmChannel = (pwms[pwmNo].flag & (pwm_chBitSize << pwm_chBitRank)) >> pwm_chBitRank; // Get channel value from struct
    byte pwmTimer = (pwms[pwmNo].flag & (pwm_timerBitSize << pwm_timerBitRank)) >> pwm_timerBitRank; // Get timer value from struct
    byte pwmStatus = (pwms[pwmNo].flag & (pwm_statusBitSize << pwm_statusBitRank)) >> pwm_statusBitRank; // Get timer value from struct

    /* Timer Select Bit */
    byte CxTSEL = (pwmTimer >> 1) - 1;

    /* Channel Selection */
    if ( pwmChannel == 1 ) {
        systemPortInit('C', 2, 'D', 'O', 'L');
        CCPTMRS0bits.C1TSEL = CxTSEL; // Timer selection    
        CCP1CON = 0x0C; // Set CCPxCON as PWM mode
    }
    else if ( pwmChannel == 2 ) {
        systemPortInit('C', 1, 'D', 'O', 'L');
        CCPTMRS0bits.C2TSEL = CxTSEL; // Timer selection
        CCP2CON = 0x0C; // Set CCPxCON as PWM mode
    }
    else if ( pwmChannel == 3 ) {
        systemPortInit('B', 5, 'D', 'O', 'L');
        CCPTMRS0bits.C3TSEL = CxTSEL; // Timer selection 
        CCP3CON = 0x0C; // Set CCPxCON as PWM mode
    }
    else if ( pwmChannel == 4 ) {
        systemPortInit('D', 1, 'D', 'O', 'L');
        CCPTMRS1bits.C4TSEL = CxTSEL; // Timer selection 
        CCP4CON = 0x0C; // Set CCPxCON as PWM mode
    }
    else if ( pwmChannel == 5 ) {
        systemPortInit('E', 2, 'D', 'O', 'L');
        CCPTMRS1bits.C5TSEL = CxTSEL; // Timer selection 
        CCP5CON = 0x0C; // Set PWM mode
    }

    byte tmrPrescale = 1; // Timer Prescale Value
    byte TxCKPS = 0; // Temporary timer prescale selection register value
    byte PRx; // Temporary Pulse Period register value

    /* Tuning the right prescale value */
    dword tempPRx = (_XTAL_FREQ / (4 * pwmFreq)) - 1; // datasheet
    while ( tempPRx > 255 ) {
        tempPRx >>= 1;
        tmrPrescale <<= 2;
        TxCKPS++;
        if ( TxCKPS > 2 ) break;
    }
    if ( TxCKPS > 2 ) return;

    /* PRx (Period) register value set*/
    PRx = (_XTAL_FREQ / (4 * pwmFreq * tmrPrescale)) - 1; // Seting PRx register value


    /* CCPRxL (Duty) period register set */
    if ( pwmChannel == 1 ) CCPR1L = ((PRx + 1) * pwmDuty) / 100;
    else if ( pwmChannel == 2 ) CCPR2L = ((PRx + 1) * pwmDuty) / 100;
    else if ( pwmChannel == 3 ) CCPR3L = ((PRx + 1) * pwmDuty) / 100;
    else if ( pwmChannel == 4 ) CCPR4L = ((PRx + 1) * pwmDuty) / 100;
    else if ( pwmChannel == 5 ) CCPR5L = ((PRx + 1) * pwmDuty) / 100;

    /* Timer and PR Settings */
    if ( pwmTimer == 2 ) {
        T2CON = 0; // No pre-scalar, timer2 is off
        TMR2 = 0; // Clear Timer6 initially
        T2CONbits.T2CKPS = TxCKPS; // Set TxCKPS Prescale Value Bits
        T2CONbits.TMR2ON = pwmStatus; // Timer ON for start counting
        PR2 = PRx; // Set period register
    }
    else if ( pwmTimer == 4 ) {
        T4CON = 0; // No pre-scalar, timer2 is off
        TMR4 = 0; // Clear Timer6 initially
        T4CONbits.T4CKPS = TxCKPS; // Set TxCKPS Prescale Value Bits
        T4CONbits.TMR4ON = pwmStatus; // Timer ON for start counting
        PR4 = PRx; // Set period register
    }
    if ( pwmTimer == 6 ) {
        T6CON = 0; // No pre-scalar, timer2 is off
        TMR6 = 0; // Clear Timer6 initially
        T6CONbits.T6CKPS = TxCKPS; // Set TxCKPS Prescale Value Bits
        T6CONbits.TMR6ON = pwmStatus; // Timer ON for start counting
        PR6 = PRx; // Set period register
    }
}

void pwmInitAll() {
    for ( byte i = 0; i < 5; i++ ) {
        pwmInit(i);
    }
}

void pwmSetDuty(byte pwmNo, byte duty) {
    pwms[pwmNo].duty = duty;
    pwmInit(pwmNo);
}

void pwmSetFreq(byte pwmNo, dword freq) {
    pwms[pwmNo].freq = freq;
    pwmInit(pwmNo);
}

void pwmSetStatus(byte pwmNo, byte status) {
    pwms[pwmNo].flag = (pwms[pwmNo].flag & ~(pwm_statusBitSize << pwm_statusBitRank)) | (status << pwm_statusBitRank);
    pwmInit(pwmNo);
}

void pwmSetCh(byte pwmNo, byte channel) {
    pwms[pwmNo].flag = (pwms[pwmNo].flag & ~(pwm_chBitSize << pwm_chBitRank)) | (channel << pwm_chBitRank);
    pwmInit(pwmNo);
}

void pwmSetTimer(byte pwmNo, byte timer) {
    pwms[pwmNo].flag = (pwms[pwmNo].flag & ~(pwm_timerBitSize << pwm_timerBitRank)) | (timer << pwm_timerBitRank);
    pwmInit(pwmNo);
}
