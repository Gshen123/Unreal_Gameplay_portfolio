// Scope Portfolio. All rights reserved


#include "SP_InputConfig.h"

const UInputAction* UInputConfig::FindInputActionForTag(const FGameplayTag& InputTag) const
{
    for (const FTaggedInputAction& TaggedInputAction : TaggedInputActions)
    {
        //if (TaggedInputAction.InputAction && TaggedInputAction.InputTag == InputTag)

        //FName st = InputTag.GetTagName();
        if (TaggedInputAction.InputAction && TaggedInputAction.InputTag == InputTag)
        {
            return TaggedInputAction.InputAction;
        }
    }

    return nullptr;
}