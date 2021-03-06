#include "BMP.h"
int* statisticRubikscubeSum(int n)
{
	int *sum=new int[13]{};
	for (int i = 0; i < n; ++i)
	{
		++sum[(rand() % 6 + 1) + (rand() % 6 + 1)];

	}
	return sum;
}

int main(int argc, char* argv[])
{
     int color =0x00ff00;
	
	 bmp_image test(1000,1000,color);
	 Point polygon1[] = { {100, 100}, {200, 100}, {150, 300} };
	 int n = sizeof(polygon1) / sizeof(polygon1[0]);
	 test.printLine(100,100,200,100,0xff0000);
	 test.printLine(100,100,150,300,0xff0000);
	 test.printLine(200,100,150,300,0xff0000);
	 test.fillPolygon(polygon1, n, 0x0000ff);
	// test.lineNtimes(0xff0000, 80);
	 test.write_bmp("polygon.bmp");
	try
	{
		for (int i = 1; i < argc; ++i)
		{
			if (strcmp(argv[i] ,"-i")==0)
			{
				cout << argv[i] << '\n';
				++i;
				test.read_bmp(argv[i]);
			}
			else if (strcmp(argv[i], "-o") == 0)
			{
				test.write_bmp(argv[++i]);
			}
			else if (strcmp(argv[i], "-r") == 0)
			{
				test.rotateRight();
			}
			else if (strcmp(argv[i], "-l") == 0)
			{
				test.rotateLeft();
			}
			else if (strcmp(argv[i], "-h") == 0)
			{
				test.flipHorizontal();
			}
			else if (strcmp(argv[i] ,"-v")==0)
			{
				test.flipVertical();
			}
			else if (strcmp(argv[i], "-c") == 0)
			{
				test.crop(stoi(argv[++i]), stoi(argv[++i]), stoi(argv[++i]), stoi(argv[++i]));
			}
			else if (strcmp(argv[i], "-b") == 0)
			{
				test.BlurNTimes(stoi(argv[++i]));
			}
			else if (strcmp(argv[i], "-s") == 0)
			{
				test.Sepia();
			}
			else if (strcmp(argv[i], "-bw") == 0)
			{
				test.blackAndWhite();
			}
			else if (strcmp(argv[i], "-sc") == 0)
			{
				test.scale(stoi(argv[++i]));
			}
			else if (strcmp(argv[i], "-constr") == 0)
			{
				cout << argv[i] << '\n';
				test = bmp_image(stoi(argv[++i]), stoi(argv[++i]), stoi(argv[++i]));
				cout << argv[i-4] << argv[i - 3]<< argv[i - 2] << argv[i - 1]<< argv[i ] << '\n';

			}

		}
	}
	catch (invalid_argument* ex)
	{
		cout << ex->what() << '\n';
	}
	
	
	system("pause");
	return 0;
}