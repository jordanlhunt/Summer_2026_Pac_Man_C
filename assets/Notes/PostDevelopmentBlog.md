# I Wrote A Rudimentary PAC-MAN Clone In C

(No generative AI was used in the writing of this, just want to address that off the rip. Also this isn't SEO'ed in anyway and I'm not trying to sell you anything. All the links are purely to provide context or credit)

### Table of Contents

* [About Me](#about-me)
* [What Inspired Me To Pick This Project](#what-inspired-me-to-pick-this-project)
* [My Programming Background](#my-programming-background)
* [Why I Didn't Originally Proceed With Game Development as a Hobby](#why-i-didnt-originally-proceed-with-game-development-as-a-hobby)
* [About The Project](#about-the-project)
* [Picking Where and How to Start](#picking-where-and-how-to-start)
* [Getting Lucky With The Dossier](#getting-lucky-with-the-dossier)
* [The Actual Development of the Project](#the-actual-development-of-the-project)
* [My Development Configuration](#my-development-configuration)


Hello Internet! I wrote an approximate reconstruction of PAC-MAN implementation in C using SDL2. My project isn't wholly a 1-to-1 arcade cabinet recreation but it get most of the fundamentals down. It was a really fun project and it helped me complete something from zero, which is often one of the advice you hear from independent game developers and computer programmers alike. This project was totally self-guided (often misguided) and free of generative AI usage. It was a project by me for me and it's many flaws and shortcomings are mine too. The whole project was learning experience that was meant to force me to buckle myself into my seat and write some C, do research, and commit myself to the learning the process. Overall, I think it went quite well and I'll share my thoughts in this blog. I also want to write more in general, so this will be an excellent means to practice communicating my thoughts and experiences.



## About Me

### What Inspired Me To Pick This Project

As is common with many computer programmers, I got interested in writing code since through playing games. I grew up playing games on the family computer along with reading comic-books, manga, and sci-fi novels. I also played tabletop games like [HeroClix](https://wizkids.com/heroclix/) and [MechWarrior: Dark Age](https://en.wikipedia.org/wiki/MechWarrior:_Dark_Age) and tabletop role-playing games like [Pathfinder](https://paizo.com/pathfinder), [Traveller](https://www.mongoosepublishing.com/collections/traveller-rpgs), [D20 Modern](https://en.wikipedia.org/wiki/D20_Modern), and many of the [White Wolf games](https://web.archive.org/web/20050308083942/http://www.white-wolf.com/). I played some Magic: The Gathering as well, I was always fond of Blue decks. Of the countless games I have played, the ones that made me want to learn how to make games were the marvelous [Cave Story+](https://cavestory.com/games/cavestory+) and [Bastion](https://www.supergiantgames.com/games/bastion/) in the year 2011.

Those two games really made me understand that video games could be both entertaining and also tell stories that really touch the player's heart. Prior and after I have played games that I loved and impacted me, but something about playing those two game at made me understand that games were made by people, and I could be a person who made games. Those games were were released during a time where online distribution and the very of idea an indie game were novel, and that really made me think "hey, I could make a game. I have cool idea...".

_For the record that "cool idea" has not come to fruition because it's not a "cool idea" and I still lack the skills to make my "dream game" come to life_

Fast-forward today I'm a 35 year old man going back to school to get computer science degree in the age of generative AI with hopes to get a job in the rapidly crumbling industry of video games. So after taking Computer Architecture in the Spring and seeing C++ in action with a really great professor who really inspired me to more actively engage with my learning I decided I needed a summer programming project. I wanted to do something outside my current ability level and something that would force me to learn something.

### My Programming Background

I actually have a previous Bachelor's degree in "Information Studies" on my first attempt at university. I genuinely cannot tell you what I learned in that degree program as I don't even know what it means. I essentially failed out of computer science my first time and I was luck enough to have an advisor who really cared about student success. She helped me scrape my credits together and bundle together to a degree so I could graduate in a timely fashion. I did a little bit of Python and Java in school but nothing larger than a homework program that did some I/O and a for loop or two.

I even managed to get a job after graduation and worked at a MEGACORP for a bit. I didn't really do much programming there either, it was a very small amount of JavaScript my first year and a moderate amount of SQL. I also learned proprietary software I will never see again before I quit because I wasn't going anywhere or doing anything and most importantly I was miserable.

All of my programming came from a couple of E-books on XNA/Monogame and a random smattering of online tutorials. When I first tried to learn game development it was "[XNA](https://en.wikipedia.org/wiki/Microsoft_XNA)" which later became the "[Monogame](https://monogame.net/)" that you see today. I originally picked books on Monogame because I learned that Bastion was written in Monogame. I would later play "Salt & Sanctuary" another excellent game also written in XNA. The XNA/Monogame books were are quite good and I'd highly recommend anyone interested in learning game development pick up Monogame. It's really beginner-friendly and the online community is really nice.

I even did a little bit GDScript with the rise of Godot. I did some tutorials through [GDQuest](https://www.gdquest.com/) and they were quite good as well. However I never quite took the extra step of the path of guided tutorials. I always felt like I "wanted" to make games, but never had the drive to really learn the "process" of making games. I liked "wanting" more than i liked "trying" and I feel like this is a common behavior with a particular type of person. You get infintenatly 

### Why I Didn't Originally Proceed With Game Development as a Hobby

The biggest issue in my programming background were primarily two things: lack of self-confidence in my programming ability and a lack of self-motivating discipline. Those two issues created a negative feedback loop that really hindered my ability to do anything outside of a very direct tutorial. It's really messed up because those two issues made getting better really hard. You can't get better as a programmer if you don't have the discipline and self-motivation try to solve harder problems, and you can't improve your discipline if you don't try to do anything outside your comfort-zone. A vicious cycle that kept me weight down and limited my digital horizons.

I read just about [magazine article](https://www.gamedeveloper.com/game-platforms) (remember when those were a thing?), [every blog](https://makegames.tumblr.com/post/1136623767/finishing-a-game), and [watched every developer interview on "how to be an indie developer" and all of them said](https://buy.indiegamethemovie.com/) "just make games". The "just" part for me was my biggest issue, I couldn't seem to "just" do something. My problem was I never really took that to heart because I never really believed I could do anything.

I didn't try hard enough mostly because I didn't want to fall short of my expectations. I think it's an elaborate means of procrastination to avoid disappointment ultimately. I don't know the exact reason but I spent far too long of my time in front of the computer not believing in myself. I did this project to prove to myself I can do something, even something hard and unknown. I also want to give my chance to make something that wasn't perfect. I also hope that anyone who may read this also internalizes the fact they too can do something.

I think I worked though though these limiting beliefs. At least enough for now. I know now I can do things, so long as I try hard and don't fight myself the entire time. I think this is true for anyone, I think we can all do great things.

## About The Project

### Picking Where and How to Start

I recently read ["Master's Of Doom"](https://www.penguinrandomhouse.com/books/96382/masters-of-doom-by-david-kushner/9780812972153/) book and it was a really good history lesson on nature of game development. I was really impressed that DOOM was written in C, and always was a bit scared of C. My Computer Architecture course had us write in C and C++ and it was really refreshing. John Romero also mentions really liking PAC-MAN in his ["DOOM Guy"](https://romero.com/shop/p/doomguy) autobiography so I chose the arcade classic of yesteryear.

I had done some C and C++ tutorials in previous ventures so I thought it would be an good reason to restart where I originally began. I did some of the [LazyFoo SDL2 tutorials](https://lazyfoo.net/) in the past but again nothing outside the tutorial guidelines. These tutorials are quite good and I'd recommend them as an intro to SDL. I also wanted to do something in the "old-school" sense and just to start from zero. I elected not to use generative AI software or tools for this project as well.

I wanted to focus on learning and I'm of the belief that learning comes from the mistakes you make and the struggle of trying to figure something out. Which is the least glamorous part of learning and the part I think most everything online seems to skip over. I think in the long term this choice will benefit me as a developer. It may slow me down and may not make as marketable but I do think it will help me be a better computer science student. 

I didn't do this project in one sitting, I didn't do this project on my first try, I didn't do a perfect recreation, and that's fine. I sturggled on a lot of things and had to look up a lot, but that was the goal so I see that as a success.

### Getting Lucky With The Dossier

When I picked a PAC-MAN clone, I knew I'd have to do some research on the game. During my initial research I discovered the [Pac-Man Dossier](https://pacman.holenet.info/), and it served as my design document. Strangely enough I discovered it through the gamedeveloper magazine website. This webpage was treasure trove of information both on the game as well as a great history lesson on the game.

The Dossier has a lot of great information. It was also something I could reference on what to research. Searching for programming or software help these days isn't that great. I modified my Ublock filters to get bad search results, and I had to edit my YouTube extensions to do filter out the many unrelated search results.

I would read something from the dossier, run into something I didn't know how to do and internet search for an example. Many of the examples i'd fine were not in C but in Java or Python which then lead me to research how to do something in C. That wasn't completely optimal workflow it did expose me to a lot of code and reading a lot of different thing is I think helpful.

The Dossier included a lot of the inner-working of PAC-MAN and saved me a lot of time on what to do but it wasn't a how-to guide. I really liked how with this project I had to figure "how" to do something, even though the dossier pretty clearly explain "what" was done, often even "why" something was done.

### My Development Configuration

I recently switch to [Linux Mint](https://www.linuxmint.com/) due to frustration with Windows 11 and things have been pretty swell. Development on Linux has been pretty breezy overall. I downloaded [SDL2 and SDL3](https://www.libsdl.org/) from the website and [VSCodium](https://vscodium.com/) did a most of the C/C++ configuration for me. I set up my Git repository and I was pretty much all set. 

I tried using the classic Linux editors like [emacs](https://www.gnu.org/software/emacs/) and [vim](https://www.vim.org/), but I couldn't quite get the hang of it. I grew up on Windows machines and I'm still rather unfamiliar with CLI style computing and text editing. They are great tools, but they are bit too old-school for me. I also tried [Zed](https://zed.dev/) for a bit during development (I disabled the AI features), but I didn't quite like that either. VSCodium and it's many extensions well suite all my needs. 

I also download the [Hack font](https://sourcefoundry.org/hack/) because I think it's really easy on my eyes. I think having a good font is important for development. If you're going to look at a screen with glyphs on it all day, you might as well have glyths that are aesthetically pleasing and present information clearly. There are [tons to choose from](https://www.programmingfonts.org/) and I think it gives your code some personality. Having 'l','1','i' all look different or 'O', '0', and '8' is one of those things you can't "unsee" once you switch fonts. I think it's a simple quality of life improvement for anyone who looks at screens, but especially for programmers. 

## What I Actually Learned During Development In A Technical Sense

### Headers

This was my first C project that had multiple files. I remember once did an assignment in community college that had one or two shared headers but that was it. My project grew I found that there was lot of code that needed to know where other code was. I had multiple instances of circular dependencies throughout my development process. The biggest culprit was `gamecontext.h` , `ecs.h`
, and `main.h` I think because those are the most involved pieces of code I have. 

I liked using headers because they are force you to create to think about function signatures and declaring constants ahead of time. It's sort of like pseudocode in that you don't quite know how something ought to be implemented but it gives you a general shape most of the time and you can easily modify. Having done this project in C I found it to be very particularly insightful in that C doesn't do a lot things for you. I was forced to learn about how forward declaration work and made sure my `.h` were populated with the proper data. Making sure functions signatures match in there `.c` and `.h` definition is important and I goofed that up often. 



### Separation of Concerns

At my first year at MEGACORP in my naive vigor to be a good employee I read a small amount [Heads First Design Patterns]([Head First Design Patterns [Book]](https://www.oreilly.com/library/view/head-first-design/0596007124/)) because it was available in the employee "library". The "library" being a bookcase full of full-throated Corpo propaganda, trite entrepreneur books and mid 90's MBA dreck, and religious conversion pamphlets. The design pattern book just caught me eye by chance and I read at my desk. 

I learned about "separation of concerns" from that book and I have seen and read that design pattern mentioned in a many of the game development tutorial as well. I tried to divide up as much as possible to make things do one thing or only handle one thing. Doing or handling one can be a rather broad statement but I think I managed to keep things small enough that the scope and context of anyone particular file could stay in my head.

`main.c` for example handles the game loop. Handling the game loop is main's job but handling the game loop means it has to coordinate a lot different things. Things like the `gamecontext` and the `sdlcontext` and all the various systems I ended up building. `main` had to handled all of those things but that mean all of those things themselves had to handle other things and often themselves. 

I like to think of separation of concerns a bit like toy blocks in each concern itself is a block you bind and bundle blocks together to create small chunks of the whole set. With `main` being the whole playset that contains all of the smaller sets you had built prior. Also much like a toy block set, it's can difficult to see how a single piece fits into the whole until you actually put it all together. During the very beginning of my the project I started with just `map.h`, `maptile.c`, and `maze.txt`. It's difficult to see how all of that will build into a larger game, but you can much more easily see how maptiles can be generated from the .txt file and be bundled together to create a map. 



### Entity Component System

The Entity Component System (ECS) what I'm actually most proud of in this project. I first heard of an ECS from the [Game Programming Patterns book](https://gameprogrammingpatterns.com/) I bought a long time ago. I read a little bit of before but I never read it cover to cover. I'm currently reading now as part of my mental recalibration toward reading more physical books every month. I don't rightly know if my project really *needed* an ECS, but was really fun to research what an ECS is, how an ECS can be used for my particular project, and implementing through trial and error. 

Making things an `Entity` that's defined by various IDs made thinking about the types of systems I needed a lot easier. I had `POSITION`, `VELOCITY`, `RENDERABLE` entity IDs so it me think I would need things like a `movementsystem`, `collisionsystem`,`renderSystem` and so on. Having an ECS made features like frightened mode, fruit spawning, and dot scoring easier to manage, since they’re just component changes or new entities rather than special‑case if‑chains.

This allowed me to focus more on "[Data-Oriented Design](https://en.wikipedia.org/wiki/Data-oriented_design)" which is something I hear/see often online to be a superior methodology to "[Object-oriented programming](https://en.wikipedia.org/wiki/Object-oriented_programming)". I don't know if was doing it correctly but I did see the value of Data-oriented programming. 


### Defensive Programming

I have never created anything particularly large in C and I didn't know how easy it is write code that "build" but doesn't run or runs but crashes as soon as you do something. Segmentation faults are a common trope online but I didn't realize how real it was until I started this project. I made sure to a `NULL` pointers were handled properly, either through a instant `return` or a some sort of output to console. C doesn't have all of the sort of niceties in something you'd get in something like Java. There aren't a lot of functions like `.length()` so you have to keep track of array bounds yourself. Just little things like that made me code with a bit more. I actually enjoy that in the sense it forces me to actively think about those sorts of thing. In a project like this where' it's just me, I didn't want to develop bad habits so I spent a some time reading StackOverflow and Programming related subreddits to get little bit of a general feel for what a C programmer shouldn't do. 

### The Basics of Git

I used Git and GitHub to store my code that allowed me to work on my home PC and the University PC with relative easy. Learning to `git add`, `git commit -m`, `git push`, and `git pull` became pretty natural. I used the GUI in VSCodium mostly but I also did several through the CLI as well. I even created for the entity component system. I thought it would be good way to try and develop something totally separate from the rest of the code. Once I got it work I was able to just merge it back into the main branch. It was relatively easy to create and merge. I would imagine if this project were more complex or had more contributors it'd be more important to track changes more rigorously but luckily I didn't have to worry about that at all.

### Pointers aren't that complex anymore

For the longest time I thought pointers were super confusing and unwieldily curiosities of the C language. With this project I have come to appreciate their value. A pointer is an address in memory, they referring to a value somewhere else. Dereferencing a pointer with `&` allows you access the value at that memory address. That's it. Pointers are often a tricky thing for CS students (myself included most certainly) but using them more frequently gets you into a groove and it starts to become more natural. One of the things that tripped me up remembering I wasn't always passing a pointer, sometimes I was passing the memory address of the value.  

### Other Design Patterns

I didn't do it intentionally but I did implement the Flyweight and Facade Patterns. The [Flyweight Pattern](https://en.wikipedia.org/wiki/Flyweight_pattern) is something I recognized from my previous Monogame/XNA development and using in my `graphics.c` seemed to make sense to me. I loaded the spritesheet of the PAC-MAN then is reused to draw every sprite draw call instead of loading duplicate texture for each entity. I didn't know the name of the Flyweight pattern and I had never seen any other way of drawing sprites.  

I also used the [Facade Pattern](https://en.wikipedia.org/wiki/Facade_pattern) another one I was unfamiliar with by name but I knew the general idea behind it before hand. In my `InitializeSDL()` method it's the single entry point for a more complex instructions. I didn't know that was a design pattern until re-reading the Heads Up Design patterns book and searching online for fundamental C programming software engineering recommendations

### The Importance Of Iteration

One of if not *the* most important things I learned in this project from a technical perspective is that programming is a very iterative process. A lot of my code is and git commit messages are full of message saying something is "sorta" working or I "fixed" something multiple times. Ideally, I'd like to be able to fix things *once* and be able to move forward on something else, but until then I think programming on my own is about getting something working and then getting something correct later, and then getting it "right" finally. 

I don't think it's critical to focus on getting everything right on my first try every time for everything when it comes to programming as I don't think that's a healthy way of looking at problem-solving. I think that' a hold over from our education system's test taking approach, in that they are one and done all-or-nothing exams. Working on a personal project gives you time to make mistakes and learn from them at much more lower stakes. 

Making mistakes, addressing the mistakes, and iterating is I think the purest loop of any programming project. There is no avoiding, and even trying to avoid is costly in time and understanding. Learning to use [gdb](https://sourceware.org/git/binutils-gdb.git), [valgrind](https://valgrind.org/), and [rubber ducking](https://en.wikipedia.org/wiki/Rubber_duck_debugging) are all essential skills for programming. In the same way creative writing involves a lot of re-writing, programming involves a lot of iteration. Sometimes it's a sign I going in the wrong direction, my project had many of those instances, but more often than it was I learned the most. 

## What I Actually Learned During Development in Moral Sense

### The Internet Warps Your Senses

I think there has been some sort of narrative in programming circles that everything is super fast and if you're not hacking together something near instantly you're not really a programmer. I started this project on April 9th and I'm finishing this post-development writeup on July 9th. Part of me feels like three months from zero to a functional prototype is rather good, however *speed* really one of the primary measures of value in our modern development culture. I think that's foolish and we are rewarding the wrong things for the wrong reasons in general. I didn't make the [killer-app](https://en.wikipedia.org/wiki/Killer_application) in three months and that's fine. That was never my objective. 

### Getting Better At Something Is Very Boring

Much like any other skill, art, or craft, getting better at programming is a very incremental and unremarkable. I know a lot of stuff I didn't know prior because of this project, however I can't just hack together a full arcade classic like [Centipede](https://en.wikipedia.org/wiki/Centipede_(video_game)) or [Bubble Bobble](https://en.wikipedia.org/wiki/Bubble_Bobble). I'll have to keep coding away and solving more problems to be able to put one of those games together from scratch.

### Knowing How My Tools Works Helps Me work

Knowing the basics of how my tools (All the various softwares I use) work makes using them to easier. Taking some time to learn hotkeys makes getting around VSCodium easier. Even just simple things like changing files with `CTRL+P` or go to symbol with `CTRL+T` helps reduce the friction of coding. There is a lot of friction already in development and a lot of it is totally necessary, but I shouldn't have friction going from one page to another. I'm going to learn more hotkeys and other CLI tools to help my development for my next project. 

### What's Next 

I'll probably make another clone of another arcade game, probably [Galaga](https://en.wikipedia.org/wiki/Galaga). It's a year older than PAC-MAN and more mechanically complex. I think that will be a good way to take a step and a half outside my current skillset and comfort zone. As that's were all the learning happens. 

Thank you for reading all of this.
