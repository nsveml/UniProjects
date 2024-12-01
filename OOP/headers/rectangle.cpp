Rectangle::Rectangle(){
    name = "Rectangle";
    n=4;
    coords = new float [2*n];
    for(long unsigned int i = 0; i<2*n; i++){
        coords[i]=0.0;
    }
}

Rectangle::Rectangle(std::istream& is){
    name = "Rectangle";
    n=4;
    coords = new float[2*n];
    for(long unsigned int i=0; i<2*n; i++){
        is>>coords[i];
    }
}