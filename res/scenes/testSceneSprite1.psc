type=Node
name=TestScene
children_start
type=Sprite
name=background
position=0.000000,0.000000
rotation=0.000000
scale=1.000000,1.000000
pivot=0.500000,0.500000
width=1920.000000
height=1080.000000
zIndex=0.000000
imagePath=res/textures/abstract_stairs.png
children_start
children_end

type=Sprite
name=testSprite1
position=0.000000,0.000000
rotation=0.000000
scale=1.000000,1.000000
pivot=0.500000,0.500000
width=100.000000
height=100.000000
zIndex=0.000000
imagePath=res/textures/TestTexture.png
children_start
children_end

type=Sprite
name=testSprite2
position=200.000000,200.000000
rotation=0.000000
scale=1.000000,1.000000
pivot=0.500000,0.500000
width=100.000000
height=100.000000
zIndex=1.000000
imagePath=res/textures/TestTexture.png
children_start
children_end

type=ActorCamera2D
name=Player camera
position=0.000000,-100.000000
rotation=0.000000
scale=1.000000,1.000000
pivot=0.500000,0.500000
zNear=-1.000000
zFar=1.000000
zoom=1.000000
target=testSprite1
initialOffset=0.000000,-100.000000
stiffness=0.010000
children_start
children_end

children_end
