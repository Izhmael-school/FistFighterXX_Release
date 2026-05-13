#include "ArmUtility.h"
#include "../Object/GameObject/Arm/ArmBase.h"

void ArmUtility::UnuseArm(ArmBase* _arm) {
    ArmManager::GetInstance().UnuseArm(_arm);
}

ArmBase* ArmUtility::UseArm(ArmType _type, Player* _owner, ArmPos pos, std::string _attachFrameName) {
    return ArmManager::GetInstance().UseArm(_type,_owner, pos,_attachFrameName);
}

int ArmUtility::GetArmGraphHandle(ArmType _arm) {
    return ArmManager::GetInstance().GetArmGraphHandle(_arm);
}

ArmData ArmUtility::GetArmData(ArmType _arm) {
    return ArmManager::GetInstance().GetArmData(static_cast<int>(_arm));
}

void ArmUtility::DeleteData() {
    ArmManager::GetInstance().DeleteData();
}
