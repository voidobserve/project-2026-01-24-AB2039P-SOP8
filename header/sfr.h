#ifndef _MATE_SFR_
#define _MATE_SFR_


#ifndef __ASSEMBLER__
#define SFR_RO *(volatile unsigned long const *)
#define SFR_WO *(volatile unsigned long*)
#define SFR_RW *(volatile unsigned long*)
#define LPSFR_RO *(volatile unsigned long const *)
#define LPSFR_WO *(volatile unsigned long*)
#define LPSFR_RW *(volatile unsigned long*)
#define RTCSFR_RO *(volatile unsigned long const *)
#define RTCSFR_WO *(volatile unsigned long*)
#define RTCSFR_RW *(volatile unsigned long*)
#define SWINT()      asm(".long 0xb0030057")
#define EEBREAKINT() asm(".long 0xb0040057")
#else
#define SFR_RO
#define SFR_WO
#define SFR_RW
#define SWINT      .long 0xb0030057
#define EEBREAKINT .long 0xb0040057
#endif

#define SFR_BASE          0x00000100    // address 0~255 is reserved
#define SFR0_BASE         (SFR_BASE + 0x000)
#define SFR1_BASE         (SFR_BASE + 0x100)
#define SFR2_BASE         (SFR_BASE + 0x200)
#define SFR3_BASE         (SFR_BASE + 0x300)
#define SFR4_BASE         (SFR_BASE + 0x400)
#define SFR5_BASE         (SFR_BASE + 0x500)
#define SFR6_BASE         (SFR_BASE + 0x600)
#define SFR7_BASE         (SFR_BASE + 0x700)
#define SFR8_BASE         (SFR_BASE + 0x800)
#define SFR9_BASE         (SFR_BASE + 0x900)
#define SFR10_BASE        (SFR_BASE + 0xa00)
#define SFR11_BASE        (SFR_BASE + 0xb00)
#define SFR12_BASE        (SFR_BASE + 0xc00)
#define SFR13_BASE        (SFR_BASE + 0xd00)
#define SFR14_BASE        (SFR_BASE + 0xe00)
#define SFR15_BASE        (SFR_BASE + 0xf00)

//------------------------- SFR Group0 ---------------------------------------//
#define TICK0CON          SFR_RW (SFR0_BASE + 0x01*4)
#define TICK0CPND         SFR_RW (SFR0_BASE + 0x02*4)
#define TICK0CNT          SFR_RW (SFR0_BASE + 0x03*4)
#define TICK0PR           SFR_RW (SFR0_BASE + 0x04*4)
#define TICK1CON          SFR_RW (SFR0_BASE + 0x05*4)
#define TICK1CPND         SFR_RW (SFR0_BASE + 0x06*4)

#define CPDATA            SFR_RW (SFR0_BASE + 0x0c*4)
#define SPMODE            SFR_RW (SFR0_BASE + 0x0d*4)
#define DEVICEID          SFR_RW (SFR0_BASE + 0x0e*4)
#define VERSIONID         SFR_RW (SFR0_BASE + 0x0f*4)

#define UART0CON          SFR_RW (SFR0_BASE + 0x10*4)
#define UART0CPND         SFR_RW (SFR0_BASE + 0x11*4)
#define UART0BAUD         SFR_RW (SFR0_BASE + 0x12*4)
#define UART0DATA         SFR_RW (SFR0_BASE + 0x13*4)
#define TMR0CON           SFR_RW (SFR0_BASE + 0x14*4)
#define TMR0CPND          SFR_RW (SFR0_BASE + 0x15*4)
#define TMR0CNT           SFR_RW (SFR0_BASE + 0x16*4)
#define TMR0PR            SFR_RW (SFR0_BASE + 0x17*4)
#define CRSTPND           SFR_RW (SFR0_BASE + 0x18*4)

#define WDTCON            SFR_RW (SFR0_BASE + 0x1a*4)
#define RTCCON            SFR_RW (SFR0_BASE + 0x1b*4)
#define VBRSTCON          SFR_RW (SFR0_BASE + 0x1c*4)

#define RTCCPND           SFR_WO (SFR0_BASE + 0x1e*4)

#define SPI0CON           SFR_RW (SFR0_BASE + 0x2a*4)
#define SPI0BUF           SFR_RW (SFR0_BASE + 0x2b*4)
#define SPI0BAUD          SFR_RW (SFR0_BASE + 0x2c*4)
#define SPI0CPND          SFR_RW (SFR0_BASE + 0x2d*4)
#define SPI0DMACNT        SFR_RW (SFR0_BASE + 0x2e*4)
#define SPI0DMAADR        SFR_RW (SFR0_BASE + 0x2f*4)


#define TMR1CON           SFR_RW (SFR0_BASE + 0x35*4)
#define TMR1CPND          SFR_RW (SFR0_BASE + 0x36*4)
#define TMR1CNT           SFR_RW (SFR0_BASE + 0x37*4)
#define TMR1PR            SFR_RW (SFR0_BASE + 0x38*4)

#define TMR2CON           SFR_RW (SFR0_BASE + 0x3a*4)
#define TMR2CPND          SFR_RW (SFR0_BASE + 0x3b*4)
#define TMR2CNT           SFR_RW (SFR0_BASE + 0x3c*4)
#define TMR2PR            SFR_RW (SFR0_BASE + 0x3d*4)
#define TMR2CPT           SFR_RO (SFR0_BASE + 0x3e*4)

//------------------------- SFR Group1 ---------------------------------------//
#define CLKCON0           SFR_RW (SFR1_BASE + 0x00*4)
#define CLKCON1           SFR_RW (SFR1_BASE + 0x01*4)
#define CLKCON2           SFR_RW (SFR1_BASE + 0x02*4)
#define CLKCON3           SFR_RW (SFR1_BASE + 0x03*4)
#define CLKCON4           SFR_RW (SFR1_BASE + 0x04*4)
#define CLKDIVCON0        SFR_RW (SFR1_BASE + 0x05*4)
#define CLKDIVCON1        SFR_RW (SFR1_BASE + 0x06*4)
#define CLKDIVCON2        SFR_RW (SFR1_BASE + 0x07*4)

#define CLKGAT0           SFR_RW (SFR1_BASE + 0x0a*4)
#define CLKGAT1           SFR_RW (SFR1_BASE + 0x0b*4)
#define CLKGAT2           SFR_RW (SFR1_BASE + 0x0c*4)


#define PLL0CON           SFR_RW (SFR1_BASE + 0x20*4)
#define PLL0CON1          SFR_RW (SFR1_BASE + 0x21*4)
#define PLL0DIV           SFR_RW (SFR1_BASE + 0x22*4)

#define XOSCCON           SFR_RW (SFR1_BASE + 0x2f*4)

#define RSTCON0           SFR_RW (SFR1_BASE + 0x30*4)
#define LVDCON            SFR_RW (SFR1_BASE + 0x31*4)
#define PWRCON0           SFR_RW (SFR1_BASE + 0x32*4)
#define PWRCON1           SFR_RW (SFR1_BASE + 0x33*4)
#define PWRCON2           SFR_RW (SFR1_BASE + 0x34*4)
#define LPMCON            SFR_RW (SFR1_BASE + 0x35*4)

#define MEMCON            SFR_RW (SFR1_BASE + 0x3a*4)
#define MEMCON1           SFR_RW (SFR1_BASE + 0x3b*4)
#define MEMCON2           SFR_RW (SFR1_BASE + 0x3c*4)

#define PROTCON0          SFR_RW (SFR1_BASE + 0x3e*4)
#define PROTCON1          SFR_RW (SFR1_BASE + 0x3f*4)

//------------------------- SFR Group2 ---------------------------------------//
#define UFADDR          SFR_RW (SFR2_BASE + 0x00*4)
#define UPOWER          SFR_RW (SFR2_BASE + 0x01*4)
#define UINTRTX1        SFR_RW (SFR2_BASE + 0x02*4)
#define UINTRTX2        SFR_RW (SFR2_BASE + 0x03*4)
#define UINTRRX1        SFR_RW (SFR2_BASE + 0x04*4)
#define UINTRRX2        SFR_RW (SFR2_BASE + 0x05*4)
#define UINTRUSB        SFR_RW (SFR2_BASE + 0x06*4)
#define UINTRTX1E       SFR_RW (SFR2_BASE + 0x07*4)
#define UINTRTX2E       SFR_RW (SFR2_BASE + 0x08*4)
#define UINTRRX1E       SFR_RW (SFR2_BASE + 0x09*4)
#define UINTRRX2E       SFR_RW (SFR2_BASE + 0x0a*4)
#define UINTRUSBE       SFR_RW (SFR2_BASE + 0x0b*4)
#define UFRAME1         SFR_RW (SFR2_BASE + 0x0c*4)
#define UFRAME2         SFR_RW (SFR2_BASE + 0x0d*4)
#define UINDEX          SFR_RW (SFR2_BASE + 0x0e*4)
#define UDEVCTL         SFR_RW (SFR2_BASE + 0x0f*4)

#define UTXMAXP         SFR_RW (SFR2_BASE + 0x10*4)
#define UCSR0           SFR_RW (SFR2_BASE + 0x11*4)
#define UTXCSR1         SFR_RW (SFR2_BASE + 0x11*4)
#define UTXCSR2         SFR_RW (SFR2_BASE + 0x12*4)
#define URXMAXP         SFR_RW (SFR2_BASE + 0x13*4)
#define URXCSR1         SFR_RW (SFR2_BASE + 0x14*4)
#define URXCSR2         SFR_RW (SFR2_BASE + 0x15*4)
#define UCOUNT0         SFR_RW (SFR2_BASE + 0x16*4)
#define URXCOUNT1       SFR_RW (SFR2_BASE + 0x16*4)
#define URXCOUNT2       SFR_RW (SFR2_BASE + 0x17*4)
#define UTXTYPE         SFR_RW (SFR2_BASE + 0x18*4)
#define UTXINTERVAL     SFR_RW (SFR2_BASE + 0x19*4)
#define URXTYPE         SFR_RW (SFR2_BASE + 0x1a*4)
#define URXINTERVAL     SFR_RW (SFR2_BASE + 0x1b*4)

#define UFIFO0          SFR_RW (SFR2_BASE + 0x20*4)
#define UFIFO1          SFR_RW (SFR2_BASE + 0x21*4)
#define UFIFO2          SFR_RW (SFR2_BASE + 0x22*4)
#define UFIFO3          SFR_RW (SFR2_BASE + 0x23*4)
#define UFIFO4          SFR_RW (SFR2_BASE + 0x24*4)
#define UFIFO5          SFR_RW (SFR2_BASE + 0x25*4)
#define UFIFO6          SFR_RW (SFR2_BASE + 0x26*4)
#define UFIFO7          SFR_RW (SFR2_BASE + 0x27*4)
#define UFIFO8          SFR_RW (SFR2_BASE + 0x28*4)
#define UFIFO9          SFR_RW (SFR2_BASE + 0x29*4)
#define UFIFO10         SFR_RW (SFR2_BASE + 0x2a*4)
#define UFIFO11         SFR_RW (SFR2_BASE + 0x2b*4)
#define UFIFO12         SFR_RW (SFR2_BASE + 0x2c*4)
#define UFIFO13         SFR_RW (SFR2_BASE + 0x2d*4)
#define UFIFO14         SFR_RW (SFR2_BASE + 0x2e*4)
#define UFIFO15         SFR_RW (SFR2_BASE + 0x2f*4)

//------------------------- SFR Group3 ---------------------------------------//
#define USBCON0         SFR_RW (SFR3_BASE + 0x00*4)
#define USBCON1         SFR_RW (SFR3_BASE + 0x01*4)
#define USBCON2         SFR_RW (SFR3_BASE + 0x02*4)
#define USBCON3         SFR_RW (SFR3_BASE + 0x03*4)

#define USBEP0ADR       SFR_RW (SFR3_BASE + 0x05*4)
#define USBEP1RXADR     SFR_RW (SFR3_BASE + 0x06*4)
#define USBEP1TXADR     SFR_RW (SFR3_BASE + 0x07*4)
#define USBEP2RXADR     SFR_RW (SFR3_BASE + 0x08*4)
#define USBEP2TXADR     SFR_RW (SFR3_BASE + 0x09*4)
#define USBEP3RXADR     SFR_RW (SFR3_BASE + 0x0a*4)
#define USBEP3TXADR     SFR_RW (SFR3_BASE + 0x0b*4)
#define BTPHYTSCON      SFR_RW (SFR3_BASE + 0x0c*4)

#define DBGCON1         SFR_RW (SFR3_BASE + 0x0e*4)
#define DBGCON          SFR_RW (SFR3_BASE + 0x0f*4)

#define CRCDAT          SFR_RW (SFR3_BASE + 0x10*4)
#define CRCRES          SFR_RW (SFR3_BASE + 0x11*4)
#define LFSRRES         SFR_RW (SFR3_BASE + 0x12*4)
#define TESTDATA                LFSRRES
#define LFCRCCON        SFR_RW (SFR3_BASE + 0x13*4)
#define BTDMAADR        SFR_RW (SFR3_BASE + 0x14*4)

#define BTRFDMACON      SFR_RW (SFR3_BASE + 0x18*4)
#define BTADDMACNT      SFR_RW (SFR3_BASE + 0x19*4)
#define BTADDMAADR      SFR_RW (SFR3_BASE + 0x1a*4)
#define BTDADMACNT      SFR_RW (SFR3_BASE + 0x1b*4)
#define BTDADMAADR      SFR_RW (SFR3_BASE + 0x1c*4)


#define CRC1DAT         SFR_RW (SFR3_BASE + 0x20*4)
#define CRC1RES         SFR_RW (SFR3_BASE + 0x21*4)

#define DCODETCON         SFR_RW (SFR3_BASE + 0x29*4)
#define DCODETCNT         SFR_RW (SFR3_BASE + 0x2a*4)
#define DCODETTGT         SFR_RW (SFR3_BASE + 0x2b*4)
#define DCODETCON1        SFR_RW (SFR3_BASE + 0x2c*4)
#define DCOTMRPR          SFR_RW (SFR3_BASE + 0x2d*4)
#define DCODETCPND        SFR_RW (SFR3_BASE + 0x2e*4)
#define DCOCON            SFR_RW (SFR3_BASE + 0x2f*4)

#define HSUT0CON        SFR_RW (SFR3_BASE + 0x30*4)
#define HSUT0CPND       SFR_RW (SFR3_BASE + 0x31*4)
#define HSUT0BAUD       SFR_RW (SFR3_BASE + 0x32*4)
#define HSUT0DATA       SFR_RW (SFR3_BASE + 0x33*4)
#define HSUT0TXCNT      SFR_RW (SFR3_BASE + 0x34*4)
#define HSUT0TXADR      SFR_RW (SFR3_BASE + 0x35*4)
#define HSUT0RXCNT      SFR_RW (SFR3_BASE + 0x36*4)
#define BTCON3          SFR_RW (SFR3_BASE + 0x37*4)
#define BTCON4          SFR_RW (SFR3_BASE + 0x38*4)
#define HSUT0RXADR      SFR_RW (SFR3_BASE + 0x39*4)
#define HSUT0FIFOCNT    SFR_RW (SFR3_BASE + 0x3a*4)
#define HSUT0FIFO       SFR_RW (SFR3_BASE + 0x3b*4)
#define HSUT0FIFOADR    SFR_RW (SFR3_BASE + 0x3c*4)
#define HSUT0TMRCNT     SFR_RW (SFR3_BASE + 0x3d*4)
#define HSUT0FCCON      SFR_RW (SFR3_BASE + 0x3e*4)


//------------------------- SFR Group4 ---------------------------------------//
//0x00~0x3f reserve for CPU
#define EXCEPTPND       SFR_RO (SFR4_BASE + 0x00*4)
#define EXCEPTCPND      SFR_WO (SFR4_BASE + 0x01*4)
#define NMICON          SFR_RW (SFR4_BASE + 0x02*4)
#define BP0ADR          SFR_RW (SFR4_BASE + 0x03*4)
#define BP1ADR          SFR_RW (SFR4_BASE + 0x04*4)
#define BP2ADR          SFR_RW (SFR4_BASE + 0x05*4)
#define BP3ADR          SFR_RW (SFR4_BASE + 0x06*4)
#define BP4ADR          SFR_RW (SFR4_BASE + 0x07*4)
#define BP5ADR          SFR_RW (SFR4_BASE + 0x08*4)
#define BP6ADR          SFR_RW (SFR4_BASE + 0x09*4)

#define PICCONCLR       SFR_WO (SFR4_BASE + 0x0c*4)
#define PICCONSET       SFR_WO (SFR4_BASE + 0x0d*4)
#define PICENCLR        SFR_WO (SFR4_BASE + 0x0e*4)
#define PICENSET        SFR_WO (SFR4_BASE + 0x0f*4)

#define PICCON          SFR_RW (SFR4_BASE + 0x10*4)
#define PICEN           SFR_RW (SFR4_BASE + 0x11*4)
#define PICPR           SFR_RW (SFR4_BASE + 0x12*4)
#define PICADR          SFR_RW (SFR4_BASE + 0x13*4)
#define PICPND          SFR_RW (SFR4_BASE + 0x14*4)
#define CACHCON0        SFR_RW (SFR4_BASE + 0x15*4)
#define CACHCON1        SFR_RW (SFR4_BASE + 0x16*4)
#define ICTAG           SFR_RW (SFR4_BASE + 0x17*4)
#define ICINDEX         SFR_RW (SFR4_BASE + 0x18*4)
#define ICADRMS         SFR_RW (SFR4_BASE + 0x19*4)
#define ICLOCK          SFR_RW (SFR4_BASE + 0x1a*4)
#define ICVAL           SFR_RW (SFR4_BASE + 0x1b*4)

#define SWBK            SFR_RW (SFR4_BASE + 0x1d*4)
#define EPICCON         SFR_RW (SFR4_BASE + 0x1e*4)
#define EPC             SFR_RW (SFR4_BASE + 0x1f*4)

#define BP7ADR          SFR_RW (SFR4_BASE + 0x20*4)
#define BP8ADR          SFR_RW (SFR4_BASE + 0x21*4)
#define BP9ADR          SFR_RW (SFR4_BASE + 0x22*4)
#define BP10ADR         SFR_RW (SFR4_BASE + 0x23*4)
#define BP11ADR         SFR_RW (SFR4_BASE + 0x24*4)
#define BP12ADR         SFR_RW (SFR4_BASE + 0x25*4)
#define BP13ADR         SFR_RW (SFR4_BASE + 0x26*4)
#define BP14ADR         SFR_RW (SFR4_BASE + 0x27*4)
#define BP15ADR         SFR_RW (SFR4_BASE + 0x28*4)
#define PICPR1          SFR_RW (SFR4_BASE + 0x29*4)

#define PCERR           SFR_RW (SFR4_BASE + 0x2e*4)
#define PCST            SFR_RW (SFR4_BASE + 0x2f*4)

#define CPUID           SFR_RW (SFR4_BASE + 0x3f*4)

//------------------------- SFR Group5 ---------------------------------------//

#define EFCON0          SFR_RW (SFR5_BASE + 0x10*4)
#define EFCON1          SFR_WO (SFR5_BASE + 0x11*4)
#define EFDAT           SFR_RW (SFR5_BASE + 0x12*4)
#define MBISTCON        SFR_RW (SFR5_BASE + 0x13*4)
#define MBISTEADR       SFR_WO (SFR5_BASE + 0x14*4)
#define MBISTBADR       SFR_WO (SFR5_BASE + 0x15*4)
#define MBISTCRC        SFR_RW (SFR5_BASE + 0x16*4)
#define MBISTERR        SFR_RO (SFR5_BASE + 0x17*4)


#define SADCDAT0        SFR_RO (SFR5_BASE + 0x20*4)
#define SADCDAT1        SFR_RO (SFR5_BASE + 0x21*4)
#define SADCDAT2        SFR_RO (SFR5_BASE + 0x22*4)
#define SADCDAT3        SFR_RO (SFR5_BASE + 0x23*4)
#define SADCDAT4        SFR_RO (SFR5_BASE + 0x24*4)
#define SADCDAT5        SFR_RO (SFR5_BASE + 0x25*4)
#define SADCDAT6        SFR_RO (SFR5_BASE + 0x26*4)
#define SADCDAT7        SFR_RO (SFR5_BASE + 0x27*4)
#define SADCDAT8        SFR_RO (SFR5_BASE + 0x28*4)
#define SADCDAT9        SFR_RO (SFR5_BASE + 0x29*4)
#define SADCDAT10       SFR_RO (SFR5_BASE + 0x2a*4)
#define SADCDAT11       SFR_RO (SFR5_BASE + 0x2b*4)
#define SADCDAT12       SFR_RO (SFR5_BASE + 0x2c*4)
#define SADCDAT13       SFR_RO (SFR5_BASE + 0x2d*4)
#define SADCDAT14       SFR_RO (SFR5_BASE + 0x2e*4)
#define SADCDAT15       SFR_RO (SFR5_BASE + 0x2f*4)

#define SADCCON         SFR_RW (SFR5_BASE + 0x30*4)
#define SADCCH          SFR_RW (SFR5_BASE + 0x31*4)
#define SADCST          SFR_WO (SFR5_BASE + 0x32*4)
#define SADCBAUD        SFR_WO (SFR5_BASE + 0x33*4)

#define SADCDMA         SFR_RW (SFR5_BASE + 0x34*4)
#define SADCBADR        SFR_RW (SFR5_BASE + 0x35*4)
#define SADCMCON        SFR_RW (SFR5_BASE + 0x36*4)
#define SADCCPND        SFR_RW (SFR5_BASE + 0x37*4)

#define MICAUDCON0      SFR_RW (SFR5_BASE + 0x38*4)
#define MICAUDCON1      SFR_RW (SFR5_BASE + 0x39*4)


//------------------------- SFR Group6 ---------------------------------------//

#define GPIOBSET        SFR_RW (SFR6_BASE + 0x10*4)
#define GPIOBCLR        SFR_RW (SFR6_BASE + 0x11*4)
#define GPIOB           SFR_RW (SFR6_BASE + 0x12*4)
#define GPIOBDIR        SFR_RW (SFR6_BASE + 0x13*4)
#define GPIOBDE         SFR_RW (SFR6_BASE + 0x14*4)
#define GPIOBFEN        SFR_RW (SFR6_BASE + 0x15*4)
#define GPIOBFDIREN     SFR_RW (SFR6_BASE + 0x16*4)
#define GPIOBDRV        SFR_RW (SFR6_BASE + 0x17*4)
#define GPIOBPU         SFR_RW (SFR6_BASE + 0x18*4)
#define GPIOBPD         SFR_RW (SFR6_BASE + 0x19*4)
#define GPIOBPU200K     SFR_RW (SFR6_BASE + 0x1a*4)
#define GPIOBPD200K     SFR_RW (SFR6_BASE + 0x1b*4)
#define GPIOBPU300      SFR_RW (SFR6_BASE + 0x1c*4)
#define GPIOBPD300      SFR_RW (SFR6_BASE + 0x1d*4)


#define FUNCOMCON0    SFR_RW (SFR6_BASE + 0x30*4)
#define FUNCOMCON1    SFR_RW (SFR6_BASE + 0x31*4)
#define FUNCOMCON2    SFR_RW (SFR6_BASE + 0x32*4)
#define FUNCOMCON3    SFR_RW (SFR6_BASE + 0x33*4)
#define FUNCOMCON4    SFR_RW (SFR6_BASE + 0x34*4)
#define FUNCOMCON5    SFR_RW (SFR6_BASE + 0x35*4)
#define FUNCOMCON6    SFR_RW (SFR6_BASE + 0x36*4)
#define FUNCOMCON7    SFR_RW (SFR6_BASE + 0x37*4)
#define FUNCIMCON0    SFR_RW (SFR6_BASE + 0x38*4)
#define FUNCIMCON1    SFR_RW (SFR6_BASE + 0x39*4)
#define FUNCIMCON2    SFR_RW (SFR6_BASE + 0x3a*4)
#define FUNCIMCON3    SFR_RW (SFR6_BASE + 0x3b*4)
#define FUNCIMCON4    SFR_RW (SFR6_BASE + 0x3c*4)
#define FUNCIMCON5    SFR_RW (SFR6_BASE + 0x3d*4)
#define FUNCIMCON6    SFR_RW (SFR6_BASE + 0x3e*4)

//------------------------- SFR Group7 ---------------------------------------//
#define GPIOGSET        SFR_RW (SFR7_BASE + 0x00*4)
#define GPIOGCLR        SFR_RW (SFR7_BASE + 0x01*4)
#define GPIOG           SFR_RW (SFR7_BASE + 0x02*4)
#define GPIOGDIR        SFR_RW (SFR7_BASE + 0x03*4)
#define GPIOGDE         SFR_RW (SFR7_BASE + 0x04*4)
#define GPIOGFEN        SFR_RW (SFR7_BASE + 0x05*4)
#define GPIOGFDIREN     SFR_RW (SFR7_BASE + 0x06*4)
#define GPIOGDRV        SFR_RW (SFR7_BASE + 0x07*4)
#define GPIOGPU         SFR_RW (SFR7_BASE + 0x08*4)
#define GPIOGPD         SFR_RW (SFR7_BASE + 0x09*4)
#define GPIOGPU200K     SFR_RW (SFR7_BASE + 0x0a*4)
#define GPIOGPD200K     SFR_RW (SFR7_BASE + 0x0b*4)
#define GPIOGPU300      SFR_RW (SFR7_BASE + 0x0c*4)
#define GPIOGPD300      SFR_RW (SFR7_BASE + 0x0d*4)

#define WKUPCON         LPSFR_RW (SFR7_BASE + 0x10*4)
#define WKUPEDG         LPSFR_RW (SFR7_BASE + 0x11*4)
#define WKUPCPND        LPSFR_RW (SFR7_BASE + 0x12*4)
#define PORTINTEDG      LPSFR_RW (SFR7_BASE + 0x13*4)
#define PORTINTEN       LPSFR_RW (SFR7_BASE + 0x14*4)
#define WKPINMAP        LPSFR_RW (SFR7_BASE + 0x15*4)
#define WKRSRC          LPSFR_RW (SFR7_BASE + 0x16*4)
#define WKFSRC          LPSFR_RW (SFR7_BASE + 0x17*4)
#define BTCON2          LPSFR_RW (SFR7_BASE + 0x18*4)
#define KEYSCAN_CON0    LPSFR_RW (SFR7_BASE + 0x19*4)
#define KEYSCAN_CON1    LPSFR_RW (SFR7_BASE + 0x1a*4)
#define KEYSCAN_CLR     LPSFR_RW (SFR7_BASE + 0x1b*4)
#define KEYSCAN_INFO0   LPSFR_RW (SFR7_BASE + 0x1c*4)
#define KEYSCAN_INFO1   LPSFR_RW (SFR7_BASE + 0x1d*4)
#define KEYSCAN_INFO2   LPSFR_RW (SFR7_BASE + 0x1e*4)


#define IRTXCON         SFR_RW (SFR7_BASE + 0x25*4)

#define IRTXPEND        SFR_RW (SFR7_BASE + 0x28*4)
#define IRDMACON        SFR_RW (SFR7_BASE + 0x29*4)
#define IRDMAIADR       SFR_RW (SFR7_BASE + 0x2a*4)
#define IRDMAISIZE      SFR_RW (SFR7_BASE + 0x2b*4)

#define IRDMAPEND       SFR_RW (SFR7_BASE + 0x2e*4)
#define IRRXCON         SFR_RW (SFR7_BASE + 0x2f*4)
#define IRRXDAT         SFR_RW (SFR7_BASE + 0x30*4)
#define IRRXCPND        SFR_WO (SFR7_BASE + 0x31*4)
#define IRRXERR0        SFR_WO (SFR7_BASE + 0x32*4)
#define IRRXERR1        SFR_WO (SFR7_BASE + 0x33*4)
#define IRRXPR0         SFR_WO (SFR7_BASE + 0x34*4)
#define IRRXPR1         SFR_WO (SFR7_BASE + 0x35*4)
#define IRFLTCON        SFR_RW (SFR7_BASE + 0x36*4)

#define CORDICCON       SFR_RW (SFR7_BASE + 0x3b*4)
#define CORDICINDATX    SFR_RW (SFR7_BASE + 0x3c*4)
#define CORDICINDATY    SFR_RW (SFR7_BASE + 0x3d*4)
#define CORDICOUTDATX   SFR_RW (SFR7_BASE + 0x3e*4)
#define CORDICOUTDATY   SFR_RW (SFR7_BASE + 0x3f*4)

//------------------------- SFR Group8 ---------------------------------------//



//------------------------- SFR Group9 ---------------------------------------//
#define TMR3CON         SFR_RW (SFR9_BASE + 0x00*4)
#define TMR3CPND        SFR_WO (SFR9_BASE + 0x01*4)
#define TMR3CNT         SFR_RW (SFR9_BASE + 0x02*4)
#define TMR3PR          SFR_RW (SFR9_BASE + 0x03*4)
#define TMR3CPT         SFR_RO (SFR9_BASE + 0x04*4)



#define SPI1CON         SFR_RW (SFR9_BASE + 0x20*4)
#define SPI1BUF         SFR_RW (SFR9_BASE + 0x21*4)
#define SPI1BAUD        SFR_RW (SFR9_BASE + 0x22*4)
#define SPI1CPND        SFR_RW (SFR9_BASE + 0x23*4)
#define SPI1DMACNT      SFR_RW (SFR9_BASE + 0x24*4)
#define SPI1DMAADR      SFR_RW (SFR9_BASE + 0x25*4)

#define FREQDETCON      SFR_RW (SFR9_BASE + 0x28*4)
#define FREQDETCPND     SFR_RW (SFR9_BASE + 0x29*4)
#define FREQDETCNT      SFR_RW (SFR9_BASE + 0x2a*4)
#define FREQDETTGT      SFR_RW (SFR9_BASE + 0x2b*4)

#define TMRPCON         SFR_RW (SFR9_BASE + 0x30*4)
#define TMRPCPND        SFR_RW (SFR9_BASE + 0x31*4)
#define TMRPCNT         SFR_RW (SFR9_BASE + 0x32*4)
#define TMRPPR          SFR_RW (SFR9_BASE + 0x33*4)
#define TMRPDUTY0       SFR_RW (SFR9_BASE + 0x34*4)
#define TMRPDUTY1       SFR_RW (SFR9_BASE + 0x35*4)
#define TMRPDUTY2       SFR_RW (SFR9_BASE + 0x36*4)
#define TMRPDUTY3       SFR_RW (SFR9_BASE + 0x37*4)
#define TMRPDUTY4       SFR_RW (SFR9_BASE + 0x38*4)
#define TMRPDUTY5       SFR_RW (SFR9_BASE + 0x39*4)
#define TMRPG2CNT       SFR_RW (SFR9_BASE + 0x3a*4)
#define TMRPG2PR        SFR_RW (SFR9_BASE + 0x3b*4)
#define PWMDZCON        SFR_RW (SFR9_BASE + 0x3c*4)

//------------------------- SFR Group10 --------------------------------------//

#define RTCRAMADR       RTCSFR_RW (SFR10_BASE + 0x1c*4)
#define RTCRAMDAT       RTCSFR_RW (SFR10_BASE + 0x1d*4)
#define RTCALM          RTCSFR_RW (SFR10_BASE + 0x1e*4)
#define RTCCNT          RTCSFR_RW (SFR10_BASE + 0x1f*4)

#define RTCCON0         RTCSFR_RW (SFR10_BASE + 0x20*4)
#define RTCCON1         RTCSFR_RW (SFR10_BASE + 0x21*4)
#define RTCCON2         RTCSFR_RW (SFR10_BASE + 0x22*4)
#define RTCCON3         RTCSFR_RW (SFR10_BASE + 0x23*4)
#define RTCCON4         RTCSFR_RW (SFR10_BASE + 0x24*4)
#define RTCCON5         RTCSFR_RW (SFR10_BASE + 0x25*4)
#define RTCCON6         RTCSFR_RW (SFR10_BASE + 0x26*4)
#define RTCCON7         RTCSFR_RW (SFR10_BASE + 0x27*4)
#define RTCCON8         RTCSFR_RW (SFR10_BASE + 0x28*4)
#define RTCCON9         RTCSFR_RW (SFR10_BASE + 0x29*4)
#define RTCCON10        RTCSFR_RW (SFR10_BASE + 0x2a*4)
#define RTCCON11        RTCSFR_RW (SFR10_BASE + 0x2b*4)
#define RTCCON12        RTCSFR_RW (SFR10_BASE + 0x2c*4)
#define RTCCON13        RTCSFR_RW (SFR10_BASE + 0x2d*4)
#define RTCCON14        RTCSFR_RW (SFR10_BASE + 0x2e*4)
#define RTCCON15        RTCSFR_RW (SFR10_BASE + 0x2f*4)

#define WPTCON          SFR_RW (SFR10_BASE + 0x30*4)
#define WPTPND          SFR_RW (SFR10_BASE + 0x31*4)
#define WPTADR          SFR_RW (SFR10_BASE + 0x32*4)
#define WPTDAT          SFR_RW (SFR10_BASE + 0x33*4)


#define FPGATBBGCLR     SFR_RW (SFR10_BASE + 0x39*4)
#define FPGATBBGSET     SFR_RW (SFR10_BASE + 0x3a*4)
#define FPGAUTCON       SFR_RW (SFR10_BASE + 0x3b*4)
#define FPGAUTDATA      SFR_RW (SFR10_BASE + 0x3c*4)
#define FPGAUTCPND      SFR_RW (SFR10_BASE + 0x3d*4)
#define FPGAUTBAUD      SFR_RW (SFR10_BASE + 0x3e*4)
#define FPGATEST        SFR_RW (SFR10_BASE + 0x3f*4)



#define FPGAUTCON2      SFR_RW (SFR11_BASE + 0x36*4)
#define FPGAUTDATA2     SFR_RW (SFR11_BASE + 0x37*4)
#define FPGAUTCPND2     SFR_RW (SFR11_BASE + 0x38*4)
#define FPGAUTBAUD2     SFR_RW (SFR11_BASE + 0x39*4)


// SFR bank12 define
//////////////////////////////


#define LEDCCON         SFR_RW (SFR12_BASE + 0x30*4)
#define LEDCFD          SFR_RW (SFR12_BASE + 0x31*4)
#define LEDCLP          SFR_RW (SFR12_BASE + 0x32*4)
#define LEDCTIX         SFR_RW (SFR12_BASE + 0x33*4)
#define LEDCRSTX        SFR_RW (SFR12_BASE + 0x34*4)
#define LEDCADDR        SFR_RW (SFR12_BASE + 0x35*4)
#define LEDCCNT         SFR_RW (SFR12_BASE + 0x36*4)
#define LEDCPEND        SFR_RW (SFR12_BASE + 0x37*4)

// SFR bank13 define


#ifndef __ASSEMBLER__
enum funo_select_tbl {
    FO_PWM0           =5,
    FO_PWM1,
    FO_PWM2,
    FO_PWM3,            //8
    FO_PWM4,
    FO_PWM5,
    FO_LEDCDAT,
    FO_IRTX,            //12
    FO_UR0TX,
    FO_HURTX,
    FO_HURRTS,
    FO_SPI1D0,          //16
    FO_SPI1D1,
    FO_SPI1CLK,
    FO_CLKOUT,          //19
};

enum funi_io_tbl {
    FI_PB0              = 1,
    FI_PB1,
    FI_PB2,
    FI_PB3,
    FI_PB4,
    FI_PB5,
    FI_PB6,
    FI_PB7,
    FI_PB8,
    FI_PB9,
    FI_PB10,
    FI_PB11,
};
#endif

#define FUNO_PB0SEL(funo_sel)   FUNCOMCON4 = (funo_sel<< 0)
#define FUNO_PB1SEL(funo_sel)   FUNCOMCON4 = (funo_sel<< 8)
#define FUNO_PB2SEL(funo_sel)   FUNCOMCON4 = (funo_sel<<16)
#define FUNO_PB3SEL(funo_sel)   FUNCOMCON4 = (funo_sel<<24)
#define FUNO_PB4SEL(funo_sel)   FUNCOMCON5 = (funo_sel<< 0)
#define FUNO_PB5SEL(funo_sel)   FUNCOMCON5 = (funo_sel<< 8)
#define FUNO_PB6SEL(funo_sel)   FUNCOMCON5 = (funo_sel<<16)
#define FUNO_PB7SEL(funo_sel)   FUNCOMCON5 = (funo_sel<<24)
#define FUNO_PB8SEL(funo_sel)   FUNCOMCON6 = (funo_sel<< 0)
#define FUNO_PB9SEL(funo_sel)   FUNCOMCON6 = (funo_sel<< 8)
#define FUNO_PB10SEL(funo_sel)  FUNCOMCON6 = (funo_sel<<16)
#define FUNO_PB11SEL(funo_sel)  FUNCOMCON6 = (funo_sel<<24)

#define FUNO_PG1SEL(funo_sel)   FUNCOMCON7 = (funo_sel<< 0)
#define FUNO_PG2SEL(funo_sel)   FUNCOMCON7 = (funo_sel<< 8)
#define FUNO_PG4SEL(funo_sel)   FUNCOMCON7 = (funo_sel<<16)
#define FUNO_PG5SEL(funo_sel)   FUNCOMCON7 = (funo_sel<<24)

#define FUNI_UR0RX(funi_io)     FUNCIMCON0 = (funi_io<< 0)          //0
#define FUNI_SPI1CLK(funi_io)   FUNCIMCON0 = (funi_io<<16)
#define FUNI_SPI1DI0(funi_io)   FUNCIMCON0 = (funi_io<<24)
#define FUNI_SPI1DI1(funi_io)   FUNCIMCON1 = (funi_io<< 0)          //4
#define FUNI_HURRX(funi_io)     FUNCIMCON1 = (funi_io<< 8)
#define FUNI_HURCTS(funi_io)    FUNCIMCON1 = (funi_io<<16)
#define FUNI_TINC0(funi_io)     FUNCIMCON1 = (funi_io<<24)
#define FUNI_TINC1(funi_io)     FUNCIMCON2 = (funi_io<< 0)          //8
#define FUNI_T2CAP(funi_io)     FUNCIMCON2 = (funi_io<< 8)
#define FUNI_T3CAP(funi_io)     FUNCIMCON2 = (funi_io<<16)
#define FUNI_IRRX(funi_io)      FUNCIMCON2 = (funi_io<<24)
#define FUNI_SPI0CLK(funi_io)   FUNCIMCON3 = (funi_io<< 0)          //12
#define FUNI_SPI0DI0(funi_io)   FUNCIMCON3 = (funi_io<< 8)
#define FUNI_SP10DI1(funi_io)   FUNCIMCON3 = (funi_io<<16)
#define FUNI_CH27(funi_io)      FUNCIMCON3 = (funi_io<<24)
#endif
