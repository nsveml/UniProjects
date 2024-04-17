Figure::Figure(){
    n=0;
    coords=nullptr;
}

Figure::Figure(int a){
    n=a;
    coords = new float [2*n];
    std::cout<<"Enter coordinates in clockwise order:\n";
    for(long unsigned int i = 0; i<2*n; i++){
        std::cin>>coords[i];
    }
}

Figure::~Figure(){
    delete [] coords;
}

size_t Figure::VertexesNumber(){
    return n;
}

float Figure::Area(){
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