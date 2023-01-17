// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "SP_InputConfig.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FTaggedInputAction
{
    GENERATED_BODY()

public:

    UPROPERTY(EditDefaultsOnly)
    const UInputAction* InputAction = nullptr;

    UPROPERTY(EditDefaultsOnly, Meta = (Categories = "InputTag"))
    FGameplayTag InputTag;
};

/**
 *
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API UInputConfig : public UDataAsset
{
    GENERATED_BODY()

public:
    // Returns the first Input Action associated with a given tag.
    const UInputAction* FindInputActionForTag(const FGameplayTag& InputTag) const;

public:
    // List of input actions used by the owner. These input actions are mapped to a gameplay tag and must be manually bound.
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
    TArray<FTaggedInputAction> TaggedInputActions;
};