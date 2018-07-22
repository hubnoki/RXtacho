/*
 * ST7735S_regs.c
 *
 *  Created on: 2016/10/29
 *      Author: akihiro
 */


#include "lcdc_ST7735S.h"


#ifdef ST7735S_REG_ACCESS

const ST7735S_REG ST7735S_regs_00to3A[] =
{
    {REG_W, 0}, // 00h ST7735S_NOP
    {REG_W, 0}, // 01h ST7735S_SWRESET
    {REG_N, 0},
    {REG_N, 0},
    {REG_R, 3}, // 04h ST7735S_RDDID
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_R, 4}, // 09h ST7735S_RDDST
    {REG_R, 1}, // 0Ah ST7735S_RDDPM
    {REG_R, 1}, // 0Bh ST7735S_RDD_MADCTL
    {REG_R, 1}, // 0Ch ST7735S_RDD_COLMOD
    {REG_R, 1}, // 0Dh ST7735S_RDDIM
    {REG_R, 1}, // 0Eh ST7735S_RDDSM
    {REG_R, 1}, // 0Fh ST7735S_RDDSDR

    {REG_W, 0}, // 10h ST7735S_SLPIN
    {REG_W, 0}, // 11h ST7735S_SLPOUT
    {REG_W, 0}, // 12h ST7735S_PTLON
    {REG_W, 0}, // 13h ST7735S_NORON
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},

    {REG_W, 0}, // 20h ST7735S_INVOFF
    {REG_W, 0}, // 21h ST7735S_INVON
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_W, 1}, // 26h ST7735S_GAMSET
    {REG_N, 0},
    {REG_W, 0}, // 28h ST7735S_DISPOFF
    {REG_W, 0}, // 29h ST7735S_DISPON
    {REG_W, 4}, // 2Ah ST7735S_CASET
    {REG_W, 4}, // 2Bh ST7735S_RASET
    {REG_W, LCDC_ROW*LCDC_COL}, // 2Ch ST7735S_RAMWR
    {REG_W, 128}, // 2Dh ST7735S_RGBSET
    {REG_R, LCDC_ROW*LCDC_COL}, // 2Eh ST7735S_RAMRD
    {REG_N, 0},

    {REG_W, 4}, // 30h ST7735S_PTLAR
    {REG_N, 0},
    {REG_N, 0},
    {REG_W, 6}, // 33h ST7735S_SCRLAR
    {REG_W, 0}, // 34h ST7735S_TEOFF
    {REG_W, 0}, // 35h ST7735S_TEON
    {REG_W, 1}, // 36h ST7735S_MADCTL
    {REG_W, 2}, // 37h ST7735S_VSCSAD
    {REG_W, 0}, // 38h ST7735S_IDMOFF
    {REG_W, 0}, // 39h ST7735S_IDMON
    {REG_W, 1} // 3Ah ST7735S_COLMOD
};

const ST7735S_REG ST7735S_regs_B0toFF[] =
{
    {REG_N, 0},
    {REG_W, 3}, // B1h ST7735S_FRMCTR1
    {REG_W, 3}, // B2h ST7735S_FRMCTR2
    {REG_W, 6}, // B3h ST7735S_FRMCTR3
    {REG_W, 1}, // B4h ST7735S_INVCTR
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},

    {REG_W, 3}, // C0h ST7735S_PWCTR1
    {REG_W, 1}, // C1h ST7735S_PWCTR2
    {REG_W, 2}, // C2h ST7735S_PWCTR3
    {REG_W, 2}, // C3h ST7735S_PWCTR4
    {REG_W, 2}, // C4h ST7735S_PWCTR5
    {REG_W, 1}, // C5h ST7735S_VMCTR1
    {REG_N, 0},
    {REG_W, 1}, // C7h ST7735S_VMOFCTR
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},

    {REG_N, 0},
    {REG_W, 1}, // D1h ST7735S_WRID2
    {REG_W, 1}, // D2h ST7735S_WRID3
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_W, 1}, // D9h ST7735S_NVFCTR1
    {REG_R, 1}, // DAh ST7735S_RDID1
    {REG_R, 1}, // DBh ST7735S_RDID2
    {REG_R, 1}, // DCh ST7735S_RDID3
    {REG_N, 0},
    {REG_W, 2}, // DEh ST7735S_NVFCTR2
    {REG_W, 2}, // DFh ST7735S_NVFCTR3

    {REG_W, 16}, // E0h ST7735S_GMCTRP1
    {REG_W, 16}, // E1h ST7735S_GMCTRN1
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},

    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_W, 1},  // FCh ST7735S_GCV
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0}
};


#endif // ST7735S_REG_ACCESS
