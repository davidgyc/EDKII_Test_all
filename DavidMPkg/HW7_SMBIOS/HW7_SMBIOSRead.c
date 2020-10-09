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
#include  <Uefi.h>
#include  <Library/UefiLib.h>
#include  <Library/ShellCEntryLib.h>
//#include <Guid/SmBios.h>
#include  <stdio.h>
#include  <LibSmbiosView.h>

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


extern GetSystemConfigurationTable (IN EFI_GUID *TableGuid,IN OUT VOID **Table);

STATIC SMBIOS_TABLE_ENTRY_POINT     *mSmbiosTable   = NULL;


int
main (
  IN int Argc,
  IN char **Argv
  )
{
	UINT8 Address1=0;
    {//from SMBIOSVIEW
	    EFI_STATUS  Status;
	    //
	    // Get SMBIOS table from System Configure table
	    //
        Status = GetSystemConfigurationTable (&gEfiSmbiosTableGuid, (VOID**)&mSmbiosTable);

	    if (mSmbiosTable == NULL) {
	    return EFI_NOT_FOUND;
        }
      Address1  = (UINT8 *) (UINTN) (mSmbiosTable->TableAddress);
	}
  
  printf("Addr= %d\n", Address1);
  return 0;
}
