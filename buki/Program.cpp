#include "STRING.h"
#include <fstream>
#include <filesystem>

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
	//uint8_t alpha;
};

/**
* Structure describes the BMP file format, which consists from two parts:
* 1. the header (metadata)
* 2. the data (pixels)
*/
class bmp_image {
	bmp_header* header=nullptr;
	pixel* data=nullptr;         // nr. of pixels is `width` * `height`

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
		fout.write((char*)header, 54);
		long int numberOfPixels = header->width * header->height;
		for (int i = 0; i < numberOfPixels; i++) {
			fout.write((char*)&data[i], 3);
		}
		fout.close();
		return true;
	}
	void flipVertical()
	{
		unsigned int size = header->height % 2 == 0 ? header->height / 2 + 1 : header->height / 2;
		unsigned int width = header->width;
		pixel temp;
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				temp = data[i*width+j];
				data[i * width + j] = data[(header->height - 1 - i) * width + j];
				data[(header->height - 1 - i) * width + j] = temp;
			}
		}

	}
	void flipHorizontal()
	{
		unsigned int size = header->width % 2 == 0 ? header->width / 2 + 1 : header->width / 2;
		unsigned int width = header->width;
		pixel temp;
		for (int i = 0; i < header->height; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				temp = data[i * width + j];
				data[i * width + j] = data[(i) * width +width-1- j];
				data[(i)*width + width - 1 - j] = temp;
			}
		}

	}
	void rotateLeft()
	{
		if (header->height == header->width)
		{
			pixel tmp;
			int size = header->height;
			for (int i = 0; i < size / 2; i++)
			{
				for (int j = i; j < size - 1 - i; j++)
				{
					tmp = data[i * size + j];
					data[i * size + j] = data[i + size * (size - 1 - j)];
					data[i + size * (size - 1 - j)] = data[(size - 1 - i) * size + size - 1 - j];
					data[(size - 1 - i) * size + size - 1 - j] = data[(size - 1 - i) + size * j];
					data[(size - 1 - i) + size * j] = tmp;
				}
			}
		}
	
		else
		{
			
			pixel *tmp = new pixel[header->width * header->height];
			int temp = 0;
			for (int i = 0; i < header->width; i++)
			{
				for (int j = 0; j < header->height; j++)
				{
					//temp = j * (header->width) + header->width - 1 - i;
					tmp[i * header->height + j] = data[j*(header->width)+header->width-1-i];
				}
			}
			delete [] data;
			data = tmp;
			int t = header->height;
			header->height = header->width;
			header->width = t;


		}

	}
	void rotateRight()
	{
		if (header->height == header->width)
		{
			pixel tmp;
			int size = header->height;
			for (int i = 0; i < size / 2; i++)
			{
				for (int j = i; j < size - 1 - i; j++)
				{
					tmp = data[i * size + j];
					data[i * size + j] = data[j * size + size - 1 - i];
					data[j * size + size - 1 - i] = data[(size - 1 - i) * size + size - 1 - j];
					data[(size - 1 - i) * size + size - 1 - j] = data[(size - 1 - j) * size + i];
					data[(size - 1 - j) * size + i] = tmp;
				}
			}
		}
		else
		{

			pixel* tmp = new pixel[header->width * header->height];
			int temp = 0;
			for (int i = 0; i < header->width; i++)
			{
				for (int j = 0; j < header->height; j++)
				{
					temp = j * (header->width) + header->width - 1 - i;
					tmp[i * header->height + j] = data[i + (header->width) *(header->height - 1 - j)];
				}
			}
			delete[] data;
			data = tmp;
			int t = header->height;
			header->height = header->width;
			header->width = t;

		}
	

	}
	void blackAndWhite()
	{
		long int numberOfPixels = header->width * header->height;
		uint8_t average = 0;
		for (int i = 0; i < numberOfPixels; i++) {
			average = (data[i].blue + data[i].green + data[i].red) / 3;
			data[i].blue = average;
			data[i].green = average;
			data[i].red = average;
			
		}
	}
	void Average(int& averageRED, int& averageGREEN, int& averageBLUE, int i, int j)
	{
		averageRED+= data[i * header->width + j].red;
		averageGREEN += data[i * header->width + j].green;
		averageBLUE += data[i * header->width + j].blue;
	}
	void Blur()
	{
		int counter = 0;
		int averageRED = 0;
		int averageGREEN = 0;
		int averageBLUE = 0;
		for (int i = 0; i < header->height; i++)
		{
			for (int j = 0; j < header->width; j++)
			{
				counter = 1;
				 averageRED = 0;
				 averageGREEN = 0;
				averageBLUE = 0;
				Average(averageRED, averageGREEN, averageBLUE, i, j);
				if (i != 0)
				{
					Average(averageRED, averageGREEN, averageBLUE, i-1, j);
					++counter;
					if (j != 0)
					{
						Average(averageRED, averageGREEN, averageBLUE, i-1, j-1);
						++counter;
					}
					if (j != (header->width - 1))
					{
						Average(averageRED, averageGREEN, averageBLUE, i-1, j+1);
						++counter;
					}
				}
				if (j != 0)
				{
					Average(averageRED, averageGREEN, averageBLUE, i, j-1);
					++counter;
				}
				if(j!= (header->width - 1))
				{
					Average(averageRED, averageGREEN, averageBLUE, i, j+1);
					++counter;
				}
				if (i !=( header->height-1))
				{
					Average(averageRED, averageGREEN, averageBLUE, i+1, j);
					++counter;
					if (j != 0)
					{
						Average(averageRED, averageGREEN, averageBLUE, i+1, j-1);
						++counter;
					}
					if (j != (header->width - 1))
					{
						Average(averageRED, averageGREEN, averageBLUE, i+1, j+1);
						++counter;
					}
				}
				data[i * header->width + j].blue = averageBLUE / counter;
				data[i * header->width + j].green = averageGREEN / counter;
				data[i * header->width + j].red = averageRED / counter;
			}
		}
	}
	void Sepia()
	{
		int inputRed = 0;
		int inputGreen = 0;
		int inputBlue = 0;
		long int numberOfPixels = header->width * header->height;

		for (int i = 0; i < numberOfPixels; i++) {

			inputRed = data[i].red;
			inputGreen = data[i].green;
			inputBlue = data[i].blue;
			data[i].red = min((int)((inputRed * .393) + (inputGreen * .769) + (inputBlue * .189)),255);
			data[i].green = min((int)((inputRed * .349) + (inputGreen * .686) + (inputBlue * .168)),255);
			data[i].blue = min((int)((inputRed * .272) + (inputGreen * .534) + (inputBlue * .131)),255);

		}

	}
	void BlurNTimes(int n)
	{
		while (n != 0)
		{
			Blur();
			--n;
		}
	}
	
private:

	bmp_header* read_bmp_header(string file)
	{
		std::ifstream is(file, ios_base::binary);
		if (!is.is_open())
		{
			throw new invalid_argument("Can't open file");
		}
		header = new bmp_header();
		is.read((char*)header, 54);
		if (header->type != 0x4D42) {
			return nullptr;
		}
		cout << header->type;
		cout << header->height << '\n';
		cout << header->width << '\n';
		cout << header->size << '\n';
		cout << header->offset << '\n';
		is.close();
		return header;


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
	bmp_header header;
	try
	{
		bmp_image test("courtyard.bmp");
		test.BlurNTimes(3);
		test.write_bmp("lenna2.bmp");
	}
	catch (invalid_argument* ex)
	{
		cout << ex->what() << '\n';
	}
	

	system("pause");
	return 0;
}