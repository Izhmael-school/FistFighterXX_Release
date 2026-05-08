#pragma once
#include <memory>
#include "../Definition.h"
#include <functional>

class Collider;

class ColliderObjectUtility {
public:
	static void Update();

	static void Register(std::unique_ptr<Collider> _pCol, float _lifeTime,std::function<void(Collider* _pOhter)> _func ,Tag _tag = NoTag);
};

