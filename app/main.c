#include <main.h>

void lv_ex_label(void)
{
		char* github_addr = "https://gitee.com/W23";
		lv_obj_t * label = lv_label_create(lv_scr_act());
    lv_label_set_recolor(label, true);
    lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR); /*Circular scroll*/
    lv_obj_set_width(label, 120);
    lv_label_set_text_fmt(label, "#ff0000 Gitee: %s#", github_addr);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 10);
	
    lv_obj_t * label2 = lv_label_create(lv_scr_act());
    lv_label_set_recolor(label2, true);
    lv_label_set_long_mode(label2, LV_LABEL_LONG_SCROLL_CIRCULAR); /*Circular scroll*/
    lv_obj_set_width(label2, 120);
    lv_label_set_text_fmt(label2, "#ff0000 Hello# #0000ff world !123456789#");
    lv_obj_align(label2, LV_ALIGN_CENTER, 0, -10);
}

void SysTick_Handler(void)
{
    SysTick_IncTick();
	  
	  lv_tick_inc(1);
}

static void SPI_Config(void)
{
    stc_spi_init_t stcSpiInit;


    /* Configure Port */
    GPIO_SetFunc(SPI_SS_PORT,   SPI_SS_PIN,   SPI_SS_FUNC);
    GPIO_SetFunc(SPI_SCK_PORT,  SPI_SCK_PIN,  SPI_SCK_FUNC);
    GPIO_SetFunc(SPI_MOSI_PORT, SPI_MOSI_PIN, SPI_MOSI_FUNC);
    GPIO_SetFunc(SPI_MISO_PORT, SPI_MISO_PIN, SPI_MISO_FUNC);

    /* Configuration SPI */
    FCG_Fcg1PeriphClockCmd(SPI_CLK, ENABLE);
    SPI_StructInit(&stcSpiInit);
    stcSpiInit.u32WireMode          = SPI_4_WIRE;
    stcSpiInit.u32TransMode         = SPI_FULL_DUPLEX;
    stcSpiInit.u32MasterSlave       = EXAMPLE_SPI_MASTER_SLAVE;
    stcSpiInit.u32Parity            = SPI_PARITY_INVD;
    stcSpiInit.u32SpiMode           = SPI_MD_0;///SPI_MD_1;
    stcSpiInit.u32BaudRatePrescaler = SPI_BR_CLK_DIV2;///SPI_BR_CLK_DIV64;
    stcSpiInit.u32DataBits          = SPI_DATA_SIZE_8BIT;
    stcSpiInit.u32FirstBit          = SPI_FIRST_MSB;
    stcSpiInit.u32FrameLevel        = SPI_1_FRAME;
    (void)SPI_Init(SPI_UNIT, &stcSpiInit);
    SPI_Cmd(SPI_UNIT, ENABLE);
}

uint8_t spi_write_byte(uint8_t byte)
{
		/* Wait tx buffer empty */
    while (RESET == SPI_GetStatus(CM_SPI4, SPI_FLAG_TX_BUF_EMPTY)) {
		}
    SPI_WriteData(CM_SPI4, (uint32_t)byte);
		
		/* Wait rx buffer full */
    while (RESET == SPI_GetStatus(CM_SPI4, SPI_FLAG_RX_BUF_FULL)) {
		}
    return ((char)SPI_ReadData(CM_SPI4));
} 
int main(void)
{
	
    /* Peripheral registers write unprotected */
    LL_PERIPH_WE(EXAMPLE_PERIPH_WE);
    /* Configure BSP */
    BSP_CLK_Init();
    ///BSP_LED_Init();
    ///BSP_KEY_Init();
	
	  /* SysTick configuration */
    (void)SysTick_Init(1000U);
	
    /* Configure SPI */
    SPI_Config();
		LCD_Control_Init();
		lv_init();
		lv_port_disp_init();
		while(1)
		{
			lv_tick_inc(1);
			lv_task_handler();
			SysTick_Delay(200U);
			lv_ex_label();
		}
		return 0;
}