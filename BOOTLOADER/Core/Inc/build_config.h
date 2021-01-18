#ifndef BUILD_CONFIG__H
#define BUILD_CONFIG__H

#define CRYPTO					1

#define BINARY_FILE_NAME 		"firmware.bin"
#define PAGE_SIZE               ((uint16_t)0x400)    /* 1 Kbytes */
#define FLASH_SIZE              ((uint32_t)0x10000)  /* 64 KBytes */
#define BOOTLOADER_SIZE         ((uint32_t)0x8000)   /* 32Kbytes*/
#define APPLICATIONADDRESS      ((uint32_t)FLASH_STARTADDRESS+BOOTLOADER_SIZE) /* User start code space */
#define FLASH_STARTADDRESS      ((uint32_t)0x08000000) /* Flash Start Address */
#define FLASH_ENDADDRESS		((uint32_t)FLASH_STARTADDRESS +FLASH_SIZE)
#define BUFFER_SIZE   			((uint16_t)1*8192) /* Binary reading buffer*/
//#define BUFFER_SIZE   			((uint16_t)4704) /* Binary reading buffer*/

//openssl enc -aes-128-cbc -in blinky1.bin -nosalt -K 000102030405060708090a0b0c0d0e0f -iv 000102030405060708090a0b0c0d0e0f -out firmware.bin -p


#endif
