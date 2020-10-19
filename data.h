#ifndef DATA_H
#define DATA_H

class Data
{
private:
    int channel;
    int count;
public:
    Data();
    Data(int ch, int co);
    int getChannel();
    int getCount();
    void setChannel(int ch);
    void setCount(int co);
};

#endif // DATA_H
