#include "Misc/AutomationTest.h"
#include "Modules/ModuleManager.h"
#include "SeqsoVersion.h"

/**
 * Summary: Sanity test that the module loads and version macro matches.
 * Usage: Run via Session Frontend → Automation or headless command line.
 * Performance: Trivial.
 */
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSeqsoLoads, "SEQSO.Basic.Loads",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FSeqsoLoads::RunTest(const FString&)
{
    if (!FModuleManager::Get().IsModuleLoaded("SuperEQSOrchestrator"))
    {
        FModuleManager::Get().LoadModule("SuperEQSOrchestrator");
    }
    TestTrue(TEXT("Module loaded"), FModuleManager::Get().IsModuleLoaded("SuperEQSOrchestrator"));
    TestEqual(TEXT("Version macro"), FString(SEQSO_VERSION), FString(TEXT("0.1.0")));
    return true;
}
