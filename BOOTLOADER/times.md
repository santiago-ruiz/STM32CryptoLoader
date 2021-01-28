# Boot times and sizes
T0 represents -O0 and T1 represents -O1 optimizations.
Anything above -O1 won´t work correctly
## No crypto
FLASH = 20.5kB
RAM = 12kB

5kB BIN --->T0 = 164ms / T1 = 132ms
20kB BIN--->T0 = 540ms / T1 = 434ms

## Crypto
### AES (Tiny-AES)

Added FLASH = 3.4kB
Added RAM = 0.1kB
Added Times: -O0/-O1
For 5kB BIN File:

| |CBC  | CTR | ECB|
| --|--|--|--|
| AES128| 1267ms/84ms| 170ms/38ms|
| AES192| 1544ms/100ms | 205ms/45ms |
| AES256| 1824ms/120ms| 401ms/55ms |

For 20kB BIN File:

| |CBC  | CTR | ECB|
| --|--|--|--|
| AES128| 6595ms/437ms| 891ms/198ms|
| AES192| 8041ms/522ms| 1068ms/234ms|
| AES256| 9491ms/625ms| 1241ms/286ms|

Note: changing `sbox[256]` and `rsbox[256]`from `static const` to `static` (from ROM to RAM) produce less than 1% improvement.

## Verification
### CRC32 (Hardware implemented)
Added FLASH =  0.4kB
Added RAM = 0kB

For 5kB BIN File:
Added Time: T0=19ms / T1=8ms
For 20kB BIN File:
Added Time: T0=199ms / T1=35ms

### SHA256
-Added FLASH =  2kB
-Added RAM = 0.1kB

-For 5kB BIN File:
-Added Time: T0=36ms / T1=1ms
-For 20kB BIN File:
-Added Time: T0=156ms / T1=12ms

