-- HaskellTypes.hs
module Main where

type Ponto = (Int, Int)
type Lista_Pontos = [Ponto]

data Cor = Verde | Azul | Amarelo
    deriving (Eq, Show)

corBasica :: Cor -> Bool
corBasica c = (c == Verde || c == Azul || c == Amarelo)

main :: IO ()
main = do
    putStrLn "Olá, mundo!"