//
//  CommonReadHandleTest.cpp
//  DataHandleTests
//
//  Created by Alkenso on 5/3/17.
//
//

#include <DataHandle/ContainerReadHandle.h>
#include "TestData.h"

TEST(DataReadHandle, GetDataSize)
{
    const int dataLength = 1050;
    const datarw::ByteBuffer someData(dataLength);
    
    datarw::VectorReadHandle reader(someData);
    
    EXPECT_EQ(reader.getDataSize(), dataLength);
}

TEST(DataReadHandle, ReadDataInRange_URaw)
{
    datarw::VectorReadHandle reader(datarw::testing::g_testData);
    const int64_t readDataOffset = 10;
    const uint64_t readDataLength = 5;
    const datarw::Range readDataRange(readDataOffset, readDataLength);
    
    const datarw::ByteBuffer expectedReadData = { 0x12, 0xCD, 0xE2, 0x8A, 0x8C };
    
    datarw::ByteBuffer actualReadData(readDataLength);
    reader.peekData(readDataRange, actualReadData.data());
    
    EXPECT_EQ(actualReadData, expectedReadData);
}

TEST(DataReadHandle, ReadDataInRange_SRaw)
{
    datarw::StringReadHandle reader(datarw::testing::g_testString);
    const int64_t readDataOffset = 10;
    const uint64_t readDataLength = 5;
    const datarw::Range readDataRange(readDataOffset, readDataLength);
    
    const std::string expectedReadData = "LMNOP";
    
    std::string actualReadData(readDataLength, '\0');
    reader.peekData(readDataRange, &actualReadData[0]);
    
    EXPECT_EQ(actualReadData, expectedReadData);
}

TEST(DataReadHandle, ReadDataInRange_ByteBuffer)
{
    datarw::VectorReadHandle reader(datarw::testing::g_testData);
    const int64_t readDataOffset = 10;
    const uint64_t readDataLength = 5;
    const datarw::Range readDataRange(readDataOffset, readDataLength);
    
    const datarw::ByteBuffer expectedReadData = { 0x12, 0xCD, 0xE2, 0x8A, 0x8C };
    
    datarw::ByteBuffer actualReadData;
    reader.peekData(readDataRange, actualReadData);
    
    EXPECT_EQ(actualReadData, expectedReadData);
}

TEST(DataReadHandle, ReadDataInRange_String)
{
    datarw::StringReadHandle reader(datarw::testing::g_testString);
    const int64_t readDataOffset = 10;
    const uint64_t readDataLength = 5;
    const datarw::Range readDataRange(readDataOffset, readDataLength);
    
    const std::string expectedReadData = "LMNOP";
    
    std::string actualReadData;
    reader.peekData(readDataRange, actualReadData);
    
    EXPECT_EQ(actualReadData, expectedReadData);
}

TEST(DataReadHandle, AppendDataInRange_ByteBuffer)
{
    datarw::VectorReadHandle reader(datarw::testing::g_testData);
    const int64_t readDataOffset = 10;
    const uint64_t readDataLength = 5;
    const datarw::Range readDataRange(readDataOffset, readDataLength);
    
    const datarw::ByteBuffer expectedAppendedData = { 0x01, 0x02, 0x03, 0x12, 0xCD, 0xE2, 0x8A, 0x8C };
    
    datarw::ByteBuffer existingData = { 0x01, 0x02, 0x03 };
    reader.peekAppendData(readDataRange, existingData);
    
    EXPECT_EQ(existingData, expectedAppendedData);
}

TEST(DataReadHandle, AppendDataInRange_String)
{
    datarw::StringReadHandle reader(datarw::testing::g_testString);
    const int64_t readDataOffset = 10;
    const uint64_t readDataLength = 5;
    const datarw::Range readDataRange(readDataOffset, readDataLength);
    
    const std::string expectedAppendedData = "abcLMNOP";
    
    std::string existingData = "abc";
    reader.peekAppendData(readDataRange, existingData);
    
    EXPECT_EQ(existingData, expectedAppendedData);
}

TEST(DataReadHandle, ReadDataInRange_Return)
{
    datarw::VectorReadHandle reader(datarw::testing::g_testData);
    const int64_t readDataOffset = 10;
    const uint64_t readDataLength = 5;
    const datarw::Range readDataRange(readDataOffset, readDataLength);
    
    const datarw::ByteBuffer expectedReadData = { 0x12, 0xCD, 0xE2, 0x8A, 0x8C };
    
    EXPECT_EQ(reader.peekData<datarw::ByteBuffer>(readDataRange), expectedReadData);
}

TEST(DataReadHandle, ReadStringInRange_Return)
{
    datarw::StringReadHandle reader(datarw::testing::g_testString);
    const int64_t readDataOffset = 10;
    const uint64_t readDataLength = 5;
    const datarw::Range readDataRange(readDataOffset, readDataLength);
    
    const std::string expectedReadData = "LMNOP";
    
    EXPECT_EQ(reader.peekData<std::string>(readDataRange), expectedReadData);
}

TEST(DataReadHandle, ReadNextData_ByteBuffer)
{
    datarw::VectorReadHandle reader(datarw::testing::g_testData, false);
    
    const uint64_t dataSize0 = 2;
    const uint64_t dataSize1 = 4;
    const uint64_t dataSize2 = 6;
    const uint64_t dataSize3 = 3;
    
    datarw::ByteBuffer readData0;
    datarw::ByteBuffer readData1;
    datarw::ByteBuffer readData2;
    datarw::ByteBuffer readData3;
    
    readData0.resize(dataSize0);
    reader.readData(dataSize0, readData0.data());
    EXPECT_EQ(readData0, datarw::ByteBuffer({0x09, 0x76}));
    
    reader.readData(dataSize1, readData1);
    EXPECT_EQ(readData1, datarw::ByteBuffer({0xC6, 0xEE, 0xF6, 0xB3}));
    
    readData2 = { 0x01, 0x02, 0x03 };
    reader.appendData(dataSize2, readData2);
    EXPECT_EQ(readData2, datarw::ByteBuffer({0x01, 0x02, 0x03, 0xF3, 0x8F, 0x79, 0xE6, 0x12, 0xCD}));
    
    readData3 = reader.readData<datarw::ByteBuffer>(dataSize3);
    EXPECT_EQ(readData3, datarw::ByteBuffer({0xE2, 0x8A, 0x8C}));
}

TEST(DataReadHandle, ReadNextData_String)
{
    datarw::StringReadHandle reader(datarw::testing::g_testString, false);
    
    const uint64_t dataSize0 = 2;
    const uint64_t dataSize1 = 4;
    const uint64_t dataSize2 = 6;
    const uint64_t dataSize3 = 3;
    
    std::string readData0;
    std::string readData1;
    std::string readData2;
    std::string readData3;
    
    readData0.resize(dataSize0);
    reader.readData(dataSize0, &readData0[0]);
    EXPECT_EQ(readData0, "AB");
    
    reader.readData(dataSize1, readData1);
    EXPECT_EQ(readData1, "CDEF");
    
    readData2 = "abc";
    reader.appendData(dataSize2, readData2);
    EXPECT_EQ(readData2, "abcGHJKLM");
    
    readData3 = reader.readData<std::string>(dataSize3);
    EXPECT_EQ(readData3, "NOP");
}

TEST(DataReadHandle, ReadData_ReadBytesToString)
{
    datarw::VectorReadHandle reader(datarw::testing::g_textualTestData, false);
    
    const uint64_t firstDataSize = 4;
    const uint64_t secondDataSize = 7;
    
    std::string firstReadData;
    std::string secondReadData;
    
    reader.readData(firstDataSize, firstReadData);
    reader.readData(secondDataSize, secondReadData);
    
    const std::string firstExpectedData = "ABCD";
    const std::string secondExpectedData = "EFGHJKL";
    
    EXPECT_EQ(firstExpectedData, firstReadData);
    EXPECT_EQ(secondExpectedData, secondReadData);
}

TEST(DataReadHandle, ReadAllData_URaw)
{
    datarw::VectorReadHandle reader(datarw::testing::g_testData);
    
    datarw::ByteBuffer actualReadData(datarw::testing::g_testData.size());
    reader.readAllData(actualReadData.data());
    
    EXPECT_EQ(actualReadData, datarw::testing::g_testData);
}

TEST(DataReadHandle, ReadAllData_SRaw)
{
    datarw::StringReadHandle reader(datarw::testing::g_testString);
    
    std::string actualReadData(datarw::testing::g_testString.size(), '\0');
    reader.readAllData(&actualReadData[0]);
    
    EXPECT_EQ(actualReadData, datarw::testing::g_testString);
}

TEST(DataReadHandle, ReadAllData_ByteBuffer)
{
    datarw::VectorReadHandle reader(datarw::testing::g_testData);
    
    datarw::ByteBuffer actualReadData;
    reader.readAllData(actualReadData);
    
    EXPECT_EQ(actualReadData, datarw::testing::g_testData);
}

TEST(DataReadHandle, ReadAllData_String)
{
    datarw::StringReadHandle reader(datarw::testing::g_testString);
    
    std::string actualReadData;
    reader.readAllData(actualReadData);
    
    EXPECT_EQ(actualReadData, datarw::testing::g_testString);
}

TEST(DataReadHandle, AppendAllData_ByteBuffer)
{
    datarw::VectorReadHandle reader(datarw::testing::g_testData);
    
    datarw::ByteBuffer actualReadData = { 0x01, 0x02, 0x03 };
    datarw::ByteBuffer expectedData = actualReadData;
    std::copy(datarw::testing::g_testData.begin(), datarw::testing::g_testData.end(), std::back_inserter(expectedData));
    
    reader.appendAllData(actualReadData);
    EXPECT_EQ(actualReadData, expectedData);
}

TEST(DataReadHandle, AppendAllData_String)
{
    datarw::StringReadHandle reader(datarw::testing::g_testString);
    
    std::string actualReadData = "qweqwe";
    std::string expectedData = actualReadData + datarw::testing::g_testString;
    
    reader.appendAllData(actualReadData);
    EXPECT_EQ(actualReadData, expectedData);
}

TEST(DataReadHandle, ReadAllData_Return)
{
    datarw::VectorReadHandle reader(datarw::testing::g_testData);
    EXPECT_EQ(reader.readAllData<datarw::ByteBuffer>(), datarw::testing::g_testData);
}

TEST(DataReadHandle, ReadAllString_Return)
{
    datarw::StringReadHandle reader(datarw::testing::g_testString);
    EXPECT_EQ(reader.readAllData<std::string>(), datarw::testing::g_testString);
}

TEST(DataReadHandle, SeekTell)
{
    datarw::VectorReadHandle reader(datarw::testing::g_testData);
    ASSERT_EQ(reader.getRemainingSize(), 32);
    
    reader.skipBytes(3);
    EXPECT_EQ(reader.getRemainingSize(), 29);
    
    reader.skipBytes(5);
    EXPECT_EQ(reader.getRemainingSize(), 24);
    
    reader.skipBytes(2);
    EXPECT_EQ(reader.getRemainingSize(), 22);
}

TEST(DataReadHandle, SeekTell_ReadInRange)
{
    datarw::VectorReadHandle reader(datarw::testing::g_testData);
    const datarw::Range readDataRange(10, 5);
    const datarw::ByteBuffer expectedReadData = { 0x12, 0xCD, 0xE2, 0x8A, 0x8C };
    
    datarw::ByteBuffer actualReadData = reader.peekData<datarw::ByteBuffer>(readDataRange);
    ASSERT_EQ(actualReadData, expectedReadData);
    
    EXPECT_EQ(reader.getRemainingSize(), 32);
}

TEST(DataReadHandle, SeekTell_ReadNext)
{
    datarw::VectorReadHandle reader(datarw::testing::g_testData);
    const size_t readDataSize = 5;
    const datarw::ByteBuffer expectedReadData = { 0x09, 0x76, 0xC6, 0xEE, 0xF6 };
    
    datarw::ByteBuffer actualReadData = reader.readData<datarw::ByteBuffer>(readDataSize);
    ASSERT_EQ(actualReadData, expectedReadData);
    
    EXPECT_EQ(reader.getRemainingSize(), 27);
}

TEST(DataReadHandle, EnshureRemainingSize)
{
    const size_t bufferSize = 16;
    datarw::ByteBuffer buffer16Bytes(bufferSize, 0x00);
    
    datarw::VectorReadHandle reader(buffer16Bytes);
    reader.readData<datarw::ByteBuffer>(4);
    reader.readData<datarw::ByteBuffer>(8);
    
    EXPECT_TRUE(reader.enshureRemainingSize(4));
    EXPECT_TRUE(reader.enshureRemainingSize(2));
    
    EXPECT_FALSE(reader.enshureRemainingSize(6));
}

TEST(DataReadHandle, PeekValue_Uint16)
{
    const int64_t valueOffset = 2;
    const datarw::ByteBuffer dataToRead = { 0x00, 0x00, 0x8F, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    
    datarw::VectorReadHandle reader(dataToRead);
    
    const uint16_t expectedValue = 655;
    EXPECT_EQ(reader.peekValueLE<uint16_t>(valueOffset), expectedValue);
}

TEST(DataReadHandle, PeekValue_Uint32)
{
    const int64_t valueOffset = 2;
    const datarw::ByteBuffer dataToRead = { 0x00, 0x00, 0x09, 0xD2, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    
    datarw::VectorReadHandle reader(dataToRead);
    
    const uint32_t expectedValue = 1888777;
    EXPECT_EQ(reader.peekValueLE<uint32_t>(valueOffset), expectedValue);
}

TEST(DataReadHandle, PeekValue_Uint64)
{
    const int64_t valueOffset = 2;
    const datarw::ByteBuffer dataToRead = { 0x00, 0x00, 0x68, 0x84, 0xAC, 0x13, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    
    datarw::VectorReadHandle reader(dataToRead);
    
    const uint64_t expectedValue = 111999222888;
    EXPECT_EQ(reader.peekValueLE<uint64_t>(valueOffset), expectedValue);
}

TEST(DataReadHandle, PeekValue_InOffset)
{
    datarw::VectorReadHandle readerLE(datarw::testing::g_valuesLE);
    datarw::VectorReadHandle readerBE(datarw::testing::g_valuesBE);
    
    ASSERT_EQ(readerLE.peekValueLE<uint32_t>(0), datarw::testing::g_value0);
    ASSERT_EQ(readerLE.peekValueLE<uint64_t>(4), datarw::testing::g_value1);
    EXPECT_EQ(readerLE.getRemainingSize(), 12);
    
    ASSERT_EQ(readerBE.peekValueBE<uint32_t>(0), datarw::testing::g_value0);
    ASSERT_EQ(readerBE.peekValueBE<uint64_t>(4), datarw::testing::g_value1);
    EXPECT_EQ(readerBE.getRemainingSize(), 12);
}

TEST(DataReadHandle, PeekValueFromCurrent)
{
    datarw::VectorReadHandle readerLE(datarw::testing::g_valuesLE);
    datarw::VectorReadHandle readerBE(datarw::testing::g_valuesBE);
    const uint64_t seekOffset = 2;
    readerLE.skipBytes(seekOffset);
    readerBE.skipBytes(seekOffset);
    
    const int64_t valueOffset = 2;
    
    ASSERT_EQ(readerLE.peekValueFromCurrentLE<uint64_t>(valueOffset), datarw::testing::g_value1);
    EXPECT_EQ(readerLE.getRemainingSize(), 10);
    
    ASSERT_EQ(readerBE.peekValueFromCurrentBE<uint64_t>(valueOffset), datarw::testing::g_value1);
    EXPECT_EQ(readerBE.getRemainingSize(), 10);
}

TEST(DataReadHandle, ReadNextValue)
{
    datarw::VectorReadHandle readerLE(datarw::testing::g_valuesLE);
    datarw::VectorReadHandle readerBE(datarw::testing::g_valuesBE);
    
    EXPECT_EQ(readerLE.readValueLE<uint32_t>(), datarw::testing::g_value0);
    EXPECT_EQ(readerLE.readValueLE<uint64_t>(), datarw::testing::g_value1);
    EXPECT_EQ(readerLE.getRemainingSize(), 0);
    
    EXPECT_EQ(readerBE.readValueBE<uint32_t>(), datarw::testing::g_value0);
    EXPECT_EQ(readerBE.readValueBE<uint64_t>(), datarw::testing::g_value1);
    EXPECT_EQ(readerBE.getRemainingSize(), 0);
}

TEST(DataReadHandle, PeekDataOutOfRange)
{
    datarw::VectorReadHandle valueReader(datarw::testing::g_valuesLE);  // size = 12
    datarw::VectorReadHandle bufferReader(datarw::testing::g_testData); // size = 32
    
    EXPECT_THROW(valueReader.peekValueLE<uint64_t>(10), std::out_of_range);
    
    datarw::ByteBuffer buf;
    EXPECT_THROW(bufferReader.peekData(datarw::Range(16, 20), buf), std::out_of_range);
}

TEST(DataReadHandle, ReadNextDataOutOfRange)
{
    datarw::VectorReadHandle bufferReader(datarw::testing::g_testData); // size = 32
    
    EXPECT_NO_THROW(bufferReader.readData<datarw::ByteBuffer>(15));
    EXPECT_NO_THROW(bufferReader.readData<datarw::ByteBuffer>(15));
    EXPECT_THROW(bufferReader.readData<datarw::ByteBuffer>(15), std::out_of_range);
}

TEST(DataReadHandle, NullBuffer)
{
    datarw::VectorReadHandle bufferReader(datarw::testing::g_testData);
    
    unsigned char* ptr = nullptr;
    EXPECT_THROW(bufferReader.peekData(datarw::Range(0, 10), ptr), std::invalid_argument);
}

TEST(DataReadHandle, ZeroSize)
{
    datarw::VectorReadHandle bufferReader(datarw::testing::g_testData);
    
    unsigned char* ptr = nullptr;
    EXPECT_NO_THROW(bufferReader.peekData(datarw::Range(0, 0), ptr));
}
