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

I even did a little bit GDScript with the rise of Godot. I did some tutorials through [GDQuest](https://www.gdquest.com/) and they were quite good as well. However I never quite took the extra step of the path of guided tutorials. I always felt like I "wanted" to make games, but never had the drive to really learn the "process" of making games. I liked "wanting" more than i liked "trying" and I feel like this is a common behavior with a particular type of person.

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

## The Actual Development of the Project
### My Development Configuration

I recently switch to [Linux Mint](https://www.linuxmint.com/) due to frustration with Windows 11 and things have been pretty swell. Development on Linux has been pretty breezy overall. I downloaded [SDL2 and SDL3](https://www.libsdl.org/) from the website and [VSCodium](https://vscodium.com/) did a most of the C/C++ configuration for me. I set up my Git repository and I was pretty much all set. 

I tried using the classic Linux editors like [emacs](https://www.gnu.org/software/emacs/) and [vim](https://www.vim.org/), but I couldn't quite get the hang of it. I grew up on Windows machines and I'm still rather unfamiliar with CLI style computing and text editing. They are great tools, but they are bit too old-school for me. I also tried [Zed](https://zed.dev/) for a bit during development (I disabled the AI features), but I didn't quite like that either. 

I also download the [Hack font](https://sourcefoundry.org/hack/) because I think it's really easy on my eyes. 

### 