-- MeuPrograma.hs
module Main where

soma :: Int -> Int
soma 1 = 1
soma x = x + soma (x-1)

fat :: Int -> Int
fat 0 = 1
fat x = x * fat (x - 1)

fib :: Int -> Int
fib 0 = 1
fib 1 = 1
fib x = fib(x - 1) + fib(x - 2)

defT :: Int -> Int -> Int -> Int
defT x1 x2 x3
    | x1 == x2 && x1 == x3 = 1
    | x1 /= x2 && x1 /= x3 && x2 /= x3 = 3
    | otherwise = 2

maior3 :: Int -> Int -> Int -> Int
maior3 a b c
    | a > b && a > c = a
    | b > a && b > c = b
    | otherwise = c


d_AB :: Float -> Float -> Float -> Float -> Float
d_AB x1 y1 x2 y2 
    | x1 == x2 = abs (y2 - y1)
    | y1 == y2 = abs (x2 - x1)
    | otherwise = sqrt((x2 - x1)^2 +(y2 - y1)^2)

main :: IO ()
main = do 
    putStrLn "Olá, mundo!"
