#ifndef Items_hpp
#define Items_hpp

using namespace::std;

struct Items {
    int x, y, dir;
    Items() {};
    Items(const int& x, const int& y, const int& dir): x{x}, y{y}, dir{dir} {}
    ~Items() {}
    friend ostream& operator <<(ostream& out, Items& item)
    {
        out << "(" << item.x << "," << item.y << ") ";
        switch (item.dir) {
            case 1:
                out << "go N to ";
                break;
            case 2:
                out << "go NE to ";
                break;
            case 3:
                out << "go E to ";
                break;
            case 4:
                out << "go SE to ";
                break;
            case 5:
                out << "go S to ";
                break;
            case 6:
                out << "go SW to ";
                break;
            case 7:
                out << "go W to ";
                break;
            case 8:
                out << "go NW to ";
                break;
            default:
                break;
        }
        return out;
    }
};

#endif
