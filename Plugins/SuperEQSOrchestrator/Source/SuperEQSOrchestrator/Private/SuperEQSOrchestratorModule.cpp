#include "SuperEQSOrchestrator.h"
#include "SeqsoVersion.h"

DEFINE_LOG_CATEGORY(LogSEQSO);
IMPLEMENT_MODULE(FSuperEQSOrchestratorModule, SuperEQSOrchestrator)

void FSuperEQSOrchestratorModule::StartupModule()
{
    UE_LOG(LogSEQSO, Display, TEXT("%s %s started"), SEQSO_PLUGIN_FRIENDLY_NAME, SEQSO_VERSION);
}

void FSuperEQSOrchestratorModule::ShutdownModule()
{
    UE_LOG(LogSEQSO, Display, TEXT("%s stopped"), SEQSO_PLUGIN_FRIENDLY_NAME);
}
