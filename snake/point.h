#ifndef SNAKE_POINT_H
#define SNAKE_POINT_H


struct point {
    int x;
    int y;

    point()
        : x(0),
          y(0) { }

    point(int x, int y)
        : x(x),
          y(y) { }

    bool operator==(const point &other) const;
};

inline bool point::operator==(const point &other) const {
    return x == other.x && y == other.y;
}


#endif // SNAKE_POINT_H
