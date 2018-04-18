# Birds
A boids simulation written for Texas A&M University's CSCE 649 Physics Based Rendering class.

![Paper Planes](https://user-images.githubusercontent.com/5340992/38898428-96e1d634-425a-11e8-9db5-bc009f3dcf11.gif)

## What it does
This simulation spawns [boids](https://en.wikipedia.org/wiki/Boids), little paper airplanes that behave following a few simple rules. For this program, those rules are mostly unchanged from the traditional simple boids.

### Boids
In order to emulate the movement of flocks of birds, they steer rather than accelerate like normal particles. For the most part, this means that each boid's speed remains pretty close to constant. Behavior is defined by three simple rules:

1. Avoidance: Keep some distance from neighbors, to mimic a bird's tendency to avoid collisions with other birds.
2. Allignment: Try to match the direction that nearby boids are flying.
3. Cohesion: Try to steer towards the center of the local flock.

Implied is the ability to avoid the ground or boundaries.

### Implementation
This program first builds a little world for the boids to live in, which I call a terrarium. It then spawns in one or more flocks of boids. These flocks just define initial conditions, after t=0 the boids are free to split or merge into new flocks.

Each boid has a cone of vision and a sphere of influence. The cone of vision applies to rule 2, boids will only try to match the speed of the others directly in front of it. This leads to the "follow the leader" effect, where changes at the front of the flock propogate to the back. The sphere of influence applies to rules 1 and 3, meaning that boids will perceive the 'center' of a flock differently depending on where they are. This encourages clumping and flock separation, and puts a carrying capacity to the flock size.

This program also has a naïve implementation of spatial partitioning. It spawns exactly 1,280,000 empty containers representing sections of space in the terrarium. Boids need only check for their neighbors by querying the nearby containers, rather than searching against every other boid in the simulation. This speeds up the simulation when boids are spread out.

## Conclusion
### What I learned
While this was not my first particle simulation, this was my first time writing one where the particles interact with each other. I had to devise a spatial partitioning system, and I had to write the simulation to effectively update this system. I had a particularly tough debug session with this system, getting runtime errors semmingly at random, (Using vectors where lists were more appropriate).

### 3 years later
I spent a few hours cleaning up the code. When I wrote this, I had little concern for notes, readibility, or dependency inversion. I tried to put entire classes inside 500 line header files, and switching back and forth between `float` and `double`, and no consistency to speak of.

What I can't fix in a few hours are fundamental design issues. For whatever reason, I group flocks of boids by spawn, and keep referring to them like such, when it would make more sense to use a [state vector](https://en.wikipedia.org/wiki/State_variable), like I have done with every simulation I've written since. I've since learned how to use Octrees and BSP trees. So many things were hard-coded, and while I fixed as much of that as was reasonable, much more work would be needed to change that completely.

In short, it was ugly. But, I suppose it's good now that I can see that. I did my best for readibility, splitting up files, adding descriptive comments where I could, and injecting my preferred style now that I actually have one. While naming and overall organization are better, they're still hit and miss. This program is a good example of what I know how to do, and what I know not to do next time.
