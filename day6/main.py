LIGTH_GRID_SIZE = 1000


def apply(grid, op, selection):
    sr, sc = selection[0]
    er, ec = selection[1]
    for i in range(sr, er + 1):
        for j in range(sc, ec + 1):
            if op == 'toggle':
                grid[i][j] = not grid[i][j]
            elif op == 'turn on':
                grid[i][j] = True
            else:  # 'turn off'
                grid[i][j] = False


def apply2(grid, op, selection):
    sr, sc = selection[0]
    er, ec = selection[1]
    for i in range(sr, er + 1):
        for j in range(sc, ec + 1):
            if op == 'toggle':
                grid[i][j] += 2
            elif op == 'turn on':
                grid[i][j] += 1
            else:  # 'turn off'
                grid[i][j] = max(0, grid[i][j] - 1)


def get_vect2d(s):
    return tuple(map(int, s.split(',')))


def count_grid(grid):
    return sum(sum(row) for row in grid)


def read_instruction(line):
    parts = line.split()
    if parts[0] == 'toggle':
        op = 'toggle'
        start = get_vect2d(parts[1])
        end = get_vect2d(parts[3])
    else:
        op = ' '.join(parts[:2])  # 'turn on' or 'turn off'
        start = get_vect2d(parts[2])
        end = get_vect2d(parts[4])
    return op, [start, end]


if __name__ == '__main__':
    ligth_grid = [[False for _ in range(LIGTH_GRID_SIZE)] for _ in range(LIGTH_GRID_SIZE)]
    ligth_grid2 = [[0 for _ in range(LIGTH_GRID_SIZE)] for _ in range(LIGTH_GRID_SIZE)]

    with open('input.txt') as f:
        for line in f:
            op, selection = read_instruction(line.strip())
            apply(ligth_grid, op, selection)
            apply2(ligth_grid2, op, selection)

    lcount = count_grid(ligth_grid)
    lsum = count_grid(ligth_grid2)

    print("Part 1:")
    print("    Lights on:", lcount)
    print("Part 2:")
    print("    Total brightness:", lsum)
