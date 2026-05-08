#pragma once

class Collider;

class CollisionUtility {
public:
	static void Update();
	static void Render();
	static void Register(Collider* _pCol);
	static void UnRegister(Collider* _pCol);
	static void UnRegisterAll();
};

