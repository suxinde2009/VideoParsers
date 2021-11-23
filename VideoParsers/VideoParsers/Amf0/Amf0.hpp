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



#ifndef Amf0_hpp
#define Amf0_hpp

#include <stdio.h>
#include <iostream>
#include <map>

#include "PtrBuffer.hpp"

namespace VP
{
    class Amf0
    {
        typedef std::function<std::shared_ptr<Amf0>(size_t&)> FN;
        
    public:
        enum Type
        {
            kNumber      = 0x00,
            kBoolean     = 0x01,
            kString      = 0x02,
            kObject      = 0x03,
            kMovieClip   = 0x04,
            kNull        = 0x05,
            kUndefined   = 0x06,
            kReference   = 0x07,
            kEcmaArray   = 0x08,
            kEndOfObject = 0x09,
            kArray       = 0x0A,
            kDate        = 0x0B,
            kLongString  = 0x0C,
            kUnsupported = 0x0D,
        };
        
        Amf0(std::shared_ptr<PtrBuffer> buffer)
        {
            buffer_ = buffer;
            type_   = kNull;
        }
        
        virtual void analyze()
        {
            type_ = (Type)buffer_->read8(0, false);
        }
        
        virtual void parser(size_t& size)
        {
            type_ = (Type)buffer_->read8();
        }
        
        virtual void parseValue(size_t& size)
        {}
        
        ~Amf0(){};
        
        void initParser();
        
        void setNames(std::map<int,FN> names)
        {
            names_ = names;
        }
        
        Type getType() const
        {
            return type_;
        }
        
        uint64_t getLength() const
        {
            return length_;
        }
        
    private:
        Amf0(const Amf0& _rhs);
        Amf0& operator= (const Amf0& _rhs);
        
    protected:
        Type type_;
        uint64_t length_;
        std::shared_ptr<PtrBuffer> buffer_;
        std::map<int,FN> names_;
    };
}

#endif /* Amf0_hpp */
