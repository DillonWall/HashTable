#include "stdafx.h"
#include "CppUnitTest.h"
#include "crt_check_memory.hpp"
#include "Exception.h"
#include "Exception.cpp"
#include "HashTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(HashTableClassTests)
	{
	public:

		struct Book
		{
			std::string m_title;
			std::string m_author;
			int m_pages;

			inline bool operator==(const Book& rhs)
			{
				return m_title == rhs.m_title &&
					m_author == rhs.m_author &&
					m_pages == rhs.m_pages;
			}
		};
		
		TEST_METHOD(HashTableDefaultCtor)
		{
			crt_check_memory check;

			static const int TABLESIZE = 0;

			HashTable<std::string, Book> table;

			Assert::AreEqual(table.Size(), TABLESIZE);
		}

		TEST_METHOD(HashTable1ArgCtor)
		{
			crt_check_memory check;

			static const int TABLESIZE = 7;

			HashTable<std::string, Book> table(TABLESIZE);

			Assert::AreEqual(table.Size(), TABLESIZE);
		}

		TEST_METHOD(HashTable2ArgCtor)
		{
			crt_check_memory check;

			static const int TABLESIZE = 7;

			auto ShiftHash = [](std::string key)
			{
				int hashVal = 0;
				for (int i = 0; i < key.length(); ++i)
				{
					hashVal = (hashVal << 5) ^ key[i] ^ hashVal;
				}
				return hashVal % TABLESIZE;
			};

			HashTable<std::string, Book> table(TABLESIZE, ShiftHash);

			Assert::AreEqual(table.Size(), TABLESIZE);
		}

		TEST_METHOD(HashTableCopyCtor)
		{
			crt_check_memory check;

			static const int TABLESIZE = 7;

			auto ShiftHash = [](std::string key)
			{
				int hashVal = 0;
				for (int i = 0; i < key.length(); ++i)
				{
					hashVal = (hashVal << 5) ^ key[i] ^ hashVal;
				}
				return hashVal % TABLESIZE;
			};

			HashTable<std::string, Book> table(TABLESIZE, ShiftHash);
			Book temp = { "C++: An Active Learning Approach", "Randal Albert", 635 };
			table.Insert("0763757233", temp);
			Book temp1 = { "Rodeo for Dummies", "Calvin Caldwell", 137 };
			table.Insert("7063757233", temp1);
			Book temp2 = { "And That n There", "Ralph Carestia", 439 };
			table.Insert("7063757234", temp2);

			HashTable<std::string, Book> table2(table);

			Assert::AreEqual(table.Size(), table2.Size());
			Assert::AreEqual(table["0763757233"].m_title, table2["0763757233"].m_title);
		}

		TEST_METHOD(HashTableOperatorEquals)
		{
			crt_check_memory check;

			static const int TABLESIZE = 7;

			auto ShiftHash = [](std::string key)
			{
				int hashVal = 0;
				for (int i = 0; i < key.length(); ++i)
				{
					hashVal = (hashVal << 5) ^ key[i] ^ hashVal;
				}
				return hashVal % TABLESIZE;
			};

			HashTable<std::string, Book> table(TABLESIZE, ShiftHash);
			Book temp = { "C++: An Active Learning Approach", "Randal Albert", 635 };
			table.Insert("0763757233", temp);
			Book temp1 = { "Rodeo for Dummies", "Calvin Caldwell", 137 };
			table.Insert("7063757233", temp1);
			Book temp2 = { "And That n There", "Ralph Carestia", 439 };
			table.Insert("7063757234", temp2);

			HashTable<std::string, Book> table2;
			table2 = table;

			Assert::AreEqual(table.Size(), table2.Size());
			Assert::AreEqual(table["0763757233"].m_title, table2["0763757233"].m_title);
		}

		TEST_METHOD(HashTableSetSize)
		{
			crt_check_memory check;

			static int TABLESIZE = 7;

			auto ShiftHash = [](std::string key)
			{
				int hashVal = 0;
				for (int i = 0; i < key.length(); ++i)
				{
					hashVal = (hashVal << 5) ^ key[i] ^ hashVal;
				}
				return hashVal % TABLESIZE;
			};

			HashTable<std::string, Book> table(TABLESIZE, ShiftHash);
			Book temp = { "C++: An Active Learning Approach", "Randal Albert", 635 };
			table.Insert("0763757233", temp);
			Book temp1 = { "Rodeo for Dummies", "Calvin Caldwell", 137 };
			table.Insert("7063757233", temp1);
			Book temp2 = { "And That n There", "Ralph Carestia", 439 };
			table.Insert("7063757234", temp2);

			TABLESIZE = 23;
			table.SetSize(TABLESIZE);

			Book temp3 = { "foo bar foobar", "Dillon Wall", 349 };
			table.Insert("7063167819", temp3);

			Assert::AreEqual(table.Size(), TABLESIZE);
		}

		TEST_METHOD(HashTableInsert)
		{
			crt_check_memory check;

			static const int TABLESIZE = 7;

			auto ShiftHash = [](std::string key)
			{
				int hashVal = 0;
				for (int i = 0; i < key.length(); ++i)
				{
					hashVal = (hashVal << 5) ^ key[i] ^ hashVal;
				}
				return hashVal % TABLESIZE;
			};

			HashTable<std::string, Book> table(TABLESIZE, ShiftHash);
			Book temp = { "C++: An Active Learning Approach", "Randal Albert", 635 };
			table.Insert("0763757233", temp);
			Book temp1 = { "Rodeo for Dummies", "Calvin Caldwell", 137 };
			table.Insert("7063757233", temp1);
			Book temp2 = { "And That n There", "Ralph Carestia", 439 };
			table.Insert("7063757234", temp2);

			Assert::AreEqual(table.Size(), TABLESIZE);
			Assert::AreEqual(table["0763757233"].m_title, std::string("C++: An Active Learning Approach"));
		}

		TEST_METHOD(HashTableSetHash)
		{
			crt_check_memory check;

			static const int TABLESIZE = 7;

			auto ShiftHash = [](std::string key)
			{
				int hashVal = 0;
				for (int i = 0; i < key.length(); ++i)
				{
					hashVal = (hashVal << 5) ^ key[i] ^ hashVal;
				}
				return hashVal % TABLESIZE;
			};

			auto AsciiHash = [](std::string key)
			{
				int hashVal = 0;
				for (int i = 0; i < key.length(); ++i)
				{
					hashVal += key[i];
				}
				return hashVal % TABLESIZE;
			};

			HashTable<std::string, Book> table(TABLESIZE);

			table.SetHash(ShiftHash);

			Book temp = { "C++: An Active Learning Approach", "Randal Albert", 635 };
			table.Insert("0763757233", temp);
			Book temp1 = { "Rodeo for Dummies", "Calvin Caldwell", 137 };
			table.Insert("7063757233", temp1);
			Book temp2 = { "And That n There", "Ralph Carestia", 439 };
			table.Insert("7063757234", temp2);

			table.SetHash(AsciiHash);

			Assert::AreEqual(table.Size(), TABLESIZE);
			Assert::AreEqual(table["0763757233"].m_title, std::string("C++: An Active Learning Approach"));
		}

		TEST_METHOD(HashTableOperatorBrackets)
		{
			crt_check_memory check;

			static const int TABLESIZE = 7;

			auto ShiftHash = [](std::string key)
			{
				int hashVal = 0;
				for (int i = 0; i < key.length(); ++i)
				{
					hashVal = (hashVal << 5) ^ key[i] ^ hashVal;
				}
				return hashVal % TABLESIZE;
			};

			HashTable<std::string, Book> table(TABLESIZE, ShiftHash);
			Book temp = { "C++: An Active Learning Approach", "Randal Albert", 635 };
			table.Insert("0763757233", temp);
			Book temp1 = { "Rodeo for Dummies", "Calvin Caldwell", 137 };
			table.Insert("7063757233", temp1);
			Book temp2 = { "And That n There", "Ralph Carestia", 439 };
			table.Insert("7063757234", temp2);

			Assert::AreEqual(table.Size(), TABLESIZE);
			Assert::AreEqual(table["7063757233"].m_title, std::string("Rodeo for Dummies"));
		}

		TEST_METHOD(HashTableDelete)
		{
			crt_check_memory check;

			static const int TABLESIZE = 7;

			auto ShiftHash = [](std::string key)
			{
				int hashVal = 0;
				for (int i = 0; i < key.length(); ++i)
				{
					hashVal = (hashVal << 5) ^ key[i] ^ hashVal;
				}
				return hashVal % TABLESIZE;
			};

			HashTable<std::string, Book> table(TABLESIZE, ShiftHash);
			Book temp = { "C++: An Active Learning Approach", "Randal Albert", 635 };
			table.Insert("0763757233", temp);
			Book temp1 = { "Rodeo for Dummies", "Calvin Caldwell", 137 };
			table.Insert("7063757233", temp1);
			Book temp2 = { "And That n There", "Ralph Carestia", 439 };
			table.Insert("7063757234", temp2);

			table.Delete("7063757233");

			bool pass = false;
			try
			{
				table["7063757233"];
			}
			catch (Exception e)
			{
				pass = true;
			}

			Assert::IsTrue(pass);
		}

		TEST_METHOD(HashTableTraverse)
		{
			crt_check_memory check;

			static const int TABLESIZE = 7;

			auto ShiftHash = [](std::string key)
			{
				int hashVal = 0;
				for (int i = 0; i < key.length(); ++i)
				{
					hashVal = (hashVal << 5) ^ key[i] ^ hashVal;
				}
				return hashVal % TABLESIZE;
			};

			HashTable<std::string, Book> table(TABLESIZE, ShiftHash);
			Book temp = { "C++: An Active Learning Approach", "Randal Albert", 635 };
			table.Insert("0763757233", temp);
			Book temp1 = { "Rodeo for Dummies", "Calvin Caldwell", 137 };
			table.Insert("7063757233", temp1);
			Book temp2 = { "And That n There", "Ralph Carestia", 439 };
			table.Insert("7063757234", temp2);

			//add up page numbers
			static int total = 0;
			auto AddPages = [](Book b)
			{
				total += b.m_pages;
			};

			table.Traverse(AddPages);

			Assert::AreEqual(table.Size(), TABLESIZE);
			Assert::AreEqual(total, 635+137+439);
		}

		TEST_METHOD(HashTableNegSizeCtor)
		{
			crt_check_memory check;

			static const int TABLESIZE = -10;

			bool pass = false;
			try
			{
				HashTable<std::string, Book> table(TABLESIZE);
			}
			catch (Exception e)
			{
				pass = true;
			}

			Assert::IsTrue(pass);
		}

		TEST_METHOD(HashTableNegSizeSetSize)
		{
			crt_check_memory check;

			static const int TABLESIZE = 7;

			auto ShiftHash = [](std::string key)
			{
				int hashVal = 0;
				for (int i = 0; i < key.length(); ++i)
				{
					hashVal = (hashVal << 5) ^ key[i] ^ hashVal;
				}
				return hashVal % TABLESIZE;
			};

			HashTable<std::string, Book> table(TABLESIZE, ShiftHash);
			Book temp = { "C++: An Active Learning Approach", "Randal Albert", 635 };
			table.Insert("0763757233", temp);
			Book temp1 = { "Rodeo for Dummies", "Calvin Caldwell", 137 };
			table.Insert("7063757233", temp1);
			Book temp2 = { "And That n There", "Ralph Carestia", 439 };
			table.Insert("7063757234", temp2);

			bool pass = false;
			try
			{
				table.SetSize(-10);
			}
			catch (Exception e)
			{
				pass = true;
			}

			Assert::IsTrue(pass);
		}

		TEST_METHOD(HashTableInsertNoHashFunction)
		{
			crt_check_memory check;

			static const int TABLESIZE = 7;

			HashTable<std::string, Book> table(TABLESIZE);
			Book temp = { "C++: An Active Learning Approach", "Randal Albert", 635 };

			bool pass = false;
			try
			{
				table.Insert("0763757233", temp);
			}
			catch (Exception e)
			{
				pass = true;
			}

			Assert::IsTrue(pass);
		}

		TEST_METHOD(HashTableOpBracketsNoHashFunction)
		{
			crt_check_memory check;

			static const int TABLESIZE = 7;

			HashTable<std::string, Book> table(TABLESIZE);

			bool pass = false;
			try
			{
				table["0763757233"];
			}
			catch (Exception e)
			{
				pass = true;
			}

			Assert::IsTrue(pass);
		}

		TEST_METHOD(HashTableOpBracketsNoKey)
		{
			crt_check_memory check;

			static const int TABLESIZE = 7;

			auto ShiftHash = [](std::string key)
			{
				int hashVal = 0;
				for (int i = 0; i < key.length(); ++i)
				{
					hashVal = (hashVal << 5) ^ key[i] ^ hashVal;
				}
				return hashVal % TABLESIZE;
			};

			HashTable<std::string, Book> table(TABLESIZE, ShiftHash);
			Book temp = { "C++: An Active Learning Approach", "Randal Albert", 635 };
			table.Insert("0763757233", temp);
			Book temp1 = { "Rodeo for Dummies", "Calvin Caldwell", 137 };
			table.Insert("7063757233", temp1);
			Book temp2 = { "And That n There", "Ralph Carestia", 439 };
			table.Insert("7063757234", temp2);

			bool pass = false;
			try
			{
				table["0799999999"];
			}
			catch (Exception e)
			{
				pass = true;
			}

			Assert::IsTrue(pass);
		}

		TEST_METHOD(HashTableDeleteNoHashFunction)
		{
			crt_check_memory check;

			static const int TABLESIZE = 7;

			HashTable<std::string, Book> table(TABLESIZE);

			bool pass = false;
			try
			{
				table.Delete("0763757233");
			}
			catch (Exception e)
			{
				pass = true;
			}

			Assert::IsTrue(pass);
		}

		TEST_METHOD(HashTableDeleteNoKey)
		{
			crt_check_memory check;

			static const int TABLESIZE = 7;

			auto ShiftHash = [](std::string key)
			{
				int hashVal = 0;
				for (int i = 0; i < key.length(); ++i)
				{
					hashVal = (hashVal << 5) ^ key[i] ^ hashVal;
				}
				return hashVal % TABLESIZE;
			};

			HashTable<std::string, Book> table(TABLESIZE, ShiftHash);
			Book temp = { "C++: An Active Learning Approach", "Randal Albert", 635 };
			table.Insert("0763757233", temp);
			Book temp1 = { "Rodeo for Dummies", "Calvin Caldwell", 137 };
			table.Insert("7063757233", temp1);
			Book temp2 = { "And That n There", "Ralph Carestia", 439 };
			table.Insert("7063757234", temp2);

			bool pass = false;
			try
			{
				table.Delete("0799999999");
			}
			catch (Exception e)
			{
				pass = true;
			}

			Assert::IsTrue(pass);
		}
	};
}