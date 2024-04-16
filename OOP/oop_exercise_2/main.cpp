#include <iostream>

class TimePoint{
    public:
    
    int h,m,s;

    TimePoint(){
        h=0;
        m=0;
        s=0;
    }

    TimePoint(int a, int b, int c){
        h=a;
        m=b;
        s=c;
    }

    int seconds(){
        return (h*60+m)*60 + s;
    }

    int minutes(){
        return h*60+m;
    }

    TimePoint FromMinutes(int minutes){
        h=0;
        s=0;
        m=minutes;
        if(m>=60){
            h+=m/60;
            m%=60;
        }
        return *this;
    }

    TimePoint FromSeconds(int seconds){
        h=0;
        m=0;
        s=seconds;
        if(s>=60){
            m+=s/60;
            s%=60;}
        if(m>=60){
            h+=m/60;
            m%=60;
        }
        return *this;
    }

};

float HowMuchMore(TimePoint a, TimePoint b){
    float res = (float)a.seconds()/b.seconds();
    return res;
}

float HowMuchLess(TimePoint a, TimePoint b){
    float res = (float)b.seconds()/a.seconds();
    return res;
}

TimePoint operator +(TimePoint a, TimePoint b){
    TimePoint c;
    c.h=a.h+b.h;
    c.m=a.m+b.m;
    c.s=a.s+b.s;
    if(c.s>=60){
        c.m+=c.s/60;
        c.s%=60;}
    if(c.m>=60){
        c.h+=c.m/60;
        c.m%=60;}
    return c;
}

TimePoint operator +(TimePoint a, int seconds){
    TimePoint c;
    c.h=a.h;
    c.m=a.m;
    c.s=a.s + seconds;
    if(c.s>=60){
        c.m+=c.s/60;
        c.s%=60;}
    if(c.m>=60){
        c.h+=c.m/60;
        c.m%=60;}
    return c;
}

TimePoint operator -(TimePoint a, TimePoint b){
    TimePoint c;
    c.s = a.seconds()-b.seconds();
    if(c.s <= -60 || c.s >= 60){
        c.m = c.s/60;
        c.s = c.s%60;
    }
    if(c.m <= -60 || c.m >= 60){
        c.h = c.m/60;
        c.m = c.m%60;
    }
    if(c.s < 0){
        c.s = 0 - c.s;
    }
    if(c.m < 0){
        c.m = 0 - c.m;
    }
    return c;
}

TimePoint operator -(TimePoint a, int seconds){
    TimePoint c;
    c.s=a.seconds()-seconds;
    if(c.s <= -60 || c.s >= 60){
        c.m = c.s/60;
        c.s = c.s%60;
    }
    if(c.m <= -60 || c.m >= 60){
        c.h = c.m/60;
        c.m = c.m%60;
    }
    if(c.s < 0){
        c.s = 0 - c.s;
    }
    if(c.m < 0){
        c.m = 0 - c.m;
    }
    return c;
}

bool operator < (TimePoint a, TimePoint b){
    return a.seconds() < b.seconds();
}

bool operator > (TimePoint a, TimePoint b){
    return a.seconds() > b.seconds();
}

bool operator == (TimePoint a, TimePoint b){
    return a.seconds() == b.seconds();
}

TimePoint operator"" _tp(const char* a, size_t size){
    TimePoint c;
    int i=0, d=1, dif='0'-0;
    while(a[i]!=':'){
        c.h*=10;
        c.h+=a[i]-dif;
        i++;
    }
    d=1;
    i++;
    while(a[i]!=':'){
        c.m*=10;
        c.m+=a[i]-dif;
        i++;
    }
    d=1;
    i++;
    while(a[i]!='\0'){
        c.s*=10;
        c.s+=a[i]-dif;
        i++;
    }
    return c;
}

std::ostream& operator <<(std::ostream& out, const TimePoint &a){
    out<<a.h<<':'<<a.m<<':'<<a.s;
    return out;
}

std::istream& operator >>(std::istream &in, TimePoint &a){
    char c;
    in>>a.h>>c>>a.m>>c>>a.s;
    if(a.s>=60){
        a.m+=a.s/60;
        a.s%=60;
    }
    if(a.m>=60){
        a.h+=a.m/60;
        a.m%=60;
    }
    if(a.s>=60.){
        a.m+=a.s/60;
        a.s%=60;
    }
    if(a.m>=60){
        a.h+=a.m/60;
        a.m%=60;
    }
    if(a.s<0){
        a.m--;
        a.s+=60;
    }
    if(a.m<0){
        a.h--;
        a.m+=60;
    }
    return in;
}

int main(){
    TimePoint a, b;
    std::cout << "Enter two time points:" << std::endl;
    std::cin >> a >> b;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a - b = " << a - b << std::endl;
    std::cout << "a + 30 sec = " << a + 30 << std::endl;
    std::cout << "a - 30 sec = " << a - 30 << std::endl;
    std::cout << "\"1:15:30\" = " << "1:15:30"_tp << std::endl;
    std::cout << "How much a is more then b: " << HowMuchMore(a, b) << std::endl;
    std::cout << "How much b is less then a: " << HowMuchLess(b, a) << std::endl;
    std::cout << "a + 1:15:30 = " << a + "1:15:30"_tp << std::endl;
    std::cout << "a in seconds: " << a.seconds() << std::endl;
    std::cout << "a in minutes: " << a.minutes() << std::endl;
    std::cout << "a = 3600 seconds: " << a.FromSeconds(3600) << std::endl;
    std::cout << "a = 3600 minutes: " << a.FromMinutes(3600) << std::endl;
}