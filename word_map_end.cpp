#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <list>
#include <map>
using namespace std;

typedef list<int> WordOff;//词偏移
typedef struct VVa{
	string filename;
	int count;//出现的次数
	int total;//文章中的总词数
	WordOff offset;//词偏移
	bool operator < (const struct VVa &va) const{
		return filename<va.filename;
	}
}Va;

typedef struct {
     string name;//文件名
     string article;//文件正文
     string title;
     int flag;//标号
}FILE_S;

typedef struct{
	string keyword;
	int off;
}Word;

typedef list<Word> DLST;
typedef list<Va> WordLocate;
typedef map<string,list<Va> >  WordMap;

//FILELIST Filelist;
list <FILE_S> fileInfo;	//文件信息结构体
void updateMap(WordMap &wordmap,WordMap::iterator it,WordLocate Filelist,Word word,FILE_S file,int totalWord);
void addTomap(WordMap &wordmap,Word word,FILE_S file,int totalWord);

int main(int argc,char *argv[])
{
	int fileCount;//文章总数
	int totalWord;

	Word word;
	//string SearchWord;
	WordMap wordmap;
	WordMap::iterator iter;
	list <FILE_S>::iterator fit;
	WordLocate Filelist;
	DLST Dlst;

	for(fit=fileInfo.begin();fit!=fileInfo.end();fit++)
	{
		Dlst=divide((*fit).name,(*fit).article);//将文章进行分词，返回一个list
		totalWord=Dlst.size();
		for(DLST::iterator it=Dlst.begin();it!=Dlst.end();it++)//文章的每一个词都在map里进行查找
		{
			word=*it;//取出这个word

			//iter=wordmap.find((*it).keyword);
			iter=wordmap.find(word.keyword);//找这个词在不在map里面,find函数找到的话就是返回那个word所在的iterator，找不到就返回map.end()
			if(iter==wordmap.end())	//找不到这个word
			{
				addTomap(wordmap,word,(*fit),totalWord);//添加到map
			}
			else//找到了这个word
			{
				Filelist=iter->second;//返回的是value，也就是整个list
				updateMap(wordmap,iter,Filelist,word,(*fit),totalWord);//更新map
			}
	  	}

	}


	//输出map
	WordMap::iterator it2;//遍历wordmap,输出wordmap
	WordLocate::iterator k;
	WordOff::iterator m;
	for(it2=wordmap.begin();it2!=wordmap.end();++it2)
	{
		cout<<"key:"<<it2->first;
		Filelist=it2->second;
		for(k=Filelist.begin();k!=Filelist.end();k++)
		{
			cout<<"  the  value:"<<"filename: "<<(*k).filename<<"word count:"<<(*k).count<<"totalWord:"<<(*k).total;
			cout<<" offset:";
			for(m=(*k).offset.begin();m!=(*k).offset.end();m++)
				cout<<*m<<" ";
			cout<<endl;
		}
	}

	return 0;
}

void addTomap(WordMap &wordmap,Word word,FILE_S file,int totalWord)
{
	Va InsertFile;
	WordLocate Filelist;
	InsertFile.filename=file.name;//要插入到filelist的结构体
	InsertFile.count=1;
	InsertFile.total=totalWord;
	InsertFile.offset.push_back(word.off);

	Filelist.push_back(InsertFile);
	wordmap.insert(pair<string,list<Va> >(word.keyword,Filelist));//建立map

}



void updateMap(WordMap &wordmap,WordMap::iterator it,WordLocate Filelist,Word word,FILE_S file,int totalWord)
{
	WordLocate::iterator ite;
	Va InsertFile;
	int flag=0;


	for(ite=Filelist.begin();ite!=Filelist.end();ite++)
	{
		if((*ite).filename==file.name)//这个文件在list里面
		{
			(*ite).count=(*ite).count+1;//出现的次数++
			(*ite).offset.push_back(word.off);//把词的偏移量放进list
			break;
		}
		else
		{
			flag++;
		}

	}


	//这个文件不在list里面
	if(flag==Filelist.size())
	{
		InsertFile.filename=file.name;
		InsertFile.count=1;
		InsertFile.total=totalWord;
		InsertFile.offset.push_back(word.off);
		Filelist.push_back(InsertFile);
	}
	wordmap.erase(it);//删除这个<key,value>键值对，重新添加更改后的<key,value>
	wordmap.insert(pair<string,list<Va> >(word.keyword,Filelist));
	for(ite=Filelist.begin();ite!=Filelist.end();ite++)//输出更改后的list
		cout<<(*ite).filename<<" "<<(*ite).count<<" "<<(*ite).total<<endl;
}
