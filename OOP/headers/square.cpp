Square::Square(){
    name = "Square";
    n=4;
    coords = new float [2*n];
    for(long unsigned int i = 0; i<2*n; i++){
        coords[i]=0.0;
    }
}

Square::Square(std::istream& is){
    name = "Square";
    n=4;
    coords = new float[2*n];
    for(long unsigned int i=0; i<2*n; i++){
        is>>coords[i];
    }
}