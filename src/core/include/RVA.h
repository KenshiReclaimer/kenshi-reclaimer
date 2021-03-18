#pragma once

#include <stdafx.h>

/*
	Class that implements RVA resolution at runtime. Mostly like how F4SE/SKSE64 implement it.
*/


class RVACore
{
public:

    RVACore(uintptr_t rva) : m_addr(c_base + rva) {}

    uintptr_t GetUIntPtr() const
	{
		return m_addr;
	}
	
protected:

    static uintptr_t c_base;

    uintptr_t m_addr;

    RVACore() = delete;
    RVACore(RVACore & rhs) = delete;
	RVACore & operator=(RVACore & rhs) = delete;
};

template <typename T>
class RVAPtr : public RVACore
{
public:
	using Type = T;

	operator T *() const
	{
		return *reinterpret_cast <T *>(m_addr);
	}

	T * operator->() const
	{
		return *reinterpret_cast <T *>(m_addr);
	}

	T * GetPtr() const
	{
		return reinterpret_cast <T *>(m_addr);
	}

	const T * GetConst() const
	{
		return *reinterpret_cast <T *>(m_addr);
	}

};


template <typename _Ret, typename... _Args>
class RVAFn : public RVACore
{
public:
	using Type = _Ret(*)(_Args...);

	_Ret operator()(_Args... e)
	{
		return reinterpret_cast<Type>(m_addr)(e);
	}

private:
};