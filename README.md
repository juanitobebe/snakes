# Snakes
Gameboy Snake Game using [GBDK-2000](https://github.com/Zal0/gbdk-2020.git).

# Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.
When I have a playable version of this game you will be able to just download the release.

## Docker
Clone this repo somewhere and cd into it
```sh
$ git clone https://github.com/juanitobebe/snakes.git
$ cd snakes
```

Build my dockerfile to make [GBDK-2000](https://github.com/Zal0/gbdk-2020.git) (couldn't make it work from the releases 😜) and get all the dev environment for free
```sh
$ docker build --pull --rm -f "Dockerfile" -t snake:latest "."
```

Create a container to get everything in one place (Code and GBDK) and attach to it
```sh
# I have no idea what I'm doing.
$ SNAKE_DEV_ID=$(docker run -dit -P --name snake-dev -v $(pwd):/opt/snake snake:latest)
$ docker attach $SNAKE_DEV_ID
```

*Note, for subsequent runs you only need to do*: `docker start snake-dev --interactive`


Make it
```sh
cd snakes && make
```

Making will generate a ROM `bin/main.gb` that you can use to run Snakes.

# Contribuiting
This is one of my COVID-19 projects, I appreciate your input regarding Docker stuff and C development tips, but I won't be accepting PRs that actually add to the game.


