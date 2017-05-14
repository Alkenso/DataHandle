## DataHandle
DataHandle provides unified processing of completely different data sources under a single interface.
Generally DataHandle consists of two parts: data reading and data writing.

At hte beginning, the library was designed for convenient parsing of data and the arrangement of new data.
With functional growth, DataHandle makes it convenient to work with data of absolutely different nature.

Originally, DataHandle provides the ability to work with the most popular data sources.
The main advantage is the extensibility of the solution: under the common interface, it could provide work with:
 - encrypted data
 - packed / unpacked data
 - data of different formats having a nonlinear structure
 - any other data formats

## Reading and writing data
Reading and writing is allowed to read to and write from:
 - C-style arrays char / signed char / unsigned char / std :: byte (C ++ 17)
 - std :: vector <char / signed char / unsigned char / std :: byte (C ++ 17)>
 - std :: string
 
Reading and writing is restricted to ensure that the data will be read / written from a continuous byte array.


**Base classes**

The base _DataReadHandle_ defines methods that provide:
 - obtaining the full size of the data (in the final form)
 - selective reading of data from the range
 - sequential reading of data
 - selective / sequential reading of LE / BE values

The base _DataWriteHandle_ defines methods that provide:
 - obtaining the full current data size (in the final form)
 - data writing it certain position
 - sequential data writing
 - selective / sequential recording of LE / BE values

## Implementing support of new data formats and types
The main interface files are DataReadHandle and DataWriteHandle.
All child classes responsible for the particular data format or type processing must be inherited from them.

The data source class MUST redefine only 2 methods:
 - obtaining the full size of the data (in the final form)
 - read / write data from Range (position; length) to a specific address

## Example

Let's figured out that there is some message that can be sent and received in some way as serialized sequence of bytes.

```c++
Message is simple structure:
struct Message
{
    uint32_t size;
    char username[16];
    unsigned char key[32];
};

bool ReadMessage(datarw::DataReadHandle& blobReader, Message& m)
{
    m.size = blobReader.readNextValue<uint32_t>();
    if (m.size != blob.size())
    {
        return false;
    }
    
    blobReader.readNextData(16, m.username);
    blobReader.readNextData(32, m.key);
}

void WriteMessage(datarw::DataWriteHandle>& blobWriter, const Message& m)
{
    blobWriter.skipNextBytes(sizeof(uint32_t));
    blobWriter.writeData(m.username, 16);
    blobWriter.writeData(m.key, 32);
    
    blobWriter.insertValue<uint32_t>(blob.size(), 0); // write correct message size
}

int main(void)
{
    ...
    const std::vector<unsigned char> blob = ReceiveMessage(...);
    Message m = {};
    datarw::VectorReadHandle reader(blob);
    if (!ReadMessage(reader, m))
    {
        PrintError("Unable to read message");
        return 1;
    }
    
    const Message response = PrepareResponseMessage(...);
    std::vector<unsigned char> responseBlob;
    datarw::VectorWriteHandle writer(responseBlob);
    WriteMessage(writer, response);
    
    SendMessage(responseBlob);
}
```

**But...there is more...**

Assume that the message is received as compressed, encrypted or compressed + encrypted blob

```c++
class CryptoReader : public datarw::DataReadHandle
{
public:
    CryptoReader(datawr::DataReadHandle& parentReader, ...);
...
};

class ZipReader : public datarw::DataReadHandle
{
public:
    ZipReader(datawr::DataReadHandle& parentReader, ...);
...
};

int main(void)
{
    Message m = {};
    
    // Case 1: encrypted data
    const std::vector<unsigned char> blob = ReceiveEncryptedMessage(...);
    datarw::VectorReadHandle reader(blob);
    CryptoReader cryptoReader(reader, ...);
    if (!ReadMessage(cryptoReader, m))
    {
        PrintError("Unable to read encrypted message");
        return 1;
    }
    
    // Case 2: encrypted compressed data
    const std::vector<unsigned char> blob = ReceiveCompressedEncryptedMessage(...);
    datarw::VectorReadHandle reader(blob);
    ZipReader zipReader(reader, ...);
    CryptoReader cryptoReader(zipReader, ...);
    if (!ReadMessage(cryptoReader, m))
    {
        PrintError("Unable to read encrypted compressed message");
        return 1;
    }
}
```

__Note:__
__Originally, we have to decompress, decrypt, etc before performing any data manipulations.__
__It's ok if we need all data content, but there are cases when only small part of data is needed.__

## Work in progress:
  - add Xcode tests integration (in progress)
