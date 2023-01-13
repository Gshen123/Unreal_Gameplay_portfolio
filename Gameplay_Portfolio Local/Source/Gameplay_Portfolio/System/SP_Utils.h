// Scope Portfolio. All rights reserved

#pragma once
#include "Gameplay_Portfolio//Player/SP_PlayerState.h"

/**
 * 
 */

class USP_Utils
{
public:
    template <typename  T>
    static T* GetSP_PlayerComponent(AActor* PlayerPawn)
    {
        if(!PlayerPawn) return nullptr;

        const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
        return Cast<T>(Component);
    }

    static FText TextFromInt(int32 Number) {return FText::FromString(FString::FromInt(Number));}
};
