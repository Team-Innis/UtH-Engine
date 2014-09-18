#pragma once
#ifndef INPUTTOUCH_H_UTH
#define INPUTTOUCH_H_UTH

#include <UtH/Platform/Common/InputBase.hpp>
#include <pmath/Vector2.hpp>

namespace uth
{
	enum class TouchMotion
	{
		NONE = 0,
		STATIONARY,
		TAP,
		DRAG,
		PINCH_IN,
		PINCH_OUT,
		MULTIPLE,
		RELEASE
	};

	class TouchInput : public InputBase
	{
	private:
		class TouchUnit
		{
			friend class TouchInput;
		private:
			TouchMotion m_motion;
		public:
			const TouchMotion Motion() const;
			const int GetStartIndex() const;
			const pmath::Vec2 GetStartPosition() const;
			const pmath::Vec2 GetPosition() const;
			const pmath::Vec2 GetEndPosition() const;
		};
		TouchUnit ID[10];
	public:
		const TouchMotion Motion() const;
		void Update(float dt);
		const TouchUnit& operator[](unsigned int id) const;
	};
}

#endif