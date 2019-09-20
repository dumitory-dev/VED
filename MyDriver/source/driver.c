#include <wdm.h>

/*
INFO BUILD:
OS VERSION: Windows 7
SDK VERSION: 10.0.18362.0
VISUAl STUDIO 2019 COMMUNITY 
*/

DRIVER_UNLOAD Unload;

NTSTATUS DriverEntry( DRIVER_OBJECT * pDriverObj, UNICODE_STRING * pRegPath)
{
    UNREFERENCED_PARAMETER(pRegPath);
 
    DbgPrint("Hello, World!\r\n");
	
    DbgBreakPoint();
    pDriverObj->DriverUnload = Unload;
    return STATUS_SUCCESS;
}

/*
   The DRIVER_UNLOAD function type is defined in the Wdm.h header file.
   To more accurately identify errors when you run the code analysis tools, be sure to add the _Use_decl_annotations_ annotation to your function definition.
   The _Use_decl_annotations_ annotation ensures that the annotations that are applied to the DRIVER_UNLOAD function type in the header file are used.
   For more information about the requirements for function declarations, see Declaring Functions by Using Function Role Types for WDM Drivers.
   For information about _Use_decl_annotations_, see Annotating Function Behavior.
*/

_Use_decl_annotations_
VOID  Unload( struct _DRIVER_OBJECT  * DriverObject )
{
   UNREFERENCED_PARAMETER(DriverObject);
   DbgPrint("Good bye!\r\n");
}