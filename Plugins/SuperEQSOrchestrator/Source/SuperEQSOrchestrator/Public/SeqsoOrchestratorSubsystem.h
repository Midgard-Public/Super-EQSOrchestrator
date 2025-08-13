#pragma once

#pragma region Includes
#include "Subsystems/WorldSubsystem.h"
#include "SeqsoOrchestratorSubsystem.generated.h"
#pragma endregion Includes

#pragma region USeqsoOrchestratorSubsystem
/**
 * Summary: World-level subsystem that will host the Super-EQSOrchestrator runtime.
 * Usage: USeqsoOrchestratorSubsystem* S = World->GetSubsystem<USeqsoOrchestratorSubsystem>();
 * Thread-safety: Public API is game-thread only unless documented otherwise.
 * Preconditions: World initialized; module loaded.
 * Errors/Logs: Initialize and Deinitialize emit lifecycle log lines with world name under LogSEQSO_Orchestrator.
 * Performance: Minimal work in Initialize; heavy tasks deferred.
 */
UCLASS()
class SEQSO_API USeqsoOrchestratorSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    /**
     * Logs "OrchestratorSubsystem initialized for world <name>" via LogSEQSO_Orchestrator.
     */
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    /**
     * Logs "OrchestratorSubsystem deinitialized for world <name>" via LogSEQSO_Orchestrator.
     */
    virtual void Deinitialize() override;
};
#pragma endregion USeqsoOrchestratorSubsystem

