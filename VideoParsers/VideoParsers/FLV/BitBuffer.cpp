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



#include "BitBuffer.hpp"

namespace VP
{
	//big endian
    int BitBuffer::readBit(size_t len)
    {
        if(len <= 0) return -1;
        
        int value = 0;
        
        size_t nRead = length_ - pos_;
        nRead = std::min(nRead, len);

		for(int i=0;i<nRead;i++)
		{
			value <<= 1;

			size_t index_i = pos_ / 8;
			size_t index_j = pos_ % 8;

			uint8_t current = buffer_[index_i];

			if(current & (0x80 >> index_j))
			{
				value |= 1;
			}
			pos_++;
		}

        return value;
    }

	void BitBuffer::skip(size_t len)
	{
		if(len <= 0) return;

		size_t nRead = length_ - pos_;
		nRead = std::min(nRead, len);

		pos_ += nRead;
	}
}
