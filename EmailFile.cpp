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


#define _CRT_SECURE_NO_WARNINGS


#include "EmailFile.h"


#include <cstring>

#include <fstream>

#include <iostream>

#include <algorithm> 

#include <iterator> 

#include <iomanip>


namespace seneca 

{

    Email::Email()
    
    
    {
        //  managed by EmailFile
    }



    Email::~Email() 
    
    {
        delete[] m_email;



        delete[] m_name;


    }

    Email& Email::operator=(const Email& rhs) 
    
    {

        if (this != &rhs) 
        

        {
            delete[] m_email;


            m_email = new char[strlen(rhs.m_email) + 1];


            strcpy(m_email, rhs.m_email);



            delete[] m_name;


            m_name = new char[strlen(rhs.m_name) + 1];


            strcpy(m_name, rhs.m_name);


            strncpy(m_year, rhs.m_year, sizeof(m_year));


        }


        return *this;


    }



    bool Email::load(std::ifstream& in)
    
    {
        char buffer[BUFFER_SIZE];


        if (in.getline(buffer, BUFFER_SIZE, ','))
        
        {
            delete[] m_email;


            m_email = new char[strlen(buffer) + 1];


            strcpy(m_email, buffer);



            if (in.getline(buffer, BUFFER_SIZE, ','))
            
            {
                delete[] m_name;


                m_name = new char[strlen(buffer) + 1];


                strcpy(m_name, buffer);



                if (in.getline(m_year, 5)) 
                
                {
                    return true;


                }
            }
        }
        return false;


    }

    EmailFile::EmailFile() : m_emailLines(nullptr), m_filename(nullptr), m_noOfEmails(0)
    
    
    
   {
        // Constructor code
    }

    EmailFile::EmailFile(const char* filename) : m_emailLines(nullptr), m_noOfEmails(0)
    
    {
        setFilename(filename);


        if (setNoOfEmails())
        
        {
            loadEmails();
        }
    }

    EmailFile::~EmailFile()
    
    {
        setEmpty();

    }

    EmailFile::EmailFile(const EmailFile& other) : m_emailLines(nullptr), m_filename(nullptr), m_noOfEmails(0)
    
    {
        *this = other;
    }

    EmailFile& EmailFile::operator=(const EmailFile& rhs) 
    
    {
        if (this != &rhs)
        
        {
            setEmpty();

            setFilename(rhs.m_filename);

            m_noOfEmails = rhs.m_noOfEmails;

            loadEmails();
            
            
        }


        return *this;


    }

    void EmailFile::setEmpty()
    
    {
        delete[] m_emailLines;


        m_emailLines = nullptr;


        delete[] m_filename;


        m_filename = nullptr;



        m_noOfEmails = 0;
    }

    void EmailFile::setFilename(const char* filename)
    
    {
        // check if m_filename already points to allocated memory and free it if necessary


        if (m_filename != nullptr)
        {
            delete[] m_filename;

            m_filename = nullptr;
            
            // Prevent dangling pointer
        }

        // allocate new memory for the new filename, if provided


        if (filename != nullptr)
        
        {
            m_filename = new char[strlen(filename) + 1];
            
            
            
            // allocate memory for the new filename with space for the null terminator
            
            
            strcpy(m_filename, filename);
            
            // Copy the new filename into m_filename
        }
    }




    bool EmailFile::setNoOfEmails() 
    
    {
        std::ifstream file(m_filename);

        if (!file.is_open())
        
        {
            std::cerr << "Failed to open file: " << m_filename << std::endl;


            return false;


        }



        m_noOfEmails = std::count(std::istreambuf_iterator<char>(file),


            std::istreambuf_iterator<char>(), '\n');


        file.close();



        return m_noOfEmails > 0;


    }

    
    void EmailFile::loadEmails() {
        
        
        if (m_filename == nullptr || m_noOfEmails <= 0) return;

        
        
        std::ifstream file(m_filename);
        
        
        if (!file) {
            
            
            std::cerr << "Failed to open file for loading: " << m_filename << std::endl;
            
            
            
            return;
       
        }



        m_emailLines = new Email[m_noOfEmails];

        for (int i = 0; i < m_noOfEmails; ++i) 
        {

            if (!m_emailLines[i].load(file))
            
            {
                std::cerr << "Error loading email at line: " << i + 1 << std::endl;


                break;


            }
        }
    }



    bool EmailFile::saveToFile(const char* filename) const 
    
    {
        if (filename == nullptr) return false;



        std::ofstream outFile(filename);


        if (!outFile)
        
        {
            std::cerr << "Error: Could not open file: " << filename << std::endl;


            return false;


        }



        for (int i = 0; i < m_noOfEmails; ++i) 
        
        {
            outFile << m_emailLines[i].m_email << ',' << m_emailLines[i].m_name << ',' << m_emailLines[i].m_year << std::endl;


        }

        return true;


    }

    void EmailFile::fileCat(const EmailFile& obj, const char* name)
    
    {
        if (!(bool(*this)) || !(bool(obj))) {


            std::cerr << "One of the EmailFile objects is not in a valid state." << std::endl;


            return;

        }



        // total number of emails after concatenation



        int totalEmails = m_noOfEmails + obj.m_noOfEmails;


        Email* newEmailLines = new Email[totalEmails];



        // Copy emails from this object


        for (int i = 0; i < m_noOfEmails; ++i)
        
        {


            newEmailLines[i] = m_emailLines[i];


        }



        // Copy emails from obj


        for (int i = 0; i < obj.m_noOfEmails; ++i)
        
        {


            newEmailLines[m_noOfEmails + i] = obj.m_emailLines[i];


        }

        // Clean up the old state


        delete[] m_emailLines;



        // Update to the new combined state


        m_emailLines = newEmailLines;


        m_noOfEmails = totalEmails;





        // If a new filename is provided, update and save the emails to the new file



        if (name != nullptr)
        
        {
            setFilename(name);



            if (!saveToFile(name))
            
            {
                std::cerr << "Failed to save file: " << name << std::endl;


            }
        }
    }

    std::ostream& EmailFile::view(std::ostream& ostr) const 
    
    {
        if (m_filename != nullptr)
        
        {
            ostr << m_filename << std::endl;


            ostr << std::string(std::strlen(m_filename), '=') << std::endl;


            for (int i = 0; i < m_noOfEmails; ++i)
            
            {
                // Adjust the setw() parameters to suit the desired output width


                ostr << std::left << std::setw(35) << m_emailLines[i].m_email


                    << std::setw(25) << m_emailLines[i].m_name


                    << "Year = " << m_emailLines[i].m_year << std::endl;


            }
        }
        return ostr;


    }

    EmailFile::operator bool() const
    
    {
        return m_filename != nullptr && m_noOfEmails > 0;


    }


    std::ostream& operator<<(std::ostream& ostr, const EmailFile& ef)
    
    {
        return ef.view(ostr);


    }

}

// namespace seneca
