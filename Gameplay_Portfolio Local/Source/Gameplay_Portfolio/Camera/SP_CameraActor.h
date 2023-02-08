// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "SP_CameraActor.generated.h"

UCLASS()
class GAMEPLAY_PORTFOLIO_API ASP_CameraActor : public ACameraActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ASP_CameraActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
