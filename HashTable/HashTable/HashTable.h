/*************************************************************
* Author: Dillon Wall
* Filename: HashTable.h
* Date Created: 3/14/2019
* Modifications:
**************************************************************/
#pragma once

#include <vector>
#include <list>
#include "HashNode.h"
#include "Exception.h"

/************************************************************************
* Class: HashTable
*
* Purpose: This class represents a HashTable ADT Data structure
*
* Manager functions:
* HashTable();
* HashTable(int size);
* HashTable(int size, int(*hash)(K key));
* ~HashTable();
* HashTable(const HashTable<K, V>& other);
* HashTable<K, V>& operator=(const HashTable<K, V>& rhs);
*
* Methods:
* int Size() const;
*		returns the size of the vector
* void SetSize(int size);
*		sets m_size and resizes, and thus rehashes the table
* void Insert(K key, V value);
*		inserts data into its corresponding hashed location
* void Insert(K key, V value, std::vector<std::list<HashNode<K, V>>>& data);
*		inserts data into its corresponding hashed location for any data list
* void SetHash(int(*hash)(K key));
*		sets the hash function and rehashes the data if needed
* V& operator[](K key);
*		returns a reference to the data at the location of the key
* void Delete(K key);
*		removes an item from the table based on its key
* void Traverse(void(*visit)(V value));
*		traverses the table and calls the visit function on all HashNodes found
*
*************************************************************************/
template <typename K, typename V>
class HashTable
{
public:
	HashTable();
	HashTable(int size);
	HashTable(int size, int(*hash)(K key));
	~HashTable();
	HashTable(const HashTable<K, V>& other);
	HashTable<K, V>& operator=(const HashTable<K, V>& rhs);

	int Size() const;
	void SetSize(int size);

	void Insert(K key, V value);
	void Insert(K key, V value, std::vector<std::list<HashNode<K, V>>>& data);
	void SetHash(int(*hash)(K key));
	V& operator[](K key);
	void Delete(K key);
	void Traverse(void(*visit)(V value));

private:
	std::vector<std::list<HashNode<K, V>>> m_data;
	int m_size;
	int(*m_hashFunction)(K key);
};


template <typename K, typename V>
inline HashTable<K,V>::HashTable() : m_data(), m_size(0), m_hashFunction(nullptr)
{
	m_data = std::vector<std::list<HashNode<K, V>>>(0);
}

template<typename K, typename V>
inline HashTable<K, V>::HashTable(int size) : m_data(), m_size(size), m_hashFunction(nullptr)
{
	if (size < 0)
		throw Exception("Cannot create table with non-negative size");

	m_data = std::vector<std::list<HashNode<K, V>>>(size);
}

template<typename K, typename V>
inline HashTable<K, V>::HashTable(int size, int(*hash)(K key)) : m_data(), m_size(size), m_hashFunction(nullptr)
{
	if (size < 0)
		throw Exception("Cannot create table with non-negative size");

	m_hashFunction = hash;
	m_data = std::vector<std::list<HashNode<K, V>>>(size);
}

template <typename K, typename V>
inline HashTable<K, V>::~HashTable()
{
	m_data = std::vector<std::list<HashNode<K, V>>>(0);
	m_size = 0;
	m_hashFunction = nullptr;
}

template<typename K, typename V>
inline HashTable<K, V>::HashTable(const HashTable<K, V>& other) : m_data(other.m_data), m_size(other.m_size), m_hashFunction(other.m_hashFunction)
{
}

template<typename K, typename V>
inline HashTable<K, V>& HashTable<K, V>::operator=(const HashTable<K, V>& rhs)
{
	if (this != &rhs)
	{
		m_data = rhs.m_data;
		m_size = rhs.m_size;
		m_hashFunction = rhs.m_hashFunction;
	}

	return *this;
}

template<typename K, typename V>
inline int HashTable<K, V>::Size() const
{
	return m_size;
}

template<typename K, typename V>
inline void HashTable<K, V>::SetSize(int size)
{
	if (size < 0)
		throw Exception("Cannot set table to non-negative size");

	m_size = size;
	SetHash(m_hashFunction); //Rehash with same function
}

template<typename K, typename V>
inline void HashTable<K, V>::Insert(K key, V value)
{
	Insert(key, value, m_data);
}

template<typename K, typename V>
inline void HashTable<K, V>::Insert(K key, V value, std::vector<std::list<HashNode<K, V>>>& data)
{
	if (m_hashFunction == nullptr)
		throw Exception("Hash function not specified Insert()");

	int hashKey = m_hashFunction(key);
	if (hashKey >= m_size || hashKey < 0)
		throw Exception("Hash function gave index out of bounds");

	data.at(hashKey).push_back(HashNode<K, V>(key, value));
}

template<typename K, typename V>
inline void HashTable<K, V>::SetHash(int(*hash)(K key))
{
	bool shouldRehash = m_hashFunction != nullptr;
	m_hashFunction = hash;

	if (shouldRehash)
	{
		std::vector<std::list<HashNode<K, V>>> newData(m_size);
		for (std::list<HashNode<K, V>>& list : m_data)
		{
			for (HashNode<K, V>& node : list)
			{
				Insert(node.GetKey(), node.GetValue(), newData);
			}
		}
		m_data = newData;
	}
}

template<typename K, typename V>
inline V& HashTable<K, V>::operator[](K key)
{
	if (m_hashFunction == nullptr)
		throw Exception("Hash function not specified operator[]");

	int hashKey = m_hashFunction(key);
	if (hashKey >= m_size || hashKey < 0)
		throw Exception("Hash function gave index out of bounds");

	for (HashNode<K, V>& node : m_data.at(hashKey))
	{
		if (node.GetKey() == key)
			return node.GetValue();
	}

	throw Exception("Key not found in hashtable operator[]");
}

template<typename K, typename V>
inline void HashTable<K, V>::Delete(K key)
{
	if (m_hashFunction == nullptr)
		throw Exception("Hash function not specified Delete()");

	int hashKey = m_hashFunction(key);
	if (hashKey >= m_size || hashKey < 0)
		throw Exception("Hash function gave index out of bounds");

	for (HashNode<K, V> node : m_data.at(hashKey))
	{
		if (node.GetKey() == key)
		{
			m_data.at(hashKey).remove(node);
			return;
		}
	}

	throw Exception("Key not found in hashtable Delete()");
}

template<typename K, typename V>
inline void HashTable<K, V>::Traverse(void(*visit)(V value))
{
	for (std::list<HashNode<K, V>> list : m_data)
	{
		for (HashNode<K, V> node : list)
		{
			visit(node.GetValue());
		}
	}
}
