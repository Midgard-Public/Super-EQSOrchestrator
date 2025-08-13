using UnrealBuildTool;

public class SuperEQSOrchestrator : ModuleRules
{
    public SuperEQSOrchestrator(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "DeveloperSettings" });
        PrivateDependencyModuleNames.AddRange(new string[] { "AIModule", "GameplayTasks", "NavigationSystem" });

        // Allow public headers to use SEQSO_API.
        PublicDefinitions.Add("SEQSO_API=SUPEREQSORCHESTRATOR_API");
    }
}

