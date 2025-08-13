using UnrealBuildTool;

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
