#include "Modules/ModuleManager.h"
#include "Logging/LogMacros.h"

DEFINE_LOG_CATEGORY_STATIC(LogSEQSOEditor, Log, All);

class FSuperEQSOrchestratorEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override
    {
        UE_LOG(LogSEQSOEditor, Display, TEXT("Super-EQSOrchestratorEditor started"));
    }

    virtual void ShutdownModule() override
    {
        UE_LOG(LogSEQSOEditor, Display, TEXT("Super-EQSOrchestratorEditor stopped"));
    }
};

IMPLEMENT_MODULE(FSuperEQSOrchestratorEditorModule, SuperEQSOrchestratorEditor)

