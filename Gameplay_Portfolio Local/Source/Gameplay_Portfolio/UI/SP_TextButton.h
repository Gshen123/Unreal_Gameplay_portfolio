// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "SP_TextButton.generated.h"


// 자체 버튼 클래스를 통해 이를 개선했으며, 텍스트의 잦은 수정을 고려해 상위 클래스에서의 접근성을 향상시켰습니다.


UCLASS(Blueprintable, BlueprintType)
class GAMEPLAY_PORTFOLIO_API USP_TextButton : public UUserWidget
{
    
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
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|에셋",  meta = (DisplayPriority =0))
    class UButton* MainButton;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|에셋",  meta = (DisplayPriority = 1))
    class UTextBlock* TextBlock;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|텍스트")
    FText Text_Context;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|텍스트")
    int Text_FontSize = 15;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|텍스트")
    FColor Text_Color = FColor(0,0,0,255);
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|텍스트|외곽선")
    int Text_OutlineTextSize = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|텍스트|외곽선")
    FColor Text_OutlineTextColor = FColor(0,0,0,255);
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|텍스트|클릭")
    FColor Text_ClickColor = FColor(255,255,255,255);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|텍스트|클릭")
    int Text_ClickSize = 15;
	 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|텍스트|호버")
    FColor Text_HoverColor = FColor(255,255,255,255);
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|텍스트|호버")
    int Text_HoverSize = 15;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|텍스트|언호버")
    FColor Text_UnHoverColor = FColor(255,255,255,255);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|텍스트|언호버")
    int Text_UnHoverSize = 15;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|텍스트|눌림")
    FColor Text_PressColor = FColor(255,255,255,255);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|텍스트|눌림")
    int Text_PressSize = 15;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|텍스트|떼기")
    FColor Text_ReleaseColor = FColor(255,255,255,255);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|텍스트|떼기")
    int Text_ReleaseSize = 15;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|버튼")
    FColor Btn_NormalColor = FColor(255,255,255,0);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|버튼")
    FColor Btn_HoverColor = FColor(255,255,255,0);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|버튼")
    FColor Btn_PressColor = FColor(255,255,255,0);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|버튼")
    FColor Btn_DisabledColor = FColor(255,255,255,0);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|버튼")
    bool bBtn_OutlineRound = false;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|버튼")
    bool bBtn_RoundTypeisFixedRadius = true;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|버튼")
    FVector4 Btn_OutlineConerRad = FVector4(0,0,0,0);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|버튼", meta = (ToolTip = "0 = default, 1= hands, 2 = Grabhands, 3 = Grabhands closed", ClampMin = 0, ClampMax = 3, UIMin = 0, UIMax = 3))
    int Btn_CursorType = 0;
    
    UFUNCTION(BlueprintCallable)
    void SetText(FText Content);
	
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

    void SetButtonColor() const;

    void ChangeOutlineTextProperty() const;

    
};
