-- listaTelefonica.hs
module Main where

type Nome = String
type Numero = Int
type Contato = (Nome, Numero)
type Lista_Contatos = [Contato]

buscaPorNome :: Nome -> Lista_Contatos -> Bool
buscaPorNome _ [] = False -- Lista vazia
buscaPorNome nome ((n, _):resto)
    | nome == n = True
    | otherwise = buscaPorNome nome resto

buscaPorNumero :: Numero -> Lista_Contatos -> Bool
buscaPorNumero _ [] = False
buscaPorNumero numero ((_, num):resto)
    | numero == num = True
    | otherwise = buscaPorNumero numero resto

main :: IO ()
main = do
    putStrLn "Olá, mundo!"