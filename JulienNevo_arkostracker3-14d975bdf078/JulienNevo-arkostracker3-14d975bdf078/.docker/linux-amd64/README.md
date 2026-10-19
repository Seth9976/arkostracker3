# Compile ArkosTracker 3 for Linux-amd64 with Docker

If you want:

- to compile Arkos-Tracker 3 locally
- not to have all its build toolchain and dependencies installed directly on your host

... and have docker handy, read on! \
Otherwise, well, good bye.

> 💡 All the shell commands are to be run from the project root directory.

## Create the build-image for AT3
First, we must create an image with all the necessary stuff installed inside: 
```sh
docker build \
	--file .docker/linux-amd64/Dockerfile \
	--build-arg UID=$(id -u) \
	--build-arg GID=$(id -g) \
	-t arkostracker-builder .
```
 
The project codebase will be live-mounted into the container. Your current UID/GID are forwarded there to create, in the container, a user with the exact same UID/GID as you. This user will then inherit the exact same file-permissions on the codebase than you.

### Update / Force-rebuild the image
```sh
docker build \
	--no-cache \
	--file .docker/linux-amd64/Dockerfile \
	--build-arg UID=$(id -u) \
	--build-arg GID=$(id -g) \
	-t arkostracker-builder .
```

### Delete the image from your host
```sh
docker image rm arkostracker-builder
```

## ...

## Profit
```sh
docker run -v ".:/srv/" --rm -it arkostracker-builder [COMMAND]
```

Where `COMMAND` can be any of:

- `release`: to compile a release-build (default command)
	- built executables available in `.docker/linux-amd64/release`
- `debug`: to compile a debug-build
	- built executables available in `.docker/linux-amd64/debug`
- `test`: to compile and run the unit-tests
- `clean`: to delete all the build artefacts
- `cicd`: validate CICD configuration

### git
If you cloned the AT3 repository from `git`, all the commands will be performed on the currently active branch (eg. checkout `develop` if you want to make a cutting-edge build).
