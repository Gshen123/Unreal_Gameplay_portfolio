// Copyright Epic Games, Inc. All Rights Reserved.

#include "SP_PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MathUtil.h"
#include "SP_GameplayTags.h"
#include "SP_PlayerState.h"
#include "Components/SP_CameraBoom.h"
#include "Gameplay_Portfolio/EnhancedInput/SP_InputComponent.h"
#include "Kismet/KismetMathLibrary.h"


//////////////////////////////////////////////////////////////////////////
// AGameplay_PortfolioCharacter

ASP_PlayerCharacter::ASP_PlayerCharacter()
{
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
    
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;
    
    GetCharacterMovement()->bOrientRotationToMovement = true;	
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
    
    CameraBoom = CreateDefaultSubobject<USP_CameraBoom>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->bUsePawnControlRotation = true; 
    
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USP_CameraBoom::SocketName);
    FollowCamera->bUsePawnControlRotation = false;
    
    MergeComponent = CreateDefaultSubobject<USP_MergeComponent>(TEXT("MeshComponent"));
    MergeComponent->SetupAttachment(GetMesh());
}

void ASP_PlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    if(GetPlayerState<ASP_PlayerState>()->GetCurrentGameModeType() == EGameModeType::CharacterSetup)
    {
        CameraBoom->SetCamMoveMode(ESP_CameraMode::CharacterSetting);
        bBlockMoveInput = true;
    }
}

void ASP_PlayerCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    UpdateLocomotionInfo();
}

void ASP_PlayerCharacter::UpdateLocomotionInfo()
{
    LocomotionInfo.GroundSpeed = GetVelocity().Size2D();
    
    if(LocomotionInfo.GroundSpeed > 0.f && UKismetMathLibrary::NotEqual_VectorVector(GetCharacterMovement()->GetCurrentAcceleration(), FVector::ZeroVector))
        LocomotionInfo.bIsMoving = true;
    else LocomotionInfo.bIsMoving = false;

    LocomotionInfo.bIsInAir = GetCharacterMovement()->IsFalling();
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASP_PlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    const FSP_GameplayTags& GameplayTags = FSP_GameplayTags::Get();
    const APlayerController* PlayerController = Cast<APlayerController>(GetController());
    check(PlayerController);
    
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
    {
        Subsystem->ClearAllMappings();
        Subsystem->AddMappingContext(DefaultMappingContext, 0);
    }
    
    USP_InputComponent* EnhancedInputComponent = Cast<USP_InputComponent>(PlayerInputComponent);
    check(EnhancedInputComponent);
    
    EnhancedInputComponent->BindActionNativeAction(InputConfig, GameplayTags.Input_MouseAndKeyboard_Move, ETriggerEvent::Triggered, this, &ASP_PlayerCharacter::Input_Move);
    EnhancedInputComponent->BindActionNativeAction(InputConfig, GameplayTags.Input_MouseAndKeyboard_Look, ETriggerEvent::Triggered, this, &ASP_PlayerCharacter::Input_Look);
    EnhancedInputComponent->BindActionNativeAction(InputConfig, GameplayTags.Input_MouseAndKeyboard_Jump, ETriggerEvent::Triggered, this, &ASP_PlayerCharacter::Input_Jump);
    EnhancedInputComponent->BindActionNativeAction(InputConfig, GameplayTags.Input_MouseAndKeyboard_Zoom, ETriggerEvent::Triggered, this, &ASP_PlayerCharacter::Input_Zoom);
    EnhancedInputComponent->BindActionNativeAction(InputConfig, GameplayTags.Input_MouseAndKeyboard_Sprint, ETriggerEvent::Triggered, this, &ASP_PlayerCharacter::Input_Sprint_Start);
    EnhancedInputComponent->BindActionNativeAction(InputConfig, GameplayTags.Input_MouseAndKeyboard_Sprint, ETriggerEvent::Completed, this, &ASP_PlayerCharacter::Input_Sprint_Stop);
}

void ASP_PlayerCharacter::Input_Move(const FInputActionValue& Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr && !bBlockMoveInput)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        
        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        
        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

void ASP_PlayerCharacter::Input_Jump()
{
    if(!bBlockMoveInput) Jump();
}

void ASP_PlayerCharacter::Input_Sprint_Start()
{
    GetCharacterMovement()->MaxWalkSpeed = MaxSprintingSpeed;
}

void ASP_PlayerCharacter::Input_Sprint_Stop()
{
    GetCharacterMovement()->MaxWalkSpeed = MaxWalkingSpeed;
}

void ASP_PlayerCharacter::Input_Zoom(const FInputActionValue& Value)
{
    CameraBoom->CameraZoom(Value.GetMagnitude());
}

void ASP_PlayerCharacter::Input_Look(const FInputActionValue& Value)
{
    if (Controller != nullptr)
    {
        const FVector2D LookValue = Value.Get<FVector2D>();
        
        if (LookValue.X != 0.0f) TurnAtRate(LookValue.X);
        if (LookValue.Y != 0.0f) LookUpAtRate(LookValue.Y);
    }
}

void ASP_PlayerCharacter::TurnAtRate(float Rate)
{
    AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ASP_PlayerCharacter::LookUpAtRate(float Rate)
{
    AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}
