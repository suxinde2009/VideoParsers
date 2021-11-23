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



#ifndef SampleToChunkBox_hpp
#define SampleToChunkBox_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "PtrBuffer.hpp"
#include "Box.hpp"
#include "FullBox.hpp"

namespace VP
{
	//stsc
	class SampleToChunkBox : public FullBox
	{
		typedef struct {
			uint32_t first_chunk_;
			uint32_t samples_per_chunk_;
			uint32_t sample_description_index_;
		} stsc;

	public:
		SampleToChunkBox(std::shared_ptr<PtrBuffer> buffer) : FullBox(buffer)
		{}

		virtual void parser(size_t& size)
		{
			FullBox::parser(size);

			entry_count_ = buffer_->readBig32();
			for(int i=0;i<entry_count_;i++)
			{
				std::shared_ptr<stsc> elem = std::make_shared<stsc>();
				elem->first_chunk_ = buffer_->readBig32();
				elem->samples_per_chunk_ = buffer_->readBig32();
				elem->sample_description_index_ = buffer_->readBig32();
				entries_.push_back(elem);
			}
		}

	protected:
		uint32_t entry_count_;
		std::vector<std::shared_ptr<stsc>> entries_;
	};
}


#endif /* SampleToChunkBox_hpp */
