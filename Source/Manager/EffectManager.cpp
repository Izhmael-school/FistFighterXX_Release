#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include"../Object/Effect/Effect.h"

EffectManager::EffectManager()
	:effectResourceMap()
	, pEffectList() {
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
}

EffectManager::~EffectManager() {


	for (auto& pEffe : pEffectList) {
		if (pEffe != nullptr) {
			pEffe.reset();
			pEffe = nullptr;
		}
	}
	pEffectList.clear();

}

/*
 * @function Load
 *  @brief		エフェクトの読み込み
 *  @param[in]	std::string _filepath
 *  @param[in]	std::string _name
 *  @param[in]	float _magnification = 1.0f
 */
void EffectManager::Load(std::string _filePath, std::string _name, float _magnification) {
	int res = LoadEffekseerEffect(_filePath.c_str(), _magnification);
	// リソースの管理
#if 0
	effectResourceMap[_filePath.c_str()] = res;
#else
	auto itr = effectResourceMap.find(_name.c_str());

	if (itr == effectResourceMap.end()) {
		// 登録
		effectResourceMap.emplace(_name.c_str(), res);
	}
#endif
}

/*
 * @function	Instantiate
 * @brief		エフェクトの発生
 * @param[in]	std::string _name
 * @param[in]	VECTOR _pos
 * @return		Effect*
 */
Effect* EffectManager::Instantiate(std::string _name, VECTOR _pos) {
	std::unique_ptr<Effect> pEffect = std::make_unique<Effect>(effectResourceMap[_name]);
	pEffect->GetTransform().SetPosition(_pos);
	pEffectList.push_back(std::move(pEffect));
	return pEffectList.back().get();
}

void EffectManager::Update() {
	for (auto& pEffe : pEffectList) {
		if (pEffe == nullptr || !pEffe->IsActive())
			continue;

		pEffe->Update();
	}

	// STLの要素を削除
	// std::erase_if( コンテナ, ラムダ)	C++20～ ここじゃ使えん
	// isVisible = false のものを消す
	std::erase_if(pEffectList, [](std::unique_ptr<Effect>& _pE) {
		if (_pE->IsActive()) return false;

		_pE.reset();
		return true; 
		});

	UpdateEffekseer3D();
}

void EffectManager::Render() {
	for (auto& pEffe : pEffectList) {
		if (pEffe == nullptr || !pEffe->IsActive())
			continue;

		pEffe->Render();
	}
	DrawEffekseer3D();
}

void EffectManager::DeleteData() {
	for (auto itr : effectResourceMap) {
		DeleteEffekseerEffect(itr.second);
	}
	effectResourceMap.clear();
}

