#include "sound_engine.h"

#include "core/assert.h"

#include "sound/low_level_io_hook.h"

#define UNICODE

#include <AK/SoundEngine/Common/AkMemoryMgr.h>
#include <AK/SoundEngine/Common/AkMemoryMgrModule.h>
#include <AK/SoundEngine/Common/AkSoundEngine.h>
#include <AK/SoundEngine/Common/AkStreamMgrModule.h>

namespace otb
{
namespace
{
static AkBankID INIT_BANK_ID;

class FileLocationResolver : public AK::StreamMgr::IAkFileLocationResolver
{
  public:
    AKRESULT GetNextPreferredDevice(AkAsyncFileOpenData&, AkDeviceID&) override
    {
        return AK_NotImplemented;
    }
    ~FileLocationResolver() override = default;

    static FileLocationResolver* instance()
    {
        static FileLocationResolver v;
        return &v;
    }
};
}

SoundEngine::SoundEngine()
{
    AkMemSettings memSettings;
    AK::MemoryMgr::GetDefaultSettings(memSettings);

    if (AK::MemoryMgr::Init(&memSettings) != AK_Success)
    {
        OTB_ASSERT(false, "Failed to initialize AK::MemoryMgr");
    }

    AkStreamMgrSettings stmSettings;
    AK::StreamMgr::GetDefaultSettings(stmSettings);
    if (!AK::StreamMgr::Create(stmSettings))
    {
        OTB_ASSERT(false, "Failed to create AK::StreamMgr");
    }

    AK::StreamMgr::SetFileLocationResolver(FileLocationResolver::instance());

    AkDeviceSettings default_settings;
    AK::StreamMgr::GetDefaultDeviceSettings(default_settings);
    AK::StreamMgr::CreateDevice(default_settings, SoundLowLevelIOHook::instance(), SoundLowLevelIOHook::device_id);

    AkInitSettings initSettings;
    AkPlatformInitSettings platformInitSettings;
    AK::SoundEngine::GetDefaultInitSettings(initSettings);
    AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);

    if (AK::SoundEngine::Init(&initSettings, &platformInitSettings) != AK_Success)
    {
        OTB_ASSERT(false, "Failed to init AK::SoundEngine");
    }

    AK::SoundEngine::LoadBank(L"Init.bnk", INIT_BANK_ID);
}

SoundEngine::~SoundEngine()
{
    AK::SoundEngine::Term();
    if (AK::IAkStreamMgr::Get())
        AK::IAkStreamMgr::Get()->Destroy();
    AK::MemoryMgr::Term();
}

void SoundEngine::update() const
{
    AK::SoundEngine::RenderAudio();
}

void SoundEngine::load_bank(InternedString bank_name)
{
    AkBankID bank_id;
    AK::SoundEngine::LoadBank(bank_name.c_str(), bank_id);
}

size_t SoundEngine::create_game_object()
{
    return free_id++;
}

SoundEngine* SoundEngine::instance()
{
    static SoundEngine v;
    return &v;
}
}