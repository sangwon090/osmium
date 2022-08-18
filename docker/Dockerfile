FROM alpine:latest

COPY build-binutils.sh /tmp
COPY build-gcc.sh /tmp

RUN apk update
RUN apk --no-cache add build-base curl bison flex gmp-dev mpc1-dev mpfr-dev texinfo grub-bios nasm xorriso

RUN chmod 755 /tmp/build-binutils.sh && chmod 755 /tmp/build-gcc.sh

RUN /tmp/build-binutils.sh
RUN /tmp/build-gcc.sh

RUN rm /tmp/build-binutils.sh /tmp/build-gcc.sh

ENV PATH /usr/local/cross/bin:$PATH