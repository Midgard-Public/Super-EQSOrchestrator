#pragma region Includes
#include "SuperEQSOrchestrator.h"
#include "SeqsoVersion.h"
#include "SeqsoSettings.h"
#include "SeqsoLogging.h"
#pragma endregion Includes

#pragma region FSuperEQSOrchestratorModule
DEFINE_LOG_CATEGORY(LogSEQSO);
IMPLEMENT_MODULE(FSuperEQSOrchestratorModule, SuperEQSOrchestrator)

void FSuperEQSOrchestratorModule::StartupModule()
{
    const USeqsoSettings* Settings = GetDefault<USeqsoSettings>();
    if (Settings && Settings->bEnableWelcomeLog)
    {
        UE_LOG(LogSEQSO, Display, TEXT("%s %s started"), SEQSO_PLUGIN_FRIENDLY_NAME, SEQSO_VERSION);
    }
}

void FSuperEQSOrchestratorModule::ShutdownModule()
{
    UE_LOG(LogSEQSO, Display, TEXT("%s stopped"), SEQSO_PLUGIN_FRIENDLY_NAME);
}
#pragma endregion FSuperEQSOrchestratorModule

