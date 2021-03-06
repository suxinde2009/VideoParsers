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



#ifndef FLVHeaderParser_hpp
#define FLVHeaderParser_hpp

#include <stdio.h>
#include <iostream>

#include "PtrBuffer.hpp"

namespace VP
{
    class FLVHeaderParser
    {
    public:
        FLVHeaderParser(std::shared_ptr<PtrBuffer> buffer)
        {
            buffer_  = buffer;
            hasVideo_ = false;
            hasAudio_ = false;
        }
        
        void parser(size_t& size)
        {
            int ch_F = buffer_->read8();
            int ch_L = buffer_->read8();
            int ch_V = buffer_->read8();
            
            int version = buffer_->read8();
            int flags = buffer_->read8();
            
            int dataOffset = buffer_->readBig32();
            
            if(ch_F != 0x46 || ch_L != 0x4c || ch_V != 0x56 || version != 0x01 || dataOffset != 0x09)
            {
                std::cout<<"invalid flv format"<<std::endl;
            }
            
            hasAudio_ = flags & 0x04;
            hasVideo_ = flags & 0x01;
            
            size = 9;
        }
    
        ~FLVHeaderParser(){};
        
    private:
        FLVHeaderParser(const FLVHeaderParser& _rhs);
        FLVHeaderParser& operator= (const FLVHeaderParser& _rhs);
        
    protected:
        bool hasVideo_;
        bool hasAudio_;
        std::shared_ptr<PtrBuffer> buffer_;
    };
}

#endif /* FLVHeaderParser_hpp */
