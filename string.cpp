#include <iostream>
#include <cstring>
#include <cassert>

#include "mystring.h"

namespace coen79_lab5
{

    //////////////// CONSTRUCTOR, COPY CONSTRUCTOR, and DESTRUCTOR ////////////////
    string::string(const char str[]) // str should already have '/0'
    {
        // init
        current_length = strlen(str);   // keeps track of string length - null char
        allocated = current_length + 1; // keeps track of string length + null char
        characters = new char[allocated];
        strncpy(characters, str, allocated);

        // DEBUG
        // std::cout << "char []---" << std::endl;
        // std::cout << characters << " <---- " << str << " length: " << current_length << std::endl;
    }
    string::string(char c)
    { // NEW FUNCTION 1
        // init
        current_length = 1;
        allocated = 2;

        characters = new char[allocated];

        characters[0] = c;
        characters[1] = '\0';

        // DEBUG
        // std::cout << "char---" << std::endl;
        // std::cout << characters << " <---- " << c << " length: " << current_length << std::endl;
    }
    string::string(const string &source)
    {
        // init
        current_length = source.length();
        allocated = source.allocated;

        characters = new char[allocated]; // MAY CAUSE ERROR

        strncpy(characters, source.characters, allocated);

        // DEBUG
        // std::cout << "str---" << std::endl;
        // std::cout << characters << " <---- " << source << " length: " << current_length << std::endl;
    }

    string::~string()
    {
        delete[] characters;
        allocated = 0;
        current_length = 0;
    }

    // MODIFICATION MEMBER FUNCTIONS

    void string::reserve(size_t n)
    { // n should already factor in the /0 as a character
      // memory doesn't stack, must allocate new mem and delete old
        char *new_chars = new char[n];

        if (characters != NULL)
        {
            // never reduce length of characters
            strncpy(new_chars, characters, current_length);
            delete[] characters;
        }
        characters = new_chars;
    }

    void string::operator+=(const string &addend)
    {
        current_length += addend.length();
        allocated = current_length + 1;

        reserve(allocated);                                      // NOT SURE IF REF PASS CAN CALL FUNCTIONS???
        strncat(characters, addend.characters, addend.length()); // DO I NEED TO DO THIS OR IS IT DONE AUTOMATICALLY???
    }
    void string::operator+=(const char addend[])
    {
        current_length += strlen(addend);
        allocated = current_length + 1;

        reserve(allocated);
        strncat(characters, addend, strlen(addend));
    }
    void string::operator+=(char addend)
    {
        current_length += 1;
        allocated = current_length + 1;

        reserve(allocated);

        characters[current_length] = addend;
    }
    string &string::operator=(const string &source)
    {
        this->dlt(0, current_length);                // delete current characters
        if (current_length != source.current_length) // allocate more memory if source length bigger
        {
            allocated = source.allocated;
            reserve(allocated);
        }

        strncpy(characters, source.characters, source.current_length);
        current_length = source.current_length;

        return *this;
    }
    void string::insert(const string &source, unsigned int position)
    {
        char *start;
        memcpy(start, characters, position);
        char *end;
        memcpy(start, &characters[position], current_length);

        strncpy(characters, start, position);
        strncat(characters, source.characters, source.length());
        strncat(characters, end, current_length - position);
    }
    void string::dlt(unsigned int position, unsigned int num)
    {
        assert(position + num <= current_length);

        // shift characters array down from position to overwrite
        for (int i = position; i < position + num; i++)
        {
            characters[i] = characters[i + num];
        }
        current_length -= num;
    }
    void string::replace(char c, unsigned int position)
    {
        assert(position < length());

        characters[position] = c;
    }
    void string::replace(const string &source, unsigned int position)
    {
        assert(position <= length());

        strncpy(characters, &characters[0], position - 1);
        strncpy(characters, source.characters, source.length());
        if (position + source.length() < length())
        {
            strncpy(characters, &characters[position + source.length()], current_length - source.length() - position);
        }
    }

    // CONSTANT MEMBER FUNCTIONS
    // size_t string::length() const//already defined in header
    char string::operator[](size_t position) const
    {
        return characters[position];
    }
    int string::search(char c) const
    {
        for (int i = 0; i < current_length; i++)
        {
            if (characters[i] == c)
                return i;
        }
        return -1;
    }
    int string::search(const string &substring) const
    {
        for (int i = 0; i < current_length; i++)
        {
            if (characters[i] == substring[0]) // strncmp(&characters[i], substring.characters, substring.current_length) == 0
            {
                for (int j = 0; j < substring.length(); j++)
                {
                    if (characters[i + j] != substring[j])
                        return -1;
                }
                return i;
            }
        }
        return -1;
    }
    unsigned int string::count(char c) const
    {
        int count = 0;
        for (int i = 0; i < current_length; i++)
        {
            if (characters[i] == c)
                count++;
        }
        return count;
    }

    std::ostream &operator<<(std::ostream &outs, const string &source)
    {
        outs << source.characters;
        // std::cout << source.characters;
        return outs;
    }
    bool operator==(const string &s1, const string &s2)
    {
        std::cout << s1.characters << " == " << s2.characters << std::endl;
        if (strcmp(s1.characters, s2.characters) == 0) // or can use s1.characters
            return true;
        else
            return false;
    }
    bool operator!=(const string &s1, const string &s2)
    {
        if (strcmp(s1.characters, s2.characters) != 0) // or can use s1.characters
            return true;
        else
            return false;
    }
    bool operator>(const string &s1, const string &s2)
    {
        if (strcmp(s1.characters, s2.characters) > 0) // or can use s1.characters
            return true;
        else
            return false;
    }
    bool operator<(const string &s1, const string &s2)
    {
        if (strcmp(s1.characters, s2.characters) < 0) // or can use s1.characters
            return true;
        else
            return false;
    }
    bool operator>=(const string &s1, const string &s2)
    {
        if (s1 > s2 || s1 == s2) // or can use s1.characters
            return true;
        else
            return false;
    }
    bool operator<=(const string &s1, const string &s2)
    {
        if (s1 < s2 || s1 == s2) // or can use s1.characters
            return true;
        else
            return false;
    }

    // NON-MEMBER FUNCTIONS for the string class
    string operator+(const string &s1, const string &s2)
    {
        string holder;

        holder.reserve(s1.length() + s2.length() + 1);

        std::cout << "s1: " << s1 << " s2:  |" << s2 << "|" << std::endl;

        std::cout << "holder: " << holder << std::endl;
        holder = s1;
        std::cout << "holder: " << holder << std::endl;
        holder += s2;
        std::cout << "holder: " << holder << std::endl;

        return holder;
    }
    string operator+(const string &s1, const char addend[])
    {
        string holder;

        std::cout << "s1: " << s1 << " s2:  |" << addend << "|" << std::endl;

        holder.reserve(s1.length() + strlen(addend) + 1);

        std::cout << "holder: " << holder << std::endl;
        holder = s1;
        std::cout << "holder: " << holder << std::endl;
        holder += addend;
        std::cout << "holder: " << holder << std::endl;

        return holder;
    }
    std::istream &operator>>(std::istream &ins, string &target)
    {
        char *in = new char[50];
        // while (ins && isspace(ins.peek()))
        // {
        //     ins.ignore();
        // }
        ins >> in;

        std::cout << "target:  " << target << std::endl;

        target += string(in);

        std::cout << "in:  " << in << std::endl;
        std::cout << "string::in:  " << string(in) << std::endl;

        std::cout << "target:  " << target << std::endl;

        return ins;
    }

}

// NOTES
// store characters with char *str
// str console logs give us the whole string
//*str console logs the 0th position of str (like an array)
// to use strcpy with char do &<char_variable_name> ---> not to sure why this works
// to use strcat with char do &<char_variable_name> ---> not to sure why this works

// strings " " can be directly stored in char *

// to allocate memory use ---> new char[length_of_string + 1];
// always allocate memory then use strcpy to store new variable as to not run into computation issues
//  FIND THE DIFFERENCE BETWEEN CHAR, CHAR *, CONST CHAR * AND HOW TO SHIFT BETWEEN THEM