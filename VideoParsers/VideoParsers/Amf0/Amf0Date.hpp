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



#ifndef Amf0Date_hpp
#define Amf0Date_hpp

#include <stdio.h>
#include <iostream>

#include "PtrBuffer.hpp"
#include "Amf0.hpp"

namespace VP
{
    //video_file_format_spec_v10_1 - SCRIPTDATADATE
    class Amf0Date : public Amf0
    {
    public:
        Amf0Date(std::shared_ptr<PtrBuffer> buffer) : Amf0(buffer)
        {}
        
        virtual void parser(size_t& size)
        {
            Amf0::parser(size);
            parseValue(size);
            size += 1;
        }
        
        virtual void parseValue(size_t& size)
        {
            length_ = 10;
            value_  = buffer_->readBig64();
            
            //SI16
            int timestamp = 0;
            buffer_->read(&timestamp, 2, true);;
            
            //UTC time
            value_ += timestamp * 60 * 1000;
            
            size = length_;
        }
        
    private:
        double value_;
    };
}

#endif /* Amf0Date_hpp */
