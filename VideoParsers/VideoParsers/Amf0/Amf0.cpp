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



#include "Amf0.hpp"

#include "Amf0Number.hpp"
#include "Amf0Boolean.hpp"
#include "Amf0String.hpp"
#include "Amf0Object.hpp"
#include "Amf0EcmaArray.hpp"
#include "Amf0Array.hpp"
#include "Amf0Date.hpp"
#include "Amf0LongString.hpp"

namespace VP
{
    void Amf0::initParser()
    {
        int key = Amf0::kNumber;
        names_[key] = [this](size_t& size){
            std::shared_ptr<Amf0Number> amf = std::make_shared<Amf0Number>(buffer_);
            amf->parser(size);

            return amf;
        };

        key = Amf0::kBoolean;
        names_[key] = [this](size_t& size){
            std::shared_ptr<Amf0Boolean> amf = std::make_shared<Amf0Boolean>(buffer_);
            amf->parser(size);

            return amf;
        };

        key = Amf0::kString;
        names_[key] = [this](size_t& size){
            std::shared_ptr<Amf0String> amf = std::make_shared<Amf0String>(buffer_);
            amf->parser(size);

            return amf;
        };

        key = Amf0::kObject;
        names_[key] = [this](size_t& size){
            std::shared_ptr<Amf0Object> amf = std::make_shared<Amf0Object>(buffer_);
            amf->parser(size);

            return amf;
        };

        key = Amf0::kArray;
        names_[key] = [this](size_t& size){
            std::shared_ptr<Amf0Object> amf = std::make_shared<Amf0Object>(buffer_);
            amf->parser(size);

            return amf;
        };

        key = Amf0::kEcmaArray;
        names_[key] = [this](size_t& size){
            std::shared_ptr<Amf0EcmaArray> amf = std::make_shared<Amf0EcmaArray>(buffer_);
            amf->parser(size);

            return amf;
        };

        key = Amf0::kDate;
        names_[key] = [this](size_t& size){
            std::shared_ptr<Amf0Date> amf = std::make_shared<Amf0Date>(buffer_);
            amf->parser(size);

            return amf;
        };

        key = Amf0::kLongString;
        names_[key] = [this](size_t& size){
            std::shared_ptr<Amf0LongString> amf = std::make_shared<Amf0LongString>(buffer_);
            amf->parser(size);

            return amf;
        };
    }
}

