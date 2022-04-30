/*************************************************************
* Author: Dillon Wall
* Filename: HashNode.h
* Date Created: 3/14/2019
* Modifications:
**************************************************************/
#pragma once

/************************************************************************
* Class: HashNode
*
* Purpose: This class represents a HashNode used in a HashTable
*
* Manager functions:
* HashNode();
* HashNode(K key, V value);
* ~HashNode();
* HashNode(const HashNode<K, V>& other);
* HashNode<K, V>& operator=(const HashNode<K, V>& rhs);
* bool operator==(const HashNode<K, V>& rhs);
*
* Methods:
* K& GetKey();
* K GetKey() const;
* void SetKey(K key);
* V& GetValue();
* V GetValue() const;
* void SetValue(V value);
*
*************************************************************************/
template <typename K, typename V>
class HashNode
{
public:
	HashNode();
	HashNode(K key, V value);
	~HashNode();
	HashNode(const HashNode<K, V>& other);
	HashNode<K, V>& operator=(const HashNode<K, V>& rhs);

	bool operator==(const HashNode<K, V>& rhs);

	K& GetKey();
	K GetKey() const;
	void SetKey(K key);
	V& GetValue();
	V GetValue() const;
	void SetValue(V value);

private:
	K m_key;
	V m_value;
};



template <typename K, typename V>
inline HashNode<K, V>::HashNode() : m_key(), m_value()
{
}

template<typename K, typename V>
inline HashNode<K, V>::HashNode(K key, V value) : m_key(key), m_value(value)
{
}


template <typename K, typename V>
inline HashNode<K, V>::~HashNode()
{
	m_key = K();
	m_value = V();
}

template<typename K, typename V>
inline HashNode<K, V>::HashNode(const HashNode<K, V>& other) : m_key(other.m_key), m_value(other.m_value)
{
}

template<typename K, typename V>
inline HashNode<K, V>& HashNode<K, V>::operator=(const HashNode<K, V>& rhs)
{
	if (this != &rhs)
	{
		m_key = rhs.m_key;
		m_value = rhs.m_value;
	}

	return *this;
}

template<typename K, typename V>
inline bool HashNode<K, V>::operator==(const HashNode<K, V>& rhs)
{
	return m_key == rhs.m_key &&
			m_value == rhs.m_value;
}

template<typename K, typename V>
inline K & HashNode<K, V>::GetKey()
{
	return m_key;
}

template<typename K, typename V>
inline K HashNode<K, V>::GetKey() const
{
	return m_key;
}

template<typename K, typename V>
inline void HashNode<K, V>::SetKey(K key)
{
	m_key = key;
}

template<typename K, typename V>
inline V & HashNode<K, V>::GetValue()
{
	return m_value;
}

template<typename K, typename V>
inline V HashNode<K, V>::GetValue() const
{
	return m_value;
}

template<typename K, typename V>
inline void HashNode<K, V>::SetValue(V value)
{
	m_value = value;
}
