
module Main where

import Control.Monad

denom :: Int
denom = 100

vertexes :: Int -> [(Float, Float, Float)]
vertexes denom = [(sin r2 * cos r1, cos r2 * cos r1, 0.5 * sin r1) |
    m <- [-denom..denom], n <- [0..4*denom-1],
    let r1 = fromIntegral m*(pi/2/fromIntegral denom),
    let r2 = fromIntegral n*(pi/2/fromIntegral denom)]

faces :: Int -> [(Int, Int, Int)]
faces denom =
    [f | m <- [0..2*denom-1], n <- [0..4*denom-1],
         let n' = succ n `mod` (4*denom),
         let a = 4*m*denom+n,
         let b = 4*m*denom+n',
         let c = 4*succ m*denom+n,
         let d = 4*succ m*denom+n',
         f <- [(a, c, b), (d, b, c)]]

main :: IO ()
main = do
    forM_ (vertexes 20) $ \(x, y, z) ->
        putStrLn $ "v " ++ unwords (map (show . floor . (1000 *)) [x, y, z])
    forM_ (faces 20) $ \(a, b, c) ->
        putStrLn $ "f " ++ unwords (map (show . succ) [a, b, c])
