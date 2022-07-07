Library to configure onchip flash memory in PSoC-63 to allow read and write.

To read a variable, use regular c functions.

To write, follow this example code:

  // Variable to store data to be written to flash
  int16_t ram_data[CY_FLASH_SIZEOF_ROW] = {0};
  
  // Write settings to ram_data
  ram_data[0] = data_source[0];
  ram_data[1] = data_source[1];
  .
  .
  .
    
  // Write to flash using blocking function. "flash_data" is declared in the flash_memory library
  flash_write_status = Cy_Flash_WriteRow((uint32_t)flash_data, (const uint32_t *)ram_data);
    
  // Wait until write cycle ends and check if successfull
  if((flash_write_status == CY_FLASH_DRV_SUCCESS) && (memcmp(ram_data, flash_data, CY_FLASH_SIZEOF_ROW) == 0u))
    {
        // Write your code
        return 0;
    }
    
  else
    {
        // Write your error capture code
        return 1;
    };
  }
