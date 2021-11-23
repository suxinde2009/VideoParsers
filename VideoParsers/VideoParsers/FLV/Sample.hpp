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



#ifndef Sample_hpp
#define Sample_hpp

#include <stdio.h>
#include <iostream>

#include "PtrBuffer.hpp"

namespace VP
{
	class Sample
	{
	public:
		Sample(void* _pBuffer, size_t len)
		{
			buffer_ = std::make_shared<PtrBuffer>(_pBuffer,len);
			length_ = len;
			isKeyframe_ = false;
			dts_ = 0;
			cts_ = 0;
			pts_ = 0;
            
            sampleRate_ = 0;
            bitRate_    = 0;
            channelCount_ = 0;
		}

		~Sample()
		{}

	public:
		int64_t length_;

		//video
		bool isKeyframe_;

		//audio
		int sampleRate_;
		int bitRate_;
		int8_t channelCount_;
		
		//common
		int64_t dts_;
		int64_t cts_;
		int64_t pts_;
		std::shared_ptr<PtrBuffer> buffer_;
	};
}

#endif /* Sample_hpp */
