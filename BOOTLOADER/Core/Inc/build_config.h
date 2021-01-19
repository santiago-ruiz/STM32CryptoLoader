#ifndef BUILD_CONFIG__H
#define BUILD_CONFIG__H

#define BINARY_FILE_NAME 		"firmware.bin"
#define PAGE_SIZE               ((uint16_t)0x400)    /* 1 Kbytes */
#define FLASH_SIZE              ((uint32_t)0x10000)  /* 64 KBytes */
#define BOOTLOADER_SIZE         ((uint32_t)0x8000)   /* 32Kbytes*/
#define APPLICATIONADDRESS      ((uint32_t)FLASH_STARTADDRESS+BOOTLOADER_SIZE) /* User start code space */
#define FLASH_STARTADDRESS      ((uint32_t)0x08000000) /* Flash Start Address */
#define FLASH_ENDADDRESS		((uint32_t)FLASH_STARTADDRESS +FLASH_SIZE)
#define BUFFER_SIZE   			((uint16_t)1*8192) /* Binary reading buffer*/

#define CRYPTO					1

#if (CRYPTO == 1)

#define AES128					0
#define AES192					0
#define AES256					1
#define CBC						0
#define ECB						0
#define CTR						1

#define TINY_AES				1
//OpenSSL commands
//AES128
//openssl enc -aes-128-cbc -in blinky1.bin -nosalt -K 000102030405060708090a0b0c0d0e0f -iv 000102030405060708090a0b0c0d0e0f -out firmware.bin -p
//openssl enc -aes-128-ctr -in blinky1.bin -nosalt -K 000102030405060708090a0b0c0d0e0f -iv 000102030405060708090a0b0c0d0e0f -out firmware.bin -p
//openssl enc -aes-128-ecb -in blinky1.bin -nosalt -K 000102030405060708090a0b0c0d0e0f -out firmware.bin -p

//AES192-CBC
//openssl enc -aes-192-cbc -in blinky1.bin -nosalt -K 000102030405060708090a0b0c0d0e0f0001020304050607 -iv 000102030405060708090a0b0c0d0e0f -out firmware.bin -p
//openssl enc -aes-192-ctr -in blinky1.bin -nosalt -K 000102030405060708090a0b0c0d0e0f0001020304050607 -iv 000102030405060708090a0b0c0d0e0f -out firmware.bin -p

//AES256-CBC
//openssl enc -aes-256-cbc -in blinky1.bin -nosalt -K 000102030405060708090a0b0c0d0e0f000102030405060708090a0b0c0d0e0f -iv 000102030405060708090a0b0c0d0e0f -out firmware.bin -p
//openssl enc -aes-256-ctr -in blinky1.bin -nosalt -K 000102030405060708090a0b0c0d0e0f000102030405060708090a0b0c0d0e0f -iv 000102030405060708090a0b0c0d0e0f -out firmware.bin -p


#endif

#endif

