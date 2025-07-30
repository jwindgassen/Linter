// Copyright (c) 2021-2025, Forschungszentrum Jülich GmbH. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "LintRule.h"
#include "LintRule_Level_LightingNeedsToRebuilt.generated.h"


UCLASS(BlueprintType, Blueprintable)
class LINTER_API ULintRule_Level_LightingNeedsToRebuilt : public ULintRule {
    GENERATED_BODY()

public:
    ULintRule_Level_LightingNeedsToRebuilt(const FObjectInitializer& ObjectInitializer);
    
    virtual bool PassesRule(UObject* ObjectToLint, const ULintRuleSet* ParentRuleSet, TArray<FLintRuleViolation>& OutRuleViolations) const override;
    
protected:
    virtual bool PassesRule_Internal_Implementation(UObject* ObjectToLint, const ULintRuleSet* ParentRuleSet, TArray<FLintRuleViolation>& OutRuleViolations) const override;
};
