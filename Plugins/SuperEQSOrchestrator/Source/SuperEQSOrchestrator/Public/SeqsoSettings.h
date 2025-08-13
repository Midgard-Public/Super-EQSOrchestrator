#pragma once

#pragma region Includes
#include "Engine/DeveloperSettings.h"
#include "SeqsoSettings.generated.h"
#pragma endregion Includes

#pragma region USeqsoSettings
/**
 * Summary: Project settings for Super-EQSOrchestrator.
 * Usage: Project Settings → Plugins → Super-EQSOrchestrator; read via GetDefault<USeqsoSettings>().
 * Parameters:
 *   - bEnableWelcomeLog: if true, log a startup line when module loads.
 * Thread-safety: Read-only after load; safe for concurrent reads.
 * Preconditions: Engine initialized; module loaded.
 * Errors/Logs: None.
 * Performance: Trivial.
 */
UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="Super-EQSOrchestrator"))
class SEQSO_API USeqsoSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    /** Log a welcome line when the runtime module starts. */
    UPROPERTY(EditAnywhere, Config, Category="General")
    bool bEnableWelcomeLog = true;
};
#pragma endregion USeqsoSettings


