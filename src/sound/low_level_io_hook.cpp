#include "low_level_io_hook.h"

#include "core/asset/asset.h"

#include <format>
#include <iostream>

namespace otb
{
AkDeviceID SoundLowLevelIOHook::device_id;

AKRESULT SoundLowLevelIOHook::Close(AkFileDesc* descriptor)
{
    ::CloseHandle(descriptor->hFile);
    return AK_Success;
}
AkUInt32 SoundLowLevelIOHook::GetBlockSize(AkFileDesc&)
{
    // TODO: is it fine?
    return 1;
}
void SoundLowLevelIOHook::GetDeviceDesc(AkDeviceDesc&)
{
    // TODO: impl
    __debugbreak();
}
AkUInt32 SoundLowLevelIOHook::GetDeviceData()
{
    // TODO: impl
    __debugbreak();
    return 0;
}
void SoundLowLevelIOHook::BatchOpen(AkUInt32 file_count, [[maybe_unused]] AkAsyncFileOpenData** pp_items)
{
    for (AkUInt32 i = 0; i < file_count; ++i)
    {
        pp_items[i]->pFileDesc = new AkFileDesc {
            .uSector = 0,
            .deviceID = device_id,
        };
        std::wstring w_asset_name(pp_items[i]->pszFileName);
        std::string asset_name(w_asset_name.begin(), w_asset_name.end());
        const std::string asset_path = std::format("/sound/{}", asset_name.c_str());

        const DWORD desired_access = [&]()->DWORD
        {
            switch(pp_items[i]->eOpenMode)
            {
                case AK_OpenModeRead:
                    return GENERIC_READ;
                case AK_OpenModeWrite:
                    return GENERIC_WRITE;
                case AK_OpenModeWriteOvrwr:
                    return GENERIC_WRITE;
                case AK_OpenModeReadWrite:
                    return GENERIC_READ | GENERIC_WRITE;
            }
            return 0;
        }();
        const DWORD creation_disposition = [&]()->DWORD
        {
            switch(pp_items[i]->eOpenMode)
            {
                case AK_OpenModeRead:
                    return OPEN_EXISTING;
                case AK_OpenModeWrite:
                    return OPEN_ALWAYS;
                case AK_OpenModeWriteOvrwr:
                    return TRUNCATE_EXISTING;
                case AK_OpenModeReadWrite:
                    return OPEN_EXISTING;
            }
            return 0;
        }();
        pp_items[i]->pFileDesc->hFile = ::CreateFile(
            otb::AssetUtils::get_asset_file_path(otb::InternedString(asset_path.c_str())).c_str(),
            desired_access,
            0,
            NULL,
            creation_disposition,
            FILE_FLAG_OVERLAPPED,
            NULL
        );
        pp_items[i]->pFileDesc->iFileSize = ::GetFileSize(pp_items[i]->pFileDesc->hFile, NULL);
        pp_items[i]->pCallback(pp_items[i], AK_Success);
    }
}
void SoundLowLevelIOHook::BatchRead(AkUInt32 num_transfers, BatchIoTransferItem* p_transfers)
{
    for (AkUInt32 i = 0; i < num_transfers; ++i)
    {
        LPOVERLAPPED overlapped = new OVERLAPPED();
        overlapped->Offset = p_transfers[i].pTransferInfo->uFilePosition & 0xFFFFFFFF;
        overlapped->OffsetHigh = (p_transfers[i].pTransferInfo->uFilePosition >> 32) & 0xFFFFFFFF;
        overlapped->hEvent = p_transfers[i].pTransferInfo;

        std::cerr << "Start: " << overlapped << std::endl;

        static constexpr auto callback = [](DWORD, DWORD, LPOVERLAPPED ovr)
        {
            AkAsyncIOTransferInfo* transfer_info = static_cast<AkAsyncIOTransferInfo*>(ovr->hEvent);
            std::cerr << "End: " << ovr << std::endl;
            delete ovr;
            transfer_info->pCallback(transfer_info, AK_Success);
        };

        if(::ReadFileEx(
            p_transfers[i].pFileDesc->hFile,
            p_transfers[i].pTransferInfo->pBuffer,
            p_transfers[i].pTransferInfo->uBufferSize,
            overlapped,
            callback))
        {
            
        }
        else
        {
            __debugbreak();
        }
    }
}
void SoundLowLevelIOHook::BatchWrite(AkUInt32, BatchIoTransferItem*)
{
    // TODO: impl
    __debugbreak();
}
AKRESULT SoundLowLevelIOHook::OutputSearchedPaths(AKRESULT, const AkFileOpenData&, AkOSChar*, AkInt32)
{
    // TODO: impl
    __debugbreak();
    return AK_Success;
}
}