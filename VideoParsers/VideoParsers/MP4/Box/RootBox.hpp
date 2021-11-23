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



#ifndef RootBox_hpp
#define RootBox_hpp

#include <stdio.h>
#include <iostream>

#include "FileTypeBox.hpp"
#include "FreeSpaceBox.hpp"
#include "MovieBox.hpp"

namespace VP
{
	//root
	class RootBox
	{
	public:
		RootBox()
		{
		}

		void set(std::shared_ptr<FileTypeBox> value)
		{
			ftyp_ = value;
		}

		void set(std::shared_ptr<FreeSpaceBox> value)
		{
			free_ = value;
		}

		void set(std::shared_ptr<MovieBox> value)
		{
			moov_ = value;
		}

		std::shared_ptr<MovieBox> moov()
		{
			return moov_;
		}

	protected:
		std::shared_ptr<FileTypeBox> ftyp_;
		std::shared_ptr<FreeSpaceBox> free_;
		std::shared_ptr<MovieBox> moov_;
	};
}

#endif /* RootBox_hpp */
