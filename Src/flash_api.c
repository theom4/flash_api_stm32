#include "flash_api.h"

uint32_t ulGetSectorNum(uint32_t ulStartAddr)
{
	 if (ulStartAddr < 0x08007FFF) return 0;
	 if (ulStartAddr < 0x0800FFFF) return 1;
	 if (ulStartAddr < 0x08017FFF) return 2;
	 if (ulStartAddr < 0x0801FFFF) return 3;
	 if (ulStartAddr < 0x0803FFFF) return 4;
	 if (ulStartAddr < 0x0807FFFF) return 5;
	 if (ulStartAddr < 0x080BFFFF) return 6;
	 if (ulStartAddr < 0x080FFFFF) return 7;
	return 0xFF;
}
uint32_t ulFlashWriteSector(uint32_t ulStartAddr,
							uint32_t* ulWordData,
							uint32_t ulWordLen)
{
	uint32_t sector_error = 0;
	FLASH_EraseInitTypeDef sFlashErase = {0};
	HAL_FLASH_Unlock();

	sFlashErase.NbSectors = 1;
	sFlashErase.Sector = ulGetSectorNum(ulStartAddr);
	sFlashErase.TypeErase = FLASH_TYPEERASE_SECTORS;
	sFlashErase.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    if(HAL_FLASHEx_Erase(&sFlashErase,&sector_error ) != HAL_OK)
    {
    	return sector_error;
    }
    for(uint32_t idx = 0;idx < ulWordLen; idx ++)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, ulStartAddr, ulWordData[idx]);
        ulStartAddr += 4;

    }

	HAL_FLASH_Lock();
	return HAL_OK;

}
void Flash_Read_Data (uint32_t StartSectorAddress, uint32_t *RxBuf, uint16_t numberofwords)
{
	while (1)
	{

		*RxBuf = *(__IO uint32_t *)StartSectorAddress;
		StartSectorAddress += 4;
		RxBuf++;
		if (!(numberofwords--)) break;
	}
}
