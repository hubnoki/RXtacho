                                                                          
                                                                           
                                                                           
                                                                           
                                                                           
                                                                           
                                                                           
                                                                           
                                                                           
                                                                           
                                                                           
                                                                           
/************************************************************************/
/*    File Version: V1.00                                               */
/*    Date Generated: 08/07/2013                                        */
/************************************************************************/

#include "interrupt_handlers.h"

typedef void (*fp) (void);
extern void PowerON_Reset (void);
extern void stack (void);

#define FVECT_SECT          __attribute__ ((section (".fvectors")))

const void *HardwareVectors[] FVECT_SECT  = {
//;0xffffff80  MDES  Endian Select Register
#ifdef __RX_LITTLE_ENDIAN__ 
(fp)0xffffffff,
#endif
#ifdef __RX_BIG_ENDIAN__ 
(fp)0xfffffff8,
#endif
//;0xffffff84  Reserved
    (fp)0,
//;0xffffff88  OFS1 Option bytes setting
    (fp)0xffffffff,
//;0xffffff8C  OFS0 Option bytes setting
    (fp)0xffffffff,
//;0xffffff90  Reserved
    (fp)0,
//;0xffffff94  Reserved
    (fp)0,
//;0xffffff98  Reserved
    (fp)0,
//;0xffffff9C  Reserved
    (fp)0,
//;0xffffffA0  Reserved
    (fp)0xffffffff,
//;0xffffffA4  Reserved
    (fp)0xffffffff,
//;0xffffffA8  Reserved
    (fp)0xffffffff,
//;0xffffffAC  Reserved
    (fp)0xffffffff,
//;0xffffffB0  Reserved
    (fp)0,
//;0xffffffB4  Reserved
    (fp)0,
//;0xffffffB8  Reserved
    (fp)0,
//;0xffffffBC  Reserved
    (fp)0,
//;0xffffffC0  Reserved
    (fp)0,
//;0xffffffC4  Reserved
    (fp)0,
//;0xffffffC8  Reserved
    (fp)0,
//;0xffffffCC  Reserved
    (fp)0,
//;0xffffffd0  Exception(Supervisor Instruction)
    INT_Excep_SuperVisorInst,
//;0xffffffd4  Reserved
    (fp)0,
//;0xffffffd8  Reserved
    (fp)0,
//;0xffffffdc  Exception(Undefined Instruction)
    INT_Excep_UndefinedInst,
//;0xffffffe0  Reserved
    (fp)0,
//;0xffffffe4  Exception(Floating Point)
    (fp)0,
//;0xffffffe8  Reserved
    (fp)0,
//;0xffffffec  Reserved
    (fp)0,
//;0xfffffff0  Reserved
    (fp)0,
//;0xfffffff4  Reserved
    (fp)0,
//;0xfffffff8  NMI
    INT_NonMaskableInterrupt,
//;0xfffffffc  RESET
//;<<VECTOR DATA START (POWER ON RESET)>>
//;Power On Reset PC
    PowerON_Reset                                                                                                                  
//;<<VECTOR DATA END (POWER ON RESET)>>
};

#define RVECT_SECT          __attribute__ ((section (".rvectors")))
const fp RelocatableVectors[] RVECT_SECT  = {
//0000h
    (fp)0,
//0004h
    (fp)0,
//0008h
    (fp)0,
//000Ch
    (fp)0,
//0010h
    (fp)0,
//0014h
    (fp)0,
//0018h
    (fp)0,
//001Ch
    (fp)0,
//0020h
    (fp)0,
//0024h
    (fp)0,
//0028h
    (fp)0,
//002Ch
    (fp)0,
//0030h
    (fp)0,
//0034h
    (fp)0,
//0038h
    (fp)0,
//003Ch
    (fp)0,
//0040h
// BSC BUSERR
 (fp)INT_Excep_BSC_BUSERR,
//0x0044  Reserved
    (fp)0,
//0x0048  Reserved
    (fp)0,
//0x004C  Reserved
    (fp)0,
//0x0050  Reserved
    (fp)0,
//0x0054 FCUERR
   (fp)INT_Excep_FCU_FIFERR,
//0x0058  Reserved
    (fp)0,
//0x005C  FRDYI
    (fp)INT_Excep_FCU_FRDYI,
//0x0060  Reserved
    (fp)0,
//;0x0064  Reserved
    (fp)0,
//;0x0068  Reserved
    (fp)0,
//;0x006C ICU SWINT
 (fp)INT_Excep_ICU_SWINT,

// CMT0 CMI0
 (fp)INT_Excep_CMT0_CMI0,

// CMT1 CMI1
 (fp)INT_Excep_CMT1_CMI1,

// CMT2 CMI2
 (fp)INT_Excep_CMT2_CMI2,

// CMT3 CMI3
 (fp)INT_Excep_CMT3_CMI3,

// CAC FERRF
 (fp)INT_Excep_CAC_FERRF,

// CAC MENDF
 (fp)INT_Excep_CAC_MENDF,

// CAC OVFF
 (fp)INT_Excep_CAC_OVFF,
//;0x008C  Reserved
    (fp)0,
//;0x0090  Reserved
    (fp)0,
//;0x0094  Reserved
    (fp)0,
//;0x0098  Reserved
    (fp)0,
//;0x009C  Reserved
    (fp)0,
//;0x00A0  Reserved
    (fp)0,
//;0x00A4  Reserved
    (fp)0,
//;0x00A8  Reserved
    (fp)0,
//;0x00AC  Reserved
    (fp)0,
    
// RSPI0 SPEI0
 (fp)INT_Excep_RSPI0_SPEI0,

 // RSPI0 SPRI0
 (fp)INT_Excep_RSPI0_SPRI0,

// RSPI0 SPTI0
 (fp)INT_Excep_RSPI0_SPTI0,

// RSPI0 SPII0
 (fp)INT_Excep_RSPI0_SPII0,
//;0x00C0  Reserved
    (fp)0,
//;0x00C4  Reserved
    (fp)0,
//;0x00C8  Reserved
    (fp)0,
//;0x00CC  Reserved
    (fp)0,
//;0x00D0  Reserved
    (fp)0,
//;0x00D4  Reserved
    (fp)0,
//;0x00D8  Reserved
    (fp)0,
//;0x00DC  Reserved
    (fp)0,
//;0x00E0  Reserved
    (fp)0,    
// DOC DOPCF
 (fp)INT_Excep_DOC_DOPCF,
//;0x00E8  Reserved
    (fp)0,
//;0x00EC  Reserved
    (fp)0,
//;0x00F0  Reserved
    (fp)0,
//;0x00F4  Reserved
    (fp)0,
//;0x00F8  Reserved
    (fp)0,
// RTC CUP
 (fp)INT_Excep_RTC_CUP,

// ICU IRQ0
 (fp)INT_Excep_ICU_IRQ0,

// ICU IRQ1
 (fp)INT_Excep_ICU_IRQ1,

// ICU IRQ2
 (fp)INT_Excep_ICU_IRQ2,

// ICU IRQ3
 (fp)INT_Excep_ICU_IRQ3,

// ICU IRQ4
 (fp)INT_Excep_ICU_IRQ4,
 
// ICU IRQ5
 (fp)INT_Excep_ICU_IRQ5,

// ICU IRQ6
 (fp)INT_Excep_ICU_IRQ6,

// ICU IRQ7
 (fp)INT_Excep_ICU_IRQ7,
//;0x0120  Reserved
    (fp)0,
//;0x0124  Reserved
    (fp)0,
//;0x0128  Reserved
    (fp)0,
//;0x012C  Reserved
    (fp)0,
//;0x0130  Reserved
    (fp)0,
//;0x0134  Reserved
    (fp)0,
//;0x0138  Reserved
    (fp)0,
//;0x013C  Reserved
    (fp)0,
//;0x0140  Reserved
    (fp)0,
//;0x0144  Reserved
    (fp)0,
//;0x0148  Reserved
    (fp)0,
//;0x014C  Reserved
    (fp)0,
//;0x0150  Reserved
    (fp)0,
//;0x0154  Reserved
    (fp)0,
//;0x0158  Reserved
    (fp)0,
//;0x015C  Reserved
    (fp)0,    
 // LVD LVD1
 (fp)INT_Excep_LVD_LVD1,
// LVD LVD2
 (fp)INT_Excep_LVD_LVD2,
 //;0x0168  Reserved
    (fp)0,
//;0x016C  Reserved
    (fp)0,
 // RTC ALM
 (fp)INT_Excep_RTC_ALM,
 
 // RTC PRD
 (fp)INT_Excep_RTC_PRD,
 
 //;0x0178  Reserved
    (fp)0,
//;0x017C  Reserved
    (fp)0,
//;0x0180  Reserved
    (fp)0,
//;0x0184  Reserved
    (fp)0,
//;0x0188  Reserved
    (fp)0,
//;0x018C  Reserved
    (fp)0,
//;0x0190  Reserved
    (fp)0,
//;0x0194  Reserved
    (fp)0,
// S12AD S12ADI0 0x198
 (fp)INT_Excep_S12AD_S12ADI0,
// S12AD GBADI
 (fp)INT_Excep_S12AD_GBADI,
//104;0x01A0  Reserved 
    (fp)0,
//105;0x01A4  Reserved 
    (fp)0,
// ELC ELSR18I
 (fp)INT_Excep_ELC_ELSR18I,
 //;0x01AC  Reserved
    (fp)0,
//;0x01B0  Reserved
    (fp)0,
//;0x01B4  Reserved
    (fp)0,
//;0x01B8  Reserved
    (fp)0,
//;0x01BC  Reserved
    (fp)0,
//;0x01C0  Reserved
    (fp)0,
//;0x01C4  Reserved
    (fp)0, 
// MTU0 TGIA0
    (fp)INT_Excep_MTU0_TGIA0,

// MTU0 TGIB0
 (fp)INT_Excep_MTU0_TGIB0,

// MTU0 TGIC0
 (fp)INT_Excep_MTU0_TGIC0,

// MTU0 TGID0
 (fp)INT_Excep_MTU0_TGID0,

// MTU0 TCIV0
 (fp)INT_Excep_MTU0_TCIV0,

// MTU0 TGIE0
 (fp)INT_Excep_MTU0_TGIE0,

// MTU0 TGIF0
 (fp)INT_Excep_MTU0_TGIF0,

// MTU1 TGIA1
 (fp)INT_Excep_MTU1_TGIA1,

// MTU1 TGIB1
 (fp)INT_Excep_MTU1_TGIB1,

// MTU1 TCIV1
 (fp)INT_Excep_MTU1_TCIV1,

// MTU1 TCIU1
 (fp)INT_Excep_MTU1_TCIU1,

// MTU2 TGIA2
 (fp)INT_Excep_MTU2_TGIA2,

// MTU2 TGIB2
 (fp)INT_Excep_MTU2_TGIB2,

// MTU2 TCIV2
 (fp)INT_Excep_MTU2_TCIV2,

// MTU2 TCIU2
 (fp)INT_Excep_MTU2_TCIU2,

// MTU3 TGIA3
 (fp)INT_Excep_MTU3_TGIA3,

// MTU3 TGIB3
 (fp)INT_Excep_MTU3_TGIB3,

// MTU3 TGIC3
 (fp)INT_Excep_MTU3_TGIC3,

// MTU3 TGID3
 (fp)INT_Excep_MTU3_TGID3,

// MTU3 TCIV3
 (fp)INT_Excep_MTU3_TCIV3,

// MTU4 TGIA4
 (fp)INT_Excep_MTU4_TGIA4,

// MTU4 TGIB4
 (fp)INT_Excep_MTU4_TGIB4,

// MTU4 TGIC4
 (fp)INT_Excep_MTU4_TGIC4,

// MTU4 TGID4
 (fp)INT_Excep_MTU4_TGID4,

// MTU4 TCIV4
 (fp)INT_Excep_MTU4_TCIV4,

// MTU5 TGIU5
 (fp)INT_Excep_MTU5_TGIU5,

// MTU5 TGIV5
 (fp)INT_Excep_MTU5_TGIV5,

// MTU5 TGIW5
 (fp)INT_Excep_MTU5_TGIW5,
//;0x0238  Reserved
    (fp)0,
//;0x023C  Reserved
    (fp)0,
//;0x0240  Reserved
    (fp)0,
//;0x0244  Reserved
    (fp)0,
//;0x0248  Reserved
    (fp)0,
//;0x024C  Reserved
    (fp)0,
//;0x0250  Reserved
    (fp)0,
//;0x0254  Reserved
    (fp)0,
//;0x0258  Reserved
    (fp)0,
//;0x025C  Reserved
    (fp)0,
//;0x0260  Reserved
    (fp)0,
//;0x0264  Reserved
    (fp)0,
//;0x0268  Reserved
    (fp)0,
//;0x026C  Reserved
    (fp)0,
//;0x0270  Reserved
    (fp)0,
//;0x0274  Reserved
    (fp)0,
//;0x0278  Reserved
    (fp)0,
//;0x027C  Reserved
    (fp)0,
//;0x0280  Reserved
    (fp)0,
//;0x0284  Reserved
    (fp)0,
//;0x0288  Reserved
    (fp)0,
//;0x028C  Reserved
    (fp)0,
//;0x0290  Reserved
    (fp)0,
//;0x0294  Reserved
    (fp)0,
//;0x0298  Reserved
    (fp)0,
//;0x029C  Reserved
    (fp)0,
//;0x02A0  Reserved
    (fp)0,
//;0x02A4  Reserved
    (fp)0,
// POE OEI1
 (fp)INT_Excep_POE_OEI1,
// POE OEI2
 (fp)INT_Excep_POE_OEI2,
 //;0x02B0  Reserved
    (fp)0,
//;0x02B4  Reserved
    (fp)0,
// TMR0 CMIA0
 (fp)INT_Excep_TMR0_CMIA0,

// TMR0 CMIB0
 (fp)INT_Excep_TMR0_CMIB0,

// TMR0 OVI0
 (fp)INT_Excep_TMR0_OVI0,

// TMR1 CMIA1
 (fp)INT_Excep_TMR1_CMIA1,

// TMR1 CMIB1
 (fp)INT_Excep_TMR1_CMIB1,

// TMR1 OVI1
 (fp)INT_Excep_TMR1_OVI1,

// TMR2 CMIA2
 (fp)INT_Excep_TMR2_CMIA2,

// TMR2 CMIB2
 (fp)INT_Excep_TMR2_CMIB2,

// TMR2 OVI2
 (fp)INT_Excep_TMR2_OVI2,

// TMR3 CMIA3
 (fp)INT_Excep_TMR3_CMIA3,

// TMR3 CMIB3
 (fp)INT_Excep_TMR3_CMIB3,

// TMR3 OVI3
 (fp)INT_Excep_TMR3_OVI3,
//;0x02E8  Reserved
    (fp)0,
//;0x02EC  Reserved
    (fp)0,
//;0x02F0  Reserved
    (fp)0,
//;0x02F4  Reserved
    (fp)0,
//;0x02F8  Reserved
    (fp)0,
//;0x02FC  Reserved
    (fp)0,
//;0x0300  Reserved
    (fp)0,
//;0x0304  Reserved
    (fp)0,
//;0x0308  Reserved
    (fp)0,
//;0x030C  Reserved
    (fp)0,
//;0x0310  Reserved
    (fp)0,
//;0x0314  Reserved
    (fp)0,
// DMAC DMAC0I
 (fp)INT_Excep_DMAC_DMAC0I,

// DMAC DMAC1I
 (fp)INT_Excep_DMAC_DMAC1I,

// DMAC DMAC2I
 (fp)INT_Excep_DMAC_DMAC2I,

// DMAC DMAC3I
 (fp)INT_Excep_DMAC_DMAC3I,
//;0x0328  Reserved
    (fp)0,
//;0x032C  Reserved
    (fp)0,
//;0x0330  Reserved
    (fp)0,
//;0x0334  Reserved
    (fp)0,
//;0x0338  Reserved
    (fp)0,
//;0x033C  Reserved
    (fp)0,
//;0x0340  Reserved
    (fp)0,
//;0x0344  Reserved
    (fp)0,
//;0x0348  Reserved
    (fp)0,
//;0x034C  Reserved
    (fp)0,
//;0x0350  Reserved
    (fp)0,
//;0x0354  Reserved
    (fp)0,

//;0x0358  Reserved
    (fp)0,
//;0x035C  Reserved
    (fp)0,
//;0x0360  Reserved
    (fp)0,
//;0x0364  Reserved
    (fp)0,
// SCI1 ERI1
 (fp)INT_Excep_SCI1_ERI1,

// SCI1 RXI1
 (fp)INT_Excep_SCI1_RXI1,

// SCI1 TXI1
 (fp)INT_Excep_SCI1_TXI1,

// SCI1 TEI1
 (fp)INT_Excep_SCI1_TEI1,

// SCI5 ERI5
 (fp)INT_Excep_SCI5_ERI5,

// SCI5 RXI5
 (fp)INT_Excep_SCI5_RXI5,

// SCI5 TXI5
 (fp)INT_Excep_SCI5_TXI5,

// SCI5 TEI5
 (fp)INT_Excep_SCI5_TEI5,

// SCI6 ERI6
 (fp)INT_Excep_SCI6_ERI6,

// SCI6 RXI6
 (fp)INT_Excep_SCI6_RXI6,

// SCI6 TXI6
 (fp)INT_Excep_SCI6_TXI6,

// SCI6 TEI6
 (fp)INT_Excep_SCI6_TEI6,
//0398h
    (fp)0,
//039Ch
    (fp)0,
//03A0h
    (fp)0,
//03A4h
    (fp)0,

// SCI9 ERI9
 (fp)INT_Excep_SCI9_ERI9,

// SCI9 RXI9
 (fp)INT_Excep_SCI9_RXI9,

// SCI9 TXI9
 (fp)INT_Excep_SCI9_TXI9,

// SCI9 TEI9
 (fp)INT_Excep_SCI9_TEI9,

// SCI12 ERI12
 (fp)INT_Excep_SCI12_ERI12,

// SCI12 RXI12
 (fp)INT_Excep_SCI12_RXI12,

// SCI12 TXI12
 (fp)INT_Excep_SCI12_TXI12,

// SCI12 TEI12
 (fp)INT_Excep_SCI12_TEI12,

// SCI12 SCIX0
 (fp)INT_Excep_SCI12_SCIX0,

// SCI12 SCIX1
 (fp)INT_Excep_SCI12_SCIX1,

// SCI12 SCIX2
 (fp)INT_Excep_SCI12_SCIX2,

// SCI12 SCIX3
 (fp)INT_Excep_SCI12_SCIX3,

// RIIC0 EEI0
 (fp)INT_Excep_RIIC0_EEI0,

// RIIC0 RXI0
 (fp)INT_Excep_RIIC0_RXI0,

// RIIC0 TXI0
 (fp)INT_Excep_RIIC0_TXI0,

// RIIC0 TEI0
 (fp)INT_Excep_RIIC0_TEI0,
//;0x03E8h  Reserved
    (fp)0,
//;0x03ECh  Reserved
    (fp)0,
//;0x03F0h  Reserved
    (fp)0,
//;0x03F4h  Reserved
    (fp)0,
//;0x03F8h  Reserved
    (fp)0,
//;0x03FCh  Reserved
    (fp)0,
};
