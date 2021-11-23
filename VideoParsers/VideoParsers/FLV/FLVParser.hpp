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


#ifndef FLVParser_hpp
#define FLVParser_hpp

#include <iostream>
#include <memory>
#include <fstream>

#include <vector>

#include "PtrBuffer.hpp"
#include "FLVHeaderParser.hpp"
#include "FLVTag.hpp"
#include "FLVTagVideo.hpp"
#include "FLVTagAudio.hpp"
#include "AMFParser.hpp"

namespace VP
{
    class FLVParser
    {
    public:
        FLVParser(std::string filePath)
        {
            std::ifstream file;
            file.open(filePath);
            
            file.seekg(0,std::ios::end);
            int64_t length = file.tellg();
            file.seekg(0,std::ios::beg);
            
            char* buffer = new char[length];
            file.read(buffer, length);
            file.close();
            
            buffer_ = std::make_shared<PtrBuffer>((void*)buffer,length);
        }
        
        void parse()
        {
            int64_t length = buffer_->length();
            size_t skip_size = 0;
            
            if(length <= 9+4) return;
            
            header_ = std::make_shared<FLVHeaderParser>(buffer_);
            header_->parser(skip_size);
            length -= skip_size;
            
            while (true)
            {
                if(length <= 4) break;
                
                //PreviousTagSize
                int len = buffer_->readBig32();
                std::cout<<"PreviousTagSize = "<<len<<std::endl;
                
                length -= 4;
                
                //tag
                std::shared_ptr<FLVTag> tag = std::make_shared<FLVTag>(buffer_);
                skip_size = length;
                tag->parser(skip_size);
                
                length -= skip_size;
                skip_size = 0;
            }
        }
        
    private:
        FLVParser(const FLVParser& _rhs);
        FLVParser& operator= (const FLVParser& _rhs);
        
    private:
        std::shared_ptr<PtrBuffer> buffer_;
        std::shared_ptr<FLVHeaderParser> header_;
    };
}

#endif /* FLVParser_hpp */
