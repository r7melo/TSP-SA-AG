def ox_crossover(parent1, parent2, point1, point2):

    N = len(parent1)

    cut1 = int(point1*N)
    cut2 = int(point2*N)

    child = [None] * N
    child[cut1:cut2] = parent1[cut1:cut2]

    jump = 0
    for i in range(N):
        idx = (cut2 + i) % N

        if cut1 <= idx < cut2:
            continue

        element = None
        element_is_valid = False

        while not element_is_valid:
            idx_jump = (idx + jump) % N
            element = parent2[idx_jump]
            element_is_valid = True

            for j in range(cut1, cut2):
                if element == child[j]:
                    element_is_valid = False
                    jump += 1
                    break

        child[idx] = element

        
    return child


if __name__=="__main__":
        
    parent1 = [1, 2, 3, 4, 5, 6, 7, 8]
    parent2 = [8, 7, 6, 5, 4, 3, 2, 1]
    point1, point2 = 0.4, 0.8

    print(f"Pai 1: {parent1}")
    print(f"Pai 2: {parent2}\n")

    filho = ox_crossover(parent1, parent2, point1, point2)

    print(f"Filho OX: {filho}")