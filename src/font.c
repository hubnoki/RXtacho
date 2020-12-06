
// source URL
// http://libstock.mikroe.com/projects/view/1603/st7735s-1-8-inch-tft-display-demo-with-stm32

#include "font.h"

#define BYTE_X2(d) \
( ((((unsigned short)d) >> 7) & 0x1) << 15 ) | \
( ((((unsigned short)d) >> 7) & 0x1) << 14 ) | \
( ((((unsigned short)d) >> 6) & 0x1) << 13 ) | \
( ((((unsigned short)d) >> 6) & 0x1) << 12 ) | \
( ((((unsigned short)d) >> 5) & 0x1) << 11 ) | \
( ((((unsigned short)d) >> 5) & 0x1) << 10 ) | \
( ((((unsigned short)d) >> 4) & 0x1) << 9 ) | \
( ((((unsigned short)d) >> 4) & 0x1) << 8 ) | \
( ((((unsigned short)d) >> 3) & 0x1) << 7 ) | \
( ((((unsigned short)d) >> 3) & 0x1) << 6 ) | \
( ((((unsigned short)d) >> 2) & 0x1) << 5 ) | \
( ((((unsigned short)d) >> 2) & 0x1) << 4 ) | \
( ((((unsigned short)d) >> 1) & 0x1) << 3 ) | \
( ((((unsigned short)d) >> 1) & 0x1) << 2 ) | \
( ((((unsigned short)d) >> 0) & 0x1) << 1 ) | \
( ((((unsigned short)d) >> 0) & 0x1) << 0 )

#define BYTE_X4(d) \
( ((((unsigned int)d) >> 7) & 0x1) << 31 ) | \
( ((((unsigned int)d) >> 7) & 0x1) << 30 ) | \
( ((((unsigned int)d) >> 7) & 0x1) << 29 ) | \
( ((((unsigned int)d) >> 7) & 0x1) << 28 ) | \
( ((((unsigned int)d) >> 6) & 0x1) << 27 ) | \
( ((((unsigned int)d) >> 6) & 0x1) << 26 ) | \
( ((((unsigned int)d) >> 6) & 0x1) << 25 ) | \
( ((((unsigned int)d) >> 6) & 0x1) << 24 ) | \
( ((((unsigned int)d) >> 5) & 0x1) << 23 ) | \
( ((((unsigned int)d) >> 5) & 0x1) << 22 ) | \
( ((((unsigned int)d) >> 5) & 0x1) << 21 ) | \
( ((((unsigned int)d) >> 5) & 0x1) << 20 ) | \
( ((((unsigned int)d) >> 4) & 0x1) << 19 ) | \
( ((((unsigned int)d) >> 4) & 0x1) << 18 ) | \
( ((((unsigned int)d) >> 4) & 0x1) << 17 ) | \
( ((((unsigned int)d) >> 4) & 0x1) << 16 ) | \
( ((((unsigned int)d) >> 3) & 0x1) << 15 ) | \
( ((((unsigned int)d) >> 3) & 0x1) << 14 ) | \
( ((((unsigned int)d) >> 3) & 0x1) << 13 ) | \
( ((((unsigned int)d) >> 3) & 0x1) << 12 ) | \
( ((((unsigned int)d) >> 2) & 0x1) << 11 ) | \
( ((((unsigned int)d) >> 2) & 0x1) << 10 ) | \
( ((((unsigned int)d) >> 2) & 0x1) << 9 ) | \
( ((((unsigned int)d) >> 2) & 0x1) << 8 ) | \
( ((((unsigned int)d) >> 1) & 0x1) << 7 ) | \
( ((((unsigned int)d) >> 1) & 0x1) << 6 ) | \
( ((((unsigned int)d) >> 1) & 0x1) << 5 ) | \
( ((((unsigned int)d) >> 1) & 0x1) << 4 ) | \
( ((((unsigned int)d) >> 0) & 0x1) << 3 ) | \
( ((((unsigned int)d) >> 0) & 0x1) << 2 ) | \
( ((((unsigned int)d) >> 0) & 0x1) << 1 ) | \
( ((((unsigned int)d) >> 0) & 0x1) << 0 )


//static const unsigned char font[][5] =
const FONT_DATA font[]=
{
     {{0x00, 0x00, 0x00, 0x00, 0x00}} // 20
    ,{{0x00, 0x00, 0x5f, 0x00, 0x00}} // 21 !
    ,{{0x00, 0x07, 0x00, 0x07, 0x00}} // 22 "
    ,{{0x14, 0x7f, 0x14, 0x7f, 0x14}} // 23 #
    ,{{0x24, 0x2a, 0x7f, 0x2a, 0x12}} // 24 $
    ,{{0x23, 0x13, 0x08, 0x64, 0x62}} // 25 %
    ,{{0x36, 0x49, 0x55, 0x22, 0x50}} // 26 &
    ,{{0x00, 0x05, 0x03, 0x00, 0x00}} // 27 '
    ,{{0x00, 0x1c, 0x22, 0x41, 0x00}} // 28 (
    ,{{0x00, 0x41, 0x22, 0x1c, 0x00}} // 29 )
    ,{{0x14, 0x08, 0x3e, 0x08, 0x14}} // 2a *
    ,{{0x08, 0x08, 0x3e, 0x08, 0x08}} // 2b +
    ,{{0x00, 0x50, 0x30, 0x00, 0x00}} // 2c ,
    ,{{0x08, 0x08, 0x08, 0x08, 0x08}} // 2d -
    ,{{0x00, 0x60, 0x60, 0x00, 0x00}} // 2e .
    ,{{0x20, 0x10, 0x08, 0x04, 0x02}} // 2f /
    ,{{0x3e, 0x51, 0x49, 0x45, 0x3e}} // 30 0
    ,{{0x00, 0x42, 0x7f, 0x40, 0x00}} // 31 1
    ,{{0x42, 0x61, 0x51, 0x49, 0x46}} // 32 2
    ,{{0x21, 0x41, 0x45, 0x4b, 0x31}} // 33 3
    ,{{0x18, 0x14, 0x12, 0x7f, 0x10}} // 34 4
    ,{{0x27, 0x45, 0x45, 0x45, 0x39}} // 35 5
    ,{{0x3c, 0x4a, 0x49, 0x49, 0x30}} // 36 6
    ,{{0x01, 0x71, 0x09, 0x05, 0x03}} // 37 7
    ,{{0x36, 0x49, 0x49, 0x49, 0x36}} // 38 8
    ,{{0x06, 0x49, 0x49, 0x29, 0x1e}} // 39 9
    ,{{0x00, 0x36, 0x36, 0x00, 0x00}} // 3a :
    ,{{0x00, 0x56, 0x36, 0x00, 0x00}} // 3b ;
    ,{{0x08, 0x14, 0x22, 0x41, 0x00}} // 3c <
    ,{{0x14, 0x14, 0x14, 0x14, 0x14}} // 3d =
    ,{{0x00, 0x41, 0x22, 0x14, 0x08}} // 3e >
    ,{{0x02, 0x01, 0x51, 0x09, 0x06}} // 3f ?
    ,{{0x32, 0x49, 0x79, 0x41, 0x3e}} // 40 @
    ,{{0x7e, 0x11, 0x11, 0x11, 0x7e}} // 41 A
    ,{{0x7f, 0x49, 0x49, 0x49, 0x36}} // 42 B
    ,{{0x3e, 0x41, 0x41, 0x41, 0x22}} // 43 C
    ,{{0x7f, 0x41, 0x41, 0x22, 0x1c}} // 44 D
    ,{{0x7f, 0x49, 0x49, 0x49, 0x41}} // 45 E
    ,{{0x7f, 0x09, 0x09, 0x09, 0x01}} // 46 F
    ,{{0x3e, 0x41, 0x49, 0x49, 0x7a}} // 47 G
    ,{{0x7f, 0x08, 0x08, 0x08, 0x7f}} // 48 H
    ,{{0x00, 0x41, 0x7f, 0x41, 0x00}} // 49 I
    ,{{0x20, 0x40, 0x41, 0x3f, 0x01}} // 4a J
    ,{{0x7f, 0x08, 0x14, 0x22, 0x41}} // 4b K
    ,{{0x7f, 0x40, 0x40, 0x40, 0x40}} // 4c L
    ,{{0x7f, 0x02, 0x0c, 0x02, 0x7f}} // 4d M
    ,{{0x7f, 0x04, 0x08, 0x10, 0x7f}} // 4e N
    ,{{0x3e, 0x41, 0x41, 0x41, 0x3e}} // 4f O
    ,{{0x7f, 0x09, 0x09, 0x09, 0x06}} // 50 P
    ,{{0x3e, 0x41, 0x51, 0x21, 0x5e}} // 51 Q
    ,{{0x7f, 0x09, 0x19, 0x29, 0x46}} // 52 R
    ,{{0x46, 0x49, 0x49, 0x49, 0x31}} // 53 S
    ,{{0x01, 0x01, 0x7f, 0x01, 0x01}} // 54 T
    ,{{0x3f, 0x40, 0x40, 0x40, 0x3f}} // 55 U
    ,{{0x1f, 0x20, 0x40, 0x20, 0x1f}} // 56 V
    ,{{0x3f, 0x40, 0x38, 0x40, 0x3f}} // 57 W
    ,{{0x63, 0x14, 0x08, 0x14, 0x63}} // 58 X
    ,{{0x07, 0x08, 0x70, 0x08, 0x07}} // 59 Y
    ,{{0x61, 0x51, 0x49, 0x45, 0x43}} // 5a Z
    ,{{0x00, 0x7f, 0x41, 0x41, 0x00}} // 5b [
    ,{{0x02, 0x04, 0x08, 0x10, 0x20}} // 5c ?
    ,{{0x00, 0x41, 0x41, 0x7f, 0x00}} // 5d ]
    ,{{0x04, 0x02, 0x01, 0x02, 0x04}} // 5e ^
    ,{{0x40, 0x40, 0x40, 0x40, 0x40}} // 5f _
    ,{{0x00, 0x01, 0x02, 0x04, 0x00}} // 60 `
    ,{{0x20, 0x54, 0x54, 0x54, 0x78}} // 61 a
    ,{{0x7f, 0x48, 0x44, 0x44, 0x38}} // 62 b
    ,{{0x38, 0x44, 0x44, 0x44, 0x20}} // 63 c
    ,{{0x38, 0x44, 0x44, 0x48, 0x7f}} // 64 d
    ,{{0x38, 0x54, 0x54, 0x54, 0x18}} // 65 e
    ,{{0x08, 0x7e, 0x09, 0x01, 0x02}} // 66 f
    ,{{0x0c, 0x52, 0x52, 0x52, 0x3e}} // 67 g
    ,{{0x7f, 0x08, 0x04, 0x04, 0x78}} // 68 h
    ,{{0x00, 0x44, 0x7d, 0x40, 0x00}} // 69 i
    ,{{0x20, 0x40, 0x44, 0x3d, 0x00}} // 6a j
    ,{{0x7f, 0x10, 0x28, 0x44, 0x00}} // 6b k
    ,{{0x00, 0x41, 0x7f, 0x40, 0x00}} // 6c l
    ,{{0x7c, 0x04, 0x18, 0x04, 0x78}} // 6d m
    ,{{0x7c, 0x08, 0x04, 0x04, 0x78}} // 6e n
    ,{{0x38, 0x44, 0x44, 0x44, 0x38}} // 6f o
    ,{{0x7c, 0x14, 0x14, 0x14, 0x08}} // 70 p
    ,{{0x08, 0x14, 0x14, 0x18, 0x7c}} // 71 q
    ,{{0x7c, 0x08, 0x04, 0x04, 0x08}} // 72 r
    ,{{0x48, 0x54, 0x54, 0x54, 0x20}} // 73 s
    ,{{0x04, 0x3f, 0x44, 0x40, 0x20}} // 74 t
    ,{{0x3c, 0x40, 0x40, 0x20, 0x7c}} // 75 u
    ,{{0x1c, 0x20, 0x40, 0x20, 0x1c}} // 76 v
    ,{{0x3c, 0x40, 0x30, 0x40, 0x3c}} // 77 w
    ,{{0x44, 0x28, 0x10, 0x28, 0x44}} // 78 x
    ,{{0x0c, 0x50, 0x50, 0x50, 0x3c}} // 79 y
    ,{{0x44, 0x64, 0x54, 0x4c, 0x44}} // 7a z
    ,{{0x00, 0x08, 0x36, 0x41, 0x00}} // 7b {
    ,{{0x00, 0x00, 0x7f, 0x00, 0x00}} // 7c |
    ,{{0x00, 0x41, 0x36, 0x08, 0x00}} // 7d }
    ,{{0x10, 0x08, 0x08, 0x10, 0x08}} // 7e ?
    ,{{0x78, 0x46, 0x41, 0x46, 0x78}} // 7f ?
};


const FONT_DATA_X4 font_x4[] = 
{

     {{
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00)
    }} // 20
    ,{{
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x5f),BYTE_X4(0x5f),BYTE_X4(0x5f),BYTE_X4(0x5f),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00)
    }} // 21 !
    ,{{
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x07),BYTE_X4(0x07),BYTE_X4(0x07),BYTE_X4(0x07),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x07),BYTE_X4(0x07),BYTE_X4(0x07),BYTE_X4(0x07),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00)
    }} // 22 "
    ,{{
        BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14)
    }} // 23 #
    ,{{
        BYTE_X4(0x24),BYTE_X4(0x24),BYTE_X4(0x24),BYTE_X4(0x24),
        BYTE_X4(0x2a),BYTE_X4(0x2a),BYTE_X4(0x2a),BYTE_X4(0x2a),
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x2a),BYTE_X4(0x2a),BYTE_X4(0x2a),BYTE_X4(0x2a),
        BYTE_X4(0x12),BYTE_X4(0x12),BYTE_X4(0x12),BYTE_X4(0x12)
    }} // 24 $
    ,{{
        BYTE_X4(0x23),BYTE_X4(0x23),BYTE_X4(0x23),BYTE_X4(0x23),
        BYTE_X4(0x13),BYTE_X4(0x13),BYTE_X4(0x13),BYTE_X4(0x13),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x64),BYTE_X4(0x64),BYTE_X4(0x64),BYTE_X4(0x64),
        BYTE_X4(0x62),BYTE_X4(0x62),BYTE_X4(0x62),BYTE_X4(0x62)
    }} // 25 %
    ,{{
        BYTE_X4(0x36),BYTE_X4(0x36),BYTE_X4(0x36),BYTE_X4(0x36),
        BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),
        BYTE_X4(0x55),BYTE_X4(0x55),BYTE_X4(0x55),BYTE_X4(0x55),
        BYTE_X4(0x22),BYTE_X4(0x22),BYTE_X4(0x22),BYTE_X4(0x22),
        BYTE_X4(0x50),BYTE_X4(0x50),BYTE_X4(0x50),BYTE_X4(0x50)
    }} // 26 &
    ,{{
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x05),BYTE_X4(0x05),BYTE_X4(0x05),BYTE_X4(0x05),
        BYTE_X4(0x03),BYTE_X4(0x03),BYTE_X4(0x03),BYTE_X4(0x03),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00)
    }} // 27 '
    ,{{
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x1c),BYTE_X4(0x1c),BYTE_X4(0x1c),BYTE_X4(0x1c),
        BYTE_X4(0x22),BYTE_X4(0x22),BYTE_X4(0x22),BYTE_X4(0x22),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00)
    }} // 28 (
    ,{{
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x22),BYTE_X4(0x22),BYTE_X4(0x22),BYTE_X4(0x22),
        BYTE_X4(0x1c),BYTE_X4(0x1c),BYTE_X4(0x1c),BYTE_X4(0x1c),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00)
    }} // 29 )
    ,{{
        BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x3e),BYTE_X4(0x3e),BYTE_X4(0x3e),BYTE_X4(0x3e),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14)
    }} // 2a *
    ,{{
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x3e),BYTE_X4(0x3e),BYTE_X4(0x3e),BYTE_X4(0x3e),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08)
    }} // 2b +
    ,{{
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x50),BYTE_X4(0x50),BYTE_X4(0x50),BYTE_X4(0x50),
        BYTE_X4(0x30),BYTE_X4(0x30),BYTE_X4(0x30),BYTE_X4(0x30),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00)
    }} // 2c ,
    ,{{
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08)
    }} // 2d -
    ,{{
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x60),BYTE_X4(0x60),BYTE_X4(0x60),BYTE_X4(0x60),
        BYTE_X4(0x60),BYTE_X4(0x60),BYTE_X4(0x60),BYTE_X4(0x60),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00)
    }} // 2e .
    ,{{
        BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20),
        BYTE_X4(0x10),BYTE_X4(0x10),BYTE_X4(0x10),BYTE_X4(0x10),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),
        BYTE_X4(0x02),BYTE_X4(0x02),BYTE_X4(0x02),BYTE_X4(0x02)
    }} // 2f /
    ,{{
        BYTE_X4(0x3e),BYTE_X4(0x3e),BYTE_X4(0x3e),BYTE_X4(0x3e),
        BYTE_X4(0x51),BYTE_X4(0x51),BYTE_X4(0x51),BYTE_X4(0x51),
        BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),
        BYTE_X4(0x45),BYTE_X4(0x45),BYTE_X4(0x45),BYTE_X4(0x45),
        BYTE_X4(0x3e),BYTE_X4(0x3e),BYTE_X4(0x3e),BYTE_X4(0x3e)
    }} // 30 0
    ,{{
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x42),BYTE_X4(0x42),BYTE_X4(0x42),BYTE_X4(0x42),
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00)
    }} // 31 1
    ,{{
        BYTE_X4(0x42),BYTE_X4(0x42),BYTE_X4(0x42),BYTE_X4(0x42),
        BYTE_X4(0x61),BYTE_X4(0x61),BYTE_X4(0x61),BYTE_X4(0x61),
        BYTE_X4(0x51),BYTE_X4(0x51),BYTE_X4(0x51),BYTE_X4(0x51),
        BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),
        BYTE_X4(0x46),BYTE_X4(0x46),BYTE_X4(0x46),BYTE_X4(0x46)
    }} // 32 2
    ,{{
        BYTE_X4(0x21),BYTE_X4(0x21),BYTE_X4(0x21),BYTE_X4(0x21),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x45),BYTE_X4(0x45),BYTE_X4(0x45),BYTE_X4(0x45),
        BYTE_X4(0x4b),BYTE_X4(0x4b),BYTE_X4(0x4b),BYTE_X4(0x4b),
        BYTE_X4(0x31),BYTE_X4(0x31),BYTE_X4(0x31),BYTE_X4(0x31)
    }} // 33 3
    ,{{
        BYTE_X4(0x18),BYTE_X4(0x18),BYTE_X4(0x18),BYTE_X4(0x18),
        BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),
        BYTE_X4(0x12),BYTE_X4(0x12),BYTE_X4(0x12),BYTE_X4(0x12),
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x10),BYTE_X4(0x10),BYTE_X4(0x10),BYTE_X4(0x10)
    }} // 34 4
    ,{{
        BYTE_X4(0x27),BYTE_X4(0x27),BYTE_X4(0x27),BYTE_X4(0x27),
        BYTE_X4(0x45),BYTE_X4(0x45),BYTE_X4(0x45),BYTE_X4(0x45),
        BYTE_X4(0x45),BYTE_X4(0x45),BYTE_X4(0x45),BYTE_X4(0x45),
        BYTE_X4(0x45),BYTE_X4(0x45),BYTE_X4(0x45),BYTE_X4(0x45),
        BYTE_X4(0x39),BYTE_X4(0x39),BYTE_X4(0x39),BYTE_X4(0x39)
    }} // 35 5
    ,{{
        BYTE_X4(0x3c),BYTE_X4(0x3c),BYTE_X4(0x3c),BYTE_X4(0x3c),
        BYTE_X4(0x4a),BYTE_X4(0x4a),BYTE_X4(0x4a),BYTE_X4(0x4a),
        BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),
        BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),
        BYTE_X4(0x30),BYTE_X4(0x30),BYTE_X4(0x30),BYTE_X4(0x30)
    }} // 36 6
    ,{{
        BYTE_X4(0x01),BYTE_X4(0x01),BYTE_X4(0x01),BYTE_X4(0x01),
        BYTE_X4(0x71),BYTE_X4(0x71),BYTE_X4(0x71),BYTE_X4(0x71),
        BYTE_X4(0x09),BYTE_X4(0x09),BYTE_X4(0x09),BYTE_X4(0x09),
        BYTE_X4(0x05),BYTE_X4(0x05),BYTE_X4(0x05),BYTE_X4(0x05),
        BYTE_X4(0x03),BYTE_X4(0x03),BYTE_X4(0x03),BYTE_X4(0x03)
    }} // 37 7
    ,{{
        BYTE_X4(0x36),BYTE_X4(0x36),BYTE_X4(0x36),BYTE_X4(0x36),
        BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),
        BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),
        BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),
        BYTE_X4(0x36),BYTE_X4(0x36),BYTE_X4(0x36),BYTE_X4(0x36)
    }} // 38 8
    ,{{
        BYTE_X4(0x06),BYTE_X4(0x06),BYTE_X4(0x06),BYTE_X4(0x06),
        BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),
        BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),
        BYTE_X4(0x29),BYTE_X4(0x29),BYTE_X4(0x29),BYTE_X4(0x29),
        BYTE_X4(0x1e),BYTE_X4(0x1e),BYTE_X4(0x1e),BYTE_X4(0x1e)
    }} // 39 9
    ,{{
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x36),BYTE_X4(0x36),BYTE_X4(0x36),BYTE_X4(0x36),
        BYTE_X4(0x36),BYTE_X4(0x36),BYTE_X4(0x36),BYTE_X4(0x36),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00)
    }} // 3a :
    ,{{
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x56),BYTE_X4(0x56),BYTE_X4(0x56),BYTE_X4(0x56),
        BYTE_X4(0x36),BYTE_X4(0x36),BYTE_X4(0x36),BYTE_X4(0x36),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00)
    }} // 3b ;
    ,{{
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),
        BYTE_X4(0x22),BYTE_X4(0x22),BYTE_X4(0x22),BYTE_X4(0x22),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00)
    }} // 3c <
    ,{{
        BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),
        BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),
        BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),
        BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),
        BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14)
    }} // 3d =
    ,{{
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x22),BYTE_X4(0x22),BYTE_X4(0x22),BYTE_X4(0x22),
        BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08)
    }} // 3e >
    ,{{
        BYTE_X4(0x02),BYTE_X4(0x02),BYTE_X4(0x02),BYTE_X4(0x02),
        BYTE_X4(0x01),BYTE_X4(0x01),BYTE_X4(0x01),BYTE_X4(0x01),
        BYTE_X4(0x51),BYTE_X4(0x51),BYTE_X4(0x51),BYTE_X4(0x51),
        BYTE_X4(0x09),BYTE_X4(0x09),BYTE_X4(0x09),BYTE_X4(0x09),
        BYTE_X4(0x06),BYTE_X4(0x06),BYTE_X4(0x06),BYTE_X4(0x06)
    }} // 3f ?
    ,{{
        BYTE_X4(0x32),BYTE_X4(0x32),BYTE_X4(0x32),BYTE_X4(0x32),
        BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),
        BYTE_X4(0x79),BYTE_X4(0x79),BYTE_X4(0x79),BYTE_X4(0x79),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x3e),BYTE_X4(0x3e),BYTE_X4(0x3e),BYTE_X4(0x3e)
    }} // 40 @
    ,{{
        BYTE_X4(0x7e),BYTE_X4(0x7e),BYTE_X4(0x7e),BYTE_X4(0x7e),
        BYTE_X4(0x11),BYTE_X4(0x11),BYTE_X4(0x11),BYTE_X4(0x11),
        BYTE_X4(0x11),BYTE_X4(0x11),BYTE_X4(0x11),BYTE_X4(0x11),
        BYTE_X4(0x11),BYTE_X4(0x11),BYTE_X4(0x11),BYTE_X4(0x11),
        BYTE_X4(0x7e),BYTE_X4(0x7e),BYTE_X4(0x7e),BYTE_X4(0x7e)
    }} // 41 A
    ,{{
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),
        BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),
        BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),
        BYTE_X4(0x36),BYTE_X4(0x36),BYTE_X4(0x36),BYTE_X4(0x36)
    }} // 42 B
    ,{{
        BYTE_X4(0x3e),BYTE_X4(0x3e),BYTE_X4(0x3e),BYTE_X4(0x3e),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x22),BYTE_X4(0x22),BYTE_X4(0x22),BYTE_X4(0x22)
    }} // 43 C
    ,{{
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x22),BYTE_X4(0x22),BYTE_X4(0x22),BYTE_X4(0x22),
        BYTE_X4(0x1c),BYTE_X4(0x1c),BYTE_X4(0x1c),BYTE_X4(0x1c)
    }} // 44 D
    ,{{
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),
        BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),
        BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41)
    }} // 45 E
    ,{{
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x09),BYTE_X4(0x09),BYTE_X4(0x09),BYTE_X4(0x09),
        BYTE_X4(0x09),BYTE_X4(0x09),BYTE_X4(0x09),BYTE_X4(0x09),
        BYTE_X4(0x09),BYTE_X4(0x09),BYTE_X4(0x09),BYTE_X4(0x09),
        BYTE_X4(0x01),BYTE_X4(0x01),BYTE_X4(0x01),BYTE_X4(0x01)
    }} // 46 F
    ,{{
        BYTE_X4(0x3e),BYTE_X4(0x3e),BYTE_X4(0x3e),BYTE_X4(0x3e),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),
        BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),
        BYTE_X4(0x7a),BYTE_X4(0x7a),BYTE_X4(0x7a),BYTE_X4(0x7a)
    }} // 47 G
    ,{{
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f)
    }} // 48 H
    ,{{
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00)
    }} // 49 I
    ,{{
        BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x3f),BYTE_X4(0x3f),BYTE_X4(0x3f),BYTE_X4(0x3f),
        BYTE_X4(0x01),BYTE_X4(0x01),BYTE_X4(0x01),BYTE_X4(0x01)
    }} // 4a J
    ,{{
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),
        BYTE_X4(0x22),BYTE_X4(0x22),BYTE_X4(0x22),BYTE_X4(0x22),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41)
    }} // 4b K
    ,{{
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40)
    }} // 4c L
    ,{{
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x02),BYTE_X4(0x02),BYTE_X4(0x02),BYTE_X4(0x02),
        BYTE_X4(0x0c),BYTE_X4(0x0c),BYTE_X4(0x0c),BYTE_X4(0x0c),
        BYTE_X4(0x02),BYTE_X4(0x02),BYTE_X4(0x02),BYTE_X4(0x02),
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f)
    }} // 4d M
    ,{{
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x10),BYTE_X4(0x10),BYTE_X4(0x10),BYTE_X4(0x10),
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f)
    }} // 4e N
    ,{{
        BYTE_X4(0x3e),BYTE_X4(0x3e),BYTE_X4(0x3e),BYTE_X4(0x3e),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x3e),BYTE_X4(0x3e),BYTE_X4(0x3e),BYTE_X4(0x3e)
    }} // 4f O
    ,{{
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x09),BYTE_X4(0x09),BYTE_X4(0x09),BYTE_X4(0x09),
        BYTE_X4(0x09),BYTE_X4(0x09),BYTE_X4(0x09),BYTE_X4(0x09),
        BYTE_X4(0x09),BYTE_X4(0x09),BYTE_X4(0x09),BYTE_X4(0x09),
        BYTE_X4(0x06),BYTE_X4(0x06),BYTE_X4(0x06),BYTE_X4(0x06)
    }} // 50 P
    ,{{
        BYTE_X4(0x3e),BYTE_X4(0x3e),BYTE_X4(0x3e),BYTE_X4(0x3e),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x51),BYTE_X4(0x51),BYTE_X4(0x51),BYTE_X4(0x51),
        BYTE_X4(0x21),BYTE_X4(0x21),BYTE_X4(0x21),BYTE_X4(0x21),
        BYTE_X4(0x5e),BYTE_X4(0x5e),BYTE_X4(0x5e),BYTE_X4(0x5e)
    }} // 51 Q
    ,{{
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x09),BYTE_X4(0x09),BYTE_X4(0x09),BYTE_X4(0x09),
        BYTE_X4(0x19),BYTE_X4(0x19),BYTE_X4(0x19),BYTE_X4(0x19),
        BYTE_X4(0x29),BYTE_X4(0x29),BYTE_X4(0x29),BYTE_X4(0x29),
        BYTE_X4(0x46),BYTE_X4(0x46),BYTE_X4(0x46),BYTE_X4(0x46)
    }} // 52 R
    ,{{
        BYTE_X4(0x46),BYTE_X4(0x46),BYTE_X4(0x46),BYTE_X4(0x46),
        BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),
        BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),
        BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),
        BYTE_X4(0x31),BYTE_X4(0x31),BYTE_X4(0x31),BYTE_X4(0x31)
    }} // 53 S
    ,{{
        BYTE_X4(0x01),BYTE_X4(0x01),BYTE_X4(0x01),BYTE_X4(0x01),
        BYTE_X4(0x01),BYTE_X4(0x01),BYTE_X4(0x01),BYTE_X4(0x01),
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x01),BYTE_X4(0x01),BYTE_X4(0x01),BYTE_X4(0x01),
        BYTE_X4(0x01),BYTE_X4(0x01),BYTE_X4(0x01),BYTE_X4(0x01)
    }} // 54 T
    ,{{
        BYTE_X4(0x3f),BYTE_X4(0x3f),BYTE_X4(0x3f),BYTE_X4(0x3f),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),
        BYTE_X4(0x3f),BYTE_X4(0x3f),BYTE_X4(0x3f),BYTE_X4(0x3f)
    }} // 55 U
    ,{{
        BYTE_X4(0x1f),BYTE_X4(0x1f),BYTE_X4(0x1f),BYTE_X4(0x1f),
        BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),
        BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20),
        BYTE_X4(0x1f),BYTE_X4(0x1f),BYTE_X4(0x1f),BYTE_X4(0x1f)
    }} // 56 V
    ,{{
        BYTE_X4(0x3f),BYTE_X4(0x3f),BYTE_X4(0x3f),BYTE_X4(0x3f),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),
        BYTE_X4(0x38),BYTE_X4(0x38),BYTE_X4(0x38),BYTE_X4(0x38),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),
        BYTE_X4(0x3f),BYTE_X4(0x3f),BYTE_X4(0x3f),BYTE_X4(0x3f)
    }} // 57 W
    ,{{
        BYTE_X4(0x63),BYTE_X4(0x63),BYTE_X4(0x63),BYTE_X4(0x63),
        BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),
        BYTE_X4(0x63),BYTE_X4(0x63),BYTE_X4(0x63),BYTE_X4(0x63)
    }} // 58 X
    ,{{
        BYTE_X4(0x07),BYTE_X4(0x07),BYTE_X4(0x07),BYTE_X4(0x07),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x70),BYTE_X4(0x70),BYTE_X4(0x70),BYTE_X4(0x70),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x07),BYTE_X4(0x07),BYTE_X4(0x07),BYTE_X4(0x07)
    }} // 59 Y
    ,{{
        BYTE_X4(0x61),BYTE_X4(0x61),BYTE_X4(0x61),BYTE_X4(0x61),
        BYTE_X4(0x51),BYTE_X4(0x51),BYTE_X4(0x51),BYTE_X4(0x51),
        BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),BYTE_X4(0x49),
        BYTE_X4(0x45),BYTE_X4(0x45),BYTE_X4(0x45),BYTE_X4(0x45),
        BYTE_X4(0x43),BYTE_X4(0x43),BYTE_X4(0x43),BYTE_X4(0x43)
    }} // 5a Z
    ,{{
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00)
    }} // 5b [
    ,{{
        BYTE_X4(0x02),BYTE_X4(0x02),BYTE_X4(0x02),BYTE_X4(0x02),
        BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x10),BYTE_X4(0x10),BYTE_X4(0x10),BYTE_X4(0x10),
        BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20)
    }} // 5c ?
    ,{{
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00)
    }} // 5d ]
    ,{{
        BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),
        BYTE_X4(0x02),BYTE_X4(0x02),BYTE_X4(0x02),BYTE_X4(0x02),
        BYTE_X4(0x01),BYTE_X4(0x01),BYTE_X4(0x01),BYTE_X4(0x01),
        BYTE_X4(0x02),BYTE_X4(0x02),BYTE_X4(0x02),BYTE_X4(0x02),
        BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04)
    }} // 5e ^
    ,{{
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40)
    }} // 5f _
    ,{{
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x01),BYTE_X4(0x01),BYTE_X4(0x01),BYTE_X4(0x01),
        BYTE_X4(0x02),BYTE_X4(0x02),BYTE_X4(0x02),BYTE_X4(0x02),
        BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00)
    }} // 60 `
    ,{{
        BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20),
        BYTE_X4(0x54),BYTE_X4(0x54),BYTE_X4(0x54),BYTE_X4(0x54),
        BYTE_X4(0x54),BYTE_X4(0x54),BYTE_X4(0x54),BYTE_X4(0x54),
        BYTE_X4(0x54),BYTE_X4(0x54),BYTE_X4(0x54),BYTE_X4(0x54),
        BYTE_X4(0x78),BYTE_X4(0x78),BYTE_X4(0x78),BYTE_X4(0x78)
    }} // 61 a
    ,{{
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x48),BYTE_X4(0x48),BYTE_X4(0x48),BYTE_X4(0x48),
        BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),
        BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),
        BYTE_X4(0x38),BYTE_X4(0x38),BYTE_X4(0x38),BYTE_X4(0x38)
    }} // 62 b
    ,{{
        BYTE_X4(0x38),BYTE_X4(0x38),BYTE_X4(0x38),BYTE_X4(0x38),
        BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),
        BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),
        BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),
        BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20)
    }} // 63 c
    ,{{
        BYTE_X4(0x38),BYTE_X4(0x38),BYTE_X4(0x38),BYTE_X4(0x38),
        BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),
        BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),
        BYTE_X4(0x48),BYTE_X4(0x48),BYTE_X4(0x48),BYTE_X4(0x48),
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f)
    }} // 64 d
    ,{{
        BYTE_X4(0x38),BYTE_X4(0x38),BYTE_X4(0x38),BYTE_X4(0x38),
        BYTE_X4(0x54),BYTE_X4(0x54),BYTE_X4(0x54),BYTE_X4(0x54),
        BYTE_X4(0x54),BYTE_X4(0x54),BYTE_X4(0x54),BYTE_X4(0x54),
        BYTE_X4(0x54),BYTE_X4(0x54),BYTE_X4(0x54),BYTE_X4(0x54),
        BYTE_X4(0x18),BYTE_X4(0x18),BYTE_X4(0x18),BYTE_X4(0x18)
    }} // 65 e
    ,{{
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x7e),BYTE_X4(0x7e),BYTE_X4(0x7e),BYTE_X4(0x7e),
        BYTE_X4(0x09),BYTE_X4(0x09),BYTE_X4(0x09),BYTE_X4(0x09),
        BYTE_X4(0x01),BYTE_X4(0x01),BYTE_X4(0x01),BYTE_X4(0x01),
        BYTE_X4(0x02),BYTE_X4(0x02),BYTE_X4(0x02),BYTE_X4(0x02)
    }} // 66 f
    ,{{
        BYTE_X4(0x0c),BYTE_X4(0x0c),BYTE_X4(0x0c),BYTE_X4(0x0c),
        BYTE_X4(0x52),BYTE_X4(0x52),BYTE_X4(0x52),BYTE_X4(0x52),
        BYTE_X4(0x52),BYTE_X4(0x52),BYTE_X4(0x52),BYTE_X4(0x52),
        BYTE_X4(0x52),BYTE_X4(0x52),BYTE_X4(0x52),BYTE_X4(0x52),
        BYTE_X4(0x3e),BYTE_X4(0x3e),BYTE_X4(0x3e),BYTE_X4(0x3e)
    }} // 67 g
    ,{{
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),
        BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),
        BYTE_X4(0x78),BYTE_X4(0x78),BYTE_X4(0x78),BYTE_X4(0x78)
    }} // 68 h
    ,{{
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),
        BYTE_X4(0x7d),BYTE_X4(0x7d),BYTE_X4(0x7d),BYTE_X4(0x7d),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00)
    }} // 69 i
    ,{{
        BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),
        BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),
        BYTE_X4(0x3d),BYTE_X4(0x3d),BYTE_X4(0x3d),BYTE_X4(0x3d),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00)
    }} // 6a j
    ,{{
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x10),BYTE_X4(0x10),BYTE_X4(0x10),BYTE_X4(0x10),
        BYTE_X4(0x28),BYTE_X4(0x28),BYTE_X4(0x28),BYTE_X4(0x28),
        BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00)
    }} // 6b k
    ,{{
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00)
    }} // 6c l
    ,{{
        BYTE_X4(0x7c),BYTE_X4(0x7c),BYTE_X4(0x7c),BYTE_X4(0x7c),
        BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),
        BYTE_X4(0x18),BYTE_X4(0x18),BYTE_X4(0x18),BYTE_X4(0x18),
        BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),
        BYTE_X4(0x78),BYTE_X4(0x78),BYTE_X4(0x78),BYTE_X4(0x78)
    }} // 6d m
    ,{{
        BYTE_X4(0x7c),BYTE_X4(0x7c),BYTE_X4(0x7c),BYTE_X4(0x7c),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),
        BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),
        BYTE_X4(0x78),BYTE_X4(0x78),BYTE_X4(0x78),BYTE_X4(0x78)
    }} // 6e n
    ,{{
        BYTE_X4(0x38),BYTE_X4(0x38),BYTE_X4(0x38),BYTE_X4(0x38),
        BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),
        BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),
        BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),
        BYTE_X4(0x38),BYTE_X4(0x38),BYTE_X4(0x38),BYTE_X4(0x38)
    }} // 6f o
    ,{{
        BYTE_X4(0x7c),BYTE_X4(0x7c),BYTE_X4(0x7c),BYTE_X4(0x7c),
        BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),
        BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),
        BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08)
    }} // 70 p
    ,{{
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),
        BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),BYTE_X4(0x14),
        BYTE_X4(0x18),BYTE_X4(0x18),BYTE_X4(0x18),BYTE_X4(0x18),
        BYTE_X4(0x7c),BYTE_X4(0x7c),BYTE_X4(0x7c),BYTE_X4(0x7c)
    }} // 71 q
    ,{{
        BYTE_X4(0x7c),BYTE_X4(0x7c),BYTE_X4(0x7c),BYTE_X4(0x7c),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),
        BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08)
    }} // 72 r
    ,{{
        BYTE_X4(0x48),BYTE_X4(0x48),BYTE_X4(0x48),BYTE_X4(0x48),
        BYTE_X4(0x54),BYTE_X4(0x54),BYTE_X4(0x54),BYTE_X4(0x54),
        BYTE_X4(0x54),BYTE_X4(0x54),BYTE_X4(0x54),BYTE_X4(0x54),
        BYTE_X4(0x54),BYTE_X4(0x54),BYTE_X4(0x54),BYTE_X4(0x54),
        BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20)
    }} // 73 s
    ,{{
        BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),BYTE_X4(0x04),
        BYTE_X4(0x3f),BYTE_X4(0x3f),BYTE_X4(0x3f),BYTE_X4(0x3f),
        BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),
        BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20)
    }} // 74 t
    ,{{
        BYTE_X4(0x3c),BYTE_X4(0x3c),BYTE_X4(0x3c),BYTE_X4(0x3c),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),
        BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20),
        BYTE_X4(0x7c),BYTE_X4(0x7c),BYTE_X4(0x7c),BYTE_X4(0x7c)
    }} // 75 u
    ,{{
        BYTE_X4(0x1c),BYTE_X4(0x1c),BYTE_X4(0x1c),BYTE_X4(0x1c),
        BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),
        BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20),BYTE_X4(0x20),
        BYTE_X4(0x1c),BYTE_X4(0x1c),BYTE_X4(0x1c),BYTE_X4(0x1c)
    }} // 76 v
    ,{{
        BYTE_X4(0x3c),BYTE_X4(0x3c),BYTE_X4(0x3c),BYTE_X4(0x3c),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),
        BYTE_X4(0x30),BYTE_X4(0x30),BYTE_X4(0x30),BYTE_X4(0x30),
        BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),BYTE_X4(0x40),
        BYTE_X4(0x3c),BYTE_X4(0x3c),BYTE_X4(0x3c),BYTE_X4(0x3c)
    }} // 77 w
    ,{{
        BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),
        BYTE_X4(0x28),BYTE_X4(0x28),BYTE_X4(0x28),BYTE_X4(0x28),
        BYTE_X4(0x10),BYTE_X4(0x10),BYTE_X4(0x10),BYTE_X4(0x10),
        BYTE_X4(0x28),BYTE_X4(0x28),BYTE_X4(0x28),BYTE_X4(0x28),
        BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44)
    }} // 78 x
    ,{{
        BYTE_X4(0x0c),BYTE_X4(0x0c),BYTE_X4(0x0c),BYTE_X4(0x0c),
        BYTE_X4(0x50),BYTE_X4(0x50),BYTE_X4(0x50),BYTE_X4(0x50),
        BYTE_X4(0x50),BYTE_X4(0x50),BYTE_X4(0x50),BYTE_X4(0x50),
        BYTE_X4(0x50),BYTE_X4(0x50),BYTE_X4(0x50),BYTE_X4(0x50),
        BYTE_X4(0x3c),BYTE_X4(0x3c),BYTE_X4(0x3c),BYTE_X4(0x3c)
    }} // 79 y
    ,{{
        BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),
        BYTE_X4(0x64),BYTE_X4(0x64),BYTE_X4(0x64),BYTE_X4(0x64),
        BYTE_X4(0x54),BYTE_X4(0x54),BYTE_X4(0x54),BYTE_X4(0x54),
        BYTE_X4(0x4c),BYTE_X4(0x4c),BYTE_X4(0x4c),BYTE_X4(0x4c),
        BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44),BYTE_X4(0x44)
    }} // 7a z
    ,{{
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x36),BYTE_X4(0x36),BYTE_X4(0x36),BYTE_X4(0x36),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00)
    }} // 7b {
    ,{{
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),BYTE_X4(0x7f),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00)
    }} // 7c |
    ,{{
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x36),BYTE_X4(0x36),BYTE_X4(0x36),BYTE_X4(0x36),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00),BYTE_X4(0x00)
    }} // 7d }
    ,{{
        BYTE_X4(0x10),BYTE_X4(0x10),BYTE_X4(0x10),BYTE_X4(0x10),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),
        BYTE_X4(0x10),BYTE_X4(0x10),BYTE_X4(0x10),BYTE_X4(0x10),
        BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08),BYTE_X4(0x08)
    }} // 7e ?
    ,{{
        BYTE_X4(0x78),BYTE_X4(0x78),BYTE_X4(0x78),BYTE_X4(0x78),
        BYTE_X4(0x46),BYTE_X4(0x46),BYTE_X4(0x46),BYTE_X4(0x46),
        BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),BYTE_X4(0x41),
        BYTE_X4(0x46),BYTE_X4(0x46),BYTE_X4(0x46),BYTE_X4(0x46),
        BYTE_X4(0x78),BYTE_X4(0x78),BYTE_X4(0x78),BYTE_X4(0x78)
    }} // 7f ?



    // {
    //     BYTE_X4( (font[0x00].f[0]) ), BYTE_X4( (font[0x00].f[0]) ), BYTE_X4( (font[0x00].f[0]) ), BYTE_X4( (font[0x00].f[0]) ), 
    //     BYTE_X4( (font[0x00].f[1]) ), BYTE_X4( (font[0x00].f[1]) ), BYTE_X4( (font[0x00].f[1]) ), BYTE_X4( (font[0x00].f[1]) ), 
    //     BYTE_X4( (font[0x00].f[2]) ), BYTE_X4( (font[0x00].f[2]) ), BYTE_X4( (font[0x00].f[2]) ), BYTE_X4( (font[0x00].f[2]) ), 
    //     BYTE_X4( (font[0x00].f[3]) ), BYTE_X4( (font[0x00].f[3]) ), BYTE_X4( (font[0x00].f[3]) ), BYTE_X4( (font[0x00].f[3]) ),
    //     BYTE_X4( (font[0x00].f[4]) ), BYTE_X4( (font[0x00].f[4]) ), BYTE_X4( (font[0x00].f[4]) ), BYTE_X4( (font[0x00].f[4]) )
    // } // 20
    // , {
    //     BYTE_X4( (font[0x01].f[0]) ), BYTE_X4( (font[0x01].f[0]) ), BYTE_X4( (font[0x01].f[0]) ), BYTE_X4( (font[0x01].f[0]) ), 
    //     BYTE_X4( (font[0x01].f[1]) ), BYTE_X4( (font[0x01].f[1]) ), BYTE_X4( (font[0x01].f[1]) ), BYTE_X4( (font[0x01].f[1]) ), 
    //     BYTE_X4( (font[0x01].f[2]) ), BYTE_X4( (font[0x01].f[2]) ), BYTE_X4( (font[0x01].f[2]) ), BYTE_X4( (font[0x01].f[2]) ), 
    //     BYTE_X4( (font[0x01].f[3]) ), BYTE_X4( (font[0x01].f[3]) ), BYTE_X4( (font[0x01].f[3]) ), BYTE_X4( (font[0x01].f[3]) ),
    //     BYTE_X4( (font[0x01].f[4]) ), BYTE_X4( (font[0x01].f[4]) ), BYTE_X4( (font[0x01].f[4]) ), BYTE_X4( (font[0x01].f[4]) )
    // } // 21 !
    // , {
    //     BYTE_X4( (font[0x02].f[0]) ), BYTE_X4( (font[0x02].f[0]) ), BYTE_X4( (font[0x02].f[0]) ), BYTE_X4( (font[0x02].f[0]) ), 
    //     BYTE_X4( (font[0x02].f[1]) ), BYTE_X4( (font[0x02].f[1]) ), BYTE_X4( (font[0x02].f[1]) ), BYTE_X4( (font[0x02].f[1]) ), 
    //     BYTE_X4( (font[0x02].f[2]) ), BYTE_X4( (font[0x02].f[2]) ), BYTE_X4( (font[0x02].f[2]) ), BYTE_X4( (font[0x02].f[2]) ), 
    //     BYTE_X4( (font[0x02].f[3]) ), BYTE_X4( (font[0x02].f[3]) ), BYTE_X4( (font[0x02].f[3]) ), BYTE_X4( (font[0x02].f[3]) ),
    //     BYTE_X4( (font[0x02].f[4]) ), BYTE_X4( (font[0x02].f[4]) ), BYTE_X4( (font[0x02].f[4]) ), BYTE_X4( (font[0x02].f[4]) )
    // } // 22 "
    // , {
    //     BYTE_X4( (font[0x03].f[0]) ), BYTE_X4( (font[0x03].f[0]) ), BYTE_X4( (font[0x03].f[0]) ), BYTE_X4( (font[0x03].f[0]) ), 
    //     BYTE_X4( (font[0x03].f[1]) ), BYTE_X4( (font[0x03].f[1]) ), BYTE_X4( (font[0x03].f[1]) ), BYTE_X4( (font[0x03].f[1]) ), 
    //     BYTE_X4( (font[0x03].f[2]) ), BYTE_X4( (font[0x03].f[2]) ), BYTE_X4( (font[0x03].f[2]) ), BYTE_X4( (font[0x03].f[2]) ), 
    //     BYTE_X4( (font[0x03].f[3]) ), BYTE_X4( (font[0x03].f[3]) ), BYTE_X4( (font[0x03].f[3]) ), BYTE_X4( (font[0x03].f[3]) ),
    //     BYTE_X4( (font[0x03].f[4]) ), BYTE_X4( (font[0x03].f[4]) ), BYTE_X4( (font[0x03].f[4]) ), BYTE_X4( (font[0x03].f[4]) )
    // } // 23 #
    // , {
    //     BYTE_X4( (font[0x04].f[0]) ), BYTE_X4( (font[0x04].f[0]) ), BYTE_X4( (font[0x04].f[0]) ), BYTE_X4( (font[0x04].f[0]) ), 
    //     BYTE_X4( (font[0x04].f[1]) ), BYTE_X4( (font[0x04].f[1]) ), BYTE_X4( (font[0x04].f[1]) ), BYTE_X4( (font[0x04].f[1]) ), 
    //     BYTE_X4( (font[0x04].f[2]) ), BYTE_X4( (font[0x04].f[2]) ), BYTE_X4( (font[0x04].f[2]) ), BYTE_X4( (font[0x04].f[2]) ), 
    //     BYTE_X4( (font[0x04].f[3]) ), BYTE_X4( (font[0x04].f[3]) ), BYTE_X4( (font[0x04].f[3]) ), BYTE_X4( (font[0x04].f[3]) ),
    //     BYTE_X4( (font[0x04].f[4]) ), BYTE_X4( (font[0x04].f[4]) ), BYTE_X4( (font[0x04].f[4]) ), BYTE_X4( (font[0x04].f[4]) )
    // } // 24 $
    // , {
    //     BYTE_X4( (font[0x05].f[0]) ), BYTE_X4( (font[0x05].f[0]) ), BYTE_X4( (font[0x05].f[0]) ), BYTE_X4( (font[0x05].f[0]) ), 
    //     BYTE_X4( (font[0x05].f[1]) ), BYTE_X4( (font[0x05].f[1]) ), BYTE_X4( (font[0x05].f[1]) ), BYTE_X4( (font[0x05].f[1]) ), 
    //     BYTE_X4( (font[0x05].f[2]) ), BYTE_X4( (font[0x05].f[2]) ), BYTE_X4( (font[0x05].f[2]) ), BYTE_X4( (font[0x05].f[2]) ), 
    //     BYTE_X4( (font[0x05].f[3]) ), BYTE_X4( (font[0x05].f[3]) ), BYTE_X4( (font[0x05].f[3]) ), BYTE_X4( (font[0x05].f[3]) ),
    //     BYTE_X4( (font[0x05].f[4]) ), BYTE_X4( (font[0x05].f[4]) ), BYTE_X4( (font[0x05].f[4]) ), BYTE_X4( (font[0x05].f[4]) )
    // } // 25 %
    // , {
    //     BYTE_X4( (font[0x06].f[0]) ), BYTE_X4( (font[0x06].f[0]) ), BYTE_X4( (font[0x06].f[0]) ), BYTE_X4( (font[0x06].f[0]) ), 
    //     BYTE_X4( (font[0x06].f[1]) ), BYTE_X4( (font[0x06].f[1]) ), BYTE_X4( (font[0x06].f[1]) ), BYTE_X4( (font[0x06].f[1]) ), 
    //     BYTE_X4( (font[0x06].f[2]) ), BYTE_X4( (font[0x06].f[2]) ), BYTE_X4( (font[0x06].f[2]) ), BYTE_X4( (font[0x06].f[2]) ), 
    //     BYTE_X4( (font[0x06].f[3]) ), BYTE_X4( (font[0x06].f[3]) ), BYTE_X4( (font[0x06].f[3]) ), BYTE_X4( (font[0x06].f[3]) ),
    //     BYTE_X4( (font[0x06].f[4]) ), BYTE_X4( (font[0x06].f[4]) ), BYTE_X4( (font[0x06].f[4]) ), BYTE_X4( (font[0x06].f[4]) )
    // } // 26 &
    // , {
    //     BYTE_X4( (font[0x07].f[0]) ), BYTE_X4( (font[0x07].f[0]) ), BYTE_X4( (font[0x07].f[0]) ), BYTE_X4( (font[0x07].f[0]) ), 
    //     BYTE_X4( (font[0x07].f[1]) ), BYTE_X4( (font[0x07].f[1]) ), BYTE_X4( (font[0x07].f[1]) ), BYTE_X4( (font[0x07].f[1]) ), 
    //     BYTE_X4( (font[0x07].f[2]) ), BYTE_X4( (font[0x07].f[2]) ), BYTE_X4( (font[0x07].f[2]) ), BYTE_X4( (font[0x07].f[2]) ), 
    //     BYTE_X4( (font[0x07].f[3]) ), BYTE_X4( (font[0x07].f[3]) ), BYTE_X4( (font[0x07].f[3]) ), BYTE_X4( (font[0x07].f[3]) ),
    //     BYTE_X4( (font[0x07].f[4]) ), BYTE_X4( (font[0x07].f[4]) ), BYTE_X4( (font[0x07].f[4]) ), BYTE_X4( (font[0x07].f[4]) )
    // } // 27 '
    // , {
    //     BYTE_X4( (font[0x08].f[0]) ), BYTE_X4( (font[0x08].f[0]) ), BYTE_X4( (font[0x08].f[0]) ), BYTE_X4( (font[0x08].f[0]) ), 
    //     BYTE_X4( (font[0x08].f[1]) ), BYTE_X4( (font[0x08].f[1]) ), BYTE_X4( (font[0x08].f[1]) ), BYTE_X4( (font[0x08].f[1]) ), 
    //     BYTE_X4( (font[0x08].f[2]) ), BYTE_X4( (font[0x08].f[2]) ), BYTE_X4( (font[0x08].f[2]) ), BYTE_X4( (font[0x08].f[2]) ), 
    //     BYTE_X4( (font[0x08].f[3]) ), BYTE_X4( (font[0x08].f[3]) ), BYTE_X4( (font[0x08].f[3]) ), BYTE_X4( (font[0x08].f[3]) ),
    //     BYTE_X4( (font[0x08].f[4]) ), BYTE_X4( (font[0x08].f[4]) ), BYTE_X4( (font[0x08].f[4]) ), BYTE_X4( (font[0x08].f[4]) )
    // } // 28 (
    // , {
    //     BYTE_X4( (font[0x09].f[0]) ), BYTE_X4( (font[0x09].f[0]) ), BYTE_X4( (font[0x09].f[0]) ), BYTE_X4( (font[0x09].f[0]) ), 
    //     BYTE_X4( (font[0x09].f[1]) ), BYTE_X4( (font[0x09].f[1]) ), BYTE_X4( (font[0x09].f[1]) ), BYTE_X4( (font[0x09].f[1]) ), 
    //     BYTE_X4( (font[0x09].f[2]) ), BYTE_X4( (font[0x09].f[2]) ), BYTE_X4( (font[0x09].f[2]) ), BYTE_X4( (font[0x09].f[2]) ), 
    //     BYTE_X4( (font[0x09].f[3]) ), BYTE_X4( (font[0x09].f[3]) ), BYTE_X4( (font[0x09].f[3]) ), BYTE_X4( (font[0x09].f[3]) ),
    //     BYTE_X4( (font[0x09].f[4]) ), BYTE_X4( (font[0x09].f[4]) ), BYTE_X4( (font[0x09].f[4]) ), BYTE_X4( (font[0x09].f[4]) )
    // } // 29 )
    // , {
    //     BYTE_X4( (font[0x0a].f[0]) ), BYTE_X4( (font[0x0a].f[0]) ), BYTE_X4( (font[0x0a].f[0]) ), BYTE_X4( (font[0x0a].f[0]) ), 
    //     BYTE_X4( (font[0x0a].f[1]) ), BYTE_X4( (font[0x0a].f[1]) ), BYTE_X4( (font[0x0a].f[1]) ), BYTE_X4( (font[0x0a].f[1]) ), 
    //     BYTE_X4( (font[0x0a].f[2]) ), BYTE_X4( (font[0x0a].f[2]) ), BYTE_X4( (font[0x0a].f[2]) ), BYTE_X4( (font[0x0a].f[2]) ), 
    //     BYTE_X4( (font[0x0a].f[3]) ), BYTE_X4( (font[0x0a].f[3]) ), BYTE_X4( (font[0x0a].f[3]) ), BYTE_X4( (font[0x0a].f[3]) ),
    //     BYTE_X4( (font[0x0a].f[4]) ), BYTE_X4( (font[0x0a].f[4]) ), BYTE_X4( (font[0x0a].f[4]) ), BYTE_X4( (font[0x0a].f[4]) )
    // } // 2a *
    // , {
    //     BYTE_X4( (font[0x0b].f[0]) ), BYTE_X4( (font[0x0b].f[0]) ), BYTE_X4( (font[0x0b].f[0]) ), BYTE_X4( (font[0x0b].f[0]) ), 
    //     BYTE_X4( (font[0x0b].f[1]) ), BYTE_X4( (font[0x0b].f[1]) ), BYTE_X4( (font[0x0b].f[1]) ), BYTE_X4( (font[0x0b].f[1]) ), 
    //     BYTE_X4( (font[0x0b].f[2]) ), BYTE_X4( (font[0x0b].f[2]) ), BYTE_X4( (font[0x0b].f[2]) ), BYTE_X4( (font[0x0b].f[2]) ), 
    //     BYTE_X4( (font[0x0b].f[3]) ), BYTE_X4( (font[0x0b].f[3]) ), BYTE_X4( (font[0x0b].f[3]) ), BYTE_X4( (font[0x0b].f[3]) ),
    //     BYTE_X4( (font[0x0b].f[4]) ), BYTE_X4( (font[0x0b].f[4]) ), BYTE_X4( (font[0x0b].f[4]) ), BYTE_X4( (font[0x0b].f[4]) )
    // } // 2b +
    // , {
    //     BYTE_X4( (font[0x0c].f[0]) ), BYTE_X4( (font[0x0c].f[0]) ), BYTE_X4( (font[0x0c].f[0]) ), BYTE_X4( (font[0x0c].f[0]) ), 
    //     BYTE_X4( (font[0x0c].f[1]) ), BYTE_X4( (font[0x0c].f[1]) ), BYTE_X4( (font[0x0c].f[1]) ), BYTE_X4( (font[0x0c].f[1]) ), 
    //     BYTE_X4( (font[0x0c].f[2]) ), BYTE_X4( (font[0x0c].f[2]) ), BYTE_X4( (font[0x0c].f[2]) ), BYTE_X4( (font[0x0c].f[2]) ), 
    //     BYTE_X4( (font[0x0c].f[3]) ), BYTE_X4( (font[0x0c].f[3]) ), BYTE_X4( (font[0x0c].f[3]) ), BYTE_X4( (font[0x0c].f[3]) ),
    //     BYTE_X4( (font[0x0c].f[4]) ), BYTE_X4( (font[0x0c].f[4]) ), BYTE_X4( (font[0x0c].f[4]) ), BYTE_X4( (font[0x0c].f[4]) )
    // } // 2c ,
    // , {
    //     BYTE_X4( (font[0x0d].f[0]) ), BYTE_X4( (font[0x0d].f[0]) ), BYTE_X4( (font[0x0d].f[0]) ), BYTE_X4( (font[0x0d].f[0]) ), 
    //     BYTE_X4( (font[0x0d].f[1]) ), BYTE_X4( (font[0x0d].f[1]) ), BYTE_X4( (font[0x0d].f[1]) ), BYTE_X4( (font[0x0d].f[1]) ), 
    //     BYTE_X4( (font[0x0d].f[2]) ), BYTE_X4( (font[0x0d].f[2]) ), BYTE_X4( (font[0x0d].f[2]) ), BYTE_X4( (font[0x0d].f[2]) ), 
    //     BYTE_X4( (font[0x0d].f[3]) ), BYTE_X4( (font[0x0d].f[3]) ), BYTE_X4( (font[0x0d].f[3]) ), BYTE_X4( (font[0x0d].f[3]) ),
    //     BYTE_X4( (font[0x0d].f[4]) ), BYTE_X4( (font[0x0d].f[4]) ), BYTE_X4( (font[0x0d].f[4]) ), BYTE_X4( (font[0x0d].f[4]) )
    // } // 2d -
    // , {
    //     BYTE_X4( (font[0x0e].f[0]) ), BYTE_X4( (font[0x0e].f[0]) ), BYTE_X4( (font[0x0e].f[0]) ), BYTE_X4( (font[0x0e].f[0]) ), 
    //     BYTE_X4( (font[0x0e].f[1]) ), BYTE_X4( (font[0x0e].f[1]) ), BYTE_X4( (font[0x0e].f[1]) ), BYTE_X4( (font[0x0e].f[1]) ), 
    //     BYTE_X4( (font[0x0e].f[2]) ), BYTE_X4( (font[0x0e].f[2]) ), BYTE_X4( (font[0x0e].f[2]) ), BYTE_X4( (font[0x0e].f[2]) ), 
    //     BYTE_X4( (font[0x0e].f[3]) ), BYTE_X4( (font[0x0e].f[3]) ), BYTE_X4( (font[0x0e].f[3]) ), BYTE_X4( (font[0x0e].f[3]) ),
    //     BYTE_X4( (font[0x0e].f[4]) ), BYTE_X4( (font[0x0e].f[4]) ), BYTE_X4( (font[0x0e].f[4]) ), BYTE_X4( (font[0x0e].f[4]) )
    // } // 2e .
    // , {
    //     BYTE_X4( (font[0x0f].f[0]) ), BYTE_X4( (font[0x0f].f[0]) ), BYTE_X4( (font[0x0f].f[0]) ), BYTE_X4( (font[0x0f].f[0]) ), 
    //     BYTE_X4( (font[0x0f].f[1]) ), BYTE_X4( (font[0x0f].f[1]) ), BYTE_X4( (font[0x0f].f[1]) ), BYTE_X4( (font[0x0f].f[1]) ), 
    //     BYTE_X4( (font[0x0f].f[2]) ), BYTE_X4( (font[0x0f].f[2]) ), BYTE_X4( (font[0x0f].f[2]) ), BYTE_X4( (font[0x0f].f[2]) ), 
    //     BYTE_X4( (font[0x0f].f[3]) ), BYTE_X4( (font[0x0f].f[3]) ), BYTE_X4( (font[0x0f].f[3]) ), BYTE_X4( (font[0x0f].f[3]) ),
    //     BYTE_X4( (font[0x0f].f[4]) ), BYTE_X4( (font[0x0f].f[4]) ), BYTE_X4( (font[0x0f].f[4]) ), BYTE_X4( (font[0x0f].f[4]) )
    // } // 2f /
    // , {
    //     BYTE_X4( (font[0x10].f[0]) ), BYTE_X4( (font[0x10].f[0]) ), BYTE_X4( (font[0x10].f[0]) ), BYTE_X4( (font[0x10].f[0]) ), 
    //     BYTE_X4( (font[0x10].f[1]) ), BYTE_X4( (font[0x10].f[1]) ), BYTE_X4( (font[0x10].f[1]) ), BYTE_X4( (font[0x10].f[1]) ), 
    //     BYTE_X4( (font[0x10].f[2]) ), BYTE_X4( (font[0x10].f[2]) ), BYTE_X4( (font[0x10].f[2]) ), BYTE_X4( (font[0x10].f[2]) ), 
    //     BYTE_X4( (font[0x10].f[3]) ), BYTE_X4( (font[0x10].f[3]) ), BYTE_X4( (font[0x10].f[3]) ), BYTE_X4( (font[0x10].f[3]) ),
    //     BYTE_X4( (font[0x10].f[4]) ), BYTE_X4( (font[0x10].f[4]) ), BYTE_X4( (font[0x10].f[4]) ), BYTE_X4( (font[0x10].f[4]) )
    // } // 30 0
    // , {
    //     BYTE_X4( (font[0x11].f[0]) ), BYTE_X4( (font[0x11].f[0]) ), BYTE_X4( (font[0x11].f[0]) ), BYTE_X4( (font[0x11].f[0]) ), 
    //     BYTE_X4( (font[0x11].f[1]) ), BYTE_X4( (font[0x11].f[1]) ), BYTE_X4( (font[0x11].f[1]) ), BYTE_X4( (font[0x11].f[1]) ), 
    //     BYTE_X4( (font[0x11].f[2]) ), BYTE_X4( (font[0x11].f[2]) ), BYTE_X4( (font[0x11].f[2]) ), BYTE_X4( (font[0x11].f[2]) ), 
    //     BYTE_X4( (font[0x11].f[3]) ), BYTE_X4( (font[0x11].f[3]) ), BYTE_X4( (font[0x11].f[3]) ), BYTE_X4( (font[0x11].f[3]) ),
    //     BYTE_X4( (font[0x11].f[4]) ), BYTE_X4( (font[0x11].f[4]) ), BYTE_X4( (font[0x11].f[4]) ), BYTE_X4( (font[0x11].f[4]) )
    // } // 31 1
    // , {
    //     BYTE_X4( (font[0x12].f[0]) ), BYTE_X4( (font[0x12].f[0]) ), BYTE_X4( (font[0x12].f[0]) ), BYTE_X4( (font[0x12].f[0]) ), 
    //     BYTE_X4( (font[0x12].f[1]) ), BYTE_X4( (font[0x12].f[1]) ), BYTE_X4( (font[0x12].f[1]) ), BYTE_X4( (font[0x12].f[1]) ), 
    //     BYTE_X4( (font[0x12].f[2]) ), BYTE_X4( (font[0x12].f[2]) ), BYTE_X4( (font[0x12].f[2]) ), BYTE_X4( (font[0x12].f[2]) ), 
    //     BYTE_X4( (font[0x12].f[3]) ), BYTE_X4( (font[0x12].f[3]) ), BYTE_X4( (font[0x12].f[3]) ), BYTE_X4( (font[0x12].f[3]) ),
    //     BYTE_X4( (font[0x12].f[4]) ), BYTE_X4( (font[0x12].f[4]) ), BYTE_X4( (font[0x12].f[4]) ), BYTE_X4( (font[0x12].f[4]) )
    // } // 32 2
    // , {
    //     BYTE_X4( (font[0x13].f[0]) ), BYTE_X4( (font[0x13].f[0]) ), BYTE_X4( (font[0x13].f[0]) ), BYTE_X4( (font[0x13].f[0]) ), 
    //     BYTE_X4( (font[0x13].f[1]) ), BYTE_X4( (font[0x13].f[1]) ), BYTE_X4( (font[0x13].f[1]) ), BYTE_X4( (font[0x13].f[1]) ), 
    //     BYTE_X4( (font[0x13].f[2]) ), BYTE_X4( (font[0x13].f[2]) ), BYTE_X4( (font[0x13].f[2]) ), BYTE_X4( (font[0x13].f[2]) ), 
    //     BYTE_X4( (font[0x13].f[3]) ), BYTE_X4( (font[0x13].f[3]) ), BYTE_X4( (font[0x13].f[3]) ), BYTE_X4( (font[0x13].f[3]) ),
    //     BYTE_X4( (font[0x13].f[4]) ), BYTE_X4( (font[0x13].f[4]) ), BYTE_X4( (font[0x13].f[4]) ), BYTE_X4( (font[0x13].f[4]) )
    // } // 33 3
    // , {
    //     BYTE_X4( (font[0x14].f[0]) ), BYTE_X4( (font[0x14].f[0]) ), BYTE_X4( (font[0x14].f[0]) ), BYTE_X4( (font[0x14].f[0]) ), 
    //     BYTE_X4( (font[0x14].f[1]) ), BYTE_X4( (font[0x14].f[1]) ), BYTE_X4( (font[0x14].f[1]) ), BYTE_X4( (font[0x14].f[1]) ), 
    //     BYTE_X4( (font[0x14].f[2]) ), BYTE_X4( (font[0x14].f[2]) ), BYTE_X4( (font[0x14].f[2]) ), BYTE_X4( (font[0x14].f[2]) ), 
    //     BYTE_X4( (font[0x14].f[3]) ), BYTE_X4( (font[0x14].f[3]) ), BYTE_X4( (font[0x14].f[3]) ), BYTE_X4( (font[0x14].f[3]) ),
    //     BYTE_X4( (font[0x14].f[4]) ), BYTE_X4( (font[0x14].f[4]) ), BYTE_X4( (font[0x14].f[4]) ), BYTE_X4( (font[0x14].f[4]) )
    // } // 34 4
    // , {
    //     BYTE_X4( (font[0x15].f[0]) ), BYTE_X4( (font[0x15].f[0]) ), BYTE_X4( (font[0x15].f[0]) ), BYTE_X4( (font[0x15].f[0]) ), 
    //     BYTE_X4( (font[0x15].f[1]) ), BYTE_X4( (font[0x15].f[1]) ), BYTE_X4( (font[0x15].f[1]) ), BYTE_X4( (font[0x15].f[1]) ), 
    //     BYTE_X4( (font[0x15].f[2]) ), BYTE_X4( (font[0x15].f[2]) ), BYTE_X4( (font[0x15].f[2]) ), BYTE_X4( (font[0x15].f[2]) ), 
    //     BYTE_X4( (font[0x15].f[3]) ), BYTE_X4( (font[0x15].f[3]) ), BYTE_X4( (font[0x15].f[3]) ), BYTE_X4( (font[0x15].f[3]) ),
    //     BYTE_X4( (font[0x15].f[4]) ), BYTE_X4( (font[0x15].f[4]) ), BYTE_X4( (font[0x15].f[4]) ), BYTE_X4( (font[0x15].f[4]) )
    // } // 35 5
    // , {
    //     BYTE_X4( (font[0x16].f[0]) ), BYTE_X4( (font[0x16].f[0]) ), BYTE_X4( (font[0x16].f[0]) ), BYTE_X4( (font[0x16].f[0]) ), 
    //     BYTE_X4( (font[0x16].f[1]) ), BYTE_X4( (font[0x16].f[1]) ), BYTE_X4( (font[0x16].f[1]) ), BYTE_X4( (font[0x16].f[1]) ), 
    //     BYTE_X4( (font[0x16].f[2]) ), BYTE_X4( (font[0x16].f[2]) ), BYTE_X4( (font[0x16].f[2]) ), BYTE_X4( (font[0x16].f[2]) ), 
    //     BYTE_X4( (font[0x16].f[3]) ), BYTE_X4( (font[0x16].f[3]) ), BYTE_X4( (font[0x16].f[3]) ), BYTE_X4( (font[0x16].f[3]) ),
    //     BYTE_X4( (font[0x16].f[4]) ), BYTE_X4( (font[0x16].f[4]) ), BYTE_X4( (font[0x16].f[4]) ), BYTE_X4( (font[0x16].f[4]) )
    // } // 36 6
    // , {
    //     BYTE_X4( (font[0x17].f[0]) ), BYTE_X4( (font[0x17].f[0]) ), BYTE_X4( (font[0x17].f[0]) ), BYTE_X4( (font[0x17].f[0]) ), 
    //     BYTE_X4( (font[0x17].f[1]) ), BYTE_X4( (font[0x17].f[1]) ), BYTE_X4( (font[0x17].f[1]) ), BYTE_X4( (font[0x17].f[1]) ), 
    //     BYTE_X4( (font[0x17].f[2]) ), BYTE_X4( (font[0x17].f[2]) ), BYTE_X4( (font[0x17].f[2]) ), BYTE_X4( (font[0x17].f[2]) ), 
    //     BYTE_X4( (font[0x17].f[3]) ), BYTE_X4( (font[0x17].f[3]) ), BYTE_X4( (font[0x17].f[3]) ), BYTE_X4( (font[0x17].f[3]) ),
    //     BYTE_X4( (font[0x17].f[4]) ), BYTE_X4( (font[0x17].f[4]) ), BYTE_X4( (font[0x17].f[4]) ), BYTE_X4( (font[0x17].f[4]) )
    // } // 37 7
    // , {
    //     BYTE_X4( (font[0x18].f[0]) ), BYTE_X4( (font[0x18].f[0]) ), BYTE_X4( (font[0x18].f[0]) ), BYTE_X4( (font[0x18].f[0]) ), 
    //     BYTE_X4( (font[0x18].f[1]) ), BYTE_X4( (font[0x18].f[1]) ), BYTE_X4( (font[0x18].f[1]) ), BYTE_X4( (font[0x18].f[1]) ), 
    //     BYTE_X4( (font[0x18].f[2]) ), BYTE_X4( (font[0x18].f[2]) ), BYTE_X4( (font[0x18].f[2]) ), BYTE_X4( (font[0x18].f[2]) ), 
    //     BYTE_X4( (font[0x18].f[3]) ), BYTE_X4( (font[0x18].f[3]) ), BYTE_X4( (font[0x18].f[3]) ), BYTE_X4( (font[0x18].f[3]) ),
    //     BYTE_X4( (font[0x18].f[4]) ), BYTE_X4( (font[0x18].f[4]) ), BYTE_X4( (font[0x18].f[4]) ), BYTE_X4( (font[0x18].f[4]) )
    // } // 38 8
    // , {
    //     BYTE_X4( (font[0x19].f[0]) ), BYTE_X4( (font[0x19].f[0]) ), BYTE_X4( (font[0x19].f[0]) ), BYTE_X4( (font[0x19].f[0]) ), 
    //     BYTE_X4( (font[0x19].f[1]) ), BYTE_X4( (font[0x19].f[1]) ), BYTE_X4( (font[0x19].f[1]) ), BYTE_X4( (font[0x19].f[1]) ), 
    //     BYTE_X4( (font[0x19].f[2]) ), BYTE_X4( (font[0x19].f[2]) ), BYTE_X4( (font[0x19].f[2]) ), BYTE_X4( (font[0x19].f[2]) ), 
    //     BYTE_X4( (font[0x19].f[3]) ), BYTE_X4( (font[0x19].f[3]) ), BYTE_X4( (font[0x19].f[3]) ), BYTE_X4( (font[0x19].f[3]) ),
    //     BYTE_X4( (font[0x19].f[4]) ), BYTE_X4( (font[0x19].f[4]) ), BYTE_X4( (font[0x19].f[4]) ), BYTE_X4( (font[0x19].f[4]) )
    // } // 39 9
    // , {
    //     BYTE_X4( (font[0x1a].f[0]) ), BYTE_X4( (font[0x1a].f[0]) ), BYTE_X4( (font[0x1a].f[0]) ), BYTE_X4( (font[0x1a].f[0]) ), 
    //     BYTE_X4( (font[0x1a].f[1]) ), BYTE_X4( (font[0x1a].f[1]) ), BYTE_X4( (font[0x1a].f[1]) ), BYTE_X4( (font[0x1a].f[1]) ), 
    //     BYTE_X4( (font[0x1a].f[2]) ), BYTE_X4( (font[0x1a].f[2]) ), BYTE_X4( (font[0x1a].f[2]) ), BYTE_X4( (font[0x1a].f[2]) ), 
    //     BYTE_X4( (font[0x1a].f[3]) ), BYTE_X4( (font[0x1a].f[3]) ), BYTE_X4( (font[0x1a].f[3]) ), BYTE_X4( (font[0x1a].f[3]) ),
    //     BYTE_X4( (font[0x1a].f[4]) ), BYTE_X4( (font[0x1a].f[4]) ), BYTE_X4( (font[0x1a].f[4]) ), BYTE_X4( (font[0x1a].f[4]) )
    // } // 3a :
    // , {
    //     BYTE_X4( (font[0x1b].f[0]) ), BYTE_X4( (font[0x1b].f[0]) ), BYTE_X4( (font[0x1b].f[0]) ), BYTE_X4( (font[0x1b].f[0]) ), 
    //     BYTE_X4( (font[0x1b].f[1]) ), BYTE_X4( (font[0x1b].f[1]) ), BYTE_X4( (font[0x1b].f[1]) ), BYTE_X4( (font[0x1b].f[1]) ), 
    //     BYTE_X4( (font[0x1b].f[2]) ), BYTE_X4( (font[0x1b].f[2]) ), BYTE_X4( (font[0x1b].f[2]) ), BYTE_X4( (font[0x1b].f[2]) ), 
    //     BYTE_X4( (font[0x1b].f[3]) ), BYTE_X4( (font[0x1b].f[3]) ), BYTE_X4( (font[0x1b].f[3]) ), BYTE_X4( (font[0x1b].f[3]) ),
    //     BYTE_X4( (font[0x1b].f[4]) ), BYTE_X4( (font[0x1b].f[4]) ), BYTE_X4( (font[0x1b].f[4]) ), BYTE_X4( (font[0x1b].f[4]) )
    // } // 3b ;
    // , {
    //     BYTE_X4( (font[0x1c].f[0]) ), BYTE_X4( (font[0x1c].f[0]) ), BYTE_X4( (font[0x1c].f[0]) ), BYTE_X4( (font[0x1c].f[0]) ), 
    //     BYTE_X4( (font[0x1c].f[1]) ), BYTE_X4( (font[0x1c].f[1]) ), BYTE_X4( (font[0x1c].f[1]) ), BYTE_X4( (font[0x1c].f[1]) ), 
    //     BYTE_X4( (font[0x1c].f[2]) ), BYTE_X4( (font[0x1c].f[2]) ), BYTE_X4( (font[0x1c].f[2]) ), BYTE_X4( (font[0x1c].f[2]) ), 
    //     BYTE_X4( (font[0x1c].f[3]) ), BYTE_X4( (font[0x1c].f[3]) ), BYTE_X4( (font[0x1c].f[3]) ), BYTE_X4( (font[0x1c].f[3]) ),
    //     BYTE_X4( (font[0x1c].f[4]) ), BYTE_X4( (font[0x1c].f[4]) ), BYTE_X4( (font[0x1c].f[4]) ), BYTE_X4( (font[0x1c].f[4]) )
    // } // 3c <
    // , {
    //     BYTE_X4( (font[0x1d].f[0]) ), BYTE_X4( (font[0x1d].f[0]) ), BYTE_X4( (font[0x1d].f[0]) ), BYTE_X4( (font[0x1d].f[0]) ), 
    //     BYTE_X4( (font[0x1d].f[1]) ), BYTE_X4( (font[0x1d].f[1]) ), BYTE_X4( (font[0x1d].f[1]) ), BYTE_X4( (font[0x1d].f[1]) ), 
    //     BYTE_X4( (font[0x1d].f[2]) ), BYTE_X4( (font[0x1d].f[2]) ), BYTE_X4( (font[0x1d].f[2]) ), BYTE_X4( (font[0x1d].f[2]) ), 
    //     BYTE_X4( (font[0x1d].f[3]) ), BYTE_X4( (font[0x1d].f[3]) ), BYTE_X4( (font[0x1d].f[3]) ), BYTE_X4( (font[0x1d].f[3]) ),
    //     BYTE_X4( (font[0x1d].f[4]) ), BYTE_X4( (font[0x1d].f[4]) ), BYTE_X4( (font[0x1d].f[4]) ), BYTE_X4( (font[0x1d].f[4]) )
    // } // 3d =
    // , {
    //     BYTE_X4( (font[0x1e].f[0]) ), BYTE_X4( (font[0x1e].f[0]) ), BYTE_X4( (font[0x1e].f[0]) ), BYTE_X4( (font[0x1e].f[0]) ), 
    //     BYTE_X4( (font[0x1e].f[1]) ), BYTE_X4( (font[0x1e].f[1]) ), BYTE_X4( (font[0x1e].f[1]) ), BYTE_X4( (font[0x1e].f[1]) ), 
    //     BYTE_X4( (font[0x1e].f[2]) ), BYTE_X4( (font[0x1e].f[2]) ), BYTE_X4( (font[0x1e].f[2]) ), BYTE_X4( (font[0x1e].f[2]) ), 
    //     BYTE_X4( (font[0x1e].f[3]) ), BYTE_X4( (font[0x1e].f[3]) ), BYTE_X4( (font[0x1e].f[3]) ), BYTE_X4( (font[0x1e].f[3]) ),
    //     BYTE_X4( (font[0x1e].f[4]) ), BYTE_X4( (font[0x1e].f[4]) ), BYTE_X4( (font[0x1e].f[4]) ), BYTE_X4( (font[0x1e].f[4]) )
    // } // 3e >
    // , {
    //     BYTE_X4( (font[0x1f].f[0]) ), BYTE_X4( (font[0x1f].f[0]) ), BYTE_X4( (font[0x1f].f[0]) ), BYTE_X4( (font[0x1f].f[0]) ), 
    //     BYTE_X4( (font[0x1f].f[1]) ), BYTE_X4( (font[0x1f].f[1]) ), BYTE_X4( (font[0x1f].f[1]) ), BYTE_X4( (font[0x1f].f[1]) ), 
    //     BYTE_X4( (font[0x1f].f[2]) ), BYTE_X4( (font[0x1f].f[2]) ), BYTE_X4( (font[0x1f].f[2]) ), BYTE_X4( (font[0x1f].f[2]) ), 
    //     BYTE_X4( (font[0x1f].f[3]) ), BYTE_X4( (font[0x1f].f[3]) ), BYTE_X4( (font[0x1f].f[3]) ), BYTE_X4( (font[0x1f].f[3]) ),
    //     BYTE_X4( (font[0x1f].f[4]) ), BYTE_X4( (font[0x1f].f[4]) ), BYTE_X4( (font[0x1f].f[4]) ), BYTE_X4( (font[0x1f].f[4]) )
    // } // 3f ?
    // , {
    //     BYTE_X4( (font[0x20].f[0]) ), BYTE_X4( (font[0x20].f[0]) ), BYTE_X4( (font[0x20].f[0]) ), BYTE_X4( (font[0x20].f[0]) ), 
    //     BYTE_X4( (font[0x20].f[1]) ), BYTE_X4( (font[0x20].f[1]) ), BYTE_X4( (font[0x20].f[1]) ), BYTE_X4( (font[0x20].f[1]) ), 
    //     BYTE_X4( (font[0x20].f[2]) ), BYTE_X4( (font[0x20].f[2]) ), BYTE_X4( (font[0x20].f[2]) ), BYTE_X4( (font[0x20].f[2]) ), 
    //     BYTE_X4( (font[0x20].f[3]) ), BYTE_X4( (font[0x20].f[3]) ), BYTE_X4( (font[0x20].f[3]) ), BYTE_X4( (font[0x20].f[3]) ),
    //     BYTE_X4( (font[0x20].f[4]) ), BYTE_X4( (font[0x20].f[4]) ), BYTE_X4( (font[0x20].f[4]) ), BYTE_X4( (font[0x20].f[4]) )
    // } // 40 @
    // , {
    //     BYTE_X4( (font[0x21].f[0]) ), BYTE_X4( (font[0x21].f[0]) ), BYTE_X4( (font[0x21].f[0]) ), BYTE_X4( (font[0x21].f[0]) ), 
    //     BYTE_X4( (font[0x21].f[1]) ), BYTE_X4( (font[0x21].f[1]) ), BYTE_X4( (font[0x21].f[1]) ), BYTE_X4( (font[0x21].f[1]) ), 
    //     BYTE_X4( (font[0x21].f[2]) ), BYTE_X4( (font[0x21].f[2]) ), BYTE_X4( (font[0x21].f[2]) ), BYTE_X4( (font[0x21].f[2]) ), 
    //     BYTE_X4( (font[0x21].f[3]) ), BYTE_X4( (font[0x21].f[3]) ), BYTE_X4( (font[0x21].f[3]) ), BYTE_X4( (font[0x21].f[3]) ),
    //     BYTE_X4( (font[0x21].f[4]) ), BYTE_X4( (font[0x21].f[4]) ), BYTE_X4( (font[0x21].f[4]) ), BYTE_X4( (font[0x21].f[4]) )
    // } // 41 A
    // , {
    //     BYTE_X4( (font[0x22].f[0]) ), BYTE_X4( (font[0x22].f[0]) ), BYTE_X4( (font[0x22].f[0]) ), BYTE_X4( (font[0x22].f[0]) ), 
    //     BYTE_X4( (font[0x22].f[1]) ), BYTE_X4( (font[0x22].f[1]) ), BYTE_X4( (font[0x22].f[1]) ), BYTE_X4( (font[0x22].f[1]) ), 
    //     BYTE_X4( (font[0x22].f[2]) ), BYTE_X4( (font[0x22].f[2]) ), BYTE_X4( (font[0x22].f[2]) ), BYTE_X4( (font[0x22].f[2]) ), 
    //     BYTE_X4( (font[0x22].f[3]) ), BYTE_X4( (font[0x22].f[3]) ), BYTE_X4( (font[0x22].f[3]) ), BYTE_X4( (font[0x22].f[3]) ),
    //     BYTE_X4( (font[0x22].f[4]) ), BYTE_X4( (font[0x22].f[4]) ), BYTE_X4( (font[0x22].f[4]) ), BYTE_X4( (font[0x22].f[4]) )
    // } // 42 B
    // , {
    //     BYTE_X4( (font[0x23].f[0]) ), BYTE_X4( (font[0x23].f[0]) ), BYTE_X4( (font[0x23].f[0]) ), BYTE_X4( (font[0x23].f[0]) ), 
    //     BYTE_X4( (font[0x23].f[1]) ), BYTE_X4( (font[0x23].f[1]) ), BYTE_X4( (font[0x23].f[1]) ), BYTE_X4( (font[0x23].f[1]) ), 
    //     BYTE_X4( (font[0x23].f[2]) ), BYTE_X4( (font[0x23].f[2]) ), BYTE_X4( (font[0x23].f[2]) ), BYTE_X4( (font[0x23].f[2]) ), 
    //     BYTE_X4( (font[0x23].f[3]) ), BYTE_X4( (font[0x23].f[3]) ), BYTE_X4( (font[0x23].f[3]) ), BYTE_X4( (font[0x23].f[3]) ),
    //     BYTE_X4( (font[0x23].f[4]) ), BYTE_X4( (font[0x23].f[4]) ), BYTE_X4( (font[0x23].f[4]) ), BYTE_X4( (font[0x23].f[4]) )
    // } // 43 C
    // , {
    //     BYTE_X4( (font[0x24].f[0]) ), BYTE_X4( (font[0x24].f[0]) ), BYTE_X4( (font[0x24].f[0]) ), BYTE_X4( (font[0x24].f[0]) ), 
    //     BYTE_X4( (font[0x24].f[1]) ), BYTE_X4( (font[0x24].f[1]) ), BYTE_X4( (font[0x24].f[1]) ), BYTE_X4( (font[0x24].f[1]) ), 
    //     BYTE_X4( (font[0x24].f[2]) ), BYTE_X4( (font[0x24].f[2]) ), BYTE_X4( (font[0x24].f[2]) ), BYTE_X4( (font[0x24].f[2]) ), 
    //     BYTE_X4( (font[0x24].f[3]) ), BYTE_X4( (font[0x24].f[3]) ), BYTE_X4( (font[0x24].f[3]) ), BYTE_X4( (font[0x24].f[3]) ),
    //     BYTE_X4( (font[0x24].f[4]) ), BYTE_X4( (font[0x24].f[4]) ), BYTE_X4( (font[0x24].f[4]) ), BYTE_X4( (font[0x24].f[4]) )
    // } // 44 D
    // , {
    //     BYTE_X4( (font[0x25].f[0]) ), BYTE_X4( (font[0x25].f[0]) ), BYTE_X4( (font[0x25].f[0]) ), BYTE_X4( (font[0x25].f[0]) ), 
    //     BYTE_X4( (font[0x25].f[1]) ), BYTE_X4( (font[0x25].f[1]) ), BYTE_X4( (font[0x25].f[1]) ), BYTE_X4( (font[0x25].f[1]) ), 
    //     BYTE_X4( (font[0x25].f[2]) ), BYTE_X4( (font[0x25].f[2]) ), BYTE_X4( (font[0x25].f[2]) ), BYTE_X4( (font[0x25].f[2]) ), 
    //     BYTE_X4( (font[0x25].f[3]) ), BYTE_X4( (font[0x25].f[3]) ), BYTE_X4( (font[0x25].f[3]) ), BYTE_X4( (font[0x25].f[3]) ),
    //     BYTE_X4( (font[0x25].f[4]) ), BYTE_X4( (font[0x25].f[4]) ), BYTE_X4( (font[0x25].f[4]) ), BYTE_X4( (font[0x25].f[4]) )
    // } // 45 E
    // , {
    //     BYTE_X4( (font[0x26].f[0]) ), BYTE_X4( (font[0x26].f[0]) ), BYTE_X4( (font[0x26].f[0]) ), BYTE_X4( (font[0x26].f[0]) ), 
    //     BYTE_X4( (font[0x26].f[1]) ), BYTE_X4( (font[0x26].f[1]) ), BYTE_X4( (font[0x26].f[1]) ), BYTE_X4( (font[0x26].f[1]) ), 
    //     BYTE_X4( (font[0x26].f[2]) ), BYTE_X4( (font[0x26].f[2]) ), BYTE_X4( (font[0x26].f[2]) ), BYTE_X4( (font[0x26].f[2]) ), 
    //     BYTE_X4( (font[0x26].f[3]) ), BYTE_X4( (font[0x26].f[3]) ), BYTE_X4( (font[0x26].f[3]) ), BYTE_X4( (font[0x26].f[3]) ),
    //     BYTE_X4( (font[0x26].f[4]) ), BYTE_X4( (font[0x26].f[4]) ), BYTE_X4( (font[0x26].f[4]) ), BYTE_X4( (font[0x26].f[4]) )
    // } // 46 F
    // , {
    //     BYTE_X4( (font[0x27].f[0]) ), BYTE_X4( (font[0x27].f[0]) ), BYTE_X4( (font[0x27].f[0]) ), BYTE_X4( (font[0x27].f[0]) ), 
    //     BYTE_X4( (font[0x27].f[1]) ), BYTE_X4( (font[0x27].f[1]) ), BYTE_X4( (font[0x27].f[1]) ), BYTE_X4( (font[0x27].f[1]) ), 
    //     BYTE_X4( (font[0x27].f[2]) ), BYTE_X4( (font[0x27].f[2]) ), BYTE_X4( (font[0x27].f[2]) ), BYTE_X4( (font[0x27].f[2]) ), 
    //     BYTE_X4( (font[0x27].f[3]) ), BYTE_X4( (font[0x27].f[3]) ), BYTE_X4( (font[0x27].f[3]) ), BYTE_X4( (font[0x27].f[3]) ),
    //     BYTE_X4( (font[0x27].f[4]) ), BYTE_X4( (font[0x27].f[4]) ), BYTE_X4( (font[0x27].f[4]) ), BYTE_X4( (font[0x27].f[4]) )
    // } // 47 G
    // , {
    //     BYTE_X4( (font[0x28].f[0]) ), BYTE_X4( (font[0x28].f[0]) ), BYTE_X4( (font[0x28].f[0]) ), BYTE_X4( (font[0x28].f[0]) ), 
    //     BYTE_X4( (font[0x28].f[1]) ), BYTE_X4( (font[0x28].f[1]) ), BYTE_X4( (font[0x28].f[1]) ), BYTE_X4( (font[0x28].f[1]) ), 
    //     BYTE_X4( (font[0x28].f[2]) ), BYTE_X4( (font[0x28].f[2]) ), BYTE_X4( (font[0x28].f[2]) ), BYTE_X4( (font[0x28].f[2]) ), 
    //     BYTE_X4( (font[0x28].f[3]) ), BYTE_X4( (font[0x28].f[3]) ), BYTE_X4( (font[0x28].f[3]) ), BYTE_X4( (font[0x28].f[3]) ),
    //     BYTE_X4( (font[0x28].f[4]) ), BYTE_X4( (font[0x28].f[4]) ), BYTE_X4( (font[0x28].f[4]) ), BYTE_X4( (font[0x28].f[4]) )
    // } // 48 H
    // , {
    //     BYTE_X4( (font[0x29].f[0]) ), BYTE_X4( (font[0x29].f[0]) ), BYTE_X4( (font[0x29].f[0]) ), BYTE_X4( (font[0x29].f[0]) ), 
    //     BYTE_X4( (font[0x29].f[1]) ), BYTE_X4( (font[0x29].f[1]) ), BYTE_X4( (font[0x29].f[1]) ), BYTE_X4( (font[0x29].f[1]) ), 
    //     BYTE_X4( (font[0x29].f[2]) ), BYTE_X4( (font[0x29].f[2]) ), BYTE_X4( (font[0x29].f[2]) ), BYTE_X4( (font[0x29].f[2]) ), 
    //     BYTE_X4( (font[0x29].f[3]) ), BYTE_X4( (font[0x29].f[3]) ), BYTE_X4( (font[0x29].f[3]) ), BYTE_X4( (font[0x29].f[3]) ),
    //     BYTE_X4( (font[0x29].f[4]) ), BYTE_X4( (font[0x29].f[4]) ), BYTE_X4( (font[0x29].f[4]) ), BYTE_X4( (font[0x29].f[4]) )
    // } // 49 I
    // , {
    //     BYTE_X4( (font[0x2a].f[0]) ), BYTE_X4( (font[0x2a].f[0]) ), BYTE_X4( (font[0x2a].f[0]) ), BYTE_X4( (font[0x2a].f[0]) ), 
    //     BYTE_X4( (font[0x2a].f[1]) ), BYTE_X4( (font[0x2a].f[1]) ), BYTE_X4( (font[0x2a].f[1]) ), BYTE_X4( (font[0x2a].f[1]) ), 
    //     BYTE_X4( (font[0x2a].f[2]) ), BYTE_X4( (font[0x2a].f[2]) ), BYTE_X4( (font[0x2a].f[2]) ), BYTE_X4( (font[0x2a].f[2]) ), 
    //     BYTE_X4( (font[0x2a].f[3]) ), BYTE_X4( (font[0x2a].f[3]) ), BYTE_X4( (font[0x2a].f[3]) ), BYTE_X4( (font[0x2a].f[3]) ),
    //     BYTE_X4( (font[0x2a].f[4]) ), BYTE_X4( (font[0x2a].f[4]) ), BYTE_X4( (font[0x2a].f[4]) ), BYTE_X4( (font[0x2a].f[4]) )
    // } // 4a J
    // , {
    //     BYTE_X4( (font[0x2b].f[0]) ), BYTE_X4( (font[0x2b].f[0]) ), BYTE_X4( (font[0x2b].f[0]) ), BYTE_X4( (font[0x2b].f[0]) ), 
    //     BYTE_X4( (font[0x2b].f[1]) ), BYTE_X4( (font[0x2b].f[1]) ), BYTE_X4( (font[0x2b].f[1]) ), BYTE_X4( (font[0x2b].f[1]) ), 
    //     BYTE_X4( (font[0x2b].f[2]) ), BYTE_X4( (font[0x2b].f[2]) ), BYTE_X4( (font[0x2b].f[2]) ), BYTE_X4( (font[0x2b].f[2]) ), 
    //     BYTE_X4( (font[0x2b].f[3]) ), BYTE_X4( (font[0x2b].f[3]) ), BYTE_X4( (font[0x2b].f[3]) ), BYTE_X4( (font[0x2b].f[3]) ),
    //     BYTE_X4( (font[0x2b].f[4]) ), BYTE_X4( (font[0x2b].f[4]) ), BYTE_X4( (font[0x2b].f[4]) ), BYTE_X4( (font[0x2b].f[4]) )
    // } // 4b K
    // , {
    //     BYTE_X4( (font[0x2c].f[0]) ), BYTE_X4( (font[0x2c].f[0]) ), BYTE_X4( (font[0x2c].f[0]) ), BYTE_X4( (font[0x2c].f[0]) ), 
    //     BYTE_X4( (font[0x2c].f[1]) ), BYTE_X4( (font[0x2c].f[1]) ), BYTE_X4( (font[0x2c].f[1]) ), BYTE_X4( (font[0x2c].f[1]) ), 
    //     BYTE_X4( (font[0x2c].f[2]) ), BYTE_X4( (font[0x2c].f[2]) ), BYTE_X4( (font[0x2c].f[2]) ), BYTE_X4( (font[0x2c].f[2]) ), 
    //     BYTE_X4( (font[0x2c].f[3]) ), BYTE_X4( (font[0x2c].f[3]) ), BYTE_X4( (font[0x2c].f[3]) ), BYTE_X4( (font[0x2c].f[3]) ),
    //     BYTE_X4( (font[0x2c].f[4]) ), BYTE_X4( (font[0x2c].f[4]) ), BYTE_X4( (font[0x2c].f[4]) ), BYTE_X4( (font[0x2c].f[4]) )
    // } // 4c L
    // , {
    //     BYTE_X4( (font[0x2d].f[0]) ), BYTE_X4( (font[0x2d].f[0]) ), BYTE_X4( (font[0x2d].f[0]) ), BYTE_X4( (font[0x2d].f[0]) ), 
    //     BYTE_X4( (font[0x2d].f[1]) ), BYTE_X4( (font[0x2d].f[1]) ), BYTE_X4( (font[0x2d].f[1]) ), BYTE_X4( (font[0x2d].f[1]) ), 
    //     BYTE_X4( (font[0x2d].f[2]) ), BYTE_X4( (font[0x2d].f[2]) ), BYTE_X4( (font[0x2d].f[2]) ), BYTE_X4( (font[0x2d].f[2]) ), 
    //     BYTE_X4( (font[0x2d].f[3]) ), BYTE_X4( (font[0x2d].f[3]) ), BYTE_X4( (font[0x2d].f[3]) ), BYTE_X4( (font[0x2d].f[3]) ),
    //     BYTE_X4( (font[0x2d].f[4]) ), BYTE_X4( (font[0x2d].f[4]) ), BYTE_X4( (font[0x2d].f[4]) ), BYTE_X4( (font[0x2d].f[4]) )
    // } // 4d M
    // , {
    //     BYTE_X4( (font[0x2e].f[0]) ), BYTE_X4( (font[0x2e].f[0]) ), BYTE_X4( (font[0x2e].f[0]) ), BYTE_X4( (font[0x2e].f[0]) ), 
    //     BYTE_X4( (font[0x2e].f[1]) ), BYTE_X4( (font[0x2e].f[1]) ), BYTE_X4( (font[0x2e].f[1]) ), BYTE_X4( (font[0x2e].f[1]) ), 
    //     BYTE_X4( (font[0x2e].f[2]) ), BYTE_X4( (font[0x2e].f[2]) ), BYTE_X4( (font[0x2e].f[2]) ), BYTE_X4( (font[0x2e].f[2]) ), 
    //     BYTE_X4( (font[0x2e].f[3]) ), BYTE_X4( (font[0x2e].f[3]) ), BYTE_X4( (font[0x2e].f[3]) ), BYTE_X4( (font[0x2e].f[3]) ),
    //     BYTE_X4( (font[0x2e].f[4]) ), BYTE_X4( (font[0x2e].f[4]) ), BYTE_X4( (font[0x2e].f[4]) ), BYTE_X4( (font[0x2e].f[4]) )
    // } // 4e N
    // , {
    //     BYTE_X4( (font[0x2f].f[0]) ), BYTE_X4( (font[0x2f].f[0]) ), BYTE_X4( (font[0x2f].f[0]) ), BYTE_X4( (font[0x2f].f[0]) ), 
    //     BYTE_X4( (font[0x2f].f[1]) ), BYTE_X4( (font[0x2f].f[1]) ), BYTE_X4( (font[0x2f].f[1]) ), BYTE_X4( (font[0x2f].f[1]) ), 
    //     BYTE_X4( (font[0x2f].f[2]) ), BYTE_X4( (font[0x2f].f[2]) ), BYTE_X4( (font[0x2f].f[2]) ), BYTE_X4( (font[0x2f].f[2]) ), 
    //     BYTE_X4( (font[0x2f].f[3]) ), BYTE_X4( (font[0x2f].f[3]) ), BYTE_X4( (font[0x2f].f[3]) ), BYTE_X4( (font[0x2f].f[3]) ),
    //     BYTE_X4( (font[0x2f].f[4]) ), BYTE_X4( (font[0x2f].f[4]) ), BYTE_X4( (font[0x2f].f[4]) ), BYTE_X4( (font[0x2f].f[4]) )
    // } // 4f O
    // , {
    //     BYTE_X4( (font[0x30].f[0]) ), BYTE_X4( (font[0x30].f[0]) ), BYTE_X4( (font[0x30].f[0]) ), BYTE_X4( (font[0x30].f[0]) ), 
    //     BYTE_X4( (font[0x30].f[1]) ), BYTE_X4( (font[0x30].f[1]) ), BYTE_X4( (font[0x30].f[1]) ), BYTE_X4( (font[0x30].f[1]) ), 
    //     BYTE_X4( (font[0x30].f[2]) ), BYTE_X4( (font[0x30].f[2]) ), BYTE_X4( (font[0x30].f[2]) ), BYTE_X4( (font[0x30].f[2]) ), 
    //     BYTE_X4( (font[0x30].f[3]) ), BYTE_X4( (font[0x30].f[3]) ), BYTE_X4( (font[0x30].f[3]) ), BYTE_X4( (font[0x30].f[3]) ),
    //     BYTE_X4( (font[0x30].f[4]) ), BYTE_X4( (font[0x30].f[4]) ), BYTE_X4( (font[0x30].f[4]) ), BYTE_X4( (font[0x30].f[4]) )
    // } // 50 P
    // , {
    //     BYTE_X4( (font[0x31].f[0]) ), BYTE_X4( (font[0x31].f[0]) ), BYTE_X4( (font[0x31].f[0]) ), BYTE_X4( (font[0x31].f[0]) ), 
    //     BYTE_X4( (font[0x31].f[1]) ), BYTE_X4( (font[0x31].f[1]) ), BYTE_X4( (font[0x31].f[1]) ), BYTE_X4( (font[0x31].f[1]) ), 
    //     BYTE_X4( (font[0x31].f[2]) ), BYTE_X4( (font[0x31].f[2]) ), BYTE_X4( (font[0x31].f[2]) ), BYTE_X4( (font[0x31].f[2]) ), 
    //     BYTE_X4( (font[0x31].f[3]) ), BYTE_X4( (font[0x31].f[3]) ), BYTE_X4( (font[0x31].f[3]) ), BYTE_X4( (font[0x31].f[3]) ),
    //     BYTE_X4( (font[0x31].f[4]) ), BYTE_X4( (font[0x31].f[4]) ), BYTE_X4( (font[0x31].f[4]) ), BYTE_X4( (font[0x31].f[4]) )
    // } // 51 Q
    // , {
    //     BYTE_X4( (font[0x32].f[0]) ), BYTE_X4( (font[0x32].f[0]) ), BYTE_X4( (font[0x32].f[0]) ), BYTE_X4( (font[0x32].f[0]) ), 
    //     BYTE_X4( (font[0x32].f[1]) ), BYTE_X4( (font[0x32].f[1]) ), BYTE_X4( (font[0x32].f[1]) ), BYTE_X4( (font[0x32].f[1]) ), 
    //     BYTE_X4( (font[0x32].f[2]) ), BYTE_X4( (font[0x32].f[2]) ), BYTE_X4( (font[0x32].f[2]) ), BYTE_X4( (font[0x32].f[2]) ), 
    //     BYTE_X4( (font[0x32].f[3]) ), BYTE_X4( (font[0x32].f[3]) ), BYTE_X4( (font[0x32].f[3]) ), BYTE_X4( (font[0x32].f[3]) ),
    //     BYTE_X4( (font[0x32].f[4]) ), BYTE_X4( (font[0x32].f[4]) ), BYTE_X4( (font[0x32].f[4]) ), BYTE_X4( (font[0x32].f[4]) )
    // } // 52 R
    // , {
    //     BYTE_X4( (font[0x33].f[0]) ), BYTE_X4( (font[0x33].f[0]) ), BYTE_X4( (font[0x33].f[0]) ), BYTE_X4( (font[0x33].f[0]) ), 
    //     BYTE_X4( (font[0x33].f[1]) ), BYTE_X4( (font[0x33].f[1]) ), BYTE_X4( (font[0x33].f[1]) ), BYTE_X4( (font[0x33].f[1]) ), 
    //     BYTE_X4( (font[0x33].f[2]) ), BYTE_X4( (font[0x33].f[2]) ), BYTE_X4( (font[0x33].f[2]) ), BYTE_X4( (font[0x33].f[2]) ), 
    //     BYTE_X4( (font[0x33].f[3]) ), BYTE_X4( (font[0x33].f[3]) ), BYTE_X4( (font[0x33].f[3]) ), BYTE_X4( (font[0x33].f[3]) ),
    //     BYTE_X4( (font[0x33].f[4]) ), BYTE_X4( (font[0x33].f[4]) ), BYTE_X4( (font[0x33].f[4]) ), BYTE_X4( (font[0x33].f[4]) )
    // } // 53 S
    // , {
    //     BYTE_X4( (font[0x34].f[0]) ), BYTE_X4( (font[0x34].f[0]) ), BYTE_X4( (font[0x34].f[0]) ), BYTE_X4( (font[0x34].f[0]) ), 
    //     BYTE_X4( (font[0x34].f[1]) ), BYTE_X4( (font[0x34].f[1]) ), BYTE_X4( (font[0x34].f[1]) ), BYTE_X4( (font[0x34].f[1]) ), 
    //     BYTE_X4( (font[0x34].f[2]) ), BYTE_X4( (font[0x34].f[2]) ), BYTE_X4( (font[0x34].f[2]) ), BYTE_X4( (font[0x34].f[2]) ), 
    //     BYTE_X4( (font[0x34].f[3]) ), BYTE_X4( (font[0x34].f[3]) ), BYTE_X4( (font[0x34].f[3]) ), BYTE_X4( (font[0x34].f[3]) ),
    //     BYTE_X4( (font[0x34].f[4]) ), BYTE_X4( (font[0x34].f[4]) ), BYTE_X4( (font[0x34].f[4]) ), BYTE_X4( (font[0x34].f[4]) )
    // } // 54 T
    // , {
    //     BYTE_X4( (font[0x35].f[0]) ), BYTE_X4( (font[0x35].f[0]) ), BYTE_X4( (font[0x35].f[0]) ), BYTE_X4( (font[0x35].f[0]) ), 
    //     BYTE_X4( (font[0x35].f[1]) ), BYTE_X4( (font[0x35].f[1]) ), BYTE_X4( (font[0x35].f[1]) ), BYTE_X4( (font[0x35].f[1]) ), 
    //     BYTE_X4( (font[0x35].f[2]) ), BYTE_X4( (font[0x35].f[2]) ), BYTE_X4( (font[0x35].f[2]) ), BYTE_X4( (font[0x35].f[2]) ), 
    //     BYTE_X4( (font[0x35].f[3]) ), BYTE_X4( (font[0x35].f[3]) ), BYTE_X4( (font[0x35].f[3]) ), BYTE_X4( (font[0x35].f[3]) ),
    //     BYTE_X4( (font[0x35].f[4]) ), BYTE_X4( (font[0x35].f[4]) ), BYTE_X4( (font[0x35].f[4]) ), BYTE_X4( (font[0x35].f[4]) )
    // } // 55 U
    // , {
    //     BYTE_X4( (font[0x36].f[0]) ), BYTE_X4( (font[0x36].f[0]) ), BYTE_X4( (font[0x36].f[0]) ), BYTE_X4( (font[0x36].f[0]) ), 
    //     BYTE_X4( (font[0x36].f[1]) ), BYTE_X4( (font[0x36].f[1]) ), BYTE_X4( (font[0x36].f[1]) ), BYTE_X4( (font[0x36].f[1]) ), 
    //     BYTE_X4( (font[0x36].f[2]) ), BYTE_X4( (font[0x36].f[2]) ), BYTE_X4( (font[0x36].f[2]) ), BYTE_X4( (font[0x36].f[2]) ), 
    //     BYTE_X4( (font[0x36].f[3]) ), BYTE_X4( (font[0x36].f[3]) ), BYTE_X4( (font[0x36].f[3]) ), BYTE_X4( (font[0x36].f[3]) ),
    //     BYTE_X4( (font[0x36].f[4]) ), BYTE_X4( (font[0x36].f[4]) ), BYTE_X4( (font[0x36].f[4]) ), BYTE_X4( (font[0x36].f[4]) )
    // } // 56 V
    // , {
    //     BYTE_X4( (font[0x37].f[0]) ), BYTE_X4( (font[0x37].f[0]) ), BYTE_X4( (font[0x37].f[0]) ), BYTE_X4( (font[0x37].f[0]) ), 
    //     BYTE_X4( (font[0x37].f[1]) ), BYTE_X4( (font[0x37].f[1]) ), BYTE_X4( (font[0x37].f[1]) ), BYTE_X4( (font[0x37].f[1]) ), 
    //     BYTE_X4( (font[0x37].f[2]) ), BYTE_X4( (font[0x37].f[2]) ), BYTE_X4( (font[0x37].f[2]) ), BYTE_X4( (font[0x37].f[2]) ), 
    //     BYTE_X4( (font[0x37].f[3]) ), BYTE_X4( (font[0x37].f[3]) ), BYTE_X4( (font[0x37].f[3]) ), BYTE_X4( (font[0x37].f[3]) ),
    //     BYTE_X4( (font[0x37].f[4]) ), BYTE_X4( (font[0x37].f[4]) ), BYTE_X4( (font[0x37].f[4]) ), BYTE_X4( (font[0x37].f[4]) )
    // } // 57 W
    // , {
    //     BYTE_X4( (font[0x38].f[0]) ), BYTE_X4( (font[0x38].f[0]) ), BYTE_X4( (font[0x38].f[0]) ), BYTE_X4( (font[0x38].f[0]) ), 
    //     BYTE_X4( (font[0x38].f[1]) ), BYTE_X4( (font[0x38].f[1]) ), BYTE_X4( (font[0x38].f[1]) ), BYTE_X4( (font[0x38].f[1]) ), 
    //     BYTE_X4( (font[0x38].f[2]) ), BYTE_X4( (font[0x38].f[2]) ), BYTE_X4( (font[0x38].f[2]) ), BYTE_X4( (font[0x38].f[2]) ), 
    //     BYTE_X4( (font[0x38].f[3]) ), BYTE_X4( (font[0x38].f[3]) ), BYTE_X4( (font[0x38].f[3]) ), BYTE_X4( (font[0x38].f[3]) ),
    //     BYTE_X4( (font[0x38].f[4]) ), BYTE_X4( (font[0x38].f[4]) ), BYTE_X4( (font[0x38].f[4]) ), BYTE_X4( (font[0x38].f[4]) )
    // } // 58 X
    // , {
    //     BYTE_X4( (font[0x39].f[0]) ), BYTE_X4( (font[0x39].f[0]) ), BYTE_X4( (font[0x39].f[0]) ), BYTE_X4( (font[0x39].f[0]) ), 
    //     BYTE_X4( (font[0x39].f[1]) ), BYTE_X4( (font[0x39].f[1]) ), BYTE_X4( (font[0x39].f[1]) ), BYTE_X4( (font[0x39].f[1]) ), 
    //     BYTE_X4( (font[0x39].f[2]) ), BYTE_X4( (font[0x39].f[2]) ), BYTE_X4( (font[0x39].f[2]) ), BYTE_X4( (font[0x39].f[2]) ), 
    //     BYTE_X4( (font[0x39].f[3]) ), BYTE_X4( (font[0x39].f[3]) ), BYTE_X4( (font[0x39].f[3]) ), BYTE_X4( (font[0x39].f[3]) ),
    //     BYTE_X4( (font[0x39].f[4]) ), BYTE_X4( (font[0x39].f[4]) ), BYTE_X4( (font[0x39].f[4]) ), BYTE_X4( (font[0x39].f[4]) )
    // } // 59 Y
    // , {
    //     BYTE_X4( (font[0x3a].f[0]) ), BYTE_X4( (font[0x3a].f[0]) ), BYTE_X4( (font[0x3a].f[0]) ), BYTE_X4( (font[0x3a].f[0]) ), 
    //     BYTE_X4( (font[0x3a].f[1]) ), BYTE_X4( (font[0x3a].f[1]) ), BYTE_X4( (font[0x3a].f[1]) ), BYTE_X4( (font[0x3a].f[1]) ), 
    //     BYTE_X4( (font[0x3a].f[2]) ), BYTE_X4( (font[0x3a].f[2]) ), BYTE_X4( (font[0x3a].f[2]) ), BYTE_X4( (font[0x3a].f[2]) ), 
    //     BYTE_X4( (font[0x3a].f[3]) ), BYTE_X4( (font[0x3a].f[3]) ), BYTE_X4( (font[0x3a].f[3]) ), BYTE_X4( (font[0x3a].f[3]) ),
    //     BYTE_X4( (font[0x3a].f[4]) ), BYTE_X4( (font[0x3a].f[4]) ), BYTE_X4( (font[0x3a].f[4]) ), BYTE_X4( (font[0x3a].f[4]) )
    // } // 5a Z
    // , {
    //     BYTE_X4( (font[0x3b].f[0]) ), BYTE_X4( (font[0x3b].f[0]) ), BYTE_X4( (font[0x3b].f[0]) ), BYTE_X4( (font[0x3b].f[0]) ), 
    //     BYTE_X4( (font[0x3b].f[1]) ), BYTE_X4( (font[0x3b].f[1]) ), BYTE_X4( (font[0x3b].f[1]) ), BYTE_X4( (font[0x3b].f[1]) ), 
    //     BYTE_X4( (font[0x3b].f[2]) ), BYTE_X4( (font[0x3b].f[2]) ), BYTE_X4( (font[0x3b].f[2]) ), BYTE_X4( (font[0x3b].f[2]) ), 
    //     BYTE_X4( (font[0x3b].f[3]) ), BYTE_X4( (font[0x3b].f[3]) ), BYTE_X4( (font[0x3b].f[3]) ), BYTE_X4( (font[0x3b].f[3]) ),
    //     BYTE_X4( (font[0x3b].f[4]) ), BYTE_X4( (font[0x3b].f[4]) ), BYTE_X4( (font[0x3b].f[4]) ), BYTE_X4( (font[0x3b].f[4]) )
    // } // 5b [
    // , {
    //     BYTE_X4( (font[0x3c].f[0]) ), BYTE_X4( (font[0x3c].f[0]) ), BYTE_X4( (font[0x3c].f[0]) ), BYTE_X4( (font[0x3c].f[0]) ), 
    //     BYTE_X4( (font[0x3c].f[1]) ), BYTE_X4( (font[0x3c].f[1]) ), BYTE_X4( (font[0x3c].f[1]) ), BYTE_X4( (font[0x3c].f[1]) ), 
    //     BYTE_X4( (font[0x3c].f[2]) ), BYTE_X4( (font[0x3c].f[2]) ), BYTE_X4( (font[0x3c].f[2]) ), BYTE_X4( (font[0x3c].f[2]) ), 
    //     BYTE_X4( (font[0x3c].f[3]) ), BYTE_X4( (font[0x3c].f[3]) ), BYTE_X4( (font[0x3c].f[3]) ), BYTE_X4( (font[0x3c].f[3]) ),
    //     BYTE_X4( (font[0x3c].f[4]) ), BYTE_X4( (font[0x3c].f[4]) ), BYTE_X4( (font[0x3c].f[4]) ), BYTE_X4( (font[0x3c].f[4]) )
    // } // 5c ?
    // , {
    //     BYTE_X4( (font[0x3d].f[0]) ), BYTE_X4( (font[0x3d].f[0]) ), BYTE_X4( (font[0x3d].f[0]) ), BYTE_X4( (font[0x3d].f[0]) ), 
    //     BYTE_X4( (font[0x3d].f[1]) ), BYTE_X4( (font[0x3d].f[1]) ), BYTE_X4( (font[0x3d].f[1]) ), BYTE_X4( (font[0x3d].f[1]) ), 
    //     BYTE_X4( (font[0x3d].f[2]) ), BYTE_X4( (font[0x3d].f[2]) ), BYTE_X4( (font[0x3d].f[2]) ), BYTE_X4( (font[0x3d].f[2]) ), 
    //     BYTE_X4( (font[0x3d].f[3]) ), BYTE_X4( (font[0x3d].f[3]) ), BYTE_X4( (font[0x3d].f[3]) ), BYTE_X4( (font[0x3d].f[3]) ),
    //     BYTE_X4( (font[0x3d].f[4]) ), BYTE_X4( (font[0x3d].f[4]) ), BYTE_X4( (font[0x3d].f[4]) ), BYTE_X4( (font[0x3d].f[4]) )
    // } // 5d ]
    // , {
    //     BYTE_X4( (font[0x3e].f[0]) ), BYTE_X4( (font[0x3e].f[0]) ), BYTE_X4( (font[0x3e].f[0]) ), BYTE_X4( (font[0x3e].f[0]) ), 
    //     BYTE_X4( (font[0x3e].f[1]) ), BYTE_X4( (font[0x3e].f[1]) ), BYTE_X4( (font[0x3e].f[1]) ), BYTE_X4( (font[0x3e].f[1]) ), 
    //     BYTE_X4( (font[0x3e].f[2]) ), BYTE_X4( (font[0x3e].f[2]) ), BYTE_X4( (font[0x3e].f[2]) ), BYTE_X4( (font[0x3e].f[2]) ), 
    //     BYTE_X4( (font[0x3e].f[3]) ), BYTE_X4( (font[0x3e].f[3]) ), BYTE_X4( (font[0x3e].f[3]) ), BYTE_X4( (font[0x3e].f[3]) ),
    //     BYTE_X4( (font[0x3e].f[4]) ), BYTE_X4( (font[0x3e].f[4]) ), BYTE_X4( (font[0x3e].f[4]) ), BYTE_X4( (font[0x3e].f[4]) )
    // } // 5e ^
    // , {
    //     BYTE_X4( (font[0x3f].f[0]) ), BYTE_X4( (font[0x3f].f[0]) ), BYTE_X4( (font[0x3f].f[0]) ), BYTE_X4( (font[0x3f].f[0]) ), 
    //     BYTE_X4( (font[0x3f].f[1]) ), BYTE_X4( (font[0x3f].f[1]) ), BYTE_X4( (font[0x3f].f[1]) ), BYTE_X4( (font[0x3f].f[1]) ), 
    //     BYTE_X4( (font[0x3f].f[2]) ), BYTE_X4( (font[0x3f].f[2]) ), BYTE_X4( (font[0x3f].f[2]) ), BYTE_X4( (font[0x3f].f[2]) ), 
    //     BYTE_X4( (font[0x3f].f[3]) ), BYTE_X4( (font[0x3f].f[3]) ), BYTE_X4( (font[0x3f].f[3]) ), BYTE_X4( (font[0x3f].f[3]) ),
    //     BYTE_X4( (font[0x3f].f[4]) ), BYTE_X4( (font[0x3f].f[4]) ), BYTE_X4( (font[0x3f].f[4]) ), BYTE_X4( (font[0x3f].f[4]) )
    // } // 5f _
    // , {
    //     BYTE_X4( (font[0x40].f[0]) ), BYTE_X4( (font[0x40].f[0]) ), BYTE_X4( (font[0x40].f[0]) ), BYTE_X4( (font[0x40].f[0]) ), 
    //     BYTE_X4( (font[0x40].f[1]) ), BYTE_X4( (font[0x40].f[1]) ), BYTE_X4( (font[0x40].f[1]) ), BYTE_X4( (font[0x40].f[1]) ), 
    //     BYTE_X4( (font[0x40].f[2]) ), BYTE_X4( (font[0x40].f[2]) ), BYTE_X4( (font[0x40].f[2]) ), BYTE_X4( (font[0x40].f[2]) ), 
    //     BYTE_X4( (font[0x40].f[3]) ), BYTE_X4( (font[0x40].f[3]) ), BYTE_X4( (font[0x40].f[3]) ), BYTE_X4( (font[0x40].f[3]) ),
    //     BYTE_X4( (font[0x40].f[4]) ), BYTE_X4( (font[0x40].f[4]) ), BYTE_X4( (font[0x40].f[4]) ), BYTE_X4( (font[0x40].f[4]) )
    // } // 60 `
    // , {
    //     BYTE_X4( (font[0x41].f[0]) ), BYTE_X4( (font[0x41].f[0]) ), BYTE_X4( (font[0x41].f[0]) ), BYTE_X4( (font[0x41].f[0]) ), 
    //     BYTE_X4( (font[0x41].f[1]) ), BYTE_X4( (font[0x41].f[1]) ), BYTE_X4( (font[0x41].f[1]) ), BYTE_X4( (font[0x41].f[1]) ), 
    //     BYTE_X4( (font[0x41].f[2]) ), BYTE_X4( (font[0x41].f[2]) ), BYTE_X4( (font[0x41].f[2]) ), BYTE_X4( (font[0x41].f[2]) ), 
    //     BYTE_X4( (font[0x41].f[3]) ), BYTE_X4( (font[0x41].f[3]) ), BYTE_X4( (font[0x41].f[3]) ), BYTE_X4( (font[0x41].f[3]) ),
    //     BYTE_X4( (font[0x41].f[4]) ), BYTE_X4( (font[0x41].f[4]) ), BYTE_X4( (font[0x41].f[4]) ), BYTE_X4( (font[0x41].f[4]) )
    // } // 61 a
    // , {
    //     BYTE_X4( (font[0x42].f[0]) ), BYTE_X4( (font[0x42].f[0]) ), BYTE_X4( (font[0x42].f[0]) ), BYTE_X4( (font[0x42].f[0]) ), 
    //     BYTE_X4( (font[0x42].f[1]) ), BYTE_X4( (font[0x42].f[1]) ), BYTE_X4( (font[0x42].f[1]) ), BYTE_X4( (font[0x42].f[1]) ), 
    //     BYTE_X4( (font[0x42].f[2]) ), BYTE_X4( (font[0x42].f[2]) ), BYTE_X4( (font[0x42].f[2]) ), BYTE_X4( (font[0x42].f[2]) ), 
    //     BYTE_X4( (font[0x42].f[3]) ), BYTE_X4( (font[0x42].f[3]) ), BYTE_X4( (font[0x42].f[3]) ), BYTE_X4( (font[0x42].f[3]) ),
    //     BYTE_X4( (font[0x42].f[4]) ), BYTE_X4( (font[0x42].f[4]) ), BYTE_X4( (font[0x42].f[4]) ), BYTE_X4( (font[0x42].f[4]) )
    // } // 62 b
    // , {
    //     BYTE_X4( (font[0x43].f[0]) ), BYTE_X4( (font[0x43].f[0]) ), BYTE_X4( (font[0x43].f[0]) ), BYTE_X4( (font[0x43].f[0]) ), 
    //     BYTE_X4( (font[0x43].f[1]) ), BYTE_X4( (font[0x43].f[1]) ), BYTE_X4( (font[0x43].f[1]) ), BYTE_X4( (font[0x43].f[1]) ), 
    //     BYTE_X4( (font[0x43].f[2]) ), BYTE_X4( (font[0x43].f[2]) ), BYTE_X4( (font[0x43].f[2]) ), BYTE_X4( (font[0x43].f[2]) ), 
    //     BYTE_X4( (font[0x43].f[3]) ), BYTE_X4( (font[0x43].f[3]) ), BYTE_X4( (font[0x43].f[3]) ), BYTE_X4( (font[0x43].f[3]) ),
    //     BYTE_X4( (font[0x43].f[4]) ), BYTE_X4( (font[0x43].f[4]) ), BYTE_X4( (font[0x43].f[4]) ), BYTE_X4( (font[0x43].f[4]) )
    // } // 63 c
    // , {
    //     BYTE_X4( (font[0x44].f[0]) ), BYTE_X4( (font[0x44].f[0]) ), BYTE_X4( (font[0x44].f[0]) ), BYTE_X4( (font[0x44].f[0]) ), 
    //     BYTE_X4( (font[0x44].f[1]) ), BYTE_X4( (font[0x44].f[1]) ), BYTE_X4( (font[0x44].f[1]) ), BYTE_X4( (font[0x44].f[1]) ), 
    //     BYTE_X4( (font[0x44].f[2]) ), BYTE_X4( (font[0x44].f[2]) ), BYTE_X4( (font[0x44].f[2]) ), BYTE_X4( (font[0x44].f[2]) ), 
    //     BYTE_X4( (font[0x44].f[3]) ), BYTE_X4( (font[0x44].f[3]) ), BYTE_X4( (font[0x44].f[3]) ), BYTE_X4( (font[0x44].f[3]) ),
    //     BYTE_X4( (font[0x44].f[4]) ), BYTE_X4( (font[0x44].f[4]) ), BYTE_X4( (font[0x44].f[4]) ), BYTE_X4( (font[0x44].f[4]) )
    // } // 64 d
    // , {
    //     BYTE_X4( (font[0x45].f[0]) ), BYTE_X4( (font[0x45].f[0]) ), BYTE_X4( (font[0x45].f[0]) ), BYTE_X4( (font[0x45].f[0]) ), 
    //     BYTE_X4( (font[0x45].f[1]) ), BYTE_X4( (font[0x45].f[1]) ), BYTE_X4( (font[0x45].f[1]) ), BYTE_X4( (font[0x45].f[1]) ), 
    //     BYTE_X4( (font[0x45].f[2]) ), BYTE_X4( (font[0x45].f[2]) ), BYTE_X4( (font[0x45].f[2]) ), BYTE_X4( (font[0x45].f[2]) ), 
    //     BYTE_X4( (font[0x45].f[3]) ), BYTE_X4( (font[0x45].f[3]) ), BYTE_X4( (font[0x45].f[3]) ), BYTE_X4( (font[0x45].f[3]) ),
    //     BYTE_X4( (font[0x45].f[4]) ), BYTE_X4( (font[0x45].f[4]) ), BYTE_X4( (font[0x45].f[4]) ), BYTE_X4( (font[0x45].f[4]) )
    // } // 65 e
    // , {
    //     BYTE_X4( (font[0x46].f[0]) ), BYTE_X4( (font[0x46].f[0]) ), BYTE_X4( (font[0x46].f[0]) ), BYTE_X4( (font[0x46].f[0]) ), 
    //     BYTE_X4( (font[0x46].f[1]) ), BYTE_X4( (font[0x46].f[1]) ), BYTE_X4( (font[0x46].f[1]) ), BYTE_X4( (font[0x46].f[1]) ), 
    //     BYTE_X4( (font[0x46].f[2]) ), BYTE_X4( (font[0x46].f[2]) ), BYTE_X4( (font[0x46].f[2]) ), BYTE_X4( (font[0x46].f[2]) ), 
    //     BYTE_X4( (font[0x46].f[3]) ), BYTE_X4( (font[0x46].f[3]) ), BYTE_X4( (font[0x46].f[3]) ), BYTE_X4( (font[0x46].f[3]) ),
    //     BYTE_X4( (font[0x46].f[4]) ), BYTE_X4( (font[0x46].f[4]) ), BYTE_X4( (font[0x46].f[4]) ), BYTE_X4( (font[0x46].f[4]) )
    // } // 66 f
    // , {
    //     BYTE_X4( (font[0x47].f[0]) ), BYTE_X4( (font[0x47].f[0]) ), BYTE_X4( (font[0x47].f[0]) ), BYTE_X4( (font[0x47].f[0]) ), 
    //     BYTE_X4( (font[0x47].f[1]) ), BYTE_X4( (font[0x47].f[1]) ), BYTE_X4( (font[0x47].f[1]) ), BYTE_X4( (font[0x47].f[1]) ), 
    //     BYTE_X4( (font[0x47].f[2]) ), BYTE_X4( (font[0x47].f[2]) ), BYTE_X4( (font[0x47].f[2]) ), BYTE_X4( (font[0x47].f[2]) ), 
    //     BYTE_X4( (font[0x47].f[3]) ), BYTE_X4( (font[0x47].f[3]) ), BYTE_X4( (font[0x47].f[3]) ), BYTE_X4( (font[0x47].f[3]) ),
    //     BYTE_X4( (font[0x47].f[4]) ), BYTE_X4( (font[0x47].f[4]) ), BYTE_X4( (font[0x47].f[4]) ), BYTE_X4( (font[0x47].f[4]) )
    // } // 67 g
    // , {
    //     BYTE_X4( (font[0x48].f[0]) ), BYTE_X4( (font[0x48].f[0]) ), BYTE_X4( (font[0x48].f[0]) ), BYTE_X4( (font[0x48].f[0]) ), 
    //     BYTE_X4( (font[0x48].f[1]) ), BYTE_X4( (font[0x48].f[1]) ), BYTE_X4( (font[0x48].f[1]) ), BYTE_X4( (font[0x48].f[1]) ), 
    //     BYTE_X4( (font[0x48].f[2]) ), BYTE_X4( (font[0x48].f[2]) ), BYTE_X4( (font[0x48].f[2]) ), BYTE_X4( (font[0x48].f[2]) ), 
    //     BYTE_X4( (font[0x48].f[3]) ), BYTE_X4( (font[0x48].f[3]) ), BYTE_X4( (font[0x48].f[3]) ), BYTE_X4( (font[0x48].f[3]) ),
    //     BYTE_X4( (font[0x48].f[4]) ), BYTE_X4( (font[0x48].f[4]) ), BYTE_X4( (font[0x48].f[4]) ), BYTE_X4( (font[0x48].f[4]) )
    // } // 68 h
    // , {
    //     BYTE_X4( (font[0x49].f[0]) ), BYTE_X4( (font[0x49].f[0]) ), BYTE_X4( (font[0x49].f[0]) ), BYTE_X4( (font[0x49].f[0]) ), 
    //     BYTE_X4( (font[0x49].f[1]) ), BYTE_X4( (font[0x49].f[1]) ), BYTE_X4( (font[0x49].f[1]) ), BYTE_X4( (font[0x49].f[1]) ), 
    //     BYTE_X4( (font[0x49].f[2]) ), BYTE_X4( (font[0x49].f[2]) ), BYTE_X4( (font[0x49].f[2]) ), BYTE_X4( (font[0x49].f[2]) ), 
    //     BYTE_X4( (font[0x49].f[3]) ), BYTE_X4( (font[0x49].f[3]) ), BYTE_X4( (font[0x49].f[3]) ), BYTE_X4( (font[0x49].f[3]) ),
    //     BYTE_X4( (font[0x49].f[4]) ), BYTE_X4( (font[0x49].f[4]) ), BYTE_X4( (font[0x49].f[4]) ), BYTE_X4( (font[0x49].f[4]) )
    // } // 69 i
    // , {
    //     BYTE_X4( (font[0x4a].f[0]) ), BYTE_X4( (font[0x4a].f[0]) ), BYTE_X4( (font[0x4a].f[0]) ), BYTE_X4( (font[0x4a].f[0]) ), 
    //     BYTE_X4( (font[0x4a].f[1]) ), BYTE_X4( (font[0x4a].f[1]) ), BYTE_X4( (font[0x4a].f[1]) ), BYTE_X4( (font[0x4a].f[1]) ), 
    //     BYTE_X4( (font[0x4a].f[2]) ), BYTE_X4( (font[0x4a].f[2]) ), BYTE_X4( (font[0x4a].f[2]) ), BYTE_X4( (font[0x4a].f[2]) ), 
    //     BYTE_X4( (font[0x4a].f[3]) ), BYTE_X4( (font[0x4a].f[3]) ), BYTE_X4( (font[0x4a].f[3]) ), BYTE_X4( (font[0x4a].f[3]) ),
    //     BYTE_X4( (font[0x4a].f[4]) ), BYTE_X4( (font[0x4a].f[4]) ), BYTE_X4( (font[0x4a].f[4]) ), BYTE_X4( (font[0x4a].f[4]) )
    // } // 6a j
    // , {
    //     BYTE_X4( (font[0x4b].f[0]) ), BYTE_X4( (font[0x4b].f[0]) ), BYTE_X4( (font[0x4b].f[0]) ), BYTE_X4( (font[0x4b].f[0]) ), 
    //     BYTE_X4( (font[0x4b].f[1]) ), BYTE_X4( (font[0x4b].f[1]) ), BYTE_X4( (font[0x4b].f[1]) ), BYTE_X4( (font[0x4b].f[1]) ), 
    //     BYTE_X4( (font[0x4b].f[2]) ), BYTE_X4( (font[0x4b].f[2]) ), BYTE_X4( (font[0x4b].f[2]) ), BYTE_X4( (font[0x4b].f[2]) ), 
    //     BYTE_X4( (font[0x4b].f[3]) ), BYTE_X4( (font[0x4b].f[3]) ), BYTE_X4( (font[0x4b].f[3]) ), BYTE_X4( (font[0x4b].f[3]) ),
    //     BYTE_X4( (font[0x4b].f[4]) ), BYTE_X4( (font[0x4b].f[4]) ), BYTE_X4( (font[0x4b].f[4]) ), BYTE_X4( (font[0x4b].f[4]) )
    // } // 6b k
    // , {
    //     BYTE_X4( (font[0x4c].f[0]) ), BYTE_X4( (font[0x4c].f[0]) ), BYTE_X4( (font[0x4c].f[0]) ), BYTE_X4( (font[0x4c].f[0]) ), 
    //     BYTE_X4( (font[0x4c].f[1]) ), BYTE_X4( (font[0x4c].f[1]) ), BYTE_X4( (font[0x4c].f[1]) ), BYTE_X4( (font[0x4c].f[1]) ), 
    //     BYTE_X4( (font[0x4c].f[2]) ), BYTE_X4( (font[0x4c].f[2]) ), BYTE_X4( (font[0x4c].f[2]) ), BYTE_X4( (font[0x4c].f[2]) ), 
    //     BYTE_X4( (font[0x4c].f[3]) ), BYTE_X4( (font[0x4c].f[3]) ), BYTE_X4( (font[0x4c].f[3]) ), BYTE_X4( (font[0x4c].f[3]) ),
    //     BYTE_X4( (font[0x4c].f[4]) ), BYTE_X4( (font[0x4c].f[4]) ), BYTE_X4( (font[0x4c].f[4]) ), BYTE_X4( (font[0x4c].f[4]) )
    // } // 6c l
    // , {
    //     BYTE_X4( (font[0x4d].f[0]) ), BYTE_X4( (font[0x4d].f[0]) ), BYTE_X4( (font[0x4d].f[0]) ), BYTE_X4( (font[0x4d].f[0]) ), 
    //     BYTE_X4( (font[0x4d].f[1]) ), BYTE_X4( (font[0x4d].f[1]) ), BYTE_X4( (font[0x4d].f[1]) ), BYTE_X4( (font[0x4d].f[1]) ), 
    //     BYTE_X4( (font[0x4d].f[2]) ), BYTE_X4( (font[0x4d].f[2]) ), BYTE_X4( (font[0x4d].f[2]) ), BYTE_X4( (font[0x4d].f[2]) ), 
    //     BYTE_X4( (font[0x4d].f[3]) ), BYTE_X4( (font[0x4d].f[3]) ), BYTE_X4( (font[0x4d].f[3]) ), BYTE_X4( (font[0x4d].f[3]) ),
    //     BYTE_X4( (font[0x4d].f[4]) ), BYTE_X4( (font[0x4d].f[4]) ), BYTE_X4( (font[0x4d].f[4]) ), BYTE_X4( (font[0x4d].f[4]) )
    // } // 6d m
    // , {
    //     BYTE_X4( (font[0x4e].f[0]) ), BYTE_X4( (font[0x4e].f[0]) ), BYTE_X4( (font[0x4e].f[0]) ), BYTE_X4( (font[0x4e].f[0]) ), 
    //     BYTE_X4( (font[0x4e].f[1]) ), BYTE_X4( (font[0x4e].f[1]) ), BYTE_X4( (font[0x4e].f[1]) ), BYTE_X4( (font[0x4e].f[1]) ), 
    //     BYTE_X4( (font[0x4e].f[2]) ), BYTE_X4( (font[0x4e].f[2]) ), BYTE_X4( (font[0x4e].f[2]) ), BYTE_X4( (font[0x4e].f[2]) ), 
    //     BYTE_X4( (font[0x4e].f[3]) ), BYTE_X4( (font[0x4e].f[3]) ), BYTE_X4( (font[0x4e].f[3]) ), BYTE_X4( (font[0x4e].f[3]) ),
    //     BYTE_X4( (font[0x4e].f[4]) ), BYTE_X4( (font[0x4e].f[4]) ), BYTE_X4( (font[0x4e].f[4]) ), BYTE_X4( (font[0x4e].f[4]) )
    // } // 6e n
    // , {
    //     BYTE_X4( (font[0x4f].f[0]) ), BYTE_X4( (font[0x4f].f[0]) ), BYTE_X4( (font[0x4f].f[0]) ), BYTE_X4( (font[0x4f].f[0]) ), 
    //     BYTE_X4( (font[0x4f].f[1]) ), BYTE_X4( (font[0x4f].f[1]) ), BYTE_X4( (font[0x4f].f[1]) ), BYTE_X4( (font[0x4f].f[1]) ), 
    //     BYTE_X4( (font[0x4f].f[2]) ), BYTE_X4( (font[0x4f].f[2]) ), BYTE_X4( (font[0x4f].f[2]) ), BYTE_X4( (font[0x4f].f[2]) ), 
    //     BYTE_X4( (font[0x4f].f[3]) ), BYTE_X4( (font[0x4f].f[3]) ), BYTE_X4( (font[0x4f].f[3]) ), BYTE_X4( (font[0x4f].f[3]) ),
    //     BYTE_X4( (font[0x4f].f[4]) ), BYTE_X4( (font[0x4f].f[4]) ), BYTE_X4( (font[0x4f].f[4]) ), BYTE_X4( (font[0x4f].f[4]) )
    // } // 6f o
    // , {
    //     BYTE_X4( (font[0x50].f[0]) ), BYTE_X4( (font[0x50].f[0]) ), BYTE_X4( (font[0x50].f[0]) ), BYTE_X4( (font[0x50].f[0]) ), 
    //     BYTE_X4( (font[0x50].f[1]) ), BYTE_X4( (font[0x50].f[1]) ), BYTE_X4( (font[0x50].f[1]) ), BYTE_X4( (font[0x50].f[1]) ), 
    //     BYTE_X4( (font[0x50].f[2]) ), BYTE_X4( (font[0x50].f[2]) ), BYTE_X4( (font[0x50].f[2]) ), BYTE_X4( (font[0x50].f[2]) ), 
    //     BYTE_X4( (font[0x50].f[3]) ), BYTE_X4( (font[0x50].f[3]) ), BYTE_X4( (font[0x50].f[3]) ), BYTE_X4( (font[0x50].f[3]) ),
    //     BYTE_X4( (font[0x50].f[4]) ), BYTE_X4( (font[0x50].f[4]) ), BYTE_X4( (font[0x50].f[4]) ), BYTE_X4( (font[0x50].f[4]) )
    // } // 70 p
    // , {
    //     BYTE_X4( (font[0x51].f[0]) ), BYTE_X4( (font[0x51].f[0]) ), BYTE_X4( (font[0x51].f[0]) ), BYTE_X4( (font[0x51].f[0]) ), 
    //     BYTE_X4( (font[0x51].f[1]) ), BYTE_X4( (font[0x51].f[1]) ), BYTE_X4( (font[0x51].f[1]) ), BYTE_X4( (font[0x51].f[1]) ), 
    //     BYTE_X4( (font[0x51].f[2]) ), BYTE_X4( (font[0x51].f[2]) ), BYTE_X4( (font[0x51].f[2]) ), BYTE_X4( (font[0x51].f[2]) ), 
    //     BYTE_X4( (font[0x51].f[3]) ), BYTE_X4( (font[0x51].f[3]) ), BYTE_X4( (font[0x51].f[3]) ), BYTE_X4( (font[0x51].f[3]) ),
    //     BYTE_X4( (font[0x51].f[4]) ), BYTE_X4( (font[0x51].f[4]) ), BYTE_X4( (font[0x51].f[4]) ), BYTE_X4( (font[0x51].f[4]) )
    // } // 71 q
    // , {
    //     BYTE_X4( (font[0x52].f[0]) ), BYTE_X4( (font[0x52].f[0]) ), BYTE_X4( (font[0x52].f[0]) ), BYTE_X4( (font[0x52].f[0]) ), 
    //     BYTE_X4( (font[0x52].f[1]) ), BYTE_X4( (font[0x52].f[1]) ), BYTE_X4( (font[0x52].f[1]) ), BYTE_X4( (font[0x52].f[1]) ), 
    //     BYTE_X4( (font[0x52].f[2]) ), BYTE_X4( (font[0x52].f[2]) ), BYTE_X4( (font[0x52].f[2]) ), BYTE_X4( (font[0x52].f[2]) ), 
    //     BYTE_X4( (font[0x52].f[3]) ), BYTE_X4( (font[0x52].f[3]) ), BYTE_X4( (font[0x52].f[3]) ), BYTE_X4( (font[0x52].f[3]) ),
    //     BYTE_X4( (font[0x52].f[4]) ), BYTE_X4( (font[0x52].f[4]) ), BYTE_X4( (font[0x52].f[4]) ), BYTE_X4( (font[0x52].f[4]) )
    // } // 72 r
    // , {
    //     BYTE_X4( (font[0x53].f[0]) ), BYTE_X4( (font[0x53].f[0]) ), BYTE_X4( (font[0x53].f[0]) ), BYTE_X4( (font[0x53].f[0]) ), 
    //     BYTE_X4( (font[0x53].f[1]) ), BYTE_X4( (font[0x53].f[1]) ), BYTE_X4( (font[0x53].f[1]) ), BYTE_X4( (font[0x53].f[1]) ), 
    //     BYTE_X4( (font[0x53].f[2]) ), BYTE_X4( (font[0x53].f[2]) ), BYTE_X4( (font[0x53].f[2]) ), BYTE_X4( (font[0x53].f[2]) ), 
    //     BYTE_X4( (font[0x53].f[3]) ), BYTE_X4( (font[0x53].f[3]) ), BYTE_X4( (font[0x53].f[3]) ), BYTE_X4( (font[0x53].f[3]) ),
    //     BYTE_X4( (font[0x53].f[4]) ), BYTE_X4( (font[0x53].f[4]) ), BYTE_X4( (font[0x53].f[4]) ), BYTE_X4( (font[0x53].f[4]) )
    // } // 73 s
    // , {
    //     BYTE_X4( (font[0x54].f[0]) ), BYTE_X4( (font[0x54].f[0]) ), BYTE_X4( (font[0x54].f[0]) ), BYTE_X4( (font[0x54].f[0]) ), 
    //     BYTE_X4( (font[0x54].f[1]) ), BYTE_X4( (font[0x54].f[1]) ), BYTE_X4( (font[0x54].f[1]) ), BYTE_X4( (font[0x54].f[1]) ), 
    //     BYTE_X4( (font[0x54].f[2]) ), BYTE_X4( (font[0x54].f[2]) ), BYTE_X4( (font[0x54].f[2]) ), BYTE_X4( (font[0x54].f[2]) ), 
    //     BYTE_X4( (font[0x54].f[3]) ), BYTE_X4( (font[0x54].f[3]) ), BYTE_X4( (font[0x54].f[3]) ), BYTE_X4( (font[0x54].f[3]) ),
    //     BYTE_X4( (font[0x54].f[4]) ), BYTE_X4( (font[0x54].f[4]) ), BYTE_X4( (font[0x54].f[4]) ), BYTE_X4( (font[0x54].f[4]) )
    // } // 74 t
    // , {
    //     BYTE_X4( (font[0x55].f[0]) ), BYTE_X4( (font[0x55].f[0]) ), BYTE_X4( (font[0x55].f[0]) ), BYTE_X4( (font[0x55].f[0]) ), 
    //     BYTE_X4( (font[0x55].f[1]) ), BYTE_X4( (font[0x55].f[1]) ), BYTE_X4( (font[0x55].f[1]) ), BYTE_X4( (font[0x55].f[1]) ), 
    //     BYTE_X4( (font[0x55].f[2]) ), BYTE_X4( (font[0x55].f[2]) ), BYTE_X4( (font[0x55].f[2]) ), BYTE_X4( (font[0x55].f[2]) ), 
    //     BYTE_X4( (font[0x55].f[3]) ), BYTE_X4( (font[0x55].f[3]) ), BYTE_X4( (font[0x55].f[3]) ), BYTE_X4( (font[0x55].f[3]) ),
    //     BYTE_X4( (font[0x55].f[4]) ), BYTE_X4( (font[0x55].f[4]) ), BYTE_X4( (font[0x55].f[4]) ), BYTE_X4( (font[0x55].f[4]) )
    // } // 75 u
    // , {
    //     BYTE_X4( (font[0x56].f[0]) ), BYTE_X4( (font[0x56].f[0]) ), BYTE_X4( (font[0x56].f[0]) ), BYTE_X4( (font[0x56].f[0]) ), 
    //     BYTE_X4( (font[0x56].f[1]) ), BYTE_X4( (font[0x56].f[1]) ), BYTE_X4( (font[0x56].f[1]) ), BYTE_X4( (font[0x56].f[1]) ), 
    //     BYTE_X4( (font[0x56].f[2]) ), BYTE_X4( (font[0x56].f[2]) ), BYTE_X4( (font[0x56].f[2]) ), BYTE_X4( (font[0x56].f[2]) ), 
    //     BYTE_X4( (font[0x56].f[3]) ), BYTE_X4( (font[0x56].f[3]) ), BYTE_X4( (font[0x56].f[3]) ), BYTE_X4( (font[0x56].f[3]) ),
    //     BYTE_X4( (font[0x56].f[4]) ), BYTE_X4( (font[0x56].f[4]) ), BYTE_X4( (font[0x56].f[4]) ), BYTE_X4( (font[0x56].f[4]) )
    // } // 76 v
    // , {
    //     BYTE_X4( (font[0x57].f[0]) ), BYTE_X4( (font[0x57].f[0]) ), BYTE_X4( (font[0x57].f[0]) ), BYTE_X4( (font[0x57].f[0]) ), 
    //     BYTE_X4( (font[0x57].f[1]) ), BYTE_X4( (font[0x57].f[1]) ), BYTE_X4( (font[0x57].f[1]) ), BYTE_X4( (font[0x57].f[1]) ), 
    //     BYTE_X4( (font[0x57].f[2]) ), BYTE_X4( (font[0x57].f[2]) ), BYTE_X4( (font[0x57].f[2]) ), BYTE_X4( (font[0x57].f[2]) ), 
    //     BYTE_X4( (font[0x57].f[3]) ), BYTE_X4( (font[0x57].f[3]) ), BYTE_X4( (font[0x57].f[3]) ), BYTE_X4( (font[0x57].f[3]) ),
    //     BYTE_X4( (font[0x57].f[4]) ), BYTE_X4( (font[0x57].f[4]) ), BYTE_X4( (font[0x57].f[4]) ), BYTE_X4( (font[0x57].f[4]) )
    // } // 77 w
    // , {
    //     BYTE_X4( (font[0x58].f[0]) ), BYTE_X4( (font[0x58].f[0]) ), BYTE_X4( (font[0x58].f[0]) ), BYTE_X4( (font[0x58].f[0]) ), 
    //     BYTE_X4( (font[0x58].f[1]) ), BYTE_X4( (font[0x58].f[1]) ), BYTE_X4( (font[0x58].f[1]) ), BYTE_X4( (font[0x58].f[1]) ), 
    //     BYTE_X4( (font[0x58].f[2]) ), BYTE_X4( (font[0x58].f[2]) ), BYTE_X4( (font[0x58].f[2]) ), BYTE_X4( (font[0x58].f[2]) ), 
    //     BYTE_X4( (font[0x58].f[3]) ), BYTE_X4( (font[0x58].f[3]) ), BYTE_X4( (font[0x58].f[3]) ), BYTE_X4( (font[0x58].f[3]) ),
    //     BYTE_X4( (font[0x58].f[4]) ), BYTE_X4( (font[0x58].f[4]) ), BYTE_X4( (font[0x58].f[4]) ), BYTE_X4( (font[0x58].f[4]) )
    // } // 78 x
    // , {
    //     BYTE_X4( (font[0x59].f[0]) ), BYTE_X4( (font[0x59].f[0]) ), BYTE_X4( (font[0x59].f[0]) ), BYTE_X4( (font[0x59].f[0]) ), 
    //     BYTE_X4( (font[0x59].f[1]) ), BYTE_X4( (font[0x59].f[1]) ), BYTE_X4( (font[0x59].f[1]) ), BYTE_X4( (font[0x59].f[1]) ), 
    //     BYTE_X4( (font[0x59].f[2]) ), BYTE_X4( (font[0x59].f[2]) ), BYTE_X4( (font[0x59].f[2]) ), BYTE_X4( (font[0x59].f[2]) ), 
    //     BYTE_X4( (font[0x59].f[3]) ), BYTE_X4( (font[0x59].f[3]) ), BYTE_X4( (font[0x59].f[3]) ), BYTE_X4( (font[0x59].f[3]) ),
    //     BYTE_X4( (font[0x59].f[4]) ), BYTE_X4( (font[0x59].f[4]) ), BYTE_X4( (font[0x59].f[4]) ), BYTE_X4( (font[0x59].f[4]) )
    // } // 79 y
    // , {
    //     BYTE_X4( (font[0x5a].f[0]) ), BYTE_X4( (font[0x5a].f[0]) ), BYTE_X4( (font[0x5a].f[0]) ), BYTE_X4( (font[0x5a].f[0]) ), 
    //     BYTE_X4( (font[0x5a].f[1]) ), BYTE_X4( (font[0x5a].f[1]) ), BYTE_X4( (font[0x5a].f[1]) ), BYTE_X4( (font[0x5a].f[1]) ), 
    //     BYTE_X4( (font[0x5a].f[2]) ), BYTE_X4( (font[0x5a].f[2]) ), BYTE_X4( (font[0x5a].f[2]) ), BYTE_X4( (font[0x5a].f[2]) ), 
    //     BYTE_X4( (font[0x5a].f[3]) ), BYTE_X4( (font[0x5a].f[3]) ), BYTE_X4( (font[0x5a].f[3]) ), BYTE_X4( (font[0x5a].f[3]) ),
    //     BYTE_X4( (font[0x5a].f[4]) ), BYTE_X4( (font[0x5a].f[4]) ), BYTE_X4( (font[0x5a].f[4]) ), BYTE_X4( (font[0x5a].f[4]) )
    // } // 7a z
    // , {
    //     BYTE_X4( (font[0x5b].f[0]) ), BYTE_X4( (font[0x5b].f[0]) ), BYTE_X4( (font[0x5b].f[0]) ), BYTE_X4( (font[0x5b].f[0]) ), 
    //     BYTE_X4( (font[0x5b].f[1]) ), BYTE_X4( (font[0x5b].f[1]) ), BYTE_X4( (font[0x5b].f[1]) ), BYTE_X4( (font[0x5b].f[1]) ), 
    //     BYTE_X4( (font[0x5b].f[2]) ), BYTE_X4( (font[0x5b].f[2]) ), BYTE_X4( (font[0x5b].f[2]) ), BYTE_X4( (font[0x5b].f[2]) ), 
    //     BYTE_X4( (font[0x5b].f[3]) ), BYTE_X4( (font[0x5b].f[3]) ), BYTE_X4( (font[0x5b].f[3]) ), BYTE_X4( (font[0x5b].f[3]) ),
    //     BYTE_X4( (font[0x5b].f[4]) ), BYTE_X4( (font[0x5b].f[4]) ), BYTE_X4( (font[0x5b].f[4]) ), BYTE_X4( (font[0x5b].f[4]) )
    // } // 7b {
    // , {
    //     BYTE_X4( (font[0x5c].f[0]) ), BYTE_X4( (font[0x5c].f[0]) ), BYTE_X4( (font[0x5c].f[0]) ), BYTE_X4( (font[0x5c].f[0]) ), 
    //     BYTE_X4( (font[0x5c].f[1]) ), BYTE_X4( (font[0x5c].f[1]) ), BYTE_X4( (font[0x5c].f[1]) ), BYTE_X4( (font[0x5c].f[1]) ), 
    //     BYTE_X4( (font[0x5c].f[2]) ), BYTE_X4( (font[0x5c].f[2]) ), BYTE_X4( (font[0x5c].f[2]) ), BYTE_X4( (font[0x5c].f[2]) ), 
    //     BYTE_X4( (font[0x5c].f[3]) ), BYTE_X4( (font[0x5c].f[3]) ), BYTE_X4( (font[0x5c].f[3]) ), BYTE_X4( (font[0x5c].f[3]) ),
    //     BYTE_X4( (font[0x5c].f[4]) ), BYTE_X4( (font[0x5c].f[4]) ), BYTE_X4( (font[0x5c].f[4]) ), BYTE_X4( (font[0x5c].f[4]) )
    // } // 7c |
    // , {
    //     BYTE_X4( (font[0x5d].f[0]) ), BYTE_X4( (font[0x5d].f[0]) ), BYTE_X4( (font[0x5d].f[0]) ), BYTE_X4( (font[0x5d].f[0]) ), 
    //     BYTE_X4( (font[0x5d].f[1]) ), BYTE_X4( (font[0x5d].f[1]) ), BYTE_X4( (font[0x5d].f[1]) ), BYTE_X4( (font[0x5d].f[1]) ), 
    //     BYTE_X4( (font[0x5d].f[2]) ), BYTE_X4( (font[0x5d].f[2]) ), BYTE_X4( (font[0x5d].f[2]) ), BYTE_X4( (font[0x5d].f[2]) ), 
    //     BYTE_X4( (font[0x5d].f[3]) ), BYTE_X4( (font[0x5d].f[3]) ), BYTE_X4( (font[0x5d].f[3]) ), BYTE_X4( (font[0x5d].f[3]) ),
    //     BYTE_X4( (font[0x5d].f[4]) ), BYTE_X4( (font[0x5d].f[4]) ), BYTE_X4( (font[0x5d].f[4]) ), BYTE_X4( (font[0x5d].f[4]) )
    // } // 7d }
    // , {
    //     BYTE_X4( (font[0x5e].f[0]) ), BYTE_X4( (font[0x5e].f[0]) ), BYTE_X4( (font[0x5e].f[0]) ), BYTE_X4( (font[0x5e].f[0]) ), 
    //     BYTE_X4( (font[0x5e].f[1]) ), BYTE_X4( (font[0x5e].f[1]) ), BYTE_X4( (font[0x5e].f[1]) ), BYTE_X4( (font[0x5e].f[1]) ), 
    //     BYTE_X4( (font[0x5e].f[2]) ), BYTE_X4( (font[0x5e].f[2]) ), BYTE_X4( (font[0x5e].f[2]) ), BYTE_X4( (font[0x5e].f[2]) ), 
    //     BYTE_X4( (font[0x5e].f[3]) ), BYTE_X4( (font[0x5e].f[3]) ), BYTE_X4( (font[0x5e].f[3]) ), BYTE_X4( (font[0x5e].f[3]) ),
    //     BYTE_X4( (font[0x5e].f[4]) ), BYTE_X4( (font[0x5e].f[4]) ), BYTE_X4( (font[0x5e].f[4]) ), BYTE_X4( (font[0x5e].f[4]) )
    // } // 7e ?
    // , {
    //     BYTE_X4( (font[0x5f].f[0]) ), BYTE_X4( (font[0x5f].f[0]) ), BYTE_X4( (font[0x5f].f[0]) ), BYTE_X4( (font[0x5f].f[0]) ), 
    //     BYTE_X4( (font[0x5f].f[1]) ), BYTE_X4( (font[0x5f].f[1]) ), BYTE_X4( (font[0x5f].f[1]) ), BYTE_X4( (font[0x5f].f[1]) ), 
    //     BYTE_X4( (font[0x5f].f[2]) ), BYTE_X4( (font[0x5f].f[2]) ), BYTE_X4( (font[0x5f].f[2]) ), BYTE_X4( (font[0x5f].f[2]) ), 
    //     BYTE_X4( (font[0x5f].f[3]) ), BYTE_X4( (font[0x5f].f[3]) ), BYTE_X4( (font[0x5f].f[3]) ), BYTE_X4( (font[0x5f].f[3]) ),
    //     BYTE_X4( (font[0x5f].f[4]) ), BYTE_X4( (font[0x5f].f[4]) ), BYTE_X4( (font[0x5f].f[4]) ), BYTE_X4( (font[0x5f].f[4]) )
    // } // 7f ?
};

