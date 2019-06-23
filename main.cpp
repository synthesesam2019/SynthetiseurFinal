#include "mbed.h"
#include "AUDIO_DISCO_F746NG.h"
#include "SDRAM_DISCO_F746NG.h"
#include "math.h"
#include "stdint.h"
#include "bluetooth.h"
#include "Note.h"

AUDIO_DISCO_F746NG audio; //objet gestion audio
// audio IN_OUT buffer is stored in the SDRAM, SDRAM needs to be initialized and FMC enabled
SDRAM_DISCO_F746NG sdram; 

extern Serial PC;   //Communication série PC (affichage)
extern Serial HC06; //Communication BT
extern int Note;    //variable note MIDI
extern int x;       //variable taille du buffer
static uint8_t SetSysClock_PLL_HSE_200MHz(); 


int main()
{
   SetSysClock_PLL_HSE_200MHz();    
   
    //pc.baud(9600);
    read();     //Assigne la callback à l'interruption sur réception

    PC.printf("\n\nAUDIO LOOPBACK EXAMPLE START:\n\r");
    PC.printf("\nAUDIO RECORD INIT OK\n\r");
    PC.printf("Microphones sound streamed to headphones\n\r");

    /* Initialize SDRAM buffers */
    Init_note(); //Init buffers de notes

    /* Initialisation de la sortie audio */
    audio.OUT_SetAudioFrameSlot(CODEC_AUDIOFRAME_SLOT_02);
    audio.OUT_SetFrequency(44100);
    audio.OUT_SetVolume(80);    //Réglage du volume de sortie
    
    while (1) {
    }
}
/*-------------------------------------------------------------------------------------
       Callbacks implementation:
           the callbacks API are defined __weak in the stm32746g_discovery_audio.c file
           and their implementation should be done in the user code if they are needed.
           Below some examples of callback implementations.
  -------------------------------------------------------------------------------------*/
/**
  * @brief Manages the DMA Transfer complete interrupt.
  * @param None
  * @retval None
  */
void BSP_AUDIO_IN_TransferComplete_CallBack(void)
{
    //audio_rec_buffer_state = BUFFER_OFFSET_FULL;
    return;
}

/**
  * @brief  Manages the DMA Half Transfer complete interrupt.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_IN_HalfTransfer_CallBack(void)
{
 //   audio_rec_buffer_state = BUFFER_OFFSET_HALF;
    return;
}

static uint8_t SetSysClock_PLL_HSE_200MHz()
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;

    // Enable power clock
    __PWR_CLK_ENABLE();

    // Enable HSE oscillator and activate PLL with HSE as source
    RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState            = RCC_HSE_ON; /* External xtal on OSC_IN/OSC_OUT */

    // Warning: this configuration is for a 25 MHz xtal clock only
    RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM            = 25;            // VCO input clock = 1 MHz (25 MHz / 25)
    RCC_OscInitStruct.PLL.PLLN            = 400;           // VCO output clock = 400 MHz (1 MHz * 400)
    RCC_OscInitStruct.PLL.PLLP            = RCC_PLLP_DIV2; // PLLCLK = 200 MHz (400 MHz / 2)
    RCC_OscInitStruct.PLL.PLLQ            = 8;             // USB clock = 50 MHz (400 MHz / 8)

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        return 0; // FAIL
    }

    // Activate the OverDrive to reach the 216 MHz Frequency
    if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
        return 0; // FAIL
    }

    // Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers
    RCC_ClkInitStruct.ClockType      = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK; // 200 MHz
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;         // 200 MHz
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;           //  50 MHz
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;           // 100 MHz

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK) {
        return 0; // FAIL
    }
    HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSE, RCC_MCODIV_4);
    return 1; // OK
}

