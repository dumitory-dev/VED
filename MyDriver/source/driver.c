#include <wdm.h>
#include "../headers/headers.h"

/*
INFO BUILD:
OS VERSION: Windows 7
SDK VERSION: 10.0.18362.0
VISUAl STUDIO 2019 COMMUNITY
*/

DRIVER_UNLOAD Unload;
DRIVER_DISPATCH StubFunc;

NTSTATUS DriverEntry(struct _DRIVER_OBJECT* DriverObject, UNICODE_STRING* pRegPath)
{
	UNREFERENCED_PARAMETER(pRegPath);
	DriverObject->DriverUnload = Unload;

	NTSTATUS status = IoCreateDevice(DriverObject,
		0,
		&DeviceName,
		FILE_DEVICE_UNKNOWN,
		FILE_DEVICE_SECURE_OPEN,
		FALSE,
		&DeviceObject
	);

	if (!NT_SUCCESS(status))
	{
		DbgPrint("Failed creating device!");
		return status;
	}

	status = IoCreateSymbolicLink(&SymLinkName, &DeviceName);

	if (!NT_SUCCESS(status))
	{
		DbgPrint("Failed creating Symbolic Link device!");
		IoDeleteDevice(DeviceObject);
		return status;
	}

	for (int i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; ++i)
	{
		DriverObject->MajorFunction[i] = StubFunc;
	}

	//DriverObject->MajorFunction[IRP_MJ_READ] = ReadWorker;
	//DriverObject->MajorFunction[IRP_MJ_WRITE] = WriteWorker;

	DbgPrint("Success driver installation!");

	return status;
}

/*
   The DRIVER_UNLOAD function type is defined in the Wdm.h header file.
   To more accurately identify errors when you run the code analysis tools, be sure to add the _Use_decl_annotations_ annotation to your function definition.
   The _Use_decl_annotations_ annotation ensures that the annotations that are applied to the DRIVER_UNLOAD function type in the header file are used.
   For more information about the requirements for function declarations, see Declaring Functions by Using Function Role Types for WDM Drivers.
   For information about _Use_decl_annotations_, see Annotating Function Behavior.
*/

_Use_decl_annotations_
VOID  Unload(struct _DRIVER_OBJECT* DriverObject)
{

	UNREFERENCED_PARAMETER(DriverObject);

	IoDeleteSymbolicLink(&SymLinkName);
	IoDeleteDevice(DeviceObject);

	DbgPrint("Driver Unload!\r\n");
}

_Use_decl_annotations_
NTSTATUS  StubFunc(PDEVICE_OBJECT DriverObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DriverObject);
	
	PIO_STACK_LOCATION irpsp = IoGetCurrentIrpStackLocation(Irp);
	const NTSTATUS status = STATUS_SUCCESS;
	
	switch (irpsp->MajorFunction)
	{
	case  IRP_MJ_CREATE:
		DbgPrint("Create request!\r\n");
		break;
	case IRP_MJ_CLOSE:
		DbgPrint("Close request!\r\n");
		break;
	case  IRP_MJ_READ:
		DbgPrint("Read request!\r\n");
		break;
	default:
		break;
	}


	Irp->IoStatus.Information = 0;
	Irp->IoStatus.Status = status;
	IoCompleteRequest(Irp,IO_NO_INCREMENT);
	
	return status;
}