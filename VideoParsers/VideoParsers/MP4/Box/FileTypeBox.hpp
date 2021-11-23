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



#ifndef FileTypeBox_hpp
#define FileTypeBox_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "PtrBuffer.hpp"
#include "Box.hpp"

namespace VP
{
    //ftyp
	class FileTypeBox : public Box
	{
	public:
		FileTypeBox(std::shared_ptr<PtrBuffer> buffer) : Box(buffer)
		{}

		virtual void parser(size_t& size)
		{
			Box::parser(size);

			major_brand_   = buffer_->readLittle32();
			minor_version_ = buffer_->readBig32();

            size_t currentSize = size_ - 16;
            
			if(currentSize >= 12)
			{
				while (currentSize >= 4)
				{
					uint32_t brands = buffer_->readBig32();
					compatible_brands_.push_back(brands);
					currentSize -= 4;
				}
			}
		}

	protected:
		uint32_t major_brand_;  //mp42
		uint32_t minor_version_;    //1
		std::vector<int32_t> compatible_brands_; //12 mp41mp42isom
	};
}

#endif /* FileTypeBox_hpp */
