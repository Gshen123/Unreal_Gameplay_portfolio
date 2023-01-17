// Scope Portfolio. All rights reserved


#include "SP_MergeComponent.h"


// Sets default values for this component's properties
USP_MergeComponent::USP_MergeComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}


// Called when the game starts
void USP_MergeComponent::BeginPlay()
{
    Super::BeginPlay();

    // ...
    
}


// Called every frame
void USP_MergeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

