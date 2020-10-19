#include "data.h"

Data::Data():channel(0), count(0){

}

Data::Data(const int &ch, const int &co):channel(ch), count(co){

}

int Data::getChannel(){
    return channel;
}

int Data::getCount(){
    return count;
}

void Data::setChannel(const int &ch){
    channel = ch;
}
void Data::setCount(const int &co){
    count = co;
}
