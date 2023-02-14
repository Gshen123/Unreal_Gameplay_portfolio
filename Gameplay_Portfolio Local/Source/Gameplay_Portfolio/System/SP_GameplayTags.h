// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 
 */
class UGameplayTagsManager;
 
struct FSP_GameplayTags
{
public:
    static const FSP_GameplayTags& Get() { return GameplayTags;}
    static void InitializeNativeTags();

    //Input Tags
    FGameplayTag Input_MouseAndKeyboard_Move;
    FGameplayTag Input_MouseAndKeyboard_Look;
    FGameplayTag Input_MouseAndKeyboard_Jump;
    FGameplayTag Input_MouseAndKeyboard_Zoom;
    FGameplayTag Input_MouseAndKeyboard_PauseAndUndo;
    
protected:

    //Registers all of the tags with the GameplayTags Manager
    void AddAllTags(UGameplayTagsManager& Manager);

    //Helper function used by AddAllTags to register a single tag with the GameplayTags Manager
    void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);

private:

    static FSP_GameplayTags GameplayTags;
};
