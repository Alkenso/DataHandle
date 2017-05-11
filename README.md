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

## Short description
The main interface files are DataReadHandle and DataWriteHandle.
All child classes responsible for the particular data format or type processing must be inherited from them.

The data source class MUST redefine only 2 methods:
 - obtaining the full size of the data (in the final form)
 - read / write data from Range (position; length) to a specific address

## Reading and writing data
Reading and writing is allowed to read to and write from:
 - C-style arrays char / signed char / unsigned char / std :: byte (C ++ 17)
 - std :: vector <char / signed char / unsigned char / std :: byte (C ++ 17)>
 - std :: string
 
Reading and writing is restricted to ensure that the data will be read / written from a continuous byte array.

** Base classes **
The base DataReadHandle defines methods that provide:
 - obtaining the full size of the data (in the final form)
 - selective reading of data from the range
 - sequential reading of data
 - selective / sequential reading of LE / BE values

The base class DataWriteHandle defines methods that provide:
 - obtaining the full current data size (in the final form)
 - data writing it certain position
 - sequential data writing
 - selective / sequential recording of LE / BE values
