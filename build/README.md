# Build

Here are some instructions on how to build the static e-maxx-eng website.

```bash
cd e-maxx-eng
docker build -f build/Dockerfile . -t e-maxx-eng-builder
mkdir public
docker run -v $PWD/public:/output -e BASEURL="$PWD/public/" e-maxx-eng-builder:latest
```
`/output` is the directory where the Docker container will export the files to.
The `BASEURL` is the base of all urls. Per default it is [https://cp-algorithms.com](https://cp-algorithms.com).
