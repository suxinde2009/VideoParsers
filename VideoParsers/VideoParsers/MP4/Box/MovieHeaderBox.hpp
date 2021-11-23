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



#ifndef MovieHeaderBox_hpp
#define MovieHeaderBox_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "PtrBuffer.hpp"
#include "Box.hpp"
#include "FullBox.hpp"

namespace VP
{
    //mvhd
    class MovieHeaderBox : public FullBox
    {
    public:
        MovieHeaderBox(std::shared_ptr<PtrBuffer> buffer) : FullBox(buffer)
        {
			matrix_ = std::vector<std::vector<double>>(3,std::vector<double>(3));
		}
        
        virtual void parser(size_t& size)
        {
            FullBox::parser(size);
            
            if(version_ == 1)
            {
                //64
				creation_time_     = buffer_->readBig64();
				modification_time_ = buffer_->readBig64();
				timescale_         = buffer_->readBig32();
				duration_          = buffer_->readBig64();
            }
            else
            {
                //32
				creation_time_     = buffer_->readBig32();
				modification_time_ = buffer_->readBig32();
				timescale_         = buffer_->readBig32();
				duration_          = buffer_->readBig32();
            }

			rate_   = buffer_->readBig32() >> 16;
			volume_ = buffer_->readBig16() >> 8;
			reserved_[0] = buffer_->readBig16();
			reserved_[1] = buffer_->readBig32();
			reserved_[2] = buffer_->readBig32();

			for(int i=0;i<3;i++)
			{
				matrix_[i][0] = buffer_->readBig32() >> 16;
				matrix_[i][1] = buffer_->readBig32() >> 16;
				matrix_[i][2] = buffer_->readBig32() >> 30;
			}

			for(int i=0;i<6;i++)
			{
				pre_defined_[i] = buffer_->readBig32();
			}

			next_track_ID_ = buffer_->readBig32();
        }
        
    protected:
        uint64_t creation_time_;
        uint64_t modification_time_;
        uint32_t timescale_;
        uint64_t duration_;
        uint32_t rate_;             //16.16
        uint16_t volume_;           //8.8
        uint32_t reserved_[3];
		std::vector<std::vector<double>> matrix_;
        uint32_t pre_defined_[6];
        uint32_t next_track_ID_;
    };
}

#endif /* MovieHeaderBox_hpp */
