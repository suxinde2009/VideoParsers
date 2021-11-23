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



#ifndef Amf0Object_hpp
#define Amf0Object_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <cassert>

#include "PtrBuffer.hpp"
#include "Amf0.hpp"

namespace VP
{
    //video_file_format_spec_v10_1 - SCRIPTDATAOBJECT
    class Amf0Object : public Amf0
    {
    public:
        Amf0Object(std::shared_ptr<PtrBuffer> buffer) : Amf0(buffer)
        {
            initParser();
        }
        
        virtual void parser(size_t& size)
        {
            Amf0::parser(size);
            
            // 4 === type(UI8) + ScriptDataObjectEnd(UI24)
            int64_t length = size - 4;
            size_t skip_size = 0;
            
            while (true)
            {
                if(length <= 0) break;
                
                std::shared_ptr<Amf0> amf = std::make_shared<Amf0>(buffer_);
                amf->analyze();
                
                if(amf->getType() == kEndOfObject
                   || amf->getType() == kUndefined
                   || amf->getType() == kNull
                   || amf->getType() == kUnsupported)
                    break;
                
                auto fn = names_[amf->getType()];
                if(fn != nullptr)
                {
                    size_t len = length;
                    push(fn(len));
                    skip_size = len;
                }
                
                length -= skip_size;
                skip_size = 0;
            }
        }
        
        void push(std::shared_ptr<Amf0> obj)
        {
            values_.push_back(obj);
        }
        
    private:
        std::vector<std::shared_ptr<Amf0>> values_;
    };
}

#endif /* Amf0Object_hpp */
