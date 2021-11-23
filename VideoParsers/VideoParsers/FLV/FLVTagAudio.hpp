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



#ifndef FLVTagAudio_hpp
#define FLVTagAudio_hpp

#include <iostream>

#include "PtrBuffer.hpp"
#include "FLVTag.hpp"
#include "BitBuffer.hpp"

namespace VP
{
	struct MP3Header
	{
		uint16_t syn_;			//u(11)
		uint8_t version_;		//u(2)
		uint8_t layer_;			//u(2)
		uint8_t protection_;	//u(1)
		uint8_t bitrate_;		//u(4)
		uint8_t frequency_;		//u(2)
		uint8_t padding_;		//u(1)
		uint8_t private_;		//u(1)
		//00-立体声  01-Joint Stereo 10-双声道 11-单声道 (默认双声道)
		uint8_t mode_;			//u(2)
		uint8_t mode_extension_;//u(2)
		uint8_t copyright_;		//u(1)
		uint8_t original_;		//u(1)
		uint8_t emphasis_;		//u(2)
	};

	struct ACCHeader
	{
		uint8_t audioObjectType_;				//u(5)
		uint8_t samplingFrequencyIndex_;		//u(4)
		uint8_t channelConfiguration_;			//u(4)
		uint8_t extensionSamplingIndex_;		//u(4)
		uint8_t extensionAudioObjectType_;
	};

	class FLVTagAudio : public FLVTag
	{
	public:
		FLVTagAudio(std::shared_ptr<PtrBuffer> buffer) : FLVTag(buffer)
		{}

		virtual void parser(size_t& size);
		void parse_acc(size_t size);
		void parse_mp3(size_t size);
		
	protected:
		int8_t soundFormat_;
		int8_t soundRate_;
		int8_t soundSize_;
		int8_t soundType_;
		int8_t aacPacketType_;
	};
}

#endif /* FLVTagAudio_hpp */
