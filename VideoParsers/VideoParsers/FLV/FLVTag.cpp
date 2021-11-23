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



#include "FLVTag.hpp"
#include "FLVTagVideo.hpp"
#include "FLVTagAudio.hpp"
#include "AMFParser.hpp"

namespace VP
{
    void FLVTag::parser(size_t& size)
    {
        type_ = buffer_->read8() & 0x1f;
        size_ = buffer_->readBig24();
        int64_t time = buffer_->readBig24();
        timestamp_ = buffer_->read8() << 24 | time;
        
        //streamid
        buffer_->readBig24();
        
        size_t skip_size = size_;
        
        //video/audio/script
        if(type_ == 8)
        {
            //audio
			std::shared_ptr<FLVTagAudio> tag = std::make_shared<FLVTagAudio>(buffer_);
			tag->parser(skip_size);
        }
        else if(type_ == 9)
        {
            //video
            std::shared_ptr<FLVTagVideo> tag = std::make_shared<FLVTagVideo>(buffer_);
			tag->setTimestamp(timestamp_);
            tag->parser(skip_size);
        }
        else if(type_ == 18)
        {
            //script
            std::shared_ptr<AMFParser> amf = std::make_shared<AMFParser>(buffer_);
            amf->parser(skip_size);
        }
        
        size = size_ + 11;
    }
}
