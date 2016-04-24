using UnrealBuildTool;

public class BattleGameLoadingScreen:ModuleRules
{
    public BattleGameLoadingScreen(TargetInfo Target)
    {
        PrivateIncludePaths.Add("../../BattleDemo/Source/BattleLoadingScreen");

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "MoviePlayer",
                "Slate",
                "SlateCore",
                "InputCore"
            }
            );

    }
}