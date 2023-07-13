typedef list<int> WordOff; // Word offset
typedef struct VVa{
string filename; // File name
int count; // Word frequency count in the article
int total; // Total number of words in the file
WordOff off; // Word offset in the file
bool operator < (const struct VVa &va) const{
return filename < va.filename;
}
} Va;
typedef list<Va> WordLocate; // File information corresponding to each word
typedef map<string, list<Va>> WordMap; // Final storage location

typedef struct FileScore{
string filename; // File name
float score; // Score, used for even groups
WordOff off; // Offset related to scoring, used for even groups
WordOff poff; // Offset related to scoring, used for odd groups
bool operator < (Va &fs) const{
return filename < fs.filename;
}
bool operator > (Va &fs) const{
return filename > fs.filename;
} // Comparison function
} FS;
typedef list<FS> ScoreLocate; // Final list of scores, will be sorted

Translation of Chinese comments:
typedef list<int> WordOff; // Word offset
typedef struct VVa{
string filename; // File name
int count; // Word frequency count in the article
int total; // Total number of words in the file
WordOff off; // Word offset in the file
bool operator < (const struct VVa &va) const{
return filename < va.filename;
}
} Va;
typedef list<Va> WordLocate; // File information corresponding to each word
typedef map<string, list<Va>> WordMap; // Final storage location

typedef struct FileScore{
string filename; // File name
float score; // Score, used for even groups
WordOff off; // Offset related to scoring, used for even groups
WordOff poff; // Offset related to scoring, used for odd groups
bool operator < (Va &fs) const{
return filename < fs.filename;
}
bool operator > (Va &fs) const{
return filename > fs.filename;
} // Comparison function
} FS;
typedef list<FS> ScoreLocate; // Final list of scores, will be sorted