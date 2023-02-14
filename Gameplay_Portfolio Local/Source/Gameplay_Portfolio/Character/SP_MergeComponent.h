// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_MergeComponent.generated.h"

// 필요한 메시를 병합한 뒤, 리더포즈 컴포넌트 기능을 활용해 애니메이션을 일치시키는 기능을 담당합니다.
// 대부분의 로직은 로컬플레이어 메시 매니저에 구현되며, 컴포넌트는 매니저를 통해 관리됩니다.
// 멀티플레이어에서 각 로컬 플레이어별로 캐릭터 구성 시, 고유한 메시정보를 불러올 수 있습니다.
// 다만 게임디자인에 따라, 한 클라이언트가 여러 유형의 스켈레탈 메시 병합이 필요하다면 확장이 필요합니다. 
UCLASS(BlueprintType)
class GAMEPLAY_PORTFOLIO_API USP_MergeComponent : public USkeletalMeshComponent
{

private:
    GENERATED_BODY()

public:
    
    virtual void BeginPlay() override;
    
    USkeletalMeshComponent* GetOwnerMesh() const;

    UFUNCTION()
    void SetOwnerMorphTarget(FName MorphTargetName, float Value, bool RemoveWeight = true) const;

    UFUNCTION()
    void ClearMorphTarget() const;

    void UpdateAnimation(UAnimationAsset* Asset) const;
};
