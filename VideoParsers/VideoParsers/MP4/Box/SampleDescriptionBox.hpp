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



#ifndef SampleDescriptionBox_hpp
#define SampleDescriptionBox_hpp

#include <stdio.h>
#include <iostream>

#include "PtrBuffer.hpp"
#include "Box.hpp"
#include "FullBox.hpp"
#include "VisualSampleEntry.hpp"
#include "AudioSampleEntry.hpp"

namespace VP
{
	//stsd
	class SampleDescriptionBox : public FullBox
	{
	public:
		SampleDescriptionBox(std::shared_ptr<PtrBuffer> buffer) : FullBox(buffer)
		{}

		virtual void parser(size_t& size)
		{
			FullBox::parser(size);

			entry_count_ = buffer_->readBig32();
			for(int i=0;i<entry_count_;i++)
			{
				std::shared_ptr<Box> box = std::make_shared<Box>(buffer_);
				box->analyze();

				if(box->getType() == Box::parseName("avc1"))
				{
					//video
					std::shared_ptr<VisualSampleEntry> box = std::make_shared<VisualSampleEntry>(buffer_);
					size_t boxSize = 0;
					box->parser(boxSize);

					video_ = box;
				}
				else if(box->getType() == Box::parseName("mp4a"))
				{
					//audio
					std::shared_ptr<AudioSampleEntry> box = std::make_shared<AudioSampleEntry>(buffer_);
					size_t boxSize = 0;
					box->parser(boxSize);

					audio_ = box;
				}

				//subtile
			}
		}

	protected:
		uint32_t entry_count_;
		std::shared_ptr<VisualSampleEntry> video_;
		std::shared_ptr<AudioSampleEntry> audio_;
	};
}

#endif /* SampleDescriptionBox_hpp */
