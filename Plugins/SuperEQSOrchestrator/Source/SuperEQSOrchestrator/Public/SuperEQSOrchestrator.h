#pragma once
/**
 * Summary: Runtime module for Super-EQSOrchestrator.
 * Usage: Loaded by Unreal at module start; central place to register systems.
 * Thread-safety: Startup/Shutdown run on game thread. Heavy work must be deferred.
 * Preconditions: Engine initialized; plugin enabled.
 * Errors/Logs: Emits startup/shutdown logs under LogSEQSO.
 * Performance: Keep StartupModule minimal.
 */

#include "Modules/ModuleManager.h"
#include "Logging/LogMacros.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSEQSO, Log, All);

class SEQSO_API FSuperEQSOrchestratorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
