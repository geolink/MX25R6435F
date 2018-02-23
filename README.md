# QSPIFlash
Arduino library to support a Quad-SPI NOR Flash memory, if configured for the current STM32 board

## API

The library provides the following API:

* begin()
* end()
* write()
* read()
* mapped()
* erase()
* eraseChip()
* eraseSector()
* suspendErase()
* resumeErase()
* sleep()
* wakeup()
* status()
* info()
* length()

## Examples

3 sketches provide basic examples to show how to use the library API.  
demo.ino uses basic read/write functions.  
eraseChip.ino erases all data present in the memory.  
memoryMappedMode.ino shows how to use the mapped mode.  
