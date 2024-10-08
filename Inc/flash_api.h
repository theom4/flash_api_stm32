#include "main.h"
uint32_t ulFlashWriteSector(uint32_t ulStartAddr,
							uint32_t* ulWordData,
							uint32_t ulWordLen);
uint32_t ulFlashReadSector(uint32_t ulStartAddr,
						    uint32_t* ulWordData,
							uint32_t ulWordLen);
