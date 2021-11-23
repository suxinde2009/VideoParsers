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



#ifndef Box_hpp
#define Box_hpp

#include <stdio.h>
#include <iostream>

#include "PtrBuffer.hpp"

namespace VP
{
	class Box
	{
	public:
		Box(std::shared_ptr<PtrBuffer> buffer)
		{
			type_ = 0;
			size_ = 0;
			isContainer_ = false;
			buffer_ = buffer;
		}

		virtual void parser(size_t& size)
		{
			size_ = buffer_->readBig32();
			type_ = buffer_->readLittle32();

			if(size_ == 1)
			{
				size_ = buffer_->readBig64() - 8;
			}
			else if(size_ == 0)
			{
				//end of box
			}

			size_t copySize = size_;
			size = copySize;
		}

		virtual void analyze()
		{
			size_ = buffer_->readBig32(0, false);
			type_ = buffer_->readBig32(4, false);

            printTypeName(type_);
            
			if(size_ == 1)
			{
				size_ = buffer_->readBig64(8, false) - 8;
			}
			else if(size_ == 0)
			{
				return;
			}
		}

		static int parseName(const std::string& str)
		{
			if(str.length() < 4) return -1;
			int val = str[0]<<24 | str[1]<<16 | str[2]<<8 | str[3];
			return val;
		}
        
        void printTypeName(int32_t number)
        {
            char ch1st = char(number>>24);
            
            int temp = number << 8;
            char ch2nd = char(temp>>24);
            
            temp = number << 16;
            char ch3rd = char(temp>>24);
            
            temp = number << 24;
            char ch4th = char(temp>>24);
            
            std::cout<<ch1st<<ch2nd<<ch3rd<<ch4th<<std::endl;
        }

		int64_t getSize() const
		{
			return size_;
		}

		uint32_t getType() const
		{
			return type_;
		}

	private:
		Box(const Box& _rhs);
		Box& operator= (const Box& _rhs);
		
	protected:
		int64_t size_;
		uint32_t type_;
		bool isContainer_;
		std::shared_ptr<PtrBuffer> buffer_;
	};
}

#endif /* Box_hpp */
