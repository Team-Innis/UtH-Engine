#pragma once
#ifndef BINARYDATA_HPP
#define BINARYDATA_HPP

#include <memory>

class BINARY_DATA
{
	unsigned char* m_data;
	size_t m_size;
public:
	BINARY_DATA()
		: m_data(nullptr),
		  m_size(0)
	{}
	BINARY_DATA(const unsigned int size)
	{
		m_size = size;
		m_data = (new unsigned char[size]);
	}
	BINARY_DATA(void* data, const size_t size)
	{
		setData(data,size);
	}
	BINARY_DATA(const BINARY_DATA& binary_data)
	{
		m_size = binary_data.m_size;
		m_data = binary_data.m_data;
	}
	~BINARY_DATA(){}
	void setData(void* data, const size_t size)
	{
		m_data = reinterpret_cast<unsigned char*>(data);
		m_size = size;
	}
	size_t size() const
	{
		return m_size;
	}
	void* ptr() const
	{
		return reinterpret_cast<void*>(m_data);
	}
	void clear()
	{
		delete[] m_data;
		m_size = 0;
	}

};

#endif