//
//  ConcreteReadHandleTest.cpp
//  DataHandleTests
//
//  Created by Alkenso on 5/6/17.
//
//

#include <DataHandle/ContainerReadHandle.h>
#include <DataHandle/RawBytesReadHandle.h>
#include <DataHandle/SubReadHandle.h>
#include <DataHandle/SharedDataHandle.h>
#include <DataHandle/StreamReadHandle.h>
#include <DataHandle/SequentialReadHandle.h>

#include "TestData.h"

TEST(ContainerReadHandle, CreateWithTemporary)
{
    datarw::ByteBuffer dataToRead = datarw::testing::g_testData;
    
    datarw::VectorReadHandle reader({0x09, 0x76, 0xC6, 0xEE, 0xF6});
    
    datarw::ByteBuffer actualReadData;
    reader.readAllData(actualReadData);
    
    EXPECT_EQ(actualReadData, datarw::ByteBuffer({0x09, 0x76, 0xC6, 0xEE, 0xF6}));
}

TEST(ContainerReadHandle, CreateWithBufferCopy)
{
    datarw::ByteBuffer dataToRead = datarw::testing::g_testData;
    
    datarw::VectorReadHandle reader(dataToRead, true);
    memset(dataToRead.data(), 0, dataToRead.size());
    
    datarw::ByteBuffer actualReadData;
    reader.readAllData(actualReadData);
    
    EXPECT_EQ(actualReadData, datarw::testing::g_testData);
    EXPECT_NE(actualReadData, dataToRead);
}

TEST(ContainerReadHandle, CreateWithBufferNoCopy)
{
    datarw::ByteBuffer dataToRead = datarw::testing::g_testData;
    
    datarw::VectorReadHandle reader(dataToRead, false);
    memset(dataToRead.data(), 0, dataToRead.size());
    
    datarw::ByteBuffer actualReadData;
    reader.readAllData(actualReadData);
    
    EXPECT_NE(actualReadData, datarw::testing::g_testData);
    EXPECT_EQ(actualReadData, dataToRead);
}

TEST(RawBytesReadHandle, CreateWithBufferCopy)
{
    datarw::ByteBuffer dataToRead = datarw::testing::g_testData;
    
    datarw::RawBytesReadHandle reader(dataToRead.data(), dataToRead.size(), true);
    memset(dataToRead.data(), 0, dataToRead.size());
    
    datarw::ByteBuffer actualReadData;
    reader.readAllData(actualReadData);
    
    EXPECT_EQ(actualReadData, datarw::testing::g_testData);
    EXPECT_NE(actualReadData, dataToRead);
}

TEST(RawBytesReadHandle, CreateWithBufferNoCopy)
{
    datarw::ByteBuffer dataToRead = datarw::testing::g_testData;
    
    datarw::RawBytesReadHandle reader(dataToRead.data(), dataToRead.size(), false);
    memset(dataToRead.data(), 0, dataToRead.size());
    
    datarw::ByteBuffer actualReadData;
    reader.readAllData(actualReadData);
    
    EXPECT_NE(actualReadData, datarw::testing::g_testData);
    EXPECT_EQ(actualReadData, dataToRead);
}

TEST(SubReadHandle, CtorRangeBased)
{
    datarw::VectorReadHandle reader(datarw::testing::g_testData, false);
    datarw::SubReadHandle subReader(reader, datarw::Range(16, 8));
    
    const uint64_t expectedSubDataSize = 8;
    ASSERT_EQ(subReader.getDataSize(), expectedSubDataSize);
    
    const datarw::Range readDataRange(0, 4);
    datarw::ByteBuffer actualReadData;
    subReader.peekData(readDataRange, actualReadData);
    
    datarw::ByteBuffer expectedData = { 0x4A, 0x79, 0xC7, 0xB7 };
    
    EXPECT_EQ(actualReadData, expectedData);
}

TEST(SubReadHandle, CtorOffsetBased)
{
    datarw::VectorReadHandle reader(datarw::testing::g_testData);
    datarw::SubReadHandle subReader(reader, 16);
    
    const uint64_t expectedSubDataSize = 16;
    ASSERT_EQ(subReader.getDataSize(), expectedSubDataSize);
    
    const datarw::Range readDataRange(0, 4);
    datarw::ByteBuffer actualReadData;
    subReader.peekData(readDataRange, actualReadData);
    
    datarw::ByteBuffer expectedData = { 0x4A, 0x79, 0xC7, 0xB7 };
    
    EXPECT_EQ(actualReadData, expectedData);
}

TEST(SubReadHandle, CtorOffsetBased_ParentNotRelated)
{
    datarw::VectorReadHandle reader(datarw::testing::g_testData);
    reader.skipNextBytes(10);
    datarw::SubReadHandle subReader(reader, 16, false);
    
    const uint64_t expectedSubDataSize = 16;
    ASSERT_EQ(subReader.getDataSize(), expectedSubDataSize);
    
    const datarw::Range readDataRange(0, 4);
    datarw::ByteBuffer actualReadData;
    subReader.peekData(readDataRange, actualReadData);
    
    datarw::ByteBuffer expectedData = { 0x4A, 0x79, 0xC7, 0xB7 };
    
    EXPECT_EQ(actualReadData, expectedData);
}

TEST(SubReadHandle, CtorOffsetBased_ParentRelated)
{
    datarw::VectorReadHandle reader(datarw::testing::g_testData);
    reader.skipNextBytes(8);
    datarw::SubReadHandle subReader(reader, 8, true);
    
    const uint64_t expectedSubDataSize = 16;
    ASSERT_EQ(subReader.getDataSize(), expectedSubDataSize);
    
    const datarw::Range readDataRange(0, 4);
    datarw::ByteBuffer actualReadData;
    subReader.peekData(readDataRange, actualReadData);
    
    datarw::ByteBuffer expectedData = { 0x4A, 0x79, 0xC7, 0xB7 };
    
    EXPECT_EQ(actualReadData, expectedData);
}

TEST(SubReadHandle, InvalidParam)
{
    datarw::VectorReadHandle reader(datarw::testing::g_testData, false); // size == 32
    const datarw::Range rangeOutOfDataBounds(16, 17);
    EXPECT_THROW(datarw::SubReadHandle subReader(reader, rangeOutOfDataBounds), std::out_of_range);
    
    EXPECT_THROW(datarw::SubReadHandle subReader(reader, 33), std::out_of_range);
    
    reader.skipNextBytes(16); // position == 16
    EXPECT_THROW(datarw::SubReadHandle(reader, 20, true), std::out_of_range);
}

TEST(SharedReadHandle, CommonTest)
{
    std::shared_ptr<datarw::DataReadHandle> sharedSubReader = nullptr;
    {
        std::shared_ptr<datarw::DataReadHandle> baseReader(new datarw::VectorReadHandle(datarw::testing::g_testData, true));
        sharedSubReader.reset(new datarw::SharedReadHandle<datarw::SubReadHandle>(baseReader, datarw::Range(16, 8)));

        ASSERT_EQ(baseReader.use_count(), 2); // means that SharedReader owns it's parent - baseReader
    }

    const uint64_t expectedSubDataSize = 8;
    ASSERT_EQ(sharedSubReader->getDataSize(), expectedSubDataSize);

    const datarw::Range readDataRange(0, 4);
    datarw::ByteBuffer actualReadData;
    sharedSubReader->peekData(readDataRange, actualReadData);

    datarw::ByteBuffer expectedData = { 0x4A, 0x79, 0xC7, 0xB7 };

    EXPECT_EQ(actualReadData, expectedData);
}

TEST(StreamReadHandle, CommonTest)
{
    std::stringstream ssString(datarw::testing::g_testString);
    std::stringstream ssData(std::string(datarw::testing::g_testData.begin(), datarw::testing::g_testData.end()));
    datarw::StreamReadHandle readerString(ssString);
    datarw::StreamReadHandle readerData(ssData);
    
    std::string str;
    readerString.readAllData(str);
    
    datarw::ByteBuffer data;
    readerData.readAllData(data);
    
    EXPECT_EQ(str, datarw::testing::g_testString);
    EXPECT_EQ(data, datarw::testing::g_testData);
}

TEST(StreamReadHandle, DirtyStream)
{
    std::stringstream ssFinished(datarw::testing::g_testString);
    std::string str;
    ssFinished >> str;
    ASSERT_EQ(str, datarw::testing::g_testString);
    datarw::StreamReadHandle readerSsFinished(ssFinished, true);
    ASSERT_EQ(readerSsFinished.getRemainingSize(), datarw::testing::g_testString.size());
    ASSERT_EQ(readerSsFinished.getDataSize(), datarw::testing::g_testString.size());
    EXPECT_EQ(readerSsFinished.readNextData<std::string>(5), "ABCDE");
    
    
    std::stringstream ssPartialRead(datarw::testing::g_testString);
    ssPartialRead.seekg(10);
    datarw::StreamReadHandle readerSsPartialRead(ssPartialRead, true);
    ASSERT_EQ(readerSsPartialRead.getRemainingSize(), datarw::testing::g_testString.size());
    ASSERT_EQ(readerSsPartialRead.getDataSize(), datarw::testing::g_testString.size());
    EXPECT_EQ(readerSsPartialRead.readNextData<std::string>(5), "ABCDE");
}

TEST(StreamReadHandle, SeekTell)
{
    std::stringstream ssData(std::string(datarw::testing::g_testData.begin(), datarw::testing::g_testData.end()));
    datarw::StreamReadHandle reader(ssData);
    ASSERT_EQ(reader.getRemainingSize(), 32);
    
    reader.skipNextBytes(3);
    EXPECT_EQ(reader.getRemainingSize(), 29);
    
    reader.skipNextBytes(5);
    EXPECT_EQ(reader.getRemainingSize(), 24);
    
    reader.skipNextBytes(2);
    EXPECT_EQ(reader.getRemainingSize(), 22);
}

TEST(StreamReadHandle, Mixed_Seek_Peek_ReadNext)
{
    std::stringstream ssData(std::string(datarw::testing::g_testData.begin(), datarw::testing::g_testData.end()));
    datarw::StreamReadHandle reader(ssData);
    ASSERT_EQ(reader.getRemainingSize(), 32);
    
    EXPECT_EQ(reader.readNextData<datarw::ByteBuffer>(3), datarw::ByteBuffer({ 0x09, 0x76, 0xC6 }));
    EXPECT_EQ(reader.getRemainingSize(), 29);
    
    reader.skipNextBytes(16);
    EXPECT_EQ(reader.getRemainingSize(), 13);
    EXPECT_EQ(reader.readNextData<datarw::ByteBuffer>(3), datarw::ByteBuffer({ 0xB7, 0x20, 0x13 }));
    EXPECT_EQ(reader.getRemainingSize(), 10);
    
    EXPECT_EQ(reader.peekData<datarw::ByteBuffer>(datarw::Range(0, 3)), datarw::ByteBuffer({ 0x09, 0x76, 0xC6 }));
    EXPECT_EQ(reader.getRemainingSize(), 10);
    
    EXPECT_EQ(reader.readNextData<datarw::ByteBuffer>(3), datarw::ByteBuffer({ 0x42, 0xF3, 0x98 }));
    EXPECT_EQ(reader.getRemainingSize(), 7);
}

TEST(SequentialReadHandle, OneEntry)
{
    datarw::VectorReadHandle reader(datarw::testing::g_testData);
    datarw::SequentialReadHandle seqReader({reader});
    
    ASSERT_EQ(seqReader.getDataSize(), datarw::testing::g_testData.size());
    
    EXPECT_EQ(seqReader.readNextData<datarw::ByteBuffer>(4), datarw::ByteBuffer({ 0x09, 0x76, 0xC6, 0xEE }));
    EXPECT_EQ(seqReader.peekData<datarw::ByteBuffer>(datarw::Range(2, 3)), datarw::ByteBuffer({ 0xC6, 0xEE, 0xF6 }));
    EXPECT_EQ(seqReader.readNextData<datarw::ByteBuffer>(6), datarw::ByteBuffer({ 0xF6, 0xB3, 0xF3, 0x8F, 0x79, 0xE6 }));
}

TEST(SequentialReadHandle, TwoOverlapping)
{
    datarw::VectorReadHandle reader1({ 0x00, 0x01, 0x02, 0x03 });
    datarw::VectorReadHandle reader2({ 0x04, 0x05, 0x06, 0x07 });
    
    datarw::SequentialReadHandle seqReader({reader1, reader2});
    
    ASSERT_EQ(seqReader.getDataSize(), 8);
    
    EXPECT_EQ(seqReader.readNextData<datarw::ByteBuffer>(2), datarw::ByteBuffer({ 0x00, 0x01 }));
    EXPECT_EQ(seqReader.readNextData<datarw::ByteBuffer>(4), datarw::ByteBuffer({ 0x02, 0x03, 0x04, 0x05 }));
    EXPECT_EQ(seqReader.peekData<datarw::ByteBuffer>(datarw::Range(2, 3)), datarw::ByteBuffer({ 0x02, 0x03, 0x04 }));
    EXPECT_EQ(seqReader.readNextData<datarw::ByteBuffer>(2), datarw::ByteBuffer({ 0x06, 0x07 }));
}

TEST(SequentialReadHandle, MultipleEntries)
{
    unsigned char data1[] = { 0x00, 0x01, 0x02, 0x03 };
    datarw::RawBytesReadHandle reader1(data1, sizeof(data1));
    
    datarw::VectorReadHandle reader2({ 0x04, 0x05, 0x06, 0x07 });
    
    const datarw::ByteBuffer data3 = { 0x08, 0x09, 0x0A, 0x0B };
    std::stringstream ss(std::string(data3.begin(), data3.end()));
    datarw::StreamReadHandle reader3(ss);
    
    datarw::SequentialReadHandle seqReader({ reader1, reader2, reader3 });
    ASSERT_EQ(seqReader.getDataSize(), 12);
    
    EXPECT_EQ(seqReader.readNextData<datarw::ByteBuffer>(2), datarw::ByteBuffer({ 0x00, 0x01 }));
    EXPECT_EQ(seqReader.readNextData<datarw::ByteBuffer>(4), datarw::ByteBuffer({ 0x02, 0x03, 0x04, 0x05 }));
    
    EXPECT_EQ(seqReader.peekData<datarw::ByteBuffer>(datarw::Range(2, 3)), datarw::ByteBuffer({ 0x02, 0x03, 0x04 }));
    EXPECT_EQ(seqReader.readNextData<datarw::ByteBuffer>(4), datarw::ByteBuffer({ 0x06, 0x07, 0x08, 0x09 }));
    
    EXPECT_EQ(seqReader.peekData<datarw::ByteBuffer>(datarw::Range(3, 6)), datarw::ByteBuffer({ 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 }));
    
    EXPECT_EQ(seqReader.readAllData<datarw::ByteBuffer>(), datarw::ByteBuffer({ 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B }));
}

TEST(SequentialReadHandle, OnBounds)
{
    datarw::VectorReadHandle reader1({ 0x00, 0x01, 0x02, 0x03 });
    datarw::VectorReadHandle reader2({ 0x04, 0x05, 0x06, 0x07 });
    datarw::VectorReadHandle reader3({ 0x08, 0x09, 0x0A, 0x0B });
    
    datarw::SequentialReadHandle seqReader({reader1, reader2, reader3});
    
    ASSERT_EQ(seqReader.getDataSize(), 12);
    
    EXPECT_EQ(seqReader.peekData<datarw::ByteBuffer>(datarw::Range(0, 6)), datarw::ByteBuffer({ 0x00, 0x01, 0x02, 0x03, 0x04, 0x05 }));
    EXPECT_EQ(seqReader.peekData<datarw::ByteBuffer>(datarw::Range(4, 5)), datarw::ByteBuffer({ 0x04, 0x05, 0x06, 0x07, 0x08 }));
    EXPECT_EQ(seqReader.peekData<datarw::ByteBuffer>(datarw::Range(8, 3)), datarw::ByteBuffer({ 0x08, 0x09, 0x0A }));
    
    EXPECT_EQ(seqReader.peekData<datarw::ByteBuffer>(datarw::Range(3, 5)), datarw::ByteBuffer({ 0x03, 0x04, 0x05, 0x06, 0x07 }));
    EXPECT_EQ(seqReader.peekData<datarw::ByteBuffer>(datarw::Range(5, 7)), datarw::ByteBuffer({ 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B }));
    EXPECT_EQ(seqReader.peekData<datarw::ByteBuffer>(datarw::Range(3, 9)), datarw::ByteBuffer({ 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B }));
}
