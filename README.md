# Space Invaders

## Context 
As part of my education at Isart Digital Montreal, we studied the C programming language for one month. By the end, we were required to reproduce the famous 1978 [Space Invaders](https://www.youtube.com/watch?v=axlx3o0codc&t=1s). The deadline was 4 days.

## Specifications
* Use C programming language
* Use the [SDL2](https://www.libsdl.org/download-2.0.php) library for display.
* The player should able to move his ship withing the screen limits.
* The player should be able to shoot projectiles.
* The player may only have one projectile at a time.
* If a player projectile hits an enemy, that enemy dies.
* Enemies bounce on screen edges and then go dowwn.
* If an enemy reaches the bottom, the player loses.
* Enemies may shoot at random if there is no enemy in front of them.
* If the player is hit 3 times, the game ends

## Techinal specifications
The main project was initialy developed on Linux (since we spent the first month on Linux only). I have proted this project over to windows using Visual Studio.
To run the game:
* Download the project.
* Open the SpaceInvaders.sln file.
* Change architecture from x64 to x32.
* Run and enjoy.

## Key take aways
* Having to work with a new librarby under the preasure of a tight deadline.
* Implementation of simple collision detection.
* Triggering random events.
* Applying previous notions of the C programming language I have learned into a game is really cool.

## What could be improved:
Since the project was constrained with a tight deadline, I have adopted an agile incremental software methodology prioritazing core gameplay features. However, the game could use some improuvements:
* Menu Screen.
* Text Displaying score.
* Enemies only shift down a row if a top alive enemy hit the wall.
* Obstacles like the original Space Invaders.
* Shiled power up for the player.
* 
## Contact
If you have any questions please feel free to contact me on s.raouf@student.isartdigital.com
