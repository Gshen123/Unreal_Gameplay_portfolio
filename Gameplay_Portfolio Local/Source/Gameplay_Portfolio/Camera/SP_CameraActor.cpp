// Scope Portfolio. All rights reserved


#include "SP_CameraActor.h"


// Sets default values
ASP_CameraActor::ASP_CameraActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASP_CameraActor::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void ASP_CameraActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

