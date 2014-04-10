#pragma once
#ifndef INPUTTOUCH_H_UTH
#define INPUTTOUCH_H_UTH

#include <UtH/Platform/Common/InputBase.hpp>
#include <UtH/Math/Vector2.hpp>

namespace uth
{
	namespace TouchMotion
	{
		enum TouchMotion
		{
			NONE = 0,
			STATIONARY,
			TAP,
			DRAG,
			PINCH_IN,
			PINCH_OUT,
			MULTIPLE
		};
	}

	class TouchInput : public InputBase
	{
	private:
		class TouchUnit
		{
			friend class TouchInput;
		private:
			TouchMotion::TouchMotion m_motion;
		public:
			const TouchMotion::TouchMotion Motion() const;
			const int GetStartIndex() const;
			const umath::vector2 GetStartPosition() const;
			const umath::vector2 GetPosition() const;
			const umath::vector2 GetEndPosition() const;
		};
		TouchUnit ID[10];
	public:
		const TouchMotion::TouchMotion Motion() const;
		void Update(float dt);
		const TouchUnit& operator[](unsigned int id) const;
	};
}

#endif