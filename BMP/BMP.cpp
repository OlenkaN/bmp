
#include "BMP.h"


bmp_image* bmp_image:: read_bmp(string file)
{
	if (read_bmp_header(file) != nullptr)
	{
		read_data(file);
	}
	return this;
}
 bmp_image ::bmp_image(uint32_t height, uint32_t width, int color )
{
	header = new bmp_header();
	header->type = 0x4D42;
	header->height = height;
	header->width = width;
	header->bpp = 24;
	header->planes = 1;
	header->offset = 54;
	header->dib_size = 40;
	header->size = (height * width * sizeof(pixel)) * header->planes + header->offset;

	data = new pixel[height * width];
	for (int i = 0; i < height * width; i++)
	{
		data[i] = *((pixel*)(&color));
	}
}
bool bmp_image::write_bmp(string file)
{
	ofstream fout(file, ios::binary);
	bool res = write_bmp(&fout);
	fout.close();
	return res;
}

bool bmp_image::write_bmp(ostream* os)
{
	if (!os) return false;
	char buff[54] = {};
	buff[0] = 'B';
	buff[1] = 'M';
	*((uint32_t*)(buff + 2)) = header->size;
	*((uint32_t*)(buff + 10)) = 54;
	*((uint32_t*)(buff + 14)) = 40;
	*((uint32_t*)(buff + 18)) = header->width;
	*((uint32_t*)(buff + 22)) = header->height;
	*((uint16_t*)(buff + 26)) = 1;
	*((uint16_t*)(buff + 28)) = 24;

	os->write(buff, 54);
	//fout.write((char*)header, 54);
	os->write((char*)data, 3 * header->width * header->height);

	return true;
}
void bmp_image::flipVertical()
{
	unsigned int size = header->height % 2 == 0 ? header->height / 2 + 1 : header->height / 2;
	unsigned int width = header->width;
	pixel temp;
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			temp = data[i * width + j];
			data[i * width + j] = data[(header->height - 1 - i) * width + j];
			data[(header->height - 1 - i) * width + j] = temp;
		}
	}

}

void bmp_image::flipHorizontal()
{
	unsigned int size = header->width % 2 == 0 ? header->width / 2 + 1 : header->width / 2;
	unsigned int width = header->width;
	pixel temp;
	for (int i = 0; i < header->height; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			temp = data[i * width + j];
			data[i * width + j] = data[(i)*width + width - 1 - j];
			data[(i)*width + width - 1 - j] = temp;
		}
	}

}

void bmp_image::rotateLeft()
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

		pixel* tmp = new pixel[header->width * header->height];
		int temp = 0;
		for (int i = 0; i < header->width; i++)
		{
			for (int j = 0; j < header->height; j++)
			{
				//temp = j * (header->width) + header->width - 1 - i;
				tmp[i * header->height + j] = data[j * (header->width) + header->width - 1 - i];
			}
		}
		delete[] data;
		data = tmp;
		int t = header->height;
		header->height = header->width;
		header->width = t;


	}

}

void bmp_image::rotateRight()
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
				tmp[i * header->height + j] = data[i + (header->width) * (header->height - 1 - j)];
			}
		}
		delete[] data;
		data = tmp;
		int t = header->height;
		header->height = header->width;
		header->width = t;

	}


}

void bmp_image::blackAndWhite()
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

void  bmp_image:: Average(int& averageRED, int& averageGREEN, int& averageBLUE, int i, int j)
{
	averageRED += data[i * header->width + j].red;
	averageGREEN += data[i * header->width + j].green;
	averageBLUE += data[i * header->width + j].blue;
}

void bmp_image:: Blur()
{
	int counter = 0;
	int averageRED = 0;
	int averageGREEN = 0;
	int averageBLUE = 0;
	int dj[8] = { -1,0,1,1,1,0,-1,-1 };
	int di[8] = { -1,-1,-1,0,1,1,1,0 };
	for (int i = 0; i < header->height; i++)
	{
		for (int j = 0; j < header->width; j++)
		{
			counter = 1;
			averageRED = 0;
			averageGREEN = 0;
			averageBLUE = 0;
			Average(averageRED, averageGREEN, averageBLUE, i, j);
			for (int k = 0; k < 8; ++k)
			{
				if ((j + dj[k]) >= 0 && (j + dj[k]) < header->width &&
					(i + di[k]) >= 0 && (i + di[k]) < header->height)
				{
					Average(averageRED, averageGREEN, averageBLUE, i+di[k], j+dj[k]);
					++counter;
				}
			}
			data[i * header->width + j].blue = averageBLUE / counter;
			data[i * header->width + j].green = averageGREEN / counter;
			data[i * header->width + j].red = averageRED / counter;
		}
	}
}

void bmp_image::Sepia()
{
	int inputRed = 0;
	int inputGreen = 0;
	int inputBlue = 0;
	long int numberOfPixels = header->width * header->height;

	for (int i = 0; i < numberOfPixels; i++) {

		inputRed = data[i].red;
		inputGreen = data[i].green;
		inputBlue = data[i].blue;
		data[i].red = min((int)((inputRed * .393) + (inputGreen * .769) + (inputBlue * .189)), 255);
		data[i].green = min((int)((inputRed * .349) + (inputGreen * .686) + (inputBlue * .168)), 255);
		data[i].blue = min((int)((inputRed * .272) + (inputGreen * .534) + (inputBlue * .131)), 255);

	}

}

void bmp_image::BlurNTimes(int n)
{
	while (n != 0)
	{
		Blur();
		--n;
	}
}

void bmp_image::crop(int y, int x, int height, int width)
{
	pixel* temp = new pixel[height * width];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			temp[(height-1-i) * width + j] = data[(header->height-1-(y + i)) *header->width  + x + j];
		}

	}
	delete[] data;
	data = temp;
	header->height = height;
	header->width = width;
}

void bmp_image::scale(double coeff)
{
	cout << header->height * header->width * coeff * coeff;
	pixel* temp = new pixel[header->height * header->width*coeff*coeff];
	for ( int i = 0; i < (int)header->height*coeff; i++)
	{
		for ( int j = 0; j < (int)header->width*coeff; j++)
		{

			temp[(int)(i*header->width*coeff)+j] = data[((int)(i/coeff)) * header->width + (int)(j/coeff)];
		}

	}
	delete[] data;
	data = temp;
	header->height = header->height*coeff;
	header->width = header->width*coeff;
}
bmp_header* bmp_image:: read_bmp_header(string file)
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
	cout << header->height << '\n';
	cout << header->width << '\n';
	cout << header->size << '\n';
	cout << header->offset << '\n';
	is.close();
	return header;


}
pixel* bmp_image::read_data(string file)
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
	/*if (!f.eof())
	{
		return nullptr;
	}*/
	f.close();
	return this->data;
}

void bmp_image :: circle(int x, int y, int R, int color)
{
	int a;
	int x1;
	int y1;
	for (a = 0; a <= 1000; a++)
	{
		x1 = round(R * cos(a)) + x;
		y1 = round(R * sin(a)) + y;
		data[y1 * header->width + x1] = *((pixel*)(&color));
	}

}

void bmp_image::circleNtimes(int color, int n)
{
	int y = header->height / 2;
	int x = header->width / 2;
	int R = trunc(min(x, y) * 0.7);
	int r = trunc(min(x, y) * 0.25);
	circle(x, y, R, color);
	int x1, y1;
	int a = 0;
	int delta = 360 / n;
	while (a < 360)
	{
		x1 = round(R * cos(a * M_PI / 180.0)) + x;
		y1 = round(R * sin(a * M_PI / 180.0)) + y;
		circle(x1, y1, r, color);
		a += delta;
	}
}

bool bmp_image:: readNumbersData(mapNumber* numbers)
{
	ifstream f("mapForNumbers.txt");
	string info;
	int index = 0;
	int data[5];
	while (getline(f, info))
	{
		//getInfoToNumber(data, info);
		numbers[index].x = data[1];
		numbers[index].y = data[2];
		numbers[index].width = data[3];
		numbers[index].height = data[4];
		++index;
	}
	return true;
}



void bmp_image::histogram(int* arr, int N)
{
	int length = (int)header->width / (2 * (N + 1));
	int x = length;
	int coeff = 3;
	for (int i = 0; i < N; ++i)
	{
		if (arr[i] > header->height)
		{
			printOneColumn(length, header->height, x, 0x7d7d7d);
		}
		else
		{
			printOneColumn(length, arr[i], x, 0x7d7d7d);
		}
		x = length * coeff;
		coeff += 2;
	}
}

void bmp_image::printOneColumn(int width, int y, int x, int color)
{
	for (int i = 0; i < y; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			data[(y - i - 1) * header->width + x + j] = *((pixel*)(&color));
		}
	}
}