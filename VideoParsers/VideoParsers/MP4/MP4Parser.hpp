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



#ifndef MP4Parser_hpp
#define MP4Parser_hpp

#include <iostream>
#include <memory>
#include <fstream>

#include <map>
#include <vector>

#include "PtrBuffer.hpp"

#include "Box.hpp"
#include "FullBox.hpp"
#include "FileTypeBox.hpp"
#include "FreeSpaceBox.hpp"
#include "MovieHeaderBox.hpp"
#include "MediaDataBox.hpp"
#include "TrackHeaderBox.hpp"
#include "EditListBox.hpp"
#include "MediaHeaderBox.hpp"
#include "HandlerReferenceBox.hpp"
#include "MP4ContainerBox.hpp"
#include "VideoMediaHeader.hpp"
#include "DataReferenceBox.hpp"
#include "SampleDescriptionBox.hpp"
#include "TimeToSampleBox.hpp"
#include "SyncSampleBox.hpp"
#include "SampleToChunkBox.hpp"
#include "SampleSizeBox.hpp"
#include "CompactSampleSizeBox.hpp"
#include "ChunkOffsetBox.hpp"
#include "ChunkLargeOffsetBox.hpp"
#include "ColourInformationBox.hpp"
#include "FieldOrderBox.hpp"
#include "CompositionOffsetBox.hpp"

#include "MovieBox.hpp"
#include "TrackBox.hpp"
#include "EditBox.hpp"
#include "MediaBox.hpp"
#include "MediaInformationBox.hpp"
#include "SampleTableBox.hpp"
#include "DataInformationBox.hpp"

#include "RootBox.hpp"

namespace VP
{
	class MP4Parser
	{
	public:
		MP4Parser(std::string filePath)
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
			root_ = std::make_shared<RootBox>();

			initParsers();
		}

        void analyze();
        void initParsers();
		
	private:
		MP4Parser(const MP4Parser& _rhs);
		MP4Parser& operator= (const MP4Parser& _rhs);

	private:
		std::shared_ptr<PtrBuffer> buffer_;
		std::shared_ptr<RootBox> root_;
		std::map<int,std::function<void(size_t&)>> names_;
	};
}

#endif /* MP4Parser_hpp */
