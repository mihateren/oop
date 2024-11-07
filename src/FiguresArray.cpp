#include "../include/FiguresArray.h"

FiguresArray::FiguresArray() : buf(nullptr), size_(0), cap(3){
    buf = new Figure*[cap];
    for (int i = 0; i < cap; i++) {
        buf[i] = nullptr;
    }
}


void FiguresArray::resize(int new_size) {
    Figure** tmp = new Figure*[new_size];
    for (int i = 0; i < new_size; i++) {
        tmp[i] = nullptr;
    }
    for (int i = 0; i < size_; i++) {
        tmp[i] = buf[i];
    }
    delete [] buf;
    buf = tmp;
    cap = new_size;
}

int FiguresArray::size() const{ 
    return size_;
}

void FiguresArray::push_back(Figure* val){
    if (size_ == cap) {
        resize(cap + 1);
    }
    buf[size_] = val;
    size_++;
}

Figure* & FiguresArray::operator[](int idx){
    return buf[idx];
}

void FiguresArray::remove(int idx){
    if (idx < 0 || idx > size_) {
        throw std::invalid_argument("Index out of range");
    }

    Figure** new_buf = new Figure*[cap];

    for (int i = 0; i < idx; i++) {
        new_buf[i] = buf[i];
    }
    for (int i = idx; i < size_ - 1; i++) {
        new_buf[i] = buf[i + 1];
    }

    delete [] buf;
    buf = new_buf;
    size_--;
}

double FiguresArray::totalSquare() const {
    double total = 0.0;
    for (int i = 0; i < size_; i++) {
        if (buf[i] != nullptr) {
            total += buf[i]->square();
        }
    }
    return total;
}

FiguresArray::~FiguresArray(){
    size_ = 0;
    cap = 0;
    delete [] buf;
    buf = nullptr;
}