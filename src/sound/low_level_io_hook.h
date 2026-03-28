#pragma once

#include <AK/SoundEngine/Common/AkStreamMgrModule.h>

namespace otb
{
class SoundLowLevelIOHook : public AK::StreamMgr::IAkLowLevelIOHook
{
  public:
    AKRESULT Close(AkFileDesc*) override;
    AkUInt32 GetBlockSize(AkFileDesc&) override;
    void GetDeviceDesc(AkDeviceDesc&) override;
    AkUInt32 GetDeviceData() override;
    void BatchOpen(AkUInt32, AkAsyncFileOpenData**) override;
    void BatchRead(AkUInt32, BatchIoTransferItem*) override;
    void BatchWrite(AkUInt32, BatchIoTransferItem*) override;
    AKRESULT OutputSearchedPaths(AKRESULT, const AkFileOpenData&, AkOSChar*, AkInt32) override;

    ~SoundLowLevelIOHook() override = default;

    static SoundLowLevelIOHook* instance()
    {
        static SoundLowLevelIOHook v;
        return &v;
    }

    static AkDeviceID device_id;
};
}