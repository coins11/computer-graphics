
module Main where

import Data.IORef
import Control.Monad
import Control.Applicative
import System.Random
import Graphics.UI.GLUT

vertex3f :: Vertex3 GLfloat -> IO ()
vertex3f = vertex

type ObjState = 
    (Color4 GLfloat, -- color
     (GLfloat, GLfloat), -- rotate
     (Vector3 GLfloat, Vector3 GLfloat)) -- translate

vec3add :: Num a => Vector3 a -> Vector3 a -> Vector3 a
vec3add (Vector3 a b c) (Vector3 a' b' c') = Vector3 (a + a') (b + b') (c + c')

newObj :: IO ObjState
newObj = do
    let rand = randomRIO (0, 1)
        rand' = randomRIO (-0.01, 0.01)
    c <- liftM4 Color4 rand rand rand rand
    r <- liftM2 (,) (randomRIO (-30, 30)) (randomRIO (0, 360))
    t <- liftM2 (,)
        (liftM3 Vector3 rand' rand' rand')
        (liftM3 Vector3 rand rand rand)
    return (c, r, t)

step :: IORef [ObjState] -> IO ()
step state = do
    state' <- map (\(c, (r, r'), (t, t')) ->
        (c, (r, r + r'), (t, vec3add t t'))) <$> readIORef state
    case state' of
        [] -> writeIORef state []
        (_ : state') -> do
            obj <- newObj
            writeIORef state $ state' ++ [obj]

display :: IORef [ObjState] -> IO ()
display state = do
    clear [ColorBuffer]
    state' <- readIORef state
    forM_ state' $ \(c, (r, r'), (t, t')) -> preservingMatrix $ do
        color c
        translate t'
        rotate r' (Vector3 0 0 1)
        renderPrimitive Polygon $ mapM_ vertex3f
            [Vertex3 (-0.03) (-0.03) 0, Vertex3 0.03 (-0.03) 0,
             Vertex3 0.03 0.03 0, Vertex3 (-0.03) 0.03 0]
    flush

myInit :: IO ()
myInit = do
    clearColor $= Color4 0 0 0 0
    matrixMode $= Projection
    loadIdentity
    ortho 0 1 0 1 (-1) 1

makeTimer :: Int -> IO () -> IO ()
makeTimer time act = addTimerCallback time $ act >> makeTimer time act

main :: IO ()
main = do
    getArgsAndInitialize
    initialDisplayMode $= [ SingleBuffered, RGBMode ]
    initialWindowSize $= Size 250 250
    initialWindowPosition $= Position 100 100
    createWindow "hello"
    myInit
    state <- replicateM 300 newObj >>= newIORef
    displayCallback $= display state
    makeTimer 50 (step state >> display state)
    mainLoop

