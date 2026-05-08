#pragma once
#include "DxLib.h"

class MyVECTOR {
public:

	/// <summary>
	/// v1‚Æ”äŠr‚µ‚Äv2‚Ì‚·‚×‚Ä‚Ì’l‚ª‘å‚«‚¢‚©
	/// </summary>
	static bool CompareVECTORToSize(VECTOR v1, VECTOR v2);

	static bool CompareVECTORToEqual(VECTOR _vec1, VECTOR _vec2);

	/// <summary>
	/// x‚Æy‚Ì—v‘f‚ð“ü‚ê‘Ö‚¦‚é
	/// </summary>
	static VECTOR ChangeElementXY(VECTOR& v);

	/// <summary>
	/// y‚Æz‚Ì—v‘f‚ð“ü‚ê‘Ö‚¦‚é
	/// </summary>
	static VECTOR ChangeElementYZ(VECTOR& v);

	/// <summary>
	/// x‚Æz‚Ì—v‘f‚ð“ü‚ê‘Ö‚¦‚é
	/// </summary>
	static VECTOR ChangeElementXZ(VECTOR& v);

	static VECTOR VAddFloat(VECTOR v, float f);

	static VECTOR VSubFloat(VECTOR v, float f);

	static VECTOR VDiv(VECTOR _v1, VECTOR _v2);
};

