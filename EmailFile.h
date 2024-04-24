#pragma once/***********************************************************************
// OOP244 Workshop # 6
//
// File:	EmailFile.h
// Version 1.0
// Date:
// Author: Sina Talebi Moghaddam
// Description
// This file must be completed by students
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
//
/////////////////////////////////////////////////////////////////
***********************************************************************/

/*/////////////////////////////////////////////////////////////////////////
						  Workshop - 6
Full Name  : jagjit kaur
Student ID#: 156806226
Email      : jkaur682@myseneca.ca
Section    : NII
Date       : 09 march 2024

Authenticity Declaration:

I have done all the coding by myself and only copied the code that my
professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/



#ifndef SENECA_EMAILFILE_H


#define SENECA_EMAILFILE_H

#include <iostream>

namespace seneca 
{

	const int BUFFER_SIZE = 1024; 

	// for all email fields this is the maximum size 



	class EmailFile;


	class Email
	{
		friend class EmailFile;
		
		
		//  emailfile for friend class


		char* m_email{ nullptr };


		char* m_name{ nullptr };


		char m_year[5]{ '\0' };



	public:


		Email();


		Email& operator=(const Email& rhs);


		bool load(std::ifstream& in);


		~Email();


		Email(const Email&) = delete;
		
		


		// restrict copy constructor for this class



		// EmailFile of "friend" class

	};


	class EmailFile


	{


		Email* m_emailLines{ nullptr };



		char* m_filename{};


		int m_noOfEmails{ 0 };




		void setFilename(const char* filename);



		void setEmpty();


		bool setNoOfEmails();


		void loadEmails();




	public:



		EmailFile();



		EmailFile(const char* filename);



		~EmailFile();


		EmailFile(const EmailFile& other);


		EmailFile& operator=(const EmailFile& rhs);



		bool saveToFile(const char* filename) const;


		void fileCat(const EmailFile& obj, const char* name = nullptr);


		std::ostream& view(std::ostream& ostr) const;



		operator bool() const;


	};



	std::ostream& operator<<(std::ostream& ostr, const EmailFile& text);




}


#endif 


// !SENECA_EMAILFILE_H

