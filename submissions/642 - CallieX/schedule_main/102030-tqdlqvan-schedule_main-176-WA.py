from collections import deque

T = int(input())

for _ in range(T):
    N, M, K = map(int, input().split())

    P = list(map(int, input().split()))

    grafo = [[] for _ in range(N + 1)]

    grau = [0] * (N + 1)

    for i in range(1, N + 1):
        if P[i - 1] != 0:
            grafo[P[i - 1]].append(i)
            grau[i] += 1

    disponiveis = []

    for i in range(1, N + 1):
        if grau[i] == 0:
            disponiveis.append(i)

    total = 0

    for semestre in range(M):

        proximas = []

        quantidade = min(K, len(disponiveis))

        cursadas = disponiveis[:quantidade]

        total += len(cursadas)

        for disciplina in cursadas:

            for dependente in grafo[disciplina]:
                grau[dependente] -= 1

                if grau[dependente] == 0:
                    proximas.append(dependente)

        disponiveis = disponiveis[quantidade:] + proximas

    print(total)