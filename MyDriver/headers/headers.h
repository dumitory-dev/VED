#ifndef HEADER
#define HEADER

/*
 * The RTL_CONSTANT_STRING macro creates a string or Unicode string structure to hold a counted string.
 */

UNICODE_STRING DeviceName = RTL_CONSTANT_STRING(L"\\Device\\FileDriverTest");
UNICODE_STRING SymLinkName = RTL_CONSTANT_STRING(L"\\??\\FileDriverTestSymLink");

PDEVICE_OBJECT DeviceObject = NULL;

#endif
