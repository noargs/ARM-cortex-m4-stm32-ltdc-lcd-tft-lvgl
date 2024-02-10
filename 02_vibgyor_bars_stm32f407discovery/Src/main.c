#include <stdint.h>

#include "stm32f407xx.h"
#include "reg_util.h"

#include "bsp_lcd.h"

void SystemClock_Setup(void);

int main(void)
{

	for(;;);
}

void SystemClock_Setup(void)
{
  RCC_TypeDef* Rcc = RCC;
  FLASH_TypeDef* Flash = FLASH;
  PWR_TypeDef* Pwr = PWR;

  // 1. Program flash wait state  [RM page 80]
  REG_SET_VAL(Flash->ACR, 0x5U, 0x7U, FLASH_ACR_LATENCY_Pos);


  // 2. Over drive settings [DS page 79]
  REG_SET_BIT(Rcc->APB1ENR, RCC_APB1ENR_PWREN_Pos);                       // Enable clock for PWR register access
  REG_SET_BIT(Pwr->CR, PWR_CR_VOS_Pos);                                   // VOS=1 Regulator voltage scaling output selection


  // 3. Set up main PLL

  REG_SET_VAL(Rcc->PLLCFGR, 0x8U, 0x3FU, RCC_PLLCFGR_PLLM_Pos);           // PLL_M (M Divider must be  1MHz < fvco <= 2MHz) 16HSI/8 = 2MHz
  REG_SET_VAL(Rcc->PLLCFGR, 168U, 0x1FFU, RCC_PLLCFGR_PLLN_Pos);          // PLL_N (N Multiplier must be 100MHz < fvco <= 432MHz)
  REG_SET_VAL(Rcc->PLLCFGR, 0x00U, 0x3U, RCC_PLLCFGR_PLLP_Pos);           // PLL_P (P Divider to divide to get desired clock) PLL_Q/PLL_R divider are 2 by default



  // ------------[ only required if you are using RGB interface ]------------ stm32f49 etc.

  // 4. Set up LCD_CLK using PLLSAI block
//  REG_SET_VAL(Rcc->PLLSAICFGR, 50U, 0x1FFU, RCC_SAICFGR_PLLSAIN_Pos);     // PLLSAI_N
//  REG_SET_VAL(Rcc->PLLSAICFGR, 0x02U, 0x7U, RCC_SAICFGR_PLLSAIR_Pos);     // PLLSAI_R

  // LCD_CLK = 6.25MHz
//  REG_SET_VAL(Rcc->DKCFGR, 0x08U, 0x3U, RCC_DCKCFGR_PLLSAIDIVR_Pos);      // DIV

  // =====================================================================================



  // 5. Set up AHB and APBx clocks

  // Clock speed of stm32f407 [RM page 217] AHB 168MHz, APB2, 84MHz, and APB1 42MHz maximum
  REG_SET_VAL(Rcc->CFGR, 0U, 0xFU, RCC_CFGR_HPRE_Pos);                    // AHB prescaler   168/0 = 168
  REG_SET_VAL(Rcc->CFGR, 0x5U, 0x7U, RCC_CFGR_PPRE1_Pos);                 // APB1 prescaler  168/5 = 33
  REG_SET_VAL(Rcc->CFGR, 0x4U, 0x7U, RCC_CFGR_PPRE2_Pos);                 // APB2 prescaler  168/4 = 42



  // 6. Turn on PLL and wait for PLLCLK ready bit to set by hardware
  REG_SET_BIT(Rcc->CR, RCC_CR_PLLON_Pos);
  while (!REG_READ_BIT(Rcc->CR, RCC_CR_PLLRDY_Pos));


  // 7. Switch PLLCLK as SYSCLK
  REG_SET_VAL(Rcc->CFGR, 0x2U, 0x3U, RCC_CFGR_SWS_Pos);
  while (!(REG_READ_VAL(Rcc->CFGR, 0x3U, RCC_CFGR_SWS_Pos) == 0x2U));
}
