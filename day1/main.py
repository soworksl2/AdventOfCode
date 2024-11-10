sinput = open('input.txt', 'r').read()

position = 0
cursor = 0
for c in sinput:
    cursor += 1
    if c == '(':
        position += 1
    elif c == ')':
        position -= 1
    if position == -1:
        print(cursor)

print(position)
