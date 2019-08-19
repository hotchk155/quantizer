/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v5.0
processor: MKE06Z128xxx4
package_id: MKE06Z128VLD4
mcu_data: ksdk2_0
processor_version: 5.0.0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '32', peripheral: I2C0, signal: SCL, pin_signal: PTA3/KBI0_P3/UART0_TX/I2C0_SCL}
  - {pin_num: '33', peripheral: I2C0, signal: SDA, pin_signal: PTA2/KBI0_P2/UART0_RX/I2C0_SDA}
  - {pin_num: '2', peripheral: SPI1, signal: SCK, pin_signal: PTD0/KBI0_P24/FTM2_CH2/SPI1_SCK}
  - {pin_num: '1', peripheral: SPI1, signal: MOSI, pin_signal: PTD1/KBI0_P25/FTM2_CH3/SPI1_MOSI}
  - {pin_num: '31', peripheral: SPI1, signal: MISO, pin_signal: PTD2/KBI0_P26/SPI1_MISO}
  - {pin_num: '24', peripheral: UART0, signal: RX, pin_signal: PTB0/KBI0_P8/UART0_RX/PWT_IN1/ADC0_SE4}
  - {pin_num: '23', peripheral: UART0, signal: TX, pin_signal: PTB1/KBI0_P9/UART0_TX/ADC0_SE5}
  - {pin_num: '21', peripheral: SPI0, signal: MOSI, pin_signal: PTB3/KBI0_P11/SPI0_MOSI/FTM0_CH1/ADC0_SE7}
  - {pin_num: '22', peripheral: SPI0, signal: SCK, pin_signal: PTB2/KBI0_P10/SPI0_SCK/FTM0_CH0/ADC0_SE6}
  - {pin_num: '30', peripheral: GPIOA, signal: 'GPIO, 27', pin_signal: PTD3/KBI0_P27/SPI1_PCS}
  - {pin_num: '29', peripheral: GPIOA, signal: 'GPIO, 28', pin_signal: PTD4/KBI0_P28}
  - {pin_num: '20', peripheral: GPIOA, signal: 'GPIO, 16', pin_signal: PTC0/KBI0_P16/FTM2_CH0/ADC0_SE8}
  - {pin_num: '41', peripheral: GPIOA, signal: 'GPIO, 21', pin_signal: PTC5/KBI0_P21/FTM1_CH1/RTCO, pullup_enable: enable}
  - {pin_num: '37', peripheral: GPIOA, signal: 'GPIO, 22', pin_signal: PTC6/KBI0_P22/UART1_RX/CAN0_RX}
  - {pin_num: '36', peripheral: GPIOA, signal: 'GPIO, 23', pin_signal: PTC7/KBI0_P23/UART1_TX/CAN0_TX, pullup_enable: enable}
  - {pin_num: '35', peripheral: GPIOA, signal: 'GPIO, 0', pin_signal: PTA0/KBI0_P0/FTM0_CH0/I2C0_4WSCLOUT/ACMP0_IN0/ADC0_SE0}
  - {pin_num: '34', peripheral: GPIOA, signal: 'GPIO, 1', pin_signal: PTA1/KBI0_P1/FTM0_CH1/I2C0_4WSDAOUT/ACMP0_IN1/ADC0_SE1, pullup_enable: enable}
  - {pin_num: '10', peripheral: GPIOA, signal: 'GPIO, 14', pin_signal: PTB6/KBI0_P14/I2C0_SDA/XTAL}
  - {pin_num: '9', peripheral: GPIOA, signal: 'GPIO, 15', pin_signal: PTB7/KBI0_P15/I2C0_SCL/EXTAL, pullup_enable: enable}
  - {pin_num: '40', peripheral: GPIOB, signal: 'GPIO, 0', pin_signal: PTE0/KBI1_P0/SPI0_SCK/TCLK1/I2C1_SDA, pullup_enable: enable}
  - {pin_num: '39', peripheral: GPIOB, signal: 'GPIO, 1', pin_signal: PTE1/KBI1_P1/SPI0_MOSI/I2C1_SCL, pullup_enable: enable}
  - {pin_num: '38', peripheral: GPIOB, signal: 'GPIO, 2', pin_signal: PTE2/KBI1_P2/SPI0_MISO/PWT_IN0, pullup_enable: enable}
  - {pin_num: '3', peripheral: GPIOB, signal: 'GPIO, 7', pin_signal: PTE7/KBI1_P7/TCLK2/FTM1_CH1/CAN0_TX}
  - {pin_num: '4', peripheral: GPIOB, signal: 'GPIO, 26', pin_signal: PTH2/KBI1_P26/BUSOUT/FTM1_CH0/CAN0_RX, pullup_enable: enable}
  - {pin_num: '26', peripheral: GPIOA, signal: 'GPIO, 6', pin_signal: PTA6/KBI0_P6/FTM2_FLT1/ACMP1_IN0/ADC0_SE2}
  - {pin_num: '25', peripheral: GPIOA, signal: 'GPIO, 7', pin_signal: PTA7/KBI0_P7/FTM2_FLT2/ACMP1_IN1/ADC0_SE3}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)
{
    /* Pull Enable for Port A Bit 1: 0x01u */
    PORT_SetPinPullUpEnable(PORT, kPORT_PTA, 1U, true);
    /* Pull Enable for Port B Bit 7: 0x01u */
    PORT_SetPinPullUpEnable(PORT, kPORT_PTB, 7U, true);
    /* Pull Enable for Port C Bit 5: 0x01u */
    PORT_SetPinPullUpEnable(PORT, kPORT_PTC, 5U, true);
    /* Pull Enable for Port C Bit 7: 0x01u */
    PORT_SetPinPullUpEnable(PORT, kPORT_PTC, 7U, true);
    /* Pull Enable for Port E Bit 0: 0x01u */
    PORT_SetPinPullUpEnable(PORT, kPORT_PTE, 0U, true);
    /* Pull Enable for Port E Bit 1: 0x01u */
    PORT_SetPinPullUpEnable(PORT, kPORT_PTE, 1U, true);
    /* Pull Enable for Port E Bit 2: 0x01u */
    PORT_SetPinPullUpEnable(PORT, kPORT_PTE, 2U, true);
    /* Pull Enable for Port H Bit 2: 0x01u */
    PORT_SetPinPullUpEnable(PORT, kPORT_PTH, 2U, true);
    /* pin 32,33 is configured as I2C0_SCL, I2C0_SDA */
    PORT_SetPinSelect(kPORT_I2C0, kPORT_I2C0_SCLPTA3_SDAPTA2);
    /* pin 21,22 is configured as SPI0_MOSI, SPI0_SCK */
    PORT_SetPinSelect(kPORT_SPI0, kPORT_SPI0_SCKPTB2_MOSIPTB3_MISOPTB4_PCSPTB5);
    /* pin 24,23 is configured as UART0_RX, UART0_TX */
    PORT_SetPinSelect(kPORT_UART0, kPORT_UART0_RXPTB0_TXPTB1);
    /* pin 2,1,31 is configured as SPI1_SCK, SPI1_MOSI, SPI1_MISO */
    PORT_SetPinSelect(kPORT_SPI1, kPORT_SPI1_SCKPTD0_MOSIPTD1_MISOPTD2_PCSPTD3);

    SIM->SOPT0 = ((SIM->SOPT0 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT0_RXDFE_MASK | SIM_SOPT0_CLKOE_MASK)))

                  /* UART0 RxD Filter Select: RXD0 input signal is connected to UART0 module directly. */
                  | SIM_SOPT0_RXDFE(SOPT0_RXDFE_0b00)

                  /* Bus Clock Output Enable: Bus clock output is disabled on PTH2. */
                  | SIM_SOPT0_CLKOE(SOPT0_CLKOE_0b0));
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
