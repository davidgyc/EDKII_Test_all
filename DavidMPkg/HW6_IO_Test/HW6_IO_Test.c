/** @file
    A simple, basic, application showing how the Hello application could be
    built using the "Standard C Libraries" from StdLib.

    Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>
    This program and the accompanying materials
    are licensed and made available under the terms and conditions of the BSD License
    which accompanies this distribution. The full text of the license may be found at
    http://opensource.org/licenses/bsd-license.

    THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
    WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
**/
//#include  <Uefi.h>
//#include  <Library/UefiLib.h>
//#include  <Library/ShellCEntryLib.h>

#include  <stdio.h>

/***
  Demonstrates basic workings of the main() function by displaying a
  welcoming message.

  Note that the UEFI command line is composed of 16-bit UCS2 wide characters.
  The easiest way to access the command line parameters is to cast Argv as:
      wchar_t **wArgv = (wchar_t **)Argv;

  @param[in]  Argc    Number of argument tokens pointed to by Argv.
  @param[in]  Argv    Array of Argc pointers to command line tokens.

  @retval  0         The application exited normally.
  @retval  Other     An error occurred.
***/

//UINT64 asmTest ( IN UINT64 var1, IN UINT64 var2);
UINT64 readValue1(void);
UINT64 readDs(void);
UINT64 readDs1000(void);
UINT64 readValue2(IN UINT64 var1);
UINT64 readCmos(IN UINT64 offset);
void writeCmos(IN UINT64 offset, IN UINT64 Data);

int
main (
  IN int Argc,
  IN char **Argv
  )
{
  UINT64 Value1=0;
  UINT64 Value2=0;
  UINT64 mos_tmp = 0;
  printf("HW6_Start\n");
  
  Value1 = readValue1();
  
  {//Read Value2
  Value2 = readValue2(Value1);
  printf("Value1 is: %x \n", Value1);
  printf("DS is:%x \n", readDs());
  printf("DS:1000 is:%x \n", readDs1000());
  printf("Value2 is: %x \n", Value2); 
  }
  
  {//Write Value2 to Cmos Offset[9]
      mos_tmp = readCmos(0x09);
      printf("Before CMOS offset[9]= %x \n", mos_tmp); 
	  writeCmos(0x09, Value2);
	  printf("After CMOS offset[9]= %x \n", readCmos(0x09));
	  writeCmos(0x09, mos_tmp);//reset cmos
  }
  printf("HW6_End\n");
  
  return 0;
}
