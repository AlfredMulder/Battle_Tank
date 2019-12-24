// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class BattleTankEditorTarget : TargetRules
{
    public BattleTankEditorTarget(TargetInfo Target) : base(Target)
    {
        DefaultBuildSettings = BuildSettingsVersion.V2;

        Type = TargetType.Editor;

        ExtraModuleNames.AddRange(new string[] {"BattleTank"});
    }
}