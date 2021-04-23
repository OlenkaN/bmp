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
void func(bmp_image test)
{
	test.blackAndWhite();
	test.write_bmp("lennaFunc1.bmp");
}

int main(int argc, char* argv[])
{
	bmp_image test("lenna.bmp");
	func(test);
	test.write_bmp("lennaTest.bmp");
     /*int color =0x00ff00;
	 int* arrTest=statisticRubikscubeSum(10000);
	 bmp_image test(1000,1000,color);
	 test.histogram(arrTest, 13);
	 test.write_bmp("text.bmp");
	 //test.putText("12", 0.7, 0, 0, 0x993366);
	 //test.write_bmp("text.bmp");*/
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