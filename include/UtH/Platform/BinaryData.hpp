#pragma once
#ifndef BINARYDATA_HPP
#define BINARYDATA_HPP

#include <memory>

class BINARY_DATA
{
	unsigned char* m_data;
public:
	BINARY_DATA() : m_data(nullptr){}
	BINARY_DATA(const unsigned int size)
	{
		m_data = (new unsigned char[size]);
	}
	BINARY_DATA(void* data)
	{
		m_data = reinterpret_cast<unsigned char*>(data); 
	}
	BINARY_DATA(const BINARY_DATA& binary_data)
	{
		memcpy(m_data,binary_data.m_data,binary_data.size());
	}
	~BINARY_DATA()
	{
		clear();
	}
	void clear()
	{
		delete[] m_data;
	}
	size_t size() const
	{
		return sizeof(m_data);
	}
	void* ptr() const
	{
		return reinterpret_cast<void*>(m_data);
	}
	// BINARY_DATA = void*
	const BINARY_DATA& operator = (void* rightVal)
	{
		m_data = reinterpret_cast<unsigned char*>(rightVal);
		return (*this);
	}
};

#endif