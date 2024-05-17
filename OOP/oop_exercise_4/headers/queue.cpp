
// Конструктор по умолчанию
TQueue::TQueue(){
    size = 0;
    capacity = 1;
    storage = new Triangle[1];
}
// Конструктор копирования очереди.
TQueue::TQueue(const TQueue& other){
    size = other.size;
    capacity = other.capacity;
    storage = new Triangle[capacity];
    for(int i = 0; i < size; i++){
        storage[i]=other.storage[i];
    }
}

// Метод, добавляющий фигуру в конец очереди.
void TQueue::Push(const Triangle& polygon){
    if(capacity == size) extend();
    storage[size]=polygon;
    size++;
}
// Метод, убирающий первую фигуру из очереди.
const Triangle TQueue::Pop(){
    if(size > 0){
        size--;
        return(storage[size]);
    }
    else{
        return Triangle();
    }
}
// Метод, возвращающий ссылку на первую в очереди фигуру
const Triangle& TQueue::Top(){
    return storage[size-1];
}
// Метод, проверяющий пустоту очереди
bool TQueue::Empty(){
    return bool(size);
}
// Метод, возвращающий длину очереди
size_t TQueue::Length(){
    return size;
}
// Оператор вывода очереди в формате:
// "=> Sn Sn-1 ... S1 =>", где Si - площадь фигуры,
//  а n – номер последней фигуры в очереди
std::ostream& operator<<(std::ostream& os, const TQueue& queue){
    for(int i = 0; i < queue.size; i++){
        os << queue.storage[i].Area() << ' ';
    }
    os << "=>\n";
    return os;
}
// Метод, удаляющий все элементы контейнера,
// но позволяющий пользоваться им.
void TQueue::Clear(){
    size = 0;
    capacity = 1;
    delete [] storage;
    storage = new Triangle[1];
}
// Деструктор
TQueue::~TQueue(){
    delete [] storage;
}

void TQueue::extend(){
    Triangle* tmp;
    capacity*=2;
    tmp = new Triangle[capacity];
    for(int i = 0; i < size; i++){
      tmp[i]=storage[i];
    }
    delete [] storage;
    storage = tmp;
}