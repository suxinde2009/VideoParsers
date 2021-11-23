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



#ifndef BitBuffer_hpp
#define BitBuffer_hpp

#include <stdio.h>
#include <iostream>
#include <bitset>
#include <math.h>
#include <cassert>

namespace VP
{
    class BitBuffer
    {
    public:
        BitBuffer(void* _ptr,size_t _len) :
        buffer_((unsigned char*)_ptr)
        , pos_(0)
        , length_(_len*8)
        {
        }
        
        int readBit(size_t len = 1);
		void skip(size_t len);

        ~BitBuffer()
        {
            delete[] buffer_;
            
            buffer_ = NULL;
            pos_ = 0;
            length_ = 0;
        }
        
        size_t length() const
        {
            return length_;
        }

		bool isFull() const
		{
			return length_ == pos_;
		}

    private:
        BitBuffer(const BitBuffer& _rhs);
        BitBuffer& operator= (const BitBuffer& _rhs);
        
    protected:
        unsigned char* buffer_;
        size_t pos_;
        size_t length_;
    };
}

#endif /* BitBuffer_hpp */
