#include <iostream>
#include <string>
#include <vector>
#include <msgpack.hpp>

using namespace std;
using namespace msgpack;

int main()
{
    vector<unsigned char> data;
    for (unsigned i = 0; i < 10; ++i)
        data.push_back(i * 2);
    cout << "The size of array 'data' is: "<<sizeof(data)<<endl;
    sbuffer sbuf;
    pack(sbuf, data);
    cout << "The size of packed is: " << sbuf.size() <<endl;
    unpacked msg;
    unpack(&msg, sbuf.data(), sbuf.size());

    object obj = msg.get();
    cout<<"The size of unpacked object is: "<<sizeof(obj)<<endl;
    cout << obj << endl;
}
