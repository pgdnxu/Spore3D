// *********************************************************************
//             ____                       _____ ____
//            / ___| _ __   ___  _ __ ___|___ /|  _ \
//            \___ \| '_ \ / _ \| '__/ _ \ |_ \| | | |
//             ___) | |_) | (_) | | |  __/___) | |_| |
//            |____/| .__/ \___/|_|  \___|____/|____/
//                  |_|
//
//  Spore3D
//      -- High performance , Lightweight 3D Game Engine
//      -- github.com/pgdnxu/Spore3D
//  --------------------------------------------------------------------
//
//  Copyright (C) 2016 Shannon Xu
//
//  This software is distributed under the terms of the MIT License.
//  A copy of the license may be obtained at: https://opensource.org/licenses/MIT
//
// .--. --. -.. -. .. -. ..-. --.-. --. -- .- .. .-.. .-.-.- -.-. --- --

#ifndef _uStringUtils_h_
#define _uStringUtils_h_

#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <locale>

namespace Spore3D {
    
    class StringUtils {
    public:
        
        static void split(const std::string &str, char delim, std::vector<std::string> &elems) {
            std::stringstream ss(str);
            std::string item;
            while(std::getline(ss, item, delim)) {
                elems.push_back(item);
            }
        }
        
        static std::vector<std::string> split(const std::string &str, char delim) {
            std::vector<std::string> elems;
            split(str, delim, elems);
            return elems;
        }
        
        // trim from start (in place)
        static void ltrim(std::string &s) {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(),std::not1(std::ptr_fun<int, int>(std::isspace))));
        }
        
        // trim from end (in place)
        static void rtrim(std::string &s) {
            s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        }
        
        // trim from both ends (in place)
        static void trim(std::string &s) {
            ltrim(s);
            rtrim(s);
        }
        
        // trim from start (copying)
        static std::string ltrimmed(std::string s) {
            ltrim(s);
            return s;
        }
        
        // trim from end (copying)
        static std::string rtrimmed(std::string s) {
            rtrim(s);
            return s;
        }
        
        // trim from both ends (copying)
        static std::string trimmed(std::string s) {
            trim(s);
            return s;
        }

    };
    
    
}

#endif /* _uStringUtils_h_ */
