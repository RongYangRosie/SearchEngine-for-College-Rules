#include <string>
#include <iostream>
#include <sstream>
#include <set>
#include <bitset> 
#include <iterator>
#include <fstream>
#include <ctype.h>
#include <string>
#include <stdio.h>  
#include <stdlib.h>
#include <cstdlib>
#include <vector>  
using namespace std;
set <string> CHAR;
string read()
{
  	ifstream in("punc.txt", ios::in);
 	istreambuf_iterator<char> beg(in), end;
 	string CHAR(beg, end);
 	in.close();
	//cout<<CHAR<<endl;
        return CHAR; 
} 
void  judge(string in_str)
{
     string bit1;
     string bit2;
     string bit3;
     for(int i=0;i<=in_str.size();i++)
     {
	 
         if(in_str[i]>0)
	 {
	     //bit1.clear();
	     bit1=in_str[i];
	     //bit1+=bit1[i];
	     CHAR.insert(bit1);
	     continue;
	 }
	 else if(in_str[i]< 0)
	 {
             bit2[0]=in_str[i];
	     bit2[1]=in_str[i+1];
             bit2[2]=in_str[i+2];
	     bit3.assign(in_str,i,3);
	     i++;
	     i++;
	    // bit3=bit2[0]+bit2[1]+bit2[2];
	     //cout<<bit3<<endl;
	     CHAR.insert(bit3);
	     
	 }
	
     }
}
void chinese_or_english(string str,string &num,string &alpha,string &chi)  
{  
    string chinese;
    string temp;
    string number;
    int flag;
    ostringstream oss;
    //ostringstream out_str;
     
    for (int i = 0; i < str.size(); i++) {  
    if (str[i] >= 65 && str[i] <= 90 || str[i] >=97 && str[i] <= 122) {      //ascII  
    //if ((str[i] & 0x80) == 0) {   
      temp[i]=str[i];	
	temp+=temp[i];
    }
    else if (str[i] >= 48 && str[i] <= 57){
    number[i]=str[i];
    number+=number[i];
    }
        
    else if (str[i] < 0){  
    //else {  
      chinese[0] = str[i];  
      chinese[1] = str[i + 1];  
      chinese[2] = str[i + 2];  
      i++;    //skip one more  
      i++;
	
    oss << chinese[0] << chinese[1] <<chinese[2]  ;
    }
  }
	num=number;
	alpha=temp;
	chi=oss.str();
}
void split(string strflag)  
{  
    string word;
	string tmp=string("\0");
	set<string>::iterator iter;
    for (int i = 0; i < strflag.size(); i++)
    {
        /*word.assign(strflag,i,3);
        i++;
        i++;*/
		if(word[i]<0){//标点或中文
			word.assign(strflag,i,3);
			 iter = CHAR.find(word);
			if(iter != CHAR.end()){
			//cout << (*iter) <<endl;
			tmp+=word;
			}else{
				if(tmp!="\0"){
					把word放到list里
					清空tmp；
				}
			}
			i+=2;
		}
		else{
			同理，判断是数字，还是英文，或英文标点
		}
    }
} 
int main()
 {   
     string str = "taiyang123太阳，范围";
     string Char;
     Char=read();
     //cout<<Char<<endl;
     judge(Char);
     
     set<string>::iterator it; //定义前向迭代器 
    //中序遍历集合中的所有元素  
    for(it=CHAR.begin();it!=CHAR.end();it++) 
    	cout<< *it <<endl;   
     
     string number,alpha,chinese;
     chinese_or_english(str,number,alpha,chinese);
	 split(chinese) ;  
      
    //system("pause");
     return 0;
 }
