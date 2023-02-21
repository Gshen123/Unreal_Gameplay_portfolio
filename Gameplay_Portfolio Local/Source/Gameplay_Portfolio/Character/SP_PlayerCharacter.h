// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Gameplay_Portfolio/Animation/SP_AnimType.h"
#include "SP_PlayerCharacter.generated.h"



UCLASS()
class ASP_PlayerCharacter : public ACharacter
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Mesh", meta = (AllowPrivateAccess = "true"))
    class USP_MergeComponent* MergeComponent;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Camera", meta = (AllowPrivateAccess = "true"))
    class USP_CameraBoom* CameraBoom;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Camera", meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* FollowCamera;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Movement", meta = (AllowPrivateAccess = "true"))
    class UInputConfig* InputConfig;
    
    /** MappingContext */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Movement", meta = (AllowPrivateAccess = "true"))
    class UInputMappingContext* DefaultMappingContext;
    
public:
    ASP_PlayerCharacter();
    
    FSP_LocomotionInfo GetLocomotionInfo() const { return LocomotionInfo;}
    FORCEINLINE class USP_CameraBoom* GetCameraBoom() const { return CameraBoom; }
    FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
    
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION()
    void Input_Move(const FInputActionValue& Value);

    UFUNCTION()
    void Input_Zoom(const FInputActionValue& Value);

    UFUNCTION()
    void Input_Look(const FInputActionValue& Value);

    UFUNCTION()
    void Input_Jump();

    UFUNCTION()
    void Input_Sprint_Start();

    UFUNCTION()
    void Input_Sprint_Stop();

    void TurnAtRate(float Rate);
    void LookUpAtRate(float Rate);
    
    void UpdateLocomotionInfo();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Camera")
    float TurnRateGamepad = 45.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Movement")
    float MaxWalkingSpeed = 400.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Movement")
    float MaxSprintingSpeed = 600.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Movement", meta=(AllowPrivateAccess="true"))
    bool bBlockMoveInput = false;

private:
    
    UPROPERTY()
    FSP_LocomotionInfo LocomotionInfo;
};