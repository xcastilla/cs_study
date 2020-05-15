FROM alpine:3.11
RUN apk add --update make bash alpine-sdk
WORKDIR workspace
COPY . .
RUN make
