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



#ifndef SampleTableBox_hpp
#define SampleTableBox_hpp

#include <stdio.h>
#include <iostream>

#include "MP4ContainerBox.hpp"
#include "PtrBuffer.hpp"
#include "Box.hpp"

#include "SampleDescriptionBox.hpp"
#include "TimeToSampleBox.hpp"
#include "SyncSampleBox.hpp"
#include "SampleToChunkBox.hpp"
#include "SampleSizeBox.hpp"
#include "CompactSampleSizeBox.hpp"
#include "ChunkOffsetBox.hpp"
#include "ChunkLargeOffsetBox.hpp"
#include "CompositionOffsetBox.hpp"

namespace VP
{
	//stbl
	class SampleTableBox : public MP4ContainerBox
	{
	public:
		SampleTableBox(std::shared_ptr<PtrBuffer> buffer) : MP4ContainerBox(buffer)
		{
			isContainer_ = true;
		}

		virtual void parser(size_t& size)
		{
			MP4ContainerBox::parser(size);
		}

		void set(std::shared_ptr<SampleDescriptionBox> value)
		{
			stsd_ = value;
		}

		void set(std::shared_ptr<TimeToSampleBox> value)
		{
			stts_ = value;
		}

		void set(std::shared_ptr<SyncSampleBox> value)
		{
			stss_ = value;
		}

		void set(std::shared_ptr<SampleToChunkBox> value)
		{
			stsc_ = value;
		}

		void set(std::shared_ptr<SampleSizeBox> value)
		{
			stsz_ = value;
		}

		void set(std::shared_ptr<ChunkOffsetBox> value)
		{
			stco_ = value;
		}

		void set(std::shared_ptr<CompositionOffsetBox> value)
		{
			ctts_ = value;
		}

		void set(std::shared_ptr<CompactSampleSizeBox> value)
		{
			stz2_ = value;
		}

		void set(std::shared_ptr<ChunkLargeOffsetBox> value)
		{
			co64_ = value;
		}

	protected:
		std::shared_ptr<SampleDescriptionBox> stsd_;
		std::shared_ptr<TimeToSampleBox> stts_;
		std::shared_ptr<SyncSampleBox> stss_;
		std::shared_ptr<SampleToChunkBox> stsc_;
		std::shared_ptr<SampleSizeBox> stsz_;
		std::shared_ptr<ChunkOffsetBox> stco_;

		std::shared_ptr<CompositionOffsetBox> ctts_;
		std::shared_ptr<CompactSampleSizeBox> stz2_;
		std::shared_ptr<ChunkLargeOffsetBox> co64_;
	};
}

#endif /* SampleTableBox_hpp */
