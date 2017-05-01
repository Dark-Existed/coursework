#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//语言列表
void LanguageList()
{
	int num = 1;
	char Language[20];
	fstream file;
	file.open("language\\Languagelist.txt");

	while (file.getline(Language, 20))
	{
		cout << num << "." << Language << endl;
		num++;
	}

	file.close();
}

// 判断是否支持该语言
bool JudgeLanguage(string *location,string *clanguage)
{
	*location = "language\\" + *clanguage + ".txt";
	fstream file;
	file.open(*location);

	if (file.is_open())
	{
		file.close();
		return true;
	}
	else
		return NULL;
}

//将文件读入数组中
void dispose(char (*LanguageRead)[200],string *location)
{
	fstream File; 
	File.open(*location);
	int i;
	for (i = 0; File.getline(LanguageRead[i],200); ++i)
	{
	}
	File.close();
}
