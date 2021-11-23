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



#include "PtrBuffer.hpp"

namespace VP
{
    size_t PtrBuffer::read(void* _pBuffer, size_t _nLen, off_t _nPos, bool isSeek)
    {
        size_t nRead = length_ - _nPos;
        nRead = std::min(nRead, _nLen);
        memcpy(_pBuffer, buffer_ + _nPos, nRead);
        
        if(isSeek)
        {
            pos_ = pos_ + nRead;
        }
        
        return nRead;
    }
    
    //read
    size_t PtrBuffer::read(void* _pBuffer, size_t _len, bool isSeek)
    {
        if(_pBuffer == NULL) return -1;
        
        size_t nRead = read(_pBuffer, _len, pos_, isSeek);
        return nRead;
    }
    
    uint8_t PtrBuffer::read8(size_t offset, bool isSeek)
    {
        size_t nPos = pos_ + offset;
        
        uint8_t val = 0;
        read(nPos, val, isSeek);
        return val;
    }
    
    //little endian
    uint16_t PtrBuffer::readLittle16(size_t offset, bool isSeek)
    {
        size_t nPos = pos_ + offset;
        
        uint16_t val = 0;
        read(nPos, val, isSeek);
        return val;
    }
    
    unsigned int PtrBuffer::readLittle24(size_t offset, bool isSeek)
    {
        unsigned int val = 0;
        
        val = readLittle16(offset, isSeek);
        offset += 2;
        val |= read8(offset, isSeek) << 16;
        return val;
    }
    
    uint32_t PtrBuffer::readLittle32(size_t offset, bool isSeek)
    {
        size_t nPos = pos_ + offset;
        
        uint32_t val = 0;
        read(nPos, val, isSeek);
        return val;
    }
    
    uint64_t PtrBuffer::readLittle64(size_t offset, bool isSeek)
    {
        size_t nPos = pos_ + offset;
        
        uint64_t val = 0;
        read(nPos, val,isSeek);
        return val;
    }
    
    //big endian
    uint16_t PtrBuffer::readBig16(size_t offset, bool isSeek)
    {
        unsigned int val = 0;
        
        val = read8(offset, isSeek) << 8;
        offset = isSeek ? 0 : offset+1;
        val |= read8(offset, isSeek);
        return val;
    }
    
    unsigned int PtrBuffer::readBig24(size_t offset, bool isSeek)
    {
        unsigned int val = 0;
        
        val = readBig16(offset, isSeek) << 8;
        offset = isSeek ? 0 : offset+2;
        val |= read8(offset, isSeek);
        return val;
    }
    
    uint32_t PtrBuffer::readBig32(size_t offset, bool isSeek)
    {
        unsigned int val = 0;
        
        val = readBig16(offset, isSeek) << 16;
        offset = isSeek ? 0 : offset+2;
        val |= readBig16(offset, isSeek);
        return val;
    }
    
    uint64_t PtrBuffer::readBig64(size_t offset, bool isSeek)
    {
        uint64_t val = 0;
        val = (uint64_t)readBig32(offset, isSeek) << 32;
        offset = isSeek ? 0 : offset+4;
        val |= (uint64_t)readBig32(offset, isSeek);
        return val;
    }
    
    //skip
    void PtrBuffer::skip(size_t len)
    {
        size_t nRead = length_ - pos_;
        nRead = std::min(nRead, len);
        
        pos_ += nRead;
    }
    
    void PtrBuffer::write(const void* _pBuffer, size_t _nLen, off_t _nPos)
    {
        size_t nWrite = length_ - _nPos;
        nWrite = std::min(nWrite, _nLen);
        memcpy(buffer_ + _nPos, _pBuffer, nWrite);
        
        pos_ += nWrite;
    }
}

