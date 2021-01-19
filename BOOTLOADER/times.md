# Boot times and sizes
Compilation -O0 for all configurations
## No crypto
FLASH = 20.3kB
RAM = 11.9kB

5kB BIN --->T = 164ms
20kb BIN--->T = 540ms

## Tiny-AES

FLASH = 23.7kB
RAM = 12kB

For 5kB BIN File:

| |CBC  | CTR | ECB|
| --|--|--|--|
| AES128| 1431ms| 334ms|
| AES192| 1708ms | 369ms |
| AES256| 1988ms| 401ms |

For 20kB BIN File:

| |CBC  | CTR | ECB|
| --|--|--|--|
| AES128| 7135ms| 1431ms|
| AES192| 8581ms| 1608ms|
| AES256| 10031ms| 1781ms|
