#include  <Uefi.h>
#include  <Library/UefiLib.h>
#include  <stdio.h>
#include <IndustryStandard/SmBios.h>

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










//#include  <Library/ShellCEntryLib.h>
//#include <Guid/SmBios.h>
//#include  <LibSmbiosView.h>
//#include "EdkIIGlueUefi.h"
//#include "Library/EdkIIGlueMemoryAllocationLib.h"
//#include "UefiShellDebug1CommandsLib.h"
//GetSystemConfigurationTable (IN EFI_GUID *TableGuid,IN OUT VOID **Table);
//extern EFI_SYSTEM_TABLE *gST; 
//extern CompareGuid (IN CONST GUID  *Guid1,IN CONST GUID  *Guid2);
//STATIC SMBIOS_TABLE_ENTRY_POINT     *mSmbiosTable   = NULL;
//  UINT8   sSm3EntryPointStructureChecksum;
//  UINT8   sSm3EntryPointLength;
//  UINT8   sSm3SmbiosMajorVersion;
//  UINT8   sSm3SmbiosMinorVersion;
//  UINT8   sSm3SmbiosDocRev;
//  UINT8   sSm3EntryPointRevision;
//  UINT32  sSm3StructureMaximumSize;
//  UINT64  sSm3StructureTableAddress;
/*    
  EFI_SYSTEM_TABLE  *SystemTable;
  UINTN             Index;
EFI_GUID  *TableGuid=&gEfiSmbios3TableGuid;
VOID      **Table   =(VOID**)&mSmbiosTable;

  SystemTable = gST;
  *Table = NULL;
  for (Index = 0; Index < SystemTable->NumberOfTableEntries; Index++) {
	  printf("%s\r\n",(SystemTable->ConfigurationTable[Index].VendorGuid));
	    printf("\n");
    if (CompareGuid (TableGuid, &(SystemTable->ConfigurationTable[Index].VendorGuid))) {
      *Table = SystemTable->ConfigurationTable[Index].VendorTable;
      break;
    }
  }
*/
//  printf("EPS= %p\r\n",(UINT8 *) (UINTN)AppSmbios64Eps); 
    //printf("EPS_FD= %x\r\n",*usrP8); 
  //usrP8++;
  //printf("EPS_FD= %x\r\n",*usrP8);
  //printf("EPS_FD= %x\r\n",*AppSmbios64Eps);     
  //printf("userSL= %x\r\n",userSL); 
      //Address1  = (UINT8 *) (UINTN) (mSmbiosTable->TableAddress);
	  
    // printf("EPS_FD= %x\r\n",*(UINT8 *)AppSmbios64Eps);
	//printf("AnchorString head= %p\r\n",(UINT8 *) (UINTN)(AppSmbios64Eps->AnchorString));
	//  printf("Address= %p\r\n",(UINT8 *) (UINTN) (AppSmbios64Eps->TableAddress));