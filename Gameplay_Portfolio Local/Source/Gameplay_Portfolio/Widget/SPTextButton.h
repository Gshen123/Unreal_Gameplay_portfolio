// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "SPTextButton.generated.h"


// 기존 UMG의 버튼은 블루프린트에선 함수 바인딩을 잘 지원하지만, C++을 통해 접근하면 SButton의 델리게이트는 추가적인 인자를 제공하지 않기 때문에 불편합니다.
// 자체 버튼 클래스를 통해 이를 개선했으며, 텍스트의 잦은 수정을 고려해 상위 클래스에서의 접근성을 향상시켰습니다.


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScopeOnClicked, class USPTextButton*, Button);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScopeOnHoverd, class USPTextButton*, Button);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScopeOnUnHoverd, class USPTextButton*, Button);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScopeOnPressed, class USPTextButton*, Button);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScopeOnReleased, class USPTextButton*, Button);

UCLASS(Blueprintable, BlueprintType)
class GAMEPLAY_PORTFOLIO_API USPTextButton : public UUserWidget
{

private:
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;

	//텍스트 내용을 담은 프로퍼티가 수정될 때마다 즉각 TextBox의 내용이 동기화됩니다.
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;

	FScopeOnClicked ScopeOnClicked;
	FScopeOnHoverd ScopeOnHoverd;
	FScopeOnUnHoverd ScopeOnUnHoverd;
	FScopeOnPressed ScopeOnPressed;
	FScopeOnReleased ScopeOnReleased;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* MainButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Content Text")
	FText text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor ClickColor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor HoverColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor UnHoverColor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor ReleaseColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor PressColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* TextBlock;
	
	UFUNCTION(BlueprintCallable)
	void OnButtonClicked();

	UFUNCTION(BlueprintCallable)
	void OnButtonHoverd();
	
	UFUNCTION(BlueprintCallable)
	void OnButtonUnHoverd();

	UFUNCTION(BlueprintCallable)
	void OnButtonPressd();
	
	UFUNCTION(BlueprintCallable)
	void OnButtonReleased();

	void TextColorChange(FColor color) const;
	
};
