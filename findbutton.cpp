#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <map>

using namespace std;

int findButton(const string& fileName);

int main (int argc, char* argv[])
{
    int retVal;
    if ( argc != 2 )
    {
        cerr << "[usage] " << argv[0] << " fileName" << endl;
        return 0;
    }

    const string fileName(argv[1]);

    retVal = findButton(fileName);
    cout << retVal << endl;

    return 0;
}


/*
 * 1. 문제: 주어진 tile에서 각 꼭지점에 같은 문자을 찾아 가장 큰 직사각형을 만들어 넓이를 구한다.
 * 2. 분석: x,y : j, i 축으로 각각 point에서 검색.(순회)
 *              x축에서 같은 문자를 먼거리에서 가까운 순으로 찾고, y축에 같은 문자가 있으면 넓이를 구하고 큰 값보다 크면 저장.
 *              y축에서 같은 문자를 먼거리에서 가까운 순으로 찾고, x축에 같은 문자가 있으면 넓이를 구하고 큰 값보다 크면 저장.
 *
 *          중간에  만약 구해진 넓이가 남은 넓이 보다 크면 구해진 넓이가 가장 크므로 검색을 중단한다.
 * 3. 방법:
          1. 검색이 용이 하기 (back search을 용이 하기 위해 ), 확장성을 위해 .
             데이터 구조를 x, y를 각각 문자열의 vector로 만든다.
             데이터 구조를 x,y 을 각각 vector of vector로 x,y로 열로 만들수 있으나,
                가독성으로 vector of string을 선택.
 *
 *
 *
 */

#define __DEBUG__

int findButton(const string& fileName)
{
    // data
    vector<string> xVec, yVec;
#ifdef __DEBUG__
    map<string,int> gResult;
#endif

    // output
    int maxVal(0);


    // input
    ifstream in;
    in.open(fileName, ifstream::in);

    if(in.is_open() == false ) {
        cerr << "Could not open: " << fileName << endl;
        return 0;
    }

    string line;
    size_t maxLen(0);
    while ( getline(in,line) ) {

        if (line.length() == 0 ) continue;  // Hoxy,and then last

        if ( maxLen < line.length() ) { // xVec size assign.
            maxLen = line.length();
            xVec.resize(maxLen);
        }

        // y insert
        yVec.push_back(line);

        // x insert
        for ( size_t i = 0 ; i < line.length(); i ++ )
        {
            string ch = " ";
            ch = line.at(i);
            xVec[i].append(ch);
        }
        line.erase(line.begin(),line.end());
    }
    // calc
    bool isMax(false);

    for ( size_t i = 0 ; i < yVec.size() ; i ++ ) {
        for ( size_t j = 0 ; j < yVec[i].length(); j ++ ) {
            size_t x = yVec[i].rfind(yVec[i].at(j));
            size_t y = xVec[j].rfind(yVec[i].at(j));

            // is Max Area...
            if ( maxVal > ((yVec[i].length()) * ( xVec[j].length() - i)) )  {
#ifdef __DEBUG__
                cout << maxVal << "("<< j << "," << i << ")=(" << yVec[i].length() << ", " << xVec[j].length()-i << ")" << endl;
#endif
                isMax = true;
                break;
            }

            if ( j == x || i == y ) {// itself
                continue;
            }
            else {
                while ( j != x ) {

                    if( yVec[i].at(j) == yVec[y].at(x) ) {

                        string ch = " ";
                        ch = yVec[i].at(j);
#ifdef __DEBUG__
                        if ( gResult[ch] < (x-j+1)*(y-i+1) && ((x-j) != (y-i))) { gResult[ch] =  (x-j+1)*(y-i+1); }
#endif
                        if ( maxVal < (x-j+1)*(y-i+1) && ((x-j) != (y-i)) ) {
							maxVal = (x-j+1)*(y-i+1);
							break;
						}
                    }
                    x = yVec[i].rfind(yVec[i].at(j),x-1);
                    if( j == x ) break;
                }
            }

            x = yVec[i].rfind(yVec[i].at(j));

            if ( i == y ) { continue; }
            else {
                while ( i != y) {
                    if ( xVec[j].at(i) == xVec[x].at(y) ) {
                        string ch = " ";
                        ch = xVec[j].at(i);
#ifdef __DEBUG__
                        if ( gResult[ch] < (x-j+1)*(y-i+1) && ((x-j) != (y-i))) gResult[ch] =  (x-j+1)*(y-i+1);
#endif
                        if ( maxVal < (x-j+1)*(y-i+1) && ((x-j) != (y-i)) ) { 
							maxVal = (x-j+1)*(y-i+1);
							break;
						}
                    }
                    y = xVec[j].rfind(yVec[i].at(j),y-1);
                    if( i == y ) break;
                }
            }

        }
        if ( isMax == true ) break;
    }

    // output
#ifdef __DEBUG__
    for ( map<string,int>::iterator it = gResult.begin(); it != gResult.end() ; it++ ) {
        cout << "[" << it->first << "]->" << it->second << " ";
    }
    cout << " maxVal = " << maxVal << endl;
#endif

    return maxVal;
}

