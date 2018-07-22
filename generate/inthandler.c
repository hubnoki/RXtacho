                                                                          
                                                                           
                                                                           
                                                                           
                                                                           
                                                                           
                                                                           
                                                                           
                                                                           
                                                                           
                                                                           
                                                                           
/************************************************************************/
/*    File Version: V1.00                                               */
/*    Date Generated: 08/07/2013                                        */
/************************************************************************/

#include "interrupt_handlers.h"
#include "hardware_lib.h"
#include "uart.h"


// Exception(Supervisor Instruction)
void INT_Excep_SuperVisorInst(void){/* brk(){  } */}

// Exception(Undefined Instruction)
void INT_Excep_UndefinedInst(void){/* brk(){  } */}

// NMI
void INT_NonMaskableInterrupt(void){/* brk(){  } */}

// Dummy
void INT_Dummy(void){/* brk(){  } */}

// BRK
void INT_Excep_BRK(void){/* wait();*/ }

// BSC BUSERR
void INT_Excep_BSC_BUSERR(void){ }

// FCU FIFERR
void INT_Excep_FCU_FIFERR(void){ }

// FCU FRDYI
void INT_Excep_FCU_FRDYI(void){ }

// ICU SWINT
void INT_Excep_ICU_SWINT(void){ }


#include "timer_soft.h"
// CMT0 CMI0
void INT_Excep_CMT0_CMI0(void)
{
	timer_soft_int();
}

// CMT1 CMI1
void INT_Excep_CMT1_CMI1(void){ }

// CMT2 CMI2
void INT_Excep_CMT2_CMI2(void){ }

// CMT3 CMI3
void INT_Excep_CMT3_CMI3(void){ }

// CAC FERRF
void INT_Excep_CAC_FERRF(void){ }

// CAC MENDF
void INT_Excep_CAC_MENDF(void){ }

// CAC OVFF
void INT_Excep_CAC_OVFF(void){ }

// RSPI0 SPEI0
void INT_Excep_RSPI0_SPEI0(void){ }

// RSPI0 SPRI0
void INT_Excep_RSPI0_SPRI0(void){ }

// RSPI0 SPTI0
void INT_Excep_RSPI0_SPTI0(void){ }

// RSPI0 SPII0
void INT_Excep_RSPI0_SPII0(void){ }

// DOC DOPCF
void INT_Excep_DOC_DOPCF(void){ }

// CMPB CMPB0
void INT_Excep_CMPB_CMPB0(void){ }

// CMPB CMPB1
void INT_Excep_CMPB_CMPB1(void){ }

// RTC CUP
void INT_Excep_RTC_CUP(void){ }

// ICU IRQ0
//void INT_Excep_ICU_IRQ0(void){ } // implemented in hardware_lib.c

// ICU IRQ1
//void INT_Excep_ICU_IRQ1(void){ } // implemented in hardware_lib.c

// ICU IRQ2
void INT_Excep_ICU_IRQ2(void){ }

// ICU IRQ3
void INT_Excep_ICU_IRQ3(void){ }

// ICU IRQ4
void INT_Excep_ICU_IRQ4(void){ }

// ICU IRQ5
void INT_Excep_ICU_IRQ5(void){ }

// ICU IRQ6
void INT_Excep_ICU_IRQ6(void){ }

// ICU IRQ7
void INT_Excep_ICU_IRQ7(void){ }

// LVD LVD1
void INT_Excep_LVD_LVD1(void){ }

// LVD LVD2
void INT_Excep_LVD_LVD2(void){ }

///##############################################
// CMPA CMPA1
void INT_Excep_CMPA_CMPA1(void){ }

// CMPA CMPA2
void INT_Excep_CMPA_CMPA2(void){ }
///##############################################

// RTC ALM
void INT_Excep_RTC_ALM(void){ }

// RTC PRD
void INT_Excep_RTC_PRD(void)
{
//	uart_puts("RTC interrupt\r\n");
	LCD_LED ^= 1;
}

// S12AD S12ADI0
void INT_Excep_S12AD_S12ADI0(void){ }

// S12AD GBADI
void INT_Excep_S12AD_GBADI(void){ }

// ELC ELSR18I
void INT_Excep_ELC_ELSR18I(void){ }

// ELC ELSR19I
//void INT_Excep_ELC_ELSR19I(void){ }

// MTU0 TGIA0
void INT_Excep_MTU0_TGIA0(void){ }

// MTU0 TGIB0
void INT_Excep_MTU0_TGIB0(void){ }

// MTU0 TGIC0
void INT_Excep_MTU0_TGIC0(void){ }

// MTU0 TGID0
void INT_Excep_MTU0_TGID0(void){ }

// MTU0 TCIV0
void INT_Excep_MTU0_TCIV0(void){ }

// MTU0 TGIE0
void INT_Excep_MTU0_TGIE0(void){ }

// MTU0 TGIF0
void INT_Excep_MTU0_TGIF0(void){ }

// MTU1 TGIA1
void INT_Excep_MTU1_TGIA1(void){ }

// MTU1 TGIB1
void INT_Excep_MTU1_TGIB1(void){ }

// MTU1 TCIV1
void INT_Excep_MTU1_TCIV1(void){ }

// MTU1 TCIU1
void INT_Excep_MTU1_TCIU1(void){ }

// MTU2 TGIA2
void INT_Excep_MTU2_TGIA2(void){ }

// MTU2 TGIB2
void INT_Excep_MTU2_TGIB2(void){ }

// MTU2 TCIV2
void INT_Excep_MTU2_TCIV2(void){ }

// MTU2 TCIU2
void INT_Excep_MTU2_TCIU2(void){ }

// MTU3 TGIA3
void INT_Excep_MTU3_TGIA3(void){ }

// MTU3 TGIB3
void INT_Excep_MTU3_TGIB3(void){ }

// MTU3 TGIC3
void INT_Excep_MTU3_TGIC3(void){ }

// MTU3 TGID3
void INT_Excep_MTU3_TGID3(void){ }

// MTU3 TCIV3
void INT_Excep_MTU3_TCIV3(void){ }

// MTU4 TGIA4
void INT_Excep_MTU4_TGIA4(void){ }

// MTU4 TGIB4
void INT_Excep_MTU4_TGIB4(void){ }

// MTU4 TGIC4
void INT_Excep_MTU4_TGIC4(void){ }

// MTU4 TGID4
void INT_Excep_MTU4_TGID4(void){ }

// MTU4 TCIV4
void INT_Excep_MTU4_TCIV4(void){ }

// MTU5 TGIU5
void INT_Excep_MTU5_TGIU5(void){ }

// MTU5 TGIV5
void INT_Excep_MTU5_TGIV5(void){ }

// MTU5 TGIW5
void INT_Excep_MTU5_TGIW5(void){ }

// POE OEI1
void INT_Excep_POE_OEI1(void){ }

// POE OEI2
void INT_Excep_POE_OEI2(void){ }

// TMR0 CMIA0
void INT_Excep_TMR0_CMIA0(void){ }

// TMR0 CMIB0
void INT_Excep_TMR0_CMIB0(void){ }

// TMR0 OVI0
void INT_Excep_TMR0_OVI0(void){ }

// TMR1 CMIA1
void INT_Excep_TMR1_CMIA1(void){ }

// TMR1 CMIB1
void INT_Excep_TMR1_CMIB1(void){ }

// TMR1 OVI1
void INT_Excep_TMR1_OVI1(void){ }

// TMR2 CMIA2
void INT_Excep_TMR2_CMIA2(void){ }

// TMR2 CMIB2
void INT_Excep_TMR2_CMIB2(void){ }

// TMR2 OVI2
void INT_Excep_TMR2_OVI2(void){ }

// TMR3 CMIA3
void INT_Excep_TMR3_CMIA3(void){ }

// TMR3 CMIB3
void INT_Excep_TMR3_CMIB3(void){ }

// TMR3 OVI3
void INT_Excep_TMR3_OVI3(void){ }

// DMAC DMAC0I
void INT_Excep_DMAC_DMAC0I(void){ }

// DMAC DMAC1I
void INT_Excep_DMAC_DMAC1I(void){ }

// DMAC DMAC2I
void INT_Excep_DMAC_DMAC2I(void){ }

// DMAC DMAC3I
void INT_Excep_DMAC_DMAC3I(void){ }

// SCI0 ERI0
void INT_Excep_SCI0_ERI0(void){ }

// SCI0 RXI0
void INT_Excep_SCI0_RXI0(void){ }

// SCI0 TXI0
void INT_Excep_SCI0_TXI0(void){ }

// SCI0 TEI0
void INT_Excep_SCI0_TEI0(void){ }

// SCI1 ERI1
void INT_Excep_SCI1_ERI1(void){ }

// SCI1 RXI1
void INT_Excep_SCI1_RXI1(void)
{
	uart_rx_int();
}

// SCI1 TXI1
void INT_Excep_SCI1_TXI1(void){ }

// SCI1 TEI1
void INT_Excep_SCI1_TEI1(void){ }

// SCI5 ERI5
void INT_Excep_SCI5_ERI5(void){ }

// SCI5 RXI5
void INT_Excep_SCI5_RXI5(void){ }

// SCI5 TXI5
void INT_Excep_SCI5_TXI5(void){ }

// SCI5 TEI5
void INT_Excep_SCI5_TEI5(void){ }

// SCI6 ERI6
void INT_Excep_SCI6_ERI6(void){ }

// SCI6 RXI6
void INT_Excep_SCI6_RXI6(void){ }

// SCI6 TXI6
void INT_Excep_SCI6_TXI6(void){ }

// SCI6 TEI6
void INT_Excep_SCI6_TEI6(void){ }

// SCI8 ERI8
void INT_Excep_SCI8_ERI8(void){ }

// SCI8 RXI8
void INT_Excep_SCI8_RXI8(void){ }

// SCI8 TXI8
void INT_Excep_SCI8_TXI8(void){ }

// SCI8 TEI8
void INT_Excep_SCI8_TEI8(void){ }

// SCI9 ERI9
void INT_Excep_SCI9_ERI9(void){ }

// SCI9 RXI9
void INT_Excep_SCI9_RXI9(void){ }

// SCI9 TXI9
void INT_Excep_SCI9_TXI9(void){ }

// SCI9 TEI9
void INT_Excep_SCI9_TEI9(void){ }

// SCI12 ERI12
void INT_Excep_SCI12_ERI12(void){ }

// SCI12 RXI12
void INT_Excep_SCI12_RXI12(void){ }

// SCI12 TXI12
void INT_Excep_SCI12_TXI12(void){ }

// SCI12 TEI12
void INT_Excep_SCI12_TEI12(void){ }

// SCI12 SCIX0
void INT_Excep_SCI12_SCIX0(void){ }

// SCI12 SCIX1
void INT_Excep_SCI12_SCIX1(void){ }

// SCI12 SCIX2
void INT_Excep_SCI12_SCIX2(void){ }

// SCI12 SCIX3
void INT_Excep_SCI12_SCIX3(void){ }

// RIIC0 EEI0
void INT_Excep_RIIC0_EEI0(void){ }

// RIIC0 RXI0
void INT_Excep_RIIC0_RXI0(void){ }

// RIIC0 TXI0
void INT_Excep_RIIC0_TXI0(void){ }

// RIIC0 TEI0
void INT_Excep_RIIC0_TEI0(void){ }

