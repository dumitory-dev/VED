#include <wdm.h>

/* 
Easy "Hello world"
*/

static VOID Unload(DRIVER_OBJECT * pDriverObj)
{
    UNREFERENCED_PARAMETER(pDriverObj);
 
    DbgPrint("Good bye!\r\n");
}
 
NTSTATUS DriverEntry(DRIVER_OBJECT * pDriverObj, UNICODE_STRING * pRegPath)
{
    UNREFERENCED_PARAMETER(pRegPath);
 
    DbgPrint("Hello, World!\r\n");
	
    DbgBreakPoint();
    pDriverObj->DriverUnload = Unload;
    return STATUS_SUCCESS;
}

