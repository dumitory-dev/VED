#pragma once
#include "libraries.h"
#define MAX_PASSWORD_SIZE 16
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
#define PASSWORD_OFFSET 4096





