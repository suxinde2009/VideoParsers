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



#ifndef AudioSampleEntry_hpp
#define AudioSampleEntry_hpp

#include <stdio.h>
#include <iostream>

#include "PtrBuffer.hpp"
#include "Box.hpp"

namespace VP
{
	//audio SampleEntry
	class AudioSampleEntry : public Box
	{
	public:
		AudioSampleEntry(std::shared_ptr<PtrBuffer> buffer) : Box(buffer)
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

			reserveds_[0] = buffer_->readBig32();
			reserveds_[1] = buffer_->readBig32();

			channelcount_ = buffer_->readBig16();
			samplesize_   = buffer_->readBig16();

			pre_defined_  = buffer_->readBig16();
			reserved1_   = buffer_->readBig16();
			samplerate_  = buffer_->readBig32() >> 16;
		}

	protected:
		uint32_t reserveds_[2];
		uint16_t channelcount_;
		uint16_t samplesize_;
		uint16_t pre_defined_;
		uint16_t reserved1_;
		uint32_t samplerate_;
	};
}

#endif /* AudioSampleEntry_hpp */
