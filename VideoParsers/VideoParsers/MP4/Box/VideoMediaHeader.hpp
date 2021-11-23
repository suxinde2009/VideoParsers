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



#ifndef VideoMediaHeader_hpp
#define VideoMediaHeader_hpp

#include <stdio.h>
#include <iostream>

#include "PtrBuffer.hpp"
#include "Box.hpp"
#include "FullBox.hpp"

namespace VP
{
	//vmhd
	class VideoMediaHeader : public FullBox
	{
	public:
		VideoMediaHeader(std::shared_ptr<PtrBuffer> buffer) : FullBox(buffer)
		{}

		virtual void parser(size_t& size)
		{
			FullBox::parser(size);

			graphicsmode_  = buffer_->readBig16();

			for(int i=0;i<3;i++)
			{
				opcolor_[i] = buffer_->readBig16();
			}
		}

	protected:
		uint16_t graphicsmode_;
		uint16_t opcolor_[3];
	};
}

#endif /* VideoMediaHeader_hpp */
