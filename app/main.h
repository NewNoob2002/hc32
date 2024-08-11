#ifndef __MAIN_H__
#define __MAIN_H__
#include "hc32_ll.h"
#include "ev_hc32f460_lqfp100_v2_bsp.h"
#include <string.h>
#include "lvgl.h"
#include "../lvgl/porting/lv_port_disp.h"
///#include "lvgl/demos/widgets/lv_demo_widgets.h"
#include "../lvgl/demos/keypad_encoder/lv_demo_keypad_encoder.h"


/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* unlock/lock peripheral */
#define EXAMPLE_PERIPH_WE               (LL_PERIPH_GPIO | LL_PERIPH_EFM | LL_PERIPH_FCG | \
                                         LL_PERIPH_PWC_CLK_RMU | LL_PERIPH_SRAM)
#define EXAMPLE_PERIPH_WP               (LL_PERIPH_EFM | LL_PERIPH_FCG | LL_PERIPH_SRAM)

/* Configuration for Example */
#define EXAMPLE_SPI_MASTER_SLAVE        (SPI_MASTER)
#define EXAMPLE_SPI_BUF_LEN             (128UL)

/* SPI definition */
#define SPI_UNIT                        (CM_SPI4)
#define SPI_CLK                         (FCG1_PERIPH_SPI4)

/* SS = PA7 */
#define SPI_SS_PORT                     (GPIO_PORT_B)
#define SPI_SS_PIN                      (GPIO_PIN_05)
#define SPI_SS_FUNC                     (GPIO_FUNC_46)
/* SCK = PA8 */
#define SPI_SCK_PORT                    (GPIO_PORT_B)
#define SPI_SCK_PIN                     (GPIO_PIN_15)
#define SPI_SCK_FUNC                    (GPIO_FUNC_47)
/* MOSI = PB0 */
#define SPI_MOSI_PORT                   (GPIO_PORT_B)
#define SPI_MOSI_PIN                    (GPIO_PIN_13)
#define SPI_MOSI_FUNC                   (GPIO_FUNC_44)
/* MISO = PC5 */
#define SPI_MISO_PORT                   (GPIO_PORT_B)
#define SPI_MISO_PIN                    (GPIO_PIN_12)
#define SPI_MISO_FUNC                   (GPIO_FUNC_45)


static void SPI_Config(void);
uint8_t spi_write_byte(uint8_t byte);
#endif