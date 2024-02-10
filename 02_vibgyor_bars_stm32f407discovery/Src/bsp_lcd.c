#include "reg_util.h"
#include "stm32f407xx.h"
#include "ili9341_reg.h"

#define SPI                                          SPI2
#define LCD_SCL_PIN                                  GPIO_PIN_13
#define LCD_SCL_PORT                                 GPIOB
#define LCD_SDI_PIN                                  GPIO_PIN_15
#define LCD_SDI_PORT                                 GPIOB
#define LCD_SDO_PIN                                  GPIO_PIN_2
#define LCD_SDO_PORT                                 GPIOC
#define LCD_RESX_PIN                                 GPIO_PIN_10
#define LCD_RESX_PORT                                GPIOD
#define LCD_CSX_PIN                                  GPIO_PIN_11
#define LCD_CSX_PORT                                 GPIOD
#define LCD_DCX_PIN                                  GPIO_PIN_9
#define LCD_DCX_PORT                                 GPIOD

void LCD_Pin_Init(void);
void LCD_SPI_Init(void);
void LCD_SPI_Enable(void);
void LCD_Reset(void);
void LCD_Config(void);
void LCD_Write_Cmd(uint8_t cmd);
void LCD_Write_Data(uint8_t* buffer, uint32_t len);

#define GPIO_PIN_0               0U
#define GPIO_PIN_1               1U
#define GPIO_PIN_2               2U
#define GPIO_PIN_3               3U
#define GPIO_PIN_4               4U
#define GPIO_PIN_5               5U
#define GPIO_PIN_6               6U
#define GPIO_PIN_7               7U
#define GPIO_PIN_8               8U
#define GPIO_PIN_9               9U
#define GPIO_PIN_10              10U
#define GPIO_PIN_11              11U
#define GPIO_PIN_12              12U
#define GPIO_PIN_13              13U
#define GPIO_PIN_14              14U
#define GPIO_PIN_15              15U

#define LCD_RESX_HIGH()          REG_SET_BIT(LCD_RESX_PORT->ODR, LCD_RESX_PIN)
#define LCD_RESX_LOW()           REG_CLEAR_BIT(LCD_RESX_PORT->ODR, LCD_RESX_PIN)

#define LCD_CSX_HIGH()           REG_SET_BIT(LCD_CSX_PORT->ODR, LCD_CSX_PIN)
#define LCD_CSX_LOW()            REG_CLEAR_BIT(LCD_CSX_PORT->ODR, LCD_CSX_PIN)

#define LCD_DCX_HIGH()           REG_SET_BIT(LCD_DCX_PORT->ODR, LCD_DCX_PIN)
#define LCD_DCX_LOW()            REG_CLEAR_BIT(LCD_DCX_PORT->ODR, LCD_DCX_PIN)

void BSP_LCD_Init(void)
{
  LCD_Pin_Init();
  LCD_SPI_Init();
  LCD_SPI_Enable();
  LCD_Reset();
  LCD_Config();
}

void LCD_SPI_Enable(void)
{
  SPI_TypeDef* pSPI = SPI;
  REG_SET_BIT(pSPI->CR1, SPI_CR1_SPE_Pos);
}

void LCD_SPI_Init(void)
{
  SPI_TypeDef* pSPI = SPI;

  REG_SET_BIT(pSPI->CR1, SPI_CR1_MSTR_Pos);                     // Master/Controller mode
  REG_CLEAR_BIT(pSPI->CR1, SPI_CR1_BIDIMODE_Pos);               // 2 lines uni directional lines
  REG_SET_BIT(pSPI->CR1, SPI_CR1_BIDIOE_Pos);                   // Tx only
  REG_CLEAR_BIT(pSPI->CR1, SPI_CR1_DFF_Pos);                    // DFF = 8bits
  REG_SET_BIT(pSPI->CR1, SPI_CR1_SSM_Pos);                      // SSM enable
  REG_SET_BIT(pSPI->CR1, SPI_CR1_SSI_Pos);                      // SSI enable
  REG_CLEAR_BIT(pSPI->CR1, SPI_CR1_LSBFIRST_Pos);               // Send msb first
  REG_SET_VAL(pSPI->CR1, 0x00U, 0x7U, SPI_CR1_BR_Pos);          // SPI clock = 42MHz/2 ==> 21MHz
  REG_CLEAR_BIT(pSPI->CR1, SPI_CR1_CPOL_Pos);                   // CPOL=0
  REG_CLEAR_BIT(pSPI->CR1, SPI_CR1_CPHA_Pos);                   // CPHA=0
  REG_CLEAR_BIT(pSPI->CR1, SPI_CR2_FRF_Pos);                    // SPI Motorola frame format
}

void delay_50ms(void)
{
  for (uint32_t i=0; i< (0xFFFFU * 10U); i++);
}

void LCD_Reset(void)
{
  LCD_RESX_LOW();
  for (uint32_t i=0; i<(0xFFFFU * 20U); i++);                   // 50 millisecond
  LCD_RESX_HIGH();
  for (uint32_t i=0; i<(0xFFFFU * 20U); i++);
}

void LCD_Config(void)
{
  uint8_t params[15];
  LCD_Write_Cmd(ILI9341_SWRESET);
  LCD_Write_Cmd(ILI9341_POWERB);
  params[0] = 0x00;
  params[1] = 0xD9;
  params[2] = 0x30;
  LCD_Write_Data(params, 3);
}

void LCD_Write_Cmd(uint8_t cmd)
{
  SPI_TypeDef* pSPI = SPI;
  LCD_CSX_LOW();
  LCD_DCX_LOW();                                                // DCX=0, for command
  while (!REG_READ_BIT(pSPI->SR, SPI_SR_TXE_Pos));
  REG_WRITE(pSPI->DR, cmd);
  while (!REG_READ_BIT(pSPI->SR, SPI_SR_TXE_Pos));
  while (REG_READ_BIT(pSPI->SR, SPI_SR_BSY_Pos));
  LCD_CSX_HIGH();
  LCD_DCX_HIGH();
}

void LCD_Write_Data(uint8_t* buffer, uint32_t len)
{
  SPI_TypeDef* pSPI = SPI;
  for (uint32_t i=0; i < len; i++)
  {
	while (!REG_READ_BIT(pSPI->SR, SPI_SR_TXE_Pos));
	REG_WRITE(pSPI->DR, buffer[i]);
  }
  while (!REG_READ_BIT(pSPI->SR, SPI_SR_TXE_Pos));
  while (REG_READ_BIT(pSPI->SR, SPI_SR_BSY_Pos));
  LCD_CSX_HIGH();
}

void lcd_pin_init(void)
{
  RCC_TypeDef* pRCC = RCC;

  // Enable the clock access to GPIOB, C, D peripheral
  REG_SET_BIT(pRCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN_Pos);
  REG_SET_BIT(pRCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN_Pos);
  REG_SET_BIT(pRCC->AHB1ENR, RCC_AHB1ENR_GPIODEN_Pos);

  // RESX
  REG_SET_VAL(LCD_RESX_PORT->MODER, 0x1U, 0x3, (LCD_RESX_PIN * 2U));           // Mode
  REG_CLEAR_BIT(LCD_RESX_PORT->OTYPER, LCD_RESX_PIN);                          // Output type
  REG_SET_VAL(LCD_RESX_PORT->OSPEEDR, 2U, 0x3U, LCD_RESX_PIN * 2U);            // Speed

  // CSX
  REG_SET_VAL(LCD_CSX_PORT->MODER, 0x1U, 0x3, (LCD_CSX_PIN * 2U));             // Mode
  REG_CLEAR_BIT(LCD_CSX_PORT->OTYPER, LCD_CSX_PIN);                            // Output type
  REG_SET_VAL(LCD_CSX_PORT->OSPEEDR, 2U, 0x3U, (LCD_CSX_PIN * 2U));            // Speed

  // D/CX
  REG_SET_VAL(LCD_DCX_PORT->MODER, 0x1U, 0x3, (LCD_DCX_PIN * 2U));             // Mode
  REG_CLEAR_BIT(LCD_DCX_PORT->OTYPER, LCD_DCX_PIN);                            // Output type
  REG_SET_VAL(LCD_DCX_PORT->OSPEEDR, 2U, 0x3U, (LCD_DCX_PIN * 2U));            // Speed

  // SPI CLK (PB13)
  REG_SET_VAL(LCD_SCL_PORT->MODER, 2U, 0x3U, (LCD_SCL_PIN * 2U));
  REG_CLEAR_BIT(LCD_SCL_PORT->OTYPER, LCD_SCL_PIN);
  REG_SET_VAL(LCD_SCL_PORT->OSPEEDR, 2U, 0x3U, (LCD_SCL_PIN * 2U));
  REG_SET_VAL(LCD_SCL_PORT->AFR[1], 5U, 0xFU, ((LCD_SCL_PIN % 8)* 4U));

  // SPI SDI  (PB15) (PICO)
  REG_SET_VAL(LCD_SDI_PORT->MODER, 2U, 0x3U, (LCD_SDI_PIN * 2U));
  REG_CLEAR_BIT(LCD_SDI_PORT->OTYPER, LCD_SDI_PIN);
  REG_SET_VAL(LCD_SDI_PORT->OSPEEDR, 2U, 0x3U, (LCD_SDI_PIN * 2U));
  REG_SET_VAL(LCD_SDI_PORT->AFR[1], 5U, 0xFU, ((LCD_SDI_PIN % 8) * 4U));

  // SPI SDO  (PC2) (POCI)
  REG_SET_VAL(LCD_SDO_PORT->MODER, 2U, 0x3U, (LCD_SDO_PIN * 2U));
  REG_CLEAR_BIT(LCD_SDO_PORT->OTYPER, LCD_SDO_PIN);
  REG_SET_VAL(LCD_SDO_PORT->OSPEEDR, 2U, 0x3U, (LCD_SDO_PIN * 2U));
  REG_SET_VAL(LCD_SDO_PORT->AFR[0], 5U, 0xFU, (LCD_SDO_PIN * 4U));

  REG_SET_BIT(LCD_RESX_PORT->ODR, LCD_RESX_PIN);                                // RESX = HIGH

  REG_SET_BIT(LCD_DCX_PORT->ODR, LCD_DCX_PIN);                                  // D/CX = HIGH
}


