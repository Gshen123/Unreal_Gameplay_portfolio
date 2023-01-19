// Scope Portfolio. All rights reserved

#pragma once

#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
//#include "SP_SaveGameArchive.generated.h"

/**
 /  아카이브를 통해 객체 정보를 변환합니다.
 */
struct FSP_SaveGameArchive : public FObjectAndNameAsStringProxyArchive
{
    FSP_SaveGameArchive(FArchive& InInnerArchive) :
    FObjectAndNameAsStringProxyArchive(InInnerArchive, true)
    {
        ArIsSaveGame = true;
        ArNoDelta = true;                                                                                                                  
        // 선택 사항. 레벨을 재설정하지 않고 변수를 저장/로드할 때 유용합니다.
        // 수정되지 않은 변수를 직렬화하고 기본값을 유지합니다.
    }
};
