#include<iostream>
#include <fstream>
#include<string>
#include<list>
#include<algorithm>
#include<map>
#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;

typedef struct{
	string keyword;
	int off;
}Word;				//define the type of the elements in the result returned by splitting the search string

typedef struct{
	string sentence;
	int off;
}STR;				//clause
typedef list<Word>  DLST;//the result data type of dividing a string
typedef list<STR> STRLIST;
typedef map<string,int> DICTION;//word dictonary

DICTION myMapWord;//存储wordfreq的map
DICTION myMapChar;//存储charfreq的map

DLST all_divi_res(STRLIST str);//to find all the words which  starts with the character appearing in the search statement,and deal with them
DLST last_choose_res(DLST,string search);//Adopt  one strategy to decide the final consequence of the combination of key words
DLST one_divi_res(STR Str,DICTION w_dictionary);//to divide one string to serveral words
DLST deal_with_res(DLST res,STR str);//to get the splitting result of one substring
DICTION readTxt(const char *s,DICTION temp);//从.txt文件读词库到map


int main(){
	//string test="hello";
	//string tmp;
	string::iterator t,t1;
	STR test;
	int i;
	STRLIST tmp;
	DLST res,rest;
	DLST:: iterator p;
	test.sentence="祖国我爱你";
	test.off=0;
	/****************** load word dictionary  **************************/
	const char *s1="charfreq.txt";
	const char *s2="wordfreq.txt";
	//system("iconv charfreq.txt -f UTF-8 -t ASCII -o charfreq.txt");
	myMapChar=readTxt(s1,myMapChar);//调用readTxt文件得到map
	myMapWord=readTxt(s2,myMapWord);

/************************** split search sentence**************************************/
	tmp.push_back(test);
	res=all_divi_res(tmp);
	//rest=last_choose_res(res,test.sentence);
	//cout<<2<<endl;
	for(p=res.begin();p!=res.end();p++){
		cout<<(*p).keyword<<"\t"<<(*p).off<<endl;
	}
	return 0;
}

DICTION readTxt(const char *s,DICTION temp)
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

DLST one_divi_res(STR Str,DICTION w_dictionary){//to divide one string to serveral words
	DLST t;
	string str;
	string::iterator p;
	Word word,tmp;
	int p1=0,p2=2;
	str=Str.sentence;
	for(p=str.begin();p!=str.end(),p1<str.length();){
			if(p1+3*p2>str.length())
				{
					p1+=3;
					p2=2;
					continue;
				}
			tmp.keyword.assign(str,p1,3*p2);
			//cout<<p1<<" "<<p2<<" "<<tmp.keyword<<endl;
			if(w_dictionary.count(tmp.keyword)==0)//when there is no word can be found in dictionary
			{
				p2++;
				continue;
			}else {//find word
				word.keyword=tmp.keyword;
				word.off=p1+Str.off;
				t.push_back(word);
				//cout<<word.keyword<<p2<<endl;
				p2++;
			}
	}
	return t;
}
DLST all_divi_res(STRLIST str){ //to find all the words which  starts with the character appearing in the search statement,and then deal with them
	string tmp;
	STR search_sentence;
	DLST all,sub,subres,result;
	STRLIST:: iterator slist;
	DLST::iterator dl;
	Word num_letter;
	for(slist=str.begin();slist!=str.end();slist++){
		search_sentence=(*slist);
		if(search_sentence[0]<0){
			sub=one_divi_res(search_sentence,myMapWord);
			subres=last_choose_res(sub,search_sentence.sentence);
			result=deal_with_res(subres,(*slist));
			dl=all.end();
			//cout<<result.size();
			all.splice(dl,result);
		}else{
			num_letter.keyword=search_sentence.sentence;
			num_letter.off=search_sentence.off;
			all.push_back(num_letter);
		}

	}
	return all;

}

//Adopt  oen strategy to decide the final consequence of the combination of key words
DLST last_choose_res(DLST aL,string search){
	DLST res;
	DLST amb_r;//ambiguity range
	Word tmp;
	DLST:: iterator p,t,p_flag;
	tmp=aL.front();
	int i=0,offset=0;
	//cout<<aL.size()<<endl;
	for(p=aL.begin();p!=aL.end();p++)
	{
		if(tmp.off==(*p).off){
			if((tmp.keyword.find((*p).keyword))==string::npos){
				tmp=(*p);
			}
		}else{
			if(offset<=tmp.off){
				res.push_back(tmp);
				offset=tmp.off+tmp.keyword.length();
			}
			tmp=(*p);
			if((p++)==aL.end() && offset<=(tmp.off))
				res.push_back(tmp);
			p--;
			}
	}
	return res;
}

DLST deal_with_res(DLST res,STR str){  // to get the splitting result of one substring
	int length,offset;
	Word tmp;
	DLST:: iterator p;
	DLST  sp;
	length=res.size();
	int *arr=new int[length];
	//tmp=res.front();
	offset=str.off;
	for(p=res.begin();p!=res.end();p++){
		if(offset<(*p).off){
				for(int i=0;i+str.off<(*p).off;){
						tmp.keyword.assign(str.sentence,i,3);
						tmp.off=offset;
						sp.push_back(tmp);
						offset+=3;
						i+=3;
				}
		}
		sp.push_back((*p));
		offset=(*p).off+(*p).keyword.length();
	}
	return sp;
}
