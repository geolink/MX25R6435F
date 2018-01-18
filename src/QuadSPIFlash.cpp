/**
  ******************************************************************************
  * @file    QuadSPIFlash.c
  * @author  WI6LABS
  * @version V1.0.0
  * @date    19-July-2017
  * @brief   QuadSPIFlash library for STM32 Arduino
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

#include "QuadSPIFlash.h"

QSPIFlashClass QSPIFlash;

QSPIFlashClass::QSPIFlashClass(): initDone(0)
{

}

void QSPIFlashClass::begin(void)
{
  if(BSP_QSPI_Init() == MEMORY_OK)
    initDone = 1;
}

void QSPIFlashClass::end(void)
{
  BSP_QSPI_DeInit();
  initDone = 0;
}

uint32_t QSPIFlashClass::write(uint8_t data, uint32_t addr)
{
  return write(&data, addr, 1);
}

uint32_t QSPIFlashClass::write(uint8_t *pData, uint32_t addr, uint32_t size)
{
  if((pData == NULL) || (initDone == 0))
    return 0;

  if(BSP_QSPI_Write(pData, addr, size) != MEMORY_OK)
    return 0;

  return size;
}

uint8_t QSPIFlashClass::read(uint32_t addr)
{
  uint8_t data;

  read(&data, addr, 1);

  return data;
}

void QSPIFlashClass::read(uint8_t *pData, uint32_t addr, uint32_t size)
{
  if((pData != NULL) && (initDone == 1))
    BSP_QSPI_Read(pData, addr, size);
}

uint8_t *QSPIFlashClass::mapped(void)
{
  if(BSP_QSPI_EnableMemoryMappedMode() != MEMORY_OK)
    return NULL;

  return (uint8_t *)MEMORY_MAPPED_ADDRESS;
}

uint8_t QSPIFlashClass::erase(uint32_t addr)
{
  if(initDone == 0)
    return MEMORY_ERROR;

  return BSP_QSPI_Erase_Block(addr);
}

uint8_t QSPIFlashClass::eraseChip(void)
{
  if(initDone == 0)
    return MEMORY_ERROR;

  return BSP_QSPI_Erase_Chip();
}

uint8_t QSPIFlashClass::eraseSector(uint32_t sector)
{
  if(initDone == 0)
    return MEMORY_ERROR;

  return BSP_QSPI_Erase_Sector(sector);
}

uint8_t QSPIFlashClass::suspendErase(void)
{
  if(initDone == 0)
    return MEMORY_ERROR;

  return BSP_QSPI_SuspendErase();
}

uint8_t QSPIFlashClass::resumeErase(void)
{
  if(initDone == 0)
    return MEMORY_ERROR;

  return BSP_QSPI_ResumeErase();
}

uint8_t QSPIFlashClass::sleep(void)
{
  if(initDone == 0)
    return MEMORY_ERROR;

  return BSP_QSPI_EnterDeepPowerDown();
}

uint8_t QSPIFlashClass::wakeup(void)
{
  if(initDone == 0)
    return MEMORY_ERROR;

  return BSP_QSPI_LeaveDeepPowerDown();
}

uint8_t QSPIFlashClass::status(void)
{
  if(initDone == 0)
    return MEMORY_ERROR;

  return BSP_QSPI_GetStatus();
}

uint32_t QSPIFlashClass::info(memory_info_t info)
{
  uint32_t res;
  QSPI_Info pInfo;

  BSP_QSPI_GetInfo(&pInfo);

  switch(info){
    case MEMORY_SIZE:
      res = pInfo.FlashSize;
    break;

    case MEMORY_SECTOR_SIZE:
      res = pInfo.EraseSectorSize;
    break;

    case MEMORY_SECTOR_NUMBER:
      res = pInfo.EraseSectorsNumber;
    break;

    case MEMORY_PAGE_SIZE:
      res = pInfo.ProgPageSize;
    break;

    case MEMORY_PAGE_NUMBER:
      res = pInfo.ProgPagesNumber;
    break;

    default:
      res = 0;
    break;
  }

  return res;
}

uint32_t QSPIFlashClass::length(void)
{
  return info(MEMORY_SIZE);
}
