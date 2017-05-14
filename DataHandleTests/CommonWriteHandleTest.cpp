//
//  CommonWriteHandleTest.cpp
//  DataHandleTests
//
//  Created by Alkenso on 5/5/17.
//
//

#include <DataHandle/ContainerWriteHandle.h>

#include "TestData.h"

TEST(DataWriteHandle, GetDataSize)
{
    datarw::ByteBuffer data = datarw::testing::g_testData;
    datarw::VectorWriteHandle writer(data);
    EXPECT_EQ(writer.getDataSize(), datarw::testing::g_testData.size());
}

TEST(DataWriteHandle, InsertData_URaw)
{
    datarw::ByteBuffer data = datarw::testing::g_fourZeroes;
    datarw::VectorWriteHandle writer(data);
    
    const uint64_t dataSize = 4;
    unsigned char writeData [dataSize] = { 0x01, 0x02, 0x03, 0x04 };
    const int64_t writeOffset = 2;
    
    writer.insertData(writeData, dataSize, writeOffset);
    
    EXPECT_EQ(writer.getContainer(), datarw::ByteBuffer({ 0x00, 0x00, 0x01, 0x02, 0x03, 0x04 }));
}

TEST(DataWriteHandle, InsertData_SRaw)
{
    datarw::ByteBuffer data = datarw::testing::g_fourZeroes;
    datarw::VectorWriteHandle writer(data);
    
    char writeData[] = "qwe";
    const int64_t writeOffset = 2;
    
    writer.insertData(writeData, strlen(writeData), writeOffset);
    
    EXPECT_EQ(writer.getContainer(), datarw::ByteBuffer({ 0x00, 0x00, 0x71, 0x77, 0x65 }));
}

TEST(DataWriteHandle, InsertData_ByteBuffer)
{
    datarw::ByteBuffer data = datarw::testing::g_fourZeroes;
    datarw::VectorWriteHandle writer(data);
    
    const datarw::ByteBuffer writeData = { 0x01, 0x02, 0x03, 0x04 };
    const int64_t writeOffset = 2;
    
    writer.insertData(writeData, writeOffset);
    
    EXPECT_EQ(writer.getContainer(), datarw::ByteBuffer({ 0x00, 0x00, 0x01, 0x02, 0x03, 0x04 }));
}

TEST(DataWriteHandle, InsertData_String)
{
    datarw::ByteBuffer data = datarw::testing::g_fourZeroes;
    datarw::VectorWriteHandle writer(data);
    
    const std::string writeData = "qwe";
    const int64_t writeOffset = 2;
    
    writer.insertData(writeData, writeOffset);
    
    EXPECT_EQ(writer.getContainer(), datarw::ByteBuffer({ 0x00, 0x00, 0x71, 0x77, 0x65 }));
}

TEST(DataWriteHandle, WriteData_URaw)
{
    datarw::ByteBuffer data = datarw::testing::g_fourZeroes;
    datarw::VectorWriteHandle writer(data);
    
    const uint64_t dataSize = 4;
    unsigned char writeData [dataSize] = { 0x01, 0x02, 0x03, 0x04 };
    
    writer.writeData(writeData, dataSize);
    
    EXPECT_EQ(writer.getContainer(), datarw::ByteBuffer({ 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04 }));
}

TEST(DataWriteHandle, WriteData_SRaw)
{
    datarw::ByteBuffer data = datarw::testing::g_fourZeroes;
    datarw::VectorWriteHandle writer(data);
    
    char writeData[] = "qwe";
    writer.writeData(writeData, strlen(writeData));
    
    EXPECT_EQ(writer.getContainer(), datarw::ByteBuffer({ 0x00, 0x00, 0x00, 0x00, 0x71, 0x77, 0x65 }));
}

TEST(DataWriteHandle, WriteData_ByteBuffer)
{
    datarw::ByteBuffer data = datarw::testing::g_fourZeroes;
    datarw::VectorWriteHandle writer(data);
    
    const datarw::ByteBuffer writeData = { 0x01, 0x02, 0x03, 0x04 };
    
    writer.writeData(writeData);
    
    EXPECT_EQ(writer.getContainer(), datarw::ByteBuffer({ 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04 }));
}

TEST(DataWriteHandle, WriteData_String)
{
    datarw::ByteBuffer data = datarw::testing::g_fourZeroes;
    datarw::VectorWriteHandle writer(data);
    
    const std::string writeData = "qwe";
    
    writer.writeData(writeData);
    
    EXPECT_EQ(writer.getContainer(), datarw::ByteBuffer({ 0x00, 0x00, 0x00, 0x00, 0x71, 0x77, 0x65 }));
}

TEST(DataWriteHandle, InsertValue)
{
    datarw::VectorWriteHandle writerLE(datarw::testing::g_fourZeroes);
    datarw::VectorWriteHandle writerBE(datarw::testing::g_fourZeroes);
    
    const size_t offset = 2;
    writerLE.insertValue(datarw::testing::g_value0, offset);
    writerBE.insertValueBE(datarw::testing::g_value0, offset);
    
    EXPECT_EQ(writerLE.getContainer(), datarw::ByteBuffer({ 0x00, 0x00, 0x00, 0x00, 0xff, 0xff }));
    EXPECT_EQ(writerBE.getContainer(), datarw::ByteBuffer({ 0x00, 0x00, 0xff, 0xff, 0x00, 0x00 }));
}

TEST(DataWriteHandle, WriteValue)
{
    datarw::VectorWriteHandle writerLE;
    datarw::VectorWriteHandle writerBE;
    
    writerLE.writeValue(datarw::testing::g_value0);
    writerLE.writeValue(datarw::testing::g_value1);
    writerBE.writeValueBE(datarw::testing::g_value0);
    writerBE.writeValueBE(datarw::testing::g_value1);
    
    EXPECT_EQ(writerLE.getContainer(), datarw::testing::g_valuesLE);
    EXPECT_EQ(writerBE.getContainer(), datarw::testing::g_valuesBE);
}

TEST(DataWriteHandle, WriteString)
{
    datarw::ByteBuffer data = datarw::testing::g_fourZeroes;
    datarw::VectorWriteHandle writer(data);
    
    std::string str = "Abc";
    writer.writeString(str, false);
    
    EXPECT_EQ(writer.getContainer(), datarw::ByteBuffer({ 0x00, 0x00, 0x00, 0x00, 'A', 'b', 'c' }));
}

TEST(DataWriteHandle, WriteString_Terminated)
{
    datarw::ByteBuffer data = datarw::testing::g_fourZeroes;
    datarw::VectorWriteHandle writer(data);
    
    std::string str = "Abc";
    writer.writeString(str, true);
    
    EXPECT_EQ(writer.getContainer(), datarw::ByteBuffer({ 0x00, 0x00, 0x00, 0x00, 'A', 'b', 'c', 0x00 }));
}

TEST(DataWriteHandle, WriteCString)
{
    datarw::ByteBuffer data = datarw::testing::g_fourZeroes;
    datarw::VectorWriteHandle writer(data);

    char str[] = "Abc";
    writer.writeString(str, false);

    EXPECT_EQ(writer.getContainer(), datarw::ByteBuffer({ 0x00, 0x00, 0x00, 0x00, 'A', 'b', 'c' }));
}

TEST(DataWriteHandle, WriteCString_Terminated)
{
    datarw::ByteBuffer data = datarw::testing::g_fourZeroes;
    datarw::VectorWriteHandle writer(data);
    
    char str[] = "Abc";
    writer.writeString(str, true);
    
    EXPECT_EQ(writer.getContainer(), datarw::ByteBuffer({ 0x00, 0x00, 0x00, 0x00, 'A', 'b', 'c', 0x00 }));
}

TEST(DataWriteHandle, InsertString_Terminated)
{
    datarw::ByteBuffer data = datarw::testing::g_fourZeroes;
    datarw::VectorWriteHandle writer(data);
    
    std::string str = "Abc";
    writer.insertString(str, 2, true);
    
    EXPECT_EQ(writer.getContainer(), datarw::ByteBuffer({ 0x00, 0x00, 'A', 'b', 'c', 0x00 }));
}

TEST(DataWriteHandle, InvalidData)
{
    datarw::ByteBuffer data = datarw::testing::g_fourZeroes;
    datarw::VectorWriteHandle writer(data);
    
    const unsigned char* nullData = nullptr;
    EXPECT_NO_THROW(writer.insertData(nullData, 0, 0));
    EXPECT_THROW(writer.insertData(nullData, 100500, 0), std::invalid_argument);
    
    EXPECT_NO_THROW(writer.writeData(nullData, 0));
    EXPECT_THROW(writer.writeData(nullData, 100500), std::invalid_argument);
}
