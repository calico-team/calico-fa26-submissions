
# Online Python - IDE, Editor, Compiler, Interpreter
def calcular_xor(valores):
    resultado = 0

    for valor in valores:
        resultado ^= valor

    return resultado

def solve(L,R):
    valores = []
    for i in range(len(L)):
        melhor_valor = L[i]
        melhor_resultado = calcular_xor(valores + [L[i]])
        
        for valor in range(L[i], R[i] + 1):
            valores.append(valor)
            resultado_atual = calcular_xor(valores)
            valores.pop()
            if resultado_atual > melhor_resultado:
                melhor_resultado = resultado_atual
                melhor_valor = valor
        
        valores.append(melhor_valor)

    return calcular_xor(valores)
    

T = int(input())

for x in range(T):
    N = int(input())

    L = []
    R = []

    for value in input().split():
        L.append(int(value))

    for value in input().split():
        R.append(int(value))
        
    resultado = solve(L, R)

    print(resultado)

