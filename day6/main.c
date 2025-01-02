#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


#define LIGTH_GRID_SIZE 1000
#define INST_LINE_BUFFER_SIZE 50

#define OP_TOOGLE "toggle"
#define OP_TOOGLE_L (sizeof(OP_TOOGLE) - 1)

#define OP_TURNON "turn on"
#define OP_TURNON_L (sizeof(OP_TURNON) - 1)

#define OP_TURNOFF "turn off"
#define OP_TURNOFF_L (sizeof(OP_TURNOFF) - 1)


typedef struct Vect2d_def {
    int32_t x;
    int32_t y;
} Vect2d;

typedef struct Range_def {
    Vect2d start;
    Vect2d end;
} Range;


typedef enum InstOp_def {
    TURN_ON,
    TURN_OFF,
    TOOGLE
} InstOp;

typedef struct Inst_def {
    InstOp op;
    Range selection;
} Inst;


const char* extract_operation_from_line(const char* buf, InstOp* op){
    if (strstr(buf, OP_TOOGLE)){
        *op = TOOGLE;
        return buf + OP_TOOGLE_L;
    } else if (strstr(buf, OP_TURNON)){
        *op = TURN_ON;
        return buf + OP_TURNON_L;
    } else if (strstr(buf, OP_TURNOFF)){
        *op = TURN_OFF;
        return buf + OP_TURNOFF_L;
    } else {
        return NULL;
    }
}

const char* extract_number_from_line(const char* buf, int32_t* out){
    char nbuf[6];
    size_t i;
    for (i=0; i<5; ++i){
        if (!isdigit(buf[i])){
            nbuf[i] = '\0';
            break;
        }
        nbuf[i] = buf[i];
    }

    if (i==0){
        return NULL;
    }

    *out = atoi(nbuf);
    return buf + i;
}

const char* extract_vect2d_from_line(const char* buf, Vect2d* out){
    const char* next_part = extract_number_from_line(buf, &out->x);
    next_part++; //pass the ,
    next_part = extract_number_from_line(next_part, &out->y);
    return next_part;
}

bool extract_range_from_line(const char* buf, Range* selection){
    Vect2d start;
    Vect2d end;
    const char* next_part = extract_vect2d_from_line(buf, &start);
    
    //shift " through " keyword
    next_part = next_part + sizeof("through") + 1;
    extract_vect2d_from_line(next_part, &end);
    *selection = (Range){start, end};
    return true;
}

bool get_next_inst(FILE* f, Inst* inst){
    if (feof(f)){
        return false;
    }

    char line_buf[INST_LINE_BUFFER_SIZE];
    const char* next_part;
    if (!fgets(line_buf, INST_LINE_BUFFER_SIZE, f)){
        printf("ERROR READING FILE\n");
        return false;//exit(1); //Memory leaks at least the OS free all resources
    }
    
    if (!(next_part = extract_operation_from_line(line_buf, &inst->op))){
        printf("ERROR READING THE OPERATION\n");
        exit(1);
    }

    next_part++; //consume empty space
    if (!extract_range_from_line(next_part, &inst->selection)){
        printf("ERROR READING THE RANGE");
        exit(1);
    }
    return true;
}

bool process_new_state(bool cstate, InstOp op){
    if (op == TURN_ON){
        return true;
    }else if(op == TURN_OFF){
        return false;
    }else{
        return !cstate;
    }
}

int32_t process_new_state2(int32_t cstate, InstOp op){
    if (op == TURN_ON){
        return cstate + 1;
    }else if(op == TURN_OFF){
        int32_t nstate = cstate - 1;
        if (nstate < 0){
            nstate = 0;
        }
        return nstate;
    }else{
        return cstate + 2;
    }
}

void apply_inst_to_grid(Inst* inst, bool grid[LIGTH_GRID_SIZE][LIGTH_GRID_SIZE]){
    Vect2d start = inst->selection.start;
    Vect2d end = inst->selection.end;
    for (size_t i = start.y; i <= (size_t)end.y; ++i){
        for (size_t j = start.x; j <= (size_t)end.x; ++j){
            bool cstate = grid[i][j];
            grid[i][j] = process_new_state(cstate, inst->op);
        }
    }
}

void apply_inst_to_grid2(Inst* inst, int32_t* grid){
    Vect2d start = inst->selection.start;
    Vect2d end = inst->selection.end;
    for (size_t i = start.y; i <= (size_t)end.y; ++i){
        for (size_t j = start.x; j <= (size_t)end.x; ++j){
            int32_t cstate = grid[(i * LIGTH_GRID_SIZE) + j];
            grid[(i * LIGTH_GRID_SIZE) + j] = process_new_state2(cstate, inst->op);
        }
    }
}

size_t count_ligths_on(bool grid[LIGTH_GRID_SIZE][LIGTH_GRID_SIZE]){
    size_t count = 0;
    bool* endit = &grid[LIGTH_GRID_SIZE-1][LIGTH_GRID_SIZE];
    bool* it = &grid[0][0];
    for (;it < endit; ++it){
        if (*it == true){
            count++;
        }
    }
    return count;
}

void print_inst(Inst* inst){
    const char* opstr;
    switch (inst->op){
        case TOOGLE:
            opstr = "toggle";
            break;
        case TURN_OFF:
            opstr = "turn off";
            break;
        case TURN_ON:
            opstr = "turn on";
            break;
    }
    int32_t sx = inst->selection.start.x;
    int32_t sy = inst->selection.start.y;
    int32_t ex = inst->selection.end.x;
    int32_t ey = inst->selection.end.y;

    printf("%s %d,%d through %d,%d\n", opstr, sx, sy, ex, ey);
}

int32_t count_ligths_brigth(int32_t* grid){
    int32_t count = 0;
    int32_t* endit = &grid[LIGTH_GRID_SIZE*LIGTH_GRID_SIZE];
    int32_t* it = grid;
    for (;it < endit; ++it){
        count += *it;
    }
    return count;
}


int main() {
    FILE* input = fopen("input.txt", "rb");
    bool ligth_grid[LIGTH_GRID_SIZE][LIGTH_GRID_SIZE] = {0};
    int32_t* ligth_grid2 = malloc(sizeof(int32_t) * LIGTH_GRID_SIZE * LIGTH_GRID_SIZE);

    Inst cinst;
    while (get_next_inst(input, &cinst)){
        apply_inst_to_grid(&cinst, ligth_grid);
        apply_inst_to_grid2(&cinst, ligth_grid2);
        //print_inst(&cinst);
    }

    size_t ligths_on = count_ligths_on(ligth_grid);
    size_t total_brigth = count_ligths_brigth(ligth_grid2);

    printf("Part1:\n");
    printf("    ligths on:%ld\n", ligths_on);
    printf("Part2:\n");
    printf("    total brigth:%ld\n", total_brigth);

    free(ligth_grid2);
    fclose(input);
    return 0;
}
