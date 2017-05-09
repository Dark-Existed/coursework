#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
#include "CalEquation.h"
#include "Generated.h"
#include "ProcessLanguage.h"
using namespace std;

int main(int argc, char const *argv[])
{
	srand(unsigned(time(0)));
	
    int count=0, t=0, f, temp, flag=0;
	float input, answer;
	string equation, location, clanguage;
	char LanguageRead[20][200],end;

    ifstream fin;
    fin.open(argv[1]);
	fin >> count;
	if (count != 0)
		flag = 1;
	fin.close();

    ofstream fout;
    fout.open(argv[2]);

	cout<<"Enter the serial number to select the language."<<endl;
    cout<<"==================================================================="<<endl;
    LanguageList();
    cout<<"==================================================================="<<endl;
	cin>>clanguage;
	while(JudgeLanguage(&location,&clanguage)==false)
    {
        cout<<"Your input is wrong or software does not support your language."<<endl;
        cin>>clanguage;
    }
    dispose(LanguageRead,&location);
    cout<<LanguageRead[0]<<endl;
    cout<<LanguageRead[1];
    fout<<LanguageRead[1]<<count<<endl;
    


    if (flag != 1)
        cin>>count;
    
    for (int i = 0; i < count; ++i)
    {
    	equation = generateExpression();
    	answer = calculateResult(equation);
    	temp=(int)(answer*100+0.5f);//四舍五入保留两位小数
        answer=(float)temp/100;
		cout << '<' << i + 1 << "> " << equation << '=';
		fout << '<' << i + 1 << "> " << equation << '=' << answer << endl;
    	cin>>input;
    	if (input==answer)
    	{
    		t++;
    		cout<<LanguageRead[2]<<endl;
            fout<<LanguageRead[2]<<endl;

    	}
    	else
    	{	cout<<LanguageRead[3]<<answer<<endl;
            fout<<LanguageRead[3]<<answer<<endl;
        }
    }
    f = count-t;
	cout << LanguageRead[4] << endl;
	cin >> end;
	if (end == 'Q' || end == 'q')
	{
		cout << LanguageRead[5] << t << LanguageRead[7] << endl;
        fout << LanguageRead[5] << t << LanguageRead[7] << endl;
		
        cout << LanguageRead[6] << f << LanguageRead[7];
        fout << LanguageRead[6] << f << LanguageRead[7];
	}

    fout.close();
	return 0;
}
