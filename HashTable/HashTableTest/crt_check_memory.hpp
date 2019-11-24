#ifndef CRTCHECKMEMORY_H
#define CRTCHECKMEMORY_H

#include "stdafx.h"
#include "CppUnitTest.h"
#include "crtdbg.h"

#define _CRTDBG_MAP_ALLOC

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	struct crt_check_memory
	{
		_CrtMemState state1{};
		_CrtMemState state2{};
		_CrtMemState state3{};
		crt_check_memory()
		{
			_CrtMemCheckpoint(&state1);
		}

		crt_check_memory(const crt_check_memory& copy) = delete;
		crt_check_memory& operator=(const crt_check_memory& copy) = delete;
		crt_check_memory(crt_check_memory&& copy) = delete;
		crt_check_memory& operator=(crt_check_memory&& copy) = delete;

		~crt_check_memory()
		{
			_CrtMemCheckpoint(&state2);

			if (_CrtMemDifference(&state3, &state1, &state2) != 0)
			{
				Assert::Fail(L"Detected memory leaks!");
			}
		}
	};
}

#endif