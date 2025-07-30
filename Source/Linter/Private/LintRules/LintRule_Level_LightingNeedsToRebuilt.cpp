// Copyright (c) 2021-2025, Forschungszentrum Jülich GmbH. All rights reserved.


#include "LintRules/LintRule_Level_LightingNeedsToRebuilt.h"
#include "EngineModule.h"

ULintRule_Level_LightingNeedsToRebuilt::ULintRule_Level_LightingNeedsToRebuilt(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    bRequiresGameThread = true;
}

bool ULintRule_Level_LightingNeedsToRebuilt::PassesRule(UObject* ObjectToLint, const ULintRuleSet* ParentRuleSet, TArray<FLintRuleViolation>& OutRuleViolations) const {
    if (!Cast<UWorld>(ObjectToLint)) {
        return true;
    }
    
    return Super::PassesRule(ObjectToLint, ParentRuleSet, OutRuleViolations);
}

bool ULintRule_Level_LightingNeedsToRebuilt::PassesRule_Internal_Implementation(UObject* ObjectToLint, const ULintRuleSet* ParentRuleSet, TArray<FLintRuleViolation>& OutRuleViolations) const {
    UWorld* World = CastChecked<UWorld>(ObjectToLint);
    
    GetRendererModule().UpdateMapNeedsLightingFullyRebuiltState(World);
    if (World->NumLightingUnbuiltObjects > 0 || World->NumUnbuiltReflectionCaptures > 0) {
        const FText RecommendedAction = NSLOCTEXT("Linter", "LintRule_Level_LightingNeedsToRebuilt", "Rebuild the Lighting of {0}");
        OutRuleViolations.Push(
            FLintRuleViolation(ObjectToLint, GetClass(), FText::FormatOrdered(RecommendedAction, FText::FromString(World->GetMapName())))
        );
        return false;
    }
    
    return true;
}