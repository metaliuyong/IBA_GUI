#include "data.h"

Data::Data():channel(0), count(0){

}

Data::Data(int ch, int co):channel(ch), count(co){

}

int Data::getChannel(){
    return channel;
}

int Data::getCount(){
    return count;
}

void Data::setChannel(int ch){
    channel = ch;
}
void Data::setCount(int co){
    count = co;
}
