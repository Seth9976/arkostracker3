FROM cimg/base:2026.06

COPY ./.docker/linux-amd64/bin/setup-build-dependencies /usr/bin/

# setup everything we need
ARG UID=0
ARG GID=0
RUN sudo /bin/bash /usr/bin/setup-build-dependencies $UID $GID

# switch to our newly created build user with the same UID/GID as the host
USER $UID:$GID

# set our working directory to where the AT3 codebase will be mounted
WORKDIR "/srv"

# we want to use the container as a glorified shell command
ENTRYPOINT ["/bin/bash", ".docker/linux-amd64/bin/entry-point"]

# default to build a release
CMD ["release"]

