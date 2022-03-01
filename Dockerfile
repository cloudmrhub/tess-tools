FROM gcc:9
LABEL maintainer="Dr. Eros Montin, PhD <eros.montin@gmail.com>"
RUN set -ex;                                                                      \
    apt-get update;                                                               \
    apt-get install -y cmake libzmq3-dev;                                         \
    mkdir -p /usr/src;                                                            \
    cd /usr/src;                                                                  \
    curl -L https://github.com/zeromq/cppzmq/archive/v4.6.0.tar.gz | tar -zxf -;  \
    cd /usr/src/cppzmq-4.6.0;                                                     \
    cmake -D CPPZMQ_BUILD_TESTS:BOOL=OFF .; make; make install





RUN mkdir /src
COPY CpTemperature /src
RUN mkdir /celery_tasks
WORKDIR /celery_task
RUN cmake /src; make; make install



#sign!
RUN mkdir /cloudmr/
RUN echo "Tess muscle, \ built the " `date` "from user dock " $USER  >/cloudmr/buildversion.txt
ENTRYPOINT ["./cpptemperature"]
