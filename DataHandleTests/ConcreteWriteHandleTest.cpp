//
//  ConcreteWriteHandleTest.cpp
//  DataHandleTests
//
//  Created by Alkenso on 5/6/17.
//
//

#include <DataHandle/ContainerWriteHandle.h>
#include <DataHandle/StreamWriteHandle.h>

#include "TestData.h"

TEST(ContainerWriteHandle, DefaultCtor)
{
    datarw::VectorWriteHandle writer;
    EXPECT_EQ(writer.getContainer().size(), 0);
}

TEST(ContainerWriteHandle, CtorRefNoCopy)
{
    datarw::ByteBuffer testData = { 0xf0, 0xf1, 0xf2, 0xf3 };
    datarw::VectorWriteHandle writer(testData, false);
    
    ASSERT_EQ(writer.getContainer().size(), testData.size());
    
    writer.writeData(datarw::ByteBuffer({ 0x00, 0x01, 0x02, 0x03 }));
    EXPECT_EQ(writer.getContainer(), datarw::ByteBuffer({ 0xf0, 0xf1, 0xf2, 0xf3, 0x00, 0x01, 0x02, 0x03 }));
    EXPECT_EQ(testData, datarw::ByteBuffer({ 0xf0, 0xf1, 0xf2, 0xf3, 0x00, 0x01, 0x02, 0x03 }));
    
    testData.clear();
    
    EXPECT_EQ(testData.size(), 0);
    EXPECT_EQ(writer.getContainer().size(), 0);
}

TEST(ContainerWriteHandle, CtorRefCopy)
{
    datarw::ByteBuffer testData = { 0xf0, 0xf1, 0xf2, 0xf3 };
    datarw::VectorWriteHandle writer(testData, true);
    
    ASSERT_EQ(writer.getContainer().size(), testData.size());
    
    writer.writeData(datarw::ByteBuffer({ 0x00, 0x01, 0x02, 0x03 }));
    EXPECT_EQ(writer.getContainer(), datarw::ByteBuffer({ 0xf0, 0xf1, 0xf2, 0xf3, 0x00, 0x01, 0x02, 0x03 }));
    EXPECT_EQ(testData, datarw::ByteBuffer({ 0xf0, 0xf1, 0xf2, 0xf3 }));
    
    testData.clear();
    
    EXPECT_EQ(testData.size(), 0);
    EXPECT_EQ(writer.getContainer().size(), 8);
}

TEST(ContainerWriteHandle, CtorConstRef)
{
    const datarw::ByteBuffer testData = { 0xf0, 0xf1, 0xf2, 0xf3 };
    datarw::VectorWriteHandle writer(testData);
    
    ASSERT_EQ(writer.getContainer().size(), testData.size());
    
    writer.writeData(datarw::ByteBuffer({ 0x00, 0x01, 0x02, 0x03 }));
    EXPECT_EQ(writer.getContainer(), datarw::ByteBuffer({ 0xf0, 0xf1, 0xf2, 0xf3, 0x00, 0x01, 0x02, 0x03 }));
    EXPECT_EQ(testData, datarw::ByteBuffer({ 0xf0, 0xf1, 0xf2, 0xf3 }));
}

TEST(ContainerWriteHandle, CtorMove)
{
    datarw::VectorWriteHandle writer({ 0xf0, 0xf1, 0xf2, 0xf3 });
    
    writer.writeData(datarw::ByteBuffer({ 0x00, 0x01, 0x02, 0x03 }));
    EXPECT_EQ(writer.getContainer(), datarw::ByteBuffer({ 0xf0, 0xf1, 0xf2, 0xf3, 0x00, 0x01, 0x02, 0x03 }));
}

TEST(StreamWriteHandle, GetDataSize)
{
    std::stringstream ssData("qwerty");
    datarw::StreamWriteHandle writerData(ssData);
    
    EXPECT_EQ(writerData.getDataSize(), 6);
}

TEST(StreamWriteHandle, WriteData)
{
    std::stringstream ssString;
    std::stringstream ssData;
    datarw::StreamWriteHandle writerString(ssString);
    datarw::StreamWriteHandle writerData(ssData);
    
    writerString.writeData(datarw::testing::g_textualTestData);
    writerData.writeData(datarw::testing::g_testData);
    
    EXPECT_EQ(ssString.str(), datarw::testing::g_testString);
    const std::string& data = ssData.str();
    EXPECT_EQ(datarw::ByteBuffer(data.begin(), data.end()), datarw::testing::g_testData);
}

TEST(StreamWriteHandle, InsertData)
{
    std::stringstream ssData;
    datarw::StreamWriteHandle writerData(ssData);
    
    writerData.writeData(datarw::testing::g_fourZeroes);
    writerData.insertData(datarw::ByteBuffer({ 0xff, 0xff, 0xff }), 2);
    
    const std::string& data = ssData.str();
    EXPECT_EQ(datarw::ByteBuffer(data.begin(), data.end()), datarw::ByteBuffer({ 0x00, 0x00, 0xff, 0xff, 0xff }));
}

TEST(StreamWriteHandle, DirtyStream)
{
    std::stringstream ss;
    ss << "abcde";
    ASSERT_EQ(ss.tellp(), 5);
    
    datarw::StreamWriteHandle writer(ss, true);
    EXPECT_EQ(writer.getDataSize(), 5);
    writer.writeString("ABCDE");
    EXPECT_EQ(ss.str(), "abcdeABCDE");
}
