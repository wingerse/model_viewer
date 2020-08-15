def det2(m, sign):
    if sign == 1:
        return f"{m[0][0]}*{m[1][1]} - {m[0][1]}*{m[1][0]}"
    else:
        return f"{m[0][1]}*{m[1][0]} - {m[0][0]}*{m[1][1]}"

def det3(m, sign):
    S_00 = [
        [m[1][1], m[1][2]],
        [m[2][1], m[2][2]],
    ]
    S_01 = [
        [m[1][0], m[1][2]],
        [m[2][0], m[2][2]],
    ]
    S_02 = [
        [m[1][0], m[1][1]],
        [m[2][0], m[2][1]],
    ]
    if sign == 1:
        return f"""{m[0][0]}*({det2(S_00, 1)}) + 
             {m[0][1]}*({det2(S_01, -1)}) + 
             {m[0][2]}*({det2(S_02, 1)})"""
    else:
        return f"""{m[0][0]}*({det2(S_00, -1)}) + 
             {m[0][1]}*({det2(S_01, 1)}) + 
             {m[0][2]}*({det2(S_02, -1)})"""

print("const mat4& m = *this;")
print()
for i in range(0, 4):
    for j in range(0, 4):
        S_ij = [[0]*3 for _ in range(3)]
        si = 0
        for ii in range(0, 4):
            if ii == i: continue
            sj = 0
            for jj in range(0, 4):
                if jj == j: continue
                S_ij[si][sj] = f"m[{ii}][{jj}]"
                sj += 1
            si += 1
        print(f"float S_{i}{j} = {det3(S_ij, (-1)**(i+j))};")

print()
print(f"float det = 1/(m[0][0]*S_00 + m[0][1]*S_01 + m[0][2]*S_02 + m[0][3]*S_03);")
print()
print("return {")
for i in range(0, 4):
    print("    ", end='')
    for j in range(0, 4):
        print(f"det*S_{j}{i}, ", end='')
    print()

print("};")
