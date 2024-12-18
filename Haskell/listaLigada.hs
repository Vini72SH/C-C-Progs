-- listaLigada.hs
module Main where

data Lista a = Vazia
    | No a (Lista a)
    deriving (Show, Eq)

inserir :: a -> Lista a -> Lista a 
inserir x lista = No x lista

remover :: Lista a -> Lista a 
remover Vazia = Vazia
remover (No _ resto) = resto

imprimir :: Lista a -> [a]
imprimir Vazia = []
imprimir (No x resto) = x : imprimir resto 

main :: IO ()
main = do
    putStrLn "Olá, mundo!"