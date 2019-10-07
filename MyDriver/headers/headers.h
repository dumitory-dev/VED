#ifndef HEADER
#define HEADER
#include <ntifs.h>
#include <ntdddisk.h>
#include <ntddcdrm.h>
#include <ntstrsafe.h>
#include <wdmsec.h>
#include <mountmgr.h>
#include <ntddvol.h>
#include <ntddscsi.h>

#define WIN9X_COMPAT_SPINLOCK

#define FILE_DISK_POOL_TAG 'ksiD'
#ifndef __T
#ifdef _NTDDK_
#define __T(x) L ## x
#else
#define __T(x) x
#endif
#endif
#ifndef _T
#define _T(x) __T(x)
#endif)
#define DEVICE_BASE_NAME	_T("\\FileDisk")
#define DEVICE_DIR_NAME		_T("\\Device")	DEVICE_BASE_NAME
#define DEVICE_NAME_PREFIX	DEVICE_DIR_NAME	DEVICE_BASE_NAME


#define IOCTL_FILE_DISK_OPEN_FILE	CTL_CODE(FILE_DEVICE_DISK, 0x800, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_FILE_DISK_CLOSE_FILE	CTL_CODE(FILE_DEVICE_DISK, 0x801, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)

#define MAX_PASSWORD_SIZE 16

/*
 * The RTL_CONSTANT_STRING macro creates a string or Unicode string structure to hold a counted string.
 */

UNICODE_STRING DeviceName = RTL_CONSTANT_STRING(L"\\Device\\FileDriverTest");
UNICODE_STRING SymLinkName = RTL_CONSTANT_STRING(L"\\??\\FileDriverTestSymLink");
HANDLE DeviceObject = NULL;

//PDEVICE_OBJECT DeviceObject = NULL;

typedef struct _OPEN_FILE_INFORMATION {
	LARGE_INTEGER	FileSize;
	UCHAR			DriveLetter;
	USHORT			FileNameLength;
	USHORT			PasswordLength;
	CHAR			Password[MAX_PASSWORD_SIZE];
	WCHAR			FileName[1];
}OPEN_FILE_INFORMATION, *POPEN_FILE_INFORMATION;


typedef struct _DEVICE_EXTENSION {
    BOOLEAN                     media_in_device;
    UNICODE_STRING              device_name;
    ULONG                       device_number;
    DEVICE_TYPE                 device_type;
    HANDLE                      file_handle;
	UNICODE_STRING              file_name;
    LARGE_INTEGER               file_size;
	ANSI_STRING					password;
    LIST_ENTRY                  list_head;
    KSPIN_LOCK                  list_lock;
    KEVENT                      request_event;
    PVOID                       thread_pointer;
    BOOLEAN                     terminate_thread;
} DEVICE_EXTENSION, *PDEVICE_EXTENSION;


#endif
