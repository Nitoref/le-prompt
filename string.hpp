#ifndef STRING_H
#define STRING_H

#include <string>
#include <cstring>


class string: public std::string {
public:
	using std::string::string;
	
	string(const char* s)
	{
		if (s != NULL)
			this->assign(s);
	}
	
	void replace_all(const std::string& from, const std::string& to)
	{
	    size_t cursor = 0;
	    while((cursor = this->find(from, cursor)) != std::string::npos) {
	        this->replace(cursor, from.length(), to);
	        cursor += to.length();
	    }
	}

	size_t rnfind (char c, size_t n)
	{
		if (!this->empty())
	        for (int i = this->length() - 1; i >= 0; --i)
	            if (this->at(i) == c)
	                if (--n == 0)
	                    return i;
	    return std::string::npos;
	}
};



#endif
