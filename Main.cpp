#include <iostream>
//#include "Ñoding.h"
#include"HuffmanAlgoritm.h"
using namespace std;

int main()
{
    string first = "YYy yYY YyY yy *";
    cout << first;
    CodeHuffman firstrCod = CodeHuffman(first);
    firstrCod.create();
    cout << endl;
    string second = "Chop your own wood and it will warm you twice. (Henry Ford)";
    cout << second;
    CodeHuffman secondCod = CodeHuffman(second);
    secondCod.create();
    cout << endl;
    string third = "Wise men speak because they have something to say; fools because they have to say something. (Plato)";
    cout << third;
    CodeHuffman thirdCod = CodeHuffman(third);
    thirdCod.create();
}
