import random
from math import gcd

# Função para verificar se um número é primo
def is_prime(n):
    if n <= 1:
        return False
    if n <= 3:
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False
    i = 5
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i += 6
    return True

# Função para encontrar o inverso modular usando o Algoritmo de Euclides Estendido
def modinv(a, m):
    m0, x0, x1 = m, 0, 1
    while a > 1:
        q = a // m
        a, m = m, a % m
        x0, x1 = x1 - q * x0, x0
    return x1 + m0 if x1 < 0 else x1

# Função para gerar dois números primos grandes diferentes
def generate_prime_pair(min_value=100, max_value=300):
    while True:
        p = random.randint(min_value, max_value)
        q = random.randint(min_value, max_value)
        if is_prime(p) and is_prime(q) and p != q:
            return p, q

# Geração das chaves RSA
def generate_rsa_keys():
    p, q = generate_prime_pair()
    n = p * q
    phi_n = (p - 1) * (q - 1)

    # Escolher e tal que 1 < e < phi_n e mdc(e, phi_n) = 1
    e = random.randrange(2, phi_n)
    while gcd(e, phi_n) != 1:
        e = random.randrange(2, phi_n)

    # Calcular d, o inverso modular de e módulo phi_n
    d = modinv(e, phi_n)

    public_key = (e, n)
    private_key = (d, n)

    print(f"Primos escolhidos: p = {p}, q = {q}")
    print(f"Chave pública: {public_key}")
    print(f"Chave privada: {private_key}")
    return public_key, private_key

# Função para criptografar uma mensagem
def encrypt(message, public_key):
    e, n = public_key
    cipher = [pow(ord(char), e, n) for char in message]
    return cipher

# Função para descriptografar uma mensagem
def decrypt(cipher, private_key):
    d, n = private_key
    decrypted = [chr(pow(char, d, n)) for char in cipher]
    return ''.join(decrypted)

# Exemplo de uso
if __name__ == "__main__":
    public_key, private_key = generate_rsa_keys()

    mensagem = input("Digite a mensagem para criptografar: ")
    criptografada = encrypt(mensagem, public_key)
    print(f"Mensagem criptografada: {criptografada}")

    descriptografada = decrypt(criptografada, private_key)
    print(f"Mensagem descriptografada: {descriptografada}")
