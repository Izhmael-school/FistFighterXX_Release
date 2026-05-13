#pragma once
#include <string>
#include <list>
#include <map>
#include <DxLib.h>
#include "../Component/Singleton.h"
#include "ManagerBase.h"
#include <memory>

class Effect;

class EffectManager : public Singleton<EffectManager> , public ManagerBase{

public:	// コンストラクタとデストラクタ
	/*
	 * @brief	コンストラクタ
	 * @tip		外部で生成されないようにアクセス指定子をprivateにする
	 */
	EffectManager();

	/*
	 * @brief	デストラクタ
	 */
	~EffectManager();

private:
	std::map<std::string, int> effectResourceMap;	// リソースの連想配列
	std::list<std::unique_ptr<Effect>> pEffectList;		// エフェクトの一元管理

public:

	// エフェクトの読み込み
	void Load(std::string _filePath, std::string _name, float _magnification = 1.0f);

	// エフェクトの発生
	Effect* Instantiate(std::string _name, VECTOR _pos);

	void Update() override;

	void Render() override;

	void DeleteAllEffect();

	void DeleteData() override;

};

