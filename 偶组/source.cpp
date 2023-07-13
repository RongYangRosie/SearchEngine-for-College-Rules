#include <iostream>
#include <dirent.h>
#include <vector>
#include <fstream>
#include <map>
#include	<math.h>
#include <string>
#include <list>
#include <time.h>
#include<algorithm>
#include<numeric>
#define pathname "./database/"

using namespace std;

typedef list<int> WordOff;

typedef struct VVa{
	string filename;
	int count;
	int total;
	WordOff off;
	bool operator < (const struct VVa &va) const{
		return filename<va.filename;
	}
}Va;

typedef map<string,float> WordScore;

typedef list <Va> WordLocate;
typedef map<string, list<Va> > WordMap;

typedef struct{
	int count;
	int total;
}W;
typedef vector<float> FOff;
typedef struct{
	int count;
	int total;
	int off;
}WF;
typedef list<W> VS;
typedef multimap <string,WF> MMap;
MMap::iterator pre_i(MMap&c,string word){
	MMap::iterator w0=c.equal_range(word).first;
	return w0;
}
pair<string,WF> make_pai(string&T1,WF T2){
	return pair<string,WF>(T1,T2);
}
typedef struct FileScore{
	string filename;
	float score;
	WordOff off;
	WordOff poff;
	bool operator < (Va &fs) const{
		return filename<fs.filename;
	}
	bool operator > (Va &fs) const{
		return filename>fs.filename;
	}
}FS;
typedef list <FS> ScoreLocate;

void pwrit_off(WordOff::iterator &f){
	cout<<"itr->off:"<<*f<<endl;
}
void pwrit_locate(WordOff::iterator &f){
	cout<<"locate->off:"<<*f<<endl;
}

void pwrit_Va(ScoreLocate::iterator &v ){
	cout<<"filename:"<<v->filename<<endl;
	cout<<"score:"<<v->score<<endl;
	WordOff::iterator f;
    //for(f=v->off.begin();f!=v->off.end();f++)
	//	pwrit_off(f);
    for(f=v->poff.begin();f!=v->poff.end();f++)
		pwrit_locate(f);
	cout<<endl;
}
void sw(ScoreLocate &d,WordLocate::iterator v,int i){
	FS fs;
	WordOff off;
	WordOff poff;
	off.push_back(i);
	fs={v->filename,0,off,poff};
	d.push_back(fs);
}
void inisc(ScoreLocate &d,WordLocate&val){
	int i=0;
	for(WordLocate::iterator v=val.begin();v!=val.end();v++){
		sw(d,v,i++);
	}
}

void cut(ScoreLocate::iterator &first1,ScoreLocate::iterator &last1,WordLocate::iterator &first2,WordLocate::iterator &last2, ScoreLocate &tmp){
	ScoreLocate::iterator result=tmp.begin();
	int i=0,j=0;
	while(first1!=last1&&first2!=last2)
		if(*first1<*first2){
			first1++;
			i++;
		}
		else if(*first1>*first2){
			first2++;
			j++;
		}
		else {
			FS fs;
			WordOff off;
			off=first1->off;
			off.push_back(j);
			string filename=first1->filename;
			fs={filename,0,off};
			tmp.push_back(fs);
			first1++;
			first2++;
			i++;
			j++;
			result++;
		}
}
void cmp(ScoreLocate &tmp,ScoreLocate &val1,WordLocate &val2){
	ScoreLocate::iterator v1b=val1.begin();
	ScoreLocate::iterator v1e=val1.end();
	WordLocate::iterator v2b=val2.begin();
	WordLocate::iterator v2e=val2.end();
	cut(v1b,v1e,v2b,v2e,tmp);
}


void write_off(ofstream &outfile, WordOff::iterator &f){
	char Os=')';
	outfile.write((char *)&Os,sizeof(char));
	outfile.write((char *)&*f,sizeof(int));
}

void write_Va(ofstream &outfile,WordLocate::iterator &v ){
	char Vs='(';
	outfile.write((char *)&Vs,sizeof(char));
	const char*p=v->filename.c_str();
	outfile.write((char *)p,16*sizeof(char));
	outfile.write((char *)&(v->count),sizeof(int));
	outfile.write((char *)&(v->total),sizeof(int));
	WordOff::iterator f;
	for(f=v->off.begin();f!=v->off.end();f++){
		write_off(outfile,f);
	}
}
void write_map(WordMap& M,WordMap::iterator &i){
	string dir=pathname;
	dir=dir+i->first;
	ofstream outfile(dir,ios::out | ios::trunc|ios::binary);
	WordLocate::iterator v;
	for(v=i->second.begin();v!=i->second.end();v++){
		write_Va(outfile,v);
	}
	outfile.close();
}

bool is_Vs(ifstream &infile){
		char Vs;
		infile.read((char*)&Vs,sizeof(char));
		return Vs=='(';
}

bool is_Os(ifstream &infile){
		char Os;
		infile.read((char*)&Os,sizeof(char));
		return Os==')';
}

void read_off(ifstream&infile,WordOff &off){
	while(is_Os(infile)){
			char *of=(char*)malloc(sizeof(int));
			infile.read((char*)of,sizeof(int));
			off.push_back(*of);
			free(of);
	}
}
void read_Va(ifstream &infile,WordLocate&val){
	Va va;

	char *name=(char*)malloc(16*sizeof(char));
	infile.read((char*)name,16*sizeof(char));

	char *count=(char*)malloc(sizeof(int));
	infile.read((char*)count,sizeof(int));

	char *total=(char*)malloc(sizeof(int));
	infile.read((char*)total,sizeof(int));

	WordOff off;
	read_off(infile,off);
	va={name,*count,*total,off};
	free(name);
	free(count);
	val.push_back(va);
}
void read_map(WordMap& M,string &word){
	string dir=pathname;
	dir=dir+word;
	ifstream infile(dir,ios::in | ios::binary);
	WordLocate val;
	if(is_Vs(infile))
	do{
		read_Va(infile,val);
		infile.seekg((-1)*sizeof(char),ios::cur);
	}while(is_Vs(infile));
	M[word]=val;
	infile.close();
}

void pwrite_off(WordOff::iterator &f){
	cout<<"off:"<<*f<<endl;
}

void pwrite_Va(WordLocate::iterator &v ){
	cout<<"filename:"<<v->filename<<endl;
	cout<<"count:"<<v->count<<endl;
	cout<<"total:"<<v->total<<endl;
	WordOff::iterator f;
    for(f=v->off.begin();f!=v->off.end();f++)
		pwrite_off(f);
}

void pwrite_list(WordMap::iterator &i){
	WordLocate::iterator v;
    for(v=i->second.begin();v!=i->second.end();v++)
		pwrite_Va(v);
}

void pwrite_map(WordMap M){
    	WordMap::iterator i;
    	for(i=M.begin();i!=M.end();i++){
    		cout<<"wordname:"<<i->first<<endl;
			pwrite_list(i);
	}
}

void read_stru(WordMap&M){
		DIR *dp;
		struct dirent *dirp;
		vector<string> file_names;
		if((dp = opendir(pathname)) == NULL){
		perror("Fail to open dir:");
		exit(1);
		}
		while((dirp = readdir(dp)) != NULL){
			if(dirp->d_name[0] != '.'){
			file_names.push_back(dirp->d_name);
			}
		}
		for(vector<string>::iterator it = file_names.begin(); it != file_names.end(); it++){
			read_map(M,*it);
		}
}
void cir(WordMap & M,string word[],int n,ScoreLocate &tmp,ScoreLocate &d,int i){
	cmp(tmp,d,M[word[i]]);
	d.clear();
	if(i==n-1){
		return;
	}
	d.splice(d.begin(),tmp);
	tmp.clear();
}
void combine(ScoreLocate &tmp,WordMap M,string word[],int n){
	ScoreLocate d;

	inisc(d,M[word[0]]);
	for(int i=1;i<n;i++)
		cir(M,word,n,tmp,d,i);
}
float cal_var_vec(WordOff v,VS vs){
		float sum =accumulate(begin(v),end(v), 0.0);
		float mean =  sum / v.size();
		float accum  = 0.0;
		VS::iterator s=vs.begin();
		WordOff::iterator t=v.begin();
		for(s,t;t!=v.end()&&s!=vs.end();t++,s++){
			 accum  +=(float)(log10(s->total/s->count))*(*t-mean)*(*t-mean);
		}
		return accum;
}
void cals(WordOff& fv,float &var,VS vs,WordOff vf,MMap&c,string word[],int cur,int n,MMap::iterator f){
	if(cur==n){
		float tmp=cal_var_vec(vf,vs);
		if(var>tmp)
		{
			var=tmp;
			fv=vf;
		}
	}
	else
	{
		if(cur<n-1){
		MMap::iterator t=pre_i(c,word[cur+1]);
		for(f;f!=t;f++){
			vf.push_back(f->second.off);
			vs.push_back({f->second.count,f->second.total});
			cals(fv,var,vs,vf,c,word,cur+1,n,t);
			vf.pop_back();
			vs.pop_back();
		}
		}
		else{
			MMap::iterator k=c.find(word[cur]);
			for(k;k!=c.end();k++){
			vf.push_back(k->second.off);
			vs.push_back({k->second.count,k->second.total});
			cals(fv,var,vs,vf,c,word,cur+1,n,c.end());
			vf.pop_back();
			vs.pop_back();
			}
		}

	}
}
void calave(MMap&c,string word[],int n,int k,WordOff ::iterator &l,WordMap & M){
	WordLocate::iterator v=M[word[k]].begin();
	advance(v,*l);
	WordOff::iterator f;
	for(f=v->off.begin();f!=v->off.end();f++){
		c.insert(make_pai(word[k],{v->count,v->total,*f}));
	}
}
void calscore(string wordi[],int ni,ScoreLocate ::iterator &ti,WordMap & M){
	MMap ci;
	WordOff ::iterator l=ti->off.begin();
	int k=0;
	for(l;l!=ti->off.end();l++){
		calave(ci,wordi,ni,k,l,M);
		k++;
	}
	WordOff fvi;
	WordOff vfi;
	VS vsi;
	float vari=100000000;
	MMap::iterator tk=pre_i(ci,wordi[0]);
	cals(fvi,vari,vsi,vfi,ci,wordi,0,ni,tk);
	/*WordOff::iterator fk=fvi.begin();
	for(fk;fk!=fvi.end();fk++)
		cout<<*fk<<endl;
		*/
	/*for(MMap::iterator w1=ci.begin();w1!=ci.end();w1++)
		cout<<"word:"<<w1->first<<"	off:"<<w1->second.off<<" count:"<<w1->second.count<<" total:"<<w1->second.total<<endl;
		*/
	ti->poff=fvi;
	ti->score=vari;
}
void sortfile(WordMap M,string word[],int n,ScoreLocate &tmp){
	ScoreLocate ::iterator t=tmp.begin();
	for(t;t!=tmp.end();t++){
		cout<<"filename:"<<t->filename<<endl;
		calscore(word,n,t,M);
	}
}
bool op(FS &f1,FS &f2){
	return f1.score<f2.score;
}
void iniva(WordLocate &val,string filename,int count,int total,WordOff off){
    		Va va={filename,count,total,off};
    		val.push_back(va);
}

void insert(WordMap&M,string&word,string filename[],int n,int count[],int total[],WordOff off[]){
    		WordLocate val;
			for(int i=0;i<n;i++)
				iniva(val,filename[i],count[i],total[i],off[i]);
			val.sort();
			M[word]=val;
}
void write_data_base(WordMap M){
		for(WordMap::iterator i=M.begin();i!=M.end();i++)
			write_map(M,i);
}
void sort_file_off(string w[],int n,WordMap M,ScoreLocate &tmp){
	sort(w,w+n);
	combine(tmp,M,w,n);
	sortfile(M,w,n,tmp);
	tmp.sort(op);
}
int main(int argc,char *argv[])
{
    WordMap M;
    string word[4];
    word[0]="的子";
    word[1]="呵呵看";
    word[2]="到疯狂";
    word[3]="采购";
    string filename[]={"ahh","full","gkl","heloij"};
    string filenam[]={"full","gkl","glkl","heloij"};
    string filena[]={"aull","full","gkl","heloij","hkhhh","nkljldfi"};
    string filen[]={"aull","full","kkkk","glk","heloij"};
	int count[]={12,13,14,15};
	int coun[]={11,15,19,20};
	int cou[]={9,20,9,21,35,34};
	int co[]={15,17,35,24,25};
    int total[]={100,90,110,200};
    int tota[]={110,105,201,190};
    int tot[]={90,110,110,95,98,120};
    int to[]={80,100,110,120,115};
    WordOff of[]={{2,13,14},{5,10,11},{7,9,10},{11,12,15}};
    WordOff off[]={{1,3,4},{1,5,9},{1,7,8},{9,11,17}};
    WordOff o[]={{23,26,28},{75,77,79},{70,88,99},{1,5,9},{1,7,8},{9,11,17}};
    WordOff oi[]={{75,77,79},{70,88,99},{1,5,9},{1,7,8},{9,11,17}};
	insert(M,word[0],filename,4,count,total,off);
	insert(M,word[1],filenam,4,coun,tota,of);
	insert(M,word[2],filena,6,cou,tot,o);
	insert(M,word[3],filen,5,co,to,oi);
    //pwrite_map(M);
	//write_data_base(M);
	//
    /*WordMap temp;
    read_stru(temp);
    pwrite_map(temp);
	*/
	string w[10];
	int n=3;
	for(int i=0;i<n;i++){
		w[i].assign(word[i]);
	}
	ScoreLocate tmp;
	sort_file_off(w,n,M,tmp);


	ScoreLocate::iterator v;
	for(v=tmp.begin();v!=tmp.end();v++)
		pwrit_Va(v);
    return 0;
}
