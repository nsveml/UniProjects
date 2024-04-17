Triangle::Triangle(){
    name = "Triangle";
    n=3;
    coords = new float [2*n];
    for(long unsigned int i = 0; i<2*n; i++){
        coords[i]=0.0;
    }
}

Triangle::Triangle(std::istream& is){
    name = "Triangle";
    n=3;
    coords = new float[2*n];
    for(long unsigned int i=0; i<2*n; i++){
        is>>coords[i];
    }
}