// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_InputConfig.h"
#include "UObject/Object.h"
#include "SP_InputComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_InputComponent : public UObject
{
    GENERATED_BODY()

public:
	
    template<class UserClass, typename FuncType>
    void BindActionNativeAction(const UInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func);
	
};

template<class UserClass, typename FuncType>
void USP_InputComponent::BindActionNativeAction(const UInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func)
{
    check(InputConfig);
    if (const UInputAction* IA = InputConfig->FindInputActionForTag(InputTag))
    {
        BindAction(IA, TriggerEvent, Object, Func);
    }
}
