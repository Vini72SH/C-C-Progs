
data ArvoreBin = NodoNull | NodoInt Int ArvoreBin ArvoreBin
    deriving Show

arvoreBin = NodoInt 4 (NodoInt 2 NodoNull NodoNull)
                      (NodoInt 10 (NodoInt 5 NodoNull NodoNull)
                                  (NodoInt 15 NodoNull NodoNull))

passeio :: ArvoreBin -> [Int]
passeio NodoNull = []
passeio (NodoInt a NodoNull NodoNull) = [a]
passeio (NodoInt a esq dir) = [a] ++ passeio esq ++ passeio dir

criaNodo :: Int -> ArvoreBin
criaNodo a = (NodoInt a NodoNull NodoNull)

insere :: Int -> ArvoreBin -> ArvoreBin
insere x NodoNull = criaNodo x
insere x (NodoInt a esq dir)
    | x > a = (NodoInt a esq (insere x dir))
    | x < a = (NodoInt a (insere x esq) dir)