#include "StageGenerator.h"
#include "DxLib.h"
#include "../Definition.h"
#include "../Other/CommonModule/MyString.h"
#include "../Object/GameObject/Stage/StageBase.h"

StageGenerator::StageGenerator() 
	:originModelHandleArray()
{ LoadModel(); }

void StageGenerator::LoadModel() {
	for (int i = 0; i < STAGE_NUM; i++) {
		originModelHandleArray.push_back(MV1LoadModel(MyString::MergeString(STAGE_FILEPATH.data(), STAGE_FILENAME->data(), MODEL_FILE_EXTENSION.data()).c_str()));
	}
}

std::unique_ptr<StageBase> StageGenerator::Create(int _stageNum) {
	if (_stageNum >= STAGE_NUM) return nullptr;

	std::unique_ptr<StageBase> stage = std::make_unique<StageBase>(originModelHandleArray[_stageNum]);

	return stage;
}

void StageGenerator::DeleteOriginModelHandle() {
	for (int i = 0; i < STAGE_NUM; i++) {
		MV1DeleteModel(originModelHandleArray[i]);
	}
}
