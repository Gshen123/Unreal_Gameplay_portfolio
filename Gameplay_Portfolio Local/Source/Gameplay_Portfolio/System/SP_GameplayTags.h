﻿// Scope Portfolio. All rights reserved

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

    FGameplayTag InputTag_Move;
    
protected:

    //Registers all of the tags with the GameplayTags Manager
    void AddAllTags(UGameplayTagsManager& Manager);

    //Helper function used by AddAllTags to register a single tag with the GameplayTags Manager
    void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);

private:

    static FSP_GameplayTags GameplayTags;
};