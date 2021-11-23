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



#ifndef FLVTagVideo_hpp
#define FLVTagVideo_hpp

#include <stdio.h>
#include <iostream>

#include "PtrBuffer.hpp"
#include "FLVTag.hpp"
#include "SPSParser.hpp"

namespace VP
{
	struct AVCDecoderConfigurationRecord
	{
		uint8_t configurationVersion;
		uint8_t avcProfileIndication;
		uint8_t profile_compatibility;
		uint8_t AVCLevelIndication;
		uint8_t naluLengthSize;
		uint8_t numOfSequenceParameterSets;
		uint8_t numOfPictureParameterSets;
	};
	
    class FLVTagVideo : public FLVTag
    {
    public:
        FLVTagVideo(std::shared_ptr<PtrBuffer> buffer) : FLVTag(buffer)
        {
            frameType_ = -1;
            codecID_   = -1;
            avcPacketType_ = -1;
            cts_ = 0;
        }
        
        virtual void parser(size_t& size);
        ~FLVTagVideo(){};

		void setTimestamp(int64_t timestamp)
		{
			timestamp_ = timestamp;
		}

    private:
        FLVTagVideo(const FLVTagVideo& _rhs);
        FLVTagVideo& operator= (const FLVTagVideo& _rhs);
        
    protected:
        int frameType_;
        int codecID_;
        int avcPacketType_;
        int cts_;
		int64_t timestamp_;
    };
}

#endif /* FLVTagVideo_hpp */
