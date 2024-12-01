
Figure::Figure(){
    n=0;
    coords=nullptr;
}

Figure::Figure(int a, std::istream& is){
    n=a;
    coords = new float [2*n];
    for(long unsigned int i = 0; i<2*n; i++){
        is >> coords[i];
    }
}

Figure::Figure(const Figure& other){
    n = other.n;
    coords = new float[2*n];
    for(long unsigned int i = 0; i < 2*n; i++){
        coords[i] = other.coords[i];
    }
}


Figure& Figure::operator=(const Figure& other){
    n = other.n;
    coords = new float[2*n];
    for(long unsigned int i = 0; i < 2*n; i++){
        coords[i] = other.coords[i];
    }
    return *this;
}

bool Figure::operator==(const Figure& other){
    size_t i = 0;
    while((i<2*n)&&(coords[i] == other.coords[i])) i++;
    return i==2*n-1;
}

Figure::~Figure(){
    delete [] coords;
}

size_t Figure::VertexesNumber(){
    return n;
}

float Figure::Area() const{
    float area = 0;
    for(long unsigned int i=0; i<2*n; i++){
        area += (i % 2) ? -coords[i]*coords[(i+1) % (2*n)] : coords[i]*coords[(i+3) % (2*n)];
    }
    area/=2;
    return (area<0)? -area : area;
}

void Figure::Print(std::ostream& os){
    os<<name<<":";
    for(long unsigned int i = 0; i<2*n; i+=2){
        os<<" ("<<coords[i]<<", "<<coords[i+1]<<')';
    }
    os<<'\n';
}

std::ostream& operator<<(std::ostream& os, const Figure& figure){
    os<<figure.name<<":";
    for(long unsigned int i = 0; i<2*figure.n; i+=2){
        os<<" ("<<figure.coords[i]<<", "<<figure.coords[i+1]<<')';
    }
    os<<'\n';
    return os;
}

std::istream& operator>>(std::istream& is, const Figure& figure){
    for(long unsigned int i = 0; i<2*figure.n; i++){
        is >> figure.coords[i];
    }
    return is;
}