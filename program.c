#include <stdlib.h>
#include "stm32f7xx_fmc.h"
#include "stm32f7xx_gpio.h"
#include "stm32f7xx_rcc.h"
#include "stm32f7xx_hal.h"

/* Function for initializing SPI in master mode */
void spi_init() {
    // Configuring SPI 1
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // timing of port A
    // РA.5, 6, 7 => alternative function AF5 (SPI)
    GPIOA->AFR[0] |= 0x00000555;
    U0CTL = CHAR+SYNC+MM+SWRST; // 8 bits, SPI, master
    U0TCTL |= SSEL1+STC; // SMCLK, 3-wire
    U0BR0 = 0x00, U0BR1 = 0x01; // frequency is SMCLK/4
    U0MCTL = 0x00; // bits of modulation
    ME2 |= USPIE0; // SPI module on
    U0CTL &= ~SWRST; // enable SPI

    // Configuring output of PA.4 port (for SS signal)  
    // output rate is 50 MHz
    GPIOA->CRL |= (GPIO_CRL_MODE4_0 GPIO_CRL_MODE4_1);  
    // push-pull output mode of alternative function
    GPIOA->CRL |= (!GPIO_CRL_CNF4_0 GPIO_CRL_CNF4_1);
    // Setting zero on PA.4
    GPIOA->BSRR |= GPIO_BSRR_BR4;
    
    // Configuring SPI 4
    RCC->APB2ENR |= RCC_APB2ENR_IOPEEN; // timing of port E
    // РE.2, 5, 6 => alternative function AF5 (SPI)
    GPIOE->AFR[0] |= 0x05500500;
    U1CTL = CHAR+SYNC+MM+SWRST; // 8 bits, SPI, master
    U1TCTL |= SSEL1+STC; // SMCLK, 3-wire
    U1BR0 = 0x00, U1BR1 = 0x01; // frequency is SMCLK/4
    U1MCTL = 0x00; // bits of modulation
    ME2 |= USPIE1; // SPI module on
    U1CTL &= ~SWRST; // enable SPI

    // Configuring output of PE.4 port (for SS signal)  
    // output rate is 50 MHz
    GPIOE->CRL |= (GPIO_CRL_MODE4_0 GPIO_CRL_MODE4_1);  
    // push-pull output mode of alternative function
    GPIOE->CRL |= (!GPIO_CRL_CNF4_0 GPIO_CRL_CNF4_1);
    // Setting zero on PE.4
    GPIOE->BSRR |= GPIO_BSRR_BR4;   

    // Configuring SPI 5
    RCC->APB2ENR |= RCC_APB2ENR_IOPFEN; // timing of port F
    // РF.7, 8, 9 => alternative function AF5 (SPI)
    GPIOF->AFR[0] |= 0x50000000;
    GPIOF->AFR[1] |= 0x00000055;
    U2CTL = CHAR+SYNC+MM+SWRST; // 8 bits, SPI, master
    U2TCTL |= SSEL1+STC; // SMCLK, 3-wire
    U2BR0 = 0x00, U2BR1 = 0x01; // frequency is SMCLK/4
    U2MCTL = 0x00; // bits of modulation
    ME2 |= USPIE2; // SPI module on
    U2CTL &= ~SWRST; // enable SPI

    // Configuring output of PF.6 port (for SS signal)  
    // output rate is 50 MHz
    GPIOF->CRL |= (GPIO_CRL_MODE6_0 GPIO_CRL_MODE6_1);  
    // push-pull output mode of alternative function
    GPIOF->CRL |= (!GPIO_CRL_CNF6_0 GPIO_CRL_CNF6_1);
    // Setting zero on PF.6
    GPIOF->BSRR |= GPIO_BSRR_BR6;   

    // Configuring SPI 6
    RCC->APB2ENR |= RCC_APB2ENR_IOPGEN; // timing of port G
    // РG.12, 13, 14 => alternative function AF5 (SPI)
    GPIOF->AFR[1] |= 0x05550000;
    U3CTL = CHAR+SYNC+MM+SWRST; // 8 bits, SPI, master
    U3TCTL |= SSEL1+STC; // SMCLK, 3-wire
    U3BR0 = 0x00, U3BR1 = 0x01; // frequency is SMCLK/4
    U3MCTL = 0x00; // bits of modulation
    ME2 |= USPIE3; // SPI module on
    U3CTL &= ~SWRST; // enable SPI

    // Configuring output of PG.8 port (for SS signal)  
    // output rate is 50 MHz
    GPIOG->CRL |= (GPIO_CRL_MODE8_0 GPIO_CRL_MODE8_1);  
    // push-pull output mode of alternative function
    GPIOG->CRL |= (!GPIO_CRL_CNF8_0 GPIO_CRL_CNF8_1);
    // Setting zero on PG.8
    GPIOG->BSRR |= GPIO_BSRR_BR8;       
}

/* Function for initializing SPI in slave mode */
void spi_init() {

    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // timing of port A
    // РA.5, 6, 7 => alternative function AF5 (SPI)
    GPIOA->AFR[0] |= 0x00000555;
    U0CTL = CHAR+SYNC+SWRST; // 8 bits, SPI, slave
    U0TCTL |= SSEL1+STC; // SMCLK, 3-пров.
    U0BR0 = 0x00, U0BR1 = 0x01; // frequency is SMCLK/4
    U0MCTL = 0x00; // bits of modulation
    ME2 |= USPIE0; // SPI module on
    U0CTL &= ~SWRST; // enable SPI

    // Configuring input of PA.4 port (for SS signal)   
    GPIOA->CRL |= !(GPIO_CRL_MODE4_0 GPIO_CRL_MODE4_1); 
    // floating input mode
    GPIOA->CRL |= (!GPIO_CRL_CNF4_0 GPIO_CRL_CNF4_1);
    
    // Configuring SPI 4
    RCC->APB2ENR |= RCC_APB2ENR_IOPEEN; // timing of port E
    // РE.2, 5, 6 => alternative function AF5 (SPI)
    GPIOE->AFR[0] |= 0x05500500;
    U1CTL = CHAR+SYNC+SWRST; // 8 bits, SPI, slave
    U1TCTL |= SSEL1+STC; // SMCLK, 3-wire
    U1BR0 = 0x00, U1BR1 = 0x01; // frequency is SMCLK/4
    U1MCTL = 0x00; // bits of modulation
    ME2 |= USPIE1; // SPI module on
    U1CTL &= ~SWRST; // enable SPI

    // Configuring input of PE.4 port (for SS signal)   
    GPIOE->CRL |= !(GPIO_CRL_MODE4_0 GPIO_CRL_MODE4_1); 
    // floating input mode
    GPIOE->CRL |= (!GPIO_CRL_CNF4_0 GPIO_CRL_CNF4_1);   

    // Configuring SPI 5
    RCC->APB2ENR |= RCC_APB2ENR_IOPFEN; // timing of port F
    // РF.7, 8, 9 => alternative function AF5 (SPI)
    GPIOF->AFR[0] |= 0x50000000;
    GPIOF->AFR[1] |= 0x00000055;
    U2CTL = CHAR+SYNC+SWRST; // 8 bits, SPI, slave
    U2TCTL |= SSEL1+STC; // SMCLK, 3-wire
    U2BR0 = 0x00, U2BR1 = 0x01; // frequency is SMCLK/4
    U2MCTL = 0x00; // bits of modulation
    ME2 |= USPIE2; // SPI module on
    U2CTL &= ~SWRST; // enable SPI

    // Configuring input of PF.6 port (for SS signal)       
    GPIOF->CRL |= !(GPIO_CRL_MODE6_0 GPIO_CRL_MODE6_1); 
    // floating input mode
    GPIOF->CRL |= (!GPIO_CRL_CNF6_0 GPIO_CRL_CNF6_1);

    // Configuring SPI 6
    RCC->APB2ENR |= RCC_APB2ENR_IOPGEN; // timing of port G
    // РG.12, 13, 14 => alternative function AF5 (SPI)
    GPIOF->AFR[1] |= 0x05550000;
    U3CTL = CHAR+SYNC+SWRST; // 8 bits, SPI, slave
    U3TCTL |= SSEL1+STC; // SMCLK, 3-wire
    U3BR0 = 0x00, U3BR1 = 0x01; // frequency is SMCLK/4
    U3MCTL = 0x00; // bits of modulation
    ME2 |= USPIE3; // SPI module on
    U3CTL &= ~SWRST; // enable SPI

    // Configuring input of PG.8 port (for SS signal)       
    GPIOG->CRL |= !(GPIO_CRL_MODE8_0 GPIO_CRL_MODE8_1); 
    // floating input mode
    GPIOG->CRL |= (!GPIO_CRL_CNF8_0 GPIO_CRL_CNF8_1);
}

/* Function for data packet transmission through SPI in master mode */
int spi_send(short *buf, int size, int port) {

    volatile int i;

    if(port == 0) { // SPI 1        

        for(i = 0; i < size; i++) {
            // write low byte from (buf + i) address to the buffer
            U0TXBUF = ((*(buf + i))>>8) & 0xFF; 
            // wait for transmission buffer availability
            while (!(IFG2 & UTXIFG0)); 
            // write high byte from (buf + i) address to the buffer
            U0TXBUF = (*(buf + i)) & 0xFF; 
            // wait for transmission buffer availability
            while (!(IFG2 & UTXIFG0));
        }

        // write word 1 of packet ending to the buffer
        U0TXBUF = 0xAA; 
        // wait for transmission buffer availability
        while (!(IFG2 & UTXIFG0));

        // write word 2 of packet ending to the buffer
        U0TXBUF = 0xBB; 
        // wait for transmission buffer availability
        while (!(IFG2 & UTXIFG0));

        // setting one at PA.4 (end of session)
        GPIOA->BSRR |= GPIO_BSRR_BS4;

        for(i = 0; i < 10; i++); // delay for approximately 50 ns

        // setting zero at PA.4 (start of session)
        GPIOA->BSRR |= GPIO_BSRR_BR4;

        return 0;

    } else if (port == 1) { // SPI 4

        for(i = 0; i < size; i++) {
            // write low byte from (buf + i) address to the buffer
            U1TXBUF = ((*(buf + i))>>8) & 0xFF; 
            // wait for transmission buffer availability
            while (!(IFG2 & UTXIFG1)); 
            // write high byte from (buf + i) address to the buffer
            U1TXBUF = (*(buf + i)) & 0xFF; 
            // wait for transmission buffer availability
            while (!(IFG2 & UTXIFG1)); 
        }

        // write word 1 of packet ending to the buffer
        U1TXBUF = 0xAA; 
        // wait for transmission buffer availability
        while (!(IFG2 & UTXIFG1));

        // write word 2 of packet ending to the buffer
        U1TXBUF = 0xBB; 
        // wait for transmission buffer availability
        while (!(IFG2 & UTXIFG1));

        // setting one at PE.4 (end of session)
        GPIOE->BSRR |= GPIO_BSRR_BS4;

        for(i = 0; i < 10; i++); // delay for approximately 50 ns

        // setting zero at PE.4 (start of session)
        GPIOE->BSRR |= GPIO_BSRR_BR4;

        return 0;

    } else if (port == 2) { // SPI 5

        for(i = 0; i < size; i++) {
            // write low byte from (buf + i) address to the buffer
            U2TXBUF = ((*(buf + i))>>8) & 0xFF; 
            // wait for transmission buffer availability
            while (!(IFG2 & UTXIFG2)); 
            // write high byte from (buf + i) address to the buffer
            U2TXBUF = (*(buf + i)) & 0xFF; 
            // wait for transmission buffer availability
            while (!(IFG2 & UTXIFG2)); 
        }

        // write word 1 of packet ending to the buffer
        U2TXBUF = 0xAA; 
        // wait for transmission buffer availability
        while (!(IFG2 & UTXIFG2));

        // write word 2 of packet ending to the buffer
        U2TXBUF = 0xBB; 
        // wait for transmission buffer availability
        while (!(IFG2 & UTXIFG2));

        // setting one at PF.6 (end of session)
        GPIOF->BSRR |= GPIO_BSRR_BS6;

        for(i = 0; i < 10; i++); // delay for approximately 50 ns
    
        // setting zero at PF.6 (start of session)
        GPIOF->BSRR |= GPIO_BSRR_BR6;

        return 0;

    } else if (port == 3) { // SPI 6

        for(i = 0; i < size; i++) {
            // write low byte from (buf + i) address to the buffer
            U3TXBUF = ((*(buf + i))>>8) & 0xFF; 
            // wait for transmission buffer availability
            while (!(IFG2 & UTXIFG3)); 
            // write high byte from (buf + i) address to the buffer
            U3TXBUF = (*(buf + i)) & 0xFF; 
            // wait for transmission buffer availability
            while (!(IFG2 & UTXIFG3)); 
        }

        // write word 1 of packet ending to the buffer
        U3TXBUF = 0xAA; 
        // wait for transmission buffer availability
        while (!(IFG2 & UTXIFG3));

        // write word 2 of packet ending to the buffer
        U3TXBUF = 0xBB; 
        // wait for transmission buffer availability
        while (!(IFG2 & UTXIFG3));

        // setting one at PG.8 (end of session)
        GPIOG->BSRR |= GPIO_BSRR_BS8;

        for(i = 0; i < 10; i++); // delay for approximately 50 ns
        
        // setting zero at PG.8 (start of session)
        GPIOG->BSRR |= GPIO_BSRR_BR8;

        return 0;

    } else {

        return 1;
    }
}

/* Function for data packet transmission through SPI in slave mode */
int spi_send(short *buf, int size, int port) {

    if(port == 0) { // SPI 1        

        // wait for SS line to get in a low logical level
        while(GPIOA->IDR & 0x0010 != 0);

        for(i = 0; i < size; i++) {
            // write low byte from (buf + i) address to the buffer
            U0TXBUF = ((*(buf + i))>>8) & 0xFF; 
            // wait for transmission buffer availability
            while (!(IFG2 & UTXIFG0)); 
            // write high byte from (buf + i) address to the buffer
            U0TXBUF = (*(buf + i)) & 0xFF; 
            // wait for transmission buffer availability
            while (!(IFG2 & UTXIFG0)); 
        }

        // write word 1 of packet ending to the buffer
        U0TXBUF = 0xAA; 
        // wait for transmission buffer availability
        while (!(IFG2 & UTXIFG0));

        // write word 2 of packet ending to the buffer
        U0TXBUF = 0xBB; 
        // wait for transmission buffer availability
        while (!(IFG2 & UTXIFG0));

        // wait for SS line to get in a high logical level
        while(GPIOA->IDR & 0x0010 != 1);

        return 0;

    } else if (port == 1) { // SPI 4

        // wait for SS line to get in a low logical level
        while(GPIOE->IDR & 0x0010 != 0);

        for(i = 0; i < size; i++) {
            // write low byte from (buf + i) address to the buffer
            U1TXBUF = ((*(buf + i))>>8) & 0xFF; 
            // wait for transmission buffer availability
            while (!(IFG2 & UTXIFG1)); 
            // write high byte from (buf + i) address to the buffer
            U1TXBUF = (*(buf + i)) & 0xFF; 
            // wait for transmission buffer availability
            while (!(IFG2 & UTXIFG1)); 
        }

        // write word 1 of packet ending to the buffer
        U1TXBUF = 0xAA; 
        // wait for transmission buffer availability
        while (!(IFG2 & UTXIFG1));

        // write word 2 of packet ending to the buffer
        U1TXBUF = 0xBB; 
        // wait for transmission buffer availability
        while (!(IFG2 & UTXIFG1));

        // wait for SS line to get in a high logical level
        while(GPIOE->IDR & 0x0010 != 1);

        return 0;

    } else if (port == 2) { // SPI 5

        // wait for SS line to get in a low logical level
        while(GPIOF->IDR & 0x0040 != 0);

        for(i = 0; i < size; i++) {
            // write low byte from (buf + i) address to the buffer
            U2TXBUF = ((*(buf + i))>>8) & 0xFF; 
            // wait for transmission buffer availability
            while (!(IFG2 & UTXIFG2)); 
            // write high byte from (buf + i) address to the buffer
            U2TXBUF = (*(buf + i)) & 0xFF; 
            // wait for transmission buffer availability
            while (!(IFG2 & UTXIFG2)); 
        }

        // write word 1 of packet ending to the buffer
        U2TXBUF = 0xAA; 
        // wait for transmission buffer availability
        while (!(IFG2 & UTXIFG2));

        // write word 2 of packet ending to the buffer
        U2TXBUF = 0xBB; 
        // wait for transmission buffer availability
        while (!(IFG2 & UTXIFG2));

        // wait for SS line to get in a high logical level
        while(GPIOF->IDR & 0x0040 != 1);

        return 0;

    } else if (port == 3) { // SPI 6

        // wait for SS line to get in a low logical level
        while(GPIOG->IDR & 0x0100 != 0);

        for(i = 0; i < size; i++) {
            // write low byte from (buf + i) address to the buffer
            U3TXBUF = ((*(buf + i))>>8) & 0xFF; 
            // wait for transmission buffer availability
            while (!(IFG2 & UTXIFG3)); 
            // write high byte from (buf + i) address to the buffer
            U3TXBUF = (*(buf + i)) & 0xFF; 
            // wait for transmission buffer availability
            while (!(IFG2 & UTXIFG3)); 
        }

        // write word 1 of packet ending to the buffer
        U3TXBUF = 0xAA; 
        // wait for transmission buffer availability
        while (!(IFG2 & UTXIFG3));

        // write word 2 of packet ending to the buffer
        U3TXBUF = 0xBB; 
        // wait for transmission buffer availability
        while (!(IFG2 & UTXIFG3));

        // wait for SS line to get in a high logical level
        while(GPIOG->IDR & 0x0100 != 1);

        return 0;

    } else {

        return 1;
    }
}

/* Function for data packet reception through SPI in master mode */
int spi_receive(short *buf, int port) {

    int i = 0; // variable for counter
    char cur; // high byte of data
    char prev; // low byte of data
    short temp; // two-byte word of data

    if(port == 0) { // SPI 1        

        while(1) {

            while (!(IFG2 & URXIFG0));  // wait for reception buffer availability
            prev = U0RXBUF;             // low byte of data reception
            while (!(IFG2 & URXIFG0));  // wait for reception buffer availability
            cur = U0RXBUF;              // high byte of data reception

            if (prev == 0xAA && cur == 0xBB)
                break;
            else {

                temp = cur; // high byte copying
                temp = temp << 8; // high byte shifting
                temp = temp | prev; // low byte copying

                *(buf + i) = temp; // write word of data in memory

                i++;
            }
        }

        // setting one at PA.4 (end of session)
        GPIOA->BSRR |= GPIO_BSRR_BS4;

        for(i = 0; i < 10; i++); // delay for approximately 50 ns

        // setting zero at PA.4 (start of session)
        GPIOA->BSRR |= GPIO_BSRR_BR4;

        return i;

    } else if (port == 1) { // SPI 4

        while(1) {

            while (!(IFG2 & URXIFG1));  // wait for reception buffer availability
            prev = U1RXBUF;             // low byte of data reception
            while (!(IFG2 & URXIFG1));  // wait for reception buffer availability
            cur = U1RXBUF;              // high byte of data reception

            if (prev == 0xAA && cur == 0xBB)
                break;
            else {

                temp = cur; // high byte copying
                temp = temp << 8; // high byte shifting
                temp = temp | prev; // low byte copying

                *(buf + i) = temp; // write word of data in memory

                i++;
            }
        }

        // setting one at PE.4 (end of session)
        GPIOE->BSRR |= GPIO_BSRR_BS4;

        for(i = 0; i < 10; i++); // delay for approximately 50 ns

        // setting zero at PE.4 (start of session)
        GPIOE->BSRR |= GPIO_BSRR_BR4;

        return i;

    } else if (port == 2) { // SPI 5

        while(1) {

            while (!(IFG2 & URXIFG2));  // wait for reception buffer availability
            prev = U2RXBUF;             // low byte of data reception
            while (!(IFG2 & URXIFG2));  // wait for reception buffer availability
            cur = U2RXBUF;              // high byte of data reception

            if (prev == 0xAA && cur == 0xBB)
                break;
            else {

                temp = cur; // high byte copying
                temp = temp << 8; // high byte shifting
                temp = temp | prev; // low byte copying

                *(buf + i) = temp; // write word of data in memory

                i++;
            }
        }

        // setting one at PF.6 (end of session)
        GPIOF->BSRR |= GPIO_BSRR_BS6;

        for(i = 0; i < 10; i++); // delay for approximately 50 ns
    
        // setting zero at PF.6 (start of session)
        GPIOF->BSRR |= GPIO_BSRR_BR6;

        return i;

    } else if (port == 3) { // SPI 6

        while(1) {

            while (!(IFG2 & URXIFG3));  // wait for reception buffer availability
            prev = U3RXBUF;             // low byte of data reception
            while (!(IFG2 & URXIFG3));  // wait for reception buffer availability
            cur = U3RXBUF;              // high byte of data reception

            if (prev == 0xAA && cur == 0xBB)
                break;
            else {

                temp = cur; // high byte copying
                temp = temp << 8; // high byte shifting
                temp = temp | prev; // low byte copying

                *(buf + i) = temp; // write word of data in memory

                i++;
            }
        }

        // setting one at PG.8 (end of session)
        GPIOG->BSRR |= GPIO_BSRR_BS8;

        for(i = 0; i < 10; i++); // delay for approximately 50 ns
        
        // setting zero at PG.8 (start of session)
        GPIOG->BSRR |= GPIO_BSRR_BR8;

        return i;

    } else {

        return 0;
    }
}

/* Function for data packet reception through SPI in slave mode */
int spi_receive(short *buf, int port) {
    
    int i = 0; // variable for counter
    char cur; // high byte of data
    char prev; // low byte of data
    short temp; // two-byte word of data

    if(port == 0) { // SPI 1    

        // wait for SS line to get in a low logical level
        while(GPIOA->IDR & 0x0010 != 0);    

        while(1) {

            while (!(IFG2 & URXIFG0));  // wait for reception buffer availability
            prev = U0RXBUF;             // low byte of data reception
            while (!(IFG2 & URXIFG0));  // wait for reception buffer availability
            cur = U0RXBUF;              // high byte of data reception

            if (prev == 0xAA && cur == 0xBB)
                break;
            else {

                temp = cur; // high byte copying
                temp = temp << 8; // high byte shifting
                temp = temp | prev; // low byte copying

                *(buf + i) = temp; // write word of data in memory

                i++;
            }
        }

        // wait for SS line to get in a high logical level
        while(GPIOA->IDR & 0x0010 != 1);

        return i;

    } else if (port == 1) { // SPI 4

        // wait for SS line to get in a low logical level
        while(GPIOE->IDR & 0x0010 != 0);

        while(1) {

            while (!(IFG2 & URXIFG1));  // wait for reception buffer availability
            prev = U1RXBUF;             // low byte of data reception
            while (!(IFG2 & URXIFG1));  // wait for reception buffer availability
            cur = U1RXBUF;              // high byte of data reception

            if (prev == 0xAA && cur == 0xBB)
                break;
            else {

                temp = cur; // high byte copying
                temp = temp << 8; // high byte shifting
                temp = temp | prev; // low byte copying

                *(buf + i) = temp; // write word of data in memory

                i++;
            }
        }

        // wait for SS line to get in a high logical level
        while(GPIOE->IDR & 0x0010 != 1);

        return i;

    } else if (port == 2) { // SPI 5

        // wait for SS line to get in a low logical level
        while(GPIOF->IDR & 0x0040 != 0);

        while(1) {

            while (!(IFG2 & URXIFG2));  // wait for reception buffer availability
            prev = U2RXBUF;             // low byte of data reception
            while (!(IFG2 & URXIFG2));  // wait for reception buffer availability
            cur = U2RXBUF;              // high byte of data reception

            if (prev == 0xAA && cur == 0xBB)
                break;
            else {

                temp = cur; // high byte copying
                temp = temp << 8; // high byte shifting
                temp = temp | prev; // low byte copying

                *(buf + i) = temp; // write word of data in memory

                i++;
            }
        }

        // wait for SS line to get in a high logical level
        while(GPIOF->IDR & 0x0040 != 1);

        return i;

    } else if (port == 3) { // SPI 6

        // wait for SS line to get in a low logical level
        while(GPIOG->IDR & 0x0100 != 0);

        while(1) {

            while (!(IFG2 & URXIFG3));  // wait for reception buffer availability
            prev = U3RXBUF;             // low byte of data reception
            while (!(IFG2 & URXIFG3));  // wait for reception buffer availability
            cur = U3RXBUF;              // high byte of data reception

            if (prev == 0xAA && cur == 0xBB)
                break;
            else {

                temp = cur; // high byte copying
                temp = temp << 8; // high byte shifting
                temp = temp | prev; // low byte copying

                *(buf + i) = temp; // write word of data in memory

                i++;
            }
        }

        // wait for SS line to get in a high logical level
        while(GPIOG->IDR & 0x0100 != 1);

        return i;

    } else {

        return 0;
    }
}

/* Function for reception of SPI port number that connects this executive
   node with executive node that is closest by its spatial address */
int route(char dest_address) {

    int i;
    // spatial addresses of neighbouring executive nodes
    unsigned char neighbours[4] = {0x14, 0x02, 0x04, 0x07};
    // spatial address of this executive node
    unsigned char cur_addr = 0x06;
    unsigned char temp, min = 5;
    // Hamming distance
    unsigned char hem_dist[4] = {0, 0, 0, 0};

    int port = -1;

    if(dest_address == cur_addr)
        return port;

    // performing a cycle for 4 ports
    for(i = 0; i < 4; i++) {

        temp = neighbours[i] ^ dest_address;

        // calculating of Hamming distance
        for(j = 0; j < 4; j++) {

            if(temp & 0x01)
                hem_dist[i]++;

            temp = temp >> 1;
        }

        // comparing with minimal Hamming distance
        if(hem_dist[i] < min) {

            port = i;
            min = hem_dist[i];
        }
    }

    return port;
}

/* Function for FMC module initializing and configuring */
void fmc_init() {

    SRAM_HandleTypeDef sramHandle;
    FMC_SRAM_TimingTypeDef FMC_SRAM;
    GPIO_InitTypeDef GPIO_InitStructure;

    sramHandle.Instance = FMC_SRAM_DEVICE;
    sramHandle.Extended = FMC_SRAM_EXTENDED_DEVICE;

    /* FMC time delays configuring */
    FMC_SRAM.AddressSetupTime = 0; // 0 нс
    FMC_SRAM.AddressHoldTime = 40;
    FMC_SRAM.DataSetupTime = 15;
    FMC_SRAM.DataLatency = 15;
    FMC_SRAM.AccessMode = FMC_ACCESS_MODE_A;

    sramHandle.Init.NSBank = FMC_SRAM_BANK1;
    sramHandle.Init.DataAddressMux = FMC_DATA_ADDRESS_MUX_DISABLE;
    sramHandle.Init.MemoryType = FMC_MEMORY_TYPE_SRAM;
    sramHandle.Init.MemoryDataWidth = FMC_SRAM_MEM_BUS_WIDTH_16;

    // ports configuring
    // enable timing of AHB1 bus for ports
    RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE
        | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG, ENABLE);

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // push-pull mode
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL; // floating output,
                                                      // without pull-up resistor

    /* PD, PE, PF, PG
    A0   - PF0               D0  - PD14  
    A1   - PF1               D1  - PD15  
    A2   - PF2               D2  - PD0   
    A3   - PF3               D3  - PD1   
    A4   - PF4               D4  - PE7   
    A5   - PF5               D5  - PE8   
    A6   - PF12              D6  - PE9   
    A7   - PF13              D7  - PE10  
    A8   - PF14              D8  - PE11  
    A9   - PF15              D9  - PE12  
    A10  - PG0               D10 - PE13  
    A11  - PG1               D11 - PE14  
    A12  - PG2               D12 - PE15  
                             D13 - PD8   
                             D14 - PD9   
                             D15 - PD10  
                            
    NOE  - PD4 
    NWE  - PD5     
    NBL0 - PE0   
    NBL1 - PE1   
    
    PD0, PD1, PD4, PD5, PD7, PD8, PD9, PD10, PD14, PD15
    PE0, PE1, PE7, PE8, PE9, PE10, PE11, PE12, PE13, PE14, PE15
    PF0, PF1, PF2, PF3, PF4, PF5, PF12, PF13, PF14, PF15
    PG0, PG1, PG2
    */   

    // GPIOD: PD0, PD1, PD4, PD5, PD8, PD9, PD10, PD14, PD15
    GPIO_PinAFConfig (GPIOD, GPIO_PinSource0, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOD, GPIO_PinSource1, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOD, GPIO_PinSource4, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOD, GPIO_PinSource5, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOD, GPIO_PinSource8, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOD, GPIO_PinSource9, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOD, GPIO_PinSource10, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOD, GPIO_PinSource14, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOD, GPIO_PinSource15, GPIO_AF_FMC);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
    GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;

    GPIO_Init (GPIOD, &GPIO_InitStructure);

    // GPIOE: PE0, PE1, PE7, PE8, PE9, PE10, PE11, PE12, PE13, PE14, PE15
    GPIO_PinAFConfig (GPIOE, GPIO_PinSource0, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOE, GPIO_PinSource1, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOE, GPIO_PinSource7, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOE, GPIO_PinSource8, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOE, GPIO_PinSource9, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOE, GPIO_PinSource10, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOE, GPIO_PinSource11, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOE, GPIO_PinSource12, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOE, GPIO_PinSource13, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOE, GPIO_PinSource14, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOE, GPIO_PinSource15, GPIO_AF_FMC);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_7 | GPIO_Pin_8 |
    GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |
    GPIO_Pin_15;

    GPIO_Init (GPIOE, &GPIO_InitStructure);

    // GPIOF: PF0, PF1, PF2, PF3, PF4, PF5, PF12, PF13, PF14, PF15
    GPIO_PinAFConfig (GPIOF, GPIO_PinSource0, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOF, GPIO_PinSource1, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOF, GPIO_PinSource2, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOF, GPIO_PinSource3, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOF, GPIO_PinSource4, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOF, GPIO_PinSource5, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOF, GPIO_PinSource12, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOF, GPIO_PinSource13, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOF, GPIO_PinSource14, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOF, GPIO_PinSource15, GPIO_AF_FMC);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
    GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;

    GPIO_Init (GPIOF, &GPIO_InitStructure);

    // GPIOG: PG0, PG1, PG2
    GPIO_PinAFConfig (GPIOG, GPIO_PinSource0, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOG, GPIO_PinSource1, GPIO_AF_FMC);
    GPIO_PinAFConfig (GPIOG, GPIO_PinSource2, GPIO_AF_FMC);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;

    GPIO_Init (GPIOG, &GPIO_InitStructure);
}

/* Function for data packet transmission through Ethernet */
void eth_send(short *buf, int size) {

    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // timing of port A
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // timing of port B
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // timing of port C
    // РA.0 => alternative function
    GPIOA->AFR[0] |= 0x00000007;
    // РB.10, 11, 12, 13 => alternative functions
    GPIOB->AFR[1] |= 0x00896800;
    // РС.3, 4, 5 => alternative functions
    GPIOC->AFR[0] |= 0x00364000;

    // reset Ethernet settings to initial state
    ETH_DeInit();
    
    // software reset of Ethernet
    ETH_softwareReset();
    
    // wait for acknowledgement of Ethernet reset
    while(ETH_GetSoftwareResetStatus() == SET);

    ETH_InitTypeDef ETH_InitStructure;

    // configuring Ethernet
    ETH_StructInit(&ETH_InitStructure);

    // setting parameters ETH_InitStructure
    ETH_InitStructure.ETH_AutoNegotiation = ETH_AutoNegotiation_Enable;
    ETH_InitStructure.ETH_Speed = ETH_Speed_100M;
    ETH_InitStructure.ETH_LoopbackMode = ETH_LoopbackMode_Disable;
    ETH_InitStructure.ETH_Mode = ETH_Mode_FullDuplex;

    // enable reception from all MAC-addresses
    ETH_InitStructure.ETH_ReceiveAll = ETH_ReceiveAll_Enable;

    // parameters initialization
    Value = ETH_Init(&ETH_InitStructure, PHY_ADDRESS);

    // descriptors
    ETH_DMADESCTypeDef DMARxDscrTab[ETH_RXBUFNB], DMATxDscrTab[ETH_TXBUFNB];
    
    // array of reception and transmission of data buffers,
    // that descriptors will refer to
    int RxBuff[ETH_RXBUFNB][ETH_MAX_PACKET_SIZE];
    int Tx_Buff[ETH_TXBUFNB][ETH_MAX_PACKET_SIZE];

    // writing parameters of descriptors (pointers to the buffer
    // and to the next descriptor)
    ETH_DMATxDescChainInit(DMATxDscrTab, &Tx_Buff[0][0], ETH_TXBUFNB);

    // writing length of buffer to descriptor
    DMATxDscrTab->ControlBufferSize = size * 2;

    // start of Ethernet
    ETH_START();

    // check if previous packet is sent
    if((DMATxDscrTab->Status&ETH_DMARxDesc_OWN) == 0) {

        // turn off transmission
        ETH_DMATransmissionCmd(DISABLE);

        for(int i = 0; i < size; i += 2) {

            Tx_Buff[0][i] = *(buf + i) & 0xFF;
            Tx_Buff[0][i + 1] = *(buf + i) >> 8;
        }

        // transmit descriptor to DMA Ethernet
        DMATxDscrTab->Status = ETH_DMARxDesc_OWN | ETH_DMATxDesc_TCH |
        ETH_DMATxDesc_TTSE | ETH_DMATxDesc_LS | ETH_DMATxDesc_FS;
        // enable transmission
        ETH_DMATransmissionCmd(ENABLE);
    }
}

/* Function for data packet reception through Ethernet */
int eth_receive(short *buf, int size) {

    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // timing of port A
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // timing of port B
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // timing of port C
    // РA.0 => alternative function
    GPIOA->AFR[0] |= 0x00000007;
    // РB.10, 11, 12, 13 => alternative functions
    GPIOB->AFR[1] |= 0x00896800;
    // РС.3, 4, 5 => alternative functions
    GPIOC->AFR[0] |= 0x00364000;

    // reset Ethernet settings to initial state
    ETH_DeInit();
    
    // software reset of Ethernet
    ETH_softwareReset();
    
    // wait for acknowledgement of Ethernet reset
    while(ETH_GetSoftwareResetStatus() == SET);

    ETH_InitTypeDef ETH_InitStructure;

    // configuring Ethernet
    ETH_StructInit(&ETH_InitStructure);

    // setting parameters ETH_InitStructure
    ETH_InitStructure.ETH_AutoNegotiation = ETH_AutoNegotiation_Enable;
    ETH_InitStructure.ETH_Speed = ETH_Speed_100M;
    ETH_InitStructure.ETH_LoopbackMode = ETH_LoopbackMode_Disable;
    ETH_InitStructure.ETH_Mode = ETH_Mode_FullDuplex;

    // enable reception from all MAC-addresses
    ETH_InitStructure.ETH_ReceiveAll = ETH_ReceiveAll_Enable;

    // parameters initialization
    Value = ETH_Init(&ETH_InitStructure, PHY_ADDRESS);

    // descriptors
    ETH_DMADESCTypeDef DMARxDscrTab[ETH_RXBUFNB], DMATxDscrTab[ETH_TXBUFNB];
    
    // array of reception and transmission of data buffers,
    // that descriptors will refer to
    int RxBuff[ETH_RXBUFNB][ETH_MAX_PACKET_SIZE];
    int Tx_Buff[ETH_TXBUFNB][ETH_MAX_PACKET_SIZE];

    // writing parameters of descriptors
    (указатели на буфер и на следующий дескриптор)
    ETH_DMATxDescChainInit(DMATxDscrTab, &Tx_Buff[0][0], ETH_TXBUFNB);

    // writing length of buffer to descriptor
    DMATxDscrTab->ControlBufferSize = size * 2;

    // setting descriptors for reception
    ETH_DMARxDescChainInit(DMARxDscrTab, &Rx_Buff[0][0], ETH_RXBUFNB);
    DMARxDscrTab->ControlBufferSize = ETH_MAX_PACKET_SIZE | (1 << 14);

    // enable reception
    DMARxDscrTab->Status = ETH_DMARxDesc_OWN;

    // start Ethernet
    ETH_START();

    // Check if descriptor belongs to processor or application
    if((DMARxDscrTab->Status&ETH_DMARxDesc_OWN) == 0) {

        // turn off reception
        ETH_DMAReceptionCmd(DISABLE);

        // read data from buffer
        for(int i = 0; i < size; i += 2)
            *(buf + i / 2) = Rx_Buff[0][i] + (Rx_Buff[0][i + 1] << 8);
    }

    // transmit descriptor to DMA Ethernet
    DMARxDscrTab->Status = ETH_DMARxDesc_OWN;

    // enable reception
    ETH_DMAReceptionCmd(ENABLE);    
}

/* Function for selection a memory block of executive node using 2-to-4 decoder */
void line_select(int num) {

    RCC->APB2ENR |= RCC_APB2ENR_IOPDEN; // timing of port D
    RCC->APB2ENR |= RCC_APB2ENR_IOPGEN; // timing of port G

    // configuring output of port PD.7 (NE1)    
    // output rate is 50 MHz
    GPIOD->CRL |= (GPIO_CRL_MODE7_0 GPIO_CRL_MODE7_1);  
    // push-pull output mode of alternative function
    GPIOD->CRL |= (!GPIO_CRL_CNF7_0 GPIO_CRL_CNF7_1);

    // configuring output of port PG.9 (NE2)    
    // output rate is 50 MHz
    GPIOG->CRL |= (GPIO_CRL_MODE9_0 GPIO_CRL_MODE9_1);  
    // push-pull output mode of alternative function
    GPIOG->CRL |= (!GPIO_CRL_CNF9_0 GPIO_CRL_CNF9_1);

    // configuring output of port PG.10 (NE3)   
    // output rate is 50 MHz
    GPIOG->CRL |= (GPIO_CRL_MODE10_0 GPIO_CRL_MODE10_1);    
    // push-pull output mode of alternative function
    GPIOG->CRL |= (!GPIO_CRL_CNF10_0 GPIO_CRL_CNF10_1);

    // configuring output of port PG.12 (NE4)   
    // output rate is 50 MHz
    GPIOG->CRL |= (GPIO_CRL_MODE12_0 GPIO_CRL_MODE12_1);    
    // push-pull output mode of alternative function
    GPIOG->CRL |= (!GPIO_CRL_CNF12_0 GPIO_CRL_CNF12_1);

    if(num & 0x01 == 1)
        GPIOD->BSRR |= GPIO_BSRR_BS7; // setting high logical level
    else
        GPIOD->BSRR |= GPIO_BSRR_BR7; // setting low logical level

    if(num & 0x02 == 1)
        GPIOG->BSRR |= GPIO_BSRR_BS9; // setting high logical level
    else
        GPIOG->BSRR |= GPIO_BSRR_BR9; // setting low logical level

    if(num & 0x04 == 1)
        GPIOG->BSRR |= GPIO_BSRR_BS10; // setting high logical level
    else
        GPIOG->BSRR |= GPIO_BSRR_BR10; // setting low logical level

    if(num & 0x08 == 1)
        GPIOG->BSRR |= GPIO_BSRR_BS12; // setting high logical level
    else
        GPIOG->BSRR |= GPIO_BSRR_BR12; // setting low logical level
}

/* Structure for deincaps function */
typedef struct _ELEMENT {

    short subtask_num;
    short *res_addr;
    short res_size;
    struct _ELEMENT *prev;

} ELEMENT;

/* Function for task packet deincapsulation with creating a table
   "number of subtask-address of result-size of result-pointer to previous string"
   and filling arrays of command and data blocks */
ELEMENT* deincaps(short *address, short **command_blocks, short **data_blocks) {

    ELEMENT *link = NULL;
    ELEMENT *prev = NULL;
    short subtask_size;
    short com_block_size;
    short data_block_size;
    unsigned int bias_words = 1;

    for(int i = 0; i < 16; i++) {
        
        subtask_size = (*(address + bias_words) >> 8) & 0xFF + (*(address + 9) & 0x3F); 

        if(subtask_size == 0) {

            return link;
        } else {

            ELEMENT *temp = (ELEMENT*)malloc(sizeof(ELEMENT));

            temp->subtask_num = (*(address + bias_words + 1) >> 6) & 0x0F;
            temp->res_addr = (*(address + bias_words + 1) >> 10) & 0x3F \
            + (*(address + bias_words + 2) & 0x03FF);
            temp->res_size = (*(address + bias_words + 2) >> 10) & 0x3F \
            + (*(address + bias_words + 3) & 0x0F);
            temp->prev = prev;

            prev = temp;

            link = temp;

            com_block_size = ((*(address + bias_words + 3)) & 0x1FFF) / 2;
            short *command_block = (short*)malloc(sizeof(short) * com_block_size);

            for(int j = 0; j < com_block_size; j++)
                *(command_block + j) = *(address + bias_words + 4 + j);

            *command_blocks[i] = command_block;

            data_block_size = ((*(address + bias_words + 3 \
                + com_block_size)) & 0x1FFF) / 2;
            short *data_block = (short*)malloc(sizeof(short) * data_block_size);

            for(int j = 0; j < data_block_size; j++)
                *(data_block + j) = *(address + bias_words + 4 + com_block_size + j);

            *data_blocks[i] = data_block;
        }

        bias_words += subtask_size / 2;
    }

    return link;
}

/* Function for request memory blocks for presence at certain address
   the word that indicates end of subtask execution */
short completion() {

    // address that this word is located at
    short address = 0x1FFF; 
    short end_word = 0xAABB;
    short result = 0;

    short buf;

    for(int i = 0; i < 16; i++) {

        line_select(i);
        mem_read(&buf, 1, address);

        if(buf == 0xAABB)
            result += (0x0001 << i);
    }

    return result;
}

/* Function for assembling result of task using results of subtasks */
int result_form(ELEMENT *table, short *result) {

    ELEMENT *temp = table;
    ELEMENT *prev = NULL;
    int res_size = 0;
    int temp_res_size = 0;
    int i = 0;

    // obtain total size of result in bytes
    while(temp != NULL) {

        res_size += temp->res_size;
        temp = temp->prev;
    }

    temp = table;

    result = (short*)malloc(sizeof(short) * res_size / 2);

    while(temp != NULL) {

        temp_res_size = temp->res_size / 2;
        
        for(int j = 0; j < temp_res_size; j++)
            *(result + i + j) = *((temp->res_addr) + j);

        i += temp_res_size;
        temp = temp->prev;
    }

    return res_size / 2;
}