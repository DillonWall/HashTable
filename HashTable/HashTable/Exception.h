/*************************************************************
* Author: Dillon Wall
* Filename: Exception.h
* Date Created: 1/19/2019
* Modifications:
**************************************************************/

#pragma once

#include <iostream>
using std::ostream;


/************************************************************************
* Class: Exception
*
* Purpose: This class represents an exception that is used in exception handling
*
* Manager functions:
* Exception()
*		Creates default Exception with a blank message
* Exception(const char * msg)
*		Creates a Exception with a specified message
* Exception(const Exception& other)
* Exception& operator=(const Exception& other)
* ~Exception()
* friend ostream& operator<<(ostream& stream, const Exception& except)
*		Allows the exception to be put in a stream (useful for cout-ing the exception)
*
* Methods:
* const char * GetMessage() const
* void SetMessage(char * msg)
*
*
*************************************************************************/
class Exception
{
public:
	Exception();
	Exception(const char * msg);
	Exception(const Exception& copy);
	~Exception();
	Exception& operator=(const Exception& rhs);

	const char * GetMsg() const;
	void SetMessage(char * msg);

	friend ostream& operator<<(ostream& stream, const Exception& except);
private:
	char * m_msg;
};

