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



#ifndef GlomobDecoder_hpp
#define GlomobDecoder_hpp

#include <stdio.h>
#include <iostream>
#include <bitset>
#include <math.h>

#include "BitBuffer.hpp"

namespace VP
{
    //test https://en.wikipedia.org/wiki/Exponential-Golomb_coding
    //9.1 Parsing process for Exp-Golomb codes
    class Golomb
    {
    public:
        Golomb()
        {}
        
        //codeNum = 2^leadingzerobits − 1 + read_bits( leadingZeroBits )
        static int read_ue(std::shared_ptr<BitBuffer> buffer)
        {
            int result = 0;
            int leadingzerobits = 0;
            int tail = 0;

			while (!buffer->isFull())
			{
				int32_t bit = buffer->readBit(1);
				if(bit == 0)
				{
					leadingzerobits++;
				}
				else
				{
					break;
				}
			}

            for(int i=0;i<leadingzerobits;i++)
            {
				if(buffer->isFull()) return -1;

                int32_t bit = buffer->readBit(1);
                tail = tail << 1 | bit;
            }
            
            return result = pow(2, leadingzerobits) - 1 + tail;
        }
        
        static int read_se(std::shared_ptr<BitBuffer> buffer)
        {
            int result = read_ue(buffer);

			if(result == -1) return -1;

            if(result & 0x01)
            {
                result = (result + 1) >> 1;
            }
            else
            {
                result = - result >> 1;
            }
            
            return result;
        }
    };
}

#endif /* GolombDecoder_hpp */
