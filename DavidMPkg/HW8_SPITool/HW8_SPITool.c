#include  <Uefi.h>
#include  <Library/UefiLib.h>
#include  <stdio.h>

#define DebugFlag
#define Value32Init 0x00000000
#define MMCFG_BASE 0x00,0x00,0x00,0x90
UINT64 IOReadCfgAsm(IN UINT64 bdfr);
UINT32 ReadCfgByIO(UINT8 uBus, UINT8 uDevice, UINT8 uFunction,UINT8 uRegister);
//move to .h when complete


typedef struct {
UINT32 Reserved_1 :2;
UINT32 RegisterNumber :6;
UINT32 FunctionNumber :3;
UINT32 DeviceNumber :5;
UINT32 BusNumber : 8;
UINT32 Reserved_2 :7;
UINT32 EnableConfigSpaceMapping :1;
}PCI_IO_CFG_STRUCT;

typedef struct {
UINT32 FDONE :1;
UINT32 FCERR :1;
UINT32 H_AEL :1;
UINT32 H_SAF_ERROR :1;
UINT32 H_SAF_DLR :1;
UINT32 H_SCIP :1;
UINT32 RSVD1 :5;
UINT32 WRSDIS:1;
UINT32 PRR34_LOCKDN :1;
UINT32 FDOPSS :1;
UINT32 FDV :1;
UINT32 FLOCKDN :1;
UINT32 FGO :1;
UINT32 FCYCLE :4;
UINT32 WET :1;
UINT32 RSVD2 :2;
UINT32 FDBC :6;
UINT32 RSVD :1;
UINT32 FSMIE :1;
}HSFSTS_CTL_STRUCT;

typedef struct {
UINT16 PRL; //bit15 Reserved.
UINT16 PRB; //bit15 Reserved.
HSFSTS_CTL_STRUCT BIOS_HSFSTS_CTL;
UINT32 BIOS_FADDR;
UINT32 BIOS_DLOCK;
UINT32 BIOS_FDATA00;
UINT32 BIOS_FDATA01;
UINT32 BIOS_FDATA02;
UINT32 BIOS_FDATA03;
UINT32 BIOS_FDATA04;
UINT32 BIOS_FDATA05;
UINT32 BIOS_FDATA06;
UINT32 BIOS_FDATA07;
UINT32 BIOS_FDATA08;
UINT32 BIOS_FDATA09;
UINT32 BIOS_FDATA10;
UINT32 BIOS_FDATA11;
UINT32 BIOS_FDATA12;
UINT32 BIOS_FDATA13;
UINT32 BIOS_FDATA14;
UINT32 BIOS_FDATA15; 
} SPI_STRUC_H;

int main (IN int Argc,IN char **Argv){
 UINT32 MmcfgBar=Value32Init;
 printf("!!SPI tool for lewisburg!!\r\n");
 //ReadCfg(IN UINT64 bdfr) !need to check F1:05 DID
 //UINT32 *SpiAdd,pAdd=0x800FD010 ; //!HC need to fix
//ReadCfgByIO(0x00,0x00,0x00,0x90);
 MmcfgBar =ReadCfgByIO(MMCFG_BASE);
 #ifdef DebugFlag
 printf("Main.CFGReg:0x%x\r\n",ReadCfgByIO(MMCFG_BASE));
 #ifdef DebugFlag

 
 //printf("CFG Reg:0x%x\r\n",IOReadCfgAsm(0x80000090));
 //SpiAdd = (UINT32*)pAdd;
// printf("SPI BAR0:0x%x\r\n",*SpiAdd); 
 
return 0;
}

UINT32 ReadCfgByIO(UINT8 uBus, UINT8 uDevice, UINT8 uFunction,UINT8 uRegister){
 UINT32 cFGdATA;
 PCI_IO_CFG_STRUCT* iOcFGs;
 iOcFGs=(PCI_IO_CFG_STRUCT*)&cFGdATA;
 iOcFGs->RegisterNumber =(uRegister&0xFC)>>2;
 iOcFGs->FunctionNumber =uFunction&0x07;
 iOcFGs->DeviceNumber = uDevice&0x1F;
 iOcFGs->BusNumber =uBus;
 iOcFGs->EnableConfigSpaceMapping =1;
#ifdef DebugFlag
 printf("ReadCfgByIO.CFGData:0x%x\r\n",cFGdATA);
#endif
return (UINT32)IOReadCfgAsm(cFGdATA);
}


 //iOcFGs->ST.RegisterNumber =(uRegister&0xFC)>>2;
 //iOcFGs->ST.FunctionNumber =uFunction&0x07;
 //iOcFGs->ST.DeviceNumber = uDevice&0x1F;
 //iOcFGs->ST.BusNumber =uBus;
 //iOcFGs->ST.EnableConfigSpaceMapping =1;
/*
typedef union {
struct {
UINT32 Reserved_1 :2;
UINT32 RegisterNumber :6;
UINT32 FunctionNumber :3;
UINT32 DeviceNumber :5;
UINT32 BusNumber : 8;
UINT32 Reserved_2 :7;
UINT32 EnableConfigSpaceMapping :1;
}ST;
UINT32     Uint32;
}PCI_IO_CFG_STRUCT;
*/

/* for define
 iOcFGs->ST= {
	 .RegisterNumber =uRegister&0xFC,
	 .FunctionNumber =uFunction&0x07,
	 .DeviceNumber = uDevice&0x1F,
	 .BusNumber =uBus,
	 .EnableConfigSpaceMapping =1
 };
*/
 //HSFSTS_CTL foo;
 //foo.RSVD1 = 0x17;
 //printf("Bit Fields test:0x%x \r\n",foo);//passed

/*
STATIC SMBIOS_TABLE_3_0_ENTRY_POINT *AppSmbios64Eps = NULL;

#define ForInit 0x00

enum Smbios3EpsOffset {
 oSm3AnchorString=               0x00,
 oSm3EntryPointStructureChecksum=0x05,
 oSm3EntryPointLength=           0x06,
 oSm3SmbiosMajorVersion=         0x07,
 oSm3SmbiosMinorVersion=         0x08,
 oSm3SmbiosDocRev=               0x09,
 oSm3EntryPointRevision=         0x0A,
 oSm3StructureMaximumSize=       0x0C,
 oSm3StructureTableAddress=      0x10,
 //https://www.dmtf.org/sites/default/files/standards/documents/DSP0134_3.4.0.pdf
};
#define Smbios3AnchorLength 0x05

int main (IN int Argc,IN char **Argv){
  UINT8 *usrP8;
  UINT8 userSL;
  UINT8 temSm3AnchorString[Smbios3AnchorLength]; 
  {//Get 64 bit SMIOS EPS
  EfiGetSystemConfigurationTable (&gEfiSmbios3TableGuid, (VOID**)&AppSmbios64Eps);
  if (AppSmbios64Eps == NULL) {
    printf("SMBIOS3 Table read fail\n");
    return -1;
  usrP8=(UINT8 *)AppSmbios64Eps;
  } 
  }
  {//Dump SMIOS 64bit EPS raw data
  #define userSL *(usrP8+oSm3EntryPointLength)
  #define sNumPerLine 0x10
  #define sLineHead   0x00
  #define sEndAll     userSL-1
  printf("SMBIOS 3.0 (64-bit) Entry Point structure. Address= %p\r\n",(UINT8 *)(UINTN)AppSmbios64Eps);
  printf("Offset:     ");for(UINT8 xIndex=ForInit;xIndex<sNumPerLine;xIndex++)printf("%02X ",xIndex);printf("\r\n");
  for(UINT8 xIndex=ForInit;xIndex<userSL;xIndex++ ){	
	if(xIndex%sNumPerLine==sLineHead)//head
      printf("       %02X : ",(xIndex/sNumPerLine));	 
    printf("%02X ",*(usrP8+xIndex)); //body
    if(xIndex%sNumPerLine==sNumPerLine-1||xIndex==sEndAll)
      printf("\r\n");	             //tail
  }
  }
  {//Decode 64 bit SMIOS EPS
  for(UINT8 xIndex=ForInit;xIndex<Smbios3AnchorLength;xIndex++)
    temSm3AnchorString[xIndex]=*(usrP8+oSm3AnchorString+xIndex);
  printf("SMBIOS3 AnchorString: %s\r\n",temSm3AnchorString);
  printf("EPS Checksum:         0x%x\r\n",*(usrP8+oSm3EntryPointStructureChecksum));
  printf("Entry Point Len:      %d\r\n",*(usrP8+oSm3EntryPointLength));
  printf("Version:              %d.%d\r\n",*(usrP8+oSm3SmbiosMajorVersion),*(usrP8+oSm3SmbiosMinorVersion));  
  printf("SMBIOS Docrev:        0x%x\r\n",*(usrP8+oSm3SmbiosDocRev));  
  printf("Entry Point revision: 0x%x\r\n",*(usrP8+oSm3EntryPointRevision)); 
  printf("Table Max Size:       %d\r\n",*((UINT32*)(UINTN)(usrP8+oSm3StructureMaximumSize)));  
  printf("Table Address:        0x%p\r\n",*((UINT64*)(UINTN)(usrP8+oSm3StructureTableAddress)));
  }
  return 0;
}

*/








