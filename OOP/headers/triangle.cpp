
Triangle::Triangle(){
    name = "Triangle";
    n=3;
    coords = new float [2*n];
    for(long unsigned int i = 0; i<2*n; i++){
        coords[i]=0.0;
    }
}

Triangle& Triangle::operator=(const Triangle& other){
    for(long unsigned int i = 0; i < 2*n; i++){
        coords[i] = other.coords[i];
    }
    return *this;
}

bool Triangle::operator==(const Triangle& other){
    size_t i = 0;
    while((i<2*n)&&(coords[i] == other.coords[i])) i++;
    return i==2*n-1;
}
