/** @file
  The UEFI Library provides functions and macros that simplify the development of 
  UEFI Drivers and UEFI Applications.  These functions and macros help manage EFI 
  events, build simple locks utilizing EFI Task Priority Levels (TPLs), install 
  EFI Driver Model related protocols, manage Unicode string tables for UEFI Drivers, 
  and print messages on the console output and standard error devices.

  Copyright (c) 2006 - 2017, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php.

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/



/**
  Empty constructor function that is required to resolve dependencies between 
  libraries.
  
    ** DO NOT REMOVE **
  
  @param  ImageHandle   The firmware allocated handle for the EFI image.
  @param  SystemTable   A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS   The constructor executed correctly.

**/

#include  <stdio.h>

int
TestLib(void
  )
{
printf("Hello for the other side.(TestLib)\n");
  return 0;
}

