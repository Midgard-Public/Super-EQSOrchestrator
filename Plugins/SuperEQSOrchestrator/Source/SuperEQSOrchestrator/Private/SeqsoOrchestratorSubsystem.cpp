#pragma region Includes
#include "SeqsoOrchestratorSubsystem.h"
#include "Engine/World.h"
#include "SeqsoLogging.h"
#pragma endregion Includes

#pragma region USeqsoOrchestratorSubsystem
void USeqsoOrchestratorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UWorld* World = GetWorld();
    UE_LOG(LogSEQSO_Orchestrator, Display, TEXT("OrchestratorSubsystem initialized for world %s"),
        World ? *World->GetName() : TEXT("<null>"));
}

void USeqsoOrchestratorSubsystem::Deinitialize()
{
    UWorld* World = GetWorld();
    UE_LOG(LogSEQSO_Orchestrator, Display, TEXT("OrchestratorSubsystem deinitialized for world %s"),
        World ? *World->GetName() : TEXT("<null>"));
    Super::Deinitialize();
}
#pragma endregion USeqsoOrchestratorSubsystem

