# -*- coding: utf-8 -*-
"""
Creates the SuperEQSOrchestrator plugin skeleton (non-UE Python).
Run from repo root or pass --root <path>. Writes:
- Plugins/SuperEQSOrchestrator/SuperEQSOrchestrator.uplugin
- .../Source/SuperEQSOrchestrator/SuperEQSOrchestrator.Build.cs
- .../Public/SeqsoVersion.h, SuperEQSOrchestrator.h
- .../Private/SuperEQSOrchestratorModule.cpp, SeqsoTests.cpp
"""
import argparse, os, pathlib, sys

UPLUGIN = r'''{
  "FileVersion": 3,
  "Version": 100,
  "VersionName": "0.1.0",
  "FriendlyName": "Super-EQSOrchestrator",
  "Description": "Centralized, budgeted EQS orchestration so game teams never touch EQS directly.",
  "Category": "AI",
  "EnabledByDefault": true,
  "Modules": [
    { "Name": "SuperEQSOrchestrator", "Type": "Runtime", "LoadingPhase": "Default" }
  ],
  "SupportedTargetPlatforms": [ "Win64", "Linux", "Mac", "Android", "IOS" ]
}
'''

BUILD_CS = r'''using UnrealBuildTool;

public class SuperEQSOrchestrator : ModuleRules
{
    public SuperEQSOrchestrator(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
        PrivateDependencyModuleNames.AddRange(new string[] { });

        // Export macro alias so public headers can use SEQSO_API
        PublicDefinitions.Add("SEQSO_API=SUPEREQSORCHESTRATOR_API");
    }
}
'''

SEQSO_VERSION_H = r'''#pragma once
/**
 * Summary: Defines plugin version and friendly name for Super-EQSOrchestrator.
 * Usage: Include for logs/tests to assert/display version.
 * Thread-safety: Compile-time constants.
 * Errors/Logs: None.
 * Performance: Trivial.
 */
#define SEQSO_VERSION TEXT("0.1.0")
#define SEQSO_PLUGIN_FRIENDLY_NAME TEXT("Super-EQSOrchestrator")
'''

MODULE_H = r'''#pragma once
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
'''

MODULE_CPP = r'''#include "SuperEQSOrchestrator.h"
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
'''

TEST_CPP = r'''#include "Misc/AutomationTest.h"
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
'''

def write(p: pathlib.Path, content: bytes | str) -> None:
    p.parent.mkdir(parents=True, exist_ok=True)
    if isinstance(content, (bytes, bytearray)):
        with open(p, "wb") as f:
            f.write(content)
    else:
        with open(p, "w", encoding="utf-8", newline="\n") as f:
            f.write(content)

def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--root", default=os.getcwd(), help="Repo root (default: cwd)")
    args = ap.parse_args()

    root = pathlib.Path(args.root).resolve()
    base = root / "Plugins" / "SuperEQSOrchestrator"
    src = base / "Source" / "SuperEQSOrchestrator"
    pub = src / "Public"
    prv = src / "Private"

    write(base / "SuperEQSOrchestrator.uplugin", UPLUGIN)
    write(src / "SuperEQSOrchestrator.Build.cs", BUILD_CS)
    write(pub / "SeqsoVersion.h", SEQSO_VERSION_H)
    write(pub / "SuperEQSOrchestrator.h", MODULE_H)
    write(prv / "SuperEQSOrchestratorModule.cpp", MODULE_CPP)
    write(prv / "SeqsoTests.cpp", TEST_CPP)

    print("[SEQSO] BOOTSTRAP: created plugin skeleton at", str(base))
    return 0

if __name__ == "__main__":
    sys.exit(main())
