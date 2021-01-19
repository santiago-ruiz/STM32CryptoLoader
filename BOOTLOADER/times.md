# Boot times and sizes
Compilation -O0 for all configurations
## No crypto
For 5kB BIN File:
T = 164ms
FLASH = 20.3kB
RAM = 11.9kB

## Tiny-AES

For 5kB BIN File:

| |CBC  | CTR | ECB|
| --|--|--|--|
| AES128| 1431ms/23.7kB/12kB | 334ms/22.2kB/12kB |
| AES192| 1708ms/23.8kB/12kB | 369ms/22.3kB/12kB |
| AES256| 1988ms/23.8kB/12kB | 401ms/22.3kB/12kB |
