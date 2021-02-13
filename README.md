# Snakes

Gameboy Snake Game using [GBDK-2020](https://github.com/Zal0/gbdk-2020.git).

![Snakes Alpha Gameplay](https://cdn.kapwing.com/final_5ecb3365a8e42400146f9bbe_765365.gif)

[Play Now](http://juanitobebe.github.io/GameBoy-Online?rom=https://github.com/juanitobebe/snakes/releases/latest/download/snakes.gb)

# Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.
When I have a playable version of this game you will be able to just download the release.

## Docker

Clone this repo somewhere and cd into it

```sh
$ git clone https://github.com/juanitobebe/snakes.git
$ cd snakes
```

Build my dockerfile to make [GBDK-2020](https://github.com/Zal0/gbdk-2020.git) (couldn't make it work from the releases 😜) and get all the dev environment for free

```sh
$ docker image build --pull --rm -f "Dockerfile" -t snake:latest "."
```

Build project with Docker:

```sh
docker container run --rm -it -P \                                                                                                                                                   ⇣0 B/s ⇡0 B/s 192.168.1.150    95.169.225.75   ─╯
--name snake-dev \
--user `id -u`:`id -g` \
-v $(pwd):/opt/snakes \
snake:latest \
make
```

Making will generate a ROM `bin/main.gb` that you can use to run Snakes.

# Contribuiting

This is one of my COVID-19 projects, I appreciate your input regarding Docker stuff and C development tips, but I won't be accepting PRs that actually add to the game.

