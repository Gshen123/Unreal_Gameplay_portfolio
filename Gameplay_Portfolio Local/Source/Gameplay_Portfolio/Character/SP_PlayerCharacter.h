// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Gameplay_Portfolio/Camera/SP_PlayerCameraManager.h"
#include "SP_PlayerCharacter.generated.h"



UCLASS()
class ASP_PlayerCharacter : public ACharacter
{
    GENERATED_BODY()

    /** Camera boom positioning the camera behind the character */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* CameraBoom;

    /** Follow camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* FollowCamera;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputConfig* InputConfig;
    
    /** MappingContext */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputMappingContext* DefaultMappingContext;
    
public:
    ASP_PlayerCharacter();

public:
    /** Returns CameraBoom subobject **/
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    /** Returns FollowCamera subobject **/
    FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

    void ToggleCameraMode();
    
protected:
    
    // APawn interface
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
    // To add mapping context
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
    class USP_MergeComponent* MergeComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
    float ZOOM_MIN_VALUE = 60.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
    float ZOOM_MAX_VALUE = 320.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
    float ZOOM_MULTIPLE = 16.f;
    
protected:

    /** Called for movement input */
    void Input_Move(const FInputActionValue& Value);
    void Input_Jump();
    void Input_Zoom(const FInputActionValue& Value);
    void Input_Look(const FInputActionValue& Value);

    void TurnAtRate(float Rate);
    void LookUpAtRate(float Rate);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    float TurnRateGamepad = 45.f;
    
private:

    UPROPERTY()
    bool bCanMove = true;

    UPROPERTY()
    ASP_PlayerCameraManager* CameraManager;
};