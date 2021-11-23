/**
 ==============================================================================
 MIT License
 
 Copyright (c) 2011-Present __承_影__
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 ==============================================================================
 */



#ifndef AMFParser_hpp
#define AMFParser_hpp

#include <iostream>
#include <memory>
#include <fstream>

#include <vector>

#include "Amf0.hpp"
#include "Amf0Number.hpp"
#include "Amf0Boolean.hpp"
#include "Amf0String.hpp"
#include "Amf0Object.hpp"
#include "Amf0EcmaArray.hpp"
#include "Amf0Array.hpp"
#include "Amf0Date.hpp"
#include "Amf0LongString.hpp"

#include "PtrBuffer.hpp"

namespace VP
{
    class AMFParser
    {
    public:
        AMFParser(std::shared_ptr<PtrBuffer> buffer) : buffer_(buffer)
        {
            initParsers();
        }
        
        void parser(size_t& size);
        void initParsers();
        
    private:
        AMFParser(const AMFParser& _rhs);
        AMFParser& operator= (const AMFParser& _rhs);
        
    private:
        std::shared_ptr<PtrBuffer> buffer_;
        std::vector<std::shared_ptr<Amf0>> results_;
        std::map<int,std::function<void(size_t&)>> names_;
    };
}

#endif /* AMFParser_hpp */
