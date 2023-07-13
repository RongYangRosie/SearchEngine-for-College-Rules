#include <cstdlib>
#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

map<string,int> readTxt(const char *s,map<string,int>temp);//从.txt文件读词库到map

int main()
{
	const char *s1="charfreq.txt";
	const char *s2="wordfreq.txt";
	map<string,int> myMapWord;//存储wordfreq的map
	map<string,int>myMapChar;//存储charfreq的map
	//system("iconv charfreq.txt -f UTF-8 -t ASCII -o charfreq.txt");
	myMapChar=readTxt(s1,myMapChar);//调用readTxt文件得到map
	myMapWord=readTxt(s2,myMapWord);
	return 0;
}
std::map<string,int> readTxt(const char *s,map<string,int>temp)
{
	string key,line;
	fstream file;
	char *pt;
	int value;
	cout<<"file name:"<<s<<endl;
	file.open(s,std::ios::in|std::ios::out);//打开指定文件
	if(!file){
		cout<<"error can't open file:"<<file<<endl;
	}
	else{
		cout<<"open file success"<<endl;
		while(!file.eof())//一直读到文件末尾
		{
			getline(file,line);//从file文件读取一行到line
			pt=strtok(&line[0],"	");//以tab键为分隔符分割读取到的一行
			int m=0;
			while(pt!=NULL)//当分割的字符串还没到尾时
			{
				m++;//用来标记是key还是value
				if(m%2!=0)
					key=pt;//第一次分割出来的是key
				else
				{
					value=atoi(pt);//把字符串转换成int整数
					//temp[key]=value;
					temp.insert(pair<string,int>(key,value));//在map中插入<key,value>值对
				//	cout<<key<<"*** "<<value<<endl;
				}
				pt=strtok(NULL,"	");//继续分割,NULL的作用只是为了使得每次调用时，都不是从头开始，而是从上次调用时查找所停止的位置开始
			}
		}
	}
	return temp;//返回建立好的map
}
