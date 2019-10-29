#pragma once
#include <ntifs.h>
#include <ntddk.h>
#include <Bcrypt.h>
#define BLOCK_SIZE 16

void Rc4Crypt(char *key,size_t len,char * data,size_t data_len);

NTSTATUS DecryptEncrypt(UCHAR * puDataPassword, size_t uSizePassword, UCHAR * puData, size_t uSizeData, BOOLEAN bIsEncrypt);
