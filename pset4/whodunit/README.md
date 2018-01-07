# Questions

## What's `stdint.h`?
It's header defines a set of integral type aliases with specific width requirements, along with macros specifying their limits and macro functions to create values of these types.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?
You can fill up exactly the amount of space you want in a file which is good for things like bitmap headers.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?
BYTE is 1 byte, DWORD is 4 bytes, LONG is 4 bytes and WORD is 2 bytes.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."
0x4d42

## What's the difference between `bfSize` and `biSize`?
bfSize is size of file in bytes, where biSize is the number of bytes required by the structure.

## What does it mean if `biHeight` is negative?
It's pixels are starting at top left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?
biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?
fopen might return a NULL pointer if the file that fopen is trying to write to doesn't exist.

## Why is the third argument to `fread` always `1` in our code?
Becouse we need 'one' unit of structured header.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?
If biWidth is 3:
int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4 = 3.
This step ensures the number of bytes in every row is a multiple of 4.

## What does `fseek` do?
fseek allows us to change the offset of a pointer.

## What is `SEEK_CUR`?
SEEK_CUR is the current position indicator in the file.
