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



#import <XCTest/XCTest.h>
#import "MP4Parser.hpp"
#import "FLVParser.hpp"

namespace VP {
    class FLVTest
    {
    public:
        FLVTest(){};
        
        void testReadBit()
        {
            char* buffer = new char[1];
            buffer[0] = 0b01100111;        // 0x67
            std::shared_ptr<BitBuffer> bits = std::make_shared<BitBuffer>(buffer,1);
            int bit1 = bits->readBit(1);    //0
            int bit4 = bits->readBit(4);    //12
            int bit3 = bits->readBit(3);    //7
            
            std::cout<<bit1<<"\t"<<bit4<<"\t"<<bit3<<std::endl;
        }
        
        void testReadByte()
        {
            char* buffer = new char[7];
            buffer[0] = 0x67;        // 0x67
            
            buffer[1] = 0xc0;
            buffer[2] = 0x15;
            
            buffer[3] = 0x02;
            buffer[4] = 0x05;
            buffer[5] = 0xcc;
            buffer[6] = 0x11;
            
            std::shared_ptr<BitBuffer> bits = std::make_shared<BitBuffer>(buffer,sizeof(buffer)/sizeof(char));
            int byte1 = bits->readBit(8);    //103
            int byte2 = bits->readBit(16);    //49173
            int byte4 = bits->readBit(32);    //33934353
            
            std::cout<<byte1<<"\t"<<byte2<<"\t"<<byte4<<std::endl;
        }
        
        void testGolomb()
        {
            {
                char* buffer = new char[1];
                buffer[0] = 0b00010010;    // codesum=8 (the last 0 is for test)
                std::shared_ptr<BitBuffer> bits = std::make_shared<BitBuffer>(buffer,1);
                int value = Golomb::read_ue(bits);
                
                std::cout<<value<<std::endl;
            }
            
            
            {
                char* buffer = new char[1];
                buffer[0] = 0b00111000;    // codesum=6 (the last three's 0 is for test)
                std::shared_ptr<BitBuffer> bits = std::make_shared<BitBuffer>(buffer,1);
                int value = Golomb::read_ue(bits);
                
                std::cout<<value<<std::endl;
            }
            
            {
                char* buffer = new char[1];
                buffer[0] = 0b00010010;    // codesum=-4 (the last 0 is for test)
                std::shared_ptr<BitBuffer> bits = std::make_shared<BitBuffer>(buffer,1);
                int value = Golomb::read_se(bits);
                
                std::cout<<value<<std::endl;
            }
        }
    };
};



@interface VideoParsersTests : XCTestCase

@end

@implementation VideoParsersTests

- (void)testMP4Parser {
    NSBundle *bundle = [NSBundle bundleForClass:[VideoParsersTests class]];
    NSString *path = [bundle pathForResource:@"Horizontal" ofType:@"mp4"];
    std::string string = [path cStringUsingEncoding:NSUTF8StringEncoding];
    
    std::shared_ptr<VP::MP4Parser> mp4 = std::make_shared<VP::MP4Parser>(string);
    mp4->analyze();
}

- (void)testFlvParser {
    NSBundle *bundle = [NSBundle bundleForClass:[VideoParsersTests class]];
    NSString *path = [bundle pathForResource:@"2" ofType:@"flv"];
    std::string string = [path cStringUsingEncoding:NSUTF8StringEncoding];
    
    std::shared_ptr<VP::FLVParser> flv = std::make_shared<VP::FLVParser>(string);
    flv->parse();
}

- (void)testFlvParserParts {
    VP::FLVTest().testReadBit();
    VP::FLVTest().testReadByte();
    VP::FLVTest().testGolomb();
}

@end






