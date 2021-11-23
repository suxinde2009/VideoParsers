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



#ifndef VisualSampleEntry_hpp
#define VisualSampleEntry_hpp

#include <stdio.h>
#include <iostream>

#include "PtrBuffer.hpp"
#include "Box.hpp"

namespace VP
{
	//video SampleEntry
	class VisualSampleEntry : public Box
	{
	public:
		VisualSampleEntry(std::shared_ptr<PtrBuffer> buffer) : Box(buffer)
		{}

		virtual void parser(size_t& size)
		{
			Box::parser(size);

			if(size_ > 16)
			{
				buffer_->readBig32();
				buffer_->readBig16();
				buffer_->readBig16();	//dref id
			}

			pre_defined1_ = buffer_->readBig16();
			reserved1_ = buffer_->readBig16();
			for(int i=0;i<3;i++)
			{
				pre_defineds_[i] = buffer_->readBig32();
			}
			width_  = buffer_->readBig16();
			height_ = buffer_->readBig16();

			horizresolution_  = buffer_->readBig32();
			vertresolution_ = buffer_->readBig32();

			reserved2_ = buffer_->readBig32();
			frame_count_ = buffer_->readBig16();

			int len = buffer_->read8();
			if(len > 31)
			{
				len = 31;
				for(int i=0;i<len;i++)
				{
					compressorname_ += char(buffer_->read8());
				}
			}
			else
			{
				buffer_->skip(31-len);
			}
			
			depth_ = buffer_->readBig16();
			pre_defined2_ = buffer_->readBig16();
		}

	protected:
		uint16_t pre_defined1_;
		uint16_t reserved1_;
		uint32_t pre_defineds_[3];
		uint16_t width_;
		uint16_t height_;
		uint32_t horizresolution_;
		uint32_t vertresolution_;
		uint32_t reserved2_;
		uint16_t frame_count_;
		std::string compressorname_;
		uint16_t depth_;
		uint16_t pre_defined2_;
	};
}

#endif /* VisualSampleEntry_hpp */
