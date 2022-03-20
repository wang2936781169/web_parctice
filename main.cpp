#include <iostream>
#include <string>

#include <socket.hpp>
#include "template.hpp"

using namespace std;
const int PORT = 9000;
const int OPEN_MAX = 1024;

class test : public Instance<test>
{
public:
    int a = 1;

};

int main(int argc, char** argv)
{
    const test &t = test::get();
    cout << t.a << endl;

    return 0;
}