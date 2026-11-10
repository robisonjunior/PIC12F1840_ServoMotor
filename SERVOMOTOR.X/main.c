 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
© [2026] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"

// Controle da Posição: 0 = Posicao 0° (550us), 1 = Posicao 180° (2600us)
volatile uint8_t posicao_servo = 0; // Inicia em 0° ao ligar

// Interrupção do Timer1 executada a cada 20 ms (50 Hz)
void Servo_Pulse_Handler(void)
{
    IO_RA2_SetHigh();
    
    if (posicao_servo == 1)
    {
        __delay_us(2500); // Aumentado de 2400us para 2500us para atingir os 180° reais
       // __delay_us(1278); // 70° para sistema xtend
        
    }
    else
    {
        __delay_us(500);  // Ajustado para 550us para garantir o batente inicial de 0°
       // __delay_us(1500);  //  90° para sistema xtend
    }
    
    IO_RA2_SetLow();
}

int main(void)
{
    // Inicializa Clock (16MHz), Pinos e Timer1 (20 ms)
    SYSTEM_Initialize();

    // Garante que RA4 seja entrada digital pura
    IO_RA4_SetDigitalMode();
    IO_RA4_SetDigitalInput();

    // Habilita as interrupções Globais e Periféricas
    INTERRUPT_PeripheralInterruptEnable();
    INTERRUPT_GlobalInterruptEnable();

    // Registra o handler no Timer1 e inicia a contagem de 50 Hz
    TMR1_OverflowCallbackRegister(Servo_Pulse_Handler);
    TMR1_Start();

    while (1)
    {
        // Leitura do botão no pino RA4 (Pull-Up de 10k: pressionado = LOW / 0)
        if (IO_RA4_GetValue() == 0) 
        {
            __delay_ms(40); // Debounce por software
            
            if (IO_RA4_GetValue() == 0) 
            {
                // Alterna o estado (0 -> 1 -> 0)
                posicao_servo = !posicao_servo;

                // Aguarda soltar o botão antes de continuar
                while (IO_RA4_GetValue() == 0);
            }
        }
    }
}