#include "Misc/AutomationTest.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSeqsoEditorLoads, "SEQSO.Editor.Loads",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FSeqsoEditorLoads::RunTest(const FString&)
{
    if (!FModuleManager::Get().IsModuleLoaded("SuperEQSOrchestratorEditor"))
    {
        FModuleManager::Get().LoadModule("SuperEQSOrchestratorEditor");
    }
    const bool bLoaded = FModuleManager::Get().IsModuleLoaded("SuperEQSOrchestratorEditor");
    TestTrue(TEXT("Editor module loaded"), bLoaded);
    return true;
}

