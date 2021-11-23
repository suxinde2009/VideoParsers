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



#ifndef FLVTag_hpp
#define FLVTag_hpp

#include <stdio.h>
#include <iostream>

#include "PtrBuffer.hpp"

namespace VP
{
    class FLVTag
	{
    public:
        FLVTag(std::shared_ptr<PtrBuffer> buffer)
        {
            buffer_  = buffer;
            type_ = -1;
            size_ = 0;
            timestamp_ = 0;
        }
        
        virtual void parser(size_t& size);
        ~FLVTag(){};
        
    private:
        FLVTag(const FLVTag& _rhs);
        FLVTag& operator= (const FLVTag& _rhs);
        
    protected:
        int type_;
        size_t size_;
        int64_t timestamp_;
        std::shared_ptr<PtrBuffer> buffer_;
    };
}

#endif /* FLVTag_hpp */
