// revision 2021-12-28-1
// Flash memory only works with the "2047 line"


#ifndef _SG_FLASH_H_
#define _SG_FLASH_H_

#include "project.h"
#include <string.h>     // e.g.: strcpy()
    
#define MAKE_FLASH_WRITE_FAIL 0u
CY_ALIGN(CY_FLASH_SIZEOF_ROW)

#define LAST_FLASH_ROW        2047u
#define CALCULATE_FLASH_ADDRESS(rowNum) (CY_FLASH_BASE + ((rowNum) * CY_FLASH_SIZEOF_ROW))

#if(MAKE_FLASH_WRITE_FAIL == 0)
/* Make the address point to last user flash row */
     const int16_t *flash_data = (int16_t *)CALCULATE_FLASH_ADDRESS(LAST_FLASH_ROW); // use with "#define LAST_FLASH_ROW 2047u" and "#define CALCULATE_FLASH_ADDRESS(rowNum) (CY_FLASH_BASE + ((rowNum) * CY_FLASH_SIZEOF_ROW))"
     //const int16_t flash_data[CY_FLASH_SIZEOF_ROW] = {0}; // used in another example that does not use "#define LAST_FLASH_ROW 2047u"
#else
    /* Make the address point to some RAM location */
    const int16_t *flashData = (int16_t *)CY_SRAM0_BASE;
#endif  /* #if(MAKE_FLASH_WRITE_FAIL == 0) */

int16_t ram_data[CY_FLASH_SIZEOF_ROW] = {0};
bool flash_error_flag = false;
cy_en_flashdrv_status_t flash_write_status;
//int16_t IMU_calibration_data_valid = 0;
bool flash_intr_set = false;


uint8_t flash_write_test(void);

/**********************************************************************************/
/**********************************************************************************/
uint8_t flash_write_test(void)
{
    memset(ram_data, 'a', CY_FLASH_SIZEOF_ROW); // Use this to test writing to flash, 'a' = 0x61 = 24929d
    
    // Write to flash using blocking function
    flash_write_status = Cy_Flash_WriteRow((uint32_t)flash_data, (const uint32_t *)ram_data);
    
    // Wait until write cycle ends and check if successfull
    if((flash_write_status == CY_FLASH_DRV_SUCCESS) && (memcmp(ram_data, flash_data, CY_FLASH_SIZEOF_ROW) == 0u))
    {
        return 1; // success
    }
    
    else
    {
        return 0; // fail
    };
}

#endif 