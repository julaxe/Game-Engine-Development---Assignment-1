#pragma once
#include <map>

template<class T>
class ObjectPoolingEngine
{
public:
	ObjectPoolingEngine(unsigned int initSize = 0);
	T* RetrieveObjectFromPool();
	void ThrowBackObjectToPool(T* object);
	int GetSize();
	std::map<T*,bool> GetPool();
private:
	void InitializePool();
	T* GrowPool();
private:
	std::map<T*, bool> m_mPool;
	unsigned int m_iSize;
};

/////////////////////////////////////////////////// IMPLEMENTATION /////////////////////////////////////////////////////////
template<class T>
ObjectPoolingEngine<T>::ObjectPoolingEngine(unsigned int initSize)
{
	m_iSize = initSize;
	InitializePool();
}

template<class T>
T* ObjectPoolingEngine<T>::RetrieveObjectFromPool()
{
	for(auto object : m_mPool)
	{
		if(object.second == false)
		{
			m_mPool[object.first] = true;
			return object.first;
		}
	}
	return GrowPool();
}

template<class T>
void ObjectPoolingEngine<T>::ThrowBackObjectToPool(T* object)
{
	m_mPool[object] = false;
}

template <class T>
int ObjectPoolingEngine<T>::GetSize()
{
	return m_iSize;
}

template <class T>
std::map<T*, bool> ObjectPoolingEngine<T>::GetPool()
{
	return m_mPool;
}

template<class T>
void ObjectPoolingEngine<T>::InitializePool()
{
	for (int i = 0; i < m_iSize; i++)
	{
		m_mPool.emplace(new T(), false);
	}
}

template<class T>
T* ObjectPoolingEngine<T>::GrowPool()
{
	T* newObject = new T();
	m_mPool.emplace(newObject, true);
	return newObject;
}