                                                             
                                                                          
                                                                           
                                                                           
                                                                           
                                                                           
                                                                           
                                                                           
                                                                           
                                                                           
                                                                           
                                                                           
/************************************************************************/
/*    File Version: V1.00                                               */
/*    Date Generated: 08/07/2013                                        */
/************************************************************************/

#ifndef INTERRUPT_HANDLERS_H
#define INTERRUPT_HANDLERS_H

// Exception(Supervisor Instruction)
void INT_Excep_SuperVisorInst(void) __attribute__ ((interrupt));

// Exception(Undefined Instruction)
void INT_Excep_UndefinedInst(void) __attribute__ ((interrupt));

// NMI
void INT_NonMaskableInterrupt(void) __attribute__ ((interrupt));

// Dummy
void Dummy(void) __attribute__ ((interrupt));

// BRK
void INT_Excep_BRK(void) __attribute__ ((interrupt));

// BSC BUSERR
void INT_Excep_BSC_BUSERR(void) __attribute__ ((interrupt));


// FCU FIFERR
void INT_Excep_FCU_FIFERR(void) __attribute__ ((interrupt));

// FCU FRDYI
void INT_Excep_FCU_FRDYI(void) __attribute__ ((interrupt));

// ICU SWINT
void INT_Excep_ICU_SWINT(void) __attribute__ ((interrupt));

// CMT0 CMI0
void INT_Excep_CMT0_CMI0(void) __attribute__ ((interrupt));

// CMT1 CMI1
void INT_Excep_CMT1_CMI1(void) __attribute__ ((interrupt));

// CMT2 CMI2
void INT_Excep_CMT2_CMI2(void) __attribute__ ((interrupt));

// CMT3 CMI3
void INT_Excep_CMT3_CMI3(void) __attribute__ ((interrupt));

// CAC FERRF
void INT_Excep_CAC_FERRF(void) __attribute__ ((interrupt));

// CAC MENDF
void INT_Excep_CAC_MENDF(void) __attribute__ ((interrupt));

// CAC OVFF
void INT_Excep_CAC_OVFF(void) __attribute__ ((interrupt));

// RSPI0 SPEI0
void INT_Excep_RSPI0_SPEI0(void) __attribute__ ((interrupt));

// RSPI0 SPRI0
void INT_Excep_RSPI0_SPRI0(void) __attribute__ ((interrupt));

// RSPI0 SPTI0
void INT_Excep_RSPI0_SPTI0(void) __attribute__ ((interrupt));

// RSPI0 SPII0
void INT_Excep_RSPI0_SPII0(void) __attribute__ ((interrupt));

// DOC DOPCF
void INT_Excep_DOC_DOPCF(void) __attribute__ ((interrupt));

// CMPB CMPB0
void INT_Excep_CMPB_CMPB0(void) __attribute__ ((interrupt));

// CMPB CMPB1
void INT_Excep_CMPB_CMPB1(void) __attribute__ ((interrupt));

// RTC CUP
void INT_Excep_RTC_CUP(void) __attribute__ ((interrupt));

// ICU IRQ0
void INT_Excep_ICU_IRQ0(void) __attribute__ ((interrupt));

// ICU IRQ1
void INT_Excep_ICU_IRQ1(void) __attribute__ ((interrupt));

// ICU IRQ2
void INT_Excep_ICU_IRQ2(void) __attribute__ ((interrupt));

// ICU IRQ3
void INT_Excep_ICU_IRQ3(void) __attribute__ ((interrupt));

// ICU IRQ4
void INT_Excep_ICU_IRQ4(void) __attribute__ ((interrupt));

// ICU IRQ5
void INT_Excep_ICU_IRQ5(void) __attribute__ ((interrupt));

// ICU IRQ6
void INT_Excep_ICU_IRQ6(void) __attribute__ ((interrupt));

// ICU IRQ7
void INT_Excep_ICU_IRQ7(void) __attribute__ ((interrupt));

// LVD LVD1
void INT_Excep_LVD_LVD1(void) __attribute__ ((interrupt));

// LVD LVD2
void INT_Excep_LVD_LVD2(void) __attribute__ ((interrupt));

///##############################################
// CMPA CMPA1
void INT_Excep_CMPA_CMPA1(void) __attribute__ ((interrupt));

// CMPA CMPA2
void INT_Excep_CMPA_CMPA2(void) __attribute__ ((interrupt));
///##############################################

// RTC ALM
void INT_Excep_RTC_ALM(void) __attribute__ ((interrupt));

// RTC PRD
void INT_Excep_RTC_PRD(void) __attribute__ ((interrupt));

// S12AD S12ADI0
void INT_Excep_S12AD_S12ADI0(void) __attribute__ ((interrupt));

// S12AD GBADI
void INT_Excep_S12AD_GBADI(void) __attribute__ ((interrupt));

// ELC ELSR18I
void INT_Excep_ELC_ELSR18I(void) __attribute__ ((interrupt));

// ELC ELSR19I
//void INT_Excep_ELC_ELSR19I(void) __attribute__ ((interrupt));

// MTU0 TGIA0
void INT_Excep_MTU0_TGIA0(void) __attribute__ ((interrupt));

// MTU0 TGIB0
void INT_Excep_MTU0_TGIB0(void) __attribute__ ((interrupt));

// MTU0 TGIC0
void INT_Excep_MTU0_TGIC0(void) __attribute__ ((interrupt));

// MTU0 TGID0
void INT_Excep_MTU0_TGID0(void) __attribute__ ((interrupt));

// MTU0 TCIV0
void INT_Excep_MTU0_TCIV0(void) __attribute__ ((interrupt));

// MTU0 TGIE0
void INT_Excep_MTU0_TGIE0(void) __attribute__ ((interrupt));

// MTU0 TGIF0
void INT_Excep_MTU0_TGIF0(void) __attribute__ ((interrupt));

// MTU1 TGIA1
void INT_Excep_MTU1_TGIA1(void) __attribute__ ((interrupt));

// MTU1 TGIB1
void INT_Excep_MTU1_TGIB1(void) __attribute__ ((interrupt));

// MTU1 TCIV1
void INT_Excep_MTU1_TCIV1(void) __attribute__ ((interrupt));

// MTU1 TCIU1
void INT_Excep_MTU1_TCIU1(void) __attribute__ ((interrupt));

// MTU2 TGIA2
void INT_Excep_MTU2_TGIA2(void) __attribute__ ((interrupt));

// MTU2 TGIB2
void INT_Excep_MTU2_TGIB2(void) __attribute__ ((interrupt));

// MTU2 TCIV2
void INT_Excep_MTU2_TCIV2(void) __attribute__ ((interrupt));

// MTU2 TCIU2
void INT_Excep_MTU2_TCIU2(void) __attribute__ ((interrupt));

// MTU3 TGIA3
void INT_Excep_MTU3_TGIA3(void) __attribute__ ((interrupt));

// MTU3 TGIB3
void INT_Excep_MTU3_TGIB3(void) __attribute__ ((interrupt));

// MTU3 TGIC3
void INT_Excep_MTU3_TGIC3(void) __attribute__ ((interrupt));

// MTU3 TGID3
void INT_Excep_MTU3_TGID3(void) __attribute__ ((interrupt));

// MTU3 TCIV3
void INT_Excep_MTU3_TCIV3(void) __attribute__ ((interrupt));

// MTU4 TGIA4
void INT_Excep_MTU4_TGIA4(void) __attribute__ ((interrupt));

// MTU4 TGIB4
void INT_Excep_MTU4_TGIB4(void) __attribute__ ((interrupt));

// MTU4 TGIC4
void INT_Excep_MTU4_TGIC4(void) __attribute__ ((interrupt));

// MTU4 TGID4
void INT_Excep_MTU4_TGID4(void) __attribute__ ((interrupt));

// MTU4 TCIV4
void INT_Excep_MTU4_TCIV4(void) __attribute__ ((interrupt));

// MTU5 TGIU5
void INT_Excep_MTU5_TGIU5(void) __attribute__ ((interrupt));

// MTU5 TGIV5
void INT_Excep_MTU5_TGIV5(void) __attribute__ ((interrupt));

// MTU5 TGIW5
void INT_Excep_MTU5_TGIW5(void) __attribute__ ((interrupt));

// POE OEI1
void INT_Excep_POE_OEI1(void) __attribute__ ((interrupt));

// POE OEI2
void INT_Excep_POE_OEI2(void) __attribute__ ((interrupt));

// TMR0 CMIA0
void INT_Excep_TMR0_CMIA0(void) __attribute__ ((interrupt));

// TMR0 CMIB0
void INT_Excep_TMR0_CMIB0(void) __attribute__ ((interrupt));

// TMR0 OVI0
void INT_Excep_TMR0_OVI0(void) __attribute__ ((interrupt));

// TMR1 CMIA1
void INT_Excep_TMR1_CMIA1(void) __attribute__ ((interrupt));

// TMR1 CMIB1
void INT_Excep_TMR1_CMIB1(void) __attribute__ ((interrupt));

// TMR1 OVI1
void INT_Excep_TMR1_OVI1(void) __attribute__ ((interrupt));

// TMR2 CMIA2
void INT_Excep_TMR2_CMIA2(void) __attribute__ ((interrupt));

// TMR2 CMIB2
void INT_Excep_TMR2_CMIB2(void) __attribute__ ((interrupt));

// TMR2 OVI2
void INT_Excep_TMR2_OVI2(void) __attribute__ ((interrupt));

// TMR3 CMIA3
void INT_Excep_TMR3_CMIA3(void) __attribute__ ((interrupt));

// TMR3 CMIB3
void INT_Excep_TMR3_CMIB3(void) __attribute__ ((interrupt));

// TMR3 OVI3
void INT_Excep_TMR3_OVI3(void) __attribute__ ((interrupt));

// DMAC DMAC0I
void INT_Excep_DMAC_DMAC0I(void) __attribute__ ((interrupt));

// DMAC DMAC1I
void INT_Excep_DMAC_DMAC1I(void) __attribute__ ((interrupt));

// DMAC DMAC2I
void INT_Excep_DMAC_DMAC2I(void) __attribute__ ((interrupt));

// DMAC DMAC3I
void INT_Excep_DMAC_DMAC3I(void) __attribute__ ((interrupt));

// SCI0 ERI0
void INT_Excep_SCI0_ERI0(void) __attribute__ ((interrupt));

// SCI0 RXI0
void INT_Excep_SCI0_RXI0(void) __attribute__ ((interrupt));

// SCI0 TXI0
void INT_Excep_SCI0_TXI0(void) __attribute__ ((interrupt));

// SCI0 TEI0
void INT_Excep_SCI0_TEI0(void) __attribute__ ((interrupt));

// SCI1 ERI1
void INT_Excep_SCI1_ERI1(void) __attribute__ ((interrupt));

// SCI1 RXI1
void INT_Excep_SCI1_RXI1(void) __attribute__ ((interrupt));

// SCI1 TXI1
void INT_Excep_SCI1_TXI1(void) __attribute__ ((interrupt));

// SCI1 TEI1
void INT_Excep_SCI1_TEI1(void) __attribute__ ((interrupt));

// SCI5 ERI5
void INT_Excep_SCI5_ERI5(void) __attribute__ ((interrupt));

// SCI5 RXI5
void INT_Excep_SCI5_RXI5(void) __attribute__ ((interrupt));

// SCI5 TXI5
void INT_Excep_SCI5_TXI5(void) __attribute__ ((interrupt));

// SCI5 TEI5
void INT_Excep_SCI5_TEI5(void) __attribute__ ((interrupt));

// SCI6 ERI6
void INT_Excep_SCI6_ERI6(void) __attribute__ ((interrupt));

// SCI6 RXI6
void INT_Excep_SCI6_RXI6(void) __attribute__ ((interrupt));

// SCI6 TXI6
void INT_Excep_SCI6_TXI6(void) __attribute__ ((interrupt));

// SCI6 TEI6
void INT_Excep_SCI6_TEI6(void) __attribute__ ((interrupt));

// SCI8 ERI8
void INT_Excep_SCI8_ERI8(void) __attribute__ ((interrupt));

// SCI8 RXI8
void INT_Excep_SCI8_RXI8(void) __attribute__ ((interrupt));

// SCI8 TXI8
void INT_Excep_SCI8_TXI8(void) __attribute__ ((interrupt));

// SCI8 TEI8
void INT_Excep_SCI8_TEI8(void) __attribute__ ((interrupt));

// SCI9 ERI9
void INT_Excep_SCI9_ERI9(void) __attribute__ ((interrupt));

// SCI9 RXI9
void INT_Excep_SCI9_RXI9(void) __attribute__ ((interrupt));

// SCI9 TXI9
void INT_Excep_SCI9_TXI9(void) __attribute__ ((interrupt));

// SCI9 TEI9
void INT_Excep_SCI9_TEI9(void) __attribute__ ((interrupt));

// SCI12 ERI12
void INT_Excep_SCI12_ERI12(void) __attribute__ ((interrupt));

// SCI12 RXI12
void INT_Excep_SCI12_RXI12(void) __attribute__ ((interrupt));

// SCI12 TXI12
void INT_Excep_SCI12_TXI12(void) __attribute__ ((interrupt));

// SCI12 TEI12
void INT_Excep_SCI12_TEI12(void) __attribute__ ((interrupt));

// SCI12 SCIX0
void INT_Excep_SCI12_SCIX0(void) __attribute__ ((interrupt));

// SCI12 SCIX1
void INT_Excep_SCI12_SCIX1(void) __attribute__ ((interrupt));

// SCI12 SCIX2
void INT_Excep_SCI12_SCIX2(void) __attribute__ ((interrupt));

// SCI12 SCIX3
void INT_Excep_SCI12_SCIX3(void) __attribute__ ((interrupt));

// RIIC0 EEI0
void INT_Excep_RIIC0_EEI0(void) __attribute__ ((interrupt));

// RIIC0 RXI0
void INT_Excep_RIIC0_RXI0(void) __attribute__ ((interrupt));

// RIIC0 TXI0
void INT_Excep_RIIC0_TXI0(void) __attribute__ ((interrupt));

// RIIC0 TEI0
void INT_Excep_RIIC0_TEI0(void) __attribute__ ((interrupt));

#endif
