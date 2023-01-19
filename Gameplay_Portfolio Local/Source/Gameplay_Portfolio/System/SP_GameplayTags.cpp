// Scope Portfolio. All rights reserved


#include "SP_GameplayTags.h"
#include "GameplayTagsManager.h"

FSP_GameplayTags FSP_GameplayTags::GameplayTags;

void FSP_GameplayTags::InitializeNativeTags()
{
    UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();
    
    GameplayTags.AddAllTags(GameplayTagsManager);
    
    GameplayTagsManager.DoneAddingNativeTags();
}

void FSP_GameplayTags::AddAllTags(UGameplayTagsManager& Manager)
{
    AddTag(InputTag_Move, "InputTag.Move", "Move input.");
}

void FSP_GameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
    OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}
