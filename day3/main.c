#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "sow_std.h"


typedef struct Point2d_def {
    int32_t x;
    int32_t y;
} Point2d;

bool Point2d_is_equal(Point2d lhs, Point2d rhs){
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

Point2d move_santa(Point2d cp, char dir){
    int32_t xd = 0;
    int32_t yd = 0;

    if (dir == '>'){
        xd = 1;
    }
    else if(dir == '^'){
        yd = 1;
    }
    else if(dir == '<'){
        xd = -1;
    }
    else if(dir == 'v'){
        yd = -1;
    }

    Point2d new;
    new.x = cp.x + xd;
    new.y = cp.y + yd;

    return new;
}

int main1(void) {
    const char* input = S_file_get_content_by_filename("input.txt");

    Point2d SantaLoc = {0, 0};
    SVector SantaLocVisited;
    SVector_init(&SantaLocVisited, sizeof(Point2d), 2);

    SVector_push(&SantaLocVisited, &SantaLoc);

    size_t l = strlen(input);

    for(size_t i = 0; i < l; ++i){
        char c = input[i];
        SantaLoc = move_santa(SantaLoc, c);
        
        bool is_already_visited = false;
        for (size_t j = 0; j < SantaLocVisited.count; ++j){
            Point2d sc = ((Point2d*)SantaLocVisited.data)[j];
            if (Point2d_is_equal(SantaLoc, sc)){
                is_already_visited = true;
                break;
            }
        }

        if (!is_already_visited) {
            SVector_push(&SantaLocVisited, &SantaLoc);
        }
    }

    printf("Houses that received at least one gift: %ld\n", SantaLocVisited.count);

    return 0;
}

int main2(void){
    const char* input = S_file_get_content_by_filename("input.txt");

    Point2d SantaLoc = {0, 0};
    Point2d rsl = {0, 0};
    Point2d* cpoint = &SantaLoc;
    SVector SantaLocVisited;
    SVector_init(&SantaLocVisited, sizeof(Point2d), 2);

    SVector_push(&SantaLocVisited, &SantaLoc);

    size_t l = strlen(input);

    for(size_t i = 0; i < l; ++i){
        char c = input[i];
        *cpoint = move_santa(*cpoint, c);
        
        bool is_already_visited = false;
        for (size_t j = 0; j < SantaLocVisited.count; ++j){
            Point2d sc = ((Point2d*)SantaLocVisited.data)[j];
            if (Point2d_is_equal(*cpoint, sc)){
                is_already_visited = true;
                break;
            }
        }

        if (!is_already_visited) {
            SVector_push(&SantaLocVisited, cpoint);
        }
        cpoint = (cpoint == &SantaLoc)? &rsl : &SantaLoc;
    }

    printf("Houses that received at least one gift: %ld\n", SantaLocVisited.count);

    return 0;
}

int main(void){
    main1();
    printf("------------------------------------\n");
    main2();
    return 0;
}
