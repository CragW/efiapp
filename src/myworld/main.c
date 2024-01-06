#include <efi.h>
#include <efilib.h>

EFI_STATUS
efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    InitializeLib(ImageHandle, SystemTable);

    // Your EFI application code here

    Print(L"Hello, EFI!\n");

    return EFI_SUCCESS;
}
