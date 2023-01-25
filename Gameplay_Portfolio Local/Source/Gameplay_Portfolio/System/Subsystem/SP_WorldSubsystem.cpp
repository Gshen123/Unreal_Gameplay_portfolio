// Scope Portfolio. All rights reserved


#include "SP_WorldSubsystem.h"

bool USP_WorldSubsystem::AddMergeComponent(UMergeComponent* Component)
{
    return MergeComponents.AddUnique(Component);
}

TArray<UMergeComponent*> USP_WorldSubsystem::GetMergeComponents()
{
    return MergeComponents;
}
