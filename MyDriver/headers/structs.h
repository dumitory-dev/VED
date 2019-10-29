#pragma once
#include "libraries.h"
#include "constants.h"
#include  "crypt.h"

typedef struct _OPEN_FILE_INFORMATION {
	LARGE_INTEGER	FileSize;
	WCHAR			DriveLetter;
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

