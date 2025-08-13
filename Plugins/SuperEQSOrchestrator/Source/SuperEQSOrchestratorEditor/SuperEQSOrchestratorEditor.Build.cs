using UnrealBuildTool;

public class SuperEQSOrchestratorEditor : ModuleRules
{
    public SuperEQSOrchestratorEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core", "CoreUObject", "Engine"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "UnrealEd", "Slate", "SlateCore", "LevelEditor"
        });
    }
}

