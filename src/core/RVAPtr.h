#pragma once

#include "../stdafx.h"


class RVAPtrCore
{
    static uintptr_t c_base;
};

template <typename T>
class RVAPtr : public RVAPtrCore
{
public:

    RVAPtr(uintptr_t rva) : m_rva(c_base + rva) {}

	operator T *() const
	{
		return GetPtr();
	}

	T * operator->() const
	{
		return GetPtr();
	}

	T * GetPtr() const
	{
		return reinterpret_cast <T *>(m_rva);
	}

	const T * GetConst() const
	{
		return reinterpret_cast <T *>(m_rva);
	}

    uintptr_t GetUIntPtr() const
	{
		return m_rva;
	}

private:
    uintptr_t m_rva;

    RVAPtr() = delete;
    RVAPtr(RVAPtr & rhs) = delete;
	RVAPtr & operator=(RVAPtr & rhs) = delete;
};