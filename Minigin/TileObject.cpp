#pragma once
#include <memory>

#include "Transform.h"
#include "Texture2D.h"
#include "SceneObject.h"
#include "GameObject.h"
#include "MiniginPCH.h"
namespace dae
{
	class TileObject : public GameObject
	{
	public:
		TileValue GetTileValue() { return m_Value; }
		void SetTileValue(TileValue value) { m_Value = value; }
		bool HasBeenDug() { return m_IsDug; }
		void Dig() { m_IsDug = true; }
	private:

		TileValue m_Value;
		bool m_IsDug = false;
	};

}

