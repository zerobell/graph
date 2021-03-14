#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>

using namespace std;

vector<vector<char> > Vec;

int findArea(int x, int y,int key)
{
	char ch = Vec[y][x];
	printf("(%d,%d)[%c]\n",x,y,ch);

	int area = key;
	size_t length = Vec[0].size();
	size_t height = Vec.size();

	for ( int rx = (length - 1) ; rx > x; rx-- ) {
		for ( int ry = (height -1) ; ry > y; ry-- ) {

			if ((rx - x + 1) * (ry - y + 1) < area ) break; 
			if ((rx - x) == (ry-y)) break;
			if(Vec[ry][rx] == ch && Vec[ry][x] == ch && Vec[y][rx] == ch ) {
				printf("%c: %d,%d - %d,%d : %d", ch, x,y , rx,ry, (rx - x + 1) * (ry - y + 1));
				printf("(%d,%d)[%c] (%d,%d)[%c] (%d,%d)[%c]\n", ry,rx, Vec[ry][rx], ry,x, Vec[ry][x], y, rx, Vec[y][rx]);
				area = max(area, (rx - x + 1) * (ry - y + 1));
				break;
			}
		}
	}
	return area;
}

int findKey()
{
	int key(0);
	size_t length = Vec[0].size();
	size_t height = Vec.size();

	for ( int x = 0 ; x <  length ; x++ ){
		for ( int y = 0 ; y < height; y++ ) {
			if( (length - x + 1) * (  height - y + 1) < key ) break;
			key = max(findArea(x,y,key), key);
		}
	}
	return key;
}


int FindButtonImpl (const std::string& fileName)
{
    // input
    ifstream in;

    in.open(fileName, ifstream::in);

    if (in.is_open() == false) {
        cerr << "Could not open : " << fileName << endl;
        return 0;
    }

    string   line;
    while ( getline (in, line) ) {

        if (line.length() == 0 ) continue; // never event but sometime endline..

        vector<char> yItemVec;
        for ( size_t i = 0 ; i < line.length(); i ++ )
        {
            char ch = line.at(i);
            yItemVec.push_back(ch);
        }
        Vec.push_back(yItemVec);

        line.erase(line.begin(),line.end()); // erase init.
    }

    // print
    return findKey();
}

int main(int argc, char* argv[])
{
	int retVal; 
	if ( argc != 2 ) {
		cerr << "[usage] " << argv[0] << " fileName" << endl;
		return 0;
	}

	const string fileName(argv[1]);
           
	retVal = FindButtonImpl (fileName);

	cout << retVal << endl;

	return 0;
}
