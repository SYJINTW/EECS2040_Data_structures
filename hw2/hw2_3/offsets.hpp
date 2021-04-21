#ifndef offsets_hpp
#define offsets_hpp

using namespace::std;

class offsets {
public:
    int a, b;
};
enum directions { N, NE, E, SE, S, SW, W, NW};

offsets movearray[8];

void setmovearray() {
    movearray[N].a = -1;
    movearray[N].b = 0;
    movearray[NE].a = -1;
    movearray[NE].b = 1;
    movearray[E].a = 0;
    movearray[E].b = 1;
    movearray[SE].a = 1;
    movearray[SE].b = 1;
    movearray[S].a = 1;
    movearray[S].b = 0;
    movearray[SW].a = 1;
    movearray[SW].b = -1;
    movearray[W].a = 0;
    movearray[W].b = -1;
    movearray[NW].a = -1;
    movearray[NW].b = -1;
}

#endif
