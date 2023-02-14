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
    AddTag(Input_MouseAndKeyboard_Move, "Input.MouseAndKeyboard.Move", "Move input.");
    AddTag(Input_MouseAndKeyboard_Look, "Input.MouseAndKeyboard.Look", "Look input.");
    AddTag(Input_MouseAndKeyboard_Jump, "Input.MouseAndKeyboard.Jump", "Jump input.");
    AddTag(Input_MouseAndKeyboard_Zoom, "Input.MouseAndKeyboard.Zoom", "Zoom input.");
    AddTag(Input_MouseAndKeyboard_PauseAndUndo, "Input.MouseAndKeyboard.PauseAndUndo", "PauseAndUndo input.");
}

void FSP_GameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
    OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}
