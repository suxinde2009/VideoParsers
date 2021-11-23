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



#ifndef HandlerReferenceBox_hpp
#define HandlerReferenceBox_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "PtrBuffer.hpp"
#include "Box.hpp"
#include "FullBox.hpp"

namespace VP
{
	//hdlr
	class HandlerReferenceBox : public FullBox
	{
	public:
		HandlerReferenceBox(std::shared_ptr<PtrBuffer> buffer) : FullBox(buffer)
		{}

		virtual void parser(size_t& size)
		{
			FullBox::parser(size);

			pre_defined_  = buffer_->readBig32();
			handler_type_ = buffer_->readBig32();

			for(int i=0;i<3;i++)
			{
				reserved_[i] = buffer_->readBig32();
			}

			if(handler_type_ == Box::parseName("vide"))
			{
				//video
			}
			else if(handler_type_ == Box::parseName("soun"))
			{
				//aduio
			}
			else if(handler_type_ == Box::parseName("mla "))
			{
				//mp2
			}
			else if(handler_type_ == Box::parseName("subp")
					|| handler_type_ == Box::parseName("clcp"))
			{
				//subtitle
			}

			size_t len = size_ - 24 - 8;
			while(len > 0)
			{
				uint8_t val = 0;
				buffer_->read(val);
				name_ += char(val);
				len--;
			}
		}

	protected:
		uint32_t pre_defined_;
		uint32_t handler_type_;
		uint32_t reserved_[3];
		std::string name_;
	};
}

#endif /* HandlerReferenceBox_hpp */
