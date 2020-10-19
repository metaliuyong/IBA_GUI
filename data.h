#ifndef DATA_H
#define DATA_H

class Data
{
private:
    int channel;
    int count;
public:
    Data();
    Data(const int &ch, const int &co);
    int getChannel();
    int getCount();
    void setChannel(const int &ch);
    void setCount(const int &co);
};

#endif // DATA_H
