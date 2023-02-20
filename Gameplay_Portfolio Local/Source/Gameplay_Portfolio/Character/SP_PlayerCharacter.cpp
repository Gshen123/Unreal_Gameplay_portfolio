// Copyright Epic Games, Inc. All Rights Reserved.

#include "SP_PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MathUtil.h"
#include "SP_GameplayTags.h"
#include "SP_MergeComponent.h"
#include "Gameplay_Portfolio/EnhancedInput/SP_InputComponent.h"


//////////////////////////////////////////////////////////////////////////
// AGameplay_PortfolioCharacter

ASP_PlayerCharacter::ASP_PlayerCharacter()
{
    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // Don't rotate when the controller rotates. Let that just affect the camera.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

    // Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
    // instead of recompiling to adjust them
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

    // Create a camera boom (pulls in towards the player if there is a collision)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
    CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

    // Create a follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
    FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
      // Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
      // are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
    MergeComponent = CreateDefaultSubobject<USP_MergeComponent>(TEXT("MeshComponent"));
    MergeComponent->SetupAttachment(GetMesh());
}

void ASP_PlayerCharacter::BeginPlay()
{
    // Call the base class  
    Super::BeginPlay();
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASP_PlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    const FSP_GameplayTags& GameplayTags = FSP_GameplayTags::Get();
    const APlayerController* PlayerController = Cast<APlayerController>(GetController());
    check(PlayerController);
    
    // //Add Input Mapping Context
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
    {
        Subsystem->ClearAllMappings();
        Subsystem->AddMappingContext(DefaultMappingContext, 0);
    }
    
    USP_InputComponent* EnhancedInputComponent = Cast<USP_InputComponent>(PlayerInputComponent);
    check(EnhancedInputComponent);
    
    // Set up action bindings
    EnhancedInputComponent->BindActionNativeAction(InputConfig, GameplayTags.Input_MouseAndKeyboard_Move, ETriggerEvent::Triggered, this, &ASP_PlayerCharacter::Input_Move);
    EnhancedInputComponent->BindActionNativeAction(InputConfig, GameplayTags.Input_MouseAndKeyboard_Look, ETriggerEvent::Triggered, this, &ASP_PlayerCharacter::Input_Look);
    EnhancedInputComponent->BindActionNativeAction(InputConfig, GameplayTags.Input_MouseAndKeyboard_Jump, ETriggerEvent::Triggered, this, &ASP_PlayerCharacter::Input_Jump);
    EnhancedInputComponent->BindActionNativeAction(InputConfig, GameplayTags.Input_MouseAndKeyboard_Zoom, ETriggerEvent::Triggered, this, &ASP_PlayerCharacter::Input_Zoom);
}

void ASP_PlayerCharacter::Input_Move(const FInputActionValue& Value)
{
    // input is a Vector2D
    const FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr && bCanMove)
    {
        // find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get forward vector
        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
        // get right vector 
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        // add movement 
        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

void ASP_PlayerCharacter::Input_Jump()
{
    if(bCanMove) Jump();
}

void ASP_PlayerCharacter::Input_Zoom(const FInputActionValue& Value)
{
    const float MultiValue = Value.GetMagnitude() * ZOOM_MULTIPLE;
    CameraBoom->TargetArmLength += MultiValue;
    
    if(CameraBoom->TargetArmLength < ZOOM_MIN_VALUE) CameraBoom->TargetArmLength = ZOOM_MIN_VALUE;
    if(CameraBoom->TargetArmLength > ZOOM_MAX_VALUE) CameraBoom->TargetArmLength = ZOOM_MAX_VALUE;
}

void ASP_PlayerCharacter::Input_Look(const FInputActionValue& Value)
{
    if (Controller != nullptr)
    {
        // input is a Vector2D
        const FVector2D LookValue = Value.Get<FVector2D>();
        
        if (LookValue.X != 0.0f) TurnAtRate(LookValue.X);
        if (LookValue.Y != 0.0f && bCanMove) LookUpAtRate(LookValue.Y);
    }
}

void ASP_PlayerCharacter::TurnAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ASP_PlayerCharacter::LookUpAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ASP_PlayerCharacter::ToggleCameraMode()
{
    bCanMove = !bCanMove;
}
