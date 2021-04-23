#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <regex>
#include <sstream>
# define M_PI 3.14159265358979323846
using namespace std;
class bmp_image;
/**
* Structure contains information about the type, size, layout, dimensions
* and color format of a BMP file. Size of structure is 54 bytes.
*/

#pragma pack(push,1)
struct bmp_header {
	uint16_t type;              // "BM" (0x42, 0x4D)
	uint32_t size;              // file size
	uint16_t reserved1;         // not used (0)
	uint16_t reserved2;         // not used (0)
	uint32_t offset;            // offset to image data (54B)
	uint32_t dib_size;          // DIB header size (40B)
	uint32_t width;             // width in pixels
	uint32_t height;            // height in pixels
	uint16_t planes;            // 1
	uint16_t bpp;               // bits per pixel (1/4/8/24)
	uint32_t compression;       // compression type (0/1/2) 0
	uint32_t image_size;        // size of picture in bytes, 0
	uint32_t x_ppm;             // X Pixels per meter (0)
	uint32_t y_ppm;             // X Pixels per meter (0)
	uint32_t num_colors;        // number of colors (0)
	uint32_t important_colors;  // important colors (0)
};
#pragma pack(pop)


/**
* This structure describes a color consisting of relative intensities of
* red, green, and blue.
*/
struct pixel {
	uint8_t blue;
	uint8_t green;
	uint8_t red;
	pixel(){}
	pixel(uint8_t red, uint8_t green, uint8_t blue)
	{
		this->blue = blue;
		this->green = green;
		this->red = red;
	}
	
	//uint8_t alpha;
};
/**
* Structure need to store information about a number in the map
* x,y coordinates of start's point
*/
struct mapNumber
{
	uint32_t x=0;
	uint32_t y=0;
	uint32_t width=0;
	uint32_t height=0;
	mapNumber(){

	}
	mapNumber(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		this->x = x;
		this->y = y;
		this->height = height;
		this->width = width;
	}
};
/**
* Structure describes the BMP file format, which consists from two parts:
* 1. the header (metadata)
* 2. the data (pixels)
*/
class bmp_image {
	bmp_header* header = nullptr;
	pixel* data = nullptr;         // nr. of pixels is `width` * `height`


public:
    bmp_image()
	{}
	bmp_image(string file)
	{
		read_bmp(file);
	}
	
	bmp_image(uint32_t height, uint32_t width, int color = 0xCCCCCC);
	bmp_image(const bmp_image& b)
	{
		cout << "copy!!!!!" << "\n";
		this->header = new bmp_header();
		*this->header = *b.header;
		this->data = new pixel[header->width * header->height];
		for (int i = 0; i < header->width * header->height; ++i)
		{

			data[i] = b.data[i];

		}
		cout << header <<" "<< b.header<<"\n";
		cout << data <<" "<< b.data<<"\n";

	}
	bmp_image& operator=(const bmp_image& b)
	{
		cout << "=!!!!!"<<"\n";
		this->header = new bmp_header();
		*this->header = *b.header;
		this->data = new pixel[header->width * header->height];
		for (int i = 0; i < header->width * header->height; ++i)
		{

			data[i] = b.data[i];

		}
		return *this;

	}
	~bmp_image()
	{
		cout << "destr!!!!!" << "\n";
		if (this->data != nullptr)
		{
			delete [] this->data;
			this->data = nullptr;
		}
		if (this->header != nullptr)
		{
			delete this->header;
			this->header = nullptr;
		}
	}
	bmp_image* read_bmp(string file);
	bool write_bmp(string file);
	bool write_bmp(ostream* os);

	void flipVertical();
	void flipHorizontal();
	void rotateLeft();
	void rotateRight();

	void blackAndWhite();
	void Average(int& averageRED, int& averageGREEN, int& averageBLUE, int i, int j);
	void Blur();
	void Sepia();
	void BlurNTimes(int n);
	bmp_image crop(int x, int y, int height, int weight);
	void scale(double coeff);

	void circle(int x, int y, int R, int color);
	void circleNtimes(int color, int n);

	bool  readNumbersData(mapNumber* numbers);
	void getInfoToNumber(int* data, string info);
	void putText(string text, double scale, int x, int y, int color);
	//pixel* cropAndScaleFromMap(bmp_image sourceMap, mapNumber num, double coeff);

	void histogram(int* arr, int N);
	void printOneColumn(int width, int y, int x, int color);
private:

	bmp_header* read_bmp_header(string file);
	pixel* read_data(string file);
};

