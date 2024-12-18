-- MeuPrograma.hs
module Main where

soma_e_sub :: (Int, Int) -> (Int, Int)
soma_e_sub (a, b) = (a + b, a - b)

quadrados :: (Int, Int) -> (Int, Int)
quadrados (a, b) = (a*a + 2*a*b + b*b, a*a - 2*a*b + b * b)

dividir :: Int -> Int -> (Int, Int)
dividir x y = (x `div` y, x `mod` y)

f_currificada x y z w = x + y + z + w

type Peso = Float
type Idade = Int
type Nome = String
type Esporte = String
type Pessoa = (Nome, Idade, Peso, Esporte)
f_Joao :: Pessoa
f_Joao = ("Joao", 19, 75.78, "Basquete")

selec_nome :: Pessoa -> Nome
selec_idade :: Pessoa -> Idade
selec_peso :: Pessoa -> Peso
selec_esporte :: Pessoa -> Esporte

selec_nome (n, i, p, e) = n 
selec_idade (n, i, p, e) = i 
selec_peso (n, i, p, e) = p 
selec_esporte (n, i, p, e) = e

type Meu_tipo = (String, Float, Char)
pessoa :: Float -> Meu_tipo
pessoa rg
    | rg == 1 = ("Joao", 12, 'm')
    | rg == 2 = ("Jonas", 81, 'm')
    | rg == 3 = ("Joice", 21, 'f')
    | rg == 4 = ("Janete", 55, 'f')
    | rg == 5 = ("Jocileide", 21, 'f')
    | rg == 6 = ("Jonathan", 8, 'm')
    | otherwise = ("Ninguem", 0, 'x')

idade (n1, i1, g1) = i1
genero (n1, i1, g1) = g1

menor (n1, i1, g1) (n2, i2, g2)
    | i1 <= i2 = (n1, i1, g1)
    | otherwise =  (n2, i2, g2)

menor_idade :: Float -> Meu_tipo
menor_idade x
    | x == 1 = pessoa 1
    | otherwise = menor (pessoa x) (menor_idade(x-1))

media_idade :: Float -> Float
media_idade x = (soma_idade x)/x

ordena_par :: (Int, Int) -> (Int, Int)
ordena_par (a, b)
    | a >= b = (b, a)
    | otherwise = (a, b)

ordena_quatro :: (Int, Int, Int, Int) -> (Int, Int, Int, Int)
ordena_quatro (a, b, c, d) = 
    let 
        (m1, m2) = ordena_par (a, b)
        (m3, m4) = ordena_par (c, d)

        (n1, n2) = ordena_par (m1, m3)
        (n3, n4) = ordena_par (m2, m4)
        (n5, n6) = ordena_par (n2, n3)
    in (n1, n5, n6, n4) 

soma_idade x 
    | x == 1 = idade (pessoa 1)
    | otherwise = idade (pessoa x) + (soma_idade (x-1))

main :: IO ()
main = do
    putStrLn "Olá, mundo!"
