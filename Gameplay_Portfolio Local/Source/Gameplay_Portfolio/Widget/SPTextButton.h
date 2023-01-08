// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "SPTextButton.generated.h"


// 기존 UMG의 버튼은 블루프린트에선 함수 바인딩을 잘 지원하지만, C++을 통해 접근하면 SButton의 델리게이트는 추가적인 인자를 제공하지 않기 때문에 불편합니다.
// 자체 버튼 클래스를 통해 이를 개선했으며, 텍스트의 잦은 수정을 고려해 상위 클래스에서의 접근성을 향상시켰습니다.


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScopeOnClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScopeOnHoverd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScopeOnUnHoverd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScopeOnPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScopeOnReleased);

UCLASS(Blueprintable, BlueprintType)
class GAMEPLAY_PORTFOLIO_API USPTextButton : public UUserWidget
{

private:
	GENERATED_BODY()

public:
	//에디터와 인게임에서 위젯 초기화로 작동합니다.
	//UMG의 텍스트 프로퍼티가 수정될 때마다 텍스트 박스의 콘텐츠 텍스트를 수정합니다. 프로퍼티를 통해 하위 UMG에서 쉽게 접근가능합니다.
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;

#if WITH_EDITOR
	// PostEditChangeProperty를 활용하지 않아도 NativePreConstruct에서 text변수를 확인해 UMG를 업데이트하지만, 에디터에서 빠른 작업 확인이 가능하도록 구성했습니다.
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "버튼|기본",  meta = (DisplayPriority =0))
	class UButton* MainButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "버튼|기본",  meta = (DisplayPriority = 1))
	class UTextBlock* TextBlock;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Content Text", Category = "버튼|기본",  meta = (DisplayPriority = 2, BindWidget))
	FText text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "버튼|상호작용|클릭", meta = (DisplayPriority = 3))
	FColor ClickColor = FColor(255,255,255,255);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "버튼|상호작용|클릭", meta = (DisplayPriority = 4))
	int ClickSize;
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "버튼|상호작용|호버", meta = (DisplayPriority = 5))
	FColor HoverColor = FColor(255,255,255,255);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "버튼|상호작용|호버", meta = (DisplayPriority = 6))
	int HoverSize;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "버튼|상호작용|언호버", meta = (DisplayPriority = 7))
	FColor UnHoverColor = FColor(255,255,255,255);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "버튼|상호작용|언호버", meta = (DisplayPriority = 8))
	int UnHoverSize;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "버튼|상호작용|눌림", meta = (DisplayPriority = 9))
	FColor PressColor = FColor(255,255,255,255);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "버튼|상호작용|눌림", meta = (DisplayPriority = 10))
	int PressSize;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "버튼|상호작용|떼기", meta = (DisplayPriority = 11))
	FColor ReleaseColor = FColor(255,255,255,255);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "버튼|상호작용|떼기", meta = (DisplayPriority = 12))
	int ReleaseSize;
	
	FScopeOnClicked ScopeOnClicked;
	FScopeOnHoverd ScopeOnHoverd;
	FScopeOnUnHoverd ScopeOnUnHoverd;
	FScopeOnPressed ScopeOnPressed;
	FScopeOnReleased ScopeOnReleased;
	
	UFUNCTION(BlueprintCallable)
	void OnButtonClicked();

	UFUNCTION(BlueprintCallable)
	void OnButtonHoverd();
	
	UFUNCTION(BlueprintCallable)
	void OnButtonUnHoverd();

	UFUNCTION(BlueprintCallable)
	void OnButtonPressed();
	
	UFUNCTION(BlueprintCallable)
	void OnButtonReleased();

private:
	void TextColorChange(FColor color) const;

	void TextSizeChange(int size) const;
	
};
