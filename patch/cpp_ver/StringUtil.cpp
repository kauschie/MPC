#include "StringUtil.h"
#include <sstream>
#include <iostream>


namespace StringUtil
{

    bool isEmpty(const std::string & s)
    {
        for (auto & c : s)
        {
            if (c != '\0')
            {
                return false;
            }
        }

        return true;
    }

    bool contains(const std::string& s, const std::string lookfor) {
		return s.find(lookfor) != std::string::npos;
	}

    std::vector<std::string> split(const std::string & s, char delim, bool skipEmpties, bool skipSpaces)
    {
        std::stringstream ss(s);
        std::string item;

        std::vector<std::string> tokens;
        std::vector<std::string> sub_tokens;

        while (std::getline(ss, item, delim))
        {
            // Add item if it's non-empty, or if skip empties is turned off

            // remove carriage return
            item.erase( std::remove(item.begin(), item.end(), '\r'), item.end() );

            if (!skipEmpties || !isEmpty(item))
            {
                if (delim != ' ' && skipSpaces == true) {
                    sub_tokens.clear();
                    sub_tokens = split(item, ' ');
                    for (auto & t : sub_tokens) {
                        tokens.push_back(trim(t));
                    }
                } else {
                    tokens.push_back(trim(item));
                }
            }
        }

        return tokens;
    }

    std::string trim(const std::string & str)
    {
        auto first = str.find_first_not_of(' ');
        auto last  = str.find_last_not_of(' ');

        return str.substr(first, (last - first + 1));
    }

    std::string lower(const std::string & str)
	{
		auto result = str;

		std::transform(result.begin(), result.end(), result.begin(), ::tolower);

		return result;
	}

	std::string upper(const std::string & str)
	{
		auto result = str;

		std::transform(result.begin(), result.end(), result.begin(), ::toupper);

		return result;
	}

	std::string clean(const std::string & str)
	{
		return lower(trim(str));
	}

    
    std::string join(const std::vector<std::string> & tokens, const char ins)
    {
        std::stringstream ss;
        bool isFirstTok = true;

        for (auto & tok : tokens)
        {
            // Add item if it's non-empty
            if (!isEmpty(tok))
            {
                if (isFirstTok) {
                    ss << tok;
                    isFirstTok = false;
                } else {
                    ss << ins << tok;
                }
            }
        }

        return ss.str();
    }

    void print_tokens(std::vector<std::string> tokens)
    {
        std::stringstream ss;
        bool isFirst = true;

        ss << "{ ";

        for (auto tok : tokens) {
            if (isFirst) {
                isFirst = false;
                ss << tok;
            } else {
                ss << ", " << tok;
            }
        }
        ss << " }";

        std::cout << ss.str() << std::endl;
    }
}
