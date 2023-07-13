#include <iostream>
#include <string>
#include <map>
#include <list>
#include <algorithm>

using namespace std;

typedef list<int> WordOff;//词偏移
typedef struct VVa{
	string filename;//文件名
	int count;//文件总词数
	WordOff offset;//该文件下的词偏移
	bool operator < (const struct VVa &va) const{
		return filename<va.filename;
	}//比较函数
	/**建议可以加int node;//文件的编号
	 *			float wordinfo;//词的信息量，你们可以决定
	 */
}Va;//每个文件的信息
typedef list <Va> WordLocate;//每个词所对应的所以文件信息
typedef map<string, list<Va> > WordMap;//最终保存的地方

typedef struct FileScore{
	string filename;
	float score;
	WordOff off;
	WordOff poff;
	bool operator <(Va & fs) const{
		return filename<fs.filename;
	}

	bool operator > (Va &fs)const{
		return filename>fs.filename;
	}
}FS;

typedef list <FS> ScoreLocate;//the final result of score which is sorted

typedef struct{
	string abstract;
	string filename;
}ABS;
typedef struct {
     string name;//文件名
     string article;//文件正文
     string title;
     int flag;//标号
}FILE_S;

typedef list <ABS> ABS_LS;//abstract list
ABS get_file_abs(FS file);  //to get the abstract of one file
ABS_LS final_abs_list(ScoreLocate l );//to get  abstract  of each element whic is  in the list

list <FILE_S>  fileInfo;
int main(){
	ABS_LS return_list;
	ABS_LS::iterator p;
	ScoreLocate l;
	FILE_S t1,t2,t3;
	FS s1,s2,s3;
	t1.name="中该";
	s1.filename="中该";
	t2.name="中国";
	s2.filename="中国";
	t3.name="面在";
	s3.filename="面在";
	t1.article="在C++中，有一个stream这个类，所有的I/O都以这个“流”类为基础的，包括我们要认识的文件I/O，stream这个类有两个重要的运算符：1、插入器(<<)向流输出数据。比如说系统有一个默认的标准输出流(cout)，一般情况下就是指的显示器，所以，就表示把字符串和换行字符(' ')输出到标准输出流。2、析取器(>>)从流中输入数据。比如说系统有一个默认的标准输入流(cin)，一般情况下就是指的键盘，所以，cin>>x;就表示从标准输入流中读取一个指定类型(即变量x的类型)的数据。在C++中，对文件的操作是通过stream的子类fstream(file stream)来实现的，所以，要用这种方式操作文件，就必须加入头文件fstream.h。下面就把此类的文件操作过程一一道来。";
	t2.article="在C++中，有一个stream这个类，所有的I/O都以这个“流”类为基础的，包括我们要认识的文件I/O，stream这个类有两个重要的运算符：1、插入器(<<)向流输出数据。比如说系统有一个默认的标准输出流(cout)，一般情况下就是指的显示器，所以，就表示把字符串和换行字符(' ')输出到标准输出流。2、析取器(>>)从流中输入数据。比如说系统有一个默认的标准输入流(cin)，一般情况下就是指的键盘，所以，cin>>x;就表示从标准输入流中读取一个指定类型(即变量x的类型)的数据。在C++中，对文件的操作是通过stream的子类fstream(file stream)来实现的，所以，要用这种方式操作文件，就必须加入头文件fstream.h。下面就把此类的文件操作过程一一道来。";
	t3.article="在C++中，有一个stream这个类，所有的I/O都以这个“流”类为基础的，包括我们要认识的文件I/O，stream这个类有两个重要的运算符：1、插入器(<<)向流输出数据。比如说系统有一个默认的标准输出流(cout)，一般情况下就是指的显示器，所以，就表示把字符串和换行字符(' ')输出到标准输出流。2、析取器(>>)从流中输入数据。比如说系统有一个默认的标准输入流(cin)，一般情况下就是指的键盘，所以，cin>>x;就表示从标准输入流中读取一个指定类型(即变量x的类型)的数据。在C++中，对文件的操作是通过stream的子类fstream(file stream)来实现的，所以，要用这种方式操作文件，就必须加入头文件fstream.h。下面就把此类的文件操作过程一一道来。";
	fileInfo.push_back(t1);
	fileInfo.push_back(t2);
	fileInfo.push_back(t3);
	s1.poff.push_back(1);
	s1.poff.push_back(30);
	s1.poff.push_back(300);
	s2.poff.push_back(20);
	s2.poff.push_back(30);
	s2.poff.push_back(60);
	s3.poff.push_back(1);
	s3.poff.push_back(6);
	s3.poff.push_back(300);
	l.push_back(s1);
	l.push_back(s2);
	l.push_back(s3);
	return_list=final_abs_list(l);
	for(p=return_list.begin();p!=return_list.end();p++)
		cout<<(*p).filename<<"\t"<<(*p).abstract<<endl;
	return 0;
}
ABS get_file_abs(FS file){ //to get the abstract of one file
	list <FILE_S>:: iterator p;
	list <WordOff> off_l;
	WordOff tmp;
	WordOff::iterator o,t;
	list <WordOff>:: iterator wo;
	int start,num/*,tmp*/,size=0;
	string content;
	ABS abs_str;
	abs_str.filename=file.filename;
	for(p= fileInfo.begin();p!= fileInfo.end();p++){
		if(file.filename==(*p).name){
			content=(*p).article;
			break;
		}
	}
	//start=file.poff.front();
	size=file.poff.size();
	//o=file.poff.end();
	for(o=file.poff.begin();o!=file.poff.end();o++){
		t=o;
		start=(*o);
		while(t!=file.poff.end()){ //to find the offset which is  less than 300 far away
			if((*t)-(*o)<=300)
				tmp.push_back(*t);
			else break;
			t++;
		}
		off_l.push_back(tmp);
		tmp.clear();
	}
	for(wo=off_l.begin();wo!=off_l.end();wo++){
		if((*wo).size()>size){
			tmp=(*wo);
			size=tmp.size();
		}else if((*wo).size()==size){
			if( ((*wo).back()-(*wo).front()) > (tmp.back()-tmp.front()) ){
				tmp=(*wo);
				size=tmp.size();
			}
		}
	}
	start=tmp.front();
	num=tmp.back()-start+21;
	abs_str.abstract.assign(content,start,num);
	return abs_str;
}

ABS_LS final_abs_list(ScoreLocate l ){//to get  abstract  of each element whic is  in the list
	ScoreLocate::iterator p;
	ABS elem;
	ABS_LS res;
	for(p=l.begin();p!=l.end();p++){
		elem=get_file_abs(*p);
		res.push_back(elem);
	}
	return res;
}
