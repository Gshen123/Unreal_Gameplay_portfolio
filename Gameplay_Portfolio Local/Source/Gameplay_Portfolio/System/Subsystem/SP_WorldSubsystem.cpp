// Scope Portfolio. All rights reserved


#include "SP_WorldSubsystem.h"

void USP_WorldSubsystem::AddMergeComponent(UMergeComponent* Component)
{
    MergeComponents.AddUnique(Component);
}

TArray<UMergeComponent*> USP_WorldSubsystem::GetMergeComponents()
{
    return MergeComponents;
}
