# Boot times and sizes
T0 represents -O0 and T1 represents -O1 optimizations.
Anything above -O1 won´t work correctly
## No crypto
FLASH = 20.3kB
RAM = 11.9kB

5kB BIN --->T0 = 164ms / T1 = 132ms
20kB BIN--->T0 = 540ms / T1 = 434ms

## Tiny-AES

FLASH = 23.7kB
RAM = 12kB
Times: -O0/-O1
For 5kB BIN File:

| |CBC  | CTR | ECB|
| --|--|--|--|
| AES128| 1431ms/216ms| 334ms/170ms|
| AES192| 1708ms/232ms | 369ms/177ms |
| AES256| 1988ms/252ms| 401ms/187ms |

For 20kB BIN File:

| |CBC  | CTR | ECB|
| --|--|--|--|
| AES128| 7135ms/871ms| 1431ms/632ms|
| AES192| 8581ms/956ms| 1608ms/668ms|
| AES256| 10031ms/1059ms| 1781ms/720ms|

Note: changing `sbox[256]` and `rsbox[256]`from `static const` to `static` (from ROM to RAM) produce less than 1% improvement.

