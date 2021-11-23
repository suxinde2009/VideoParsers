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



#ifndef MediaInformationBox_hpp
#define MediaInformationBox_hpp

#include <stdio.h>
#include <iostream>

#include "MP4ContainerBox.hpp"
#include "PtrBuffer.hpp"
#include "Box.hpp"

#include "VideoMediaHeader.hpp"
#include "DataInformationBox.hpp"
#include "SampleTableBox.hpp"

namespace VP
{
	//minf
	class MediaInformationBox : public MP4ContainerBox
	{
	public:
		MediaInformationBox(std::shared_ptr<PtrBuffer> buffer) : MP4ContainerBox(buffer)
		{
			isContainer_ = true;
		}

		virtual void parser(size_t& size)
		{
			MP4ContainerBox::parser(size);
		}

		void set(std::shared_ptr<VideoMediaHeader> value)
		{
			vmhd_ = value;
		}

		void set(std::shared_ptr<DataInformationBox> value)
		{
			dinf_ = value;
		}

		void set(std::shared_ptr<SampleTableBox> value)
		{
			stbl_ = value;
		}

		std::shared_ptr<DataInformationBox> dinf()
		{
			return dinf_;
		}

		std::shared_ptr<SampleTableBox> stbl()
		{
			return stbl_;
		}

	protected:
		std::shared_ptr<VideoMediaHeader> vmhd_;
		std::shared_ptr<DataInformationBox> dinf_;
		std::shared_ptr<SampleTableBox> stbl_;
	};
}

#endif /* MediaInformationBox_hpp */
