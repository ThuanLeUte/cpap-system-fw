/**
* @file       bsp.c
* @copyright  Copyright (C) 2021 ThuanLe. All rights reserved.
* @license    This project is released under the ThuanLe License.
* @version    01.00.00
* @date       2021-03-13
* @author     ThuanLe
* @brief      BSP (Board Support Package)
* @note       None
* @example    None
*/

/* Includes ----------------------------------------------------------------- */
#include "bsp.h"

/* Private defines ---------------------------------------------------------- */
//static const char *TAG = "BSP";

/* Public variables --------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
static inline void m_bsp_nvs_init(void);
static inline void m_bsp_spiffs_init(void);

/* Function definitions ----------------------------------------------------- */
void bsp_init(void)
{
  m_bsp_nvs_init();
  m_bsp_spiffs_init();
}


/* Private function --------------------------------------------------------- */

/* End of file -------------------------------------------------------- */