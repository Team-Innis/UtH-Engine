#pragma once
#ifndef UNCOPYABLE_H_UTH
#define UNCOPYABLE_H_UTH

namespace uth
{
	class Uncopyable
	{
	protected:
		Uncopyable(){}
		~Uncopyable(){}

	private:
		Uncopyable(const Uncopyable&);
		Uncopyable& operator =(const Uncopyable&);

	};
}

#endif
