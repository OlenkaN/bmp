#include "STRING.h"
#include <fstream>
#include <filesystem>

/**
* Structure contains information about the type, size, layout, dimensions
* and color format of a BMP file. Size of structure is 54 bytes.
*/


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


/**
* This structure describes a color consisting of relative intensities of
* red, green, and blue.
*/
struct pixel {
	uint8_t blue;
	uint8_t green;
	uint8_t red;
	//uint8_t alpha;
};

/**
* Structure describes the BMP file format, which consists from two parts:
* 1. the header (metadata)
* 2. the data (pixels)
*/
class bmp_image {
	bmp_header* header;
	pixel* data;         // nr. of pixels is `width` * `height`
public:
	bmp_image(string file)
	{
		read_bmp(file);
	}
	bmp_image* read_bmp(string file)
	{
		if (read_bmp_header(file) != nullptr)
		{
			read_data(file);
		}

		return this;
	}
	bool write_bmp(string file)
	{
		ofstream fout(file, ios::binary);
		if (!fout) return false;
		fout.write((char*)&header, 54);
		long int numberOfPixels = header->width * header->height;
		for (int i = 0; i < numberOfPixels; i++) {
			fout.write((char*)&data, 3);
		}
		fout.close();
		return true;
	}
private:
	bmp_header* read_bmp_header(string file)
	{
		std::ifstream is("courtyard.bmp", ios_base::binary);
		if (!is)
		{
			throw new invalid_argument("Can't open file");
		}
		if (header = (struct bmp_header*)malloc(sizeof(bmp_header))) {
			is.read((char*)header->type, 2);
			is.read((char*)header->size, 4);
			is.read((char*)header->reserved1, 4);
			is.read((char*)header->offset, 4);
			if (header->type != 0x4D42) {
				return nullptr;
			}

			cout << header->size << '\n';
			cout << header->offset << '\n';
			is.close();
			return header;
		}
		else
			return nullptr;

	}
	pixel* read_data(string file)
	{
		ifstream f(file, ios_base::binary);
		if (!f) throw new invalid_argument("Can't open file");
		f.seekg(54, ios::beg);
		long int numberOfPixels = header->width * header->height;
		data = new pixel[numberOfPixels];
		for (int i = 0; i < numberOfPixels; ++i)
		{

			f.read((char*)&data[i], 3);
			if (f.eof())
			{
				return nullptr;
			}

		}
		if (!f.eof())
		{
			return nullptr;
		}
		f.close();
		return this->data;
	}
};



int main()
{
	/*bmp_header header;
	cout << sizeof(header) << '\n';
	std::ifstream is("courtyard.bmp", ios_base::binary);
	is.read((char*)&header, 54);
	is.close();
	cout << header.height << '\n';
	cout << header.width << '\n';
	cout << header.size << '\n';
	cout << header.offset << '\n';
	*/

	bmp_image test("courtyard.bmp");
	test.write_bmp("yard2.bmp");

	system("pause");
	return 0;
}